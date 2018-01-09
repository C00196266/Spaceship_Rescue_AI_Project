#pragma once

#include "stdafx.h"
#include "AStar.h"

class PredatorShip {
public:
	PredatorShip();
	PredatorShip(sf::Vector2f pos, NodeLayout &nodes, sf::Vector2f &playerPos);

	void render(sf::RenderWindow &window);

	void update(float deltaTime);
	void chooseTarget(float deltaTime);
	void seek(float deltaTime, sf::Vector2f v);
	void setupPath();

	void normalise(sf::Vector2f &v);
	float calculateMagnitude(sf::Vector2f v);
	float calculateMagnitude(sf::Vector2f v1, sf::Vector2f v2);

	float getOrient(float orientation, sf::Vector2f velocity, sf::Vector2f target);
	void Seek(sf::Vector2f target);
	float Arrive(sf::Vector2f target);

private:
	sf::Vector2f m_pos;
	bool playerSeek = false;
	sf::Vector2f m_vel;
	sf::Vector2f m_linearAccel;
	float m_magnitudeAccel;
	float m_maxAccel;

	float m_distToNextPoint;
	float m_distToPlayer;

	float orient;

	sf::Vector2f& m_playerPos;

	sf::Image m_image;
	sf::Texture m_texture;
	sf::Sprite m_sprite;

	float m_maxSpeed;

	NodeLayout& m_nodeLayout;
	std::vector<Node*> m_path;

	AStar* m_astar;
};