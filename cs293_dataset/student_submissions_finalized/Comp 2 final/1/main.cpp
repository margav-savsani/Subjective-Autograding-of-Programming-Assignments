#include "Graph.h"

//computing criteria 1
void compute_sim1(bool **Similarity, Graph &G, int a){
    Node *node = &G.nodes[a - 1];
    //only one incoming edge.
    //so similar to parent
    if(node->in_degree == 1){
        Similarity[a - 1][node->parents[0] - 1] = true;
        return;
    }
    return;
}
//functions for disjoint set unions to compute the symmetric, transitive closure of the relation

//root of the sub-tree (current equivalence class)
int find_root(int node, int *parents){
    if(parents[node] == node) return node;
    return find_root(parents[node], parents);
}
//fusing 2 classes/sub-trees. labels store the max values in the classes of the roots
void set_union(int node1, int node2, int *parents, int *labels){
    int root1 = find_root(node1, parents);
    int root2 = find_root(node2, parents);
    int max_label = max(labels[root1], labels[root2]);
    parents[root1] = root2;
    labels[root2] = max_label;
}
//label each node according to the max value in the class = label of the root
int* compute_labels(bool **Similarity, int n){
    int *parents = new int[n];
    int *labels = new int[n];
    for(int i = 0; i < n; i++){
        parents[i] = i; //initialize to each node in separate class
        labels[i] = i + 1;
    }
    //fuse 2 classes if relation between nodes from those 2
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            if(Similarity[i][j]) set_union(i, j, parents, labels);
        }
    }
    for(int i = 0; i < n; i++){
        labels[i] = labels[find_root(i, parents)];
    }
    return labels;
}

//computing criteria 2
//node b is ahead of a (or a) in the sort
void compute_sim2(bool **Similarity, Graph &G, int a, int b){
    //ofs << "------" << a << " " << b << endl;
    Node *node1 = &G.nodes[a - 1];
    Node *node2 = &G.nodes[b - 1];
    if(node1->in_degree == 0 || node2->in_degree == 0) return;
    //we have all similarity pair information for the parents of a, b in Similarity
    //since we move in the order of the topological sort

    //check if each parent of a similar to some parent of b
    for(int i = 0; i < node1->in_degree; i++){
        bool for_i = false;
        for(int j = 0; j < node2->in_degree; j++){
            if(Similarity[node1->parents[i] - 1][node2->parents[j] - 1]){
                //ofs << node2->parents[i] << " " << node1->parents[j] << endl;
                for_i = true;
                break;
            }
        }
        if(!for_i) return;
    }
    //check if each parent of b similar to some parent of a
    for(int i = 0; i < node2->in_degree; i++){
        bool for_i = false;
        for(int j = 0; j < node1->in_degree; j++){
            if(Similarity[node2->parents[i] - 1][node1->parents[j] - 1]){
                //ofs << node2->parents[i] << " " << node1->parents[j] << endl;
                for_i = true;
                break;
            }
        }
        if(!for_i) return;
    }
    Similarity[a - 1][b - 1] = true;
    Similarity[b - 1][a - 1] = true;
    //ofs << "(" << b << ", " << a << ") ";
    return;
}

int main(){
    /*string waste;
    cin >> waste;*/
    
    ofstream ofs("outgraph.txt");
    int numNodes;
    cin >> numNodes;
    //make the graph, relation matrix
    Graph G(numNodes);
    bool **Similarity = new bool *[numNodes];
    for(int i = 0; i < numNodes; i++){
        Similarity[i] = new bool[numNodes];
        for(int j = 0; j < numNodes; j++) Similarity[i][j] = false;
    }
    //add edges
    int start, end;
    while(cin >> start >> end){
        if(start == -1) break;
        //ofs << start << " " << end << endl;
        G.add_edge(start, end);
    }
    //add similarity info for sources
    while(cin >> start >> end){
        if(start == -1) break;
        Similarity[start - 1][end - 1] = true;
    }

    for(int i = 0; i < numNodes; i++){
        G.nodes[i].add_parents(G.adjacency, numNodes);
    }
    //printing the source nodes
    ofs << "Source nodes: ";
    for(int i = 0; i < numNodes; i++){
        if(G.nodes[i].in_degree == 0){
            ofs << i + 1 << " ";
        }
    }
    ofs << endl << endl;
    //sort Topologically
    DFS_graph(G);
    
    int *sorted = topological_sort(G);
    //compute the similarity relation matrix in order of the sort
    for(int i = 0; i < numNodes; i++){
        compute_sim1(Similarity, G, sorted[i]);
        for(int j = 0; j <= i; j++){ //all previous nodes
            compute_sim2(Similarity, G, sorted[j], sorted[i]);
        }
    }
    ofs << "Similar node pairs: ";
    for(int i = 0; i < numNodes; i++){
        for(int j = 0; j < numNodes; j++){
            if(Similarity[i][j]){
                ofs << "(" << i + 1 << ", " << j + 1 << ") ";
            }
        }
    }
    ofs << endl << endl;
    //compute classes of the nodes according to Similarity
    int *labels = compute_labels(Similarity, numNodes);

    int labels2[numNodes];
    for(int i = 0; i < numNodes; i++) labels2[i] = -1;
    int new_nodes = 0;
    for(int i = 0; i < numNodes; i++){
        if(labels2[labels[i] - 1] == -1){
            labels2[labels[i] - 1] = new_nodes;
            new_nodes++;
        }
    }
    ofs << "Collapsed graph:" << endl << endl << new_nodes << ": ";
    for(int i = 0; i < numNodes; i++){
        if(labels2[i] >= 0) ofs << i + 1 << " ";
    }
    ofs << endl;
    //for edges of the collapsed graph
    bool **adjacency2 = new bool*[new_nodes];
    for(int i = 0; i < new_nodes; i++){
        adjacency2[i] = new bool[new_nodes];
        for(int j = 0; j < new_nodes; j++){
            adjacency2[i][j] = false;
        }
    }

    for(int i = 0; i < numNodes; i++){
        for(int j = 0; j < numNodes; j++){
            if(G.adjacency[i][j]){
                //if new edge in the collapsed graph discovered, print it
                if(labels[i] != labels[j] && !adjacency2[labels2[labels[i] - 1]][labels2[labels[j] - 1]]){
                   ofs << labels[i] << " " << labels[j] << endl;
                   adjacency2[labels2[labels[i] - 1]][labels2[labels[j] - 1]] = true;
                }
            }
        }
    }
}