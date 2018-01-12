#pragma once

#include "stdafx.h"
#include "AStar.h"
#include "Wall.h"
#include "Player.h"
#include "Worker.h"

class SweeperBoid {
public:
	SweeperBoid();
	SweeperBoid(NodeLayout &nodes, Player* player, std::vector<Wall*> &walls, std::vector<Worker*> &workers, int pathNo);

	void render(sf::RenderWindow &window);

	void update(float deltaTime);
	void chooseTarget(float deltaTime);
	void seek(float deltaTime, sf::Vector2f v, float dist, bool seekingWorker);
	void checkWallCollisions(Wall* wall, float deltaTime);
	//void checkBulletCollision(Projectile* p);
	void setupPatrol(int pathNo);
	void patrol();

	void normalise(sf::Vector2f &v);
	float calculateMagnitude(sf::Vector2f v);
	float calculateMagnitude(sf::Vector2f v1, sf::Vector2f v2);

private:
	sf::Vector2f m_pos;
	sf::Vector2f m_nextPosX;
	sf::Vector2f m_nextPosY;

	float m_width;
	float m_height;

	sf::Vector2f m_vel;
	float m_maxSpeed;
	sf::Vector2f m_accel;
	float m_magnitudeAccel;
	float m_maxAccel;

	sf::Image m_image;
	sf::Texture m_texture;
	sf::Sprite m_sprite;

	float m_orientation;

	Player* m_player;

	bool m_fleeing;

	std::vector<Wall*>& m_walls;
	std::vector<Worker*>& m_workers;

	NodeLayout& m_nodeLayout;
	std::vector<Node*> m_patrolPath;

	AStar* m_astar;
};