#include "A2_OnInit.h"
#include "A2.h"
#include "Define.h"
#include "Level.h"

bool A2::OnInit() {
	
	if(SDL_Init(SDL_INIT_EVERYTHING) < 0)  return false;
    
	if((Surf_Display = SDL_SetVideoMode(WWIDTH, WHEIGHT, 32, SDL_HWSURFACE | SDL_DOUBLEBUF)) == NULL) return false;

	level = new Level;
	Pikachu = new Player;
	Pikachu->animate();

	SDL_EnableKeyRepeat(1, SDL_DEFAULT_REPEAT_INTERVAL / 3);
	SDL_WM_SetCaption("PikaPursuit!", NULL);
	
	//DISPLAY WELCOME SCREEN
	if( (Surf_Status = Surface::OnLoad("/Users/nathanielblumer/Documents/McGill/U4/COMP 521/521 A2/A2.521/A2.521/WELCOME.bmp")) == NULL) return false;
	if( Surf_Status == NULL || Surf_Display == NULL) return false;
    Surface::OnDraw(Surf_Display, Surf_Status, 0, 0, 0, 0, 1020, 480);
	SDL_Flip(Surf_Display);

    return true;
}