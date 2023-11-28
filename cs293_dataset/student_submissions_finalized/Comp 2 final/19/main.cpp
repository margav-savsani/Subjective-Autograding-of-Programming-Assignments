#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string>
#include <vector>
#include <sstream>
#include <cstring>
#include <cctype>
using namespace std;

struct set{
    public:

    int a; int b;
    set(){
        a = -1, b = -1;
    }
    set(int p, int q){
        a = p; b = q;
    }
};

class Node
{
public:
  int value;
  vector<int> out_nodes; // storing values not index
  vector<int> in_nodes;  // storing values not index
  vector<int> similar;   // storing values not index

  Node(){
    value = -1;
  }
  Node(int v){
    value = v;
  }
};

class Graph
{
    public:
    int numNodes;
    Node *nodes;
    bool *visited;
    int total_visit;
    vector<set> similar_relations; // to store all the similar relations
    vector<set> edges;

    Graph(int N){
        numNodes = N;
        nodes = new Node[numNodes];
        visited = new bool[numNodes];
        total_visit = 0;
        for(int i = 0; i < numNodes ; i++){
            nodes[i].value = i+1;
            visited[i] = false;
        }
    }
    void insert(int a, int b){
        nodes[a-1].out_nodes.push_back(b);
        nodes[b-1].in_nodes.push_back(a);
    }
};

int main(int argc, char **argv){
    Graph *myGraph;
    int num;
    cin >> num;
    myGraph = new Graph(num);
    int a,b;
    cin >> a; cin >> b;
    ofstream cerr;
    string out = "outgraph.txt";
    cerr.open(out);
    
    while (a != -1 && b!= -1){
        myGraph->insert(a,b);
        cin >> a; cin >> b;
        set new_edge = set(a,b); // storing values
        myGraph->edges.push_back(new_edge); 
    }

    cerr<<"Source nodes:" ;
    for(int i = 0; i < num; i++){
        if(myGraph->nodes[i].in_nodes.size() == 0){
            myGraph->visited[i] = true;
            myGraph->total_visit ++;
            cerr<< " " << i+1 ;
        }
    }

    // for case - 1
    cerr<< endl << endl;;
    cin >> a; cin >> b;
    cerr<< "Similar node pairs:" ;                  // UNCOMMENT AT LAST
    while(a != -1 && b!= -1){
        myGraph->nodes[a-1].similar.push_back(b);
        // myGraph->nodes[b-1].similar.push_back(a);
        int c = myGraph->nodes[a-1].in_nodes.size();
        int d = myGraph->nodes[b-1].in_nodes.size();
        if(c == 0 && d == 0){
            set new_similar = set(a,b);   //if both are source nodes
            cerr<< " ("<< a << ", " << b << ")" ;    // UNCOMMENT AT LAST
            myGraph->similar_relations.push_back(new_similar);
        }
        cin >> a; cin >> b;
    }

    // for case - 2
    while (myGraph->total_visit != myGraph->numNodes){
        vector<int> initializer;
        int N = myGraph->numNodes;
        for(int i =0; i < N; i++){
            if(myGraph->visited[i]){
                initializer.push_back(i+1); //storing only values not index
            }
        }
        // got all the initializer nodes
        // collect all the children of the initailzers
        vector<int> children;
        for(int i = 0; i < initializer.size(); i++){
            int initial = initializer[i]; // stored as a value
            int size = myGraph->nodes[initial - 1].out_nodes.size();
            for(int j = 0; j < size; j++){
                int child = myGraph->nodes[initial-1].out_nodes[j]; // got  the value of the child
                if(!myGraph->visited[child-1]){
                    // have to insert in children only if it is not visited
                    // another condition is that it's parents should only be from initializer
                    int parents_size = myGraph->nodes[child-1].in_nodes.size();
                    int parent_count = 0;
                    for(int k = 0; k < parents_size ; k++){
                        // have to check this parent is in initializer or not
                        int parent = myGraph->nodes[child-1].in_nodes[k];
                        for(int l = 0; l < initializer.size(); l++){
                            if(parent == initializer[l]){
                                parent_count++;
                            }
                        }
                    }
                    // we have to add this child if parent_count is parent_size
                    if(parent_count == parents_size){
                        // have to add this child  only if it is not present in children
                        int chidren_size = children.size();
                        bool present = false;
                        for(int i =0; i < chidren_size; i++){
                            if(child == children[i]){
                                present = true;
                            }
                        }
                        if(present == false){
                            children.push_back(child);
                        }
                    }
                }
            }
        }
        // finally got the children.
        
        // have to check similar relations with these children
        int n = children.size();
        for(int i = 0; i < n; i++){
            for(int j = 0; j < n; j++){
                int a = children[i]; int b = children[j];
                
                // if (a,b) is a relation don't do anything
                bool present_ = false;
                int sim_size = myGraph->similar_relations.size();
                for(int i = 0; i < sim_size; i++){
                    int p = myGraph->similar_relations[i].a;
                    int q = myGraph->similar_relations[i].b;
                    if(a == p && b == q){
                        present_ = true;
                    }
                }
                if(!present_){
                        int incoming_1 = myGraph->nodes[a-1].in_nodes.size();
                        int incoming_2 = myGraph->nodes[b-1].in_nodes.size();

                        int found_1 = 0;
                        int found_2 = 0;
                        for(int w = 0; w < incoming_1; w++){
                            int m1 = myGraph->nodes[a-1].in_nodes[w];    // got the value of the parent

                            // from parent go to the similar relations
                            int sim_parent_size = myGraph->nodes[m1-1].similar.size();
                            // got the no. of m1 --> x relations where m1 is the parent of a
                            bool found = false;
                            for(int x = 0; x < sim_parent_size; x++){ // going through all the relations
                                int m2 = myGraph->nodes[m1-1].similar[x]; // got one relation
                                // have to check whether b is a child of m2
                                int m2_child_size = myGraph->nodes[m2-1].out_nodes.size();
                                for(int y = 0; y < m2_child_size; y++){
                                    int m2_child = myGraph->nodes[m2-1].out_nodes[y];
                                    if(m2_child == b){
                                        found = true;
                                    }
                                } 
                            }
                            if(found){
                                found_1 ++;
                            }
                        }
                        for(int w = 0; w < incoming_2; w++){
                            int m1 = myGraph->nodes[b-1].in_nodes[w]; // got the value of the parent

                            // from parent go to the similar relations
                            int sim_parent_size = myGraph->nodes[m1-1].similar.size();
                            // got the no. of m1 --> x relations where m1 is the parent of a
                            bool found = false;
                            for(int x = 0; x < sim_parent_size; x++){ // going through all the relations
                                int m2 = myGraph->nodes[m1-1].similar[x]; // got one relation
                                // have to check whether b is a child of m2
                                int m2_child_size = myGraph->nodes[m2-1].out_nodes.size();
                                for(int y = 0; y < m2_child_size; y++){
                                    int m2_child = myGraph->nodes[m2-1].out_nodes[y];
                                    if(m2_child == a){
                                        found = true;
                                    }
                                } 
                            }
                            if(found){
                                found_2 ++;
                            }
                        }
                        if(found_1 == incoming_1 && found_2 == incoming_2){
                            if(a != b){
                                set new_similar = set(a,b);
                                myGraph->nodes[a-1].similar.push_back(b);
                                myGraph->nodes[b-1].similar.push_back(a);
                                cerr<< " ("<< a << ", " << b << ")" ;    // UNCOMMENT AT LAST
                                set new_similar2 = set(b,a);
                                cerr<< " ("<< b << ", " << a << ")" ;    // UNCOMMENT AT LAST 
                                myGraph->similar_relations.push_back(new_similar);
                                myGraph->similar_relations.push_back(new_similar2);
                            }
                            else{
                                set new_similar = set(a,b);
                                myGraph->nodes[a-1].similar.push_back(b);
                                cerr<< " (" << a << ", " << b << ")";
                                myGraph->similar_relations.push_back(new_similar);
                            }
                        }
                }
            }   
        }  

        int child_sz = children.size();
        for(int i = 0; i < child_sz; i++){
            int val = children[i];
            myGraph->visited[val-1] = true;
        }
        int c = 0;
        for(int i =0; i < myGraph->numNodes; i++){
            if(myGraph->visited[i]){
                c++;
            }
        }
        myGraph->total_visit = c;
    }

    // for case - 3
    for(int i = 0; i < num; i++){
        int no_of_incoming = myGraph->nodes[i].in_nodes.size();
        int no_of_outgoing = myGraph->nodes[i].out_nodes.size();
        
        if(no_of_incoming == 1){
            int b = myGraph->nodes[i].in_nodes.front();
            set new_similar = set(i+1,b);
            cerr<< " ("<< i+1 << ", " << b << ")" ;    // UNCOMMENT AT LAST
            myGraph->similar_relations.push_back(new_similar);
        }
    }
    cerr<< endl;

    // ******* for compression ******* //
    vector<int> vertices;
    for(int i =0 ; i < myGraph->numNodes; i++){
        vertices.push_back(i+1); // storing values not vertices
    }
    int sz = myGraph->similar_relations.size();

    for(int i = 0; i < sz; i++){
        int a = myGraph->similar_relations[i].a;
        int b = myGraph->similar_relations[i].b;
        int c;
        if(a > b){
            c = a;
        }
        else{
            c = b;
        }
        for(int j = 0; j < myGraph->numNodes; j++){
            if(vertices[j] == a || vertices[j] == b){
                vertices[j] = c;
            }
        }
        for(int j = 0; j < myGraph->similar_relations.size(); j++){
            int p = myGraph->similar_relations[j].a;
            int q = myGraph->similar_relations[j].b;
            if(p == a || p == b){
                myGraph->similar_relations[j].a = c;
            }
            if(q == a || q == b){
                myGraph->similar_relations[j].b = c;
            }
        }
        for(int j = 0; j < myGraph->edges.size(); j++){
            int p = myGraph->edges[j].a;
            int q = myGraph->edges[j].b;
            if(p == a || p == b){
                myGraph->edges[j].a = c;
            }
            if(q == a || q == b){
                myGraph->edges[j].b = c;
            }
        }
    }

    vector<int> final_vertices;
    for(int i = 0; i < myGraph->numNodes; i++){
        bool found = false;
        int insert = vertices[i];
        for(int j = 0; j < final_vertices.size(); j++){
            if(final_vertices[j] == insert){
                found = true;
            }
        }
        if(!found){
            final_vertices.push_back(insert);
        }
    }

    vector<set> final_edges;
    for(int i =0; i < myGraph->edges.size(); i++){
        bool found = false;
        set insert = myGraph->edges[i];
        for(int j=0; j < final_edges.size(); j++){
            if(insert.a == final_edges[j].a && insert.b == final_edges[j].b){
                found = true;
            }
        }
        if(!found){
            if(insert.a != -1  && insert.b != -1 && insert.a != insert.b){
                final_edges.push_back(insert);
            }
        }
    }

    cerr<< "\nCollapsed graph:" << endl;
    cerr<< endl;
    cerr<< final_vertices.size() << ": ";
    for(int i = 0; i < final_vertices.size(); i++){
        cerr<< final_vertices[i] << " ";
    }
    cerr<< endl;

    for(int j = 0; j < final_edges.size(); j++){
        cerr<< final_edges[j].a << " " << final_edges[j].b << "\n"; 
    }
    return 0;
}