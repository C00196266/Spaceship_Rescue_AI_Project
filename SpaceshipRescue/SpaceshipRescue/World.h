#pragma once

#include "Wall.h"
#include "Floor.h"

class World {
public:
	World();

	void render(sf::RenderWindow &window);

	void update(float deltaTime);
private:
	std::vector<Wall*> m_walls;
	std::vector<Floor*> m_floors;
};