
#include "Pokeball.h"
#include <time.h>

Pokeball::Pokeball() {
	TYPE = POKEBALL;
	Surf_Pokeball = NULL;
	
	if((Surf_Pokeball = Surface::OnLoad("/Users/nathanielblumer/Documents/McGill/U4/COMP 521/521 A2/A2.521/A2.521/pball.bmp")) == NULL) return;
	
	MAX_X_SPEED = 10;
	MAX_Y_SPEED = 5;
	
	WIDTH = HEIGHT = 25;
	
	srand (time(NULL));

	X = rand() % WWIDTH/2 + WWIDTH/2; //64 is Pikachu's width
	Y = 1;
	
	srand (time(NULL));

	X_Speed = rand() % (int)MAX_X_SPEED - MAX_X_SPEED;
	Y_Speed = 0;
	
	checkDirection();

	X_Acceleration = STANDSTILL;
	Y_Acceleration = GRAVITY/2;
	bounceCount = 0;
}

Pokeball::~Pokeball() {	}

void Pokeball::checkDirection(){
	if (X_Speed > 0) direction = RIGHT;
	if (X_Speed < 0) direction = LEFT;
}

void Pokeball::OnLoop() {
	move();
	
//	std::cout << "Ball X: " << X << "  Ball Y: " << this->getBottom() <<  "\n";
	std::cout << " Vx: " << X_Speed << "  Vy: " << Y_Speed <<  "\n";
}

void Pokeball::OnRender(SDL_Surface * Surf_Display) {
    if( (Surf_Pokeball == NULL) || Surf_Display == NULL) return;
	
	Surface::OnDraw(Surf_Display, Surf_Pokeball, X, Y);
}

void Pokeball::OnCleanup() {
    if(Surf_Pokeball)	SDL_FreeSurface(Surf_Pokeball);
	
	Surf_Pokeball = NULL;
}

void Pokeball::OnAnimate(){		}

void Pokeball::move()
{	
	//MODIFY X SPEED
	int direction_before = direction;

	if (X_Acceleration == SPEEDING_UP){ //if accelerting forward
		X_Speed += (X_Speed > 0 ? 0.25:-0.25); //increase the speed depending on direction
		checkDirection();
		if (direction != direction_before){
			X_Acceleration = SLOWING_DOWN;
		}
	}else if (X_Acceleration == SLOWING_DOWN){ //if slowing down
		X_Speed += (X_Speed > 0 ? -0.25:0.25); //slow the speed depending on direction
		checkDirection();
		if (direction != direction_before){
			X_Acceleration = SPEEDING_UP;
		}
	}
	
	X += X_Speed;					//MODIFY X POSITION
	Y_Speed += Y_Acceleration;		//MODIFY Y SPEED
	Y += Y_Speed;					//MODIFY Y POSITION
	
	if (X > WWIDTH || X < 0 || Y > WHEIGHT){ //moves off-screen
		X_Acceleration = STANDSTILL;
		Y_Acceleration = STANDSTILL;
	}
}

bool Pokeball::isColliding(Entity * e)
{	
	if ( e->TYPE == GROUND || e->TYPE == WATER ){
		return surfaceIntersection(e);
		
	}else if ( e->TYPE == POKEBALL ){
		return projectileIntersection(e);
	}
	
	return false;
}

bool Pokeball::projectileIntersection(Entity * e)
{
	//d > r1 + r2
	double intersection = 0;
	
	if (X < e->getRight() &&
		X+HEIGHT/2 > e->getLeft() &&
		Y < e->getBottom() &&
		Y+HEIGHT/2 > e->getTop()){
		intersection = -1;
	}
	
	if (intersection == -1){
		if ( e->TYPE == POKEBALL ){	//two pokeballs collide, swap Velocities
			double temp = e->get_X_Speed();
			e->set_X_Speed(X_Speed);
			X_Speed = temp;
			return true;
		}
	}
	
	return false;
}

bool Pokeball::surfaceIntersection(Entity * e)
{
	double * hm = e->getHeightMap(); //the height map of current object
	double bottom_of_ball = this->getBottom();
	double top_of_terrain_left = hm[X];
	double top_of_terrain_right = hm[X+WIDTH];
	int direction = 0;
	
	double intersection_left = hm[X] - bottom_of_ball; //should be +
	double intersection_right = hm[X+WIDTH] - bottom_of_ball; //should be +

	
	if (e->TYPE == WATER){
		if (intersection_left <= 0 || intersection_right <=0) return true; //intersection occured
	}

	if (e->TYPE == GROUND){
		
		//CASES FOR TOUCHING A HILL - determine the direction to slide
		if (intersection_left <= 0 && !(intersection_right <= 0) ){ // touching only on left
			X_Speed = 1;
			direction = RIGHT;
		}else if (intersection_right <= 0 && !(intersection_left <= 0) ){ //touching only on right
			X_Speed = -1;
			direction = LEFT;
		}
		
		//WHEN TOUCHING ON EITHER SIDE
		if (intersection_left <= 0 || intersection_right <= 0){ 
			if (bounceCount < 3){
				Y_Speed *= -0.25; //inverse the bounce direction (coefficient of bounce)
				bounceCount++;
			}
			
			double target = Y;
			if (intersection_left <= 0){
				target = top_of_terrain_left - HEIGHT;
			}else if (intersection_right <= 0){
				target = top_of_terrain_right - HEIGHT;
			}
			
			if (target < Y){
				X_Acceleration = SLOWING_DOWN; //going uphill, slow down
			}else if (target > Y){
				X_Acceleration = SPEEDING_UP; //going uphill, speed up
			}
			Y = target;


		}else{
			Y_Acceleration = GRAVITY/2;
		}
	}

	return false;
}