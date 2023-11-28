#ifndef GRAPH_BST_CPP
#define GRAPH_BST_CPP

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef GRAPH_BST_H
#include "Graph.h"
#endif
 using namespace std;
// Add code as appropriate for your implementation

int n_ones = 0;
int n_twos = 0;


int** matrix;

ofstream out_file;

void Graph::printSources(){//print sources in graph
  out_file.open("outgraph.txt");
  out_file << "Source nodes: ";
  for(int i =0; i<numNodes; i++){
    if(nodes[i].adjacency_src==nullptr){
      out_file << i+1 << " ";
    }
  }
  out_file << endl << endl;
  out_file.close();
}

void Graph::fix_similar(){ //uses rules to add new elements to similar list

  linked_list* parent_list = new linked_list;
  linked_list_node* marker = source_nodes->start;
  while (marker!=nullptr){
    parent_list->insert(marker->node_number);
    marker = marker->next;
  }

  
  while (parent_list->length<numNodes){
    
    linked_list* child_list = new linked_list;

    for(int i =0 ; i<numNodes; i++){
      if(!parent_list->present(i+1)){
        bool present = true;
        linked_list* my_parents= nodes[i].adjacency_src;
        linked_list_node* parent_marker = my_parents->start;
        while(parent_marker!=nullptr){
          if(!parent_list->present(parent_marker->node_number)){
            present = false;
          }
          parent_marker = parent_marker->next;
        }
        if(present){
          child_list->insert(i+1);
        }
      }
    }
    marker = parent_list->start;
    while (marker!=nullptr){
      if(nodes[marker->node_number-1].adjacency_dest==nullptr){
        marker = marker->next;
        continue;
      }
      linked_list_node* marker2 = nodes[marker->node_number-1].adjacency_dest->start;
      while(marker2!=nullptr){
        if(nodes[marker2->node_number-1].adjacency_src->length==1){
          if(nodes[marker2->node_number-1].similar==nullptr){
            nodes[marker2->node_number-1].add_similarity_node(marker->node_number);
          }
          else{
            if(!nodes[marker2->node_number-1].similar->present(marker->node_number)){
              nodes[marker2->node_number-1].add_similarity_node(marker->node_number);
            }
          }
        }
        marker2 = marker2->next;
      }
      marker = marker->next;
    }
    
    marker = child_list->start;



    while (marker!=nullptr){
      linked_list_node* marker2 = marker;
      while (marker2!=nullptr){

        if(nodes[marker->node_number-1].adjacency_src==nullptr){
          marker = marker->next;
          break;
        }

        if(nodes[marker2->node_number-1].adjacency_src==nullptr){
          marker2 = marker2->next;
          continue;
        }
        linked_list_node* parent_marker = nodes[marker->node_number-1].adjacency_src->start;
        bool parent_found_drxn1=true;
        while(parent_marker!=nullptr){
          if(nodes[parent_marker->node_number-1].similar==nullptr){
            parent_found_drxn1 = false;
            break;
          }
          linked_list_node* parent_similar_node = nodes[parent_marker->node_number-1].similar->start;
          bool suitable_similar_parent_drxn1 = false;
          while(parent_similar_node!=nullptr){
            if(nodes[marker2->node_number-1].adjacency_src->present(parent_similar_node->node_number)){
              suitable_similar_parent_drxn1 = true;
              break;
            }
            parent_similar_node = parent_similar_node->next;
          }
          if(suitable_similar_parent_drxn1==false){
            parent_found_drxn1 = false;
            break;
          }
          parent_marker = parent_marker->next;
        }

        parent_marker = nodes[marker2->node_number-1].adjacency_src->start;
        bool parent_found_drxn2=true;
        while(parent_marker!=nullptr){
          if(nodes[parent_marker->node_number-1].similar==nullptr){
            parent_found_drxn1 = false;
            break;
          }
          linked_list_node* parent_similar_node = nodes[parent_marker->node_number-1].similar->start;
          bool suitable_similar_parent_drxn2 = false;
          while(parent_similar_node!=nullptr){
            if(nodes[marker->node_number-1].adjacency_src->present(parent_similar_node->node_number)){
              suitable_similar_parent_drxn2 = true;
              break;
            }
            parent_similar_node = parent_similar_node->next;
          }
          if(suitable_similar_parent_drxn2==false){
            parent_found_drxn1 = false;
            break;
          }
          parent_marker = parent_marker->next;
        }

        if(parent_found_drxn1 && parent_found_drxn2){
          if(nodes[marker->node_number-1].similar==nullptr){
            nodes[marker->node_number-1].add_similarity_node(marker2->node_number);
          }
          else{
            if(!nodes[marker->node_number-1].similar->present(marker2->node_number)){
              nodes[marker->node_number-1].add_similarity_node(marker2->node_number);
            }
          }

          if(nodes[marker2->node_number-1].similar==nullptr){
            nodes[marker2->node_number-1].add_similarity_node(marker->node_number);
          }
          else{
            if(!nodes[marker2->node_number-1].similar->present(marker->node_number)){
              nodes[marker2->node_number-1].add_similarity_node(marker->node_number);
            }
          }
        }
        marker2 = marker2->next;
      }
      marker = marker->next;
    }

    marker = child_list->start;

    while (marker!=nullptr){
      parent_list->insert(marker->node_number);
      marker = marker->next;
    }

    
  }
}

void Graph::printSimilar(){ //print similar list
  out_file.open("outgraph.txt", std::ios::app);
  out_file << "Similar node pairs: ";
  for(int i =0; i<numNodes; i++){
    if(nodes[i].similar!=nullptr){
      linked_list_node* similarities = nodes[i].similar->start;
      while (similarities!=nullptr){
        out_file << "("<<i+1<<","<<similarities->node_number<<") ";
        similarities = similarities->next;
      }
    }
  }
  out_file << endl << endl;
  out_file.close();
}

void Graph::take_closure_and_collapse(){
  node_pointers = new Node*[numNodes];
  for(int i =0; i<numNodes; i++){
    node_pointers[i] = &nodes[i];
  }
  bool changed = true;
  while(changed){
    changed = false;
    for(int i =0; i<numNodes; i++){
      Node* my_node1 = node_pointers[i];
      if(my_node1->similar!=nullptr){
        changed = true;
        if(my_node1->similar->start==nullptr){
          changed = false;
          continue;
        }
        int connected = my_node1->similar->start->node_number;

        
        my_node1->similar->remove();
        Node* my_node2 = node_pointers[connected-1];
        int new_name, old_name;

        if(my_node2->value>my_node1->value){
          new_name = my_node2->value; old_name = my_node1->value;
        }
        else{
          old_name = my_node2->value; new_name = my_node1->value;
        }

        my_node1->remove_all_connections(old_name);
        my_node2->remove_all_connections(old_name);

        my_node1->remove_all_connections(new_name);
        my_node2->remove_all_connections(new_name);

        if(new_name==old_name){
          continue;
        }
        
        if(my_node1->adjacency_dest!=nullptr){
          linked_list_node* marker = my_node1->adjacency_dest->start;
          while (marker!=nullptr){
            my_node2->add_dest_node(marker->node_number);
            marker = marker->next;
          }
        }

        if(my_node1->adjacency_src!=nullptr){
          linked_list_node* marker = my_node1->adjacency_src->start;
          while (marker!=nullptr){
            my_node2->add_src_node(marker->node_number);
            marker = marker->next;
          }
        }

        if(my_node1->similar!=nullptr){
          linked_list_node* marker = my_node1->similar->start;
          while (marker!=nullptr){
            my_node2->add_similarity_node(marker->node_number);
            marker = marker->next;
          }
        }


        my_node2->value = new_name;
        node_pointers[old_name-1] = my_node2;
        node_pointers[new_name-1] = my_node2;
        collapsed_nodes->find_and_remove(old_name);
      }
    }
  }
}


void Graph::print_collapsed(){
  out_file.open("outgraph.txt", std::ios::app);
  out_file << "Collapsed graph:" << endl << endl << collapsed_nodes->length << ": ";
  linked_list_node* marker = collapsed_nodes->start;
  
  while(marker!=nullptr){
    out_file<<marker->node_number << " ";
    marker = marker->next;
  }
  out_file << endl;
  marker = collapsed_nodes->start;
  while(marker!=nullptr){
    linked_list* l = node_pointers[marker->node_number-1]->adjacency_dest;
    if(l==nullptr){
      marker = marker->next;
      continue;
    }
    linked_list* list_of_out = new linked_list;
    linked_list_node* adj_marker = l->start;
    while(adj_marker!=nullptr){
      int n1 = node_pointers[marker->node_number-1]->value, n2 = node_pointers[adj_marker->node_number-1]->value;
      if(!list_of_out->present(n2)){
        out_file << n1 << " " << n2 << endl;
        list_of_out->insert(n2);
      }
      adj_marker = adj_marker->next;
    }
    marker = marker->next;
  }

  out_file.close();
  
}





#endif
