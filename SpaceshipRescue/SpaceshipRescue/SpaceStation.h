#pragma once

#include "Floor.h"
#include "Wall.h"

class SpaceStation {
public:
	SpaceStation();
	void render(sf::RenderWindow & window);
	//void resetLevel();
private:
	static const int layoutArray[53][78];
	std::vector<Wall*> m_walls;
	std::vector<Floor*> m_floors;
	int *layout;
};