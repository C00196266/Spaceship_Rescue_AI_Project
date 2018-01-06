#pragma once

#include "stdafx.h"
#include "Arc.h"

#include <list>

class Node {
public:
	Node() {}
	Node(sf::Vector2f pos, int id);

	void addArc(Node *n);
	float calculateArcWeight(sf::Vector2f otherNodePos);

	sf::Vector2f getPos();

	int getID();

	bool getMarked();
	void setMarked(bool marked);

private:
	int m_id;
	sf::Vector2f m_pos;
	bool m_marked; // if the node has been visited
	
	std::list<Arc> m_arcs;
};