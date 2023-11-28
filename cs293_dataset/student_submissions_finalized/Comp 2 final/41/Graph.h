#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#include <stdio.h>
#include <stdlib.h>
using namespace std;

template <typename T> class NewVector{
  T* array;
  int cap;

public:
  NewVector(){
    array = nullptr;
    cap = 0;
  }
  void push_back(T val){
    if(cap==0){
      array = new T[1];
      array[0] = val;
      cap = 1;
      return;
    }
    else{
      cap++;
      array = (T*) realloc(array, cap*sizeof(T));
      array[cap-1] = val;
      return;
    }
  }
  T pop(){
    if(cap==0) return nullptr;
    else if(cap == 1){
      cap = 0;
      array = nullptr;
    }
    else{
      T store = array[cap - 1];
      cap--;
      array = (T*) realloc(array, cap*sizeof(T));
      return store;
    }
    return nullptr;;
  }

  T return_max(){
    return array[cap-1];
  }
  int vector_size(){
    return cap;
  }
  T get_value_at_index(int val){
    if(0 <= val && val < cap) return array[val];
    else return nullptr;
  }
  int get_index_of_value(T val){
    for(int i = 0; i<cap; i++) if(array[i]==val) return i;
    return -1;
  }
};

class Node {
 public:
  int value;
  NewVector<Node*> startnode;
  NewVector<Node*> endnode;
};

class Graph {
  int numNodes;
  int numEdges;
  fstream graphFile;

  NewVector<Node*> nodes;
  
 public:
  Graph(string filename) {
    ifstream input_stream(filename);
    string raw;
    if(input_stream.is_open() == false){
      cerr << "Error";
      cerr << filename << endl;
      exit(0);
    }

    getline(filename,raw);
    int numNodes = stoi(raw), i = 0;
    while(i < numNodes){
      int j = i + 1;
      Node* new_noode =  new Node(j);
      if(new_noode != nullptr){
        if(nodes.get_index_of_value(new_noode) == -1){
          nodes.push_back(new_noode);
        }
      }
    }

    while(getline(filename,raw)){
      if (raw.find("-1 -1") == 0) break;
      stringstream tmp_string(raw);
      string e1, e2;
      tmp_string >> e1 >> e2;
      int a, b;
      a = stoi(e1) - 1;
      b = stoi(e2) - 2;
      Node* new_node1 = nodes.get_index_of_value(a);
      Node* new_node2 = nodes.get_index_of_value(b);

      if(new_node1 != nullptr && new_node2 != nullptr){
        if(nodes.get_index_of_value(new_node1) == -1 && nodes.get_index_of_value(new_node2) == -1){
          numEdges++
        }
      }
    }
    while(getline(filename,raw)){
      if (raw.find("-1 -1") == 0) break;
      stringstream tmp_string(raw);
      string e1, e2;
      tmp_string >> e1 >> e2;
      int a, b;
      a = stoi(e1) - 1;
      b = stoi(e2) - 2;
      Node* new_node1 = nodes.get_index_of_value(a);
      Node* new_node2 = nodes.get_index_of_value(b);

      if(new_node1 != nullptr && new_node2 != nullptr){
        if(nodes.get_index_of_value(new_node1.value) == -1 && nodes.get_index_of_value(new_node2.value) == -1){
          numEdges--;
        }
      }
    }
  }
      
  ~Graph() {
    if (graphFile.is_open()) {
      graphFile.close();
    }
    delete[] nodes;
  }

  // will add more functions for help
  void printResults();
};
