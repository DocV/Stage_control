#include "stdafx.h"
#include "SceneManager.h"

using namespace stage_control;

SceneManager* SceneManager::globalManager = nullptr;

void SceneManager::setGlobalManager(SceneManager* mgr){
	globalManager = mgr;
}

SceneManager* SceneManager::getGlobalManager(){
	if (globalManager == nullptr){
		abort();
	}
	return globalManager;
}