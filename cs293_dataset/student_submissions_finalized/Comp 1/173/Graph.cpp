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
	static int nodeIdx = 0;
	static int depth = 1;
	// static int idxConn = 1;
	// static int x=0;
	(t+numComp-1)->insert(nodeIdx+1);
	visited[nodeIdx]++;
	list *curr = nodes[nodeIdx].adj->next;
	while (curr != nullptr) {

		int currIdx = nodeIdx;
		nodeIdx = curr->value - 1;
		if (visited[nodeIdx] < 2) {
			// if (visited[nodeIdx] == 0)
				// connected[nodeIdx] = idxConn;
			del(&nodes[nodeIdx].adj, currIdx+1);
			depth++;
			modifiedDFS();
			depth--;
		}
		curr = curr->next;
	}

	if (depth == 1) {
		for (int i=0; i<numNodes; i++)
			if (visited[i] == 0) {
				numComp++;
				nodeIdx=i;
				modifiedDFS();
			}
	}
	return;
}

void Graph::printResults() {
	int visits1=0;
	int visits2=0;
	for (int i=0; i<numNodes; i++) {
		if (visited[i]==1) visits1++;
		else if (visited[i]==2) visits2++;
	}
	cout << "numComp: " << numComp << endl;
	cout << "vists-1: " << visits1 << endl;
	cout << "vists-2: " << visits2 << endl;
	for (int i=0; i<numComp; i++)
		(t+i)->printBST("", false);
	return;
}

#endif