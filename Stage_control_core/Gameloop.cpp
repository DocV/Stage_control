#pragma once

#include "stdafx.h"
#include <iostream>
#include <string>
#include "Gameloop.h"
//#include "GameObject.h"

using namespace stage_control;

namespace stage_control {

	float Gameloop::getTimescale() {
		return timescale;
	}
	void Gameloop::setTimescale(float ts) {
		timescale = ts;
	}
	void Gameloop::start() {

		if (activeScene != nullptr && cam !=nullptr)
			loop();
	}
	void Gameloop::stop(){
		abort = true;
	}
	void Gameloop::loop() {
		while (!abort) {
			activeScene->update(1);
			activeScene->render();
			gc->draw(*cam);
		}
		shutdown();
	}
	void Gameloop::shutdown(){
		std::cout << "shutting down";
	}

	void Gameloop::setActiveScene(Scene* scene){
		activeScene = scene;
	}

	void Gameloop::setActiveCamera(CameraComponent* cam){
		this->cam = (cam->getRawCamera());
	}
};