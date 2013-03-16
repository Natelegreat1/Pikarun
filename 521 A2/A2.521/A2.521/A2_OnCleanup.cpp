
#include "A2_OnCleanup.h"
#include "A2.h"

void A2::OnCleanup() {
		
	for(int i = 0;i < A2::EntityList.size();i++) {
		if(!A2::EntityList[i]) continue;
		A2::EntityList[i]->OnCleanup();
	}
	A2::EntityList.clear();
	
    SDL_FreeSurface(Surf_Display);
	SDL_FreeSurface(Surf_Status);
	SDL_Quit();
}