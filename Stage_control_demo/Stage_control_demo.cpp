// Stage_control_demo.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <ModelComponent.h>
#include <Gameloop.h>
#include <Component.h>
#include <iostream>
#include <glm\gtc\matrix_transform.hpp>
#include <SimpleShader.h>
#include <vector>
#include "Sphere.h"
#include "Plane.h"
#include <PhysicsComponent.h>
#include "GameObjectFactory.h"
#include "CameraControlComponent.h"
#include <fstream>

using namespace stage_control;


int _tmain(int argc, _TCHAR* argv[])
{
	int SCALE = 10;
	int SPHERES = 5;
	std::string configfile;
	std::ifstream configStream("config.ini", std::ios::in);

	if (configStream.is_open())
	{
		std::string line = "";
		std::string start, end;
		int delimiterPos;
		while (getline(configStream, line)){
			delimiterPos = line.find("=");
			if (delimiterPos == std::string::npos){
				std::cerr << "Invalid configuration parameter " << start << std::endl;
				continue;
			}
			start = line.substr(0, delimiterPos);
			end = line.substr(delimiterPos+1);
			if (start == "SCALE"){
				try{
					SCALE = std::stoi(end);
					if (SCALE < 5) SCALE = 5;
				}
				catch(...){
					std::cerr << "Error parsing configuration parameter SCALE" << std::endl;
					continue;
				}
			}
			else if (start == "SPHERES"){
				try{
					SPHERES = std::stoi(end);
					if (SPHERES < 1) SPHERES = 1;
				}
				catch (...){
					std::cerr << "Error parsing configuration parameter SCALE" << std::endl;
					continue;
				}
			}
			else std::cerr << "Unknown configuration parameter " << start << std::endl;
		}
		configStream.close();
	}
	else std::cerr << "Warning: config.ini not found, falling back to default parameters" << std::endl;

	Gameloop loop(std::string("Stage control engine demo"), 640, 480);
	Scene scene;
	
	glm::mat4 bottompos;
	bottompos = glm::scale(bottompos, glm::vec3(SCALE, 1, SCALE));
	bottompos = glm::translate(bottompos, glm::vec3(0, -SCALE, 0));
	GameObject& bottom = GameObjectFactory::constructWall(&scene, bottompos, glm::vec3(SCALE, 0, SCALE));

	glm::mat4 toppos;
	toppos = glm::rotate(toppos, glm::radians(180.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	toppos = glm::translate(toppos, glm::vec3(0, -SCALE, 0));
	toppos = glm::scale(toppos, glm::vec3(SCALE, 1, SCALE));
	GameObject& top = GameObjectFactory::constructWall(&scene, toppos, glm::vec3(SCALE, 0, SCALE));

	glm::mat4 leftpos;
	leftpos = glm::rotate(leftpos, glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
	leftpos = glm::translate(leftpos, glm::vec3(0, -SCALE, 0));
	leftpos = glm::scale(leftpos, glm::vec3(SCALE, 1, SCALE));
	GameObject& left = GameObjectFactory::constructWall(&scene, leftpos, glm::vec3(0, SCALE, SCALE));

	glm::mat4 rightpos;
	rightpos = glm::rotate(rightpos, glm::radians(-90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
	rightpos = glm::translate(rightpos, glm::vec3(0, -SCALE, 0));
	rightpos = glm::scale(rightpos, glm::vec3(SCALE, 1, SCALE));
	GameObject& right = GameObjectFactory::constructWall(&scene, rightpos, glm::vec3(0, SCALE, SCALE));

	glm::mat4 backpos;
	backpos = glm::rotate(backpos, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	backpos = glm::translate(backpos, glm::vec3(0, -SCALE, 0));
	backpos = glm::scale(backpos, glm::vec3(SCALE, 1, SCALE));
	GameObject& back = GameObjectFactory::constructWall(&scene, backpos, glm::vec3(SCALE, SCALE, 0));

	glm::mat4 frontpos;
	frontpos = glm::rotate(frontpos, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	frontpos = glm::translate(frontpos, glm::vec3(0, -SCALE, 0));
	frontpos = glm::scale(frontpos, glm::vec3(SCALE, 1, SCALE));
	GameObject& front = GameObjectFactory::constructWall(&scene, frontpos, glm::vec3(SCALE, SCALE, 0));

	for (int i = 0; i < SPHERES; i++){
		GameObject& sphere = GameObjectFactory::constructRandomSphere(&scene, glm::vec3(SCALE - 1, SCALE - 1, SCALE - 1));
	}


	GameObject& camera = scene.createObject();

	Transform* camPos = new Transform(&camera);
	camPos->setMatrix(glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, -SCALE * 2)));

	glm::mat4 Projection = glm::perspective(45.0f, 4.0f / 3.0f, 0.1f, SCALE * 10.0f);
	glm::mat4 View = glm::lookAt(
		glm::vec3(0, 0, -SCALE * 2),
		glm::vec3(0, 0, 0), 
		glm::vec3(0, 1, 0)  
	);

	CameraComponent* cam = new CameraComponent(&camera, Projection, View);
	CameraControlComponent* ccc = new CameraControlComponent(&camera);

	loop.setActiveScene(&scene);
	loop.setActiveCamera(cam);


	loop.start();

	char c;
	std::cin >> c;

	return 0;
}


