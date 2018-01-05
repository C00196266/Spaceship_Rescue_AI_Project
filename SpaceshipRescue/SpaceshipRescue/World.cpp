#include "World.h"

World::World() {

}

void World::init() {
	player.Init();
}


void World::render(sf::RenderWindow &window) {
	m_spaceStation.render(window);
	player.Draw(window);
}

void World::update(float deltaTime) {

	player.update(deltaTime);
}