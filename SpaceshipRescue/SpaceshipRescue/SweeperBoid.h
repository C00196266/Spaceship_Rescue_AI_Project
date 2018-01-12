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
	void chooseTarget();
	void seek(float deltaTime, sf::Vector2f v, float dist, bool seekingWorker);
	void checkWallCollisions(Wall* wall, float deltaTime);
	void chooseBehaviour();
	//void checkBulletCollision(Projectile* p);
	void setupPatrol(int pathNo);
	void patrol(float deltaTime);
	void abduct(float deltaTime);
	void returnToPatrol(float deltaTime);
	void flee(float deltaTime);

	void normalise(sf::Vector2f &v);
	float calculateMagnitude(sf::Vector2f v);
	float calculateMagnitude(sf::Vector2f v1, sf::Vector2f v2);

private:
	enum Behaviour { PATROL, FLEE, ABDUCT, RETURN };
	Behaviour m_behaviour;

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

	bool m_targetChosen;
	int m_targetIndex;

	bool m_fleeing;

	std::vector<Wall*>& m_walls;
	std::vector<Worker*>& m_workers;

	NodeLayout& m_nodeLayout;

	std::vector<Node*> m_patrolPath;
	int m_currentPatrolNode;
	float m_distToNode;

	std::vector<Node*> m_seekPath;
	std::vector<Node*> m_returnPath;
	std::vector<Node*> m_fleePath;

	AStar* m_astar;
};