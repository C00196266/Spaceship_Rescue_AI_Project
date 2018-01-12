#include "Worker.h"

Worker::Worker(sf::Vector2f pos, NodeLayout &nodes, std::vector<Wall*> &walls) : m_nodeLayout(nodes),  m_walls(walls) {
	m_pos = pos;
	m_nextPosX = pos;
	m_nextPosY = pos;

	m_maxSpeed = 1.75f;
	m_maxAccel = 15;

	m_image.loadFromFile("assets/Worker.png");
	m_texture.loadFromImage(m_image);
	m_sprite.setTexture(m_texture);
	m_sprite.setPosition(m_pos);
	m_sprite.setOrigin(sf::Vector2f(m_texture.getSize().x / 2, m_texture.getSize().y / 2));

	m_astar = new AStar(nodes);

	m_width = m_texture.getSize().x;
	m_height = m_texture.getSize().y;

	m_abducted = false;
	m_rescued = false;
}

void Worker::render(sf::RenderWindow &window) {
	/********************************************//**
*  ...  renders the worker in the game world
	***********************************************/
	if (m_rescued != true && m_abducted != true)
	{
		window.draw(m_sprite);
	}
}

void Worker::update(float deltaTime) {
	/********************************************//**
  *  ...  updates workers who havent been abducted or rescued
 ***********************************************/
	// set up new path for worker
	if (m_rescued != true)
	{
		if (m_path.empty()) {
			setupPath();
		}
		// seek to next node in path
		else {
			seek(deltaTime, m_path.at(0)->getPos() - m_pos);
		}

		// checks if the velocity is greater than its max velocity
		if (calculateMagnitude(m_vel) > m_maxSpeed) {
			normalise(m_vel);
			m_vel *= m_maxSpeed;
		}

		m_nextPosX.x += m_vel.x;
		m_nextPosY.y += m_vel.y;

		// check collisions with wall
		auto iter = m_walls.begin();
		auto endIter = m_walls.end();

		for (; iter != endIter; iter++) {
			checkCollisions((*iter), deltaTime);
		}

		m_pos.x = m_nextPosX.x;
		m_pos.y = m_nextPosY.y;

		m_nextPosX.y = m_pos.y;
		m_nextPosY.x = m_pos.x;

		m_sprite.setPosition(m_pos.x + m_width / 2, m_pos.y + m_height / 2);

		m_orientation = (atan2(m_vel.x, -m_vel.y) * 180 / 3.14159265);
		m_sprite.setRotation(m_orientation);
	}
}


sf::Sprite Worker::getSprite()
{
	return m_sprite;
}

void Worker::seek(float deltaTime, sf::Vector2f v) {
	/********************************************//**
 *  ...  seeks to target
***********************************************/


	// gets distance to next node
	m_distToNextNode = calculateMagnitude(v);

	// slows down when near node
	if (m_distToNextNode < 40) {
		// removes the first node once close enough
		m_path.erase(m_path.begin());
	}
	else if (m_distToNextNode > 140) {
		m_targetSpeed = m_maxSpeed;
	}
	else {
		m_targetSpeed = m_maxSpeed * (m_distToNextNode / 140);
	}

	normalise(v);
	v *= m_targetSpeed;

	float timeToTarget = 4;

	m_accel = v - (m_vel / timeToTarget);

	if (calculateMagnitude(m_accel) > m_maxAccel) {
		normalise(m_accel);
	}

	m_vel += m_accel * deltaTime;
}

void Worker::checkCollisions(Wall* wall, float deltaTime) {
	/********************************************//**
	 *  ...  collision between worker and wall
 ***********************************************/

	// checks for intersection along x between the worker and the wall
	if (m_nextPosX.x < wall->getRight()
		&& m_nextPosX.x + m_width > wall->getPos().x
		&& m_nextPosX.y < wall->getBottom()
		&& m_nextPosX.y + m_height > wall->getPos().y)
	{
		// left of worker collides with the right of the wall
		if (m_nextPosX.x < wall->getRight() && m_nextPosX.x > wall->getPos().x) {
			m_vel.x = 0;
			m_nextPosX.x = wall->getPos().x + wall->getWidth();
		}
		// right of worker collides with the left of the wall
		else if (m_nextPosX.x + m_width > wall->getPos().x && m_nextPosX.x + m_width < wall->getRight()) {
			m_vel.x = 0;
			m_nextPosX.x = wall->getPos().x - m_width;
		}
	}

	// checks for intersection along y between the worker and the wall
	if (m_nextPosY.x < wall->getRight()
		&& m_nextPosY.x + m_width > wall->getPos().x
		&& m_nextPosY.y < wall->getBottom()
		&& m_nextPosY.y + m_height > wall->getPos().y)
	{
		// bottom of worker collides with top of the wall
		if (m_nextPosY.y + m_height > wall->getPos().y && m_nextPosY.y + m_height < wall->getBottom()) {
			m_vel.y = 0;
			m_nextPosY.y = wall->getPos().y - m_height;
		}
		// top of worker collides with bottom of the wall
		else if (m_nextPosY.y < wall->getBottom() && m_nextPosY.y > wall->getPos().y) {
			m_vel.y = 0;
			m_nextPosY.y = wall->getPos().y + wall->getHeight();
		}
	}
}

void Worker::setupPath() {
	srand(time(NULL));
	/********************************************//**
	  *  ...  generates random path for worker
	 ***********************************************/
	//gets node closest to worker
	float closestNodeDist = 99999;
	int closestNodeIndex;

	for (int i = 0; i < m_nodeLayout.getNoOfNodes() - 1; i++) {
		float nodeDist = calculateMagnitude(m_nodeLayout.getNodes()[i]->getPos(), m_pos);

		if (nodeDist < closestNodeDist) {
			closestNodeDist = nodeDist;
			closestNodeIndex = i;
		}
	}

	pickRandomDest(rand() % (m_nodeLayout.getNoOfNodes() - 1), closestNodeIndex);
}

void Worker::pickRandomDest(int randomIndex, int startIndex) {
	/********************************************//**
*  ...  selects random destination for worker
***********************************************/

	// stops the random dest node to be the same as the starting node
	if (randomIndex == startIndex) {
		pickRandomDest(rand() % (m_nodeLayout.getNoOfNodes() - 1), startIndex);
	}
	else {
		m_astar->calculatePath(m_nodeLayout.getNodes()[randomIndex], m_nodeLayout.getNodes()[startIndex], m_path);
	}
}

void Worker::normalise(sf::Vector2f &v) {
	/********************************************//**
  *  ...  normalise vector 
	 ***********************************************/

	float magnitude = calculateMagnitude(v);

	if (magnitude > 0)
	{
		v.x = v.x / magnitude;
		v.y = v.y / magnitude;
	}
}

float Worker::calculateMagnitude(sf::Vector2f v) {
	/********************************************//**
  *  ...  calc mag of a vector
	  ***********************************************/
	return sqrt((v.x * v.x) + (v.y * v.y));
}

float Worker::calculateMagnitude(sf::Vector2f v1, sf::Vector2f v2) {
	/********************************************//**
	  *  ...  calc mag of two vectors
  ***********************************************/
	return sqrt(((v2.x - v1.x) * (v2.x - v1.x)) + ((v2.y - v1.y) * (v2.y - v1.y)));
}

void Worker::setRescued(bool rescued) {
	m_rescued = rescued;
}

bool Worker::getRescued() {
	return m_rescued;
}

void Worker::setAbducted(bool abducted) {
	m_abducted = abducted;
}

bool Worker::getAbducted() {
	return m_abducted;
}

sf::Vector2f Worker::getPos() {
	return m_pos;
}

sf::Vector2f Worker::getCenter() {
	return sf::Vector2f(m_pos.x + (m_width / 2), m_pos.y + (m_height / 2));
}