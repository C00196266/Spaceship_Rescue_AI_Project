#include "Tile.h"

Tile::Tile(sf::Vector2f pos) {
	m_pos = pos;

	loadImage();
}

void Tile::loadImage() {
	m_image.loadFromFile("assets/default.png");
	m_texture.loadFromImage(m_image);
	m_sprite.setTexture(m_texture);
	m_sprite.setPosition(m_pos);

	m_width = m_texture.getSize().x;
	m_height = m_texture.getSize().y;
}

void Tile::render(sf::RenderWindow &window) {
	window.draw(m_sprite);
}

//sf::Vector2f Tile::getPos() {
//	return m_pos;
//}