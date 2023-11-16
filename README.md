# Windy-8-Puzzle-Solver
The Windy 8 Puzzle Solver is a program developed to solve the Windy 8-Puzzle Problem using an A* Search Algorithm.

## Description
This program uses a priority queue for the frontier set and a hash table for the explored set. The prioritization is based on the evaluation function: 
`f(n) = g(n) + h(n)`, where nodes with lower costs are assigned higher priority. The primary objective of the program is to navigate from an initial state to the specified goal state, using an A* search algorithm to find the optimal path.

**Initial State:**
```
[2 8 3]
[6 7 4]
[1 5 -]
```

**Goal State:**
```
[1 2 3]
[8 - 4]
[7 6 5]
```

**Related Conditions:**
- Moving between rows, going North or South, cost 1 and 3, respectively.
- Moving between columns, going East or West, has a cost of 2.
