#include "World.h"

World::World() {

}

void World::init() {
	player.Init();
}


void World::render(sf::RenderWindow &window) {

	player.Draw(window);
}

void World::update(float deltaTime) {

	player.Update();
}