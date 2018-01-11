#include "Nest.h"
#include <iostream>
//Nest::Nest() {
//
//}

Nest::Nest(sf::Vector2f pos, NodeLayout &nodes, Player* player, std::vector<Wall*> &walls) : m_nodeLayout(nodes), m_player(player), m_walls(walls) {
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

	m_image.setOrigin(sf::Vector2f(m_texture.getSize().x / 2.0f, (m_texture.getSize().y  / 2.0f)));

	m_image.setScale(0.1f, 0.1f);
	m_image.rotate(0);

	offSetX = m_image.getGlobalBounds().width / 2.0f;
	offSetY = m_image.getGlobalBounds().height / 2.0f;




	m_image.setPosition(m_position);



	//children stuff

	predatorVector.push_back(new PredatorShip(m_position, m_nodeLayout, m_player->getRect(), m_walls));

	seekerMissileArray[0].initialise(0);

	seekerMissileArray[0].setPosition(m_position);

	seekerMissileVector.push_back(seekerMissileArray[0]);




	m_radarTexture.loadFromFile("assets/blipNest.png");
	m_radarImage.setTexture(m_radarTexture);
	m_radarImage.setOrigin(m_radarTexture.getSize().x / 2.0f, m_radarTexture.getSize().y / 2.0f);
	m_radarImage.setScale(0.2f, 0.2f);

}

void Nest::radarRender(sf::RenderWindow &window)
{
	if (m_isAlive == true)
	{


		window.draw(m_radarImage);



		for (predatorIterator = predatorVector.begin(); predatorIterator != predatorVector.end(); predatorIterator++)
		{
			(*predatorIterator)->renderRadar(window);
		}

		//for (seekerMissileIterator = seekerMissileVector.begin(); seekerMissileIterator != seekerMissileVector.end(); seekerMissileIterator++)
		//{
		//	seekerMissileIterator->Draw(window);
		//}

		//for (predatorIterator = predatorVector.begin(); predatorIterator != predatorVector.end(); predatorIterator++)
		//{
		//	(*predatorIterator)->render(window);
		//}


		//for (seekerMissileIterator = seekerMissileVector.begin(); seekerMissileIterator != seekerMissileVector.end(); seekerMissileIterator++)
		//{
		//	seekerMissileIterator->Draw(window);
		//}
	}

}

void Nest::render(sf::RenderWindow &window)
{
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


		//for (seekerMissileIterator = seekerMissileVector.begin(); seekerMissileIterator != seekerMissileVector.end(); seekerMissileIterator++)
		//{
		//	seekerMissileIterator->Draw(window);
		//}
	}

}


void Nest::update(float deltaTime, Player* player)
{
	if (m_isAlive == true)
	{
		m_radarImage.setPosition(m_position);

		int count = 0;

		for (predatorIterator = predatorVector.begin(); predatorIterator != predatorVector.end(); predatorIterator++)
		{
			(*predatorIterator)->update(deltaTime, m_player->getPosition());
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


				//seekerMissileVector.erase(seekerMissileIterator);
			}
			count++; //compromised by isalive atm
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


	}
	//player.update(deltaTime);
}


