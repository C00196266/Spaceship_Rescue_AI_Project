#pragma once

#include "stdafx.h"
#include "AStar.h"
#include "Wall.h"

class PredatorShip {
public:
	PredatorShip();
	PredatorShip(sf::Vector2f pos, NodeLayout &nodes, sf::Vector2f &playerPos, std::vector<Wall*> &walls);

	void render(sf::RenderWindow &window);

	void update(float deltaTime);
	void chooseTarget(float deltaTime);
	void seek(float deltaTime, sf::Vector2f v, float dist, bool seekingPlayer);
	void checkCollisions(Wall* wall, float deltaTime);
	void setupPath();

	void normalise(sf::Vector2f &v);
	float calculateMagnitude(sf::Vector2f v);
	float calculateMagnitude(sf::Vector2f v1, sf::Vector2f v2);

private:
	sf::Vector2f m_pos;

	float m_width;
	float m_height;

	sf::Vector2f m_vel;
	sf::Vector2f m_linearAccel;
	float m_magnitudeAccel;
	float m_maxAccel;

	float m_distToNextPoint;
	float m_distToPlayer;

	float m_orientation;

	sf::Vector2f& m_playerPos;

	sf::Image m_image;
	sf::Texture m_texture;
	sf::Sprite m_sprite;

	float m_maxSpeed;

	std::vector<Wall*>& m_walls;
	std::vector<Wall*> m_closestWalls;

	NodeLayout& m_nodeLayout;
	std::vector<Node*> m_path;

	AStar* m_astar;
};