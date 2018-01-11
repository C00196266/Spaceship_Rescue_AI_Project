#include "Nest.h"
#include <iostream>
//Nest::Nest() {
//
//}

Nest::Nest(sf::Vector2f pos, NodeLayout &nodes, sf::Vector2f &playerPos, std::vector<Wall*> &walls) : m_nodeLayout(nodes), m_playerPos(playerPos), m_walls(walls) {
	//m_pos = pos;
	//m_nextPosX = pos;
	//m_nextPosY = pos;

	//m_maxSpeed = 3.0f;

	//m_image.loadFromFile("assets/PredatorShip.png");
	//m_texture.loadFromImage(m_image);
	//m_sprite.setTexture(m_texture);
	//m_sprite.setPosition(m_pos);
	//m_sprite.setOrigin(sf::Vector2f(m_texture.getSize().x / 2, m_texture.getSize().y / 2));

	//m_astar = new AStar(nodes);

	//m_maxAccel = 30;

	//m_width = m_texture.getSize().x;
	//m_height = m_texture.getSize().y;
}

void Nest::init(int i) 
{

	


	m_texture.loadFromFile("nest.png"); //reset relevant vars
	m_image.setTexture(m_texture); //apply texture to image

	if (i == 0)
	{
		m_position = sf::Vector2f(200, 200); //offset each SeekerMissile (formerly i* 86) CONST
	}
	else if (i == 1)
	{

	}
	else if (i == 2)
	{

	}
	m_isAlive = true; //for test only

	m_image.setOrigin(sf::Vector2f(m_image.getGlobalBounds().width / 2.0f, (m_image.getGlobalBounds().height / 2.0f)));

	m_image.setScale(0.1f, 0.1f);
	m_image.rotate(0);

	offSetX = m_image.getGlobalBounds().width / 2.0f;
	offSetY = m_image.getGlobalBounds().height / 2.0f;




	m_image.setPosition(m_position);



	//children stuff

	predatorVector.push_back(new PredatorShip(m_position, m_nodeLayout, m_playerPos, m_walls));

	seekerMissileArray[0].initialise(0);

	seekerMissileArray[0].setPosition(m_position);

	seekerMissileVector.push_back(seekerMissileArray[0]);

}



void Nest::render(sf::RenderWindow &window)
{
	window.draw(m_image);

	for (seekerMissileIterator = seekerMissileVector.begin(); seekerMissileIterator != seekerMissileVector.end(); seekerMissileIterator++)
	{
		seekerMissileIterator->Draw(window);
	}

	for (predatorIterator = predatorVector.begin(); predatorIterator != predatorVector.end(); predatorIterator++)
	{
		(*predatorIterator)->render(window);
	}


	//for (seekerMissileIterator = seekerMissileVector.begin(); seekerMissileIterator != seekerMissileVector.end(); seekerMissileIterator++)
	//{
	//	seekerMissileIterator->Draw(window);
	//}


}


void Nest::update(float deltaTime, Player player)
{

	int count = 0;

	for (predatorIterator = predatorVector.begin(); predatorIterator != predatorVector.end(); predatorIterator++)
	{
		(*predatorIterator)->update(deltaTime);
	}


	for (seekerMissileIterator = seekerMissileVector.begin(); seekerMissileIterator != seekerMissileVector.end(); seekerMissileIterator++)
	{
		if (seekerMissileIterator->getAlive())
		{

			seekerMissileIterator->update(count, player.getPosition(), deltaTime);

		}
		else
		{
			seekerMissileIterator->setPosition(m_position);
			seekerMissileIterator->setAlive(true); //rebirth


			//seekerMissileVector.erase(seekerMissileIterator);
		}
		count++; //compromised by isalive atm
	}

	//player.update(deltaTime);
}


