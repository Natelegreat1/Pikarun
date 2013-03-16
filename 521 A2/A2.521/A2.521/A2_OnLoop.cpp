#include "A2_OnLoop.h"
#include "A2.h"

void A2::OnLoop() {
		
	double windSpeed = 0;
	for (int i = 0; i < A2::EntityList.size(); i++) {
		Entity * current = A2::EntityList[i];
		if (!current) continue;
		
		if (current->deleted){
			A2::EntityList.erase(A2::EntityList.begin() + i);
			continue;
		}
		
		if (current->TYPE == GROUND || current->TYPE == WATER) continue;
		
		if (current->TYPE == WIND){
			( (Wind *) current )->OnLoop();
			windSpeed = current->get_X_Speed();
			
			continue;
		}
		if (current->TYPE == POKEBALL){
			double old = ( (Pokeball *)current )->get_X_Speed();
			( (Pokeball *)current )->set_X_Speed(old + windSpeed);
			( (Pokeball *)current )->OnLoop();
		}
		if (current->TYPE == PLAYER){
			double old = ( (Player *)current )->get_X_Speed();
			( (Player *)current )->set_X_Speed(old + windSpeed);
			( (Player *)current )->OnLoop();
			
			if ( ((Player *)current)->screenChanged ){
				level->screenCleared();
			
				if ( level->didWin() ){
					std::cout << "VICTORY! YOU WIN!!!";

					//DISPLAY VICTORY SCREEN
					if ( (Surf_Status = Surface::OnLoad("/Users/nathanielblumer/Documents/McGill/U4/COMP 521/521 A2/A2.521/A2.521/VICTORY.bmp")) == NULL) return;
					if ( Surf_Status == NULL || Surf_Display == NULL) return;
					Surface::OnDraw(Surf_Display, Surf_Status, 0, 0, 0, 0, 1020, 480);
					SDL_Flip(Surf_Display);
					start = false;
				}
				
				A2::EntityList.clear();
				A2::EntityList = level->loadLevel(level->getLevel());
				A2::EntityList.push_back(current);
				
				((Player *)current)->screenChanged = false;
			}
		}
		
		for (int j=0; j < A2::EntityList.size(); j++) {
			if (i != j){
				Entity * collidee = A2::EntityList[j];
				if ( (!collidee) || (collidee->TYPE == WIND) || (collidee->TYPE == PLAYER) ) continue;
				
				if ( collisionDetection(i, j) ) {
					break;
				}
			}
		}
	}
}

bool A2::collisionDetection(int i, int j){
	Entity * current = A2::EntityList[i];
	Entity * collidee = A2::EntityList[j];

	if (current->isColliding(collidee)){ //interesection is found
		
		if (current->TYPE == PLAYER){
			if (collidee->TYPE == WATER){
				std::cout << "Pikachu hit water \n";
			}else if (collidee->TYPE == POKEBALL){
				std::cout << "Pikachu hit a pokeball \n";
			}
			gameOver();
			
		}else if (current->TYPE == POKEBALL){
			if (collidee->TYPE == WATER){
				std::cout << "Pokeball hit water \n";
				current->deleted = true;
			}else if (collidee->TYPE == POKEBALL){
				std::cout << "Pokeball hit another pokeball! \n";
				current->deleted = true;
				collidee->deleted = true;
			}
		}
		return true;
	}
	return false;
}

void A2::gameOver(){
	std::cout << "GAME OVER \n\n";
	if ((Surf_Status = Surface::OnLoad("/Users/nathanielblumer/Documents/McGill/U4/COMP 521/521 A2/A2.521/A2.521/GAME_OVER.bmp")) == NULL) return;
	if (Surf_Status == NULL || Surf_Display == NULL) return;
    Surface::OnDraw(Surf_Display, Surf_Status, 0, 0, 0, 0, 1020, 480);
	SDL_Flip(Surf_Display);
	
	start = false;
}