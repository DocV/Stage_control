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
	/** Komponentti, joka mahdollistaa 3D-mallin liittämisen peliolioon
	*/
	class ModelComponent : public Component {
	public:
		/** Luo uuden mallikomponentin. Katso oikea käyttö yliluokasta.
		@see			stage::component
		@param owner	Osoitin tämän olion omistavaan peliolioon
		@param mod		Osoitin siihen 3D-malliin, joka halutaan liittää tämän olion omistajaan
		*/
		ModelComponent(GameObject* owner, stage_common::Model* mod);

		/** Tuhoaa mallikomponentin
		*/
		~ModelComponent(){}

		/** Valmistelee mallin piirrettäväksi ruudulle
		*/
		virtual void render();

		/** Palauttaa mallikomponentin komponenttitunnuksen
		@returns	Mallikomponentin komponenttitunnus
		*/
		virtual int id(){ return MODEL_ID; }
	private:
		/** Osoitin tämän mallikomponentin 3D-malliin
		*/
		stage_common::Model* mod; //Jaettu useiden ModelComponent:ien kesken

		/** Osoitin olioon, joka esittää tämän komponentin omistavan peliolion sijaintia 3D-maailmassa
		*/
		Transform* position;
	};
}

#endif