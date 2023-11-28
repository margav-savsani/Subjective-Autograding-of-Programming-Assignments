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
  	static int prev=0,on=0;
  	static bool iter=true;
  	static BSTList* bst;
  	if(iter){
  		iter=false;
  		concomp=0;
  		if(numNodes>0){
  			bsts=new BSTList();
  			bst=bsts;
  			on=1;
  			prev=0;
  			modifiedDFS();
  			concomp++;
  		}
  		else{
  			return;
  		}
  		for(int i=2;i<=numNodes;i++){
  			if(nodes[i].visited==0){
  				bst->next=new BSTList();
  				bst=bst->next;
  				on=i;
  				prev=0;
  				modifiedDFS();
  				concomp++;
  			}
  		}
  		iter=true;
  	}
  	else{
  		int ON=on;
  		if(nodes[on].visited==2||nodes[on].backtrack){
  			return;
  		}
  		else{
  			if(nodes[ON].visited==1){
  				node1--;
  				node2++;
  				nodecyc++;
  			}
  			else{
  				node1++;
  			}
  			bst->obj.insert(ON);
  			nodes[ON].prev[nodes[ON].visited]=prev;
  			nodes[ON].visited++;
  			bool backtrack=true;
  			AdjList* adjacent=nodes[ON].adjacent;
  			while(adjacent!=nullptr){
  				if(adjacent->val!=nodes[ON].prev[0]&&adjacent->val!=nodes[ON].prev[1]){
  					prev=ON;
  					on=adjacent->val;
  					modifiedDFS();
  					backtrack=backtrack && nodes[adjacent->val].backtrack;
  				}
  				adjacent=adjacent->next;
  			}
  			nodes[ON].backtrack=backtrack;
  		}
  	}
}

void Graph::printResults() {
	cout<<"No. of connected components: "<<concomp<<endl;
	cout<<"No. of nodes visited once: "<<node1<<endl;
	cout<<"No. of nodes visited twice: "<<node2<<endl;
	cout<<"No. of nodes that are present in a cycle: "<<nodecyc<<endl;
	int i=1;
	for(BSTList* bst=bsts;bst!=nullptr;bst=bst->next,i++){
		cout<<"Connected Component - "<<i<<endl;
		cout<<bst->obj.root->val<<endl;
		bst->obj.printBST(bst->obj.root->left,"",true);
		bst->obj.printBST(bst->obj.root->right,"",false);
	}
 	return;
}

#endif
