#pragma once

#include "stdafx.h"
#include "Arc.h"

class Node {
public:
	Node() {}
	Node(sf::Vector2f pos, std::string id);

	void addArc(Arc arc);

	sf::Vector2f getPos();

	std::string getID();

private:
	std::string m_id;

	sf::Vector2f m_pos;
	
	std::vector<Arc> m_arcs;
};