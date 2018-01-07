#pragma once

#include "stdafx.h"
#include "AStar.h"

class PredatorShip {
public:
	PredatorShip();
	PredatorShip(sf::Vector2f pos, NodeLayout &nodes, sf::Vector2f &playerPos);

	void render(sf::RenderWindow &window);

	void update(float deltaTime);
	void seek(float deltaTime);
	void setupPath();

	void normalise(sf::Vector2f &v);
	float calculateMagnitude(sf::Vector2f v);
	float calculateMagnitude(sf::Vector2f v1, sf::Vector2f v2);

private:
	sf::Vector2f m_pos;

	sf::Vector2f m_vel;

	sf::Vector2f& m_playerPos;

	sf::Image m_image;
	sf::Texture m_texture;
	sf::Sprite m_sprite;

	float m_maxSpeed;

	NodeLayout& m_nodeLayout;
	std::vector<Node*> m_path;

	AStar* m_astar;
};