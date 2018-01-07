#include "PredatorShip.h"

PredatorShip::PredatorShip(sf::Vector2f pos, NodeLayout &nodes, sf::Vector2f &playerPos) : m_nodeLayout(nodes), m_playerPos(playerPos) {
	m_pos = pos;
	m_maxSpeed = 3.0f;

	m_image.loadFromFile("assets/PredatorShip.png");
	m_texture.loadFromImage(m_image);
	m_sprite.setTexture(m_texture);
	m_sprite.setPosition(m_pos);

	m_astar = new AStar(nodes);
}

void PredatorShip::render(sf::RenderWindow &window) {
	window.draw(m_sprite);
}

void PredatorShip::update(float deltaTime) {
	setupPath();

	// seeks towards player
	seek(deltaTime);

	// checks if the velocity is greater than its max velocity
	float velCheck = calculateMagnitude(m_vel);

	if (velCheck > m_maxSpeed) {
		normalise(m_vel);
		m_vel *= m_maxSpeed;
	}

	m_pos += m_vel;
	m_sprite.setPosition(m_pos);
}

void PredatorShip::seek(float deltaTime) {
	sf::Vector2f vecToPlayer = m_playerPos - m_pos;

	if (!m_path.empty()) {
		sf::Vector2f vecToNextPoint = m_path.at(0)->getPos() - m_pos;
		float distToNextPoint = calculateMagnitude(vecToNextPoint);

		if (distToNextPoint < calculateMagnitude(vecToPlayer)) {
			normalise(vecToNextPoint);
			vecToNextPoint *= m_maxSpeed;

			m_vel += vecToNextPoint * deltaTime;

			if (distToNextPoint < 80) {
				m_path.erase(m_path.begin());
			}
		}
		else {
			normalise(vecToPlayer);
			vecToPlayer *= m_maxSpeed;

			m_vel += vecToPlayer * deltaTime;
		}
	}
	else {
		normalise(vecToPlayer);
		vecToPlayer *= 10.0f;

		m_vel += vecToPlayer * deltaTime;
	}
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