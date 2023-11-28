#ifndef GRAPH_BST_CPP
#define GRAPH_BST_CPP

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef GRAPH_BST_H
#include "Graph.h"
#endif

void Graph::storeComp(adjacencyList<int>* &comp, int k, int visited[]){
	if(visited[k] == 1) return;
	visited[k] = 1;

	if(comp == nullptr){
		comp = new adjacencyList<int>(k + 1);
	}
	else{
		adjacencyList<int>* temp = comp;
		while(temp->next != nullptr){
				temp = temp->next;
		}
		temp->next = new adjacencyList<int>(k + 1);
	}

	for(int i=0; i<numNodes; i++){
		if(similarMatrix[k][i] == 1){
			storeComp(comp, i, visited);
		}
	}
}

bool findInList(adjacencyList<Pair*>* list, Pair* p){
	adjacencyList<Pair*>* curr = list;
	while(curr != nullptr){
		if(p->x == curr->Node->x && p->y == curr->Node->y) return true;
		curr = curr->next;
	}
	return false;
}

void Graph::collapseSimilarNodes(){
	//------------
	for(int i=0; i<numNodes; i++){
		for(int j=0; j<numNodes; j++){
			if(similarMatrix[i][j]){
				similarMatrix[j][i] = 1;
			}
		}
	}
	//-------------

	int k = 0;
	adjacencyList<adjacencyList<int>*>* allComp = nullptr;
	int visited[numNodes] = {0};
	while(k < numNodes){
		if(allComp == nullptr){
			allComp = new adjacencyList<adjacencyList<int>*>;
			allComp->Node = nullptr;
			storeComp(allComp->Node, k, visited);
		}
		else{
			adjacencyList<adjacencyList<int>*>* curr = allComp;
			while(curr->next != nullptr){
				curr = curr->next;
			}
			curr->next = new adjacencyList<adjacencyList<int>*>;
			curr->next->Node = nullptr;
			storeComp(curr->next->Node, k, visited);
		}

		while(visited[k] != 0 && k < numNodes){
				k++;
		}
	}

	adjacencyList<int>* finalTree = nullptr;
	int lenG = 0;
	adjacencyList<adjacencyList<int>*>* temp = allComp;
	while(temp != nullptr){
		adjacencyList<int>* currNode = temp->Node;
		int ma = 0;
		while(currNode != nullptr){
			ma = max(ma, currNode->Node);
			currNode = currNode->next;
		}
		if(finalTree == nullptr){
			finalTree = new adjacencyList<int>(ma);
		}
		else{
			adjacencyList<int>* curr = finalTree;
			while(curr->next != nullptr){
				curr = curr->next;
			}
			curr->next = new adjacencyList<int>(ma);
		}
		temp = temp->next;
		lenG++;
	}


	//------------------------
	graphFile << "Collapsed graph: " << endl << endl;
	//------------------------

	// RESULT 
	adjacencyList<int>* trav = finalTree;
	graphFile << lenG <<": "; 
	while(trav != nullptr){
		graphFile << trav->Node << " ";
		trav = trav->next;
	}
	graphFile << endl;


	//------------------------
	int replace[numNodes] = {0};
	temp = allComp;

	adjacencyList<int>* maxList = finalTree;
	while(temp != nullptr){
		adjacencyList<int>* currNode = temp->Node;
		while(currNode != nullptr){
			replace[currNode->Node - 1] = maxList->Node;
			currNode = currNode->next;
		}
		temp = temp->next;
		maxList = maxList->next;
	}

	// FINDING COLLPSED GRAPH EDGES
	adjacencyList<Pair*>* finalEdge = nullptr;
	adjacencyList<Pair*>* edgePair = input;
	while(edgePair != nullptr){
		if(replace[edgePair->Node->x - 1] != 0){
			edgePair->Node->x = replace[edgePair->Node->x - 1];
		}
		if(replace[edgePair->Node->y - 1] != 0){
			edgePair->Node->y = replace[edgePair->Node->y - 1];
		}
		if(edgePair->Node->x == edgePair->Node->y) {
			edgePair = edgePair->next;
			continue;
		}
		else{
			if(!findInList(finalEdge, edgePair->Node)){
				if(finalEdge == nullptr){
					finalEdge = new adjacencyList<Pair*>(edgePair->Node);
				}
				else{
					adjacencyList<Pair*>* currEdge = finalEdge;
					while(currEdge->next != nullptr){
						currEdge = currEdge->next;
					}
					currEdge->next = new adjacencyList<Pair*>(edgePair->Node);
				}
			}
		}
		edgePair = edgePair->next;
	}

	// PRINTING COLLPASED EDGES
	while(finalEdge != nullptr){
		graphFile << finalEdge->Node->x << " " << finalEdge->Node->y << endl;
		finalEdge = finalEdge->next;
	}



}

void Graph::getDepth(Node* node, int &depth, int visited[], int d){
	depth = max(depth, d);
	visited[node->value - 1] = 1;
	adjacencyList<Node*>* outNodes = node->adjOutNodes;
	while(outNodes != nullptr){
		if(visited[outNodes->Node->value - 1] == 0)
			getDepth(outNodes->Node, depth, visited, d + 1);
		outNodes = outNodes->next;
	}

}

bool Graph::condition2(int a, int b){
	adjacencyList<Node*>* inAdj1 = nodes[a - 1].adjInNodes;
	adjacencyList<Node*>* inAdj2 = nodes[b - 1].adjInNodes;

	bool chk = false;
	while(inAdj1 != nullptr){
		inAdj2 = nodes[b - 1].adjInNodes;
		while(inAdj2 != nullptr){
			if(similarMatrix[inAdj1->Node->value - 1][inAdj2->Node->value - 1] == 1) chk = true;
			inAdj2 = inAdj2->next;
		}
		if(!chk) return false;
		chk = false;
		inAdj1 = inAdj1->next;
	}
	chk = false;

	inAdj2 = nodes[b - 1].adjInNodes;
	inAdj1 = nodes[a - 1].adjInNodes;
	while(inAdj2 != nullptr){
		inAdj1 = nodes[a - 1].adjInNodes;
		while(inAdj1 != nullptr){
			if(similarMatrix[inAdj2->Node->value - 1][inAdj1->Node->value - 1] == 1) chk = true;
			inAdj1 = inAdj1->next;
		}
		if(!chk) return false;
		chk = false;
		inAdj2 = inAdj2->next;
	}
	return true;
}


int getLen(adjacencyList<Node*>* list){
	int len = 0;
	adjacencyList<Node*>* curr = list;
	while(curr!= nullptr){
		len++;
		curr = curr->next;
	}
	return len;
}

void Graph::mainDFS(Node* node, adjacencyList<int>* similar[], int visited[], int depth){
	visited[node->value - 1] = 1;
	if(getLen(nodes[node->value - 1].adjInNodes) == 1){
		similarMatrix[node->value - 1][nodes[node->value - 1].adjInNodes->Node->value - 1] = 1;
	}
	adjacencyList<Node*>* outNodes = node->adjOutNodes;
	while(outNodes != nullptr){
		if(visited[outNodes->Node->value - 1] == 0){
			adjacencyList<int>* temp = similar[depth];
			while(temp != nullptr){
				if(condition2(outNodes->Node->value, temp->Node)){
					similarMatrix[outNodes->Node->value - 1][temp->Node - 1] = 1;
					similarMatrix[temp->Node - 1][outNodes->Node->value - 1] = 1;
				}
				temp = temp->next;
			}
			if(similar[depth] == nullptr){
				similar[depth] = new adjacencyList<int>(outNodes->Node->value);
			}
			else{
				adjacencyList<int>* temp = similar[depth];
				while(temp->next != nullptr){
					temp = temp->next;
				}
				temp->next = new adjacencyList<int>(outNodes->Node->value);
			}
			mainDFS(outNodes->Node, similar, visited, depth + 1);
		}
		else{			
			adjacencyList<int>* temp = similar[depth];
			while(temp != nullptr){
				if(condition2(outNodes->Node->value, temp->Node)){
					similarMatrix[outNodes->Node->value - 1][temp->Node - 1] = 1;
					similarMatrix[temp->Node - 1][outNodes->Node->value - 1] = 1;
				}
				temp = temp->next;
			}
		}
		outNodes = outNodes->next;
	}

}


void Graph::fillSimilarNodes(int* srcNodes){
	int depth = 0;
	int visited[numNodes] = {0};

	for(int i=0; i<numSrcNodes; i++){
		getDepth(&nodes[srcNodes[i] - 1], depth, visited, 0);
		for(int j=0; j<numNodes; j++){
			visited[j] = 0;
		}
	}
	for(int i=0; i<numNodes; i++){
		visited[i] = 0;
	}
	adjacencyList<int>* similar[depth];
	for(int i=0; i<depth; i++){
		similar[i] = nullptr;
	}
	for(int i=0; i<numSrcNodes; i++){
		mainDFS(&nodes[srcNodes[i] - 1], similar, visited, 0);
	}

}


int* Graph::getSourceNodes()
{
	int temp[numNodes] = {0};

	for(int i=0; i<numNodes; i++){
		if(nodes[i].adjInNodes == nullptr){
			temp[i]++;
		}
	}
	int len = 0;
	for (int i = 0; i < numNodes; i++)
	{
		if (temp[i] == 1) len++;
	}
	int * srcNodes = new int[len];
	//
	numSrcNodes = len;
	//
	int j=0;
	for(int i=0; i < numNodes; i++){
		if(temp[i] == 1){
			srcNodes[j] = i + 1;
			j++;
		}
	}
	return srcNodes;
}


void Graph::printResults()
{
	graphFile << "Similar Node Pairs: ";
	for(int i=0; i<numNodes; i++){
		for(int j=0; j<numNodes; j++){
			if(similarMatrix[i][j])
				graphFile << "(" << i+1 << "," << j+1 <<  ")" << " ";
		}
	}
	graphFile << endl << endl;
	return;
}

#endif
