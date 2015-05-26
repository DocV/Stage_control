#ifndef SCENE_H
#define SCENE_H

#include "stdafx.h"
#include "GameObject.h"
#include <list>

namespace stage_control{
	/** Pelimaailman alueen mallintava luokka
	*/
	class Scene{
	public:
		/** Luo uuden pelialueen
		*/
		Scene() : serial(0), objects(){
		}

		/** Tuhoaa pelialueen
		*/
		~Scene();


		/** Suorittaa pelisilmukan päivitysvaiheessa tapahtuvan laskennan
		@param elapsedMS	Edellisestä pelisilmukan suorituskerrasta kulunut aika
		*/
		void update(float elapsedMS);

		/** Suorittaa pelisilmukan piirtovaiheessa tapahtuvan laskennan
		*/
		void render();

		/** Luo pelimaailmaan uuden peliolion
		@returns	Viite luotuun peliolioon
		*/
		GameObject& createObject();
	private:
		/** Peliolioiden tunnusluvuista kirjaa pitävä laskuri
		*/
		unsigned int serial;

		/** Pelimaailmassa olevat pelioliot
		*/
		std::list<GameObject*> objects;
	};
}

#endif