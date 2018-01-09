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


float PredatorShip::getOrient(float orientation, sf::Vector2f velocity, sf::Vector2f target)
{

	float bearingRad = atan2f(target.x - m_pos.x, target.y - m_pos.y);
	float bearingDegrees = bearingRad * (180 / 3.14);
	bearingDegrees = (bearingDegrees > 0.0 ? bearingDegrees : (360.0 + bearingDegrees));

	return bearingDegrees;

}


float PredatorShip::Arrive(sf::Vector2f target)
{
	sf::Vector2f temp = sf::Vector2f(target.x + 16, target.y + 16) - sf::Vector2f(m_pos.x + 16, m_pos.y + 16);

	float mag = temp.x * temp.x + temp.y * temp.y;
	mag = sqrt(mag);


	if (mag < 20)//target.getRadius())
	{
		//m_isAlive = false;
	//	cout << "pred in range" << endl;
//
//		cout << "kaboom" << endl;
////
//		lifeClock.restart();
//		lifetime = sf::Time::Zero;

		return 0;
	}
}

void PredatorShip::Seek(sf::Vector2f target)
{
	m_vel = sf::Vector2f(target.x + 16, target.y + 16) - sf::Vector2f(m_pos.x + 16, m_pos.y + 16);

	float mag = m_vel.x * m_vel.x + m_vel.y * m_vel.y;

	mag = sqrt(mag); //length of vector

	if (mag != 0)
	{
		m_vel = m_vel / mag;
	}

	m_vel = m_vel * m_maxSpeed;

	orient = getOrient(orient, m_vel, target);

	Arrive(target); //aka explode
}


void PredatorShip::update(float deltaTime) {
	setupPath();

	// seeks towards player
	chooseTarget(deltaTime);



//	delta = deltaTime;

//	Seek(target);


	if (orient < 0)
	{
		orient = (360) - (-orient);
	}

	m_pos += m_vel;

	int tempOri = orient;

	tempOri += 360;

	tempOri = tempOri % 360;
	tempOri *= -1;

	m_sprite.setRotation((tempOri + 180));

	m_sprite.setRotation(tempOri);

	m_sprite.setPosition(m_pos); //set position of sprite
}
//	else
//	{
//		//explode
//
//		//	delete this;
//	}
//
//	//// checks if the velocity is greater than its max velocity
//	//float velCheck = calculateMagnitude(m_vel);
//
//	//if (velCheck > m_maxSpeed) {
//	//	normalise(m_vel);
//	//	m_vel *= m_maxSpeed;
//	//}
//
//	//m_pos += m_vel;
//	//m_sprite.setPosition(m_pos);
//
//	//m_orientation = (atan2(m_vel.x, -m_vel.y) * 180 / 3.14159265);
//	//m_sprite.setRotation(m_orientation);
//}

void PredatorShip::chooseTarget(float deltaTime) {
	// directional vector to player
	sf::Vector2f vecToPlayer = m_playerPos - m_pos;
	m_distToPlayer = calculateMagnitude(vecToPlayer);

	if (playerSeek)
	{
		seek(deltaTime, vecToPlayer);
		m_path.clear();
	}
	else
	{
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
}

void PredatorShip::seek(float deltaTime, sf::Vector2f v) {

	m_vel = sf::Vector2f(v.x + 16, v.y + 16) - sf::Vector2f(m_pos.x + 16, m_pos.y + 16);

	float mag = m_vel.x * m_vel.x + m_vel.y * m_vel.y;

	mag = sqrt(mag); //length of vector

	if (mag != 0)
	{
		m_vel = m_vel / mag;
	}

	m_vel = m_vel * m_maxSpeed;

	orient = getOrient(orient, m_vel, v);

//	Arrive(target); //aka explode

	//////$$$$$$$$
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

	//normalise(v);
	//v *= m_maxSpeed;
	//
	//m_vel += v * deltaTime;
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

	float playerCostDist = calculateMagnitude(m_nodeLayout.getNodes()[indexClosestToPlayer]->getPos(), m_pos);

	float nodeCostDist = calculateMagnitude(m_playerPos, m_pos);


	/*if ( < )*/
	if (playerCostDist < nodeCostDist)
	{
		playerSeek = true;
	}
	else
	{
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
		playerSeek = false;
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