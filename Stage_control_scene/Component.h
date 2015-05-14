#pragma once
#ifndef COMPONENT_H
#define COMPONENT_H

#include "stdafx.h"
#include "GameObject.h"

namespace stage_control{
	class Component{
	public:
		Component(GameObject* owner) : owner(owner){
			owner->addComponent(this);
		}
		~Component(){}
		GameObject& getOwner(){ return *owner; }
		virtual void update(int elapsedMS){}
		virtual void render(){}
		virtual int id() = 0;
	private:
		GameObject* owner;
	};
}

#endif