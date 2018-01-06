#pragma once
#include "SeekerMissile.h"
#include "Player.h"
#include "SpaceStation.h"

class Nest {
public:
	Nest();

	void render(sf::RenderWindow &window);
	void init();

	void update(float deltaTime, Player player);

	//Player player;
	//SpaceStation m_spaceStation;
	//sf::View m_radar;

	sf::Vector2f m_position;
	bool m_isAlive;

	//SeekerMissile sampleSeekerMissile;
	//SeekerMissile sample2;

	SeekerMissile seekerMissileArray[50];

	std::vector<SeekerMissile> seekerMissileVector;

	std::vector<SeekerMissile>::iterator seekerMissileIterator;




	sf::Texture m_texture; //reset relevant vars
	sf::Sprite m_image; //apply texture to image


	float offSetX;
	float offSetY;

};


