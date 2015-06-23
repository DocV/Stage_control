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

using namespace stage_control;

#define SCALE 25
#define SPHERES 100


int _tmain(int argc, _TCHAR* argv[])
{
	Gameloop loop(std::string("Stage control engine demo"), 640, 480);
	Scene scene;
	GameObject& obj1 = scene.createObject();
	//GameObject& obj2 = scene.createObject();
	//GameObject& obj3 = scene.createObject();
	
	Transform* tr1 = new Transform(&obj1);
	//Transform* tr2 = new Transform(&obj2);
	//Transform* tr3 = new Transform(&obj3);
	//tr2->setMatrix(glm::translate(glm::mat4(1.0f), glm::vec3(2, 0, -0)));
	tr1->setMatrix(glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, -SCALE * 2)));
	//tr3->setMatrix(glm::translate(glm::mat4(1.0f), glm::vec3(-1, 2, -0)));

	/*stage_common::SimpleShader ss;
	stage_common::Model mod(generate_sphere_vertices(), generate_sphere_colors(), &ss);
	stage_common::Model mod_plane(generate_plane_vertices(), generate_plane_colors(), &ss);*/
	
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

	/*ModelComponent* m2 = new ModelComponent(&obj2, &mod);
	ModelComponent* m3 = new ModelComponent(&obj3, &mod);

	PhysicsComponent* ph1 = new PhysicsComponent(&obj2, 1.0f, glm::vec3(-0.001f, -0.0005f, 0), 1.0f);
	PhysicsComponent* ph2 = new PhysicsComponent(&obj3, 1.0f, glm::vec3(0.00f, -0.0005f, 0), 1.0f);*/

	glm::mat4 Projection = glm::perspective(45.0f, 4.0f / 3.0f, 0.1f, SCALE * 10.0f);
	glm::mat4 View = glm::lookAt(
		glm::vec3(0, 0, -SCALE * 2),
		glm::vec3(0, 0, 0), 
		glm::vec3(0, 1, 0)  
	);



	CameraComponent* cam = new CameraComponent(&obj1, Projection, View);

	CameraControlComponent* ccc = new CameraControlComponent(&obj1);
	loop.setActiveScene(&scene);
	loop.setActiveCamera(cam);


	loop.start();

	char c;
	std::cin >> c;

	return 0;
}


