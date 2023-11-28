#ifndef GRAPH_BST_CPP
#define GRAPH_BST_CPP

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef GRAPH_BST_H
#include "Graph.h"
#endif

#include <stack>

// Add code as appropriate for your implementation
void Graph::modifiedDFS() {
	stack<Pair<Node*, Node*>> S;

	delete[] visit_status;
	visit_status = new short[numNodes]{0};

	//delete all the old data and set connected_components to NULL
	while(connected_components){
		delete connected_components->data;
		connected_components = connected_components->next;
	} 

	connected_components = NULL;
	for(int i{0}; i<numNodes; i++){

		//add unvisited vertices to the stack
		if(visit_status[i])
			continue;
		S.push({nodes+i, NULL});
		
		//create a new BST for the new connected component
		//the newly created tree stays at the top of the list
		List<BST*>* temp = connected_components;
		connected_components = new List<BST*>{NULL};
		Node** parents = new Node*[numNodes]{NULL};
		connected_components->next = temp;

		while(!S.empty()){
			Node* n = S.top().first;
			Node* parent = S.top().second;
			S.pop();
			// cout<<n->value<<" "<<(parent?parent->value:0)<<endl;
			if(visit_status[n->value-1] >= 2)
				continue;
			if(connected_components->data)
				connected_components->data->insert(n->value);
			else
				connected_components->data = new BST{n->value};

			if(parents[n->value-1] == NULL)
				parents[n->value-1] = parent;

			visit_status[n->value-1]++;
			List<Node*>* temp = n->adj;
			while(temp){
				// cout<<temp->data->value<<" "<<n->value<<" "<<(parent?parent->value:-1)<<endl;
				short& visits = visit_status[temp->data->value-1];
				if((visits < 2) && (temp->data != parent) && (temp->data != parents[n->value-1])){
					S.push({temp->data, n});
				}
				temp = temp->next;
			}
		}
	}

	//do DFS again to find the nodes present in cycles
	int arr_time[numNodes]{-1};
	int deepest_back_edge[numNodes]{INT32_MAX}; //stores the arrival time of the end of the deepest back edge from the subtree rooted at each node
	short visit_status_2[numNodes]{0};
	for(int i{0}; i<numNodes; i++){
		arr_time[i] = -1;
		deepest_back_edge[i] = INT32_MAX;
		visit_status_2[i] = 0;
	}
	for(int i{0}; i<numNodes; i++){
		//add unvisited vertices to the stack
		if(visit_status_2[i] != 0)
			continue;
		S.push({nodes+i, NULL});
		int time = 0;
		while(!S.empty()){
			Node* n = S.top().first;
			Node* parent = S.top().second;
			if(visit_status_2[n->value-1] == 2){
				S.pop();
				continue;
			}
			if(visit_status_2[n->value-1] == 1){
				visit_status_2[n->value-1] = 2;
				S.pop();
				List<Node*>* temp = n->adj;
				while(temp){
					if(temp->data == parent){
						temp = temp->next;
						continue;
					}
					int req_time = 0;
					if(arr_time[temp->data->value-1] < arr_time[n->value-1])
						req_time = arr_time[temp->data->value-1];
					else
						req_time = deepest_back_edge[temp->data->value-1];
					if(req_time < deepest_back_edge[n->value-1])
						deepest_back_edge[n->value-1] = req_time;
					temp = temp->next;
				}
				// cout<<deepest_back_edge[n->value-1]<<" "<<n->value<<endl;
				if(deepest_back_edge[n->value-1] <= arr_time[n->value-1])
					visit_status[n->value-1]+=100;
				continue;
			}
			visit_status_2[n->value-1] = 1;
			List<Node*>* temp = n->adj;
			arr_time[n->value-1] = time++;
			while(temp){
				if(!(visit_status_2[temp->data->value-1]))
					S.push({temp->data, n});
				temp = temp->next;
			}
		}
	}	
}

void Graph::printResults() {
	int num_connected_components = 0;
	int num_visit_once = 0;
	int num_visit_twice = 0;
	int num_nodes_in_cycles = 0;
	if(!visit_status)
		return;
	for(int i{0}; i<numNodes; i++){
		if(visit_status[i]%100==1)
			num_visit_once++;
		else if(visit_status[i]%100 == 2)
			num_visit_twice++;
		if(visit_status[i] >= 100){
			// cout<<i+1<<endl;	
			num_nodes_in_cycles++;
		}
	}
	List<BST*>* temp = connected_components;
	while(temp){
		temp = temp->next;
		num_connected_components++;
	}
	cout<<"num_connected_components: "<<num_connected_components<<endl;
	cout<<"num_visit_once: "<<num_visit_once<<endl;
	cout<<"num_visit_twice: "<<num_visit_twice<<endl; 
	cout<<"num_nodes_in_cycles: "<<num_nodes_in_cycles<<endl; //number of nodes present in cycles

	temp = connected_components;
	while(temp){
		temp->data->printBST();
		temp = temp->next;
	}
}

#endif
