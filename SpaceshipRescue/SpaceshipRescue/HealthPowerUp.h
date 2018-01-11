#pragma once

#include "PowerUpBase.h"

class HealthPowerUp : public PowerUp {
public:
	HealthPowerUp() {}
	HealthPowerUp(sf::Vector2f pos);

	void checkCollision(Player &player);
};