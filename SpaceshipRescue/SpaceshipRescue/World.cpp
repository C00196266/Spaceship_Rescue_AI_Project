#include "World.h"

World::World() {

}

void World::init() {
	srand(time(NULL));



	// gives worker random position on map
	for (int i = 0; i < 15; i++) {
		m_workers.push_back(new Worker(m_spaceStation.getFloors().at(rand() % (m_spaceStation.getFloors().size() - 1))->getPos(), m_spaceStation.getNodeLayout(), m_spaceStation.getWalls()));
	}
	player = new Player(m_spaceStation.getWalls());

	player->Init(m_workers);
	
	m_nest = new Nest( m_spaceStation.getNodeLayout(), player, m_spaceStation.getWalls());

	m_nest2 = new Nest(m_spaceStation.getNodeLayout(), player, m_spaceStation.getWalls());

	m_nest3 = new Nest(m_spaceStation.getNodeLayout(), player, m_spaceStation.getWalls());

	m_nest->init(0);
	m_nest2->init(1);
	m_nest3->init(2);

	for (int i = 0; i < 5; i++) {
		m_sweepers.push_back(new SweeperBoid(m_spaceStation.getNodeLayout(), player, m_spaceStation.getWalls(), m_workers, i));
	}

	// mini-map (upper-right corner)
	m_radar.setViewport(sf::FloatRect(0.75f, -0.05f, 0.25f, 0.25f));

	m_radar.setSize(3996, 2496);
	aStar = new AStar(m_spaceStation.getNodeLayout());

	font.loadFromFile("ITCBLKAD.TTF");

	// Create a text
	text.setFont(font);
	text.setString("Health: " + std::to_string(player->getHealth()));

	text.setCharacterSize(30);
	text.setStyle(sf::Text::Bold);
	text.setFillColor(sf::Color::Black);
	text.setOutlineColor(sf::Color::White);
	text.setPosition(sf::Vector2f(0, 0));
	text.setCharacterSize(16);
}

void World::render(sf::RenderWindow &window) 
{

	m_spaceStation.render(window);

	m_nest->render(window);
	m_nest2->render(window);
	m_nest3->render(window);

	for (int i = 0; i < m_workers.size(); i++) {
		m_workers.at(i)->render(window);
	}

	for (int i = 0; i < m_sweepers.size(); i++) {
		m_sweepers.at(i)->render(window);
	}

	player->Draw(window);
	window.draw(text);
	//view #2 minimap
	window.setView(m_radar);

	m_spaceStation.render(window);

	m_nest->radarRender(window);

	m_nest2->radarRender(window);
	m_nest3->radarRender(window);

	player->DrawRadar(window);


}

void World::update(float deltaTime) {



	player->update(deltaTime);
	activeSweeps = 0;
	for (int i = 0; i < m_workers.size(); i++) {
		if (m_workers.at(i)->getAbducted() == false && m_workers.at(i)->getAbducted() == false) {
			m_workers.at(i)->update(deltaTime);
			activeSweeps++;
		}
	}

	for (std::vector<PowerUp*>::iterator i = m_spaceStation.getPowerUps().begin(); i != m_spaceStation.getPowerUps().end(); i++) {
		if ((*i)->getAlive() == true) {
			if ((*i)->getID() == "health") {
				static_cast<HealthPowerUp*>(*i)->checkCollision(player);
			}
			else if ((*i)->getID() == "shield") {
				static_cast<ShieldPowerUp*>(*i)->checkCollision(player);
			}
			else {
				static_cast<FireRatePowerUp*>(*i)->checkCollision(player);
			}
		}
	}

	// deletes powerups that have been collected from the vector
	for (int i = 0; i < m_spaceStation.getPowerUps().size(); i++) {
		if (m_spaceStation.getPowerUps().at(i)->getAlive() == false) {
			m_spaceStation.getPowerUps().erase(m_spaceStation.getPowerUps().begin() + i);
		}
	}

	for (int i = 0; i < m_sweepers.size(); i++) {
		m_sweepers.at(i)->update(deltaTime);

		// sets any workers by the sweeper to be rescued when the sweeper dies
		if (m_sweepers.at(i)->getAlive() == false) {
			for (int j = 0; j < m_sweepers.at(i)->getIndexesOfAbducted().size(); j++) {
				for (int k = 0; k < m_workers.size(); k++) {
					if (k == m_sweepers.at(i)->getIndexesOfAbducted().at(j)) {
						m_workers.at(k)->setRescued(true);
					}
				}
			}

			m_sweepers.erase(m_sweepers.begin() + i);
		}
	}

	m_nest->update(deltaTime, player);
	m_nest2->update(deltaTime, player);
	m_nest3->update(deltaTime, player);


	int temp = player->getHealth();

	text.setString("Health: " + std::to_string(temp) + "                     " + "Workers active: " + std::to_string(activeSweeps));


	text.setPosition(player->getPosition() - sf::Vector2f(160, 100));
}
