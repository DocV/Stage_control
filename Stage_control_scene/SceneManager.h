#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H

#include "stdafx.h"
#include "Scene.h"

namespace stage_control{
	class SceneManager{
	public:
		virtual void start(){}
		virtual void stop(){}
		virtual void setActiveScene(Scene* scene){}
		static SceneManager* getGlobalManager();
	protected:
		static void setGlobalManager(SceneManager* mgr);		
	private:
		static SceneManager* globalManager;
	};
}

#endif