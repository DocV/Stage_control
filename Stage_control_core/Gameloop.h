#ifndef GAMELOOP_H
#define GAMELOOP_H

#include "stdafx.h"
#include <Scene.h>
#include <SceneManager.h>
#include <GraphicsController.h>
#include <Timer.h>
#include "CameraComponent.h"

namespace stage_control{
	/** Pelisilmukan mallintava luokka
	*/
	class Gameloop : public SceneManager{
	public:
		/** Luo uuden pelisilmukan ja avaa ikkunan
		@param windowName	Ikkunan nimi
		@param xres			Ikkunan vaakaresoluutio
		@param yres			Ikkunan pystyresoluutio
		*/
		Gameloop(std::string& windowName, int xres, int yres);
		/** Hakee pelisilmukan aikaskaalan (pelin simulointinopeus)
		@returns	Pelin aikaskaala
		*/
		float getTimescale();
		/** Asettaa pelisilmukan aikaskaalan(pelin simulointinopeus)
		@returns	Pelin aikaskaala
		*/
		void setTimescale(float ts);
		/** Käynnistää pelisilmukan suorituksen*/
		void start();
		/** Pysäyttää pelisilmukan suorituksen. Kutsuttava ennen pelisilmukan tuhoamista.*/
		void stop();
		/** Asettaa pelin aktiivisen pelialueen
		@param scene	Aktiivinen pelialue
		*/
		void setActiveScene(Scene* scene);
		/** Asettaa pelin aktiivisen kameran
		@param scene	Aktiivinen kamera
		*/
		void setActiveCamera(CameraComponent* cam);
		/** Palauttaa pelimoottorin käynnistämisestä kuluneiden ruudunpäivitysten määrän
		@returns	Pelimoottorin käynnistämisestä kuluneiden ruudunpäivitysten määrä
		*/
		unsigned int getCurrentFrame();
		/** Tuhoaa pelisilmukkaolion. Kutsu ensin stop-metodia, jotta pelisilmukka voidaan tuhota turvallisesti.*/
		~Gameloop();
	private:
		/** Aktiivinen pelialue, eli se pelialue, jonka tilaa päivitetään ja joka piirretään ruudulle*/
		Scene* activeScene;
		/** Pelin grafiikkamoottoria hallinnoiva olio*/
		stage_common::GraphicsController* gc;
		/** Pelin aktiivinen kamera, eli se kamera, jonka kuvakulmasta pelimaailma näytetään*/
		stage_common::Camera* cam;
		/** Pelisilmukan suoritusaikaa mittaava ajastin*/
		stage_common::Timer loopTimer;
		/** Lukitaanko hiiri keskelle kuvaruutua?*/
		bool resetMouse = false;
		/** Pelin aikaskaala, eli pelisimulaation suoritusnopeus*/
		float timescale = 1;
		/** Ilmoittaa, pitääko pelisilmukan suoritus pysäyttää nykyisen silmukan jälkeen*/
		bool abort = false;
		/** Suorittaa pelisilmukkaa, kunnes pysäytysmetodia kutsutaan*/
		void loop();
		/** Viimeistelee pelisilmukan suorituksen lopettamisen ja varmistaa, että pelisilmukka voidaan tuhota turvallisesti*/
		void shutdown();
	};
}
#endif