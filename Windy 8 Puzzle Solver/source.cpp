// Program Name: Windy 8 Puzzle Solver
// Author: woodsj1206 (https://github.com/woodsj1206)
// Description: Uses the A* Search Algorithm to find the solution to a Windy 8 Puzzle.
// Course: CIS 479-001
// Date Created: 1/22/22
// Last Modified: 1/28/22
#include <iostream>
#include "Node_Class.h"
#include "Hash_Table.h"

int main()
{
	//Sets the Goal State of the Windy Puzzle.
	char endState[ROWS][COLUMNS] = { {'1','2','3'},
									{'8','-','4'},
									{'7','6','5'} };
	const Node goalState(endState);

	//Sets the Initial State of the Windy Puzzle.
	char startState[ROWS][COLUMNS] = { {'2','8','3'},
									  {'6','7','4'},
									  {'1','5','-'} };
	Node* root = new Node(startState);

	root->ComputeTotalManhattanDistance(goalState);
	root->ComputeTotalCost();

	//Creates a priority queue for the frontier set. 
	//The lowest total cost has the highest priority.
	std::priority_queue <Node*, std::vector<Node*>, Node::CompareNodes> frontierSet;
	
	frontierSet.push(root);

	//Creates a Hash Table to store the explored states.
	HashTable<Node> exploredSet;

	//A* Search Algorithm
	Node* currentState = frontierSet.top();
	for (int i = 0, distanceTraveled = 0; currentState->GetManhattanDistance() > 0 && !frontierSet.empty();)
	{
		currentState = frontierSet.top();
		int key = currentState->GetManhattanDistance();

		//Check whether or not the current state has been explored.
		if (exploredSet.Search(key, *currentState))
		{
			frontierSet.pop();
		}
		else
		{
			//Add the current state to the explored set.
			exploredSet.Insert(key, *currentState);

			distanceTraveled = currentState->GetPathCost();

			//Print information about the current state.
			currentState->PrintState(++i);
			std::cout << std::endl;

			frontierSet.pop();

			//Expanding the Node and adding the results to the Frontier Set.
			currentState->ComputePossibleStates(goalState, distanceTraveled, frontierSet);
		}
	}
	
	return 0;
}