#ifndef MODELCOMPONENT_H
#define MODELCOMPONENT_H

#define MODEL_ID 3

#include "stdafx.h"
#include <Component.h>
#include <GameObject.h>
#include <Model.h>
#include <Transform.h>
#include <GraphicsController.h>
#include <Shader.h>

namespace stage_control{
	class ModelComponent : public Component {
	public:
		ModelComponent(GameObject* owner, stage_common::Model* mod) :
			Component(owner), mod(mod){
			position = (Transform*)owner->getComponentByID(TRANSFORM_ID);
			if (position == nullptr) abort();
		}
		~ModelComponent(){

		}
		virtual void render(){
			stage_common::GraphicsController::getGlobalController()->queue(mod, position->getMatrix());
		}
		virtual int id(){ return MODEL_ID; }
	private:
		stage_common::Model* mod; //Jaettu useiden ModelComponent:ien kesken
		Transform* position;
	};
}

#endif