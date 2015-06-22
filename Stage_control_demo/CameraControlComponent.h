#pragma once

#include "stdafx.h"

#ifndef CAMERACONTROLCOMPONENT_H
#define CAMERACONTROLCOMPONENT_H

#define CAMERACONTROLCOMPONENT_ID 6
#define CAMERASPEED 0.025f
#define MOUSESPEED 0.01f

#include <Component.h>
#include <Transform.h>
#include <Input.h>
#include <GLFW\glfw3.h>
#include <SceneManager.h>

namespace stage_control{
	class CameraControlComponent : public Component{
	public:
		CameraControlComponent(GameObject* owner) : Component(owner){
			tr = (Transform*)(owner->getComponentByID(TRANSFORM_ID));
			stage_common::Input& in = stage_common::Input::getSingleton();
			in.registerKey(GLFW_KEY_W);
			in.registerKey(GLFW_KEY_S);
			in.registerKey(GLFW_KEY_A);
			in.registerKey(GLFW_KEY_D);
			in.registerKey(GLFW_KEY_R);
			in.registerKey(GLFW_KEY_F);
			in.registerKey(GLFW_KEY_ESCAPE);
		}

		void update(float elapsedMS){
			stage_common::Input& in = stage_common::Input::getSingleton();

			double horAngle = (in.getCursorX() - 0.5f) * MOUSESPEED * elapsedMS;
			double verAngle = (in.getCursorY() - 0.5f) * MOUSESPEED * elapsedMS;

			glm::quat rotation(glm::vec3(verAngle, horAngle, 0));

			glm::mat4 transform = tr->getMatrix();

			glm::vec3 movement(0,0,0);
			
			if (in.getKeyDown(GLFW_KEY_W)) movement += glm::vec3(transform[2]) * CAMERASPEED * elapsedMS;
			if (in.getKeyDown(GLFW_KEY_S)) movement -= glm::vec3(transform[2]) * CAMERASPEED  * elapsedMS;
			if (in.getKeyDown(GLFW_KEY_A)) movement += glm::vec3(transform[0]) * CAMERASPEED  * elapsedMS;
			if (in.getKeyDown(GLFW_KEY_D)) movement -= glm::vec3(transform[0]) * CAMERASPEED  * elapsedMS;
			if (in.getKeyDown(GLFW_KEY_F)) movement += glm::vec3(transform[1]) * CAMERASPEED  * elapsedMS;
			if (in.getKeyDown(GLFW_KEY_R)) movement -= glm::vec3(transform[1]) * CAMERASPEED  * elapsedMS;
			tr->translate(movement);

			if (in.getKeyDown(GLFW_KEY_ESCAPE)) SceneManager::getGlobalManager()->stop();
		}

		int id(){
			return CAMERACONTROLCOMPONENT_ID;
		}
	private:
		Transform* tr;
	};
}

#endif