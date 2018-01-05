#pragma once

#include "stdafx.h"

class World {
public:
	World();

	void render(sf::RenderWindow &window);

	void update(float deltaTime);
};