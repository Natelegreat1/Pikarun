
#ifndef __A2_521__Surface__
#define __A2_521__Surface__

#include <iostream>
#include <SDL/SDL.h>

class Surface {
	public:
		Surface();
		virtual ~Surface();
	
	public:
		static SDL_Surface * OnLoad(char * File);
		static bool OnDraw(SDL_Surface * Surf_Dest, SDL_Surface * Surf_Src, int X, int Y);
		static bool OnDraw(SDL_Surface * Surf_Dest, SDL_Surface * Surf_Src, int X, int Y, int X2, int Y2, int W, int H);
};

#endif /* defined(__A2_521__Surface__) */
