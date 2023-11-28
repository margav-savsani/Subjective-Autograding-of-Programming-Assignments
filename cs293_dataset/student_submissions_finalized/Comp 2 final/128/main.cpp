#include<iostream>
#include<fstream>
using namespace std;


class Node{
    public: 
    int value;
    int out_deg;
    int in_deg;
    Node** in_adjacency;
    Node** out_adjacency;

    Node(int val = 0){
        value = val;
        out_adjacency = NULL;
        in_adjacency = NULL;
        out_deg = 0;
        in_deg = 0;
    }
};

struct tup
{
    Node* a;
    Node* b;
};

class Graph{
    public:

    int num_nodes;
    Node** adjacency_lists;

    Graph(int num = 0){
        num_nodes = num;
        adjacency_lists = new Node*[num_nodes];
        for(int i = 0; i < num_nodes; i++){
            adjacency_lists[i] = new Node(i+1);
            adjacency_lists[i]->out_adjacency = new Node*[num_nodes];
            adjacency_lists[i]->in_adjacency = new Node*[num_nodes];
        }
    }

    void new_edge(int from, int to){
        adjacency_lists[from-1]->out_adjacency[adjacency_lists[from-1]->out_deg] = adjacency_lists[to-1];
        adjacency_lists[from-1]->out_deg++;
        adjacency_lists[to-1]->in_adjacency[adjacency_lists[to-1]->in_deg] = adjacency_lists[from-1];
        adjacency_lists[to-1]->in_deg++;
    }

    int add_prospective(tup* my_array, int my_array_size, int s1, int s2);
    
    bool check(tup t, bool* main_table){

        for( int i = 0; i < t.a->in_deg; i++){
            bool flag = false;
            for(int j = 0; j < t.b->in_deg; j++){
                bool to_check = 
                main_table[((t.a->in_adjacency[i]->value)-1)*num_nodes + (t.b->in_adjacency[j]->value)-1];
                flag = flag || to_check;
            }
            if(!flag){return false;}
        }

        for( int i = 0; i < t.b->in_deg; i++){
            bool flag = false;
            for(int j = 0; j < t.a->in_deg; j++){
                bool to_check = 
                main_table[((t.b->in_adjacency[i]->value)-1)*num_nodes + (t.a->in_adjacency[j]->value)-1];
                flag = flag || to_check;
            }
            if(!flag){return false;}
        }
        return true;
    }
};


int Graph::add_prospective(tup* my_array, int my_array_size, int s1, int s2){
    int new_size = my_array_size;
    for(int i =0 ; i< adjacency_lists[s1-1]->out_deg; i++){
        for(int j = 0; j< adjacency_lists[s2-1]->out_deg; j++){
            my_array[my_array_size] = {adjacency_lists[s1 - 1]->out_adjacency[i], adjacency_lists[s2 - 1]->out_adjacency[j] };
            new_size = add_prospective(my_array, my_array_size+1, my_array[my_array_size].a->value, my_array[my_array_size].b->value);  
        }
    }
    return new_size;
}


int main(){
    fstream file;
    file.open("outgraph.txt", ios::out);
    int num_nodes;

    int n1, n2;
    

    cin >> num_nodes;
    cin >> n1 >> n2;

    Graph G(num_nodes);
    while(n1 != -1){
        //store the edge;
        G.new_edge(n1, n2);
        cin >> n1 >> n2;
    }

    bool main_table[num_nodes][num_nodes] = {};
    tup prospectives[num_nodes*num_nodes];
    int num_prospective = 0;


    int s1, s2;
    cin >> s1 >> s2;

    while(s1 != -1){
        main_table[s1-1][s2-1] = true;
        num_prospective = G.add_prospective(prospectives, num_prospective, s1,s2);
        cin >> s1 >> s2;
    }


    file << "Source Nodes: ";
    for(int i = 0; i< num_nodes; i++){
        if(G.adjacency_lists[i]->in_deg == 0){
            file << G.adjacency_lists[i]->value << " ";
        }
        else if(G.adjacency_lists[i]->in_deg == 1){
            main_table[G.adjacency_lists[i]->value - 1][G.adjacency_lists[i]->in_adjacency[0]->value - 1] = true;
        }
    }
    file << endl << endl;

    //sanity check
    // for(int i=0; i < num_prospective; i++){
    //     file << prospectives[i].a->value << " " << prospectives[i].b->value << endl;
    // }

    for(int i = 0; i < num_prospective; i++){
        if (G.check(prospectives[i], &main_table[0][0]) ){
            main_table[prospectives[i].a->value - 1][prospectives[i].b -> value -1] = true;

            for(int j =0; j < i; j++){
                if(! main_table[prospectives[j].a->value - 1][prospectives[j].b->value - 1]){
                    main_table[prospectives[j].a->value - 1][prospectives[j].b->value - 1]
                     = G.check(prospectives[j], &main_table[0][0]);
                }
            }

        }

        else{
            main_table[prospectives[i].a->value - 1][prospectives[i].b -> value -1] = false;
        } 

    }
    
    file << "Similar node pairs: ";
    for(int i = 0; i < num_nodes; i++){
        for(int j = 0; j < num_nodes; j++){
            if(main_table[i][j]){
                file << "(" << i+1 << ", " << j+1 << ") ";
            }
        }
    }
    file << endl << endl;


    int adj_matrix[num_nodes][num_nodes] = {};
    for(int i = 0; i < num_nodes; i++){
        for(int j = 0; j < G.adjacency_lists[i]->out_deg; j++){
            adj_matrix[i][G.adjacency_lists[i]->out_adjacency[j]->value - 1] = 1;
        }
    }

    int auxiliary[num_nodes] = {};
    for(int i = 0; i < num_nodes; i++){
        auxiliary[i] = -1;
    }

    for(int i = 0; i < num_nodes; i++){
        for(int j = 0; j < num_nodes; j++){

            if(main_table[i][j]){
                int index_1 = i, index_2 = j;
                while(auxiliary[index_1] != -1){
                    index_1 = auxiliary[index_1];
                }
                while(auxiliary[index_2] != -1){
                    index_2 = auxiliary[index_2];
                }
                                
                if(index_2 > index_1){
                    auxiliary[index_1] = index_2;
                    for(int k = 0; k < num_nodes; k++){
                        adj_matrix[index_2][k] = adj_matrix[index_1][k] || adj_matrix[index_2][k]; 
                    }
                    for(int k = 0; k < num_nodes; k++){
                        adj_matrix[k][index_2] = adj_matrix[k][index_1] || adj_matrix[k][index_2]; 
                    }
                }
                if(index_1 > index_2){
                    auxiliary[index_2] = index_1;
                    for(int k = 0; k < num_nodes; k++){
                        adj_matrix[index_1][k] = adj_matrix[index_2][k] || adj_matrix[index_1][k]; 
                    }
                    for(int k = 0; k < num_nodes; k++){
                        adj_matrix[k][index_1] = adj_matrix[k][index_2] || adj_matrix[k][index_1]; 
                    }
                }
            }
        }
    }

    int count = 0;
    for(int i = 0; i < num_nodes; i++){
        if(auxiliary[i] == -1){
            count++;
        }
    }
    file<<"Collapsed graph:\n\n";
    file << count << ": ";
    for(int i = 0; i < num_nodes; i++){
        if(auxiliary[i] == -1){
            file << i+1 << " ";
        }
    }
    file << endl;
    
    for(int i = 0; i < num_nodes; i++){
        if(auxiliary[i] == -1){
            for(int j = 0;  j < num_nodes; j++){
                if(adj_matrix[i][j] == 1 && auxiliary[j] == -1 && j != i){
                    file << i+1 << " " << j+1 << endl;
                }
            }
        }
    }
} 
