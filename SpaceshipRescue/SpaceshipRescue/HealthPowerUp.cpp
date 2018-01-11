#include "HealthPowerUp.h"

HealthPowerUp::HealthPowerUp(sf::Vector2f pos) {
	m_pos = pos;

	m_alive = true;
}

void HealthPowerUp::checkCollision(Player &player) {
	if (player.getPosition().x < m_pos.x + m_width
		&& player.getPosition().x + player.getRect().width > m_pos.x
		&& player.getPosition().y <  m_pos.y + m_height
		&& player.getPosition().y + player.getRect().height > m_pos.y)
	{
		// restores health... to be complete

		m_alive = false;
	}
}