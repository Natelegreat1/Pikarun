
#ifndef __A2_521__Entity__
#define __A2_521__Entity__

#include <iostream>
#include "Surface.h"
#include "Define.h"

//TYPES
/// 1 : Pikachu
/// 2 : Water
/// 3 : Ground
/// 4 : Pokeball
/// 5 : Wind

class Entity {
	public:
		int				TYPE;
		SDL_Surface *	Surf_Entity;
				
		double		X_Speed;
		double		X_Acceleration;
		double		Y_Speed;
		double		Y_Acceleration;
		double		MAX_X_SPEED;
		double		MAX_Y_SPEED;
		//		float       Col_X;
		//		float       Col_Y;
		//		float       Col_Width;
		//		float       Col_Height;
	
		int				X;
		int				Y;
		int				WIDTH;
		int				HEIGHT;
		bool			grounded;
		bool			deleted;
		double			heightMap [WWIDTH];
		Uint32			color;

	public:
		Entity();
		virtual ~Entity();
		virtual bool OnLoad(char* File, int Width, int Height, int MaxFrames);
		virtual void OnLoop();
		virtual void OnRender(SDL_Surface* Surf_Display);
		virtual void OnCleanup();
	
		double * getHeightMap();
	
		int getType();
	
		double get_X();
		double get_Y();
		void set_X(double newX);
		void set_Y(double newY);
	
		void set_Bottom(double newY);
	
		double getTop();
		double getBottom();
		double getLeft();
		double getRight();
	
		bool isGrounded();
		bool isMoving();
		virtual bool isColliding(Entity * e);
	
		void move();

		//Horizontal Movement
		void set_X_Acceleration(short new_X_Acceleration);
		void set_X_Speed(double new_X_Speed);
		double get_X_Speed();
		
		//Vertical Movement
		void jump();
		void set_Y_Acceleration(double new_Y_Acceleration);
		void set_Y_Speed(double new_Y_Speed);
		double get_Y_Speed();
};

#endif
