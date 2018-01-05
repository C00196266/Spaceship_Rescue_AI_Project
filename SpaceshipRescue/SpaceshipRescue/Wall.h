#pragma once

#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

#include "Tile.h"

class Wall : public Tile {
public:
	Wall() {}
	Wall(sf::Vector2f pos);

	void loadImage();
};