#ifndef GRAPH_BST_H
#define GRAPH_BST_H

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

template <typename T> class LL{
	// linked list (set like implementation i.e no value twice)
	public:
	T obj;
	LL<T> * next = nullptr;
	LL(T obj): obj(obj){}
	bool insert(T n){
		if(obj == n) return false;
		if(next != nullptr) return next->insert(n);
		next = new LL(n);
		return true;
	}
	~LL(){
		if (next != nullptr) delete next;
	}
};

class Node {
	// node class for the graph
public:
	// int value;
	LL<int>* outedges = nullptr; // outgoing
	LL<int>* inedges = nullptr; // incoming
	// LL<int>* similar = nullptr;
	int numin = 0; // number of incoming edges
	int numout = 0; // number of outgoing edges

	Node(){}
	// Node(int value): value(value){}
	bool insertout(int node){
		// insert out edge
		if(outedges != nullptr){
			if(outedges->insert(node)){
				numout++;
				return true;
			}
			return false;
		}
		outedges = new LL<int>(node);
		numout++;
		return true;
	}
	bool insertin(int node){
		// insert in edge
		if(inedges != nullptr){
			if(inedges->insert(node)){
				numin++;
				return true;
			}
			return false;
		}
		inedges = new LL<int>(node);
		numin++;
		return true;
	}
	// bool insertsimilar(int node){
	// 	if(similar != nullptr) return similar->insert(node);
	// 	similar = new LL<int>(node);
	// 	return true;
	// }
	~Node(){
		if(outedges != nullptr) delete outedges;
		if(inedges != nullptr) delete inedges;
		// if(similar != nullptr) delete similar;
	}
};

class Graph {
	int numNodes; // number of nodes in the graph
	int numEdges; // number of edges in the graph
	Node *nodes; // array of nodes
	bool* sources; // is a node a source
	int** similarity; // similarity matrix

	int* alias; // the identifier if that node in merged graph
	int num_collcomp; // number of nodes in collapsed graph
	int* collNodes; // collapsed nodes to identifier
	bool** collapsegraph; // collapsed graph adjacency matrix

	fstream graphFile;

 public:
	Graph(int numNodes, string gFileName): numNodes(numNodes){
		nodes = new Node[numNodes];
		sources = new bool[numNodes];
		similarity = new int*[numNodes];
		for (int i = 0; i < numNodes; i++) {
			similarity[i] = new int[numNodes];
			for(int j=0; j<numNodes; j++){
				similarity[i][j] = -1;
			}
			sources[i] = true;
		}
		graphFile.open(gFileName, ios::out);
		if (!graphFile.is_open()) {
			cerr << "Couldn't open graph file " << gFileName << ". Aborting ..." << endl;
			exit(-1);
		}
	}

	// also updates sources
	void read_graph();

	// prints sources
	void print_sources();

	// reads similar relations and updates the graph
	void read_similar();

	// perform condition 3 on the graph
	void similar_check3();

	// calculates similarity relations
	void calc_similar();

	// does a one way condition 2 check on (n1, n2)
	bool check2(int n1, int n2);

	// prints similar nodes in reqd format
	void print_similar();

	// create a collapsed graph from the current graph
	void collapse();

	// print sthe collapsed garph in required format
	void print_collapsed();

	// function for memoization
	bool similar(int n1, int n2);

	// a helper dfs is used in collpasing and marking the edges
	void dfs(int n, bool* visited, int comp);

	~Graph() {
		if (graphFile.is_open()) {
      		graphFile.close();
    	}
		delete[] nodes;
		delete[] sources;
		delete[] collNodes;
		delete[] alias;
		for(int i=0; i<numNodes; i++) delete[] similarity[i];
		delete[] similarity;
		for(int i=0; i<num_collcomp; i++) delete[] collapsegraph[i];
		delete[] collapsegraph;
	}
};

#endif
