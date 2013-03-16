#include "Entity.h"

Entity::Entity()
{
    Surf_Entity = NULL;
	grounded = false;
	deleted = false;
}

Entity::~Entity() {	}

bool Entity::OnLoad(char * File, int Width, int Height, int MaxFrames)
{
    if((Surf_Entity = Surface::OnLoad(File)) == NULL)  return false;
	
    return true;
}

void Entity::OnLoop() {	}

void Entity::OnRender(SDL_Surface * Surf_Display)
{
    if(Surf_Entity == NULL || Surf_Display == NULL) return;
	
    Surface::OnDraw(Surf_Display, Surf_Entity, X, Y, 0, 0, WIDTH, HEIGHT);
}

void Entity::OnCleanup()
{
    if(Surf_Entity) {
        SDL_FreeSurface(Surf_Entity);
    }

    Surf_Entity = NULL;
}

double * Entity::getHeightMap()
{
	return heightMap;
}

double Entity::get_X()
{
	return X;
}

void Entity::set_X(double newX)
{
	X = newX;
}

void Entity::set_X_Acceleration(short direction)
{
	X_Acceleration = direction;
}

void Entity::set_X_Speed(double newSpeed)
{
	X_Speed = newSpeed;
}

double Entity::get_X_Speed()
{
	return X_Speed;
}

void Entity::set_Y_Acceleration(double direction)
{
	Y_Acceleration = direction;
}

void Entity::set_Y_Speed(double newSpeed)
{
	if (newSpeed == 0){
		grounded = true;
	}
	Y_Speed = newSpeed;
}

double Entity::get_Y()
{
	return Y;
}

void Entity::set_Y(double newY)
{
	Y = newY;
}

void Entity::set_Bottom(double newY)
{
	Y = newY - HEIGHT;
}

double Entity::get_Y_Speed()
{
	return Y_Speed;
}

double Entity::getTop()
{
	return Y;
}

double Entity::getBottom()
{
	return (Y + HEIGHT);
}

double Entity::getLeft()
{
	return X;
}

double Entity::getRight()
{
	return (X + WIDTH);
}

int Entity::getType()
{
	return TYPE;
}

bool Entity::isMoving()
{
	if (X_Speed == 0 && Y_Speed == 0){
		return true;
	}else{
		return false;
	}
}

bool Entity::isGrounded()
{
	return grounded;
}

bool Entity::isColliding(Entity * e)
{
	return false;
}