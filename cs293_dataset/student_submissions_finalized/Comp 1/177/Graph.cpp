#ifndef GRAPH_BST_CPP
#define GRAPH_BST_CPP

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef GRAPH_BST_H
#include "Graph.h"
#endif

#define MAX_INT 1000000

void Graph::double_visit_DFS(Node* start_node, BST* Component_BST, bool* visited_once, bool* visited_twice){
  std::string path = "";

  CustomStack<Node*> DFS_Stack;
  if (!visited_twice[start_node -> value - 1]) {
    DFS_Stack.push(start_node);
    path.append(std::to_string(start_node -> value));
    Component_BST -> insert(start_node -> value);
    if (visited_once[start_node -> value- 1]) visited_twice[start_node -> value - 1] = true;
    if (!visited_once[start_node -> value- 1]) visited_once[start_node -> value - 1] = true;
  }

  do{
    int top_value = DFS_Stack.top() -> value;
    if (!visited_twice[top_value -1]) {path.append(std::to_string(top_value)); Component_BST -> insert(top_value);}
    for (int i = 0; i < nodes.get(top_value - 1) -> neighbours.get_size(); i++){
      std::string edge_name = std::to_string(top_value) + std::to_string(nodes.get(top_value - 1) -> neighbours.get(i) -> value);
      std::string rev_edge_name = std::to_string(nodes.get(top_value - 1) -> neighbours.get(i) -> value) + std::to_string(top_value);
      if (!visited_twice[i] && !is_edge_in_path(edge_name,path) && is_edge_in_path(rev_edge_name, path)) DFS_Stack.push(nodes.get(top_value - 1) -> neighbours.get(i));
      else {path.pop_back(); DFS_Stack.pop()}
    } 
  } while (DFS_Stack.get_size() != 0);
}

void Graph::modifiedDFS() {
  bool* visited_once = new bool[numNodes];
  bool* visited_twice = new bool[numNodes];
  
  for (int i = 0; i < numNodes; i++){
    if (visited_once[i]) continue;
    BST* component_tree = new BST;
    double_visit_DFS(nodes.get(i), component_tree, visited_once, visited_twice);
    All_Connected_Component_Trees.push_back(component_tree);
  }


}

void Graph::printResults() {
  std::cout << "Number of Connected Components: " << All_Connected_Component_Trees.get_size() << std::endl;
}

int Graph::get_nodes_in_cycles(){
    while (true){
      bool removed = false;
      for (int i = 0; i < nodes.get_size(); i++){
        if (nodes.get(i) -> neighbours.get_size() <= 1) {
          Node* removable = nodes.get(i);
          remove_node(removable);
          removed = true;
        }
      }
      if (removed) continue;
      break;
    }
    return nodes.get_size();
}

int main(){
  Graph newgraph(3,2,"tmp.txt");
  newgraph.modifiedDFS();
  newgraph.printResults();
}

#endif
