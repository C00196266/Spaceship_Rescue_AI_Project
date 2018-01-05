#include "Node.h"

Node::Node(sf::Vector2f pos, std::string id) {
	m_pos = pos;
	m_id = id;
}

void Node::addArc(Arc arc) {
	m_arcs.push_back(arc);
}

sf::Vector2f Node::getPos() {
	return m_pos;
}

std::string Node::getID() {
	return m_id;
}