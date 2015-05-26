#pragma once
#ifndef COMPONENT_H
#define COMPONENT_H

#include "stdafx.h"
#include "GameObject.h"

namespace stage_control{
	/** Abstrakti yliluokka peliolioon liitettäville komponenteille.
	*/
	class Component{
	public:
		/** Luo uuden komponentin.
		HUOM: komponentti on aina luotava new:lla ja on luonnin jälkeen omistajaolionsa hallinnassa.
		Komponentti tuhotaan automaattisesti omistajolion tuhoutuessa.
		@param owner	Osoitin komponentin omistavaan peliolioon
		*/
		Component(GameObject* owner) : owner(owner){
			owner->addComponent(this);
		}

		/** Tuhoaa komponentin
		*/
		~Component(){}

		/** Palauttaa osoittimen komponentin omistavaan peliolioon
		@returns	Osoitin tämän komponentin omistajaolioon
		*/
		GameObject& getOwner(){ return *owner; }

		/** Suorittaa pelisilmukan päivitysvaiheessa tapahtuvan laskennan
		@param elapsedMS	Edellisestä pelisilmukan suorituskerrasta kulunut aika
		*/
		virtual void update(float elapsedMS){}

		/** Suorittaa pelisilmukan piirtovaiheessa tapahtuvan laskennan
		*/
		virtual void render(){}

		/** Palauttaa tämän komponentin tarkan tyypin määrittelevän tunnusluvun
		*/
		virtual int id() = 0;
	private:
		/** Osoitin tämän komponentin omistajaolioon
		*/
		GameObject* owner;
	};
}

#endif