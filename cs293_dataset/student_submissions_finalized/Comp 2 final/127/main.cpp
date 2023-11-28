#include <iostream>
#include <fstream>
#include <vector>




class Node {

	public:

		std::vector<Node*> outgoing;
		std::vector<Node*> incoming;
		std::vector<Node*> similarity_list;
		int number;

		Node() {}
		
		Node(int num) {
			number=num;
		}

		void add_incoming(Node* node) {
			incoming.push_back(node);
		}

		void add_outgoing(Node* node) {
			outgoing.push_back(node);
		}

		void add_similarity(Node* node) {
			similarity_list.push_back(node);
		}

};

class Graph {

	public:

		int num_nodes;
		Node** node_list;

		Graph(int n) {
			num_nodes=n;
			node_list=new Node*[n];
			for(int kappa=0; kappa<n; kappa++) {
				node_list[kappa]=new Node(kappa);
				//node_list[kappa]->number=kappa;
			}
		}

		

};



int main(int argc, char **argv) {

	std::ofstream cout("outputgraph.txt");

	std::vector<int> start_nodes;
	std::vector<int> end_nodes;
	std::vector<int> user_similar_1;
	std::vector<int> user_similar_2;

	int numNodes;
	std::cin>>numNodes;

	Graph* graph=new Graph(numNodes);

	int edge1=0;
	int edge2=0;
	int similar1=0;
	int similar2=0;

	int source[numNodes];
	int sink[numNodes];

	for(int delta=0; delta<numNodes; delta++) {
		source[delta]=0;
		sink[delta]=0;
	}

	while(true) {
		std::cin>>edge1>>edge2;
		if(edge1==-1 && edge2==-1) break;

		start_nodes.push_back(edge1-1);
		end_nodes.push_back(edge2-1);

		source[edge1-1]+=1;
		sink[edge2-1]+=1;

		graph->node_list[edge1-1]->add_outgoing((graph->node_list[edge2-1]));
		graph->node_list[edge2-1]->add_incoming((graph->node_list[edge1-1]));
	}

	while(true) {
		std::cin>>similar1>>similar2;
		if(similar1==-1 && similar2==-1) break;

		user_similar_1.push_back(similar1-1);
		user_similar_2.push_back(similar2-1);

		graph->node_list[similar1-1]->add_similarity(graph->node_list[similar2-1]);
		graph->node_list[similar2-1]->add_similarity(graph->node_list[similar1-1]);
	}

	std::vector<int> sources;
	std::vector<int> sinks;

	for(int alpha=0; alpha<numNodes; alpha++) {
		if(source[alpha]>=1 && sink[alpha]==0) sources.push_back(alpha);
		if(sink[alpha]>=1 && source[alpha]==0) sinks.push_back(alpha);
	}

	std::vector<int> similar_pair_1;
	std::vector<int> similar_pair_2;

	for(int epsilon=0; epsilon<numNodes; epsilon++) {
		for(int phi=0; phi<numNodes; phi++) {
			if(source[epsilon]>=1 && sink[epsilon]==0) {
				if(source[phi]>=1 && sink[phi]==0 && epsilon!=phi) {
					similar_pair_1.push_back(epsilon);
					similar_pair_2.push_back(phi);
				}
				else {
					if((graph->node_list[epsilon]->incoming).size()==1 && (graph->node_list[epsilon]->incoming)[0]->number==phi && epsilon!=phi) {
						similar_pair_1.push_back(epsilon);
						similar_pair_2.push_back(phi);
					}
				}
			}
			else {
				if(source[phi]>=1 && sink[phi]==0) {
					if((graph->node_list[epsilon]->incoming).size()==1 && (graph->node_list[epsilon]->incoming)[0]->number==phi && epsilon!=phi) {
						similar_pair_1.push_back(epsilon);
						similar_pair_2.push_back(phi);
					}
				}
				else {
					bool is_similar=true;
					for(int psi=0; psi<graph->node_list[epsilon]->incoming.size(); psi++) {
						for(int gamma=0; gamma<graph->node_list[phi]->incoming.size(); gamma++) {
							bool yesval=false;
							for(int theta=0; theta<graph->node_list[psi]->similarity_list.size(); theta++) {
								if(graph->node_list[graph->node_list[epsilon]->incoming[psi]->number]->similarity_list[theta]->number==graph->node_list[phi]->incoming[gamma]->number) {
									yesval=true;
									break;
								}
							}
							if(!yesval) {
								is_similar=false;
								break;
							}	
						}
						if(!is_similar) break;
					}
					if(is_similar) {
						if(epsilon!=phi) {
							similar_pair_1.push_back(epsilon);
							similar_pair_2.push_back(phi);
						}
					}
				}
			}
		}
	}

	cout<<"Source nodes: ";
	for(int n=0; n<sources.size(); n++) {
		cout<<sources[n]+1<<" ";
	}
	cout<<"\n\n";

	cout<<"Similar node pairs: ";
	for(int m=0; m<similar_pair_1.size(); m++) {
		cout<<"("<<similar_pair_1[m]+1<<", "<<similar_pair_2[m]+1<<") ";
	}
	cout<<"\n\n";

	cout<<"Collapsed graph:\n";








	return 0;
}
