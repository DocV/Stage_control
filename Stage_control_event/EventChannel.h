#pragma once

#ifndef EVENTCHANNEL_H
#define EVENTCHANNEL_H

#include "stdafx.h"
#include "EventHandler.h"
#include <list>

namespace stage_control{

	class EventChannel{
	public:
		EventChannel(){}
		EventChannel(const EventChannel& other) = delete;
		EventChannel& operator= (const EventChannel& other) = delete;

		void registerRecipient(EventHandler* recipient){
			recipients.push_back(recipient);
		}
		void broadcast(const Event& e){
			for (std::list<EventHandler*>::iterator i = recipients.begin(); i != recipients.end(); i++){
				(*i)->handleEvent(e);
			}
		}
		void broadcastOthers(const Event& e, EventHandler* sender){
			for (std::list<EventHandler*>::iterator i = recipients.begin(); i != recipients.end(); i++){
				if (sender != *i) (*i)->handleEvent(e);
			}
		}
	private:
		
		std::list<EventHandler*> recipients;
	};

}

#endif