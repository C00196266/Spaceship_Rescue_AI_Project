#pragma once
#include "SeekerMissile.h"
#include "Player.h"
#include "SpaceStation.h"

class World {
public:
	World();

	void render(sf::RenderWindow &window);
	void init();

	void update(float deltaTime);

	sf::View m_radar;

	Player player;
	SpaceStation m_spaceStation;

	//SeekerMissile sampleSeekerMissile;
	//SeekerMissile sample2;

	SeekerMissile seekerMissileArray[50];

	std::vector<SeekerMissile> seekerMissileVector;

	std::vector<SeekerMissile>::iterator seekerMissileIterator;
};


