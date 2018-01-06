#include "Node.h"

Node::Node(sf::Vector2f pos, int id) {
	m_pos = pos;
	m_id = id;
}

//void Node::addArc(Arc arc) {
//	m_arcs.push_back(arc);
//}

sf::Vector2f Node::getPos() {
	return m_pos;
}

int Node::getID() {
	return m_id;
}

bool Node::getMarked() {
	return m_marked;
}

void Node::setMarked(bool marked) {
	m_marked = marked;
}