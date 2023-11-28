#ifndef GRAPH_CPP
#define GRAPH_CPP

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef GRAPH_H
#include "graph.h"
#endif

// Helper recursive function for DFS to start with a particular source Node
void Graph::dfs(Node *node){
	static int count = 0;		// Helping variable for count the recursion level
	count++;
	if (node->visited){			// return if node is visited already
		return;
	}
	node->level = count;		// Update the level of Node
	node->visited = true;		// Update visited boolean of the node
	listOfObjects<Node *> *Adj = node->adjacency;		// iterator for adjacency list of cuurent Node
	while (Adj != nullptr){								// Apply modified dfs on adjacent nodes of cuurent Node
		if (!Adj->object->visited){			
				Adj->object->parent = node;
				dfs(Adj->object);
		}
		Adj = Adj->next;
	}
	count--;
}

// DFS Traversal of the Graph
void Graph::DFS(){
	for (int i = 0; i < numNodes; i++){		// Loop over all nodes required to traverse each Node in DAG
		if (nodes[i]->visited == 0){
      		dfs(nodes[i]);
		}
	}
	int maxLevel = 1;			// Finding the maximum depth of graph levels
	for (int i = 0; i < numNodes; i++){
		if(nodes[i]->level > maxLevel){
			maxLevel =nodes[i]->level;
		}
	}
	if(maxLevel > 1){			// Updating Similarity relation of two Nodes
		for(int Level = 2; Level <= maxLevel; Level++){
			for(int i = 0; i < numNodes; i++){
				if(nodes[i]->level != Level) continue;
				else{
				 	if(nodes[i]->inAdjacency->next == nullptr){		// 3rd Condition of similarity
						similarMatrix[i][nodes[i]->inAdjacency->object->value - 1] = 1;
					}
				 	for(int j = i+1; j < numNodes; j++){			// 2nd Condition of similarity
				 		if(nodes[j]->level != Level) continue;
				 		else{
				 			listOfObjects<Node *> *node1Pred = nodes[i]->inAdjacency;	// Checking for 1st Node of pair
				 			bool failed = false, failed2 = false;
				 			while(node1Pred != nullptr){
				 				if(failed){
				 					break;
				 				}
				 				listOfObjects<Node *> *node2Pred = nodes[j]->inAdjacency;
				 				bool simFound = false;
				 				while(node2Pred != nullptr){ 
				 					if(similarMatrix[node1Pred->object->value - 1][node2Pred->object->value - 1] == 1){
				 						simFound = true;
				 						break;
				 					}
				 					node2Pred = node2Pred->next;
				 				}
				 				if(!simFound) failed = true;
				 				node1Pred = node1Pred->next;
				 			}

				 			listOfObjects<Node *> *node2_pred = nodes[j]->inAdjacency;	//Checking for 2nd Node of pair
				 			while(node2_pred != nullptr){
				 				if(failed2){
				 					break;
				 				}
				 				listOfObjects<Node *> *node1_pred = nodes[i]->inAdjacency;
				 				bool simFound = false;
				 				while(node1_pred != nullptr){
				 					if(similarMatrix[node2_pred->object->value - 1][node1_pred->object->value - 1] == 1){
				 						simFound = true;
				 						break;
				 					}
				 					node1_pred = node1_pred->next;
				 				}
								if(!simFound) failed2 = true;
				 				node2_pred = node2_pred->next;
				 			}

				 			if(!failed && !failed2){		// Making them a similar pair, if they didn't failed 2nd condition
								similarMatrix[i][j] = 1;
								similarMatrix[j][i] = 1;
				 			}
				 		}
				 	}
				}
			}
		}
	}
	return;
}

// To Print all the required Results
void Graph::printResults(){

  	outFile << "Source Nodes: ";		// Printing all the Source Nodes
  	for(int i = 0; i < numNodes; i++){
    	if(nodes[i]->inAdjacency == nullptr){
      		outFile << nodes[i]->value << " ";
    	}
  	}
  	outFile << endl << endl;

  	outFile << "Similar node pairs: ";	// Printing all the similar Node pairs
  	for(int i = 0; i < numNodes; i++){
		for(int j = 0; j < numNodes; j++){
			if(similarMatrix[i][j] == 1){	   
       			outFile << '(' << nodes[i]->value << ',' << nodes[j]->value << ')' <<  " ";
			}
		}
		
  	}
  	outFile << endl << endl;

	for(int i = 0; i < numNodes; i++){		// similar Matrix's reflexive & symmetric closure
		similarMatrix[i][i] = 1;
		for(int j = 0; j < numNodes; j++){
			if(similarMatrix[i][j] == 1){
				similarMatrix[j][i] = 1;
			}
		}
	}
	for(int k = 0; k < numNodes; k++){		// similar Matrix's transitive closure
		for(int i = 0; i < numNodes; i++){
			for(int j = 0; j < numNodes; j++){
					similarMatrix[i][j] = similarMatrix[i][j] || (similarMatrix[i][k] && similarMatrix[k][j]);
			}
		}
	}
	outFile << "Collapsed graph: " << endl << endl;
	int numVertices = 0;					// Finding new Edges using the similar Matrix Data
	int *newVertices = new int[numNodes];
	for(int i = 0; i < numNodes; i++){
		newVertices[i] = 0;
	}
	for(int i = 0; i < numNodes; i++){
		for(int j = numNodes-1; j >= 0; j--){
			if(similarMatrix[i][j] == 1){
				newVertices[j] = j+1;
				nodes[i]->value = j+1;
				break; 
			}
		}
	}
	for(int i = 0; i < numNodes; i++){
		if(newVertices[i] > 0){
			numVertices++;
		}
	}
	outFile << numVertices << ": ";
	for(int i = 0; i < numNodes; i++){
		if(newVertices[i] > 0){
			outFile << newVertices[i] << " ";
		}
	}
	outFile << endl;
	int finalEdges[numNodes*numNodes][2];	// Array to store all the final edges
	for(int i = 0; i < numNodes*numNodes; i++){
		for(int j = 0; j < 2; j++){
			finalEdges[i][j] = 0;
		}
	}
	for(int i = 0; i < numNodes; i++){
		listOfObjects<Node *> *adjList = nodes[i]->adjacency;
		while (adjList != NULL){	    
			if(nodes[i]->value != adjList->object->value){
				bool inserted = false;		// Bool to check if already inserted into array
				for(int j = 0; j < numNodes*numNodes; j++){
					if(finalEdges[j][0] == nodes[i]->value && finalEdges[j][1] == adjList->object->value){
						inserted = true;
						break;
					}
				}
				if(!inserted){
					for(int j = 0; j < numNodes*numNodes; j++){
						if(finalEdges[j][0] == 0 && finalEdges[j][1] == 0){
							finalEdges[j][0] = nodes[i]->value;
							finalEdges[j][1] = adjList->object->value;
							break;
						}
					}
				}
			}
        	adjList = adjList->next;
		}
	}
	for(int j = 0; j < numNodes*numNodes; j++){		// Printing all the edges of Transformed Graph
		if(finalEdges[j][0] == 0 && finalEdges[j][1] == 0) break;
		else{
			outFile << finalEdges[j][0] << " " << finalEdges[j][1] << endl;
		}
	}
	outFile << endl;
	return; 
}

#endif
