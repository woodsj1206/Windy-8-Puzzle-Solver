#pragma once
#include <iostream>
#include <queue>
#include <vector>
#include <functional>
const int ROWS = 3;
const int COLUMNS = 3;

class Node
{
private:
	char state[ROWS][COLUMNS] = {NULL};
	int manhattanDistance;
	int pathCost;
	int totalCost;

	int xPosition;
	int yPosition;

	Node* west;
	Node* north;
	Node* east;
	Node* south;

public:
	//Comparing the total cost of two pointers to a Node for the priority queue.
	struct CompareNodes : public std::binary_function<Node*, Node*, bool>
	{
		bool operator()(const Node* rightSide, const Node* leftSide) const
		{
			return leftSide->GetTotalCost() < rightSide->GetTotalCost();
		}
	};

	Node();

	Node(char state[ROWS][COLUMNS]);

	void ComputeManhattanDistance(Node goalState, int x, int y);

	void ComputePossibleStates(Node goalState, int distanceTraveled, std::priority_queue<Node*, std::vector<Node*>, CompareNodes>& frontierSet);

	void ComputeTotalCost();

	void ComputeTotalManhattanDistance(Node goalState);

	int GetManhattanDistance() const;

	int GetPathCost() const;

	int GetTotalCost() const;

	int GetYPosition() const;

	int GetXPosition() const;

	friend bool operator ==(const Node& leftSide, const Node& rightSide);

	void PrintChar(int rows = ROWS, char charRows = '-', char charColumns = '-');

	void PrintState(int stateNumber = 0);

	void SearchForElement(char targetChar, int& x, int& y);

	void SetState(char newState[ROWS][COLUMNS]);
};