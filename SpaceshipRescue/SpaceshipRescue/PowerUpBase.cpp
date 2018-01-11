#include "PowerUpBase.h"

void PowerUp::render(sf::RenderWindow &window) {
	window.draw(m_sprite);
}

void PowerUp::checkCollision(Player &player) {
	if (player.getPosition().x < m_pos.x + m_width
		&& player.getPosition().x + player.getRect().width > m_pos.x
		&& player.getPosition().y <  m_pos.y + m_height
		&& player.getPosition().y + player.getRect().height > m_pos.y)
	{
		m_alive = false;
	}
}

std::string PowerUp::getID() {
	return id;
}

bool PowerUp::getAlive() {
	return m_alive;
}