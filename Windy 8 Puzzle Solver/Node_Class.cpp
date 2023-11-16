#include "Node_Class.h"
//Default Constructor
Node::Node()
{
	manhattanDistance = 0;

	pathCost = 0;

	totalCost = 0;

	xPosition = 0;

	yPosition = 0;

	west = nullptr;

	north = nullptr;

	east = nullptr;

	south = nullptr;
}

//Constructor
Node::Node(char state[ROWS][COLUMNS])
{
	memcpy(this->state, state, sizeof(this->state));

	manhattanDistance = 0;

	pathCost = 0;

	totalCost = 0;

	yPosition = 0;

	xPosition = 0;

	west = nullptr;

	north = nullptr;

	east = nullptr;

	south = nullptr;
}

//Calculates the manhattan distance for an element of the Node in relation to an element of the goal Node.
void Node::ComputeManhattanDistance(Node goalState, int x, int y)
{
	char targetChar = goalState.state[x][y];

	int xPosition;
	int yPosition;

	SearchForElement(targetChar, xPosition, yPosition);

	if (targetChar == '-')
	{
		//Store the position of the placeholder character.
		this->xPosition = xPosition;
		this->yPosition = yPosition;
		return;
	}

	//Moving between rows, going North or South, cost 1 and 3, respectively.
	int xManhattanDistance = x - xPosition;

	if (xManhattanDistance > 0)
	{
		xManhattanDistance *= 3;
	}
	else
	{
		xManhattanDistance *= -1;
	}

	//Moving between columns, going East or West, has a cost of 2.
	int yManhattanDistance = (y - yPosition) * 2;

	if (yManhattanDistance < 0)
	{
		yManhattanDistance *= -1;
	}

	manhattanDistance += xManhattanDistance + yManhattanDistance;
}

//Computes the possible states of the Node and adds them to a priority queue.
void Node::ComputePossibleStates(Node goalState, int distanceTraveled, std::priority_queue<Node*, std::vector<Node*>, CompareNodes>& frontierSet)
{
	char placeHolder = '-';
	char tempElement;

	//Swaps west element with the placeholder and saves the result in a priority queue.
	if (yPosition != 0)
	{
		this->west = new Node(state);

		tempElement = west->state[xPosition][yPosition - 1];

		west->state[xPosition][yPosition] = tempElement;

		west->state[xPosition][yPosition - 1] = placeHolder;

		west->pathCost = 2 + distanceTraveled;
		west->ComputeTotalManhattanDistance(goalState);
		west->ComputeTotalCost();

		frontierSet.push(west);
	}

	//Swaps north element with the placeholder and saves the result in a priority queue.
	if (xPosition != 0)
	{
		this->north = new Node(state);

		tempElement = north->state[xPosition - 1][yPosition];

		north->state[xPosition][yPosition] = tempElement;

		north->state[xPosition - 1][yPosition] = placeHolder;

		north->pathCost = 3 + distanceTraveled;
		north->ComputeTotalManhattanDistance(goalState);
		north->ComputeTotalCost();

		frontierSet.push(north);
	}

	//Swaps east element with the placeholder and saves the result in a priority queue.
	if (yPosition != COLUMNS - 1)
	{
		this->east = new Node(state);

		tempElement = east->state[xPosition][yPosition + 1];

		east->state[xPosition][yPosition] = tempElement;

		east->state[xPosition][yPosition + 1] = placeHolder;

		east->pathCost = 2 + distanceTraveled;
		east->ComputeTotalManhattanDistance(goalState);
		east->ComputeTotalCost();

		frontierSet.push(east);
	}

	//Swaps south element with the placeholder and saves the result in a priority queue.
	if (xPosition != ROWS - 1)
	{
		this->south = new Node(state);

		tempElement = south->state[xPosition + 1][yPosition];

		south->state[xPosition][yPosition] = tempElement;

		south->state[xPosition + 1][yPosition] = placeHolder;

		south->pathCost = 1 + distanceTraveled;
		south->ComputeTotalManhattanDistance(goalState);
		south->ComputeTotalCost();

		frontierSet.push(south);
	}
}

//Calculates the total cost (Evaluation function: f(n) = g(n) + h(n)).
void Node::ComputeTotalCost()
{
	totalCost = pathCost + manhattanDistance;
}

//Calculates the total manhattan distance of the Node in relation to the goal Node.
void Node::ComputeTotalManhattanDistance(Node goalState)
{
	for (int i = 0; i < ROWS; i++)
	{
		for (int j = 0; j < COLUMNS; j++)
		{
			ComputeManhattanDistance(goalState, i, j);
		}
	}
}

//Returns the manhattan distance.
int Node::GetManhattanDistance() const
{
	return manhattanDistance;
}

//Returns the path cost.
int Node::GetPathCost() const
{
	return pathCost;
}

//Returns the total cost.
int Node::GetTotalCost() const
{
	return totalCost;
}

//Returns the x position.
int Node::GetXPosition() const
{
	return xPosition;
}

//Returns the y position.
int Node::GetYPosition() const
{
	return yPosition;
}

//Compares each element of two Nodes to check for equality.
bool operator ==(const Node& leftSide, const Node& rightSide)
{
	for (int i = 0; i < ROWS; i++)
	{
		for (int j = 0; j < COLUMNS; j++)
		{
			if (leftSide.state[i][j] != rightSide.state[i][j])
			{
				return false;
			}
		}
	}

	return true;
}

//Searches for a specified element in the 2D array and returns its row and column positions.
void Node::SearchForElement(char targetChar, int& x, int& y)
{
	for (x = 0; x < ROWS; x++)
	{
		for (y = 0; y < COLUMNS; y++)
		{
			if (state[x][y] == targetChar)
			{
				return;
			}
		}
	}

}

//Sets the value of the state.
void Node::SetState(char newState[ROWS][COLUMNS])
{
	memcpy(state, newState, sizeof(state));
}

//Prints specified characters based on the number of rows in an n x n array.
void Node::PrintChar(int rows, char charRows, char charColumns)
{
	std::cout << charColumns;

	for (int i = 0; i <= rows * 2; i++)
	{
		std::cout << charRows;
	}

	std::cout << charColumns << std::endl;
}

//Prints every element of the 2D array in a box and in an n x n format.
void Node::PrintState(int stateNumber)
{
	char boxRow = '-';
	char boxColumn = '|';

	//Prints the horizontal outline of the box.
	PrintChar(ROWS, boxRow, boxRow);

	//Prints all of the elements in the n x n array and the vertical outline of the box.
	for (int i = 0; i < ROWS; i++)
	{
		for (int j = 0; j < COLUMNS; j++)
		{
			if (j == 0)
			{
				std::cout << boxColumn << ' ';
			}

			std::cout << state[i][j] << ' ';

			if (j == COLUMNS - 1)
			{
				std::cout << boxColumn << ' ';
			}
		}

		std::cout << std::endl;
	}

	PrintChar(ROWS, boxRow, boxColumn);

	std::cout << boxColumn << this->GetPathCost() << boxColumn << this->GetManhattanDistance() << '\t' << boxColumn << std::endl;

	PrintChar(ROWS, boxRow, boxColumn);

	std::cout << boxColumn << "#" << stateNumber << '\t' << boxColumn << std::endl;

	PrintChar(ROWS, boxRow, boxRow);
}