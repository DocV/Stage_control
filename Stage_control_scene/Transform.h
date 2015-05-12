#pragma once
#ifndef TRANSFORM_H
#define TRANSFORM_H

#define TRANSFORM_ID 1

#include "stdafx.h"
#include "Component.h"
#include <glm\glm.hpp>

namespace stage_control{
	class Transform : public Component{
	public:
		Transform(GameObject* owner): Component(owner){
			transform = glm::mat4();
		}
		Transform(GameObject* owner, glm::mat4& tr) : Component(owner), transform(tr){

		}
		glm::mat4 getMatrix() const{ return transform; }
		void setMatrix(glm::mat4& tr){
			transform = tr;
		}
		virtual int id(){ return TRANSFORM_ID; }
	private:
		glm::mat4 transform;
	};
}

#endif