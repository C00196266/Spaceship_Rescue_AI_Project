#include "World.h"

World::World() {

}

void World::init() {
	player.Init();
	aStar = new AStar(m_spaceStation.getNodeLayout());
}


void World::render(sf::RenderWindow &window) {
	m_spaceStation.render(window);
	player.Draw(window);
}

void World::update(float deltaTime) {
	std::vector<Node*> path;

	aStar->calculatePath(m_spaceStation.getNodeLayout().getNodes()[23], m_spaceStation.getNodeLayout().getNodes()[6], path);

	player.update(deltaTime);
}