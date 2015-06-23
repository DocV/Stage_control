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
#define PHYSICSCOMPONENT_ID 4

namespace stage_control{
	class PhysicsComponent : public Component, public EventHandler{
	public:
		struct CollisionEvent : public Event{
			virtual unsigned int getEventType() const {
				return PHYSICS_COLLISION_EVENT_TYPE;
			};
			const stage_common::Collider& collider;
			PhysicsComponent& sender;
			float elapsedMS;
			CollisionEvent(stage_common::Collider& coll, PhysicsComponent& sender, float elapsedMS)
				: collider(coll), sender(sender), elapsedMS(elapsedMS){}
		};
		
		PhysicsComponent(GameObject* owner, float radius, glm::vec3 initialV, float mass):
			Component(owner), velocity(initialV), mass(mass){
			setup(owner);
			collider = new stage_common::SphereCollider(radius, transform->getPosition());
			
		}
		PhysicsComponent(GameObject* owner, glm::vec3 size, glm::vec3 initialV, float mass) : 
			Component(owner), velocity(initialV), mass(mass){
			setup(owner);
			collider = new stage_common::AABBCollider(size, transform->getPosition());
			
		}

		void update(float elapsedMS){
			if (!updatedThisFrame){
				updatePosition(elapsedMS);
			}
			CollisionEvent ev(*collider, *this, elapsedMS);
			collisionChannel().broadcastOthers(ev, this);
			transform->translate(collider->center - oldPos);
		}

		void render(){
			updatedThisFrame = false;
		}

		void handleEvent(const Event& ev){
			
			if (ev.getEventType() != PHYSICS_COLLISION_EVENT_TYPE) return;
			const CollisionEvent& coll = (const CollisionEvent&)ev;
			if (!updatedThisFrame){
				updatePosition(coll.elapsedMS);
			}
			if (!collider->checkCollision(coll.collider)) return;
			glm::vec3 otherNewV = coll.sender.getVelocity();
			stage_common::Collisions::collisionVelocityChange(velocity, mass, otherNewV, coll.sender.getMass());
			coll.sender.processCollision(*collider, otherNewV);
		}

		void processCollision(const stage_common::Collider& coll, glm::vec3 newV){
			stage_common::Collisions::backOff(*collider, -1.0f * newV, coll);
			velocity = newV;
		}

		glm::vec3 getVelocity(){ return velocity; }
		float getMass(){ return mass; }

		~PhysicsComponent(){
			delete collider;
			//TODO delete event channel entry
		}

		int id(){
			return PHYSICSCOMPONENT_ID;
		}

		static EventChannel& collisionChannel(){
			static EventChannel cc;
			return cc;
		}
	private:
		stage_common::Collider* collider;
		Transform* transform;
		glm::vec3 velocity;
		glm::vec3 oldPos;
		float mass;
		bool updatedThisFrame = false;

		void setup(GameObject* owner){
			transform = (Transform*)(owner->getComponentByID(TRANSFORM_ID));
			collisionChannel().registerRecipient(this);
		}

		void updatePosition(float elapsedMS){
			oldPos = transform->getPosition();
			collider->center = oldPos + (velocity * elapsedMS);
			updatedThisFrame = true;
		}
		
	};
}

#endif