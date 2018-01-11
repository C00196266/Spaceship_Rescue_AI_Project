#pragma once

#include "PowerUpBase.h"

class ShieldPowerUp : public PowerUp {
public:
	ShieldPowerUp() {}
	ShieldPowerUp(sf::Vector2f pos);

	void checkCollision(Player* player);
};