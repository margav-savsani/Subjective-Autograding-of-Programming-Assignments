#ifndef GRAPH_BST_CPP
#define GRAPH_BST_CPP

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef GRAPH_BST_H
#include "Graph.h"
#endif

// ==========================================================================================

void Graph::modifiedDFS(){
	static int time = 0;
	static int currNode;
	static BST currBST;

	if(time == 0){

		simpleDFS();
		time++;
		for(int i=0; i<numNodes; i++){
			no_of_times_discovered[i] = 0;
		}

		no_of_connected_components = 0;

		for(int i=0; i<numNodes; i++){
			if(no_of_times_discovered[i] == 0){
				no_of_connected_components++;

				BST t;
				currBST = t;

				currNode = i;
				modifiedDFS();

				Trees.push_back(currBST);
			}
		}

		return;
	}
	// ++++++++++++++++++++++++++++++++++++++++++++++++

	int u = currNode;
	// cout << currNode+1 << endl;
	currBST.insert(u+1);
	time++;
	no_of_times_discovered[u]++;

	for(int i=0; i<nodes[u].degree(); i++){
		int v = nodes[u].adjNodes[i].first;

		if(no_of_times_discovered[v] < 2 && is_present_edge(u,v)){
			deactivate_edge(v, u);
			currNode = v;
			modifiedDFS();
		}
	}

	return;

}

// ==========================================================================================

void Graph::printResults(){
	cout << "Number of Connected Components: " << no_of_connected_components << endl;
	print_nodes_visited(1);
	print_nodes_visited(2);
	print_nodes_in_cycle();
	printTrees();
	return;
}

#endif
