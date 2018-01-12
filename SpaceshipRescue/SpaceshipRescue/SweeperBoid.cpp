#include "SweeperBoid.h"

SweeperBoid::SweeperBoid(NodeLayout &nodes, Player* player, std::vector<Wall*> &walls, std::vector<Worker*> &workers, int pathNo) : m_nodeLayout(nodes), m_player(player), m_walls(walls), m_workers(workers) {
	m_maxSpeed = 3;

	m_astar = new AStar(nodes);

	m_maxAccel = 30;

	m_fleeing = false;

	setupPatrol(pathNo);

	// sets initial position to be the start of the patrol path
	m_pos = sf::Vector2f(m_patrolPath.at(0)->getPos().x - 16, m_patrolPath.at(0)->getPos().y - 16);

	m_nextPosX = m_pos;
	m_nextPosY = m_pos;

	m_image.loadFromFile("assets/SweeperBoid.png");
	m_texture.loadFromImage(m_image);
	m_sprite.setTexture(m_texture);
	m_sprite.setPosition(m_pos);
	m_sprite.setOrigin(sf::Vector2f(m_texture.getSize().x / 2, m_texture.getSize().y / 2));

	m_width = m_texture.getSize().x;
	m_height = m_texture.getSize().y;

	m_currentPatrolNode = 0;
}

void SweeperBoid::render(sf::RenderWindow &window) {
	window.draw(m_sprite);
}

void SweeperBoid::update(float deltaTime)
{
	//patrol path
	//setupPath();

	// chooses whether to seek towards worker or next node
	//chooseTarget(deltaTime);
	patrol(deltaTime);

	// checks if the velocity is greater than its max velocity
	if (calculateMagnitude(m_vel) > m_maxSpeed) {
		normalise(m_vel);
		m_vel *= m_maxSpeed;
	}

	m_nextPosX.x += m_vel.x;
	m_nextPosY.y += m_vel.y;

	// check collisions with wall
	for (std::vector<Wall*>::iterator i = m_walls.begin(); i != m_walls.end(); i++) {
		checkWallCollisions((*i), deltaTime);
	}

	m_pos.x = m_nextPosX.x;
	m_pos.y = m_nextPosY.y;

	m_nextPosX.y = m_pos.y;
	m_nextPosY.x = m_pos.x;

	m_sprite.setPosition(m_pos.x + m_texture.getSize().x / 2, m_pos.y + m_texture.getSize().y / 2);

	m_orientation = (atan2(m_vel.x, -m_vel.y) * 180 / 3.14159265);
	m_sprite.setRotation(m_orientation);
}

void SweeperBoid::chooseTarget(float deltaTime) {
	// directional vector to player
	//sf::Vector2f vecToPlayer = (m_player)->getPosition() - m_pos;
	//m_distToPlayer = calculateMagnitude(vecToPlayer);
	//
	//// if there are nodes to seek to
	//if (!m_path.empty()) {
	//	// directional vector to next node
	//	sf::Vector2f vecToNextPoint = m_path.at(0)->getPos() - m_pos;
	//
	//	// distance to next node
	//	m_distToNextPoint = calculateMagnitude(vecToNextPoint);
	//
	//	// if the next node is closer than the player
	//	if (m_distToNextPoint < m_distToPlayer) {
	//		seek(deltaTime, vecToNextPoint, m_distToNextPoint, false);
	//
	//		if (m_distToNextPoint < 80) {
	//			m_path.erase(m_path.begin());
	//		}
	//	}
	//	// if the player is closer than the next node
	//	else {
	//		seek(deltaTime, vecToPlayer, m_distToPlayer, true);
	//	}
	//}
	//// if there aren't nodes to seek to
	//else {
	//	seek(deltaTime, vecToPlayer, m_distToPlayer, true);
	//}
}

void SweeperBoid::seek(float deltaTime, sf::Vector2f v, float dist, bool seekingWorker) {
	float targetSpeed;

	if (seekingWorker == false) {
		if (dist < 70) {
			targetSpeed = 0;
		}
		else if (dist > 200) {
			targetSpeed = m_maxSpeed;
		}
		else {
			targetSpeed = m_maxSpeed * (dist / 200);
		}
	}

	normalise(v);
	v *= targetSpeed;

	float timeToTarget = 4;

	m_accel = v - (m_vel / timeToTarget);

	if (calculateMagnitude(m_accel) > m_maxAccel) {
		normalise(m_accel);
	}

	m_vel += m_accel * deltaTime;
}

void SweeperBoid::setupPatrol(int pathNo) {
	// sets up nodes on patrol path
	if (pathNo == 1) {
		m_patrolPath.push_back(m_nodeLayout.getNodes()[0]);
		m_patrolPath.push_back(m_nodeLayout.getNodes()[1]);
		m_patrolPath.push_back(m_nodeLayout.getNodes()[9]);
		m_patrolPath.push_back(m_nodeLayout.getNodes()[21]);
		m_patrolPath.push_back(m_nodeLayout.getNodes()[20]);
		m_patrolPath.push_back(m_nodeLayout.getNodes()[19]);
		m_patrolPath.push_back(m_nodeLayout.getNodes()[4]);

		// faces next node in path
		m_orientation = 90;
	}
	else if (pathNo == 2) {
		m_patrolPath.push_back(m_nodeLayout.getNodes()[10]);
		m_patrolPath.push_back(m_nodeLayout.getNodes()[6]);
		m_patrolPath.push_back(m_nodeLayout.getNodes()[7]);
		m_patrolPath.push_back(m_nodeLayout.getNodes()[2]);
		m_patrolPath.push_back(m_nodeLayout.getNodes()[1]);
		m_patrolPath.push_back(m_nodeLayout.getNodes()[9]);

		// faces next node in path
		m_orientation = 0;
	}
	else if (pathNo == 3) {
		m_patrolPath.push_back(m_nodeLayout.getNodes()[16]);
		m_patrolPath.push_back(m_nodeLayout.getNodes()[15]);
		m_patrolPath.push_back(m_nodeLayout.getNodes()[10]);
		m_patrolPath.push_back(m_nodeLayout.getNodes()[9]);
		m_patrolPath.push_back(m_nodeLayout.getNodes()[21]);
		m_patrolPath.push_back(m_nodeLayout.getNodes()[22]);

		// faces next node in path
		m_orientation = 270;
	}
	else if (pathNo == 4) {
		m_patrolPath.push_back(m_nodeLayout.getNodes()[13]);
		m_patrolPath.push_back(m_nodeLayout.getNodes()[17]);
		m_patrolPath.push_back(m_nodeLayout.getNodes()[16]);
		m_patrolPath.push_back(m_nodeLayout.getNodes()[22]);
		m_patrolPath.push_back(m_nodeLayout.getNodes()[23]);
		m_patrolPath.push_back(m_nodeLayout.getNodes()[18]);
		m_patrolPath.push_back(m_nodeLayout.getNodes()[14]);

		// faces next node in path
		m_orientation = 180;
	}
	else {
		m_patrolPath.push_back(m_nodeLayout.getNodes()[7]);
		m_patrolPath.push_back(m_nodeLayout.getNodes()[8]);
		m_patrolPath.push_back(m_nodeLayout.getNodes()[13]);
		m_patrolPath.push_back(m_nodeLayout.getNodes()[14]);
		m_patrolPath.push_back(m_nodeLayout.getNodes()[5]);
		m_patrolPath.push_back(m_nodeLayout.getNodes()[3]);
		m_patrolPath.push_back(m_nodeLayout.getNodes()[2]);

		// faces next node in path
		m_orientation = 90;
	}
}

void SweeperBoid::patrol(float deltaTime) {
	float targetSpeed = 0;
	sf::Vector2f v = m_patrolPath.at(m_currentPatrolNode)->getPos() - m_pos;
	m_distToNode = calculateMagnitude(v);

	if (m_distToNode < 65) {
		// change to seek to next node upon reaching current node
		if (m_currentPatrolNode < m_patrolPath.size() - 1) {
			m_currentPatrolNode++;
		}
		else {
			m_currentPatrolNode = 0;
		}

		v = m_patrolPath.at(m_currentPatrolNode)->getPos() - m_pos;
	}
	else if (m_distToNode > 200) {
		targetSpeed = m_maxSpeed;
	}
	else {
		targetSpeed = m_maxSpeed * (m_distToNode / 200);
	}

	normalise(v);
	v *= targetSpeed;

	float timeToTarget = 4;

	m_accel = v - (m_vel / timeToTarget);

	if (calculateMagnitude(m_accel) > m_maxAccel) {
		normalise(m_accel);
	}

	m_vel += m_accel * deltaTime;
}

void SweeperBoid::checkWallCollisions(Wall* wall, float deltaTime) {
	// checks for intersection along x between the predator and the wall
	if (m_nextPosX.x < wall->getRight()
		&& m_nextPosX.x + m_width > wall->getPos().x
		&& m_nextPosX.y < wall->getBottom()
		&& m_nextPosX.y + m_height > wall->getPos().y)
	{
		// left of predator collides with the right of the wall
		if (m_nextPosX.x < wall->getRight() && m_nextPosX.x > wall->getPos().x) {
			m_vel.x = 0;
			m_nextPosX.x = wall->getPos().x + wall->getWidth();
		}
		// right of predator collides with the left of the wall
		else if (m_nextPosX.x + m_width > wall->getPos().x && m_nextPosX.x + m_width < wall->getRight()) {
			m_vel.x = 0;
			m_nextPosX.x = wall->getPos().x - m_width;
		}
	}

	// checks for intersection along y between the predator and the wall
	if (m_nextPosY.x < wall->getRight()
		&& m_nextPosY.x + m_width > wall->getPos().x
		&& m_nextPosY.y < wall->getBottom()
		&& m_nextPosY.y + m_height > wall->getPos().y)
	{
		// bottom of predator collides with top of the wall
		if (m_nextPosY.y + m_height > wall->getPos().y && m_nextPosY.y + m_height < wall->getBottom()) {
			m_vel.y = 0;
			m_nextPosY.y = wall->getPos().y - m_height;
		}
		// top of predator collides with bottom of the wall
		else if (m_nextPosY.y < wall->getBottom() && m_nextPosY.y > wall->getPos().y) {
			m_vel.y = 0;
			m_nextPosY.y = wall->getPos().y + wall->getHeight();
		}
	}
}

void SweeperBoid::normalise(sf::Vector2f &v) {
	float magnitude = calculateMagnitude(v);

	if (magnitude > 0)
	{
		v.x = v.x / magnitude;
		v.y = v.y / magnitude;
	}
}

float SweeperBoid::calculateMagnitude(sf::Vector2f vec) {
	return sqrt((vec.x * vec.x) + (vec.y * vec.y));
}

float SweeperBoid::calculateMagnitude(sf::Vector2f vec1, sf::Vector2f vec2) {
	return sqrt(((vec2.x - vec1.x) * (vec2.x - vec1.x)) + ((vec2.y - vec1.y) * (vec2.y - vec1.y)));
}