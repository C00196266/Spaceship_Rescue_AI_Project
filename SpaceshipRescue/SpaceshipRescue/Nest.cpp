#include "Nest.h"
#include <iostream>
//Nest::Nest() {
//
//}

Nest::Nest(NodeLayout &nodes, Player* player, std::vector<Wall*> &walls) : m_nodeLayout(nodes), m_player(player), m_walls(walls) {

}

void Nest::init(int i) 
{
	/********************************************//**
*  ... intialise nest obj variables 
	***********************************************/
	


	m_texture.loadFromFile("nest.png"); //reset relevant vars
	m_image.setTexture(m_texture); //apply texture to image

	if (i == 0)
	{
		m_position = sf::Vector2f(200, 200); //offset each SeekerMissile (formerly i* 86) CONST
	}
	else if (i == 1)
	{
		m_position = sf::Vector2f(200, 1500);
	}
	else if (i == 2)
	{
		m_position = sf::Vector2f(2300, 750);
	}
	m_isAlive = true; //for test only

	m_image.setOrigin(sf::Vector2f(m_texture.getSize().x / 2.0f, (m_texture.getSize().y  / 2.0f)));

	m_image.setScale(0.1f, 0.1f);
	m_image.rotate(0);

	offSetX = m_image.getGlobalBounds().width / 2.0f;
	offSetY = m_image.getGlobalBounds().height / 2.0f;

	m_image.setPosition(m_position);

	//children stuff

	predatorVector.push_back(new PredatorShip(m_position, m_nodeLayout, m_player, m_walls));

	seekerMissileArray[0].initialise(0, m_position);

	seekerMissileVector.push_back(seekerMissileArray[0]);




	m_radarTexture.loadFromFile("assets/blipNest.png");
	m_radarImage.setTexture(m_radarTexture);
	m_radarImage.setOrigin(m_radarTexture.getSize().x / 2.0f, m_radarTexture.getSize().y / 2.0f);
	m_radarImage.setScale(0.2f, 0.2f);

}

void Nest::radarRender(sf::RenderWindow &window)
{

	/********************************************//**
			  *  ...  render a radar blip of the nest on minimap
 ***********************************************/
	if (m_isAlive == true)
	{


		window.draw(m_radarImage);



		for (predatorIterator = predatorVector.begin(); predatorIterator != predatorVector.end(); predatorIterator++)
		{
			(*predatorIterator)->renderRadar(window);
		}

	}

}

void Nest::render(sf::RenderWindow &window)
{
	/********************************************//**
	 *  ...  render the nest sprite in game world
 ***********************************************/
	if (m_isAlive == true)
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

	}

}


void Nest::update(float deltaTime, Player* player)
{
	/********************************************//**
	  *  ...  update nest and nest spawned objects
  ***********************************************/
	if (m_isAlive == true)
	{

		spawnTime += spawnClock.getElapsedTime();


		m_radarImage.setPosition(m_position);

		int count = 0;

		for (predatorIterator = predatorVector.begin(); predatorIterator != predatorVector.end(); predatorIterator++)
		{
			if ((*predatorIterator)->getAlive())
			{
				count++;
			}
			(*predatorIterator)->update(deltaTime);
		}



		for (seekerMissileIterator = seekerMissileVector.begin(); seekerMissileIterator != seekerMissileVector.end(); seekerMissileIterator++)
		{
			if (seekerMissileIterator->getAlive())
			{

				seekerMissileIterator->update(count, player, deltaTime);

			}
			else
			{
				seekerMissileIterator->setPosition(m_position);
				seekerMissileIterator->setAlive(true); //rebirth

			}
			count++; 
		}

		std::vector<Projectile*> bulletVector = (*player).getBullets();
		std::vector<Projectile*>::iterator bulletIterator;



		for (bulletIterator = bulletVector.begin(); bulletIterator != bulletVector.end(); ++bulletIterator)
		{
			if ((*bulletIterator)->getAlive())
			{
				if ((*bulletIterator)->getPosition().x < m_position.x + offSetX
					&& (*bulletIterator)->getPosition().x + (*player).getRect().width > m_position.x
					&& (*bulletIterator)->getPosition().y <  m_position.y + offSetY
					&& (*bulletIterator)->getPosition().y + (*player).getRect().height > m_position.y)
				{
					// adds shield that protects from one attack... to be complete
					m_health -= 1;
					(*bulletIterator)->setAlive(false);
					if (m_health <= 0)
					{
						m_isAlive = false;

					}
				}
			}
		}


		if (count < 4 && spawnTime.asMilliseconds() > 1000000)
		{
			predatorVector.push_back(new PredatorShip(m_position, m_nodeLayout, m_player, m_walls));
			spawnClock.restart();
			spawnTime = sf::Time::Zero;
			std::cout << "spawn" << std::endl;
		}

	}
}


