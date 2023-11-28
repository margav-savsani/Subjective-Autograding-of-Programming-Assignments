#include "graph.h"
using namespace std;

graph::graph(int n){						//constructor
	numnodes=n;
    nodes = new Node[numnodes];
	similar=new int[n*n];
    if (nodes == nullptr){					//error case
      	cerr << "Memory allocation failure." << endl;
      	exit(-1);
    }
    for (int i = 0; i < numnodes; i++){		//values are i+1
      	nodes[i].value = i+1;
    }
    for (int i = 0; i < n*n; i++){			//initially setting all elements of similar=0
      	similar[i] = 0;
    }
	edges=NULL;
}

void graph::insert_edge(int a, int b){
	node2* k=nodes[a].outcom;
	nodes[b].sources=0;
	if(nodes[a].outcom==NULL){
		nodes[a].outcom=new node2(b);        //adding into outgoing list
	}
	else{
		while(k->next!=NULL){
			k=k->next;
		}
		k->next=new node2(b);
	}
	node2* p=nodes[b].incom;
	if(nodes[b].incom==NULL){
		nodes[b].incom=new node2(a);        //adding into incoming list
	}
	else{
		while(p->next!=NULL){
			p=p->next;
		}
		p->next=new node2(a);
	}
	if(edges==NULL){						//inserting in edges list
		edges=new point(a,b);
	}
	else{
		point* p=edges;
		while(p->next!=NULL){
			p=p->next;
		}
		p->next=new point(a,b);
		p->next->prev=p;
	}
}

bool graph::part(int a, int b){				//checks second condition of similarity
	node2* k=nodes[a].incom;
	while(k!=NULL){
		bool t=false;
		node2* p=nodes[b].incom;
		while(p!=NULL){
			// cout<<k->index+1<<"---"<<p->index+1<<endl;
			if(similar_edge(k->index,p->index)){
				t=true;
				break;
			}
			p=p->next;
		}
		if(!t){
			return false;
		}
		k=k->next;
	}
	return true;
}

bool graph::similar_edge(int a, int b){			//updates similar array
	if(similar[a*numnodes+b]==1){
		return true;
	}
	if(nodes[a].sources==0 && nodes[b].sources==0){
		if(part(a,b) && part(b,a)){
			similar[a*numnodes+b]=1;
			similar[b*numnodes+a]=1;
			return true;
		}
	}
	return false;
}

void graph::DFS(int a, node2* x){				//dfs algorithm
	if(nodes[a].visited==1){
		return;
	}
	while(x->next!=NULL){
		x=x->next;
	}
	x->next=new node2(a+1);
	nodes[a].visited=1;
	node2* p=nodes[a].coladj;
	while(p!=NULL){
		DFS(p->index, x);
		p=p->next;
	}
}
