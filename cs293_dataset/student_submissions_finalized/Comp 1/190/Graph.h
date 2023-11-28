#ifndef GRAPH_BST_H
#define GRAPH_BST_H

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#include <bits/stdc++.h>
using namespace std;

// ===============================================================================================================================================

struct TreeNode{
	int NodeValue;
	TreeNode *left;	
	TreeNode *right;
	TreeNode *parent;

	TreeNode() : NodeValue(0), left(nullptr), right(nullptr), parent(nullptr) {}
	TreeNode(int jNodeValue) : NodeValue(jNodeValue), left(nullptr), right(nullptr) {}
};

// ===============================================================================================================================================

class BST{
	TreeNode *root;
public:
	
	// '''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''

	BST()
	{
		root = NULL;
	}

	// '''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''

	BST(TreeNode *root)
	{
		this->root = root;
	}

	// '''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''

	bool insert(int NodeValue)
	{
		// if (find(NodeValue))
		// 	return false;

		if (root == NULL)
		{
			root = new TreeNode();
			root->NodeValue = NodeValue;
			return true;
		}

		TreeNode *z = new TreeNode();
		z->NodeValue = NodeValue;

		TreeNode *y = new TreeNode();
		y = NULL;
		TreeNode *x = new TreeNode();
		x = root;

		while (x != NULL)
		{
			y = x;
			if (z->NodeValue < x->NodeValue)
				x = x->left;
			else
				x = x->right;
		}

		z->parent = y;
		if (y == NULL)
			root = z;
		else if (z->NodeValue < y->NodeValue)
			y->left = z;
		else
			y->right = z;
		return true;
	}

	// '''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''

	bool find(int NodeValue)
	{
		TreeNode *x = root;
		while (x != NULL && x->NodeValue != NodeValue)
		{
			if (NodeValue < x->NodeValue)
				x = x->left;
			else
				x = x->right;
		}
		if (x == NULL)
			return false;

		return true;
	}

	// '''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''

	bool remove(int NodeValue)
	{
		TreeNode *z = root;
		while (z != NULL && z->NodeValue != NodeValue)
		{
			if (NodeValue < z->NodeValue)
				z = z->left;
			else
				z = z->right;
		}

		if (z == NULL)
			return false;

		TreeNode *y = new TreeNode();
		TreeNode *x = new TreeNode();

		if (z->left == NULL || z->right == NULL)
			y = z;
		else
			y = TreeSuccessor(z);

		if (y->left != NULL)
			x = y->left;
		else
			x = y->right;

		if (x != NULL)
			x->parent = y->parent;

		if (y->parent == NULL)
			root = x;
		else if (y == y->parent->left)
			y->parent->left = x;
		else
			y->parent->right = x;

		if (y != z)
			*z = *y; // Copying all values of y into z

		return true;
	}

	// '''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''

	void printBST(const string &prefix, bool isLeft = false)
	{
		if (root != nullptr)
		{
			cout << prefix;
			cout << (isLeft ? "|--" : "|__");
			cout << root->NodeValue << endl;
			TreeNode *curr = root;
			root = root->left;
			printBST(prefix + (isLeft ? "│   " : "    "), true);
			root = curr->right;
			printBST(prefix + (isLeft ? "│   " : "    "), false);
			root = curr;
		}
	}

	// '''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''

	TreeNode *TreeSuccessor(TreeNode *x)
	{
		if (x->right != NULL)
			TreeMinimum(x->right);
		TreeNode *y;
		y = x->parent;
		while (y != NULL && x == y->right)
		{
			x = y;
			y = y->parent;
		}
		return y;
	}

	// '''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''

	TreeNode *TreeMinimum(TreeNode *x)
	{
		while (x->left != NULL)
			x = x->left;
		return x;
	}

};



// ===============================================================================================================================================

class Node
{

public:
	int value;
	vector<pair<int,bool>> adjNodes;

	// '''''''''''''''''''''''''''''''''''''''''''''

	Node(){
		value = -1;
	}
	
	// '''''''''''''''''''''''''''''''''''''''''''''

	void add_Edge_With(int n){
		// adjNodes.push_back(n);
		adjNodes.push_back(make_pair(n,true));
		sort(adjNodes.begin(), adjNodes.end()); // FOR TESTING CODE
		return;
	}

	// '''''''''''''''''''''''''''''''''''''''''''''

	int getValue(){
		return value;
	}

	// '''''''''''''''''''''''''''''''''''''''''''''

	bool isPresent(int n){
		// if(find(adjNodes.begin(), adjNodes.end(), n) != adjNodes.end())
		if(find(adjNodes.begin(), adjNodes.end(), make_pair(n,true)) != adjNodes.end())
			return true;
		else return false;
	}

	// '''''''''''''''''''''''''''''''''''''''''''''

	int degree(){
		return adjNodes.size();
	}
};

// ===============================================================================================================================================

class Graph
{
	int numNodes;
	int numEdges;
	fstream graphFile;

	Node *nodes;
	int* no_of_times_discovered;
	bool* is_Present_in_Cycle;
	int no_of_connected_components;
	vector<BST> Trees;

	// ''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''

public:
	Graph(int nNodes, int nEdges, string gFileName)
	{
		numNodes = nNodes;
		numEdges = nEdges;
		graphFile.open(gFileName, ios::out);
		if (!graphFile.is_open())
		{
			cerr << "Couldn't open graph file " << gFileName << ". Aborting ..." << endl;
			exit(-1);
		}

		graphFile << numNodes << endl;
		graphFile << numEdges << endl;

		nodes = new Node[numNodes];
		no_of_times_discovered = new int[numNodes];
		is_Present_in_Cycle = new bool[numNodes];

		if (nodes == nullptr)
		{
			cerr << "Memory allocation failure." << endl;
			exit(-1);
		}

		for (int i = 0; i < numNodes; i++)
			nodes[i].value = i + 1;

		srand(time(0));
		int n1, n2;
		int countEdges = 0;
		while (countEdges < numEdges)
		{
			do{
				n1 = rand() % numNodes;
				n2 = rand() % numNodes;
			} while (n1 == n2);

			if (addEdge(n1, n2)){
				countEdges++;
				graphFile << n1 + 1 << " " << n2 + 1 << endl;
			}
		}

	}

	// ''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
	
	void modifiedDFS();

	// ''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''

	bool is_present_edge(int u, int v){
		
		for(int i=0; i<nodes[u].adjNodes.size(); i++){
			if(v == nodes[u].adjNodes[i].first && nodes[u].adjNodes[i].second == true) 
				return true;
		}
		return false;
	}

	// ''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''

	void deactivate_edge(int v, int u){
		for(int i=0; i<nodes[v].adjNodes.size(); i++){
			if(u == nodes[v].adjNodes[i].first) 
				nodes[v].adjNodes[i].second = false;
		}
		return;
	}

	// ''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''

	bool addEdge(int n1, int n2){
		if(n1 == n2)
			return false;

		if(is_present_edge(n1,n2))
			return false;
		nodes[n1].add_Edge_With(n2);
		nodes[n2].add_Edge_With(n1);
		return true;
	}

	// ''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''

	void simpleDFS(){
		static bool* discovered = new bool[numNodes];
		static bool* processed = new bool[numNodes];
		static int* pr= new int[numNodes];
		static int time = 0;
		static int currNode;

		if(time == 0){

			time++;
			for(int i=0; i<numNodes; i++){
				discovered[i] = false;
				processed[i] = false;
				pr[i] = -1;
				is_Present_in_Cycle[i] = false;
			}

			no_of_connected_components = 0;
			for(int i=0; i<numNodes; i++){
				if(!discovered[i]){
					no_of_connected_components++;
					currNode = i;

					simpleDFS();
				}
			}

			return;
		}

		// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

		int u = currNode;
		time++;
		discovered[u] = true;
		for(int i=0; i<nodes[u].degree(); i++){
			int v = nodes[u].adjNodes[i].first;

			if(discovered[v] && !processed[v] && pr[u] != v){
				int a = u;
				while(a != v && a != -1){
					is_Present_in_Cycle[a] = true;
					a = pr[a];
				}
				is_Present_in_Cycle[v] = true;
			}

			if(!discovered[v]){
				pr[v] = u;
				currNode = v;
				simpleDFS();
			}
		}
		time++;
		processed[u] = true;
		return;
	}

	// ''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''

	void printResults();

	// ''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''

	void printTrees(){
		for(int i=0; i<Trees.size(); i++){
			cout << "'''''''''''''''''\n";
			Trees[i].printBST("");
		}
	}

	// ''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''

	void print_nodes_visited(int t){
		cout << "Number of nodes visited ";
		(t == 1)? cout << "once: " : cout << "twice: ";
		int num = 0;
		for(int i=0; i<numNodes; i++)
			if(no_of_times_discovered[i] == t)
				num++;
		
		if(num == 0){
			cout << num << endl;
			return;
		}
		else{
			cout << num;
			int k=0;
			for(int i=0; i<numNodes; i++){
				if(no_of_times_discovered[i] == t){
					if(k == 0) cout << " (" << i+1;
					else cout << ", " << i+1;
					k++;
				}	
			}
			cout << ")" << endl;
		}
	}

	// ''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''

	void print_nodes_in_cycle(){
		cout << "Number of nodes in cycle: ";
		int num = 0;
		for(int i=0; i<numNodes; i++)
			if(is_Present_in_Cycle[i])
				num++;
		
		if(num == 0){
			cout << num << endl;
			return;
		}
		else{
			cout << num;
			int k=0;
			for(int i=0; i<numNodes; i++){
				if(is_Present_in_Cycle[i]){
					if(k == 0) cout << " (" << i+1;
					else cout << ", " << i+1;
					k++;
				}	
			}
			cout << ")" << endl;
		}
	}

	// ''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
	
	~Graph()
	{
		if (graphFile.is_open())
			graphFile.close();
		delete[] nodes;
	}

};

// ===============================================================================================================================================

#endif
