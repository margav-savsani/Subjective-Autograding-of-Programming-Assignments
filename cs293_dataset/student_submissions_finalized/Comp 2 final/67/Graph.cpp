#ifndef GRAPH_CPP
#define GRAPH_CPP

#include "std_headers.h"
#include "Graph.h"
using namespace std;

Graph::Graph(int n){
	this->n = n;
	adjacencyMatrix = new bool*[n];
	classRepresentative = new int[n];
	similarityMatrix = new bool*[n];
	sourceNodes = new bool[n];
	for(int i=0;i<n;i++){
		adjacencyMatrix[i] = new bool[n];
		similarityMatrix[i] = new bool[n];
		sourceNodes[i] = true; // initialize all sourceNodes as true as no edges for now
		classRepresentative[i] = i; // initialize classRepresentative such that there are no collapsed nodes
		for(int j=0;j<n;j++){ // initialize the adjacencyMatrix and similarityMatrix by false
			adjacencyMatrix[i][j] = false;
			similarityMatrix[i][j] = false;
		}
	}
}

Graph::~Graph(){ // Free the memory allocated using 'new'
	delete sourceNodes;
	for(int i=0;i<n;i++){
		delete adjacencyMatrix[i];
		delete similarityMatrix[i];
	}
	delete adjacencyMatrix;
	delete similarityMatrix;
	delete classRepresentative;
}

void Graph::makeGraph(){
	getEdges();
	getSourceNodes();
	getSimilarNodes();
	for(int i=0;i<n;i++){
		if(classRepresentative[i] == i)
			updateCollapsedNodesInfo(i,i); // Update the collapsed nodes data if not done till now.
	}
}

void Graph::getSourceNodes(){
	for(int i=0;i<n;i++){
		for(int j=0;j<n;j++){
			if(adjacencyMatrix[j][i]){ // If this happens, the source node condition fails
				sourceNodes[i] = false;
				break;
			}
		}
	}
}

void Graph::getEdges(){
	int n1,n2;
	while(true){
		cin>>n1>>n2; // Input the edges
		if(n1==-1 && n2==-1)	return; // Edges input ends
		n1--;n2--;
		if(n1<0 || n2<0 || n1>=n || n2>=n){ // Invalid input
			cout<<"Invalid Input in Adjacent Nodes"<<endl;
			continue;
		}
		adjacencyMatrix[n1][n2] = true;
	}
}

void Graph::getSimilarNodesInput(){
	int n1,n2;
	while(true){
		cin>>n1>>n2; // Input the similar nodes pair
		if(n1==-1 && n2==-1)	break;
		n1--;n2--;
		if(n1<0 || n2<0 || n1>=n || n2>=n){
			cout<<"Invalid Input in Similar Nodes"<<endl;
		}
		if(sourceNodes[n1] && sourceNodes[n2]) // Update only if n1 and n2 are source nodes as mentioned in condition 1
			similarityMatrix[n1][n2] = true;
	}
}

void Graph::getSimilarNodes(){
	getSimilarNodesInput();
	// Get similar nodes by condition 3
	for(int i=0;i<n;i++){
		int countSources = 0;
		int source = -1;
		for(int j=0;j<n;j++){
			if(adjacencyMatrix[j][i]){
				countSources++;
				source = j;
			}
		}
		if(countSources == 1)	similarityMatrix[i][source] = true; // source is only source for i
	}
	//Get similar nodes by condition 2
	for(int i=0;i<n;i++){
		if(sourceNodes[i])	continue;
		for(int j=i+1;j<n;j++){
			if(sourceNodes[j])	continue;
			// If i,j are non-source nodes, checkForSimilarity is used. Check for both
			if(checkForSimilarity(i,j))	similarityMatrix[i][j] = true;
			if(checkForSimilarity(j,i))	similarityMatrix[j][i] = true;
		}
	}
}

bool Graph::checkForSimilarity(int n1,int n2){
	if(similarityMatrix[n1][n2])	return true; // If already updated to true in similarityMatrix, return true
	if(sourceNodes[n1] || sourceNodes[n2])	return false; // If any is source node, Condition 2 can't do anything. The function assumes that Condition 1 and 3 are already checked.
	bool similar = true;
	for(int m1=0;m1<n;m1++){ // Check if for every source m1 of n1, there is a source m2 of n2 where m1,m2 are similar
		if(adjacencyMatrix[m1][n1]){
			bool found = false;
			for(int m2=0;m2<n;m2++){
				if(adjacencyMatrix[m2][n2]){
					if(checkForSimilarity(m1,m2)){ // If m1,m2 are similar, for m1, m2 is there, continue to check for other sources of n1
						found = true;
						break;
					}
				}
			}
			if(!found){ // As nothing found source m1 of n, n1,n2 are not similar.
				similar = false;
				break;
			}
		}
	}

	if(!similar)	return false;
	
	for(int m1=0;m1<n;m1++){// Check the other way, i.e. for every source m1 of n2, there is a source m2 of n1 where m1,m2 are similar.
		if(adjacencyMatrix[m1][n2]){
			bool found = false;
			for(int m2=0;m2<n;m2++){
				if(adjacencyMatrix[m2][n1]){
					if(checkForSimilarity(m1,m2)){ // If m1, m2 are similar, there is a similar node for m1
						found = true;
						break;
					}
				}
			}
			if(!found){// Source m1 of n2 has no corresponding similar source of n1
				similar = false;
				break;
			}
		}
	}
	if(similar){ // As condition 2 is symmetric, update both before returning.
		similarityMatrix[n1][n2] = true;
		similarityMatrix[n2][n1] = true;
		return true;
	}
	return false;
}

void Graph::printDetails(){
	// Print the list of source nodes
	cout<<"Source nodes: ";
	for(int i=0;i<n;i++){
		if(sourceNodes[i])	cout<<i+1<<" ";
	}
	cout<<"\n\n";
	// Print the list of similar node pairs
	cout<<"Similar node pairs: ";
	for(int i=0;i<n;i++){
		for(int j=0;j<n;j++){
			if(similarityMatrix[i][j]){
				cout<<"("<<i+1<<", "<<j+1<<") ";
			}
		}
	}
	cout<<"\n\n";
	int nCollapsedNodes=0; // Count the number of nodes in collapsed graph
	for(int i=0;i<n;i++){
		if(classRepresentative[i]==i)	nCollapsedNodes++; // classRepresentative[i] == i implies that i is the largest in it's class
	}
	// Print the number of collapsed nodes
	cout<<nCollapsedNodes<<" : ";
	for(int i=0;i<n;i++){
		if(classRepresentative[i]==i)	cout<<i+1<<" ";
	}
	cout<<endl;
	printCollapsedEdges(); // To print all collapsed edges
}

void Graph::updateCollapsedNodesInfo(int idx,int repr){
	static int recursionLevel = -1;
 	static bool** symmSimMat; // Symmetric Extension of similarityMatrix
	if(recursionLevel == -1){ // initialize symmSimMat
		symmSimMat = new bool*[n];
		for(int i=0;i<n;i++){
			symmSimMat[i] = new bool[n];
			for(int j=0;j<n;j++){
				if(similarityMatrix[i][j] || similarityMatrix[j][i]) symmSimMat[i][j] = true;
				else	symmSimMat[i][j] = false;
			}
		}
	}
	recursionLevel++;
	for(int i=repr-1;i>=0;i--){ // For all nodes smaller than repr, check if similar
		if(symmSimMat[idx][i] && classRepresentative[i] != repr){ // if not yet checked for collapse and symm to idx, updateCollapsedNodesInfo for it. This would work similar to recursive DFS.
			classRepresentative[i] = repr;
			updateCollapsedNodesInfo(i,repr);
		}
	}
	if(recursionLevel==0){ // Delete the symmSimMat
		for(int i=0;i<n;i++){
			delete symmSimMat[i];
		}
		delete symmSimMat;
	}
	recursionLevel--;
}

void Graph::printCollapsedEdges(){
	bool** collapsedGraphAdjacencyList = new bool*[n]; // Adjacency List for collapsed Graph
	for(int i=0;i<n;i++){
		collapsedGraphAdjacencyList[i] = new bool[n];
		for(int j=0;j<n;j++){
			collapsedGraphAdjacencyList[i][j] = false;
		}
	}
	for(int i=0;i<n;i++){
		for(int j=0;j<n;j++){
			if(adjacencyMatrix[i][j]){ // Update in collapsed graph
				collapsedGraphAdjacencyList[classRepresentative[i]][classRepresentative[j]] = true;
			}
		}
	}
	for(int i=0;i<n;i++){
		for(int j=0;j<n;j++){
			if(collapsedGraphAdjacencyList[i][j] && i!=j){ // Not an edge if i==j
				cout<<i+1<<" "<<j+1<<endl;
			}
		}
	}
	for(int i=0;i<n;i++){
		delete collapsedGraphAdjacencyList[i];
	}
	delete collapsedGraphAdjacencyList;
}

#endif
