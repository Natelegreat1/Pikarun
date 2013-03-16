
#ifndef __A2_521__Level__
#define __A2_521__Level__

#include <iostream>

#include "Pokeball.h"
#include "Entity.h"
#include <vector>

class Level {
	private:
		int currentLevel;
		int screenCount;
		int octaves;
		int amplitude;
	
	public:
		Level();
		virtual ~Level();
	
		std::vector<Entity*> loadLevel(int level);
		
		void levelUp();
		void screenCleared();
		int getLevel();
		int getScreenCount();
		bool didWin();
		void restart();
};

#endif
