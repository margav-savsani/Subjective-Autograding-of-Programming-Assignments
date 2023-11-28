#ifndef GRAPH_BST_CPP
#define GRAPH_BST_CPP

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef GRAPH_BST_H
#include "Graph.h"
#endif

// Add code as appropriate for your implementation
void Graph::modifiedDFS(int node) {
	static int reclvl = -1;
	static bool *finished = new bool[numNodes];
	static int *pi = new int[numNodes];
	static BST* curr = nullptr;
	static int flag = -1;

	reclvl++;

	if(reclvl==0){
		for(int i=0; i<numNodes; i++){
			finished[i]= 0;
			cyclic[i]=0;
			visited[i]=0;
			pi[i] = 0;
		}
		for(int i=0; i<numNodes; i++){
			if(!finished[i]){
				visited[i]++;
				auto prevflag = flag;
				flag = -1;
				curr = new BST(nodes[i].value);
				auto adjnodes = nodes[i].adjacency;
				while(adjnodes!=nullptr){
					if (pi[node] != adjnodes->obj){
						if(visited[adjnodes->obj] > 0){ 
							flag = adjnodes->obj;
							// int curr = node;
							// while(curr != adjnodes->obj){
							// 	cyclic[curr] = true;
							// 	curr = pi[curr];
							// }
						}

						if (visited[adjnodes->obj] == 0){
							pi[adjnodes->obj] = node;
							modifiedDFS(adjnodes->obj);
						}
						else if (visited[adjnodes->obj] == 1){
							modifiedDFS(adjnodes->obj);
						}
					}
					adjnodes = adjnodes->next;
				}
				finished[i] = true;
				if(flag != -1) cyclic[node] = true;
				if(flag == node) flag = -1;
				flag = prevflag;
				if(bstLL != nullptr) bstLL->insert(curr);
				else bstLL = new LL<BST*>(curr);
				curr = nullptr;
			}
		}
	}
	else{
		visited[node]++;
		auto prevflag = flag;
		flag = -1;
		curr->insert(nodes[node].value);
		auto adjnodes = nodes[node].adjacency;
		while(adjnodes!=nullptr){
			if(pi[node] != adjnodes->obj)
			{
				if(visited[adjnodes->obj] > 0){ 
					flag = adjnodes->obj;
					// int curr = node;
					// while(curr != adjnodes->obj){
					// 	cyclic[curr] = true;
					// 	curr = pi[curr];
					// }
				}

				if(visited[adjnodes->obj] == 0){
					pi[adjnodes->obj] = node;
					modifiedDFS(adjnodes->obj);
				}
				else if(visited[adjnodes->obj] == 1){
					modifiedDFS(adjnodes->obj);

				}
			}
			adjnodes = adjnodes->next;
		}
		finished[node] = true;
		if(flag != -1) cyclic[node] = true;
		if(flag == node) flag = -1;
		flag = prevflag;
	}

	reclvl--;
	if(reclvl == -1){
		delete[] finished;
		delete[] pi;
	}
}

void Graph::printResults() {
	int conn = 0;
	auto temp = bstLL;
	while(temp!=nullptr){
		cout<<"BST TREE "<<(++conn)<<":\n";
		temp->obj->printBST("",false);
		temp = temp->next;
	}
	int v1 = 0, v2 = 0, c = 0;
	for(int i=0; i<numNodes; i++){
		if(visited[i]==2) v2++;
		else if(visited[i]==1) v1++;
		else cout<<"ERROR at "<<i<<endl;
		if(cyclic[i]){ 
			// cout<<i+1<<" ";
			c++;
		}
	}
	cout<<"No. of connected components: "<<conn<<endl;
	cout<<"No. of nodes visited once: "<<v1<<endl;
	cout<<"No. of nodes visited twice: "<<v2<<endl;
	cout<<"No. of nodes that are present in a cycle: "<<c<<endl;
}
#endif
