#include "PredatorShip.h"

PredatorShip::PredatorShip(sf::Vector2f pos, NodeLayout &nodes) : m_nodeLayout(nodes) {
	m_pos = pos;

	m_image.loadFromFile("assets/PredatorShip.png");
	m_texture.loadFromImage(m_image);
	m_sprite.setTexture(m_texture);
	m_sprite.setPosition(m_pos);
}

void PredatorShip::render(sf::RenderWindow &window) {
	window.draw(m_sprite);
}