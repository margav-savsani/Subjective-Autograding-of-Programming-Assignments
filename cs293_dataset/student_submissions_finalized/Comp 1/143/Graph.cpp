#ifndef GRAPH_BST_CPP
#define GRAPH_BST_CPP

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef GRAPH_BST_H
#include "Graph.h"
#endif
/* while adding we are basically adding 2 directed edges so once we travel through the vertex in 
a specific orientation it has to become a directed edge 
and once a node 
*/
static listOfObjects<Node*>*visit;//tracks the previous visited vertex and the current vertex
listOfObjects<BST*>*tree; //tail of the list of BSTs
listOfObjects<BST*>*tree_copy; //head of the list of BSTs
BST *tree_id;//BST of a single component


bool Graph::pop(int vertex1 , int vertex2){ //will pop a directed edge from vertex1 to vertex2
  listOfObjects<Node*>*node_copy1 = nodes[vertex1].adjacency;
  while(node_copy1->next!=nullptr){
    if(node_copy1->next->object == &nodes[vertex2]){
      node_copy1->next = node_copy1->next->next;
      return true ;
    }
    node_copy1 = node_copy1->next;
  }
  return false;
}

int Graph::size(int vertex){ //returns the number of nodes which can be visited from vertex
  listOfObjects<Node*>*node_copy1 = nodes[vertex].adjacency;
  int size = 0;
  while(node_copy1!=nullptr){
    size++;
    node_copy1 = node_copy1->next;
  }
  return size-1;
}

void Graph::DFS(int vertex){
  if(tree_id == nullptr){ //creating BST
    tree_id = new BST();
  }
  if(visit == nullptr){ //creating the list of the visited vertices
    visit = new listOfObjects<Node*>(&nodes[vertex]);
  }
  else{
    visit->next =  new listOfObjects<Node*>(&nodes[vertex]);
    visit->next->prev = visit;
    visit = visit->next;
  }
  
  if(visit->prev==nullptr){ //inserting and updating
    tree_id->insert(nodes[vertex].value);
    nodes[vertex].visited++;
  }
  else{
    if(visit->prev->object->value!=visit->object->value){
      tree_id->insert(nodes[vertex].value);
      nodes[vertex].visited++;
    }
  }
  
  
  listOfObjects<Node*>*node_copy1 = nodes[vertex].adjacency;
  
  listOfObjects<Node*>*node_copy2 = nodes[vertex].adjacency;
  node_copy2 = node_copy2->next;
  
  while(node_copy2!=nullptr){ //pops an undirected edge after travelling in one direction and also removes the directed edges of backtraced edges after visiting once
    if(node_copy2->object->visited!=2 ){
        if(visit->prev==nullptr){
          pop(node_copy2->object->value-1,vertex);
          DFS(node_copy2->object->value-1);
          
        }
        else{
            if(visit->prev->object->value!=node_copy2->object->value){
               pop(node_copy2->object->value-1,vertex);
                DFS(node_copy2->object->value-1);
            }
            else{
              pop(node_copy2->object->value-1,vertex);
              pop(vertex,node_copy1->object->value-1);
            }
          }
      }
      node_copy2 = node_copy2->next;
    }
  }


void Graph::modifiedDFS() { //calls DFS on different components
  for(int i = 0;i < numNodes;i++){
    
    if(nodes[i].visited==0){
      components++;
      DFS(i);
      if(tree == nullptr){ //inserts the created tree into the list
        tree = new listOfObjects<BST*>(tree_id);
        tree_copy = tree;
      }
      else{
        tree->next = new listOfObjects<BST*>(tree_id);
        tree = tree->next;
      }
      tree_id = nullptr;
    }
  }
  for(int i = 0;i<numNodes;i++){
    if(nodes[i].visited==1){ //number of nodes visited once
      once_visited++;
    }
    else{
      if(size(i)>=1){ //number of nodes in cycle
        incycle++;
      }
      twice_visited++; //number of nodes visited twice
    }
  }
  return;
}




void Graph::printResults() {
  cout<<"No. of connected components: "<<components<<endl;
  cout<<"No. of nodes visited once: "<<once_visited<<endl;
  cout<<"No. of nodes visited twice: "<<twice_visited<<endl;
  cout<<"No. of nodes that are present in a cycle: "<<incycle<<endl;
  while(tree_copy!=nullptr){
    tree_copy->object->printBST(" ");
    cout<<endl;
    tree_copy = tree_copy->next;
  }
  
  return;
}

#endif
