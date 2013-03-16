
#include "Water.h"

Water::Water() {
	TYPE = WATER;
	waterLevel = WHEIGHT;
}

Water::~Water() {	}


void Water::OnLoop() { }

void Water::OnRender(SDL_Surface * Surf_Display)
{
    if(Surf_Display == NULL) return;
	
	Uint32 color = SDL_MapRGB(Surf_Display->format,0x00, 0xce, 0xd1); // set water color
	
	// Draw water
	SDL_Rect waterRect;
	waterRect.x = 0;
	waterRect.y = WHEIGHT - waterLevel;
	waterRect.w = WWIDTH;
	waterRect.h = WHEIGHT - waterLevel;
	SDL_FillRect(Surf_Display, &waterRect, color);
}

void Water::OnCleanup()
{
    if(Surf_Entity) SDL_FreeSurface(Surf_Entity);
	
    Surf_Entity = NULL;
}

void Water::setLevel(double level)
{
	waterLevel = level;
	for (int i=0; i < WWIDTH; i++){
		heightMap[i] = WHEIGHT - waterLevel;
	}
}