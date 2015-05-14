#include "stdafx.h"
#include "Scene.h"

using namespace stage_control;

void Scene::update(int elapsedMS){
	for (std::list<GameObject*>::iterator it = objects.begin(); it != objects.end(); it++){
		(*it)->update(elapsedMS);
	}
}

void Scene::render(){
	for (std::list<GameObject*>::iterator it = objects.begin(); it != objects.end(); it++){
		(*it)->render();
	}
}

GameObject& Scene::createObject(){
	GameObject* newObject = new GameObject(serial);
	serial++;
	objects.push_back(newObject);
	return *newObject;
}

Scene::~Scene(){
	for (std::list<GameObject*>::iterator it = objects.begin(); it != objects.end(); it++){
		delete *it;
	}
}