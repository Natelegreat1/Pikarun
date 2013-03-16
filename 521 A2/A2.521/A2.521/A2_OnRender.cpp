#include "A2_OnRender.h"
#include "A2.h"
#include <time.h>

void A2::OnRender()
{	
	//Clear the screen 
	SDL_Rect fullScreen;
	fullScreen.x = fullScreen.y = 0;
	fullScreen.w = Surf_Display->w;
	fullScreen.h = Surf_Display->h;
	SDL_FillRect(Surf_Display, &fullScreen, SDL_MapRGB(Surf_Display->format, 255, 255, 255)); //white color
	
	for (int i = 0;i < A2::EntityList.size();i++) { //draw the entities
		if(!A2::EntityList[i]) continue;
		
		A2::EntityList[i]->OnRender(Surf_Display);
	}

	SDL_Flip(Surf_Display);
}