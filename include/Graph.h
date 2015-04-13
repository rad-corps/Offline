#pragma once

#include "Node.h"
#include "Edge.h"
#include <vector>
#include <string>
#include "Vector.h"
#include <stack>

class Graph
{
public:
	Graph(void);
	~Graph(void);
	std::vector<Node*> GraphData() const;
	std::vector<Node*> AStar();

	int CalcH(Node* from_, Node* to_);
	//Node* AddNode(NodeData data_);
	Node* AddNode(Vector2 data_);
	Node* FindNode(Vector2 pos_, int tollerance_);
	std::vector<Node*> FindNodes(Vector2 pos_, int tollerance_);
	void SetHilightedNodes(std::vector<Node*> highlitedNodes_);
	void Clear();
	void ClearStartAndEndNodes();
	bool NodeWithin(Vector2 pos_, int tollerance_);

	void RemoveNode(Node* node_);
	void RemoveNodeIf(Vector2 pos_, int tollerance_);
	void SetStartNode(Vector2 pos_, int tollerance_);
	void SetEndNode(Vector2 pos_, int tollerance_);

	Node* StartNode() const;
	Node* EndNode() const;

	Node* operator[](int index_);
	//void ConnectNodes(Node* nodeA_, Node* nodeB_, int cost_, bool bidirectional_);
	void ConnectNodes(Node* nodeA_, Node* nodeB_, int cost_, bool bidirectional_);
	void ConnectCloseNodes(Node* nodeA_, int distance_, bool bidirectional_);
	int size();

	//void DFS_Step();
	//void BFS_Step();
	void PrepareForSearch(); //clears open and closed lists, searchStack, gScores etc.
	//std::vector<Node*> FindPathDijkstras();
	//void Dijkstra_Step();

	std::string ToString();

private:
	//std::vector<Node*> ReconstructPath();

	//todo comment out below 3
	Node* startNode;
	Node* endNode;
	Node* currentNode;

	std::vector<Node*> graphData;
	std::vector<Node*> highlitedNodes;
	//std::vector<Edge> edges;
	static int nodeID;

	std::vector<Node*> searchStack; //used for BFS and DFS
	std::vector<Node*> openList; //used for dijkstra's 
	std::vector<Node*> closedList; //used for dijkstra's 
	std::vector<Node*> path;
};