#include "Node.h"

Node::Node(sf::Vector2f pos, int id) {
	m_pos = pos;
	m_id = id;
}

void Node::addArc(Node *n) {
	Arc arc;

	arc.setNode(n);
	arc.setWeight(calculateArcWeight(n->getPos()));

	m_arcs.push_back(arc);
}

float Node::calculateArcWeight(sf::Vector2f otherNodePos) {
	// weight is the distance between the nodes
	return sqrt(((otherNodePos.x - m_pos.x) * (otherNodePos.x - m_pos.x)) + ((otherNodePos.y - m_pos.y) * (otherNodePos.y - m_pos.y)));
}

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