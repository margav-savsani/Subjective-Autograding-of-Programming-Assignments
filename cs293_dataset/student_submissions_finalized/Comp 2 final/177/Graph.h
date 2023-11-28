#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cmath>

template<typename T> class CustomVector{
  T* arr = nullptr;
  int size = 0;

  public:

  void push_back(T obj){
    if (arr == nullptr) {arr = new T[1]; arr[0] = obj; size++; return;}
    else {arr = (T*) realloc(arr, ++size * sizeof(T)); arr[size-1] = obj;}
  }

  T get(int n){
    if (!(0 <= n && n < size)) {std::cout << "Invalid range!!\n"; exit(-1);}
    return arr[n];
  }

  int get_index(T obj){
    for (int i = 0; i < size; i++) if (arr[i] == obj) return i;
    return -1;
  }

  T pop(){
    if (size == 0) {std::cout << "Empty CustomVector!!\n"; return NULL;}
    T ans = arr[size - 1];
    if (size == 1) {size--; arr = nullptr;}
    else arr = (T*) realloc(arr, --size * sizeof(T));
    return ans;
  }

  bool remove(T obj){
    if (get_index(obj) == -1) return false;
    for (int i = get_index(obj); i < size - 1; i++) arr[i] = arr[i+1];
    pop(); return true;
  }

  int get_size() {return size;}
};

class Node{
  public:
    int value;
    CustomVector<Node*> incoming_nodes;
    CustomVector<Node*> outgoing_nodes;
    CustomVector<Node*> similar_nodes;

    Node() {};
    Node(int val) {value = val;}

    bool add_outgoing_node(Node* node_to_add) {if (outgoing_nodes.get_index(node_to_add) == -1) {outgoing_nodes.push_back(node_to_add); return true;} return false;}
    bool add_incoming_node(Node* node_to_add) {if (incoming_nodes.get_index(node_to_add) == -1) {incoming_nodes.push_back(node_to_add); return true;} return false;}
    bool add_similar_node(Node* node_to_add) {if (similar_nodes.get_index(node_to_add) == -1) {similar_nodes.push_back(node_to_add); return true;} return false;}

    bool delete_outgoing_node(Node* node_to_delete) {if (outgoing_nodes.get_index(node_to_delete) != -1) {outgoing_nodes.remove(node_to_delete); return true;} return false;}
    bool delete_incoming_node(Node* node_to_delete) {if (incoming_nodes.get_index(node_to_delete) != -1) {incoming_nodes.remove(node_to_delete); return true;} return false;}
    bool delete_similar_node(Node* node_to_delete) {if (similar_nodes.get_index(node_to_delete) != -1) {similar_nodes.remove(node_to_delete); return true;} return false;} 
};

class Graph{
  public:

    int numEdges = 0;
    CustomVector<Node*> nodes;

    std::string get_nodes();

    bool create_node(Node* n1);
    bool create_edge_from_to(Node* n1, Node* n2);
    bool create_similar_nodes(Node* n1, Node* n2);

    bool remove_edge_from_to(Node* n1, Node* n2);
    bool remove_node(Node* to_remove);
    bool remove_similar_nodes(Node* n1, Node* n2);

    bool check_edge_from_to(Node* n1, Node* n2);
    bool check_similar_nodes(Node* n1, Node* n2);

    Graph(std::string input_file);

    bool similar_condition_1(Node* n1, Node* n2);
    bool similar_condition_2(Node* n1, Node* n2);
    bool similar_condition_3(Node* n1, Node* n2);
    bool similarity_condition(Node* n1, Node* n2);

    std::string get_source_nodes();
    void update_all_similar_node_pairs();
    std::string get_similar_nodes();
    void collapse();
};

#endif