#pragma once

#include "Floor.h"
#include "Wall.h"
#include "NodeLayout.h"
#include "HealthPowerUp.h"
#include "ShieldPowerUp.h"
#include "FireRatePowerUp.h"

class SpaceStation {
public:
	SpaceStation();
	void render(sf::RenderWindow & window);

	NodeLayout& getNodeLayout();
	std::vector<Wall*>& getWalls();
	std::vector<Floor*> getFloors();
	std::vector<PowerUp*>& getPowerUps();

private:
	static const int layoutArray[53][78];
	std::vector<Wall*> m_walls;
	std::vector<Floor*> m_floors;
	std::vector<sf::Vector2f> m_nodePositions;
	std::vector<PowerUp*> m_powerups;
	int *layout;

	NodeLayout m_nodeLayout;
};