#ifndef GRAPH_CPP
#define GRAPH_CPP

#ifndef GRAPH_H
#include "Graph.h"
#endif

std::string Graph::get_nodes(){
  std::string ans = "";
  for (int i = 0; i < nodes.get_size(); i++) ans.append(std::to_string(nodes.get(i) -> value) + " ");
  return ans;
}

bool Graph::create_node(Node* n1) {
  if (n1 != nullptr && nodes.get_index(n1) == -1) {nodes.push_back(n1); return true;}
  return false;
}

bool Graph::create_edge_from_to(Node* n1, Node* n2) {
  if (n1 != nullptr && n2 != nullptr && nodes.get_index(n1) != -1 && nodes.get_index(n2) != -1) {
    if (n1 -> add_outgoing_node(n2) && n2 -> add_incoming_node(n1)) {numEdges++; return true;}
  }
  return false;
}

bool Graph::create_similar_nodes(Node* n1, Node* n2) {
  if (n1 != nullptr && n2 != nullptr && nodes.get_index(n1) != -1 && nodes.get_index(n2) != -1) {
    if (n1 -> add_similar_node(n2)) return true;
  }
  return false;
}

bool Graph::remove_edge_from_to(Node* n1, Node* n2) {
  if (n1 != nullptr && n2 != nullptr && nodes.get_index(n1) != -1 && nodes.get_index(n2) != -1) {
    if (n1 -> delete_outgoing_node(n2) && n2 -> delete_incoming_node(n1)) {numEdges--; return true;}
  }
  return false;
}

bool Graph::remove_similar_nodes(Node* n1, Node* n2){
  if (n1 != nullptr && n2 != nullptr && nodes.get_index(n1) != -1 && nodes.get_index(n2) != -1) {
    if (n1 -> delete_similar_node(n2)) return true;
  }
  return false;
}

bool Graph::remove_node(Node* to_remove) {
  if (to_remove != nullptr and nodes.get_index(to_remove) != -1){
    for (int i = 0; i < to_remove -> outgoing_nodes.get_size(); i++) remove_edge_from_to(to_remove, to_remove -> outgoing_nodes.get(i));
    for (int i = 0; i < to_remove -> incoming_nodes.get_size(); i++) remove_edge_from_to(to_remove -> incoming_nodes.get(i), to_remove);
    for (int i = 0; i < to_remove -> similar_nodes.get_size(); i++) remove_similar_nodes(to_remove, to_remove -> similar_nodes.get(i));
    nodes.remove(to_remove);
    return true;
  }
  return false;
}

bool Graph::check_edge_from_to(Node* n1, Node* n2) {
  if (n1 != nullptr && n2 != nullptr) return n1 -> outgoing_nodes.get_index(n2) != -1 && n2 -> incoming_nodes.get_index(n1) != -1;
  return false;
}

bool Graph::check_similar_nodes(Node* n1, Node* n2) {
  if (n1 != nullptr && n2 != nullptr) return n1 -> similar_nodes.get_index(n2) != -1;
  return false;
}

Graph::Graph(std::string input_file){
  std::ifstream input_stream(input_file);
  std::string reader;
  if (!input_stream.is_open()) {std::cerr << "Couldn't open input file " << input_file << ". Aborting ..." << std::endl;exit(-1);}

  getline(input_stream, reader);
  int numNodes = std::stoi(reader);
  for (int i = 0; i < numNodes; i++) {
    Node* to_add = new Node(i+1);
    create_node(to_add);
  }

  while (getline(input_stream, reader)){
    if (reader.find("-1 -1") == 0) break;
    std::stringstream tmp_string(reader);
    std::string edge1, edge2;
    tmp_string >> edge1 >> edge2;
    create_edge_from_to(nodes.get(std::stoi(edge1) - 1), nodes.get(std::stoi(edge2) - 1));
  }

  while (getline(input_stream, reader)){
    if (reader.find("-1 -1") == 0) break;
    std::stringstream tmp_string(reader);
    std::string edge1, edge2;
    tmp_string >> edge1 >> edge2;
    create_similar_nodes(nodes.get(std::stoi(edge1) - 1), nodes.get(std::stoi(edge2) - 1));
  }
}

bool Graph::similar_condition_1(Node* n1, Node* n2){
  return n1 -> incoming_nodes.get_size() == 0 && n2 -> incoming_nodes.get_size() == 0 && n1 -> similar_nodes.get_index(n2) != -1;
}

bool Graph::similar_condition_2(Node* n1, Node* n2){
  for (int i = 0; i < n1 -> incoming_nodes.get_size(); i++){
    bool found_similar_parent = false;
    for (int j = 0; j < n2 -> incoming_nodes.get_size(); j++) {
      if (n1 -> outgoing_nodes.get(i) -> similar_nodes.get_index(n2 -> incoming_nodes.get(j)) != -1) {found_similar_parent = true; break;}
    }
    if (!found_similar_parent) return false;
  }
  return true;
}

bool Graph::similar_condition_3(Node* n1, Node* n2){
  return n1 -> outgoing_nodes.get(0) == n2 && n2 -> incoming_nodes.get_size() == 1;
}

bool Graph::similarity_condition(Node* n1, Node* n2){
  return similar_condition_1(n1, n2) || similar_condition_2(n1, n2) || similar_condition_3(n1, n2);
}

void Graph::update_all_similar_node_pairs(){
  bool changes_made;
  do{
    changes_made = false;
    for (int i = 0; i < nodes.get_size(); i++){
      for (int j = 0; j < nodes.get_size(); j++){
        if (similarity_condition(nodes.get(i), nodes.get(j))){
          if (nodes.get(i) -> similar_nodes.get_index(nodes.get(j)) == -1) {create_similar_nodes(nodes.get(i), nodes.get(j)); changes_made = true;}
        }
      }
    }
  } while(changes_made);
}

std::string Graph::get_source_nodes(){
  std::string ans = "";
  for (int i = 0; i < nodes.get_size(); i++){
    if (nodes.get(i) -> incoming_nodes.get_size() == 0) ans.append(std::to_string(i + 1) + " ");
  }
  return ans + '\n';
}

std::string Graph::get_similar_nodes(){
  std::string ans = "";
  for (int i = 0; i < nodes.get_size(); i++){
    for (int j = 0; j < nodes.get(i) -> similar_nodes.get_size(); j++){
      ans.append("(" + std::to_string(nodes.get(i) -> value) + ", " + std::to_string(nodes.get(i) -> similar_nodes.get(j) -> value) + ") ");
    }
  }
  return ans;
}

void Graph::collapse(){
  bool changes_made;
  do{
    changes_made = false;
    for (int i = 0; i < nodes.get_size(); i++){
      for (int j = 0; j < nodes.get_size(); j++){
        if (nodes.get(i) -> similar_nodes.get_index(nodes.get(j)) != -1){
          changes_made = true;
          int max_ = std::max(i,j);
          int min_ = std::min(i,j);
          // transfer all the incoming and outgoing nodes of min to max
          for (int a = 0; i < nodes.get(min_) -> outgoing_nodes.get_size(); i++) nodes.get(max_) -> add_outgoing_node(nodes.get(min_) -> outgoing_nodes.get(a));
          for (int a = 0; i < nodes.get(min_) -> incoming_nodes.get_size(); i++) nodes.get(max_) -> add_incoming_node(nodes.get(min_) -> incoming_nodes.get(a));
          remove_node(nodes.get(min_));
        }
        
      }
    }
  } while(changes_made);
}

#endif
