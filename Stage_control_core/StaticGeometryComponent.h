#pragma once

#ifndef STATICGEOMETRYCOMPONENT_H
#define STATICGEOMETRYCOMPONENT_H

#define STATICGEOMETRYCOMPONENT_ID 5

#include "PhysicsComponent.h"

namespace stage_control{
	class StaticGeometryComponent : public Component, public EventHandler{
	public:

		StaticGeometryComponent(GameObject* owner, float radius) : Component(owner){
			setup(owner);
			collider = new stage_common::SphereCollider(radius, transform->getPosition());
		}
		StaticGeometryComponent(GameObject* owner, glm::vec3 size) : Component(owner){
			setup(owner);
			collider = new stage_common::AABBCollider(size, transform->getPosition());
		}

		void update(float elapsedMS){
			collider->center = transform->getPosition();
		}

		void handleEvent(const Event& ev){

			if (ev.getEventType() != PHYSICS_COLLISION_EVENT_TYPE) return;
			const PhysicsComponent::CollisionEvent& coll = (const PhysicsComponent::CollisionEvent&)ev;
			if (!collider->checkCollision(coll.collider)) return;
			glm::vec3 otherV = coll.sender.getVelocity();
			otherV = stage_common::Collisions::reflect(otherV, collider->getCollisionNormal(coll.collider, otherV));
			coll.sender.processCollision(*collider, otherV);
		}

		int id(){
			return PHYSICSCOMPONENT_ID;
		}

		~StaticGeometryComponent(){
			delete collider;
			//TODO delete event channel entry
		}
	private:
		stage_common::Collider* collider;
		Transform* transform;

		void setup(GameObject* owner){
			transform = (Transform*)(owner->getComponentByID(TRANSFORM_ID));
			PhysicsComponent::collisionChannel().registerRecipient(this);
		}
	};
}

#endif