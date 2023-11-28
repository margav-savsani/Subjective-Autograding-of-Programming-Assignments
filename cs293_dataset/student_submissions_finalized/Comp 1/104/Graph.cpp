#ifndef GRAPH_BST_CPP
#define GRAPH_BST_CPP

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef GRAPH_BST_H
#include "Graph.h"
#endif

// Add code as appropriate for your implementation

// helper function to implement recursive DFS
void Graph::recDFS(int v, int *visited, int *parent1, int *parent2, int *DFSTree, bool *isInCycle, int *arrTime, int &time, int vp)
{
	// when we visit a node, insert it into BST
	trees->object->insert(v);

	// when we visit it first time, store the arrival time
	if (visited[v - 1] == 0)
	{
		arrTime[v - 1] = time;
		time++;
	}

	// increase the number of visited
	visited[v - 1] = visited[v - 1] + 1;

	listOfObjects<int> *adj = nodes[v - 1].adjacency;

	// iterate over the adjacency list
	while (adj != nullptr)
	{
		int adjVal = adj->object;

		// to detect the cycle and count number of nodes in that particular cycle
		// here I am only detecting "back-edge" and not "forward-edge"
		// we are encountering both of these edges as we are visiting each node twice
		// back edge must go to a node with a lesser arrival time
		if ((visited[adjVal - 1] == 2 || visited[adjVal - 1] == 1) && adjVal != DFSTree[v - 1] && DFSTree[adjVal - 1] != v && arrTime[adjVal - 1] < arrTime[v - 1])
		{
			int curr = v;

			// once we detect where back edge goes to
			// we will go up using parents until we meet the back-edge node
			// all the nodes we encounter in middle will be part of the cycle

			bool flag = false;

			while (curr != -1)
			{
				if (curr == adjVal)
				{
					flag = true;
					break;
				}
				else
				{
					curr = DFSTree[curr - 1];
				}
			}

			curr = v;

			if (flag)
			{

				while (true)
				{
					if (curr == adjVal)
					{
						isInCycle[curr - 1] = true;
						break;
					}
					if (curr == -1)
					{
						break;
					}

					isInCycle[curr - 1] = true;
					curr = DFSTree[curr - 1];
				}
			}
		}

		// if adjacent node is visited twice then don't do anything
		// if adjacent node is being visited in opposite direction then don't do it
		if (visited[adjVal - 1] == 2 || adjVal == vp || parent1[v - 1] == adjVal || parent2[v - 1] == adjVal)
		{
			adj = adj->next;
			continue;
		}

		// if adjacent node is being visited first time
		// then set the parent of that node
		// this will create a DFS tree same as in normal DFS
		if (visited[adjVal - 1] == 0 && DFSTree[adjVal - 1] == -1)
		{
			DFSTree[adjVal - 1] = v;
		}

		// setting of parent1
		if (parent1[adjVal - 1] == -1)
		{
			parent1[adjVal - 1] = v;
		}
		// setting of parent2
		else if (parent2[adjVal - 1] == -1)
		{
			parent2[adjVal - 1] = v;
		}

		// recursively call DFS on adjacent nodes
		recDFS(adjVal, visited, parent1, parent2, DFSTree, isInCycle, arrTime, time, v);

		// when backtracking, clear out the parents accordingly
		if (parent2[adjVal - 1] != -1)
		{
			parent2[adjVal - 1] = -1;
		}
		else if (parent1[adjVal - 1] != -1)
		{
			parent1[adjVal - 1] = -1;
		}

		adj = adj->next;
	}
}

void Graph::modifiedDFS()
{
	int *visited = new int[numNodes];	  // to store number of times each node is visited
	int *parent1 = new int[numNodes];	  // to store parent1
	int *parent2 = new int[numNodes];	  // to store parent2
	int *DFSTree = new int[numNodes];	  // to store parents of DFS tree
	bool *isInCycle = new bool[numNodes]; // to store if a node is in a cycle
	int *arrTime = new int[numNodes];	  // to store initial arrival time

	// initialize all the arrays
	for (int i = 0; i < numNodes; ++i)
	{
		visited[i] = 0;
		parent1[i] = -1;
		parent2[i] = -1;
		DFSTree[i] = -1;
		isInCycle[i] = false;
		arrTime[i] = -1;
	}

	// initializing the time
	int t = 0;

	// clearing BSTs if any
	trees = nullptr;

	// iterating over unvisited nodes
	// this is to find unconnected components
	for (int i = 0; i < numNodes; ++i)
	{
		if (visited[i] == 0)
		{
			// when new node is being visited
			// create a new BST for that subtree
			BST *newbst = new BST();
			insertAtHead(trees, newbst);

			// call recursive DFS on the node
			recDFS(i + 1, visited, parent1, parent2, DFSTree, isInCycle, arrTime, t, -1);
		}
	}

	// count number of connected components
	listOfObjects<BST *> *temp = trees;
	numConnectedComponents = 0;
	while (temp != nullptr)
	{
		numConnectedComponents++;
		temp = temp->next;
	}

	nodesOnce = 0;
	nodesTwice = 0;
	nodesInCycle = 0;

	// counting the required values
	for (int i = 0; i < numNodes; ++i)
	{
		if (visited[i] == 1)
		{
			nodesOnce++;
		}
		if (visited[i] == 2)
		{
			nodesTwice++;
		}

		if (isInCycle[i])
		{
			nodesInCycle++;
		}
	}
}

void Graph::printResults()
{
	cout << "No. of connected components: " << numConnectedComponents << endl;
	cout << "No. of nodes visited once: " << nodesOnce << endl;
	cout << "No. of nodes visited twice: " << nodesTwice << endl;
	cout << "No. of nodes that are present in a cycle: " << nodesInCycle << endl;

	listOfObjects<BST *> *temp = trees;

	while (temp != nullptr)
	{
		temp->object->printBST("");
		cout << endl
			 << endl;
		temp = temp->next;
	}
}

#endif
