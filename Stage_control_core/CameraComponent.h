#ifndef CAMERACOMPONENT_H
#define CAMERACOMPONENT_H

#define CAMERA_ID 2

#include "stdafx.h"
#include <Component.h>
#include <Camera.h>
#include <Transform.h>
#include <glm\gtc\matrix_transform.hpp>

namespace stage_control{
	class CameraComponent : public Component {
	public:
		CameraComponent(GameObject* owner) : Component(owner){
			position = (Transform*)owner->getComponentByID(TRANSFORM_ID);
			if (position == nullptr) abort();
		}
		CameraComponent(GameObject* owner, glm::mat4& initialProjection, glm::mat4& initialView) : Component(owner), cam(initialProjection, initialView){
			position = (Transform*)owner->getComponentByID(TRANSFORM_ID);
			if (position == nullptr) abort();
		}
		virtual int id(){ return CAMERA_ID; }
		virtual void render(){
			cam.setViewMatrix(position->getMatrix());
		}
		stage_common::Camera* getRawCamera(){
			return &cam;
		}
	private:
		Transform* position;
		stage_common::Camera cam;
	};
}

#endif