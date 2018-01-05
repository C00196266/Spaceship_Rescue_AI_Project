#include "Arc.h"

Arc::Arc(std::string id, int weight) {
	m_idOfConnectedNode = id;
	m_weight = weight;
}

int Arc::getWeight() {
	return m_weight;
}