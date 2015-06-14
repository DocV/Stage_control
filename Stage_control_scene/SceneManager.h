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

		virtual unsigned int getCurrentFrame() = 0;

		/** Hakee osoittimen globaaliin alueita hallinnoivaan olioon
		@returns	Osoitin globaaliin SceneManager-singletoniin
		*/
		static SceneManager* getGlobalManager();

		/** Hakee viitteen globaaliin lokiolioon
		@returns	Viite globaaliin Logger-singletoniin
		*/
		static stage_common::Logger& getGlobalLogger();
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