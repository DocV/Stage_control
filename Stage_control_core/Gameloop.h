#ifndef GAMELOOP_H
#define GAMELOOP_H

#include "stdafx.h"
#include <Scene.h>
#include <SceneManager.h>
#include <GraphicsController.h>
#include "CameraComponent.h"

namespace stage_control{
	class Gameloop : public SceneManager{
	public:
		Gameloop(std::string& windowName, int xres, int yres) : activeScene(nullptr){
			
			gc = new stage_common::GraphicsController(windowName, xres, yres);
			if (globalLogger != nullptr){
				globalLogger->LogError("Error: global logger already set. Aborting.");
				std::abort();
			}
			globalLogger = new stage_common::Logger(std::cout, std::cerr);
			if (SceneManager::getGlobalManager() != nullptr){
				globalLogger->LogError("Error: global scene manager already set. Aborting.");
				std::abort();
			}
			SceneManager::setGlobalManager(this);
		}
		float getTimescale();
		void setTimescale(float ts);
		void start();
		void stop();
		void setActiveScene(Scene* scene);
		void setActiveCamera(CameraComponent* cam);
		~Gameloop(){
			if (SceneManager::getGlobalManager() == this) SceneManager::setGlobalManager(NULL);
			delete gc;
			delete globalLogger;
		}
	private:
		Scene* activeScene;
		stage_common::GraphicsController* gc;
		stage_common::Camera* cam;
		float timescale = 1;
		bool abort = false;
		void loop();
		void shutdown();
	};
}

#endif