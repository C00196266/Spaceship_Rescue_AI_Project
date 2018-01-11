#pragma once

#include "stdafx.h"
#include "Player.h"

class PowerUp {
public:
	PowerUp() {}

	void render(sf::RenderWindow &window);

	void checkCollision(Player &player) {}

	std::string getID();
	bool getAlive();

protected:
	std::string id;

	sf::Vector2f m_pos;
	float m_width;
	float m_height;

	sf::Image m_image;
	sf::Texture m_texture;
	sf::Sprite m_sprite;

	bool m_alive;
};