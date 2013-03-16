
#ifndef __A2_521__Ground__
#define __A2_521__Ground__

#include <iostream>
#include "Entity.h"
#include "Define.h"
#include <cmath>
#include <vector>
#include <stdlib.h>

struct Vector2d{
	double x;
	double y;
};

class Ground : public Entity{

	private:
		std::vector<Vector2d *> points;

	public:
		Ground();
		virtual ~Ground();
		void OnLoop(Entity * wind);
		void OnRender(SDL_Surface * Surf_Display);
		void OnCleanup();
		void perlinize(double amplitude, int octaves);
		double getLowestPoint();
	
	private:
		void perlinizePoints(double amplitude);
		void addPoints();
};

#endif /* defined(__A2_521__Ground__) */
