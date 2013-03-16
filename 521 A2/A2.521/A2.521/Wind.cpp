
#include "Wind.h"
#include <time.h> 

Wind::Wind() {
	TYPE = WIND;
	
	HEIGHT = 43;
	WIDTH = 200;
	t = 0;
	X_Speed = 0;
	
	if ( (Surf_WindL = Surface::OnLoad("/Users/nathanielblumer/Documents/McGill/U4/COMP 521/521 A2/A2.521/A2.521/windL.bmp") ) == NULL){
		std::cout << "L \n";
	}
	if ( (Surf_WindR = Surface::OnLoad("/Users/nathanielblumer/Documents/McGill/U4/COMP 521/521 A2/A2.521/A2.521/windR.bmp") ) == NULL){
		std::cout << "R \n";
	}
}

Wind::~Wind() {	}

void Wind::updateSpeed(){	
	srand ( time(NULL) );
	int direction = rand() % 10 + 1 ;
	
	if (direction > 5){ //wind east
		X_Speed += (X_Speed > 5 ? -0.20:0.20);

	}else{ //wind west
		X_Speed += (X_Speed > 5 ? 0.20:-0.20);
	}
}

void Wind::OnLoop() {
	t++;
	if (t%5 == 0){
		X_Speed = 0;
	}
	if (t%10 == 0){
		updateSpeed();
	}
}

void Wind::OnRender(SDL_Surface * Surf_Display) {
    if ((Surf_WindR == NULL && Surf_WindL == NULL) || Surf_Display == NULL) return;
	
	if (X_Speed < 0){
		Surface::OnDraw(Surf_Display, Surf_WindL, WWIDTH/2, 50);
	}else if (X_Speed > 0){
		Surface::OnDraw(Surf_Display, Surf_WindR, WWIDTH/2, 50);
	}	
}

void Wind::OnCleanup() {
    if (Surf_WindR)	SDL_FreeSurface(Surf_WindR);
	if (Surf_WindL)	SDL_FreeSurface(Surf_WindL);

	Surf_WindR = NULL;
    Surf_WindL = NULL;
}

void Wind::OnAnimate(){
	
}