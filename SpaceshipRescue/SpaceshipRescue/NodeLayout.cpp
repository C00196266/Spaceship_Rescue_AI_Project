#include "NodeLayout.h"

NodeLayout::NodeLayout(std::vector<sf::Vector2f> &nodeData) {
	m_noOfNodes = nodeData.size() + 1;

	m_nodes = new Node*[m_noOfNodes];

	for (int i = 0; i < nodeData.size(); i++) {
		m_nodes[i] = new Node(nodeData.at(i), i);
		m_nodes[i]->setMarked(false);
	}

	addArcs();
}

void NodeLayout::addArcs() {
	m_nodes[0]->addArc(m_nodes[1]);
	m_nodes[1]->addArc(m_nodes[0]);

	m_nodes[1]->addArc(m_nodes[2]);
	m_nodes[2]->addArc(m_nodes[1]);
	
	m_nodes[2]->addArc(m_nodes[3]);
	m_nodes[3]->addArc(m_nodes[2]);

	m_nodes[0]->addArc(m_nodes[4]);
	m_nodes[4]->addArc(m_nodes[0]);

	m_nodes[3]->addArc(m_nodes[5]);
	m_nodes[5]->addArc(m_nodes[3]);

	m_nodes[18]->addArc(m_nodes[5]);
	m_nodes[5]->addArc(m_nodes[18]);

	m_nodes[6]->addArc(m_nodes[7]);
	m_nodes[7]->addArc(m_nodes[6]);

	m_nodes[2]->addArc(m_nodes[7]);
	m_nodes[7]->addArc(m_nodes[2]);

	m_nodes[8]->addArc(m_nodes[7]);
	m_nodes[7]->addArc(m_nodes[8]);

	m_nodes[9]->addArc(m_nodes[10]);
	m_nodes[10]->addArc(m_nodes[9]);

	m_nodes[9]->addArc(m_nodes[1]);
	m_nodes[1]->addArc(m_nodes[9]);

	m_nodes[6]->addArc(m_nodes[10]);
	m_nodes[10]->addArc(m_nodes[6]);

	m_nodes[11]->addArc(m_nodes[10]);
	m_nodes[10]->addArc(m_nodes[11]);

	m_nodes[11]->addArc(m_nodes[12]);
	m_nodes[12]->addArc(m_nodes[11]);

	m_nodes[13]->addArc(m_nodes[12]);
	m_nodes[12]->addArc(m_nodes[13]);

	m_nodes[13]->addArc(m_nodes[8]);
	m_nodes[8]->addArc(m_nodes[13]);

	m_nodes[13]->addArc(m_nodes[14]);
	m_nodes[14]->addArc(m_nodes[13]);

	m_nodes[5]->addArc(m_nodes[14]);
	m_nodes[14]->addArc(m_nodes[5]);

	m_nodes[19]->addArc(m_nodes[14]);
	m_nodes[14]->addArc(m_nodes[18]);

	m_nodes[10]->addArc(m_nodes[15]);
	m_nodes[15]->addArc(m_nodes[10]);

	m_nodes[16]->addArc(m_nodes[15]);
	m_nodes[15]->addArc(m_nodes[16]);

	m_nodes[16]->addArc(m_nodes[17]);
	m_nodes[17]->addArc(m_nodes[16]);

	m_nodes[13]->addArc(m_nodes[17]);
	m_nodes[17]->addArc(m_nodes[13]);

	m_nodes[4]->addArc(m_nodes[19]);
	m_nodes[19]->addArc(m_nodes[4]);

	m_nodes[20]->addArc(m_nodes[19]);
	m_nodes[19]->addArc(m_nodes[20]);

	m_nodes[20]->addArc(m_nodes[21]);
	m_nodes[21]->addArc(m_nodes[20]);

	m_nodes[9]->addArc(m_nodes[21]);
	m_nodes[21]->addArc(m_nodes[9]);

	m_nodes[22]->addArc(m_nodes[21]);
	m_nodes[21]->addArc(m_nodes[22]);

	m_nodes[22]->addArc(m_nodes[16]);
	m_nodes[16]->addArc(m_nodes[22]);

	m_nodes[22]->addArc(m_nodes[23]);
	m_nodes[23]->addArc(m_nodes[22]);

	m_nodes[18]->addArc(m_nodes[23]);
	m_nodes[23]->addArc(m_nodes[18]);
}

//template<class NodeType, class ArcType>
//void AStar<NodeType, ArcType>::ucs(Node* pStart, Node* pDest, std::vector<Node *>& path) {
//	if (nullptr != pStart) {
//		priority_queue<Node*, std::vector<Node*>, NodeSearchCostComparer<NodeType, ArcType>> pq;
//
//		for (int i = 0; i < m_count; i++) {
//			m_pNodes[i]->setData(std::make_pair(m_pNodes[i]->data().first, 999999));
//		}
//
//		pStart->setData(std::make_pair(pStart->data().first, 0));
//
//		pq.push(pStart);
//		pStart->setMarked(true);
//
//		while (pq.size() != 0) {
//			// add all of the child nodes that have not been marked into the queue
//			auto iter = pq.top()->arcList().begin();
//			auto endIter = pq.top()->arcList().end();
//
//			for (; iter != endIter; iter++) {
//				int distC = pq.top()->data().second + iter->weight();
//
//				if (distC < (*iter).node()->data().second) {
//					(*iter).node()->setData(std::make_pair((*iter).node()->data().first, distC));
//					(*iter).node()->setPrevious(pq.top());
//				}
//
//				if ((*iter).node()->marked() == false) {
//					// mark the node and add it to the queue.
//					pq.push((*iter).node());
//					(*iter).node()->setMarked(true);
//				}
//
//				if ((*iter).node() == pDest) {
//					Node* temp = pDest; // sets a temporary holder node that is set to be the same as destination, and is used to go back to the initial node
//
//					if (distC <= (*iter).node()->data().second) {
//						if (path.empty() != true) {
//							path.clear();
//						}
//
//						while (temp != pStart) {
//							path.push_back(temp);
//							temp = temp->previous(); // goes back to the previous node until it reaches the initial node
//						}
//						path.push_back(pStart);
//					}
//				}
//			}
//			pq.pop();
//		}
//	}
//	for (int i = 0; i < m_count; i++) {
//		m_pNodes[i]->setMarked(false);
//	}
//}
//
//template<class NodeType, class ArcType>
//void AStar<NodeType, ArcType>::aStar(Node* pStart, Node* pDest, std::vector<Node *>& path) {
//	if (nullptr != pStart) {
//		// computes the actual cost of each path from pDest to pStart for the heuristic value
//		ucs(pDest, pStart, path);
//
//		for (int i = 0; i < m_count; i++) {
//			// calculates the heuristic of each node
//			m_pNodes[i]->heuristicCost = m_pNodes[i]->data().second * 0.9;
//			// sets g[v] to infinite
//			m_pNodes[i]->setData(std::make_pair(m_pNodes[i]->data().first, 99999));
//
//			//m_pNodes[i]->setData(std::make_pair(m_pNodes[i]->data().first, 99999));
//			//m_pNodes[i]->heuristicCost = ucs(pDest, m_pNodes[i], pVisitFunc, path) * 0.9;
//		}
//
//		// sets up priority queue that compares the total cost and heuristic cost
//		priority_queue<Node*, std::vector<Node*>, NodeSearchCostComparerAStar<NodeType, ArcType>> pq;
//
//		pStart->setData(std::make_pair(pStart->data().first, 0));
//
//		pq.push(pStart);
//		pStart->setMarked(true);
//
//		while (pq.size() != 0 && pq.top() != pDest) {
//			// add all of the child nodes that have not been marked into the queue
//			auto iter = pq.top()->arcList().begin();
//			auto endIter = pq.top()->arcList().end();
//
//			for (; iter != endIter; iter++) {
//				// adds the weight of the top of the queue to the weight of the the arc that it is looking at
//				int distC = pq.top()->data().second + iter->weight();
//
//				// if this is less than the node weight of the node it is looking at
//				if (distC < (*iter).node()->data().second) {
//					// sets the weight of the node to be distC
//					(*iter).node()->setData(std::make_pair((*iter).node()->data().first, distC));
//					// sets the top of the queue to be the previous node of this node
//					(*iter).node()->setPrevious(pq.top());
//				}
//
//				if ((*iter).node()->marked() == false) {
//					// mark the node and add it to the queue - puts priority on the shortest path
//					pq.push((*iter).node());
//					(*iter).node()->setMarked(true);
//				}
//
//				if ((*iter).node() == pDest) {
//					Node* temp = pDest; // sets a temporary holder node that is set to be the same as destination, and is used to go back to the initial node
//
//					if (distC <= (*iter).node()->data().second) {
//						if (path.empty() != true) {
//							path.clear();
//						}
//
//						while (temp != pStart) {
//							path.push_back(temp);
//							temp = temp->previous(); // goes back to the previous node until it reaches the initial node
//						}
//						path.push_back(pStart);
//					}
//				}
//			}
//			pq.pop();
//		}
//	}
//}