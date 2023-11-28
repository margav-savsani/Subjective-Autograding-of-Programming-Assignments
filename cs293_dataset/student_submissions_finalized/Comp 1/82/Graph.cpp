#ifndef GRAPH_BST_CPP
#define GRAPH_BST_CPP

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef GRAPH_BST_H
#include "Graph.h"
#endif

// Add code as appropriate for your implementation


// This is "THE" mmodified DFS that tells visits every node according to the modifications that we were asked to make.
// I used an array of parent pointers to 
void doDFS(Node* node, int visited [], BST* tree, Node* parent){
	tree->insert(node->value, tree->root);
	// cout << "!" << node->value << "!" << endl;
	visited[node->value - 1]++;
	adjacencyList<Node*>* curr = node->adjNodes;
	while(curr != nullptr){
		if(visited[curr->Node->value - 1] != 2 && curr->Node->value != parent[node->value - 1].value){
			parent[curr->Node->value - 1] = *node;
			doDFS(curr->Node, visited, tree, parent);
		}
		curr = curr->next;
	}
}

// This DFS is to find the number of nodes present in the cycle using the concept of completely visited node and partially visited node
// If a node is marked as 1 its partially visited, if marked as 2 its completely visited.
// Also if a node as visited when its partially visited then there exists a cycle and I just make an update in the boolean array by visiting the parents
// starting at that node and moving untill we read the node through which the backdge originates.

void newDFS(Node* node, int* visited, bool* inCycle, Node* parent){
	visited[node->value - 1] = 1;
	adjacencyList<Node*>* curr = node->adjNodes;

	while(curr != nullptr){
		if(visited[curr->Node->value - 1] == 0){
			parent[curr->Node->value - 1] = *node;
			newDFS(curr->Node, visited, inCycle, parent);
		}
		if(visited[curr->Node->value - 1] == 1 && parent[node->value - 1].value != curr->Node->value){
			Node cycle = *node;
			while(cycle.value != curr->Node->value){
				inCycle[cycle.value - 1] = true;
				cycle = parent[cycle.value - 1];
			}
			inCycle[curr->Node->value - 1] = true;
		}
		curr = curr->next;
	}
	visited[node->value - 1] = 2;
}

void Graph::modifiedDFS()
{
	int* visited = new int[numNodes];
	bool* inCycle = new bool[numNodes];
	for(int i=0; i<numNodes; i++){
		visited[i] = 0;
		inCycle[i] = 0;
	}
	int k = 0;

	// List of the connected component in the graph.
	adjacencyList<BST*>* treeList = nullptr;
	
	Node* src;
	while(k < numNodes){
		src = &nodes[k];
		BST* newTree = new BST();
		numConnectedComp++;
		Node* parent = new Node[numNodes];
		if(!treeList){
			treeList = new adjacencyList<BST*>(newTree);
			doDFS(src, visited, treeList->Node, parent);

			int* visit = new int[numNodes];
			for(int i=0; i<numNodes; i++){
				visit[i] = 0;
			}
			newDFS(src, visit, inCycle, parent);
		}
		else{
			adjacencyList<BST*>* currTree = treeList;
			while(currTree->next != nullptr){
				currTree = currTree->next;
			}
			currTree->next = new adjacencyList<BST*>(newTree);
			
			int* visited2 = new int[numNodes];
			for(int i=0; i<numNodes; i++){
				visited2[i] = 0;
			}
			doDFS(src, visited, currTree->next->Node, parent);

			int* visit = new int[numNodes];
			for(int i=0; i<numNodes; i++){
				visit[i] = 0;
			}

			newDFS(src, visit, inCycle, parent);
		}
		
		
		while(visited[k] != 0 && k < numNodes){
			k++;
		}
	}


	// storing all the required information.
	for(int i=0; i<numNodes; i++){
		if(visited[i] == 1) numNodes1++;
		else if(visited[i] == 2) numNodes2++;

		if(inCycle[i] == true){numNodeInCycle++;}
	}


	cout << "Number of connected components: " << numConnectedComp << endl;
	cout << "Number of Nodes visited once: " << numNodes1 << endl;
	cout << "Number of Nodes visited twice: " << numNodes2 << endl;
	cout << "Number of Nodes present in a cycle: " << numNodeInCycle << endl << endl;
	listOfTrees = treeList;


	return;
}


void Graph::printResults()
{
	adjacencyList<BST*>* currTree = listOfTrees;
	int i=1;
	// Printing the tree.
	while(currTree != nullptr){
		cout << "TREE " << i << endl;
		cout << "---------------------------------------" << endl;
		currTree->Node->printBST("");
		currTree = currTree->next;
		i++;
	}

	return;
}

#endif
