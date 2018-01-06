#pragma once

#include "stdafx.h"
#include "AStar.h"

class PredatorShip {
public:
	PredatorShip();
	PredatorShip(sf::Vector2f pos, NodeLayout &nodes);

	void render(sf::RenderWindow &window);
	void update(float deltaTime);

private:
	sf::Vector2f m_pos;

	sf::Vector2f m_vel;

	sf::Image m_image;
	sf::Texture m_texture;
	sf::Sprite m_sprite;

	NodeLayout& m_nodeLayout;
};