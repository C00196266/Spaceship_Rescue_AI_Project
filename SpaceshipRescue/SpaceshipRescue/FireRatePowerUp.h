#pragma once

#include "PowerUpBase.h"

class FireRatePowerUp : public PowerUp {
public:
	FireRatePowerUp() {}
	FireRatePowerUp(sf::Vector2f pos);

	void checkCollision(Player* player);
};