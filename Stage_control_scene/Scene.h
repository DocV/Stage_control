#ifndef SCENE_H
#define SCENE_H

#include "stdafx.h"
#include "GameObject.h"
#include <list>

namespace stage_control{
	class Scene{
	public:
		Scene() : serial(0), objects(){
		}
		~Scene();

		void update(int elapsedMS);
		void render();

		GameObject& createObject();
		//TODO bool destroyObject(unsigned int id);
	private:
		unsigned int serial;
		std::list<GameObject*> objects;
	};
}

#endif