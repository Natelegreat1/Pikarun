#ifndef __A2_521__CApp__
#define __A2_521__CApp__

#include <SDL/SDL.h>
#include "Surface.h"
#include "Player.h"
#include "Event.h"
#include "Entity.h"
#include "Define.h"
#include "Ground.h"
#include "Water.h"
#include "Wind.h"
#include "Level.h"
#include <vector>

class A2 : public Event
{
	private:
		bool running;
		bool start;
		SDL_Surface * Surf_Display;
		SDL_Surface * Surf_Status;
		char * START;
		char * GAME_OVER;
	
		std::vector<Entity*> EntityList;
		Player * Pikachu;
		Wind * wind;
		Level * level;

	public:
		A2();

		int OnExecute();
		bool OnInit();
		void OnEvent(SDL_Event * e);
		void OnExit();
		void OnLoop();
		void OnRender();
		void OnCleanup();
	
		void OnKeyDown(SDLKey sym, SDLMod mod, Uint16 unicode);
		void OnKeyUp(SDLKey sym, SDLMod mod, Uint16 unicode);
	
		void reset();
		void startLevel(int lev);
		bool collisionDetection(int i, int j);
		void gameOver();
};

#endif