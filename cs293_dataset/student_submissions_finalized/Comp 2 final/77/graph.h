
#include "std_headers.h"
using namespace std;
// stores similar node pairs
class similar
{
public:
    int first_num, second_num;// node values
    bool checked;// helper variable used in the case of collapsing
    //constructors
    similar(){
        first_num=0;
        second_num=0;
        checked=false;
    }
    similar(int a, int b)
    {
        first_num = a;
        second_num = b;
        checked=false;
    }
};
// class edges stores final edges between the equivalence classes
class edges{
    public:
    int a,b;// nodes between which edge is present
    // constructors
    edges(){
        a=0;
        b=0;
    }
    edges(int a1, int b1)
    {
        a = a1;
        b= b1;
    }
};
class Node
{
public:
    int value;
    int *adjacent_out; // This is adjacent out list of node
    int *adjacent_in; // This is adjacent in list of node
    int count_of_adjacent_out; // this keeps count
    int count_of_adjacent_in; // this keeps count
    int partition_number;  // final partition number
    int max_number_from_partition;
    // Node constructor
    Node()
    {
        count_of_adjacent_out = 0;
        count_of_adjacent_in = 0;
        partition_number=-1;
        max_number_from_partition=-1;
    }
};
class Graph
{
    int numNodes;
    Node *nodes;
    fstream graphfile;
    similar* similar_node_storecase;
    int count_similar_node_storecse;
    int* is_in_partition;
    int no_partitions;
    edges* final_edges;
    int count_final_edges;
public:
    // Constructor which takes inputs
    Graph(string lp)
    {
        graphfile.open(lp,ios::out);
        int nNodes;
        // for number of nodes
        cin >> nNodes;
        // initialising defined field
        numNodes = nNodes;
        nodes = new Node[numNodes];
        is_in_partition=new int(numNodes);
        int no_partitions=0;
        final_edges=new edges[numNodes*numNodes];
        count_final_edges=0;
        similar_node_storecase=new similar[numNodes*numNodes];
        count_similar_node_storecse=1;
        if (nodes == nullptr)
        {
            cerr << "Memory allocation failure." << endl;
            exit(-1);
        }
        for (int i = 0; i < numNodes; i++)
        {
            nodes[i].value = i + 1;
            nodes[i].adjacent_out = new int(numNodes);
            nodes[i].adjacent_in = new int(numNodes);
            is_in_partition[i]=0;
        }

        // for edges
        while (true)
        {
            int a, b;
            cin >> a >> b;
            if (a == -1 && b == -1)
            {
                break;
            }
            nodes[a - 1].adjacent_out[nodes[a - 1].count_of_adjacent_out] = b;
            nodes[a - 1].count_of_adjacent_out++;
            nodes[b - 1].adjacent_in[nodes[b - 1].count_of_adjacent_in] = a;
            nodes[b - 1].count_of_adjacent_in++;
        }
        // for similar nodes by user
        while (true)
        {
            int a, b;
            cin >> a >> b;
            if (a == -1 && b == -1)
            {
                break;
            }
            similar *x = new similar(a, b);
            similar_node_storecase[count_similar_node_storecse].first_num=a;
            similar_node_storecase[count_similar_node_storecse].second_num=b;
            count_similar_node_storecse++;
        }
    }
    // Destructor
    ~Graph()
    {
        delete[] nodes;
    }
    // prints source nodes
    void print_sources();
    // prints similar node pairs
    void similar_node_pairs();
    // used ad dfs like recursive function
    void rec(int a, int b);
    // helper func
    bool is_already_present(int a, int b);
    // prints collapsed nodes
    void collapsed_graph();
    // helper func
    bool is_present_in_partition(int* partition,int size_part,int num);
    // helper func
    bool edge_already_present(int a,int b);
    // prints collapsed edges
    void collapsed_edges();
};
