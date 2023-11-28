#include<iostream>
using namespace std;
#include "Graph.cpp"
#include<fstream>

bool notFind(List<int*> &c, int max1, int max2){
	auto curr = c.start;
	while(curr!=nullptr){
		if(curr->value[0]==max1 && curr->value[1]==max2)
			return false;
		curr = curr->next;
	}
	return true;
}

void printCompressedGraph(Graph &g){
	ofstream file;
	file.open("outgraph.txt",std::ios::out|std::ios::app);
	file << endl;
	file << "Collapsed graph:"<<endl;
	file << g.totalComp <<": ";
	auto curr1 = g.comp->start;
	while(curr1!=nullptr){
		file << curr1->value->end->value<<" ";
		curr1 = curr1->next;
	}	
	file << endl;
	List<int*> c;
	for(int i=0;i<g.numberOfNodes;i++){
		auto curr = g.node[i].outEdges->start;
		int val1 = i+1;
		while(curr != nullptr){
			int val2 = curr->value;
			int max1 = g.node[val1-1].component->end->value;
			int max2 = g.node[val2-1].component->end->value;
			if(max1 != max2){
				if(notFind(c, max1, max2)){
					file << max1 <<" " << max2 << endl;
					auto x = new int[2];
					x[0] = max1;
					x[1] = max2;
					c.insert(x);
				}
			}
			curr = curr->next;
		}
	}
	file.close();
}


int main(){
	int n; // the number of nodes
	cin >> n;
	int n1,n2;
	n1 = n2 =0;
	Graph g(n); // Graph with n nodes
	while(true){
		cin >> n1 >> n2; // Take in n1 and n2 , n1 is node which directs an edge to n2
		if(n1 == -1 && n2 == -1)
			break;
		g.insertEdge(n1, n2); // insertEdge in the graph
	}
	n1 = n2 = 0;
	while(true){
		cin >> n1 >> n2;
		if(n1 == -1 && n2 == -1)
			break;
		g.insertSimilarNodes(n1, n2);
	}
	
	
	g.minLevel(); // minLevel is the shortest distance from the set of source nodes
	g.assignLevel();// level is the minLevel
	g.check3(); // find similar nodes according to condition 3
	g.check2();// find similar nodes according to condition 2
	g.printSourceNodes(); // printSoruce nodes in the outgraph.txt file
	g.printSimilarNodes();//printsimilar ndoes in the outgraph.txt file
	g.findCompMain(); //it gives us the transitive symmetrix closure 
	printCompressedGraph(g); // print the compressed graph
	//g.printLevel();
}
