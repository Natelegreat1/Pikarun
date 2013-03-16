#include "A2_OnEvent.h"
#include "A2.h"
#include "Level.h"

void A2::OnEvent(SDL_Event * e)
{
	Event::OnEvent(e);
}

void A2::OnKeyDown(SDLKey sym, SDLMod mod, Uint16 unicode)
{
    switch(sym) {
        case SDLK_SPACE:
			if (!Pikachu->jumpPressed){ 
				Pikachu->jump();
				Pikachu->jumpPressed = true;
			}
			break;

		case SDLK_LEFT:
			if (!Pikachu->leftPressed){
				Pikachu->leftPressed = true;
				Pikachu->set_X_Speed(-1);
				Pikachu->set_X_Acceleration(1);
			}
			break;
		
		case SDLK_RIGHT:
			if (!Pikachu->rightPressed){
				Pikachu->rightPressed = true;
				Pikachu->set_X_Speed(1);
				Pikachu->set_X_Acceleration(1);
			}
			break;
			
		case SDLK_1:
			startLevel(1);
			break;
		
		case SDLK_2:
			startLevel(2);
			break;
		
		case SDLK_3:			
			startLevel(3);
			break;
			
		case SDLK_4:
			startLevel(4);
			break;
			
		case SDLK_5:
			startLevel(5);
			break;
	
		case SDLK_r:
			SDL_Rect screenRect;
			screenRect.x = screenRect.y = 0;
			screenRect.w = Surf_Display->w;
			screenRect.h = Surf_Display->h;
			SDL_FillRect(Surf_Display, &screenRect, SDL_MapRGB(Surf_Display->format, 255, 255, 255)); //white color
			
			start = false;
			startLevel(level->getLevel());
			break;
			
		case SDLK_ESCAPE:
			OnExit();
			break;
			
        default: {	}
	}
}

void A2::OnKeyUp(SDLKey sym, SDLMod mod, Uint16 unicode)
{
    switch(sym) {
        case SDLK_SPACE:
			
			Pikachu->jumpPressed = false;
			break;
			
		case SDLK_LEFT:
			
			Pikachu->set_X_Acceleration(-1);
			Pikachu->move();
			Pikachu->leftPressed = false;
			break;
			
		case SDLK_RIGHT:
			
			Pikachu->set_X_Acceleration(-1);
			Pikachu->move();
			Pikachu->rightPressed = false;
			break;
			
		default: {	}
	}
}

void A2::startLevel(int lev){
	if (!start){
		start = true;
		reset();
		
		A2::EntityList = level->loadLevel(lev);
		A2::EntityList.push_back(Pikachu);
	}
}

void A2::reset(){
	A2::EntityList.clear();
	Pikachu->reset();
}