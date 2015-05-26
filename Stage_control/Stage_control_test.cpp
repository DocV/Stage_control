// Stage_control.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <ModelComponent.h>
#include <Gameloop.h>
#include <Component.h>
#include <iostream>
#include <Utilities.h>
#include <glm\gtc\matrix_transform.hpp>
#include <SimpleShader.h>
#include <vector>

using namespace stage_control;

static std::vector<glm::vec3> vertices = {
	glm::vec3(-1.0f, -1.0f, -1.0f),
	glm::vec3(-1.0f, -1.0f, 1.0f),
	glm::vec3(-1.0f, 1.0f, 1.0f),
	glm::vec3(1.0f, 1.0f, -1.0f), // triangle 2 : begin
	glm::vec3(-1.0f, -1.0f, -1.0f),
	glm::vec3(-1.0f, 1.0f, -1.0f), // triangle 2 : end
	glm::vec3(1.0f, -1.0f, 1.0f),
	glm::vec3(-1.0f, -1.0f, -1.0f),
	glm::vec3(1.0f, -1.0f, -1.0f),
	glm::vec3(1.0f, 1.0f, -1.0f),
	glm::vec3(1.0f, -1.0f, -1.0f),
	glm::vec3(-1.0f, -1.0f, -1.0f),
	glm::vec3(-1.0f, -1.0f, -1.0f),
	glm::vec3(-1.0f, 1.0f, 1.0f),
	glm::vec3(-1.0f, 1.0f, -1.0f),
	glm::vec3(1.0f, -1.0f, 1.0f),
	glm::vec3(-1.0f, -1.0f, 1.0f),
	glm::vec3(-1.0f, -1.0f, -1.0f),
	glm::vec3(-1.0f, 1.0f, 1.0f),
	glm::vec3(-1.0f, -1.0f, 1.0f),
	glm::vec3(1.0f, -1.0f, 1.0f),
	glm::vec3(1.0f, 1.0f, 1.0f),
	glm::vec3(1.0f, -1.0f, -1.0f),
	glm::vec3(1.0f, 1.0f, -1.0f),
	glm::vec3(1.0f, -1.0f, -1.0f),
	glm::vec3(1.0f, 1.0f, 1.0f),
	glm::vec3(1.0f, -1.0f, 1.0f),
	glm::vec3(1.0f, 1.0f, 1.0f),
	glm::vec3(1.0f, 1.0f, -1.0f),
	glm::vec3(-1.0f, 1.0f, -1.0f),
	glm::vec3(1.0f, 1.0f, 1.0f),
	glm::vec3(-1.0f, 1.0f, -1.0f),
	glm::vec3(-1.0f, 1.0f, 1.0f),
	glm::vec3(1.0f, 1.0f, 1.0f),
	glm::vec3(-1.0f, 1.0f, 1.0f),
	glm::vec3(1.0f, -1.0f, 1.0f)
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
	glm::vec3(0.359f, 0.583f, 0.152f),
	glm::vec3(0.483f, 0.596f, 0.789f),
	glm::vec3(0.559f, 0.861f, 0.639f),
	glm::vec3(0.195f, 0.548f, 0.859f),
	glm::vec3(0.014f, 0.184f, 0.576f),
	glm::vec3(0.771f, 0.328f, 0.970f),
	glm::vec3(0.406f, 0.615f, 0.116f),
	glm::vec3(0.676f, 0.977f, 0.133f),
	glm::vec3(0.971f, 0.572f, 0.833f),
	glm::vec3(0.140f, 0.616f, 0.489f),
	glm::vec3(0.997f, 0.513f, 0.064f),
	glm::vec3(0.945f, 0.719f, 0.592f),
	glm::vec3(0.543f, 0.021f, 0.978f),
	glm::vec3(0.279f, 0.317f, 0.505f),
	glm::vec3(0.167f, 0.620f, 0.077f),
	glm::vec3(0.347f, 0.857f, 0.137f),
	glm::vec3(0.055f, 0.953f, 0.042f),
	glm::vec3(0.714f, 0.505f, 0.345f),
	glm::vec3(0.783f, 0.290f, 0.734f),
	glm::vec3(0.722f, 0.645f, 0.174f),
	glm::vec3(0.302f, 0.455f, 0.848f),
	glm::vec3(0.225f, 0.587f, 0.040f),
	glm::vec3(0.517f, 0.713f, 0.338f),
	glm::vec3(0.053f, 0.959f, 0.120f),
	glm::vec3(0.393f, 0.621f, 0.362f),
	glm::vec3(0.673f, 0.211f, 0.457f),
	glm::vec3(0.820f, 0.883f, 0.371f),
	glm::vec3(0.982f, 0.099f, 0.879f)
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
	stage_common::Model mod(vertices, colors, &ss);

	

	ModelComponent* m2 = new ModelComponent(&obj2, &mod);
	ModelComponent* m3 = new ModelComponent(&obj3, &mod);
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

