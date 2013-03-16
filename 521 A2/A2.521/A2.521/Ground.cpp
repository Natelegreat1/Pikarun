#include "Ground.h"
#include <vector>

Ground::Ground() {
	TYPE = GROUND;
	
	points.clear();
	int pointCount = 10;
	
	Vector2d * temp;
	for (int i = 0; i <= pointCount; i++) {
		temp = new Vector2d;
		temp->x = i * (WWIDTH / pointCount);
		temp->y = BASE_GROUND;
		points.push_back(temp);
	}
	
	temp = new Vector2d; //furthest point to the right
	temp->x = WWIDTH;
	temp->y = BASE_GROUND;
	points.push_back(temp);
		
	for (int i=0; i < WWIDTH; i++){
		heightMap[i] = 100;
	}
}

Ground::~Ground() {	}

void Ground::OnLoop(Entity * wind) { }

void Ground::OnRender(SDL_Surface * Surf_Display) {
    if(Surf_Display == NULL) return;
	
	Uint32 color = SDL_MapRGB(Surf_Display->format, 0x00, 0x64, 0x00); // set grass color
	
	for (int i = 0; i < WWIDTH; i++){
		SDL_Rect currentBlade;
		currentBlade.x = i;
		currentBlade.y = heightMap[i];
		currentBlade.w = 1;
		currentBlade.h = WHEIGHT - heightMap[i] +1;
		SDL_FillRect(Surf_Display, &currentBlade, color); // draw grass blade
	}
}

void Ground::OnCleanup()
{
    if(Surf_Entity) SDL_FreeSurface(Surf_Entity);
    
    Surf_Entity = NULL;
}

void Ground::perlinize(double amplitude, int octaves)
{
	for (int i = 0; i < octaves; i++) {
		perlinizePoints( amplitude / pow(2, i) );
	}
	
	// Save terrain
	Vector2d * previous = points[0]; //previous point
	Vector2d * current; //current point
	
	for (int point = 1; point < points.size(); point++) {
		current = points[point];
		if (!current) continue;
		
		double slope = (current->y - previous->y)/(current->x - previous->x);
		
		for (int j = previous->x; j < current->x; j++){
			double k = previous->y + slope * (j - previous->x);
			
			heightMap[j] = k; //set whatever is highest to be the heightMap's y
		}
		
		previous = current;
	}
}

void Ground::perlinizePoints(double amplitude)
{
	for (int i = 0; i < points.size(); i++) {
		double newPos = (rand() % (int)amplitude) + (points[i]->y - amplitude);
		points[i]->y = newPos;
	}
}

double Ground::getLowestPoint()
{
	double lowest = WHEIGHT;
	
	for (int i=0; i < WWIDTH; i++){
		if (heightMap[i] < lowest){
			lowest = heightMap[i];
		}
	}
	return lowest;
}
