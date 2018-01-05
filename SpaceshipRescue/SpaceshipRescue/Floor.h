#pragma once

#include "Tile.h"

class Floor : public Tile {
public:
	Floor() {}
	Floor(sf::Vector2f pos, int type);

	void loadImage(int type);
};