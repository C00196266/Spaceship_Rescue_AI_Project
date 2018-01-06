#pragma once
#include "SeekerMissile.h"
#include "SpaceStation.h"
#include "Nest.h"

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

	//SeekerMissile sampleSeekerMissile;
	//SeekerMissile sample2;




	//SeekerMissile seekerMissileArray[50];

	//std::vector<SeekerMissile> seekerMissileVector;

	//std::vector<SeekerMissile>::iterator seekerMissileIterator;
};


