#ifndef WAITER_H
#define WAITER_H

#define WAITER_ID 7

#include "stdafx.h"
#include <Component.h>

namespace stage_control{
	/**Pelioliokomponentti, joka simuloi raskasta laskentaa etsimällä jokaisen ruudunpäivityksen aikana tietyn määrän alkulukuja*/
	class Waiter : public Component{
	public:
		/**Luo uuden Waiter-komponentin
		@param owner	Komponentin omistava peliolio
		@param limit	Se luku, johon asti alkulukuja etsitään
		*/
		Waiter(GameObject* owner, int limit) : 
			Component(owner), limit(limit){}
		/**Suorittaa komponentin päivitysvaiheen laskennan eli kuluttaa aikaa etsimällä alkulukuja
		@param elapsedMS	Edellisestä ruudunpäivityksestä kulunut aika
		*/
		virtual void update(float elapsedMS){
			for (int i = 3; i <= limit; i++){
				for (int j = 2; j < i; j++){
					if (i % j == 0) break;
				}
			}
		}
		/** Hakee Waiter-komponentin komponenttitunnuksen
		@returns	Komponentin komponenttitunnus
		*/
		virtual int id(){ return WAITER_ID; }
	private:
		/**Se luku, johon asti tämä komponentti laskee alkulukuja jokaisen ruudunpäivityksen aikana*/
		int limit;
	};
}
#endif