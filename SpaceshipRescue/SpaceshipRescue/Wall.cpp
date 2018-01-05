#include "Wall.h"

Wall::Wall(sf::Vector2f pos) {
	m_pos = pos;

	loadImage();
}

void Wall::loadImage() {
	// randomly selects one of three textures for the wall to add slight variance in ship's look

	int randomNum = rand() % 20;

	if (randomNum == 0) {
		m_image.loadFromFile("assets/wall2.png");
	}
	else if (randomNum == 1) {
		m_image.loadFromFile("assets/wall3.png");
	}
	else {
		m_image.loadFromFile("assets/wall1.png");
	}

	m_texture.loadFromImage(m_image);
	m_sprite.setTexture(m_texture);
	m_sprite.setPosition(m_pos);

	m_width = m_texture.getSize().x;
	m_height = m_texture.getSize().y;
}