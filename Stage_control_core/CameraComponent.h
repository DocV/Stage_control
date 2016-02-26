#ifndef CAMERACOMPONENT_H
#define CAMERACOMPONENT_H

#define CAMERA_ID 2

#include "stdafx.h"
#include <Component.h>
#include <Camera.h>
#include <Transform.h>
#include <glm\gtc\matrix_transform.hpp>

namespace stage_control{
	/** Peliolioon liitettävä komponenttiolio, joka mallintaa kameran.*/
	class CameraComponent : public Component {
	public:
		/** Luo uuden kamerakomponentin oletusasetuksilla (45 asteen fov, kuvasuhde 4:3, piirtoetäisyys 0.1-100, suunnattu origoon).
		Katso oikea käyttö yliluokasta.
		@param owner	Osoitin tämän komponentin omistavaan peliolioon
		*/
		CameraComponent(GameObject* owner);
		/** Luo uuden kamerakomponentin ja asettaa kameran alkutilan. Katso oukea käyttö yliluokasta.
		@param owner				Osoitin tämän komponentin omistavaan peliolioon
		@param initialProjection	Kameran projektiomatriisi simulaation alussa
		@param initialView			Kameran näkymämatriisi simulaation alussa
		*/
		CameraComponent(GameObject* owner, glm::mat4& initialProjection, glm::mat4& initialView);
		/** Palauttaa kamerakomponentin komponenttitunnuksen
		@returns	Kamerakomponentin komponenttitunnus
		*/
		virtual int id(){ return CAMERA_ID; }
		/** Valmistelee kameran ruudun piirtämistä varten*/
		virtual void render();
		/** Hakee osoittimen kamerakomponentin kameraolioon
		@returns	osoitin kameraolioon
		*/
		stage_common::Camera* getRawCamera(){ return &cam; }
	private:
		/** Osoitin kamerakomponentin omistavan peliolion sijaintia ylläpitävään olioon	*/
		Transform* position;
		/** Kameran tilaa ylläpitävä olio*/
		stage_common::Camera cam;
	};
}
#endif