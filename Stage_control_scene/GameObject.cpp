#include "stdafx.h"
#include "GameObject.h"
#include "Component.h"

using namespace stage_control;

void GameObject::update(int elapsedMS){
	for (std::list<Component*>::iterator it = components.begin(); it != components.end(); it++){
		(*it)->update(elapsedMS);
	}
}

void GameObject::render(){
	for (std::list<Component*>::iterator it = components.begin(); it != components.end(); it++){
		(*it)->render();
	}
}

Component* GameObject::getComponentByID(int id){
	for (std::list<Component*>::iterator it = components.begin(); it != components.end(); it++){
		if ((*it)->id() == id) return *it;
	}
	return nullptr;
}

void GameObject::addComponent(Component* comp){
	components.push_back(comp);
}