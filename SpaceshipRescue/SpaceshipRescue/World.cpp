#include "World.h"
#include <iostream>
World::World() {

}

void World::init() {

	player.Init();
	m_predator = new PredatorShip(sf::Vector2f(1344, 640), m_spaceStation.getNodeLayout(), player.getPositionRef(), m_spaceStation.getWalls());
	
	m_nest.init();
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

	m_nest.render(window);

	//for (seekerMissileIterator = seekerMissileVector.begin(); seekerMissileIterator != seekerMissileVector.end(); seekerMissileIterator++)
	//{
	//	seekerMissileIterator->Draw(window);
	//}

	player.Draw(window);
	m_predator->render(window);


	//view #2 minimap
	window.setView(m_radar);

	m_spaceStation.render(window);

	m_nest.render(window);

	//for (seekerMissileIterator = seekerMissileVector.begin(); seekerMissileIterator != seekerMissileVector.end(); seekerMissileIterator++)
	//{
	//	seekerMissileIterator->Draw(window);
	//}

	player.Draw(window);
}


void World::update(float deltaTime) {
	player.update(deltaTime);
	m_predator->update(deltaTime);



	m_nest.update(deltaTime, player);
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

	player.update(deltaTime);
}
