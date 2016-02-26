#include "stdafx.h"
#include "ModelComponent.h"

using namespace stage_control;

ModelComponent::ModelComponent(GameObject* owner, stage_common::Model* mod) :
	Component(owner), mod(mod){
	position = (Transform*)owner->getComponentByID(TRANSFORM_ID);
	if (position == nullptr) abort();
}
void ModelComponent::render(){
	stage_common::GraphicsController::getGlobalController()->queue(mod, position->getMatrix());
}