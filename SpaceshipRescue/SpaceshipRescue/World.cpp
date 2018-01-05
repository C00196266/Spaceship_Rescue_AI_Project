#include "World.h"

World::World() {

}

void World::init() {

	player.Init();
	sampleEnemy.initialise(0);

	enemyVector.push_back(sampleEnemy);
}



void World::render(sf::RenderWindow &window) {



	m_spaceStation.render(window);

	for (enemyIterator = enemyVector.begin(); enemyIterator != enemyVector.end(); enemyIterator++)
	{
		enemyIterator->Draw(window);
	}

	player.Draw(window);
}

void World::update(float deltaTime) {



	player.update(deltaTime);


	int count = 0;

	for (enemyIterator = enemyVector.begin(); enemyIterator != enemyVector.end(); enemyIterator++)
	{
		enemyIterator->update(count, player.getPosition(), deltaTime);
		count++;
	}

	player.update(deltaTime);
}


