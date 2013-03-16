#include <SDL/SDL.h>
#include "SDLMain.h"
#include <iostream>
#include "A2.h"

// this is the tutorial I followed to get SDL working on my mac: http://www.youtube.com/watch?v=F27BUDX_RSg
// the structuring of the files (with the intergration of SDL) was inspired by http://www.sdltutorials.com/

A2::A2(){
	Surf_Display = NULL;
	Surf_Status = NULL;
	
	running = true;
	start = false;
}

int main(int argc, char ** argv) {
	A2 app;
	return app.OnExecute();
}

int A2::OnExecute(){
	if(!OnInit()) {
        return -1;
	}
	
    SDL_Event Event;
	
    while(running) {
        while(SDL_PollEvent(&Event)) {
            OnEvent(&Event);
        }
		if (start){
			OnLoop();
		}
		if (start){
			OnRender();
		}
    }
	
    OnCleanup();
	
    return 0;
}

void A2::OnExit() {
    running = false;
}