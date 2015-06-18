#pragma once
#ifndef TRANSFORM_H
#define TRANSFORM_H

#define TRANSFORM_ID 1

#include "stdafx.h"
#include "Component.h"
#include <glm\glm.hpp>
#include <glm\gtx\matrix_decompose.hpp>

namespace stage_control{
	/** Peliolion sijaintia pelimaailmassa mallintava luokka
	*/
	class Transform : public Component{
	public:
		/** Luo uuden sijaintikomponentin ja asettaa sijainnin origoon.
		Katso oikea käyttö yliluokasta.
		@see			stage_control::Component
		@param owner	Komponentin omistava peliolio
		*/
		Transform(GameObject* owner): Component(owner){
			transform = glm::mat4();
		}

		/** Luo uuden sijaintikomponentin.
		Katso oikea käyttö yliluokasta.
		@see			stage_control::Component
		@param owner	Komponentin omistava peliolio
		@param tr		Sijainti simulaation alussa
		*/
		Transform(GameObject* owner, const glm::mat4& tr) : Component(owner), transform(tr){}

		/** Palauttaa komponentin mallintamaa sijaintia kuvaavan 4x4-matriisin
		@returns	4x4-matriisi, joka kertoo, missä pelimaailman pisteessä komponentin omistava peliolio on
		*/
		glm::mat4 getMatrix() const{ return transform; }

		/** Asettaa komponentin mallintamaa sijaintia kuvaavan 4x4-matriisin
		@returns	4x4-matriisi, joka kertoo, missä pelimaailman pisteessä komponentin omistava peliolio on
		*/
		void setMatrix(const glm::mat4& tr){
			transform = tr;
		}

		glm::vec3 getPosition(){
			/*glm::vec3 ret;
			glm::vec3 dummy;
			glm::quat dummy2;
			glm::vec4 dummy3;
			glm::decompose(transform, dummy, dummy2, ret, dummy, dummy3);*/
			return glm::vec3(transform[3]);
		}

		void translate(glm::vec3 direction){
			transform = glm::translate(transform, direction);
		}

		/** Palauttaa sijaintikomponentin yksilöivän tunnusluvun
		@returns	Sijaintikomponentin tunnusluku
		*/
		virtual int id(){ return TRANSFORM_ID; }
	private:
		/** Komponentin omistavan peliolion sijaintia pelimaailmassa kuvaava 4x4-matriisi
		*/
		glm::mat4 transform;
	};
}

#endif