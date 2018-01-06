#pragma once

#include "stdafx.h"
#include "Node.h"
#include "Arc.h"

#include <list>
#include <queue>

class SearchAlgorithm {
public:
	SearchAlgorithm() {}
	SearchAlgorithm(std::vector<sf::Vector2f> &nodeData);

private:
	Node** m_nodes; // pointer to array of pointers to nodes

	int m_noOfNodes;

	void ucs(Node* pStart, Node* pDest, std::vector<Node *>& path);
	void aStar(Node* pStart, Node* pDest, std::vector<Node*>& path);
};