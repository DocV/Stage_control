#pragma once

#ifndef STATICGEOMETRYCOMPONENT_H
#define STATICGEOMETRYCOMPONENT_H

#define STATICGEOMETRYCOMPONENT_ID 5

#include "PhysicsComponent.h"

namespace stage_control{
	/** Pelioliokomponentti, joka mallintaa staattista, liikkumatonta törmäyshahmoa, kuten pelimaailman maastoa
	tai seiniä.*/
	class StaticGeometryComponent : public Component, public EventHandler{
	public:
		/** Luo uuden staattisen törmäyshahmon, joka käyttää pallotörmäyshahmoa
		@param owner	Komponentin omistava peliolio
		@param radius	Törmäyshahmon säde
		*/
		StaticGeometryComponent(GameObject* owner, float radius) : Component(owner){
			setup(owner);
			collider = new stage_common::SphereCollider(radius, transform->getPosition());
		}
		/** Luo uuden staattisen törmäyshahmon, joka käyttää AABB-törmäyshahmoa
		@param owner	Komponentin omistava peliolio
		@param radius	Törmäyshahmon koko
		*/
		StaticGeometryComponent(GameObject* owner, glm::vec3 size) : Component(owner){
			setup(owner);
			collider = new stage_common::AABBCollider(size, transform->getPosition());
		}
		/** Päivittää komponentin tilan
		@param elapsedMS	Edellisestä ruudunpäivityksestä kulunut aika
		*/
		void update(float elapsedMS){
			//Haetaan uudelleen sijainti, sillä jokin muu komponentti on voinut muuttaa sitä
			collider->center = transform->getPosition();
		}
		/** Käsittelee olion vastaanottamat tapahtumaviestit
		@param ev	Käsiteltävä viesti
		*/
		void handleEvent(const Event& ev){
			//Käsitellään vain törmäysviestit
			if (ev.getEventType() != PHYSICS_COLLISION_EVENT_TYPE) return;
			const PhysicsComponent::CollisionEvent& coll = (const PhysicsComponent::CollisionEvent&)ev;
			//Tarkistetaan, onko törmäys tapahtunut
			if (!collider->checkCollision(coll.collider)) return;
			glm::vec3 otherV = coll.sender.getVelocity();
			//Kimmotetaan toinen kappale tästä
			otherV = stage_common::Collisions::reflect(otherV, collider->getCollisionNormal(coll.collider, otherV));
			//Pyydetään toista kappaletta päivittämään tilansa
			coll.sender.processCollision(*collider, otherV);
		}
		/** Palauttaa staattisen törmäyshahmokomponentin komponenttitunnuksen
		@returns	Komponentin komponenttitunnus
		*/
		int id(){
			return STATICGEOMETRYCOMPONENT_ID;
		}
		/** Tuhoaa staattisen törmäyshahmokomponentin*/
		~StaticGeometryComponent(){
			delete collider;
		}
	private:
		/** Komponentin törmäyshahmo
		*/
		stage_common::Collider* collider;		
		/** Osoitin tämän komponentin omistajaolion pelimaailmasijaintia ylläpitävään komponenttiin
		*/
		Transform* transform;
		/** Kaikille konstruktoreille yhteinen apumetodi, joka alustaa peliolion tilan
		@param owner	Tämän komponentin omistava peliolio
		*/
		void setup(GameObject* owner){
			transform = (Transform*)(owner->getComponentByID(TRANSFORM_ID));
			PhysicsComponent::collisionChannel().registerRecipient(this);
		}
	};
}
#endif