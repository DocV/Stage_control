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
	/** Peliolioon liitettävä komponentti, joka liittää peliolioon nopeuden ja törmäystentunnistuksen*/
	class PhysicsComponent : public Component, public EventHandler{
	public:
		/** Viesti, jolla kysytään, onko lähettäjä törmännyt vastaanottajaan*/
		struct CollisionEvent : public Event{
			virtual unsigned int getEventType() const {
				return PHYSICS_COLLISION_EVENT_TYPE;
			};
			/** Viite lähettäjän törmäyshahmoon*/
			const stage_common::Collider& collider;
			/** Viite lähettäjäolioon*/
			PhysicsComponent& sender;
			/** Edellisestä ruudunpäivityksestä kulunut aika*/
			float elapsedMS;
			CollisionEvent(stage_common::Collider& coll, PhysicsComponent& sender, float elapsedMS)
				: collider(coll), sender(sender), elapsedMS(elapsedMS){}
		};		
		/** Luo uuden fysiikkakomponentin, joka käyttää pallotörmäyshahmoa
		@param owner	Komponentin omistava peliolio
		@param radius	Törmäyshahmon säde
		@param initialV	Peliolion nopeus simulaation alussa
		@param mass		Peliolion massa
		*/
		PhysicsComponent(GameObject* owner, float radius, glm::vec3 initialV, float mass):
			Component(owner), velocity(initialV), mass(mass){
			setup(owner);
			collider = new stage_common::SphereCollider(radius, transform->getPosition());			
		}
		/** Luo uuden fysiikkakomponentin, joka käyttää AABB-törmäyshahmoa
		@param owner	Komponentin omistava peliolio
		@param radius	Törmäyshahmon säde
		@param initialV	Peliolion nopeus simulaation alussa
		@param mass		Peliolion massa
		*/
		PhysicsComponent(GameObject* owner, glm::vec3 size, glm::vec3 initialV, float mass) : 
			Component(owner), velocity(initialV), mass(mass){
			setup(owner);
			collider = new stage_common::AABBCollider(size, transform->getPosition());			
		}
		/** Päivittää fysiikkakomponentin tilan
		@param elapsedMS	Edellisestä ruudunpäivityksestä kulunut aika millisekunteina
		*/
		void update(float elapsedMS){
			//Siirretään törmäyshahmoa vain, jos tilaa ei ole vielä päivitetty törmäysviestin seurauksena
			if (!updatedThisFrame){
				updatePosition(elapsedMS);
			}
			//Lähetetään muille fysiikkakomponenteille tieto törmäyshahmon liikkeestä
			CollisionEvent ev(*collider, *this, elapsedMS);
			collisionChannel().broadcastOthers(ev, this);
			//Päivitetään peliolion sijainti vastaamaan törmäyshahmon uutta sijaintia
			transform->translate(collider->center - oldPos);
		}
		void render(){
			//Resetoidaan tilan päivittämisen kieltävä muuttuja update-kutsujen välissä
			updatedThisFrame = false;
		}
		/** Käsittelee olion vastaanottamat tapahtumaviestit
		@param ev	Käsiteltävä viesti
		*/
		void handleEvent(const Event& ev){
			//Käsitellään vain törmäysviestit
			if (ev.getEventType() != PHYSICS_COLLISION_EVENT_TYPE) return;
			const CollisionEvent& coll = (const CollisionEvent&)ev;
			//Jos tilaa ei vielä ole päivitetty tämän ruudunpäivityksen aikana, päivitetään se nyt
			if (!updatedThisFrame){
				updatePosition(coll.elapsedMS);
			}
			//Tarkistetaan, onko törmäys tapahtunut
			if (!collider->checkCollision(coll.collider)) return;
			//Jos törmäys on tapahtunut, lasketaan molemmille kappaleille uudet nopeudet
			glm::vec3 otherNewV = coll.sender.getVelocity();
			stage_common::Collisions::collisionVelocityChange(velocity, mass, otherNewV, coll.sender.getMass());
			//Pyydetään toista kappaletta päivittämään tilansa
			coll.sender.processCollision(*collider, otherNewV);
		}
		/** Päivittää peliolion tilan ottamaan huomioon tapahtunut törmäys
		@param coll	Se törmäyshahmo, johon tämä olio törmäsi
		@param newV	Tämän olion uusi nopeus törmäyksen jälkeen
		*/
		void processCollision(const stage_common::Collider& coll, glm::vec3 newV){
			//Siirretään oliota, kunnes se ei enää törmää
			stage_common::Collisions::backOff(*collider, -1.0f * newV, coll);
			//Asetetaan uusi nopeus
			velocity = newV;
		}
		/** Hakee tämän olion nykyisen nopeuden
		@returns	Olion nopeusvektori
		*/
		glm::vec3 getVelocity(){ return velocity; }
		/** Hakee tämän olion massan
		@returns	Olion massa
		*/
		float getMass(){ return mass; }
		/**Tuhoaa fysiikkakomponentin*/
		~PhysicsComponent(){
			delete collider;
		}
		/** Palauttaa fysiikkakomponentin komponenttitunnuksen
		@returns	Komponentin komponenttitunnus
		*/
		int id(){
			return PHYSICSCOMPONENT_ID;
		}
		/** Hakee viitteen fysiikkamoottorin törmäystestien tapahtumakanavaan
		@returns	Viite tapahtumakanavaan
		*/
		static EventChannel& collisionChannel(){
			//Staattinen kanava-singleton, jaettu kaikkien fysiikkakomponenttien kesken
			static EventChannel cc;
			return cc;
		}
	private:
		/** Tämän peliolion törmäyshahmo*/
		stage_common::Collider* collider;
		/** Osoitin tämän komponentin omistajaolion pelimaailmasijaintia ylläpitävään komponenttiin*/
		Transform* transform;
		/** Tämän fysiikkaolion liikesuunta ja nopeus*/
		glm::vec3 velocity;
		/** Tämän fysiikkaolion liikesuunta ja nopeus nykyisen ruudunpäivityksen alussa*/
		glm::vec3 oldPos;
		/** Tämän fysiikkaolion massa*/
		float mass;
		/** Ilmoittaa, onko tämän peliolion tila jo päivitetty tämän ruudunpäivityksen aikana*/
		bool updatedThisFrame = false;
		/** Molemmille konstruktoreille yhteinen apumetodi, joka alustaa peliolion tilan
		@param owner	Tämän komponentin omistava peliolio
		*/
		void setup(GameObject* owner){
			transform = (Transform*)(owner->getComponentByID(TRANSFORM_ID));
			collisionChannel().registerRecipient(this);
		}
		/** Päivittää fysiikkaolion sijainnin pelimaailmassa olion nopeuden perusteella
		@param elapsedMS	Edellisestä ruudunpäivityksestä kulunut aika
		*/
		void updatePosition(float elapsedMS){
			oldPos = transform->getPosition();
			collider->center = oldPos + (velocity * elapsedMS);
			updatedThisFrame = true;
		}		
	};
}
#endif