#ifndef GAMEOBJECTFACTORY_H
#define GAMEOBJECTFACTORY_H

#include "stdafx.h"
#include "Plane.h"
#include "Sphere.h"
#include <Scene.h>
#include <glm\glm.hpp>
#include <PhysicsComponent.h>
#include <StaticGeometryComponent.h>
#include <ModelComponent.h>
#include <SimpleShader.h>

namespace stage_control{
	class GameObjectFactory{
	public:
		static GameObject& constructRandomSphere(Scene* sc, glm::vec3 maxCoordinates){
			GameObject& obj = sc->createObject();
			glm::vec3 translation(randomFloat(-maxCoordinates.x, maxCoordinates.x),
				randomFloat(-maxCoordinates.y, maxCoordinates.y),
				randomFloat(-maxCoordinates.z, maxCoordinates.z));
			glm::mat4 transform = glm::translate(glm::mat4(1.0f), translation);
			Transform* tf = new Transform(&obj, transform);
			ModelComponent* mod = new ModelComponent(&obj, &(getSingleton().mod_sphere));
			glm::vec3 velocity(randomFloat(-0.01f, 0.01f), randomFloat(-0.01f, 0.01f), randomFloat(-0.01f, 0.01f));
			PhysicsComponent* pc = new PhysicsComponent(&obj, 1.0f, velocity, 1.0f);
			return obj;
		}
		static GameObject& constructWall(Scene* sc, const glm::mat4& transform, glm::vec3 size){
			GameObject& obj = sc->createObject();
			Transform* tf = new Transform(&obj, transform);
			ModelComponent* mod = new ModelComponent(&obj, &(getSingleton().mod_plane));
			StaticGeometryComponent* sgc = new StaticGeometryComponent(&obj, size);
			return obj;
		}
	private:
		stage_common::SimpleShader ss;
		stage_common::Model mod_sphere;
		stage_common::Model mod_plane;

		static GameObjectFactory& getSingleton(){
			static GameObjectFactory gof;
			return gof;
		}

		static float randomFloat(float start, float end){
			float random = ((float)rand()) / (float)RAND_MAX;
			return start + (end - start) * random;
		}

		GameObjectFactory() : mod_sphere(generate_sphere_vertices(), generate_sphere_colors(), &ss),
			mod_plane(generate_plane_vertices(), generate_plane_colors(), &ss){
		}
	};
}

#endif