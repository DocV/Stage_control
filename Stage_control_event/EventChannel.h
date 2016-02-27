#pragma once

#ifndef EVENTCHANNEL_H
#define EVENTCHANNEL_H

#include "stdafx.h"
#include "EventHandler.h"
#include <list>

namespace stage_control{
	/** Tapahtumajärjestelmän viestejä välittävä luokka*/
	class EventChannel{
	public:
		/** Luo uuden tapahtumakanavan*/
		EventChannel(){}
		EventChannel(const EventChannel& other) = delete;
		EventChannel& operator= (const EventChannel& other) = delete;
		/** Rekisteröi olion kanavan viestien vastaanottajaksi
		@param recipient	Olio, jolle halutaan välittää kanavan viestit
		*/
		void registerRecipient(EventHandler* recipient){
			recipients.push_back(recipient);
		}
		/** Lähettää viestin kaikille kanavaan rekisteröityneille olioille
		@param e	Lähetettävä viesti
		*/
		void broadcast(const Event& e){
			for (std::list<EventHandler*>::iterator i = recipients.begin(); i != recipients.end(); i++){
				(*i)->handleEvent(e);
			}
		}
		/** Lähettää viestin kaikille kanavaan rekisteröityneille olioille paitsi viestin lähettäjälle
		@param e		Lähetettävä viesti
		@param sender	Viestin lähettäjän osoite
		*/
		void broadcastOthers(const Event& e, EventHandler* sender){
			for (std::list<EventHandler*>::iterator i = recipients.begin(); i != recipients.end(); i++){
				if (sender != *i) (*i)->handleEvent(e);
			}
		}
	private:
		/** Lista tämän kanavan viestien vastaanottajiksi rekisteröidyistä olioista*/
		std::list<EventHandler*> recipients;
	};
}
#endif