#include "Nest.h"
#include <iostream>
Nest::Nest() {

}

void Nest::init() 
{

	


	m_texture.loadFromFile("nest.png"); //reset relevant vars
	m_image.setTexture(m_texture); //apply texture to image
	m_position = sf::Vector2f(100, 100); //offset each SeekerMissile (formerly i* 86) CONST

	m_isAlive = true; //for test only

	m_image.setOrigin(sf::Vector2f(m_image.getGlobalBounds().width / 2.0f, (m_image.getGlobalBounds().height / 2.0f)));

	m_image.setScale(0.1f, 0.1f);
	m_image.rotate(0);

	offSetX = m_image.getGlobalBounds().width / 2.0f;
	offSetY = m_image.getGlobalBounds().height / 2.0f;


	//children stuff

	seekerMissileArray[0].initialise(0);

	seekerMissileArray[1].setPosition(m_position);

	seekerMissileVector.push_back(seekerMissileArray[0]);

}



void Nest::render(sf::RenderWindow &window)
{
	window.draw(m_image);

	for (seekerMissileIterator = seekerMissileVector.begin(); seekerMissileIterator != seekerMissileVector.end(); seekerMissileIterator++)
	{
		seekerMissileIterator->Draw(window);
	}


	//for (seekerMissileIterator = seekerMissileVector.begin(); seekerMissileIterator != seekerMissileVector.end(); seekerMissileIterator++)
	//{
	//	seekerMissileIterator->Draw(window);
	//}


}


void Nest::update(float deltaTime, Player player)
{

	int count = 0;

	for (seekerMissileIterator = seekerMissileVector.begin(); seekerMissileIterator != seekerMissileVector.end(); seekerMissileIterator++)
	{
		if (seekerMissileIterator->getAlive())
		{
			seekerMissileIterator->update(count, player.getPosition(), deltaTime);
		}
		else
		{
			//seekerMissileVector.erase(seekerMissileIterator);
		}
		count++; //compromised by isalive atm
	}

	//player.update(deltaTime);
}


