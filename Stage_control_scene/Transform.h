#pragma once
#ifndef TRANSFORM_H
#define TRANSFORM_H

#define TRANSFORM_ID 1

#include "stdafx.h"
#include "Component.h"
#include <glm\glm.hpp>

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
		Transform(GameObject* owner, glm::mat4& tr) : Component(owner), transform(tr){}

		/** Palauttaa komponentin mallintamaa sijaintia kuvaavan 4x4-matriisin
		@returns	4x4-matriisi, joka kertoo, missä pelimaailman pisteessä komponentin omistava peliolio on
		*/
		glm::mat4 getMatrix() const{ return transform; }

		/** Asettaa komponentin mallintamaa sijaintia kuvaavan 4x4-matriisin
		@returns	4x4-matriisi, joka kertoo, missä pelimaailman pisteessä komponentin omistava peliolio on
		*/
		void setMatrix(glm::mat4& tr){
			transform = tr;
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