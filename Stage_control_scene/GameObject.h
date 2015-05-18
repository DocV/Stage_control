#pragma once
#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "stdafx.h"
#include <list>

namespace stage_control{
	class Component;
	class GameObject{
		friend class Scene;
		friend class Component;
	public:
		void update(float elapsedMS);
		void render();
		Component* getComponentByID(int id);
		~GameObject();
		int getID(){ return id; }
	private:
		unsigned int id;
		std::list<Component*> components;
		void addComponent(Component* comp);

		GameObject(int id) : components(), id(id){
		}
		void setID(int id) { this->id = id; }
		
	};
}

#endif