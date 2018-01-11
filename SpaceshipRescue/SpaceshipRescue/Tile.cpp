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

sf::Sprite Tile::getSprite()
{
	return m_sprite;
}

sf::Vector2f Tile::getPos() {
	return m_pos;
}

sf::Vector2f Tile::getCenter() {
	return sf::Vector2f(m_pos.x + (m_width / 2), m_pos.y + (m_height / 2));
}

float Tile::getRight() {
	return m_pos.x + m_width;
}

float Tile::getWidth() {
	return m_width;
}

float Tile::getBottom() {
	return m_pos.y + m_height;
}

float Tile::getHeight() {
	return m_height;
}

sf::FloatRect Tile::getRect() {
	return m_sprite.getGlobalBounds();
}