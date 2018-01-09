#include "World.h"
#include <iostream>
World::World() {

}

void World::init() {

	player.Init();
	
	m_nest.init();
	//seekerMissileArray[0].initialise(0);
	//seekerMissileArray[1].initialise(0);

	//seekerMissileArray[1].setPosition(sf::Vector2f(500, 500));

	//seekerMissileVector.push_back(seekerMissileArray[0]);
	//seekerMissileVector.push_back(seekerMissileArray[1]);

	// mini-map (upper-right corner)
	m_radar.setViewport(sf::FloatRect(0.66f, -0.07f, 0.33f, 0.33f));

	m_radar.setSize(3996, 2496);
	aStar = new AStar(m_spaceStation.getNodeLayout());
	m_predator = new PredatorShip(sf::Vector2f(1000, 700), m_spaceStation.getNodeLayout(), player.getPositionRef());

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
	m_predator->render(window);
	player.Draw(window);


//	view #2 minimap
	window.setView(m_radar);

	m_spaceStation.render(window);

	m_nest.render(window);

	//for (seekerMissileIterator = seekerMissileVector.begin(); seekerMissileIterator != seekerMissileVector.end(); seekerMissileIterator++)
	//{
	//	seekerMissileIterator->Draw(window);
	//}
	m_predator->render(window);
	player.Draw(window);

}


void World::update(float deltaTime) {
	std::vector<Node*> path;

	aStar->calculatePath(m_spaceStation.getNodeLayout().getNodes()[23], m_spaceStation.getNodeLayout().getNodes()[6], path);

	player.update(deltaTime);



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
	m_predator->update(deltaTime);
	player.update(deltaTime);
}


