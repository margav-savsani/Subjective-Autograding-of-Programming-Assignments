#include <bits/stdc++.h>
#include <fstream>
#include "graph.h"
using namespace std;


int main(){
	int i=1;
	int n;
	// int *source, *sink;
	ofstream f;
	f.open("outgraph.txt");
	Graph *g;
	int a, b;
	string line;
	cin >> n;
	g = new Graph(n);
	while(cin >> a >> b){
		if(a == -1 && b==-1)
			break;
		else{
			g->addEdge(a,b);
		}
		i++;
	}
	while(cin >> a >> b){
		if(a==-1 && b==-1)
			break;
		g->checksim(a,b);
	}
	g->checksimcase3();
	g->case2();
	g->printsourceNodes();
	g->printSimilarNodes();
	g->connComp();
	g->printGraph();
}