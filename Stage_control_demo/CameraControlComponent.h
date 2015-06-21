#pragma once

#include "stdafx.h"

#ifndef CAMERACONTROLCOMPONENT_H
#define CAMERACONTROLCOMPONENT_H

#define CAMERACONTROLCOMPONENT_ID 6
#define CAMERASPEED 0.025f

#include <Component.h>
#include <Transform.h>
#include <Input.h>
#include <GLFW\glfw3.h>

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
		}

		void update(float elapsedMS){
			glm::vec3 movement(0,0,0);
			stage_common::Input& in = stage_common::Input::getSingleton();
			if (in.getKeyDown(GLFW_KEY_W)) movement.z += CAMERASPEED * elapsedMS;
			if (in.getKeyDown(GLFW_KEY_S)) movement.z -= CAMERASPEED * elapsedMS;
			if (in.getKeyDown(GLFW_KEY_A)) movement.x += CAMERASPEED * elapsedMS;
			if (in.getKeyDown(GLFW_KEY_D)) movement.x -= CAMERASPEED * elapsedMS;
			if (in.getKeyDown(GLFW_KEY_F)) movement.y += CAMERASPEED * elapsedMS;
			if (in.getKeyDown(GLFW_KEY_R)) movement.y -= CAMERASPEED * elapsedMS;
			tr->translate(movement);
		}

		int id(){
			return CAMERACONTROLCOMPONENT_ID;
		}
	private:
		Transform* tr;
	};
}

#endif