#include "PredatorShip.h"

PredatorShip::PredatorShip(sf::Vector2f pos, NodeLayout &nodes, sf::Vector2f &playerPos) : m_nodeLayout(nodes), m_playerPos(playerPos) {
	m_pos = pos;
	m_maxSpeed = 4.0f;

	m_image.loadFromFile("assets/PredatorShip.png");
	m_texture.loadFromImage(m_image);
	m_sprite.setTexture(m_texture);
	m_sprite.setPosition(m_pos);
	m_sprite.setOrigin(sf::Vector2f(m_texture.getSize().x / 2, m_texture.getSize().y / 2));

	m_astar = new AStar(nodes);

	m_maxAccel = 30;
}

void PredatorShip::render(sf::RenderWindow &window) {
	window.draw(m_sprite);
}

void PredatorShip::update(float deltaTime) {
	setupPath();

	// seeks towards player
	chooseTarget(deltaTime);

	// checks if the velocity is greater than its max velocity
	float velCheck = calculateMagnitude(m_vel);

	if (velCheck > m_maxSpeed) {
		normalise(m_vel);
		m_vel *= m_maxSpeed;
	}

	m_pos += m_vel;
	m_sprite.setPosition(m_pos);

	m_orientation = (atan2(m_vel.x, -m_vel.y) * 180 / 3.14159265);
	m_sprite.setRotation(m_orientation);
}

void PredatorShip::chooseTarget(float deltaTime) {
	// directional vector to player
	sf::Vector2f vecToPlayer = m_playerPos - m_pos;
	m_distToPlayer = calculateMagnitude(vecToPlayer);

	// if there are nodes to seek to
	if (!m_path.empty()) {
		// directional vector to next node
		sf::Vector2f vecToNextPoint = m_path.at(0)->getPos() - m_pos;

		// distance to next node
		m_distToNextPoint = calculateMagnitude(vecToNextPoint);

		// if the next node is closer than the player
		if (m_distToNextPoint < m_distToPlayer) {
			seek(deltaTime, vecToNextPoint);

			if (m_distToNextPoint < 40) {
				m_path.erase(m_path.begin());
			}
		}
		// if the player is closer than the next node
		else {
			seek(deltaTime, vecToPlayer);
		}
	}
	// if there aren't nodes to seek to
	else {
		seek(deltaTime, vecToPlayer);
	}
}

void PredatorShip::seek(float deltaTime, sf::Vector2f v) {
	//m_linearAccel = (m_targetVel - m_vel) / m_timeToTarget;

	//m_magnitudeAccel = sqrt((m_linearAccel.x * m_linearAccel.x) + (m_linearAccel.y * m_linearAccel.y));
	//
	//if (m_magnitudeAccel > m_maxAccel) {
	//	normalise(m_linearAccel);
	//	m_linearAccel *= m_maxAccel;
	//}
	//
	//m_vel += m_linearAccel * deltaTime;
	//if (distToNextPoint < 80 && distToNextPoint > 40) {
	//	if (m_maxSpeed != 2.0f) {
	//		m_maxSpeed = 2.0f;
	//	}
	//}
	//else if (distToNextPoint < 40) {
	//	if (m_maxSpeed != 4.0f) {
	//		m_maxSpeed = 4.0f;
	//	}
	//	m_path.erase(m_path.begin());
	//}

	normalise(v);
	v *= m_maxSpeed;
	
	m_vel += v * deltaTime;
}

void PredatorShip::setupPath() {
	// checks which node is closest to the player and the predator
	int indexClosestToPlayer;
	int indexClosestToPredator;

	float closestDistPlayer = 99999;
	float closestDistPredator = 99999;

	for (int i = 0; i < m_nodeLayout.getNoOfNodes() - 1; i++) {
		float distPlayer = calculateMagnitude(m_nodeLayout.getNodes()[i]->getPos(), m_playerPos);

		if (distPlayer < closestDistPlayer) {
			closestDistPlayer = distPlayer;
			indexClosestToPlayer = i;
		}

		float distPredator = calculateMagnitude(m_nodeLayout.getNodes()[i]->getPos(), m_pos);

		if (distPredator < closestDistPredator) {
			closestDistPredator = distPredator;
			indexClosestToPredator = i;
		}
	}

	// if there is a path already set
	if (!m_path.empty()) {
		// if the node that is closest (the destination) to the player has changed
		if (m_nodeLayout.getNodes()[indexClosestToPlayer] != m_path.at(m_path.size() - 1)) {
			m_path.clear();
			m_astar->calculatePath(m_nodeLayout.getNodes()[indexClosestToPlayer], m_nodeLayout.getNodes()[indexClosestToPredator], m_path);
		}
	}
	else {
		// create initial path
		m_astar->calculatePath(m_nodeLayout.getNodes()[indexClosestToPlayer], m_nodeLayout.getNodes()[indexClosestToPredator], m_path);
	}
}

void PredatorShip::normalise(sf::Vector2f &v) {
	float magnitude = calculateMagnitude(v);

	if (magnitude > 0)
	{
		v.x = v.x / magnitude;
		v.y = v.y / magnitude;
	}
}

float PredatorShip::calculateMagnitude(sf::Vector2f vec) {
	return sqrt((vec.x * vec.x) + (vec.y * vec.y));
}

float PredatorShip::calculateMagnitude(sf::Vector2f vec1, sf::Vector2f vec2) {
	return sqrt(((vec2.x - vec1.x) * (vec2.x - vec1.x)) + ((vec2.y - vec1.y) * (vec2.y - vec1.y)));
}