#pragma once
#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "stdafx.h"
#include <list>

namespace stage_control{
	class Component;

	/** Luokka, joka mallintaa yksittäisen peliolion.
	*/
	class GameObject{
		friend class Scene;
		friend class Component;
	public:
		/** Suorittaa pelisilmukan päivitysvaiheessa tapahtuvan laskennan
		@param elapsedMS	Edellisestä pelisilmukan suorituskerrasta kulunut aika
		*/
		void update(float elapsedMS);

		/** Suorittaa pelisilmukan piirtovaiheessa tapahtuvan laskennan
		*/
		void render();

		/** Hakee viitteen ensimmäiseen tähän olioon liitettyyn tiettyä tyyppiä olevaan komponenttiin
		@param id	Haettavan komponentin tyypin tunnusluku
		@returns	Osoitin haettavaan komponentiin tai nullptr, jos haluttua komponenttia ei ole
		*/
		Component* getComponentByID(int id);

		/** Tuhoaa peliolion
		*/
		~GameObject();

		/** Hakee tämän peliolion identifioivan tunnusluvun
		*/
		int getID(){ return id; }
	private:
		/** Tämän peliolion uniikki tunnusluku
		*/
		unsigned int id;

		/** Tähän peliolioon liitetyt komponentit
		*/
		std::list<Component*> components;

		/** Liittää tähän peliolioon uuden komponentin.
		@param comp		Osoitin liitettävään komponenttiin
		*/
		void addComponent(Component* comp);

		/** Luo uuden peliolion
		@param id	Tämän peliolion uniikki tunnusluku
		*/
		GameObject(int id) : components(), id(id){
		}

		/** Asettaa tämän peliolion tunnusluvun
		@param id	Uusi tunnusluku
		*/
		void setID(int id) { this->id = id; }
		
	};
}

#endif