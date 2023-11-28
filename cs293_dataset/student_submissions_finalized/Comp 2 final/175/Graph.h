#ifndef GRAPH_BST_H
#define GRAPH_BST_H

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif
using namespace std;

template <typename T> class list{ // a template class for linked list implementation
 public:
  T value;
  list *next;
  list(){
    value = -1;
    next = nullptr;
  }
  bool insert(T item){ // member function to insert into the linked list
    list<T> *foo = this;
    while(foo->value != -1){
      if (foo->value == item - 1) return false;
      foo = foo->next;
    }
    foo->value = item - 1;
    foo->next = new list<T>();
    return true;
  }
  bool find(T item){ // member function to search in the linked list
    list<T> *foo = this;
    while(foo->value != -1){
      if (foo->value == item - 1) return true;
      foo = foo->next;
    }
    return false;
  }
  int size(){ // returns the size
    list<T> *foo = this;
    int size = 0;
    while(foo->value != -1){
      size ++;
      foo = foo->next;
    }
    return size;
  }
  void print_list(T item, fstream &file){ // prins the list nicely
    list<T> *foo = this;
    while(foo->value != -1){
      file << " (" << item << ", " << foo->value + 1 << ")";
      foo = foo->next;
    }
  }
};

class Node { // the node class
 public:
  int value;
  int label; // to determine in which connected component this node belongs to
  list<int> *out_adj_list; // out adjacency list
  list<int> *in_adj_list; // in adjacency list
  list<int> *out_sim_list; // in similarity list
  list<int> *in_sim_list; // out similarity list
  Node(){
    label = 0;
    value = 0;
    out_adj_list = new list<int>();
    in_adj_list = new list<int>();
    out_sim_list = new list<int>();
    in_sim_list = new list<int>();
  }
};

class Graph {
  int vertices; // no. of vertices
  Node *nodes; // nodes array
  int *collapsed; // to determine what all nodes have collapsed
  int conn_comp; // no. of connected components
  
  bool verify(list<int> *list1, list<int> *list2){ // to determine if two non-source nodes are similar
    if (list1->size() == 0) return false;
    list<int> *foo1 = list1;
    while(foo1->value != -1){
      list<int> *sim1 = nodes[foo1->value].out_sim_list; // take the in-similarity list of every element in the 1st linked list
      list<int> *foo2 = list2;
      bool found = false;
      while(foo2->value != -1){
        if (sim1->find(foo2->value + 1)){ // check if it matches with any element in the 2nd list
          found = true;
          break;
        }
        foo2 = foo2->next;
      }
      if (!found) return false;
      foo1 = foo1->next;
    }
    return true;
  }

 public:
  Graph() {
    cin >> vertices;
    nodes = new Node[vertices];
    conn_comp = 0;
    collapsed = new int[vertices];
    for (int i = 0; i < vertices; i++){
      nodes[i].value = i + 1;
      collapsed[i] = 0;
    }
    int start, end;
    while(true){
      cin >> start >> end;
      if (start == -1 && end == -1) break; // keep reading until "-1 -1" is reached
      nodes[start - 1].out_adj_list->insert(end); // insert in adjacency lists
      nodes[end - 1].in_adj_list->insert(start);
    }
  }

  void print_src(fstream &file){ 
    file << "Source nodes:";
    for (int i = 0; i < vertices; i++){
      if (nodes[i].in_adj_list->value == -1){ // nodes having empty in-adjacency list
        file << " " << nodes[i].value;
      }
    }
    file << endl;
  }
  
  void print_similar(fstream &file){
    int one, two;
    while(true){
      cin >> one >> two;
      if (one == -1 && two == -1) break; // keep reading until "-1 -1" is reached
      if (nodes[one - 1].in_adj_list->value == -1 && nodes[two - 1].in_adj_list->value == -1){ // if they are indeed source, add them in similarity list
        nodes[one - 1].out_sim_list->insert(two);
        nodes[two - 1].in_sim_list->insert(one);
      }
    }
    for (int i = 0; i < vertices; i++){
      for (int j = 0; j < vertices; j++){
        if (i == j) continue;
        if (nodes[i].in_adj_list->size() == 1 && nodes[i].in_adj_list->find(nodes[j].value)){ // the 3rd case of similarity being checked here
          nodes[i].out_sim_list->insert(nodes[j].value);
          nodes[j].in_sim_list->insert(nodes[i].value);
        }
      }
    }
    while (true){
      bool found = false;
      for (int i = 0; i < vertices; i++){
        for (int j = 0; j < vertices; j++){
          if (i == j) continue;
          if (verify(nodes[i].in_adj_list, nodes[j].in_adj_list) && verify(nodes[j].in_adj_list, nodes[i].in_adj_list)){ // if their in-adjacency lists are similar in both ways
            if (nodes[i].out_sim_list->insert(nodes[j].value)){
              found = true;
              nodes[j].in_sim_list->insert(nodes[i].value); // add them in similarity lists
            }
          }
        }
      }
      if (!found) break;
    }
    file << "Similar node pairs:";
    for (int i = 0; i < vertices; i++){
      nodes[i].out_sim_list->print_list(nodes[i].value, file); // print out the entire list of similar nodes
    }
    file << endl;
  }

  void collapse(int index){ // basically dfs, helps to collapse/merge nodes
    collapsed[index] = 1;
    nodes[index].label = conn_comp; // update the label
    list<int> *foo = nodes[index].out_sim_list; // for out-similar list
    while(foo->value != -1){
      if (collapsed[foo->value] == 0) collapse(foo->value); // recursive calling
      foo = foo->next;
    }
    list<int> *foo1 = nodes[index].in_sim_list; // for in-similar list
    while(foo1->value != -1){
      if (collapsed[foo1->value] == 0) collapse(foo1->value); //recursive calling
      foo1 = foo1->next;
    }
  }

  void print_collapse(fstream &file){
    file << "Collapsed graph:" << endl << endl;
    int index = 0;
    while (index < vertices){
      if (collapsed[index] == 1) index ++;
      else{
        conn_comp ++;
        collapse(index); // calling dfs on all nodes which are not yet collapsed and updating the no. of connected components
      }
    }
    file << conn_comp << ":";
    int comp = 1;
    int arr_comp[conn_comp], arr1[conn_comp];
    while(comp <= conn_comp){
      for (int i = vertices - 1; i >= 0; i--){
        if (nodes[i].label == comp){
          arr_comp[comp - 1] = nodes[i].value; // storing the labels
          arr1[comp - 1] = nodes[i].value; // duplicate
          break;
        }
      }
      comp ++;
    }
    std::sort(arr1, arr1 + conn_comp); // used the stl function to sort
    for (int i = 0; i < conn_comp; i++){
      file << " " << arr1[i]; // printing out
    }
    file << endl;
    list<int> *bar[conn_comp]; // array of linked lists
    for (int i = 0; i < conn_comp; i++) bar[i] = new list<int>();
    for (int i = 0; i < vertices; i++){
      list<int> *foo = nodes[i].out_adj_list;
      while(foo->value != -1){ // inserting into the array of lists and printing the edges on the go, but in sorted fashion
        if (nodes[i].label != nodes[foo->value].label && bar[nodes[i].label - 1]->insert(nodes[foo->value].label)) file << arr_comp[nodes[i].label - 1] << " " << arr_comp[nodes[foo->value].label - 1] << endl;
        foo = foo->next;
      }
    }
  }

  ~Graph() { // releasing heap memory
    delete[] nodes;
    delete[] collapsed;
  }
};

#endif
