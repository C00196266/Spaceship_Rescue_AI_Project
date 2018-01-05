#pragma once

#include "SpaceStation.h"

class World {
public:
	World();

	void render(sf::RenderWindow &window);

	void update(float deltaTime);
private:
	SpaceStation m_spaceStation;
};