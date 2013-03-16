
#include "Player.h"

Player::Player()
{
	TYPE = PLAYER;
	Surf_Pika = NULL;
	Surf_PikaR = NULL;
	Surf_PikaL = NULL;
	
	screenChanged = false;	

	X = 0;
	Y = 1;
	HEIGHT = 64;
	WIDTH = 64;
	
    CurrentFrame = 0;
    MaxFrames = 0;
    FrameInc = 1;
    FrameRate = 75; //Milliseconds
    OldTime = 0;
    Oscillate = false;
	
	MAX_X_SPEED = 12;
	MAX_Y_SPEED = 5;
	
	X_Speed = 0;
	Y_Speed = 1;
	X_Acceleration = 0;
	Y_Acceleration = GRAVITY; //'gravity'   note: small increse has big effect
	
	if((Surf_PikaL = Surface::OnLoad("/Users/nathanielblumer/Documents/McGill/U4/COMP 521/521 A2/A2.521/A2.521/PikachuRunsL.bmp")) == NULL) return; //change to 'left facing' Player
	if((Surf_PikaR = Surface::OnLoad("/Users/nathanielblumer/Documents/McGill/U4/COMP 521/521 A2/A2.521/A2.521/PikachuRunsR.bmp")) == NULL) return; //change to 'right facing' Player
	Surf_Pika = Surf_PikaR;
	
	jumpPressed		= false;
	rightPressed	= false;
	leftPressed		= false;
	grounded		= false;
}

Player::~Player(){}

void Player::reset()
{
	X_Acceleration = 0;

	X = 0;
	Y = 1;
	
	X_Speed = 0;
	Y_Speed = 1;

	grounded = false;
		
	Surf_Pika = Surf_PikaR;
}

void Player::animate(){
	MaxFrames = 4;
	Oscillate = true;
}

void Player::OnLoop()
{
	if (X_Speed != 0){
		Player::OnAnimate();  //This causes pikachu to be animated
	}

	move();
//	std::cout << "Pika X: " << this->getLeft() << "  Pika Y: " << this->getBottom() <<  "\n";
}

void Player::OnRender(SDL_Surface * Surf_Display)
{
    if( (Surf_PikaR == NULL && Surf_PikaL == NULL) || Surf_Display == NULL) return;
		
	if (leftPressed){
		Surf_Pika = Surf_PikaL;
	}else if (rightPressed){
		Surf_Pika = Surf_PikaR;
	}
	
	Surface::OnDraw(Surf_Display, Surf_Pika, X, Y, 0, CurrentFrame * HEIGHT, HEIGHT, WIDTH);
}

void Player::OnCleanup()
{
	if(Surf_PikaR)	SDL_FreeSurface(Surf_PikaR);
	if(Surf_PikaL)	SDL_FreeSurface(Surf_PikaL);

	Surf_PikaR	=	NULL;
	Surf_PikaL	=	NULL;
	Surf_Pika	=	NULL;
}

void Player::OnAnimate()
{		
    if(OldTime + FrameRate > SDL_GetTicks()) return;
	
    OldTime = SDL_GetTicks();
    CurrentFrame += FrameInc;
	
    if(Oscillate) {
        if(FrameInc > 0) {
            if(CurrentFrame >= MaxFrames) {
                FrameInc = -FrameInc;
            }
        }else{
            if(CurrentFrame <= 0) {
                FrameInc = -FrameInc;
            }
        }
    }else{
        if(CurrentFrame >= MaxFrames) {
            CurrentFrame = 0;
        }
    }
}

void Player::SetFrameRate(int Rate) {
    FrameRate = Rate;
}

void Player::SetCurrentFrame(int Frame) {
    if(Frame < 0 || Frame >= MaxFrames) return;
	
    CurrentFrame = Frame;
}

int Player::GetCurrentFrame() {
    return CurrentFrame;
}

void Player::move()
{ 
	//MODIFY X SPEED
	if (X_Acceleration == 1){ //if accelerting forward
		if (labs(X_Speed) < MAX_X_SPEED){  // speed is checked here
			X_Speed += (X_Speed > 0 ? 1.5:-1.5); //increase the speed depending on direction
		}
		
	}else if (X_Acceleration == -1){ //if slowing down
		if (X_Speed != 0){
			X_Speed += (X_Speed > 0 ? -0.5:0.5); //slow the speed depending on direction
		}else{
			X_Acceleration = 0; //no more acceleration
		}
	}
	
	//MODIFY Y POSITION
	if (Y < WHEIGHT){
		Y += 0.75 * Y_Speed;
	}
	
	//MODIFY Y SPEED
	Y_Speed += Y_Acceleration;
	
	//MODIFY X POSITION
	X += 0.5 * X_Speed;
	
	if (X > WWIDTH-WIDTH) { //when the right edge of the screen is reached, teleport back to left
		X = 1;
		screenChanged = true;
	}else if (X <= 0){ //can't go back!
		X = 1;
		X_Speed = 0;
	}
}

void Player::jump()
{
	if (grounded){ //eliminate double jumping:touching ground
		grounded = false;
		Y_Speed = JUMP_SPEED;
	}
}

bool Player::isColliding(Entity * e)
{
	if ( e->TYPE == PLAYER || e->TYPE == WIND ) return false; //can't intersect another pikachu (only one!) or the wind object
	
	if ( e->TYPE == GROUND || e->TYPE == WATER ){
		return surfaceIntersection(e);

	}else if ( e->TYPE == POKEBALL ){
		return projectileIntersection(e);
	}
	
	return false;
}

bool Player::projectileIntersection(Entity * e)
{
	//d > r1 + r2
	double intersection = 0;
	
	if (X < e->getRight()	&&	X+WIDTH > e->getLeft() &&
		Y < e->getBottom()	&&	Y+WIDTH > e->getTop()){
			intersection = -1;
	}
	
	if (intersection == -1){
		if ( e->TYPE == POKEBALL ){
			return true;
		}
	}
	
	return false;
}

bool Player::surfaceIntersection(Entity * e)
{
	double * hm = e->getHeightMap(); //the height map of current object
	double bottom_of_pikachu = this->getBottom();
	double top_of_terrain = WHEIGHT;
	
	for(int i = X; i < getRight(); i++){
		if (hm[i] < top_of_terrain){
			top_of_terrain = hm[i];
		}
	}
 
	double intersection = top_of_terrain - bottom_of_pikachu; //should be +
	
	if ( e->TYPE == WATER ){
		if (intersection < 0) return true;
	}

	if (e->TYPE == GROUND){
		
		if (intersection <= 0){
			Y_Acceleration = 0;
			grounded = true;
			Y = top_of_terrain - HEIGHT;
			
		}else{
			Y_Acceleration = GRAVITY;
			grounded = false;
		}
	}
	
	return false;
}