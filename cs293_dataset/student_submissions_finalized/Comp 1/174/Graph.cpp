#ifndef GRAPH_BST_CPP
#define GRAPH_BST_CPP

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef GRAPH_BST_H
#include "Graph.h"
using namespace std;
#endif

void Graph::modDFS(BST* b, int k, int par, node2* traversal, point* edg){
  	nodes[k].visited++;
  	// cout<<nodes[k].value<<" ";   //b is the bst for a connected component
  	b->insert(k+1);				 	// inserting into bst
  	node2* f;
  	f=nodes[k].adja;            

	node2* tra;						//travered elements 
	tra=traversal;
	while(tra->next!=NULL){
		tra=tra->next;
	}
	tra->next=new node2(k);          
	tra->next->prev=tra;
	if(nodes[k].visited==2){       //cycle case
		tra=traversal;
		while(tra->index!=k){
			tra=tra->next;
		}
		while(tra->next!=NULL){
			nodes[tra->index].cycle=true;     //making cycle of respective nodes true
			tra=tra->next;
		}
		tra=tra->prev;
	}

  	while(f!=NULL){
		if(nodes[f->index].visited<2 && f->index!=par){
			// cout<<"("<<k+1<<", "<<f->index+1<<")"<<" ";
			point* tra3;						//paths taken by dfs during traversal
			tra3=edg;
			while(tra3->next!=NULL){
				tra3=tra3->next;
				if(tra3->a==f->index+1 && tra3->b==k+1){  //correcting wrong cycle of nodes
					nodes[k].cycle=false;
				}
			}
			tra3->next=new point(k+1, f->index+1);
			modDFS(b, f->index, k, traversal, edg);			//recursive call
		}
		f=f->next;
  	}
	if(nodes[tra->next->index].adja!=NULL && nodes[tra->next->index].adja->next==NULL){tra->next=NULL;}
}

// Add code as appropriate for your implementation
void Graph::modifiedDFS() {
  	for(int i=0; i<numNodes; i++){
  	  	if(nodes[i].visited==0){
			node2* traversal;
			traversal=new node2(-5);       //for tracking dfs
			point* edg;
			edg=new point(-10,-10);       //for tracking paths taken by dfs
  	  	  	BST* b;
  	  	  	b=new BST;
  	  	  	modDFS(b,i,-1, traversal,edg);

  	  	  	b->printBST("");            //printing bst
  	  	  	conncomp++;
  	  	}
  	}
  	return;
}

void Graph::printResults() {
	int once,twice, cycles;
	once=0;
	twice=0;
	cycles=0;
  	cout<<"No. of connected components: "<<conncomp<<endl;
  	for(int i=0; i<numNodes; i++){
  	  	if(nodes[i].visited==1) once++;
  	  	if(nodes[i].visited==2) twice++;
		if(nodes[i].cycle) cycles++;		//counting no. of nodes in cycles
  	}
  	cout<<"No. of nodes visited once: "<<once<<endl;    //printing results
  	cout<<"No. of nodes visited twice: "<<twice<<endl;
  	cout<<"No. of nodes that are present in a cycle: "<<cycles<<endl;
  	return;
}

#endif
