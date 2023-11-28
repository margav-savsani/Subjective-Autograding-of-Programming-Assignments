#ifndef GRAPH_BST_H
#define GRAPH_BST_H

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

template<typename T> class StackContainer{
  public:

  T element;
  StackContainer<T>* above = nullptr;
  StackContainer<T>* below = nullptr;

  StackContainer(T obj) {element = obj;}
};

template<typename T> class CustomStack{
  StackContainer<T>* top_container = nullptr;
  int size = 0;

  public:

  void push(T obj){
    StackContainer<T>* to_insert = new StackContainer<T>(obj);
    if (size == 0) top_container = to_insert;
    else {to_insert -> below = top_container; top_container -> above = to_insert; top_container = to_insert;}
    size++;
  }

  T top() {return top_container -> element;}

  T pop(){
    if (size == 0) {std::cout << "Empty Stack!!" << std::endl; return NULL;}
    T top_element = top_container -> element;
    top_container = top_container -> below;
    delete(top_container -> above);
    size--;
    return top_element;
  }

  int get_size() {return size;}
};

template<typename T> class CustomVector{
  T* arr = nullptr;
  int size = 0;

  public:

  void push_back(T obj){
    if (arr == nullptr) {arr = new T[1]; arr[0] = obj; size++; return;}
    else {arr = (T*) realloc(arr, ++size * sizeof(T)); arr[size-1] = obj;}
  }

  T get(int n){
    if (!(0 <= n && n < size)) {std::cout << "Invalid range!!" << std:: endl; exit(-1);}
    return arr[n];
  }

  int get_index(T obj){
    for (int i = 0; i < size; i++) if (arr[i] == obj) return i;
    return -1;
  }

  T pop(){
    if (size == 0) {std::cout << "Empty CustomVector!!" << std::endl; return NULL;}
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

class BST_Node{
  public:

  int value;
  BST_Node* left = nullptr;
  BST_Node* right = nullptr;
  BST_Node* parent = nullptr;

  BST_Node(int val){value = val;}

  void printBST_node(const std::string& prefix, bool isLeft = false){
      std::cout << prefix << (isLeft ? "|--" : "|__" ) << value << std::endl;
      if (left != nullptr) left -> printBST_node(prefix + (isLeft ? "│   " : "    "), true);
      if (right != nullptr) right -> printBST_node(prefix + (isLeft ? "│   " : "    "), false);
  }
};

void make_parent_child(BST_Node* parent, BST_Node* child, bool is_left){
  if (parent != nullptr) {if (is_left) {parent -> left = child;} else {parent -> right = child;}}
  if (child != nullptr) child -> parent = parent;
}

class BST{
  BST_Node* root = nullptr;

  public:

  BST(){}
  BST(int val) {root = new BST_Node(val);} 

  bool insert(int val){
    BST_Node* to_insert = new BST_Node(val); 
    if (root == nullptr) {root = to_insert; return true;}

    BST_Node* current_node = root;

    while (current_node -> value != val){
        if (current_node -> value > val){
            if (current_node -> left == nullptr) {make_parent_child(current_node, to_insert, true); return true;}
            else current_node = current_node -> left;
        }
        else {
            if (current_node -> right == nullptr){make_parent_child(current_node, to_insert, false); return true;}
            else current_node = current_node -> right;
        }
    }
    return false; 
  }

  void printBST() {root -> printBST_node("");} 
};

class Node{
public:
  int value;
  CustomVector<Node*> neighbours;

  Node() {};
  Node(int val) {value = val;}

  void add_neighbour(Node* node_to_add) {if (neighbours.get_index(node_to_add) == -1) neighbours.push_back(node_to_add);}
  void delete_neighbour(Node* node_to_delete) {if (neighbours.get_index(node_to_delete) != -1) neighbours.remove(node_to_delete);}
};

class Graph
{
  int numNodes = 0;
  int numEdges = 0;
  std::fstream graphFile;

  CustomVector<BST*> All_Connected_Component_Trees;
  CustomVector<Node*> nodes;

  public:

    void create_node(Node* n1) {
        if (n1 != nullptr && nodes.get_index(n1) == -1) 
        nodes.push_back(n1); 
        numNodes++;
    }

    void create_edge(Node* n1, Node* n2) {
        if (n1 != nullptr && n2 != nullptr && nodes.get_index(n1) != -1 && nodes.get_index(n2) != -1) {
        n1 -> add_neighbour(n2); 
        n2 -> add_neighbour(n1);
        numEdges++;
        }
    }

    bool remove_edge(Node* n1, Node* n2) {
        if (n1 != nullptr && n2 != nullptr && nodes.get_index(n1) != -1 && nodes.get_index(n2) != -1) {
            n1 -> delete_neighbour(n2);
            n2 -> delete_neighbour(n1);
            numEdges--;
            return true;
        }
        return false;
    }

    bool remove_node(Node* to_remove) {
      if (to_remove != nullptr and nodes.get_index(to_remove) != -1){
        for (int i = 0; i < to_remove -> neighbours.get_size(); i++) {
            remove_edge(to_remove, to_remove -> neighbours.get(i));
        }
        nodes.remove(to_remove);
        numNodes--;
        return true;
      }
      return false;
    }

    bool check_edge(Node* n1, Node* n2) {
        if (n1 != nullptr && n2 != nullptr) {
            return n1 -> neighbours.get_index(n2) != -1 && n2 -> neighbours.get_index(n1) != -1;
        } 
        return false;
    }

    Graph(int nNodes, int nEdges, std::string gFileName){
      if (nEdges > nNodes*(nNodes-1)/2 || nNodes <= 0 || nEdges < 0) {std::cout << "Incompatible # of edges or nodes" << std::endl; exit(-1);}
      graphFile.open(gFileName, std::ios::out);

      if (!graphFile.is_open()) {std::cerr << "Couldn't open graph file " << gFileName << ". Aborting ..." << std::endl;exit(-1);}

      graphFile << nNodes << std::endl;
      graphFile << nEdges << std::endl;

      for (int i = 0; i < nNodes; i++) {
        Node* to_add = new Node(i+1);
        create_node(to_add);
      }

      srand(time(0));
      int n1, n2;
      int countEdges = 0;

      while (countEdges < nEdges){
        do{n1 = rand() % numNodes; n2 = rand() % numNodes;} while (n1 == n2);

        if (check_edge(nodes.get(n1), nodes.get(n2))) continue;

        create_edge(nodes.get(n1), nodes.get(n2));
        countEdges++;
        graphFile << n1 + 1 << " " << n2 + 1 << std::endl;
      }

      if (numEdges != nEdges || numNodes != nNodes) {std::cout << "Incorrect" << std::endl;}
  }

  int get_nodes_in_cycles(); // Warning, this WILL DESTROY the graph. Use only after doing everything else
  void double_visit_DFS(Node* start_node, BST* Component_BST, bool* visited_once, bool* visited_twice);
  void modifiedDFS();
  void printResults();
};

bool is_edge_in_path(std::string edge, std::string path){
  return path.find(edge) != std::string::npos;
}

#endif