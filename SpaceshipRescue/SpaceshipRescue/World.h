#pragma once
#include "SeekerMissile.h"
#include "SpaceStation.h"
#include "Nest.h"
#include "AStar.h"
#include "PredatorShip.h"

class World {
public:
	World();

	void render(sf::RenderWindow &window);
	void init();

	void update(float deltaTime);

	sf::View m_radar;

	Player player;
	SpaceStation m_spaceStation;

	Nest m_nest;
	AStar* aStar;
	//SeekerMissile sampleSeekerMissile;
	//SeekerMissile sample2;
	PredatorShip* m_predator;



	//SeekerMissile seekerMissileArray[50];

	//std::vector<SeekerMissile> seekerMissileVector;

	//std::vector<SeekerMissile>::iterator seekerMissileIterator;
private:
	/*Player player;
	SpaceStation m_spaceStation;
	*/
};


