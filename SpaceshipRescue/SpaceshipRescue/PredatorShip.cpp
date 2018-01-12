#include "PredatorShip.h"

PredatorShip::PredatorShip(sf::Vector2f pos, NodeLayout &nodes, Player* player, std::vector<Wall*> &walls) : m_nodeLayout(nodes), m_player(player), m_walls(walls) {
	m_pos = pos;
	m_nextPosX = pos;
	m_nextPosY = pos;

	m_maxSpeed = 3.0f;

	m_image.loadFromFile("assets/PredatorShip.png");
	m_texture.loadFromImage(m_image);
	m_sprite.setTexture(m_texture);
	m_sprite.setPosition(m_pos);
	m_sprite.setOrigin(sf::Vector2f(m_texture.getSize().x / 2, m_texture.getSize().y / 2));

	m_astar = new AStar(nodes);

	m_maxAccel = 30;

	m_width = m_texture.getSize().x;
	m_height = m_texture.getSize().y;

	m_radarTexture.loadFromFile("assets/blipPred.png");
	m_radarImage.setTexture(m_radarTexture);
	m_radarImage.setOrigin(m_radarTexture.getSize().x / 2.0f, m_radarTexture.getSize().y / 2.0f);
	m_radarImage.setScale(0.2f, 0.2f);
	m_fireClock.restart();
	m_fireTime = sf::Time::Zero;
	m_fireRange = 250;

	m_alive = true;
}

bool PredatorShip::getAlive()
{
	return m_alive;
}

void PredatorShip::render(sf::RenderWindow &window) {
	/********************************************//**
	 *  ...  render the predatorship sprite in game world
	***********************************************/
	if (m_alive)
	{
		for (std::vector<Projectile*>::iterator i = m_bullets.begin(); i != m_bullets.end(); i++) {
			(*i)->Draw(window);
		}

		window.draw(m_sprite);
	}
}


void PredatorShip::renderRadar(sf::RenderWindow &window) {
	/********************************************//**
  *  ...  render blip of predatorship on minimap
***********************************************/
	if (m_alive)
	{
		window.draw(m_radarImage);
	}
}


void PredatorShip::update(float deltaTime)
{
	/********************************************//**
  *  ...  update predatorship and bullets of pred ship
	***********************************************/
	if (m_alive)
	{
		std::vector<Projectile*> bulletVector = (*m_player).getBullets();
		std::vector<Projectile*>::iterator bulletIterator;

		for (bulletIterator = bulletVector.begin(); bulletIterator != bulletVector.end(); ++bulletIterator)
		{
			if ((*bulletIterator)->getAlive())
			{
				if ((*bulletIterator)->getPosition().x < m_pos.x + m_width
					&& (*bulletIterator)->getPosition().x + (*m_player).getRect().width > m_pos.x
					&& (*bulletIterator)->getPosition().y < m_pos.y + m_height
					&& (*bulletIterator)->getPosition().y + (*m_player).getRect().height > m_pos.y)
				{
					(*bulletIterator)->setAlive(false);
					m_alive = false;
				}
			}
		}


		setupPath();
		//m_playerPos = playerPos;
		m_radarImage.setPosition(m_pos);
		// seeks towards player
		setupPath();

		// chooses whether to seek towards player or next node
		chooseTarget(deltaTime);

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

	// only fire bullets if the player is alive
	if (m_player->getAlive() == true) {
		fireBullet();
	}

		for (std::vector<Projectile*>::iterator i = m_bullets.begin(); i != m_bullets.end(); i++) {
			if ((*i)->getAlive() == true) {
				checkBulletCollision((*i));
				(*i)->update(deltaTime);
			}
		}

		// removes dead projectiles from the vector
		for (int i = 0; i < m_bullets.size(); i++) {
			if (m_bullets.at(i)->getAlive() == false) {
				m_bullets.erase(m_bullets.begin() + i);
			}
		}

	
	}
}

void PredatorShip::chooseTarget(float deltaTime) {
	/********************************************//**
*  ...  choose target to seek to
 ***********************************************/

	// directional vector to player
	sf::Vector2f vecToPlayer = (m_player)->getPosition() - m_pos;
	m_distToPlayer = calculateMagnitude(vecToPlayer);

	// if there are nodes to seek to
	if (!m_path.empty()) {
		// directional vector to next node
		sf::Vector2f vecToNextPoint = m_path.at(0)->getPos() - m_pos;

		// distance to next node
		m_distToNextPoint = calculateMagnitude(vecToNextPoint);

		// if the next node is closer than the player
		if (m_distToNextPoint < m_distToPlayer) {
			seek(deltaTime, vecToNextPoint, m_distToNextPoint, false);

			if (m_distToNextPoint < 80) {
				m_path.erase(m_path.begin());
			}
		}
		// if the player is closer than the next node
		else {
			seek(deltaTime, vecToPlayer, m_distToPlayer, true);
		}
	}
	// if there aren't nodes to seek to
	else {
		seek(deltaTime, vecToPlayer, m_distToPlayer, true);
	}



}

void PredatorShip::seek(float deltaTime, sf::Vector2f v, float dist, bool seekingPlayer) {
	/********************************************//**
  *  ...  seek to chosen target
  ***********************************************/

	float targetSpeed = 0;

	if (seekingPlayer == false) {
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

void PredatorShip::setupPath() {
	/********************************************//**
 *  ...  // checks which node is closest to the player and the predator
 ***********************************************/
	
	int indexClosestToPlayer;
	int indexClosestToPredator;

	float closestDistPlayer = 99999;
	float closestDistPredator = 99999;

	for (int i = 0; i < m_nodeLayout.getNoOfNodes() - 1; i++) {
		float distPlayer = calculateMagnitude(m_nodeLayout.getNodes()[i]->getPos(), (m_player)->getPosition());

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

void PredatorShip::fireBullet() {
	/********************************************//**
*  ...  predator ship fires bullet
***********************************************/
	m_fireTime += m_fireClock.getElapsedTime();

	// if the player is within firing range
	if (m_distToPlayer < m_fireRange) {
		// if the player is within a certain angle in front of the player
		m_angleToPlayer = (atan2((m_player)->getPosition().y - m_pos.y, (m_player)->getPosition().x - m_pos.x) * 180 / 3.14) + 90;
		
		if (m_angleToPlayer > m_orientation - 15 && m_angleToPlayer < m_orientation + 15) {
			// fire rate
			if (m_fireTime.asMilliseconds() > 7000) {
				m_bullets.push_back(new Projectile(sf::Vector2f(m_pos.x + (m_width / 2) + 2, m_pos.y + (m_height / 2) + 2), m_orientation, calculateMagnitude(m_vel), m_vel));

				m_fireClock.restart();
				m_fireTime = sf::Time::Zero;
			}
		}
	}
}

void PredatorShip::checkWallCollisions(Wall* wall, float deltaTime) {
	/********************************************//**
*  ...  // checks and handles predator wall collisions
***********************************************/

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

void PredatorShip::checkBulletCollision(Projectile* p) {
	/********************************************//**
*  ...  // checks collision between predator bullet and player
***********************************************/

	if (p->getPosition().x < (m_player)->getPosition().x + (m_player)->getRect().width
		&& p->getPosition().x + p->getWidth() >(m_player)->getPosition().x
		&& p->getPosition().y < (m_player)->getPosition().y + (m_player)->getRect().height
		&& p->getPosition().y + p->getHeight() >(m_player)->getPosition().y)
	{
		p->setAlive(false);
		m_player->setHealth(1);
	}
}

void PredatorShip::normalise(sf::Vector2f &v) {

	/********************************************//**
 *  ...  //get normal vector
***********************************************/
	float magnitude = calculateMagnitude(v);

	if (magnitude > 0)
	{
		v.x = v.x / magnitude;
		v.y = v.y / magnitude;
	}
}


float PredatorShip::calculateMagnitude(sf::Vector2f vec) {
	/********************************************//**
	*  ...  // get mag of vector 
 ***********************************************/
	return sqrt((vec.x * vec.x) + (vec.y * vec.y));
}

float PredatorShip::calculateMagnitude(sf::Vector2f vec1, sf::Vector2f vec2) {
	/********************************************//**
	  *  ...  // gets mag of 2 vectors added
	***********************************************/

	return sqrt(((vec2.x - vec1.x) * (vec2.x - vec1.x)) + ((vec2.y - vec1.y) * (vec2.y - vec1.y)));
}

sf::FloatRect PredatorShip::getRect() {
	/********************************************//**
	*  ...  // gets predator rectangle
	 ***********************************************/

	return m_sprite.getGlobalBounds();
}

void PredatorShip::checkPlayerBulletColl()
{
	//i died
}


