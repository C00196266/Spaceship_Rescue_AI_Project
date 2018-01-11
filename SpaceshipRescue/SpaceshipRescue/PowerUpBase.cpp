#include "PowerUpBase.h"

void PowerUp::render(sf::RenderWindow &window) {
	window.draw(m_sprite);
}

std::string PowerUp::getID() {
	return id;
}

bool PowerUp::getAlive() {
	return m_alive;
}