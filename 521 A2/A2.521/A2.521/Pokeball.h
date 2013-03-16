
#ifndef __A2_521__Pokeball__
#define __A2_521__Pokeball__

#include <iostream>
#include "Entity.h"
#include "Wind.h"

class Pokeball : public Entity {
	private:
		SDL_Surface *	Surf_Pokeball;
		int bounceCount;
		int direction;
	
	public:
		Pokeball();
		virtual ~Pokeball();
				
		void OnAnimate();
		void OnLoop();
		void OnRender(SDL_Surface* Surf_Display);
		void OnCleanup();
	
		void checkDirection();
		bool isColliding(Entity * e);
		bool surfaceIntersection(Entity * e);
		bool projectileIntersection(Entity * e);
		void move();
};

#endif 