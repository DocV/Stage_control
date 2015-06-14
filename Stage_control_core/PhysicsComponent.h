#ifndef PHYSICSCOMPONENT_H
#define PHYSICSCOMPONENT_H

#include "stdafx.h"
#include <Component.h>
#include <Collider.h>
#include <SphereCollider.h>
#include <AABBCollider.h>
#include <Transform.h>
#include <EventChannel.h>

#define PHYSICS_COLLISION_EVENT_TYPE 99001
#define PHYSICS_COLLISION_BACKOFF_RESOLUTION 5

namespace stage_control{
	class PhysicsComponent : public Component, public EventHandler{
	public:
		struct CollisionEvent : public Event{
			virtual unsigned int getEventType(){
				return PHYSICS_COLLISION_EVENT_TYPE;
			};
			const stage_common::Collider& collider;
			PhysicsComponent& sender;
			CollisionEvent(stage_common::Collider& coll, PhysicsComponent& sender) : collider(coll), sender(sender){}
		};
		
		PhysicsComponent(GameObject* owner, float radius, glm::vec3 center): Component(owner){
			collider = new stage_common::SphereCollider(radius, center);
			setup(owner);
		}
		PhysicsComponent(GameObject* owner, glm::vec3 size, glm::vec3 center) : Component(owner){
			collider = new stage_common::AABBCollider(size, center);
			setup(owner);
		}

		void update(float elapsedMS){
			if (!updatedThisFrame){
				updatePosition();
			}
			CollisionEvent ev(*collider, *this);
			collisionChannel().broadcast(ev);
		}

		void render(){
			updatedThisFrame = false;
		}

		void handleEvent(const Event& ev){
			if (!updatedThisFrame){
				updatePosition();
			}
			if (ev.getEventType != PHYSICS_COLLISION_EVENT_TYPE) return;
			const CollisionEvent& coll = (const CollisionEvent&)ev;
			if (!collider->checkCollision(coll.collider)) return;
			glm::vec3 otherNewV = coll.sender.getVelocity();
			stage_common::collisionVelocityChange(velocity, mass, otherNewV, coll.sender.getMass());
			coll.sender.processCollision(*collider, otherNewV);
		}

		void processCollision(const stage_common::Collider& coll, glm::vec3 newV){
			stage_common::backOff(*collider, velocity, coll, PHYSICS_COLLISION_BACKOFF_RESOLUTION);
			velocity = newV;
		}

		glm::vec3 getVelocity(){ return velocity; }
		float getMass(){ return mass; }

		~PhysicsComponent(){
			delete collider;
		}
	private:
		stage_common::Collider* collider;
		Transform* transform;
		glm::vec3 velocity;
		float mass;
		bool updatedThisFrame = false;

		void setup(GameObject* owner){
			transform = (Transform*)(owner->getComponentByID(TRANSFORM_ID));
			collisionChannel().registerRecipient(*this);
		}

		void updatePosition(){
			collider->center = transform->getPosition() + velocity;
			updatedThisFrame = true;
		}
		
		static EventChannel& collisionChannel(){
			static EventChannel cc;
			return cc;
		}
	};
}

#endif