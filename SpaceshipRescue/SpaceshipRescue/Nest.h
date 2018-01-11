#pragma once
#include "SeekerMissile.h"
#include "Player.h"
#include "SpaceStation.h"
#include "PredatorShip.h"

class Nest {
public:
	Nest();
	Nest(sf::Vector2f pos, NodeLayout &nodes, sf::Vector2f &playerPos, std::vector<Wall*> &walls);

	void render(sf::RenderWindow &window);
	void init(int i);

	void update(float deltaTime, Player player);

	//Player player;
	//SpaceStation m_spaceStation;
	//sf::View m_radar;



private:

	std::vector<PredatorShip*> predatorVector;

	std::vector<PredatorShip*>::iterator predatorIterator;


	sf::Vector2f m_position;
	bool m_isAlive;

	//SeekerMissile sampleSeekerMissile;
	//SeekerMissile sample2;

	SeekerMissile seekerMissileArray[50];

	std::vector<SeekerMissile> seekerMissileVector;

	std::vector<SeekerMissile>::iterator seekerMissileIterator;

	sf::Texture m_texture; //reset relevant vars
	sf::Sprite m_image; //apply texture to image

	sf::Vector2f& m_playerPos;
	NodeLayout& m_nodeLayout;
	std::vector<Wall*>& m_walls;
	std::vector<Wall*> m_closestWalls;
	float offSetX;
	float offSetY;

};


