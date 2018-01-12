#pragma once

#include "stdafx.h"
#include "AStar.h"
#include "Wall.h"

class Worker {
public:
	Worker();
	Worker(sf::Vector2f pos, NodeLayout &nodes, std::vector<Wall*> &walls);

	void update(float deltaTime);
	void render(sf::RenderWindow &window);
	void seek(float deltaTime, sf::Vector2f v);
	void checkCollisions(Wall* wall, float deltaTime);
	void setupPath();
	void pickRandomDest(int randomIndex, int startIndex);

	void normalise(sf::Vector2f &v);
	float calculateMagnitude(sf::Vector2f v);
	float calculateMagnitude(sf::Vector2f v1, sf::Vector2f v2);

	void setRescued(bool rescued);
	bool getRescued();

	void setAbducted(bool abducted);
	bool getAbducted();

	sf::Sprite getSprite();

	sf::Vector2f getPos();
	sf::Vector2f getCenter();

private:
	sf::Vector2f m_pos;
	sf::Vector2f m_nextPosX;
	sf::Vector2f m_nextPosY;

	float m_width;
	float m_height;

	sf::Image m_image;
	sf::Texture m_texture;
	sf::Sprite m_sprite;

	float m_maxSpeed;
	float m_targetSpeed;
	float m_maxAccel;

	sf::Vector2f m_vel;
	sf::Vector2f m_accel;

	float m_orientation;

	std::vector<Wall*>& m_walls;

	NodeLayout& m_nodeLayout;
	std::vector<Node*> m_path;
	float m_distToNextNode;

	AStar* m_astar;

	bool m_abducted;
	bool m_rescued;
};