#pragma once

#include "stdafx.h"

class Node; // stops circular dependency between arc and node
class Arc {
public:
	Arc() {}

	//float getWeight();

	void setNode(Node *n);
	void setWeight(float w);

private:
	Node *m_node;
	int m_weight;
};