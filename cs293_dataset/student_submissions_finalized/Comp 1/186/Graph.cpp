#ifndef GRAPH_BST_CPP
#define GRAPH_BST_CPP

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef GRAPH_BST_H
#include "Graph.h"
#endif

// Insert a new Node with a given value into BST
bool BST::insert(int value){
	TreeNode *newNode = new TreeNode(value);
	TreeNode *y = nullptr; 				// Using 2 pointers x and y to keep track
	TreeNode *x = root;	   				// of current Node and its parent
	while (x != nullptr){
		y = x;
		if (newNode->value < x->value)
			x = x->left;
		else
			x = x->right;
	}
	newNode->parent = y;
	if (y == nullptr)
		root = newNode;
	else if (newNode->value < y->value)
		y->left = newNode;
	else
		y->right = newNode;
	return true;
}

// Print full BST
void BST::printBST(const string &prefix, bool isLeft){
	if (root != nullptr){
		cout << prefix;

		cout << (isLeft ? "|--" : "|__");

		// print the value of the node
		cout << root->value << endl;
		TreeNode *curr = root;
		root = root->left;
		// enter the next tree level - left and right branch
		printBST(prefix + (isLeft ? "│   " : "    "), true);
		root = curr->right;
		printBST(prefix + (isLeft ? "│   " : "    "), false);
		root = curr;
	}
}

// Helper recursive function for modified DFS
void Graph::dfs(Node *node, BST *tree){
	static int count = 0;		// Helping variable for debugging to count the recursion level
	count++;
	if (node->visited == 2){	// return if node is visited twice
		return;
	}

	node->visited += 1;			// increment visited counter of the node
	tree->insert(node->value);	// insert node into tree

	if (node->visited == 1){	// Check for backedges inorder to find node as part of any cycle
		Node *temp = node;	
		while (temp != NULL){				// Iterate over all the parents of the node
			listOfObjects<Node *> *adjList = node->adjacency;
			while (adjList != NULL){	    // Check if there is a backedge
				if (adjList->object->value == temp->value && node->parent != temp){	
					temp->inCycle = true;
					Node *temp2 = node;
					while (temp2->value != temp->value){	// Set inCycle to true of all the nodes 
						temp2->inCycle = true;				// that are visited as parents if
						temp2 = temp2->parent;				// any upper backedge is found here 
					}
				}
				adjList = adjList->next;
			}
			temp = temp->parent;
		}
	}

	listOfObjects<Node *> *Adj = node->adjacency;		// iterator for adjacency list of cuurent Node
	while (Adj != nullptr){						// Apply modified dfs on adjacent nodes of cuurent Node
		if (Adj->object->visited < 2){			// Do this only if they are visited atmost twice
			if (Adj->object->visited == 0){		// Updating parent of the adjacent nodes on thier first visit
				Adj->object->parent = node;
			}
			if (Adj->object != node->parent){	// Recursive Modified dfs call only when it is not going reverse to parent again
				dfs(Adj->object, tree);
			}
		}
		Adj = Adj->next;
	}
	count--;
}

// Modified DFS Function
void Graph::modifiedDFS(){
	for (int i = 0; i < numNodes; i++){		// Loop over all nodes required to traverse each connected component
		if (nodes[i]->visited == 0){
			TreeNode *root = new TreeNode(nodes[i]->value);
			BST *tree = new BST();
			dfs(nodes[i], tree);
			trees[i] = tree;		// Store the connected component attained into trees array
			connectedComponents++;
		}
	}
	return;
}

// To Print all the required Results
void Graph::printResults(){
	for (int i = 0; i < numNodes; i++){		// Updating count of nodes visited ones or twice
		if (nodes[i]->visited == 1)
			visOne++;
		else if (nodes[i]->visited == 2)
			visTwice++;
	}
	for (int i = 0; i < numNodes; i++){		// Updating count of nodes in any cycle
		if (nodes[i]->inCycle)
			numNodesInCycle++;
	}
	cout << "No. of connected components: " << connectedComponents << endl;
	cout << "No. of nodes visited once: " << visOne << endl;
	cout << "No. of nodes visited twice: " << visTwice << endl;
	cout << "No. of nodes that are present in a cycle: " << numNodesInCycle << endl;
	for (int i = 0; i < numNodes; i++){				// Printing the BSTs of each Connected Component
		if (trees[i] != nullptr){
			trees[i]->printBST("", false);
			cout << endl;
		}
	}
	return;
}

#endif
