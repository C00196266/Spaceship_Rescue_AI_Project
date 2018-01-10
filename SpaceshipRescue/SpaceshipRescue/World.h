#pragma once
#include "SeekerMissile.h"
#include "SpaceStation.h"
#include "PredatorShip.h"
#include "Nest.h"
#include "AStar.h"

class World {
public:
	World();

	void render(sf::RenderWindow &window);
	void init();

	void update(float deltaTime);

	sf::View m_radar;

	Player player;
	SpaceStation m_spaceStation;
	PredatorShip* m_predator;


	Nest m_nest;
	AStar* aStar;
	//SeekerMissile sampleSeekerMissile;
	//SeekerMissile sample2;




	//SeekerMissile seekerMissileArray[50];

	//std::vector<SeekerMissile> seekerMissileVector;

	//std::vector<SeekerMissile>::iterator seekerMissileIterator;
private:
	/*Player player;
	SpaceStation m_spaceStation;
	*/
};
