#include "World.h"

World::World() {

}

void World::init() {
	player.Init();
	m_predator = new PredatorShip(sf::Vector2f(1344, 640), m_spaceStation.getNodeLayout(), player.getPositionRef(), m_spaceStation.getWalls());
}


void World::render(sf::RenderWindow &window) {
	m_spaceStation.render(window);
	player.Draw(window);
	m_predator->render(window);
}

void World::update(float deltaTime) {
	player.update(deltaTime);
	m_predator->update(deltaTime);
}