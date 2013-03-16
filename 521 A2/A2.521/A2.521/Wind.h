
#ifndef __A2_521__Wind__
#define __A2_521__Wind__

#include <iostream>
#include "Entity.h"
#include "Surface.h"
#include <cstdlib>

class Wind : public Entity {
	private:
		SDL_Surface *	Surf_WindL;
		SDL_Surface *	Surf_WindR;
		int t;
	
	public:
		Wind();
		virtual ~Wind();
			
		void OnAnimate();
		void OnLoop();
		void OnRender(SDL_Surface* Surf_Display);
		void OnCleanup();
	
		void updateSpeed();
};

#endif
