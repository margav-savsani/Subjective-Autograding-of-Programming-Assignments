#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string>
#include <sstream>
#include <cstring>
#include <cctype>
using namespace std;

class point{             //node of list to store edges
	public:
		int a,b;
		point* next;		//pointer to next edge
		point* prev;
		point(int x, int y){
			a=x;b=y;
			next=NULL;
			prev=NULL;
		}
};

class node2{			//node of list of indices
	public:
	int index;			//contains index of node
	node2* next;
	node2(int i){
		index=i;
		next=NULL;
	}
};

class Node{
 	public:
  		int value;
  		int visited;			//visiting status
  		node2* outcom;			//nodes that has edge from this node
		node2* incom;			//nodes that has edge to this node
		int sources;			//to identify source nodes
		node2* coladj;
  		Node(){
  		  	visited=0; 			//can take 0,1
			outcom=NULL;
			incom=NULL;
			sources=1;
			coladj=NULL;
  		}
};

class graph{
	public:
		int numnodes;		//no. of nodes in graph
		Node* nodes;		//nodes array
		int* similar;		//to identify similar ones
		point* edges;		//pointer to list of edges
		graph(int n);
		void insert_edge(int a, int b);
		bool similar_edge(int a, int b);
		bool part(int a, int b);
		void DFS(int a, node2* x);
		~graph(){
			delete[] nodes;
		}
};