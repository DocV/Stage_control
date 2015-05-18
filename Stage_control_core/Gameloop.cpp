#pragma once

#include "stdafx.h"
#include <iostream>
#include <string>
#include "Gameloop.h"
#include <Timer.h>

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
		stage_common::Timer loopTimer;
		stage_common::Timer upTimer;
		stage_common::Timer rendTimer;
		stage_common::Timer maintTimer;

		while (!abort) {
			loopTimer.start();
			upTimer.start();
			activeScene->update(loopTimer.lastTickTime());
			upTimer.stop();
			rendTimer.start();
			activeScene->render();
			gc->draw(*cam);
			rendTimer.stop();
			maintTimer.start();
			if (gc->stopLoop) abort = true;
			maintTimer.stop();
			loopTimer.stop();
		}

		std::cout << "Total runtime: " << loopTimer.totalTime() << std::endl;
		std::cout << "Total frames: " << loopTimer.totalTicks() << std::endl;
		std::cout << "Average loop time: " << loopTimer.averageTime() << std::endl;
		std::cout << "Average update time: " << upTimer.averageTime() << std::endl;
		std::cout << "Average render time: " << rendTimer.averageTime() << std::endl;
		std::cout << "Average maintenance time: " << maintTimer.averageTime() << std::endl;
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