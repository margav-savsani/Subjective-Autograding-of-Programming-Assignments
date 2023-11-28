#include<iostream>
#include "Graph.cpp"
using namespace std;

int main(){
	int n;
	cin>>n;
	Graph g(n);
	g.makeGraph();
	g.printDetails();
}
