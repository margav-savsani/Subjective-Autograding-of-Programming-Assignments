#include "Graph.h"
DAG::DAG(int n){
	// Initialise graph member variables
        numNodes = n;
        numEdges = 0;
        similar = new bool*[n];
        edges = new EdgeList();
        nodes = new Node[numNodes];
        no_of_equivalence_classes = 0;
        class_representative = new int[numNodes];
        equivalence_class_list = new int*[numNodes];
        class_length = new int[numNodes];

	// Initialise relevant quantities to zero
        for (int i=0; i<numNodes; i++) {
            nodes[i].value = i + 1;
            similar[i] = new bool[numNodes];
            equivalence_class_list[i] = new int[numNodes];
            class_length[i] = 0;
            for (int j=0; j<numNodes; j++) {
                similar[i][j] = 0;
            }
        }
	// take in edges as input
        int a, b;
        cin>>a>>b;
        while (a!=-1 && b!=-1){
            nodes[a-1].out_neighbours++; nodes[b-1].in_neighbours++;
            numEdges++;
            Edge* e = new Edge(a, b);
            if (edges->object==nullptr){
                edges->object = e;
            }
            else {
                edges->prev = new EdgeList(edges, e);
                edges = edges->prev;
            }
            cin>>a>>b;
        }

        create_adjacency();

	// Take in similar nodes
        cin>>a>>b;
        while (a!=-1 && b!=-1){
            similar[a-1][b-1] = 1;
            cin>>a>>b;
        }
    }

void DAG::create_adjacency(){
    // Create the adjacency list from linked list of edges
    int out_adjcount[numNodes];
    int in_adjcount[numNodes];

    // Allocate space for adjacency lists
    for (int i=0; i<numNodes; i++) {
        nodes[i].out_adjacent = new int[nodes[i].out_neighbours];
        nodes[i].in_adjacent = new int[nodes[i].in_neighbours];
        out_adjcount[i] = 0;
        in_adjcount[i] = 0;
    }

    // Fill the adjacency lists
    EdgeList* head = edges;
    while (head!=nullptr){
        int n1 = head->object->node1;
        int n2 = head->object->node2;
        nodes[n1-1].out_adjacent[out_adjcount[n1-1]] = n2;
        nodes[n2-1].in_adjacent[in_adjcount[n2-1]] = n1;
        out_adjcount[n1-1]++;
        in_adjcount[n2-1]++;
        head = head->next;
    }
}

void DAG::printSource(){
    cout<<"Source Nodes: ";
    for (int i=0; i<numNodes; i++) {
        if (nodes[i].in_neighbours==0){
            cout<<nodes[i].value<<" ";
        }
    }
    cout<<endl;
}

bool DAG::isSimilar(int a, int b){
    if (similar[a][b]){
        return true;
    }
    if (nodes[a].in_neighbours==1 && nodes[a].in_adjacent[0] == nodes[b].value){
        similar[a][b] = 1;
        //cout<<"condition 3 for "<<a+1<<" "<<b+1<<endl;
        return true;
    }
    else if (!(isSource(a+1) || isSource(b+1))){
        // none are source nodes
	// check for condition 2 recursively
        for (int i=0; i<nodes[a].in_neighbours; i++) {
            bool found = false;
            for (int j=0; j<nodes[b].in_neighbours; j++) {
                if (isSimilar(nodes[a].in_adjacent[i]-1, nodes[b].in_adjacent[j]-1)){
                    found = true;
                }
            }
            if (!found){return false;}
        }
        for (int i=0; i<nodes[b].in_neighbours; i++) {
            bool found = false;
            for (int j=0; j<nodes[a].in_neighbours; j++) {
                if (isSimilar(nodes[b].in_adjacent[i]-1, nodes[a].in_adjacent[j]-1)){
                    found = true;
                }
            }
            if (!found){return false;}
        }
        //cout<<"condition parent for "<<a+1<<" "<<b+1<<endl;
        similar[a][b] = true;
        return true;
    }
    return false;
}

void DAG::similarPairs(){
    cout<<"\nSimilar node pairs: ";
    for (int i=0; i<numNodes; i++) {
        for (int j=0; j<numNodes; j++) {
            if (isSimilar(i, j)){
                cout<<"("<<nodes[i].value<<", "<<nodes[j].value<<") ";
            }
        }
    }
    cout<<endl;
}

void DAG::compute_closure_matrix(){
    // symmetric closure and reflexive
    for (int i=0; i<numNodes; i++) {
        for (int j=0; j<numNodes; j++) {
            if (similar[i][j]){
                similar[j][i] = 1;
            }
        }
        similar[i][i] = 1;
    }
    //transitive closure
    for (int k=0; k<numNodes; k++) {
        for (int i=0; i<numNodes; i++) {
            for (int j=0; j<numNodes; j++) {
                if (similar[i][k] && similar[k][j]){
                    similar[i][j] = 1;
                }
            }
        }
    }
}

void DAG::equivalance_class(){
    compute_closure_matrix();
    // Now the similarity matrix is transformed to a closure matrix
    bool part_of_class[numNodes] = {0};
    for (int i=0; i<numNodes; i++) {
        if (!part_of_class[i]){
            class_representative[no_of_equivalence_classes] = 0;
            for (int j=0; j<numNodes; j++) {
                if (similar[i][j]){
                    part_of_class[j] = 1;
                    nodes[j].equivalence_class_no = no_of_equivalence_classes;
                    equivalence_class_list[no_of_equivalence_classes][class_length[no_of_equivalence_classes]] = j;
                    class_length[no_of_equivalence_classes]++;
                    class_representative[no_of_equivalence_classes] = max(class_representative[no_of_equivalence_classes], nodes[j].value);
                }
            }
            no_of_equivalence_classes++;
        }
    }

    /* To print the detailed analysis of equivalence classes of this graph
    cout<<"No of equivalence classes: "<<no_of_equivalence_classes<<endl;
    cout<<"Representatives ";
    for (int i=0; i<no_of_equivalence_classes; i++) {
        cout<<class_representative[i]<<" ";
    }
    cout<<"\nThe classes"<<endl;
    for (int i=0; i<no_of_equivalence_classes; i++) {
        for (int j=0; j<class_length[i]; j++) {
            cout<<equivalence_class_list[i][j] + 1<<" ";
        }
        cout<<endl;
    }
    cout<<"The edges after collapsing"<<endl;
    */

    cout<<"\nCollapsed graph:\n"<<endl;
    cout<<no_of_equivalence_classes<<": ";
    for (int i=0; i<no_of_equivalence_classes; i++) {
        cout<<class_representative[i]<<" ";
    }
    cout<<endl;

    // Edges in the collapsed graph
    bool edge_present_between_classes[no_of_equivalence_classes][no_of_equivalence_classes] = {0};
    for (int i=0; i<numNodes; i++) {
        for (int j=0; j<nodes[i].out_neighbours; j++) {
            int class_of_j = nodes[nodes[i].out_adjacent[j] - 1].equivalence_class_no;
            int class_of_i = nodes[i].equivalence_class_no;
            if (class_of_i==class_of_j){
                continue;
            }
            int class_representative_of_i = class_representative[class_of_i];
            int class_representative_of_j = class_representative[class_of_j];
            if (!edge_present_between_classes[class_of_i][class_of_j]){
                cout<<class_representative_of_i<<" "<<class_representative_of_j<<endl;
            }
            edge_present_between_classes[class_of_i][class_of_j] = 1;
        }
    }

}
