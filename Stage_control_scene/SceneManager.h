#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H

#include "stdafx.h"
#include "Scene.h"
#include <Logger.h>

namespace stage_control{
	class SceneManager{
	public:
		virtual void start(){}
		virtual void stop(){}
		virtual void setActiveScene(Scene* scene){}
		static SceneManager* getGlobalManager();
		static stage_common::Logger& getGlobalLogger();
	protected:
		static void setGlobalManager(SceneManager* mgr);	
		static stage_common::Logger* globalLogger;
	private:
		static SceneManager* globalManager;
	};
}

#endif