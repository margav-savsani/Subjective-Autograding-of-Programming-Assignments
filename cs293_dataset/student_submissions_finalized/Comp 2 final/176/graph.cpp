#include <iostream>
using namespace std;

#include "graph.h"


// reads the graph from input
// and also prints out the source nodes in the graph
void Graph::read_and_sources() {
    int a, b;
    cin >> numOfVertices;
    vertices = new Node*[numOfVertices];        // the graph for the vertices given
    sim_vertices = new Node*[numOfVertices];    // the graph built from similar vertices only

    // initialising all the vertices or nodes of graphs
    for(int i=0; i<numOfVertices; i++){
        vertices[i] = new Node(i+1);
        sim_vertices[i] = new Node(i+1);
    }
        
    // reading the edges
    while(true) {
        cin >> a >> b;
        if(a == -1 && b == -1)      // end of input
            break;
        vertices[a-1]->to.insert(vertices[b-1]);
        vertices[b-1]->from.insert(vertices[a-1]);
    }
    

    // printing the source nodes
    out << "Source nodes:";
    for(int i=0; i<numOfVertices; i++) {
        if((vertices[i]->from).size() == 0){
            out << " " << i+1; 
            sources.insert(vertices[i]);    // storing all the source nodes
        } 
    }
    out << endl << endl;
}


// finds and prints all the similar nodes in the graph based on given user inputs
void Graph::find_similar() {
    set<Tuple> all;    // an ordered tuple of all similar nodes

    int a, b;
    while(true) {
        cin >> a >> b;
        if(a == -1 && b == -1)
            break;
        vertices[a-1]->similar.insert(vertices[b-1]);       // a similar to b
        all.insert(Tuple(vertices[a-1],vertices[b-1]));     // insert the paair into set
    }

    set<Node *> parent = sources;   // nodes at current level
    set<Node *> children;           // nodes being pointed to by parents
    
    // starting at the sources and moving down the tree level by level
    while(parent.size() != 0){
        // finding all the children
        for(auto i: parent){
            for(auto j: i->to){
                if((j->from).size() == 1){      // condition 3 of similar nodes
                    j->similar.insert(i);
                    all.insert(Tuple(j,i));
                }
                children.insert(j);
            }
        }

        // iterating through every child
        for(auto i: children){
            // comparing with every possible pair for similarity
            for(auto j: children){
                bool sim_tot = true;    // if similarity valid for every parent of i

                // checking if parent similar to some parent of j
                for(auto m: i->from){
                    bool sim = false;   // if current parent of i valid for similarity or not
                    for(auto n: j->from){
                        if(m->similar.find(n) != m->similar.end()){     // some parent of j is similar to current parent of i
                            sim = true;
                            break;
                        }
                    }
                    if(!sim){       // if no similar parent found
                        sim_tot = false;
                        break;
                    }
                }
                if(sim_tot){    // if all parents of i satisfying similarity property
                    i->similar.insert(j);
                }
            }
        }

        // checking the vice-versa of condition 2 of similarity
        for(int i=0; i<numOfVertices; i++){
            set<Node *> not_sim;    // nodes not satisfying vice-versa

            for(auto j: vertices[i]->similar){
                if(all.find(Tuple(vertices[i], j)) != all.end())    // similar by condition 1 or 3
                    continue;
                if(j->similar.find(vertices[i]) != j->similar.end())    // vice-versa satisfied
                    all.insert(Tuple(vertices[i], j));
                else                                                    // vice-versa not satisfied
                    not_sim.insert(j);
            }
            for(auto j: not_sim)
                vertices[i]->similar.erase(j);      // deleting similar nodes not satisfying vice-versa consition
        }

        // preparing for next level of iteration
        parent = children;
        children.clear();
    }

    // printing the pairs of similar nodes
    out << "Similar node pairs:";
    for(auto i: all){
        sim_vertices[i.a->value-1]->adj.insert(vertices[i.b->value-1]);
        sim_vertices[i.b->value-1]->adj.insert(vertices[i.a->value-1]);
        out << " (" << i.a->value << ", " << i.b->value << ")";
    }
    out << endl << endl;
}


// performing dfs to find out the highest node value after collapsing for each node
int Graph::DFS(int i, bool visited[]) {
    visited[i] = true;
    int val = i+1;      // value of current node
    for(auto j: sim_vertices[i]->adj){
        if(!visited[j->value - 1])
            val = max(val, DFS(j->value -1, visited));  // possibly higher value
    }
    
    return val;     // the maximum value till now
}


// collapses the similar nodes according to given condition
// and prints the collapsed graph
void Graph::collapse() {
    num_collapsed = 0;
    collapsed = new Node*[numOfVertices];

    set<int> values;    // the highest node values for each connected component

    bool *visited = new bool[numOfVertices];    // for dfs

    for(int i=0; i<numOfVertices; i++){
        for(int j=0; j<numOfVertices; j++)
            visited[j] = false;
        vertices[i]->collapsed_value = DFS(i, visited);     // the maximum node value in its connected component
        values.insert(vertices[i]->collapsed_value);
    }
    delete[] visited;

    // initialising the collapsed graph nodes
    for(auto i: values){
        collapsed[i-1] = new Node(i);
        num_collapsed++;
    }

    // building the edges of the collapsed graph
    for(int i=0; i<numOfVertices; i++){
        for(auto j: vertices[i]->to){
            if(vertices[i]->collapsed_value != j->collapsed_value)      // self-nodes not included
                collapsed[vertices[i]->collapsed_value -1]->to.insert(collapsed[j->collapsed_value -1]);
        }
    }

    // printing the collapsed graph
    out << "Collapsed graph:\n\n" << num_collapsed << ":";
    for(auto i: values)
        out << " " << i;
    out << endl;
    for(auto i: values){
        for(auto j: collapsed[i-1]->to){
            out << i << " " << j->value << endl;
        }
    }
}