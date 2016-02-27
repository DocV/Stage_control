#include "stdafx.h"
#include "SceneManager.h"

using namespace stage_control;

SceneManager* SceneManager::globalManager = nullptr;
stage_common::Logger* SceneManager::globalLogger = nullptr;

void SceneManager::setGlobalManager(SceneManager* mgr){
	globalManager = mgr;
}
SceneManager* SceneManager::getGlobalManager(){
	return globalManager;
}
stage_common::Logger& SceneManager::getGlobalLogger(){
	if (globalLogger == nullptr){
		abort();
	}
	return *globalLogger;
}