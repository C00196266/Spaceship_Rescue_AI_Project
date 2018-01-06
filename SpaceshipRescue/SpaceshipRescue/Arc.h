#pragma once

#include "stdafx.h"
#include "Node.h"

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