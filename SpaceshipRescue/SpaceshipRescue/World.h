#pragma once

#include "Player.h"
#include "SpaceStation.h"

class World {
public:
	World();

	void render(sf::RenderWindow &window);
	void init();

	void update(float deltaTime);

	Player player;
	SpaceStation m_spaceStation;
};