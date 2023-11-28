#ifndef GRAPH_H
#define GRAPH_H
#include "std_headers.h"

class Graph{
	int n; // Number of nodes in graph
	bool** adjacencyMatrix; // Adjacency matrix of graph
	bool** similarityMatrix; // i,j are similar if similarityMatrix[i][j] == true
	bool* sourceNodes; // Boolean array to store the source nodes
	int* classRepresentative; // Array to store the biggest node in collapsed graph

	void getEdges(); // Read edges from stdin
	void getSimilarNodes(); // update the similarityMatrix
	void getSimilarNodesInput(); // Read similar nodes pairs from stdin
	void getSourceNodes(); // Function to update sourceNodes
	bool checkForSimilarity(int i,int j); // checks if nodes i,j are similar (Used after updating similarityMatrix according to condition 1 and 3). This function either checks similarityMatrix or checks if condition 2 is satisfied.

	// Consider the similarity as an undirected graph. The transitive, symmetric closure to find collapsed nodes is represented by a connected component in the fraph
	// This function does a DFS on nodes by using symmetric extension of similarityMatrix as the adjacency Matrix and repr represents the highest value in the connected component. 
	// repr being largest is ensured by calling this function in a for loop with decreasing values of i
	// Updates the classRepresentative array values using DFS. After the function returns, all the nodes in class represented by repr have correct value in the array.
	void updateCollapsedNodesInfo(int idx,int repr); 
	void printCollapsedEdges(); // Prints the collapsed edges to stdout

	public:
	Graph(int n); // Constructor object. Takes number of Nodes as arguments
	~Graph(); // Destructor Object
	void makeGraph(); // makes graph by setting all the variables correctly. First, it reads the list of edges, then it sets sourceNodes array, followed by similarity matrix. At last, it updates the collapsed nodes data in classRepresentative array.
	void printDetails(); // Prints the required details in required format.
};

#endif
