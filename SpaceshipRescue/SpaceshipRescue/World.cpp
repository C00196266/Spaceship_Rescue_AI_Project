#include "World.h"
#include <iostream>
World::World() {

}

void World::init() {
	srand(time(NULL));

	//player.Init();
	//m_predator = new PredatorShip(sf::Vector2f(1344, 640), m_spaceStation.getNodeLayout(), player.getPositionRef(), m_spaceStation.getWalls());

	// gives worker random position on map
	m_worker = new Worker(m_spaceStation.getFloors().at(rand() % (m_spaceStation.getFloors().size() - 1))->getPos(), m_spaceStation.getNodeLayout(), m_spaceStation.getWalls());
	player = new Player(m_spaceStation.getWalls());

	player->Init();

	//$$m_predator = new PredatorShip(sf::Vector2f(1344, 640), m_spaceStation.getNodeLayout(), player->getPositionRef(), m_spaceStation.getWalls());
	
	m_nest = new Nest(sf::Vector2f(1344, 640), m_spaceStation.getNodeLayout(), *player, m_spaceStation.getWalls());

	m_nest->init(0);
	//seekerMissileArray[0].initialise(0);
	//seekerMissileArray[1].initialise(0);

	//seekerMissileArray[1].setPosition(sf::Vector2f(500, 500));

	//seekerMissileVector.push_back(seekerMissileArray[0]);
	//seekerMissileVector.push_back(seekerMissileArray[1]);

	// mini-map (upper-right corner)
	m_radar.setViewport(sf::FloatRect(0.75f, -0.05f, 0.25f, 0.25f));

	m_radar.setSize(3996, 2496);
	aStar = new AStar(m_spaceStation.getNodeLayout());
}



void World::render(sf::RenderWindow &window) 
{

	m_spaceStation.render(window);

	//some sort of nest draw

	m_nest->render(window);

	//for (seekerMissileIterator = seekerMissileVector.begin(); seekerMissileIterator != seekerMissileVector.end(); seekerMissileIterator++)
	//{
	//	seekerMissileIterator->Draw(window);
	//}

	//player.Draw(window);
	//m_predator->render(window);
	m_worker->render(window);
	player->Draw(window);
	//$$m_predator->render(window);


	//view #2 minimap
	window.setView(m_radar);

	m_spaceStation.render(window);

	m_nest->render(window);

	//for (seekerMissileIterator = seekerMissileVector.begin(); seekerMissileIterator != seekerMissileVector.end(); seekerMissileIterator++)
	//{
	//	seekerMissileIterator->Draw(window);
	//}

	player->Draw(window);
}


void World::update(float deltaTime) {
	player->update(deltaTime);
	//m_predator->update(deltaTime);

	if (m_worker->getAbducted() == false && m_worker->getRescued() == false) {
		m_worker->update(deltaTime);
	}

	//for (auto i = m_spaceStation.getPowerUps().begin(), e = m_spaceStation.getPowerUps().end(); i != e; i++) {
	//	if ((*i)->getAlive() == true) {
	//		if ((*i)->getID() == "health") {
	//			static_cast<HealthPowerUp*>(*i)->checkCollision(player);
	//		}
	//		else if ((*i)->getID() == "shield") {
	//			static_cast<ShieldPowerUp*>(*i)->checkCollision(player);
	//		}
	//		else {
	//			static_cast<FireRatePowerUp*>(*i)->checkCollision(player);
	//		}
	//	}
	//}

	for (int i = 0; i < m_spaceStation.getPowerUps().size(); i++) {
		if (m_spaceStation.getPowerUps().at(i)->getAlive() == true) {
			if (m_spaceStation.getPowerUps().at(i)->getID() == "health") {
				//static_cast<HealthPowerUp*>m_spaceStation.get
				static_cast<HealthPowerUp*>(m_spaceStation.getPowerUps().at(i))->checkCollision(player);
			}
			else if (m_spaceStation.getPowerUps().at(i)->getID() == "shield") {
				static_cast<ShieldPowerUp*>(m_spaceStation.getPowerUps().at(i))->checkCollision(player);
			}
			else {
				static_cast<FireRatePowerUp*>(m_spaceStation.getPowerUps().at(i))->checkCollision(player);
			}
		}
		else {
			m_spaceStation.getPowerUps().erase(m_spaceStation.getPowerUps().begin() + i);
		}
		//if (m_spaceStation.getPowerUps().at(i)->getAlive() == true) {
		//	m_spaceStation.getPowerUps().at(i)->checkCollision(player);
		//}
	}

//$$	m_predator->update(deltaTime);

	m_nest->update(deltaTime, *player);
	//int count = 0;

	//for (seekerMissileIterator = seekerMissileVector.begin(); seekerMissileIterator != seekerMissileVector.end(); seekerMissileIterator++)
	//{
	//	if (seekerMissileIterator->getAlive())
	//	{
	//		seekerMissileIterator->update(count, player.getPosition(), deltaTime);
	//	}
	//	else
	//	{
	//		//seekerMissileVector.erase(seekerMissileIterator);
	//	}
	//	count++; //compromised by isalive atm
	//}

	player->update(deltaTime);
}
