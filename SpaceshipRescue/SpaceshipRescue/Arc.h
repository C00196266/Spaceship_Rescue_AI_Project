#pragma once

#include "stdafx.h"

class Arc {
public:
	Arc() {}
	Arc(std::string id, int weight);

	int getWeight();

private:
	std::string m_idOfConnectedNode;
	int m_weight;
};