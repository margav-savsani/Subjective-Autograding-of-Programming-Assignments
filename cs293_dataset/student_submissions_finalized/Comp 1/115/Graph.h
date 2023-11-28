#ifndef GRAPH_BST_H
#define GRAPH_BST_H

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif
using namespace std;

class BSTNode
{
	public:
	int value;// value of the node of f=graph to be stored in BST
	BSTNode* left;//left BSTNode pointer
	BSTNode* right;//right BSTNode pointer
	BSTNode(int value)
	{
		this->value=value;//initialising with the given value
		left=NULL;//initialising as a leaf
		right=NULL;//initialising as a leaf
	}
};

class BST
{
	public:
	BSTNode* root;//root pointer of the BST
	BST()
	{
		root=NULL;
	}
	void add(int value)//nodes which has same value will be inserted in left subtree, predecessor of the copy node
	{
		BSTNode* D=root;
        root=D;
		if(root==NULL)
		{
			root= new BSTNode(value);
			return;
		}
		if(root->value<value)
		{
			if(root->right==NULL)
			{
				root->right= new BSTNode(value);
			}
			else
			{
				root=root->right;
				add(value);
			}
		}
		else
		{
			if(root->left==NULL)
			{
				root->left= new BSTNode(value);
			}
			else
			{
				root=root->left;
				add(value);
			}
		}
        root=D;
        return;
	}
	void printBST(const string& prefix, bool isLeft=false)//printing bst with already well known function
	{
		if(root != nullptr)
		{
			cout << prefix;
			cout << (isLeft ? "|--" : "|__" );
			cout << root->value << endl;
			BSTNode *curr = root;
			root = root->left;
			// enter the next tree level - left and right branch
			printBST( prefix + (isLeft ? "│   " : "    "), true);
			root = curr->right;
			printBST( prefix + (isLeft ? "│   " : "    "), false);
			root = curr;
		}
	}

};

class Node
{
	public:
	int value;
	int* adjacent_Nodes;// indices of the adjacent nodes
	int size;// no of adjacent nodes there for this node
	Node()
	{
		value=-1;// this value will be changed later
		size=0;
		adjacent_Nodes=NULL;
	}
	void start(int size)//intialising the adjacent nodes array with size as no of nodes in the graph to avoid usage of vectors
	{
		adjacent_Nodes= new int[size];
		return;
	}
	void Insert(int index)//inserting the adjacent nodes in the node
	{
		adjacent_Nodes[size]=index;
		size++;
	}
};

bool check(int a,Node b)//checking whether the a particular node is adjacent to the argument node or not
{
	for(int i=0;i<b.size;i++)
	{
		if(b.adjacent_Nodes[i]==a)
		{
			return true;
		}
	}
	return false;
}

class Graph
{
	int numNodes;// no of nodes in the graph
	int numEdges;// no of edges in the graph
	fstream graphFile;// edges to be stored in this file 
	Node *nodes;// all the nodes which have values from 0 to N-1, I will store them as 1 to N in BST, to avoid confusion
	BST* BST_Trees;// all the BST trees for each connected component
	int no_BST;// no of connected components
	int* stack;// stack array, if we travel on an edge, it will save the destination node index, if we backtrack then this will be removed
	int size_of_stack;// size of the above stack array
	int* freq;// this array stores the no of times each node is visited 
	bool* directions;// we have to travel every edge in one single direction
	bool* Nodes_in_cycle;// bool array, all will be initialised to 0, if we found an edge is there in a cycle, then that particular element value will be changed to 1/true.
	public:
	Graph(int nNodes, int nEdges, string gFileName)
	{
		Nodes_in_cycle=new bool[numNodes];
		directions=new bool[(nNodes)*(nNodes)];
		stack=new int[2*nNodes];// size is 2 times the no of nodes because every node can be there in the stack at most 2 times
		BST_Trees= new BST[nNodes];
		freq=new int[numNodes];
		no_BST=0;
		numNodes = nNodes;
		numEdges = nEdges;
		nodes=new Node[nNodes];
		graphFile.open(gFileName, ios::out);
		if (!graphFile.is_open())
		{
			cerr << "Couldn't open graph file " << gFileName << ". Aborting ..." << endl;
			exit(-1);
		}
		graphFile << numNodes << endl;
		graphFile << numEdges << endl;
		if (nodes == nullptr)
		{
			cerr << "Memory allocation failure." << endl;
			exit(-1);
		}
		for (int i = 0; i < numNodes; i++)
		{
			nodes[i].value = i;
		}
		srand(time(0));
		if(2*numEdges>numNodes*(numNodes-1))
		{
			cout<<"More no of edges are demanded"<<endl;
			return;
		}
		int countEdges = 0;
		int n1;
		int n2;
		for(int i=0;i<numNodes;i++)
		{
			nodes[i].start(numNodes);// initialising the adjacent nodes array of each node
		}
		while (countEdges < numEdges)
		{
			while(true)//checking whether an edge is repeated or not, if repeated then new edge will selected randomly
			{
				n1 = rand() % numNodes;
				n2 = rand() % numNodes;
				if(n1!=n2 && !check(n1,nodes[n2]))
				{
					nodes[n2].Insert(n1);//saving in the adjacent array of 1st node
					nodes[n1].Insert(n2);//saving in the adjacent array of 2nd node
					break;
				}
			}
			graphFile << n1+1 << " " << n2+1 << endl;
			countEdges++;
		}
	}

	~Graph()
	{
		if (graphFile.is_open())
		{
			graphFile.close();
		}
		delete[] nodes;
	}
	void modifiedDFS();
	void modifiedDFS_Basic(int start,int parent);// newly defined function for recursion
	void printResults();
};

#endif
