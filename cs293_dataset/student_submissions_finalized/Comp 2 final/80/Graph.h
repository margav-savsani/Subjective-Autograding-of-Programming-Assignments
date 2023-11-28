#ifndef GRAPH_BST_H
#define GRAPH_BST_H

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef BST_H
#define BST_H
#endif
using namespace std;


class linked_list_node{
  public:
  int node_number;
  linked_list_node* next;
  linked_list_node* prev;
  linked_list_node(int t){
    next = nullptr;
    prev = nullptr;
    node_number=t;
  }
};


class linked_list{
  public:
  int length;
  linked_list_node* start;
  linked_list_node* end;
  linked_list(){
    start=nullptr;
    end = nullptr;
    length = 0;
  }

  void clear(){
    start = nullptr;
    end = nullptr;
    length = 0;
  }

  void insert(int n){
    if(length==0){
      start = new linked_list_node(n);
      end = start;
      length=1;
    }
    else{
      if(present(n)){
        return;
      }
      end->next=new linked_list_node(n);
      end->next->prev = end;
      end = end->next;
      length+=1;
    }
  }

  void remove(){
    if(length==0){
      return;
    }
    if(length==1){
      start = nullptr;
      end = nullptr;
    }
    else{
      start = start->next;
      start->prev = nullptr;
    }
    length-=1;
  }

  void find_and_remove(int n){
    if(length==0){
      return;
    }
    if(length==1 && start->node_number==n){
      start = nullptr;
      end = nullptr;
      length = 0;
      return;
    }
    else{
      linked_list_node* mark = start;
      while (mark!=nullptr){
        if(mark->node_number==n){
          if(mark->prev==nullptr){
            mark->next->prev = nullptr;
            start = mark->next;
          }
          else if(mark->next==nullptr){

            mark->prev->next = nullptr;
            end = mark->prev;
          }
          else{
            mark->next->prev = mark->prev;
            mark->prev->next = mark->next;
          }
          length-=1;
          break;
        }
        mark = mark->next;
      }
    }
  }


//checks if n present in list
  bool present(int n){
    linked_list_node* mark = start;
    while (mark!=nullptr){
      if(mark->node_number==n){
        return true;
      }
      mark = mark->next;
    }
    return false;
  }
};






class Node {
 public:
  int value;
  linked_list* adjacency_dest;
  linked_list* adjacency_src;
  linked_list* similar;

  
  Node(){
    adjacency_dest = nullptr;
    adjacency_src = nullptr;
    similar = nullptr;
  }

  void add_src_node(int n){
    if(adjacency_src==nullptr){
      adjacency_src = new linked_list;
      adjacency_src->insert(n);
    }
    else{
      adjacency_src->insert(n);
    }
  }

  void add_dest_node(int n){ //number n is the node number. In nodes array we will have to subtract 1 before accessing any node
    if(adjacency_dest==nullptr){
      adjacency_dest = new linked_list;
      adjacency_dest->insert(n);
    }
    else{
      adjacency_dest->insert(n);
    }
  }

  void add_similarity_node(int n){
    if(similar==nullptr){
      similar = new linked_list;
      similar->insert(n);
    }
    else{
      similar->insert(n);
    }
  }

//remove all connections of this node and n
  void remove_all_connections(int n){
    if(adjacency_dest!=nullptr){
      adjacency_dest->find_and_remove(n);
    }

    if(adjacency_src!=nullptr){
      adjacency_src->find_and_remove(n);
    }

    if(similar!=nullptr){
      similar->find_and_remove(n);
    }
  }

};




class Graph {

  int numNodes;

  Node *nodes;

  linked_list* source_nodes;
  linked_list* collapsed_nodes;
  Node **node_pointers;

  linked_list* final_collapsed_nodes;



  // Add appropriate fields as necessary for your implementation
  
 public:
  Graph() {
    source_nodes=new linked_list;
    collapsed_nodes = new linked_list;
    final_collapsed_nodes = new linked_list;
    
    cin >> numNodes;
    nodes = new Node[numNodes];
    
    if (nodes == nullptr) {
      cerr << "Memory allocation failure." << endl;
      exit(-1);
    }
    for (int i = 0; i < numNodes; i++) {
      nodes[i].value = i+1;
      collapsed_nodes->insert(i+1);
    }

    int n1=0, n2=-1;
    while(true){
      cin>>n1;
      cin>>n2;
      if(n1==-1){
        break;
      }

      Node* src_node = &nodes[n1-1];
      Node* dest_node = &nodes[n2-1];
      src_node->add_dest_node(n2);
      dest_node->add_src_node(n1);
    }


    for(int i =0; i<numNodes; i++){
      if(nodes[i].adjacency_src==nullptr){
        source_nodes->insert(nodes[i].value);
      }
    }
    while(true){
      cin >> n1;
      cin >> n2;
      if(n1==-1){
        break;
      }
      if(source_nodes->present(n1)&& source_nodes->present(n2)){
        Node* src_similar_node = &nodes[n1-1];
        src_similar_node->add_similarity_node(n2);
      }
    }
  }
      
  ~Graph() {
    delete[] nodes;
    // Add appropriate code as necessary for your implementation
  }

  // Add appropriate method declarations as necessary for your implementation

  void printSources();
  void fix_similar();
  void printSimilar();

  void take_closure_and_collapse();
  void print_collapsed();

};




#endif
