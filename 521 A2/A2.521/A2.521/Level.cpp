#include "Level.h"
#include "Ground.h"
#include "Water.h"
#include "Wind.h"

Level::Level() {
	currentLevel = 0;
	screenCount = 0;
	amplitude = 1;
	octaves = 1;
}

Level::~Level() {	}

std::vector<Entity*> Level::loadLevel(int level){
	std::vector<Entity*> newEntities;

	switch(level) {
		case 1: {
			currentLevel = 1;
			
			Ground * tempGround = new Ground;
			newEntities.push_back(tempGround);

//			Water * tempWater = new Water;
//			double lowest = tempGround->getLowestPoint();
//			tempWater->setLevel(lowest);
//			newEntities.push_back(tempWater);
			
			break;
		}
			
		case 2: {
			currentLevel = 2;
			
			amplitude = 100;
			octaves = 2;
			
			Ground * tempGround = new Ground;
			tempGround->perlinize(amplitude, octaves);

			Water * tempWater = new Water;
			double lowest = tempGround->getLowestPoint();
			tempWater->setLevel(lowest - 20);
			newEntities.push_back(tempWater);
			newEntities.push_back(tempGround);
			
			break;
		}
			
		case 3:  {			
			currentLevel = 3;
			
			amplitude = 100;
			octaves = 2;
			
			Ground * tempGround = new Ground;
			tempGround->perlinize(amplitude, octaves);
			newEntities.push_back(tempGround);

			Wind * wind = new Wind;
			wind->OnAnimate();
			newEntities.push_back(wind);

			break;
		}
			
		case 4:  {
			currentLevel = 4;
			amplitude = 100;
			octaves = 2;
			
			Ground * tempGround;
			tempGround = new Ground;
			tempGround->perlinize(amplitude, octaves);
			newEntities.push_back(tempGround);
			
			Pokeball * p;
			for (int i=0; i < screenCount+1; i++){
				p = new Pokeball;
				newEntities.push_back(p);
			}

			break;
		}
			
		case 5:  {			
			currentLevel = 4;
			amplitude = 100;
			octaves = 2;
			
			Ground * tempGround;
			tempGround = new Ground;
			tempGround->perlinize(amplitude, octaves);
			
			Wind * wind = new Wind;
			wind->OnAnimate();
			newEntities.push_back(wind);

			Water * tempWater = new Water;
			double lowest = tempGround->getLowestPoint();
			tempWater->setLevel(lowest - 20);
			newEntities.push_back(tempWater);
			newEntities.push_back(tempGround);

			Pokeball * p;
			for (int i=0; i < screenCount+1; i++){
				p = new Pokeball;
				newEntities.push_back(p);
			}
			
			break;
		}
	}
	
	return newEntities;
}

void Level::levelUp(){
	currentLevel++;
}

void Level::screenCleared(){
	screenCount++;
}

int Level::getLevel(){
	return currentLevel;
}

int Level::getScreenCount(){
	return screenCount;
}

bool Level::didWin(){
	return (screenCount == SCREENS_NEEDED);
}

void Level::restart(){
	screenCount = 0;
}
