#include "HealthPowerUp.h"

HealthPowerUp::HealthPowerUp(sf::Vector2f pos) {
	m_pos = pos;

	m_image.loadFromFile("assets/HealthRestorationPowerUp.png");
	m_texture.loadFromImage(m_image);
	m_sprite.setTexture(m_texture);
	m_sprite.setPosition(m_pos);

	m_width = m_texture.getSize().x;
	m_height = m_texture.getSize().y;

	m_sprite.setOrigin(sf::Vector2f(m_width / 2, m_height / 2));

	m_alive = true;

	id = "health";
}

void HealthPowerUp::checkCollision(Player* player) {
	if (player->getPosition().x < m_pos.x + m_width
		&& player->getPosition().x + player->getRect().width > m_pos.x
		&& player->getPosition().y <  m_pos.y + m_height
		&& player->getPosition().y + player->getRect().height > m_pos.y)
	{
		// restores health... to be complete

		m_alive = false;
	}
}