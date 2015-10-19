#pragma once

#include "stdafx.h"
#include <iostream>
#include <string>
#include "Gameloop.h"
#include <Timer.h>
#include <Input.h>

using namespace stage_control;

Gameloop::Gameloop(std::string& windowName, int xres, int yres) : activeScene(nullptr){

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

Gameloop::~Gameloop(){
	if (SceneManager::getGlobalManager() == this) SceneManager::setGlobalManager(NULL);
	delete gc;
	delete globalLogger;
}

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
	stage_common::Timer upTimer;
	stage_common::Timer rendTimer;
	stage_common::Timer maintTimer;

	while (!abort) {
		loopTimer.start();
		//Päivitysvaihe
		upTimer.start();
		activeScene->update(loopTimer.lastTickTime());
		upTimer.stop();
		//Piirtovaihe
		rendTimer.start();
		activeScene->render();
		gc->draw(*cam);
		rendTimer.stop();
		//Ylläpitovaihe
		maintTimer.start();
		if (gc->shouldStop()) abort = true;
		stage_common::Input::getSingleton().update(resetMouse);
		maintTimer.stop();
		loopTimer.stop();
	}

	std::cout << "Total runtime: " << loopTimer.totalTime() << std::endl;
	std::cout << "Total frames: " << loopTimer.totalTicks() << std::endl;
	std::cout << "Average loop time: " << loopTimer.averageTime() << std::endl;
	std::cout << "Average fps: " << std::to_string(1000 / loopTimer.averageTime()) << std::endl;
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

unsigned int Gameloop::getCurrentFrame(){
	return loopTimer.totalTicks();
}