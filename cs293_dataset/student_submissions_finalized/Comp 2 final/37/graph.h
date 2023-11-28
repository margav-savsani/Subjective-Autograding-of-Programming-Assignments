
#include <stdlib.h>
#include <iostream>

#include <string>
#include <fstream>

#include <iostream>
#include <cstdlib>
using namespace std;
 


class listofnodes{ //a list of nodes
public: 
  int index;
  listofnodes *next;
  listofnodes() : index(-1),next(nullptr){};
  listofnodes(int v) :index(v),next(nullptr){};
};



class listofedges{
public:
  int to,from;
  listofedges *next;
  listofedges() : to(-1),from(-1),next(nullptr){};
  listofedges(int v,int m) :to(m),from(v),next(nullptr){};
};

class Node
{
public:
  int value,n_to,n_from,time;
  
  listofnodes * to,*from,*last_from,*last_to;
  Node() : value(0),n_to(0), n_from(0),time(-1),to(nullptr),from(nullptr),last_from(nullptr),last_to(nullptr){}

};

class Node1
{
public:
  int value,nadjacent,time;
  
  listofnodes * adjacent,*last;
  Node1() : value(0),nadjacent(0), time(-1),adjacent(nullptr),last(nullptr){}

};

class listofnodes1{
public:
  Node1 * v;
  listofnodes1 *next;
  listofnodes1() : v(nullptr),next(nullptr){};
  listofnodes1(Node1 * v1) :v(v1),next(nullptr){};
};

class Edge{   //a class to represent the edges
public:
  int v1,v2;
  Edge() : v1(-1),v2(-1){};
  Edge(int a,int d): v1(a),v2(d){};
};

 

class ugraph{  //undirected graph made using the similar node pair as edges
  int numNodes;
  int numEdges;
  bool * visited;
  listofnodes1 *nodes;
  listofedges *edges;
public:
  ugraph(int numNodes,bool**  is_similar){
    for(int i=0; i< numNodes;i++)
    {
      for(int j=0; j< numNodes;j++){
        if(is_similar[i][j] || is_similar[j][i] ){
          if (nodes==nullptr){
            nodes=new listofnodes1();
          }
        }
      }

    }


  }
};

class Graph
{
  int numNodes; //number of nodes
  int numEdges; // number of edges

  bool * visited;
  Node *nodes; // array of nodes
  Edge *edges; //array of edges
  bool* issource; //array of bools ,true if a node is a source node
  bool**  is_similar,**is_checked; //2D boolean arrays
public:
  Graph()
  {
    ofstream f;
    f.open("outGraph.txt");
    cin>>numNodes;
    
    int from,to,i=0;
    listofedges * edges_=nullptr,*last=nullptr;
    nodes= new Node[numNodes];
    issource=new bool[numNodes];
    visited= new bool[numNodes];
    for(int j=0 ; j< numNodes ; j++){
        issource[j]=true;
        nodes[i].value=i+1;
        visited[i]=false;
    }
    
    while(cin>>from>>to  && from!=-1 && to !=-1){   //initialising the edges
      i++;
      issource[to-1]=false;
      listofedges* temp=new listofedges(from,to);
      if(edges_==nullptr){
        edges_=temp;
        last=edges_;
      }
      else{
        last->next=temp;
        last=temp;
      }               
    }
    numEdges=i;
 
    edges=new Edge[numEdges];
    listofedges *curr=edges_;
    is_similar=new bool*[numNodes];
    is_checked=new bool*[numNodes];

    for(int i=0 ; i <numNodes; i++){    
      is_similar[i]=new bool[numNodes];
      is_checked[i]=new bool[numNodes];
      for(int j=0 ; j <numNodes ; j++){
        is_similar[i][j]=false;
        is_checked[i][j]=false;
      }
    }
    for(int i=0 ; i <numEdges; i++){   //initialising the to and from lists in the nodes.
       
      from=curr->from;
      to=curr->to;
      
      edges[i]= *(new Edge(curr->from,curr->to));
      nodes[from-1].n_to+=1;
      nodes[to-1].n_from+=1;
      
      if(nodes[from-1].to == nullptr){
        nodes[from-1].to=new listofnodes(to);
        nodes[from-1].last_to=nodes[from-1].to;
      }
      else {
        nodes[from-1].last_to->next=new listofnodes(to);
        nodes[from-1].last_to=nodes[from-1].last_to->next;
      }
      if(nodes[to-1].from == nullptr){
        nodes[to-1].from=new listofnodes(from);
        nodes[to-1].last_from=nodes[to-1].from;
      }
      else {
        nodes[to-1].last_from->next=new listofnodes(from);
        nodes[to-1].last_from=nodes[to-1].last_from->next;
      }
      curr=curr->next;
    }
    
    if (nodes == nullptr)
    {
      cerr << "Memory allocation failure." << endl;
      exit(-1);
    }
    while(cin>>from>>to  && from!=-1 && to !=-1){ //checking similarity using first condition
      
      is_similar[from-1][to-1]=true;
      is_checked[from-1][to-1]=true;

    }
    for(int i=0 ; i <numNodes; i++){    //checking similarity using third condition
      if(nodes[i].n_from==1){
        is_similar[i][nodes[i].from->index-1]=true;
        is_checked[i][nodes[i].from->index-1]=true;

      }


    }

    for(int i=0 ; i <numNodes; i++){    //checking similarity using second condition
      for(int j=0; j<numNodes ; j++){
        check_c2(i,j);   //checks if (i,j) are similar
      }
    }

    f<< "Source Nodes: ";
    for(int i=0 ; i <numNodes; i++){
      if(issource[i]) f<<i+1<<" ";
    }
    f<<endl;
    f<<endl;
    f<<"Similar node pairs: ";
    for(int i=0 ; i <numNodes; i++){
      for(int j=0; j<numNodes ; j++){
        if(is_similar[i][j]) f<<"(" << i+1 <<" , " << j+1 <<") ";

      }

    } 
    f<<endl;
    f<<endl;
    f<<"collapsed graph: ";
  }

  ~Graph()
  {

    
    
  }

  // Add appropriate method declarations as necessary for your implementation

  bool check_c2(int in,int out);
  void printResults();
};

