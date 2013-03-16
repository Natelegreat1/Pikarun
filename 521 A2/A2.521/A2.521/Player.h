
#ifndef __A2_521__Player__
#define __A2_521__Player__

#include <iostream>
#include <SDL/SDL.h>
#include "Entity.h"
#include "Wind.h"
#include "Surface.h"
#include "Define.h"

class Player : public Entity{
	public:
		SDL_Surface *	Surf_PikaR;
		SDL_Surface *	Surf_PikaL;
		SDL_Surface *	Surf_Pika;
		
		bool	screenChanged;
	
		int		CurrentFrame;
		int		FrameInc;
		int		FrameRate; //Milliseconds
		long	OldTime;
		int		MaxFrames;
		bool	Oscillate;

		bool jumpPressed = false;
		bool rightPressed = false;
		bool leftPressed = false;

	public:
		Player();
		virtual ~Player();

		void OnAnimate();
		void OnLoop();
		void OnRender(SDL_Surface* Surf_Display);
		void OnCleanup();
	
		void reset();
		void animate();

		void SetFrameRate(int Rate);
		void SetCurrentFrame(int Frame);
		int GetCurrentFrame();
		
		bool isColliding(Entity * e);
		bool surfaceIntersection(Entity * e);
		bool projectileIntersection(Entity * e);
		
	//Horizontal Movement
		void move();
	
		//Vertical Movement
		void jump();
};

#endif