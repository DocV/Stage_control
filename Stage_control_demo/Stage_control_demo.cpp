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

using namespace stage_control;

static std::vector<glm::vec3> vertices = {
	glm::vec3(-1.000000, 1.000000, -1.000000),
	glm::vec3(-1.000000, -1.000000, -1.000000),
	glm::vec3(-1.000000, -1.000000, 1.000000),
	glm::vec3(1.000000, 1.000000, -1.000000),
	glm::vec3(1.000000, -1.000000, -1.000000),
	glm::vec3(-1.000000, -1.000000, -1.000000),
	glm::vec3(1.000000, 1.000000, 1.000000),
	glm::vec3(1.000000, -1.000000, 1.000000),
	glm::vec3(1.000000, -1.000000, -1.000000),
	glm::vec3(-1.000000, 1.000000, 1.000000),
	glm::vec3(-1.000000, -1.000000, 1.000000),
	glm::vec3(1.000000, -1.000000, 1.000000),
	glm::vec3(-1.000000, -1.000000, -1.000000),
	glm::vec3(1.000000, -1.000000, -1.000000),
	glm::vec3(1.000000, -1.000000, 1.000000),
	glm::vec3(1.000000, 1.000000, -1.000000),
	glm::vec3(-1.000000, 1.000000, -1.000000),
	glm::vec3(-1.000000, 1.000000, 1.000000),
	glm::vec3(-1.000000, 1.000000, 1.000000),
	glm::vec3(-1.000000, 1.000000, -1.000000),
	glm::vec3(-1.000000, -1.000000, 1.000000),
	glm::vec3(-1.000000, 1.000000, -1.000000),
	glm::vec3(1.000000, 1.000000, -1.000000),
	glm::vec3(-1.000000, -1.000000, -1.000000),
	glm::vec3(1.000000, 1.000000, -1.000000),
	glm::vec3(1.000000, 1.000000, 1.000000),
	glm::vec3(1.000000, -1.000000, -1.000000),
	glm::vec3(1.000000, 1.000000, 1.000000),
	glm::vec3(-1.000000, 1.000000, 1.000000),
	glm::vec3(1.000000, -1.000000, 1.000000),
	glm::vec3(-1.000000, -1.000000, 1.000000),
	glm::vec3(-1.000000, -1.000000, -1.000000),
	glm::vec3(1.000000, -1.000000, 1.000000),
	glm::vec3(1.000000, 1.000000, 1.000000),
	glm::vec3(1.000000, 1.000000, -1.000000),
	glm::vec3(-1.000000, 1.000000, 1.000000)
};
static std::vector<glm::vec3> colors = {
	glm::vec3(0.583f, 0.771f, 0.014f),
	glm::vec3(0.609f, 0.115f, 0.436f),
	glm::vec3(0.327f, 0.483f, 0.844f),
	glm::vec3(0.822f, 0.569f, 0.201f),
	glm::vec3(0.435f, 0.602f, 0.223f),
	glm::vec3(0.310f, 0.747f, 0.185f),
	glm::vec3(0.597f, 0.770f, 0.761f),
	glm::vec3(0.559f, 0.436f, 0.730f),
	glm::vec3(0.583f, 0.771f, 0.014f),
	glm::vec3(0.609f, 0.115f, 0.436f),
	glm::vec3(0.327f, 0.483f, 0.844f),
	glm::vec3(0.822f, 0.569f, 0.201f),
	glm::vec3(0.435f, 0.602f, 0.223f),
	glm::vec3(0.310f, 0.747f, 0.185f),
	glm::vec3(0.597f, 0.770f, 0.761f),
	glm::vec3(0.559f, 0.436f, 0.730f),
	glm::vec3(0.583f, 0.771f, 0.014f),
	glm::vec3(0.609f, 0.115f, 0.436f),
	glm::vec3(0.327f, 0.483f, 0.844f),
	glm::vec3(0.822f, 0.569f, 0.201f),
	glm::vec3(0.435f, 0.602f, 0.223f),
	glm::vec3(0.310f, 0.747f, 0.185f),
	glm::vec3(0.597f, 0.770f, 0.761f),
	glm::vec3(0.559f, 0.436f, 0.730f),
	glm::vec3(0.435f, 0.602f, 0.223f),
	glm::vec3(0.310f, 0.747f, 0.185f),
	glm::vec3(0.597f, 0.770f, 0.761f),
	glm::vec3(0.559f, 0.436f, 0.730f),
	glm::vec3(0.583f, 0.771f, 0.014f),
	glm::vec3(0.609f, 0.115f, 0.436f),
	glm::vec3(0.327f, 0.483f, 0.844f),
	glm::vec3(0.822f, 0.569f, 0.201f),
	glm::vec3(0.435f, 0.602f, 0.223f),
	glm::vec3(0.310f, 0.747f, 0.185f),
	glm::vec3(0.597f, 0.770f, 0.761f),
	glm::vec3(0.559f, 0.436f, 0.730f)
	
};


class Testprinter : public Component {
public:
	Testprinter(GameObject* owner) : Component(owner){}
	void update(float elapsedMS){
		std::cout << "object " << getOwner().getID() << " updating after " << elapsedMS << " ms." << std::endl;
	}
	void render(){
		std::cout << "object " << getOwner().getID() << " rendering." << std::endl;
	}
	virtual int id(){
		return 99;
	}
};
class Vibrate : public Component {
public:
	Vibrate(GameObject* owner) : Component(owner){
		position = (Transform*)(owner->getComponentByID(TRANSFORM_ID));
	}
	void update(float elapsedMS){
		float rand1 = (float)(std::rand() % 100) / 1000 - 0.05;
		float rand2 = (float)(std::rand() % 100) / 1000 - 0.05;
		float rand3 = (float)(std::rand() % 100) / 1000 - 0.05;
		position->setMatrix(glm::translate(position->getMatrix(), glm::vec3(rand1, rand2, rand3)));
	}
	void render(){
	}
	virtual int id(){
		return 99;
	}
private:
	Transform* position;
};

int _tmain(int argc, _TCHAR* argv[])
{
	Gameloop loop(std::string("testapp"), 640, 480);
	Scene scene;
	GameObject& obj1 = scene.createObject();
	GameObject& obj2 = scene.createObject();
	GameObject& obj3 = scene.createObject();

	Testprinter* printer1 = new Testprinter(&obj1);
	Testprinter* printer2 = new Testprinter(&obj2);
	Testprinter* printer3 = new Testprinter(&obj3);

	Transform* tr1 = new Transform(&obj1);
	Transform* tr2 = new Transform(&obj2);

	Transform* tr3 = new Transform(&obj3);
	tr2->setMatrix(glm::translate(glm::mat4(1.0f), glm::vec3(2, 0, -5)));
	tr1->setMatrix(glm::mat4(1.0f));
	tr3->setMatrix(glm::translate(glm::mat4(1.0f), glm::vec3(-1, 0, -5)));

	stage_common::SimpleShader ss;
	stage_common::Model mod(generate_sphere_vertices(), generate_sphere_colors(), &ss);
	stage_common::Model mod_plane(generate_plane_vertices(), generate_plane_colors(), &ss);



	ModelComponent* m2 = new ModelComponent(&obj2, &mod);
	ModelComponent* m3 = new ModelComponent(&obj3, &mod_plane);
	Vibrate* v2 = new Vibrate(&obj2);
	Vibrate* v3 = new Vibrate(&obj3);

	glm::mat4 Projection = glm::perspective(45.0f, 4.0f / 3.0f, 0.1f, 100.0f);
	glm::mat4 View = glm::lookAt(
		glm::vec3(0, 0, 5), // Camera is at (4,3,3), in World Space
		glm::vec3(0, 0, 0), // and looks at the origin
		glm::vec3(0, 1, 0)  // Head is up (set to 0,-1,0 to look upside-down)
		);



	CameraComponent* cam = new CameraComponent(&obj1, Projection, View);
	loop.setActiveScene(&scene);
	loop.setActiveCamera(cam);


	loop.start();

	char c;
	std::cin >> c;

	return 0;
}

