#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H

#include "stdafx.h"
#include "Scene.h"
#include <Logger.h>

namespace stage_control{
	/** Abstrakti singleton-luokka, joka hallinnoi pelimaailman alueita
	*/
	class SceneManager{
	public:
		/** Asettaa pelin aktiivisen pelialueen
		@param scene	Osoitin uuteen aktiiviseen pelialueeseen
		*/
		virtual void setActiveScene(Scene* scene) = 0;

		/** Palauttaa pelimoottorin käynnistämisestä kuluneiden ruudunpäivitysten määrän
		@returns	Pelimoottorin käynnistämisestä kuluneiden ruudunpäivitysten määrä
		*/
		virtual unsigned int getCurrentFrame() = 0;

		/** Hakee osoittimen globaaliin alueita hallinnoivaan olioon
		@returns	Osoitin globaaliin SceneManager-singletoniin
		*/
		static SceneManager* getGlobalManager();

		/** Hakee viitteen globaaliin lokiolioon
		@returns	Viite globaaliin Logger-singletoniin
		*/
		static stage_common::Logger& getGlobalLogger();

		/** Pysäyttää ohjelman suorituksen
		*/
		virtual void stop() = 0;
	protected:
		/** Asettaa globaalin pelialueidenhallintaolion arvon
		@param mgr	Osoitin globaaliin SceneManager-singletoniin
		*/
		static void setGlobalManager(SceneManager* mgr);

		/** Osoitin globaaliin Logger-singletoniin
		*/
		static stage_common::Logger* globalLogger;
	private:
		/** Osoitin globaaliin SceneManager-singletoniin
		*/
		static SceneManager* globalManager;
	};
}

#endif