#include "Floor.h"

Floor::Floor(sf::Vector2f pos, int type) {
	m_pos = pos;

	loadImage(type);
}

void Floor::loadImage(int type) {
	/********************************************//**
  *  ...  type determines the floor texture that is loaded
	 ***********************************************/

	if (type == 0) {
		m_image.loadFromFile("assets/ground1.png");
	}
	else {
		m_image.loadFromFile("assets/ground2.png");
	}

	m_texture.loadFromImage(m_image);
	m_sprite.setTexture(m_texture);
	m_sprite.setPosition(m_pos);

	m_width = m_texture.getSize().x;
	m_height = m_texture.getSize().y;
}