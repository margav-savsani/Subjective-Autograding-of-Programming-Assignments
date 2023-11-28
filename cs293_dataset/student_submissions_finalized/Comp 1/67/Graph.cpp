#ifndef GRAPH_BST_CPP
#define GRAPH_BST_CPP

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef GRAPH_BST_H
#include "Graph.h"
#endif

// Add code as appropriate for your implementation
void Graph::modifiedDFS() {
	for(int i=0;i<numNodes;i++){
		if(visitCount[i]!=0)	continue;
		// if(!isCycleFound)	nInCycle = 0;
		// visitCount[i]=1;
		// nInCycle = 1;
		BST* newTree = nullptr;
		// listOfObjects<int>* curr = nodes[i].adjacencyList;
		// while(curr){
		// 	doDFS(newTree,curr->object,visitCount);
		// 	curr = curr->next;
		// }
		nConnectedComponents++;
		doDFS(-1,i,visitCount,newTree);
		listOfObjects<BST*>* treeToAdd = new listOfObjects<BST*>(newTree);
		treeToAdd->next = trees;
		trees = treeToAdd;
	}
}
void Graph::doDFS(int caller,int idx,int* visitCount,BST* &tree){
	if(isInStack[idx]){
		isInCycle[idx]=true;
		if(caller!=-1)
		isInCycle[caller] = true;
	}
	if(visitCount[idx] == 1 && !isCycleFound){
		isCycleFound = true;
	}
	if(visitCount[idx]==2)	return;
	if(!isCycleFound)	nInCycle++;
	visitCount[idx]++;
	isInStack[idx] = true;
	if(tree)
		tree->insert(nodes[idx].value);
	else{
		tree = new BST(nodes[idx].value);
	}
	//
	listOfObjects<int>* removeNext = nodes[idx].adjacencyList;
	listOfObjects<int>* removed = nullptr;
	if(!removeNext){}
	else if(removeNext->object == caller){
		removed = removeNext;
		nodes[idx].adjacencyList = nodes[idx].adjacencyList->next;
	}else{
		while(removeNext -> next){
			if(removeNext ->next->object == caller){
				break;
			}
			removeNext = removeNext ->next;
		}
		if(removeNext ->next){
			removed = removeNext->next;
			removeNext->next = removeNext->next->next;
		}
	}
	listOfObjects<int>* curr = nodes[idx].adjacencyList;
	while(curr){
		// listOfObjects<int>* removeNext = nodes[curr->object].adjacencyList;
		// listOfObjects<int>* removed = nullptr;
		// if(removeNext->object == idx){
		// 	removed = removeNext;
		// 	nodes[curr->object].adjacencyList = nodes[curr->object].adjacencyList->next;
		// }else{
		// 	while(removeNext -> next){
		// 		if(removeNext ->next->object == idx){
		// 			break;
		// 		}
		// 		removeNext = removeNext ->next;
		// 	}
		// 	if(removeNext ->next){
		// 		removed = removeNext->next;
		// 		removeNext->next = removeNext->next->next;
		// 	}
		// }
		doDFS(idx,curr->object,visitCount,tree);
		// if(removed){
		// 	removed -> next = nodes[curr->object].adjacencyList;
		// 	nodes[curr->object].adjacencyList = removed;
		// }
		curr = curr->next;
	}
	if(removed){
		removed -> next = nodes[idx].adjacencyList;
		nodes[idx].adjacencyList = removed;
	}
	isInStack[idx] = false;
}

void Graph::printResults() {
	cout<<"No. of connected components: "<<nConnectedComponents<<endl;
	int n1=0,n2=0;
	nInCycle = 0;
	for(int i=0;i<numNodes;i++){
		if(visitCount[i]==1)	n1++;
		if(visitCount[i]==2)	n2++;
		if(isInCycle[i])	nInCycle ++;
	}
	cout<<"No. of nodes visited once: "<<n1<<endl<<"No. of nodes visited twice: "<<n2<<endl;
	cout<<"No.of nodes in a cycle: "<<nInCycle<<endl;
	listOfObjects<BST*>* currTree = trees;
	int i=1;
	while(currTree){
		cout<<"BST for Component "<<i<<" "<<endl;
		currTree->object->printBST("");
		currTree = currTree->next;
		i++;
	}
}

#endif
