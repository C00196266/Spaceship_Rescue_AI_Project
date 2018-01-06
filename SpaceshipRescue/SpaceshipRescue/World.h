#pragma once

#include "Player.h"
#include "SpaceStation.h"
#include "AStar.h"

class World {
public:
	World();

	void render(sf::RenderWindow &window);
	void init();

	void update(float deltaTime);

private:
	Player player;
	SpaceStation m_spaceStation;
	AStar* aStar;
};