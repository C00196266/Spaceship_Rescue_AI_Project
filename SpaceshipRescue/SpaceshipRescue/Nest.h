#pragma once
#include "SeekerMissile.h"
#include "Player.h"
#include "SpaceStation.h"
#include "PredatorShip.h"

class Nest {
public:
	Nest();
	Nest(NodeLayout &nodes, Player* player, std::vector<Wall*> &walls);


	void render(sf::RenderWindow &window);
	void init(int i);

	void update(float deltaTime, Player* player);
	void radarRender(sf::RenderWindow &window);
	//Player player;
	//SpaceStation m_spaceStation;
	//sf::View m_radar;



private:

	std::vector<PredatorShip*> predatorVector;

	std::vector<PredatorShip*>::iterator predatorIterator;
	Player* m_player;

	sf::Vector2f m_position;
	bool m_isAlive = true;

	//SeekerMissile sampleSeekerMissile;
	//SeekerMissile sample2;

	SeekerMissile seekerMissileArray[50];

	std::vector<SeekerMissile> seekerMissileVector;

	std::vector<SeekerMissile>::iterator seekerMissileIterator;

	sf::Texture m_texture; //reset relevant vars
	sf::Sprite m_image; //apply texture to image
	sf::Sprite m_radarImage;
	sf::Texture m_radarTexture;

	int m_health = 4;

	sf::Clock spawnClock;
	sf::Time spawnTime;

//	sf::Vector2f& m_playerPos;
	NodeLayout& m_nodeLayout;
	std::vector<Wall*>& m_walls;
	std::vector<Wall*> m_closestWalls;
	float offSetX = m_texture.getSize().x / 2.0f;
	float offSetY = m_texture.getSize().y / 2.0f;

};


