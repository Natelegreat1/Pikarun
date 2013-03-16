
#ifndef __A2_521__Water__
#define __A2_521__Water__

#include <iostream>
#include "Entity.h"

class Water : public Entity{	
	public:
		double waterLevel;
	
	public:
		Water();
		virtual ~Water();
		void OnLoop();
		void OnRender(SDL_Surface* Surf_Display);
		void OnCleanup();
	
		void setLevel(double level);
};

#endif