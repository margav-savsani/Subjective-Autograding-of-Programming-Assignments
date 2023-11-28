#ifndef GRAPH_BST_CPP
#define GRAPH_BST_CPP

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef GRAPH_BST_H
#include "Graph.h"
#endif
using namespace std;

void Graph:: cycles( int curr, int parent){// to check all the vertices in the cycle.
	
	if ( stage_of_vertices[curr] == 2){ // Normal DFS, come back.
		
		return;
	}
	
	else if ( stage_of_vertices[curr] == 1){// means it is already visited once
		
		int current = parent; // from parent.
		present_in_cycle[curr] = 1; // current is present in the cycle.
		while( current != curr){			
			present_in_cycle[current] = 1; // make it 1, because it is present in cycle.
			current = parent_array[current];// find parent of the current node and add make present_in_cycle[curr]  = 1
		}
		return;
	}
	
	else {// if it is not visited atleast once.
		
		parent_array[curr] = parent; // make the current vertex parent of this.
		
		stage_of_vertices[curr] = 1;// change the stage of the vertex.
		
		for ( int i=0; i< numNodes; i++){// proceed the dfs.
		
			if ( adj[curr][i] == 1 && i != parent){ 
			
				cycles(i, curr);// continue the cycle.
			}
		}
		
		stage_of_vertices[curr] = 2;// change the stage of the vertex.
		
	}

}	
	
void Graph :: DFS( int currentnode,  int prev_node){ // DFS helper.
	
	if( nodes[currentnode].no_of_times_visited == 2){// if it is visited twice, then just return, Back track.
		
		return;
	}
	else{
			
		tail->tree->insert( nodes[currentnode].value);// insert into the tree, if it is not visited twice.		
		nodes[currentnode].no_of_times_visited ++;// increase the number of visits.
		
		for( int i=0; i< numNodes; i++){		
			if( adj[currentnode][i] == 1 && i != prev_node && i != parent_array[currentnode]){// if it is not parent, previous parent, then do DFS.
				
				DFS(i, currentnode);
			}
		}
	}
	
	return;
}


void Graph::modifiedDFS() {// modified DFS.
  

   while( currnode < numNodes && nodes[currnode].no_of_times_visited == 0 ){ // because all the vertices may not be connected.
        
        if ( head == nullptr){// first BFS.
        	
        	head = new ConnectedTrees;
        	tail = head;
        }
        else{
        	
        	ConnectedTrees* tail2 = new ConnectedTrees;
        	tail->next = tail2;// update the tail.
        	tail = tail2;
        }       	 
        no_of_connected_graphs ++;// increase the number of connected graphs.
        
        for( int i=0; i< numNodes; i++){// with first element do the cycles. 	
        	if ( adj[currnode][i] == 1){
        		cycles(i, currnode);
        	}
        }        
   	DFS(currnode, currnode);// do the dfs.
   	while( currnode < numNodes){ // update the currentNode.
   		
   		if ( nodes[currnode].no_of_times_visited == 0){// then do modified DFS on it.
   			break;
   		}
   		currnode++;
   	}  			   	
   }
    
  return;
}

void Graph::printResults() {// print the results.
  
  // BST trees print.
  ConnectedTrees* trees = head;// trees head.
  while( trees != nullptr){
  	
  	trees->tree->printBST("");
  	trees = trees->next;
  }
  
  cout<< "No. of connected components: " << no_of_connected_graphs << endl;
  // print number of one time and two time visited vertex.
  int one = 0, two = 0;// vertices.
  for( int i=0; i< numNodes; i++){
  	
  	if( nodes[i].no_of_times_visited == 1) one++;
  	else two++;
  }
  cout<< "No. of nodes visited once: "<< one << endl;
  cout<< "No. of nodes visited twice: "<<two<<endl;
  
  int count = 0;
  // number of vertices in the cycle.
  for ( int i=0; i<numNodes; i++){
  	if( present_in_cycle[i] == 1) {count++;}
  }
  cout<< "No. of nodes that are present in a cycle: "<< count<<endl;
  
  return;
}

#endif
