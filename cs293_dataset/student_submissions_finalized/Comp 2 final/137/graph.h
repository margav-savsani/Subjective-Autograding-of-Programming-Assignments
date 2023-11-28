#ifndef GRAPH_H
#define GRAPH_H

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

using namespace std;

template <typename T> class listOfObjects {
 public:
  T object;
  listOfObjects<T> *next;
  listOfObjects<T> *prev;
  
  // Constructor
  listOfObjects(T initValue) {object = initValue; next = prev = nullptr;}
  
  // Destructor
  ~listOfObjects() {;}
};

class Node {
 public:
  int value;        //stores the value of node
  listOfObjects<int> *adj = nullptr;        //adjacent list of the node
  listOfObjects<int> *parent = nullptr;     //parent list of the node
  bool source = true;       //checking of the node is a source node
};

class Graph{
    int numNodes;

    Node *nodes;
    listOfObjects<Node> *srcNodes;
    bool **similar1;
    listOfObjects<listOfObjects<int> *> *classes;

    public:
        Graph(){
            srcNodes = nullptr;
            cin>>numNodes;

            nodes = new Node[numNodes];     //initializing the nodes
            similar1 = new bool*[numNodes];
            for(int i=0; i<numNodes; i++)
            {
                similar1[i] = new bool[numNodes];
                for(int j=0; j<numNodes; j++)
                {
                    similar1[i][j] = false;
                }
            }
            classes = nullptr;
            if(nodes == nullptr)
            {
                cerr<<"Memory allocation failure."<<endl;
                exit(-1);
            }

            for(int i = 0; i<numNodes; i++)     //providing values to the nodes
            {
                nodes[i].value = i+1;
            }

            while(true)     //taking edge input from the user and adding edges between the defined nodes
            {
                int n1, n2;
                bool isPresent = false, isCycle = false;
                cin>>n1>>n2;

                if(n1 == -1 and n2 == -1)
                {
                    break;
                }
                
                n1 = n1-1;
                n2 = n2-1;

                listOfObjects<int> *a2 = nodes[n2].adj;
                while(a2 != nullptr)
                {
                    if(a2->object == n1)
                    {
                        isCycle = true;
                    }
                }
                if(isCycle)
                {
                    cout<<"Invalid input! "<<n2+1<<" already has a directed edge to "<<n1+1<<endl;
                }

                if(nodes[n1].adj == nullptr)
                {
                    nodes[n1].adj = new listOfObjects<int>(n2);
                    nodes[n2].source = false;
                }
                else
                {
                    listOfObjects<int> *a = nodes[n1].adj;
                    if(a->object == n2)
                    {
                        isPresent = true;
                    }
                    while(a->next != nullptr)
                    {
                        if(a->next->object == n2)
                        {
                            isPresent = true;
                            break;
                        }
                        a = a->next;
                    }
                    if(!isPresent)
                    {
                        a->next = new listOfObjects<int>(n2);
                        nodes[n2].source = false;
                    }
                }
                if(isPresent)
                {
                    cout<<"Directed edge already exists! Try again."<<endl;
                    continue;
                }
                if(!isPresent)
                {
                    if(nodes[n2].parent == nullptr)
                    {
                        nodes[n2].parent = new listOfObjects<int>(n1);
                        // similar1[n2][n1] = true;
                    }
                    else
                    {
                        // similar1[n2][n1] = false;
                        listOfObjects<int> *p = nodes[n2].parent;
                        while(p->next != nullptr)
                        {
                            p = p->next;
                        }
                        p->next = new listOfObjects<int>(n1);
                    }
                }
            }

        }

        ~Graph(){
            delete[] nodes;
        }

        void sourceNodes();     //function to print all the source nodes
        void similarInput();    //function to take similar nodes input from the user
        void printSimilar();        //function to print similar nodes
        void computeSimilar();      //function to compute similar nodes
        void BFS(int v);        //function to compute BFS
        void collapsedNodes();      //function to compute and print collapsed nodes
        void collapsedDFS(int v, bool *visited);        //function to compute equivalence classes of the similar relations using DFS
        int findMax(listOfObjects<int> *nums);      //function to find the max element in a list
        void printCollapsedEdges();     //function to print collapsed edges
        bool isPresent(int n, listOfObjects<int> *numbers);     //function to check if an element is present in the list
        int classOfNode(int n);     //function to return the collapsed edge of the equivalence class n is present in
        void printEqClass();        //function to print the equivalence class
};

#endif