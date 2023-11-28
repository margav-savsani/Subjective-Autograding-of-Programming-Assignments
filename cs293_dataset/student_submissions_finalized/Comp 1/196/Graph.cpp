#ifndef GRAPH_BST_CPP
#define GRAPH_BST_CPP

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef GRAPH_BST_H
#include "Graph.h"
#endif

//Does Recursive DFS on node n and inserts it into bst
void Graph::DFS(Node* n, BST* bst){
  //Stores the iteration level for recursive DFS call
  static int iteration=1;
  //Assigning the secondarrival time
  if(n->visits==1){
    n->secondarrival=iteration;
  }
  //Inserting the value of node n in the BST
  bst->insert(n->value);
  //Increasing the visit by 1
  n->visits++;
  //Calling DFS for every neighbour
  listOfObjects<Node*> *curr;
  curr=n->adjnodes;
  //Incrementing iteration level
  iteration++;
  while(curr!=nullptr){
    //Not calling DFS for nodes which are already visited twice or is a parent of n
    if(curr->object->visits<2 && curr->object->value!=n->parent1 && curr->object->value!=n->parent2){
      if(curr->object->visits==0){
        curr->object->parent1=n->value;
      }
      if(curr->object->visits==1){
        curr->object->parent2=n->value;
      }
      DFS(curr->object, bst);
    }
    curr=curr->next;
  }
  //Adding the firstbacktrack iteration level
  if(n->firstbacktrack==-1){
    n->firstbacktrack=iteration;
  }
}

//Does DFS for every component and Creates all BSTs
void Graph::modifiedDFS() {
  //Iteratively calling DFS and creating BST for each connected component
  //and storing them in BSTList
  for(int i=0;i<numNodes;i++){
    if(nodes[i].visits==0){
      BST* binarytree= new BST();
      //Incrementing numComponents
      numComponents++;
      DFS(&nodes[i], binarytree);
      if(BSTList==nullptr){
        BSTList=new listOfObjects<BST*>(binarytree);
        continue;
      }
      listOfObjects<BST*> *curr;
      curr=BSTList;
      while(curr->next!=nullptr){
        curr=curr->next;
      }
      curr->next=new listOfObjects<BST*>(binarytree);
    }
  }
  return;
}

//Prints the output information about graph
void Graph::printResults() {
  //If the node has been visited twice and the first backtrack through it happened after the
  //second arrival then it is in a cycle
  //Updating the bool cycle for every node and incrementing numCycle 
  for(int i=0;i<numNodes;i++){
    if(nodes[i].visits==2 && (nodes[i].firstbacktrack>=nodes[i].secondarrival)){
      nodes[i].cycle=true;
      numCycle++;
    }
  }
  //Incrementing numTwice and numOnce
  for(int i=0;i<numNodes;i++){
    if(nodes[i].visits==2){
      numTwice++;
    }
    if(nodes[i].visits==1){
      numOnce++;
    }
  }

  //Desired output
  cout<<"No. of connected components:"<<numComponents<<endl;
  cout<<"No. of nodes visited once:"<<numOnce<<endl;
  cout<<"No. of nodes visited twice:"<<numTwice<<endl;
  cout<<"No. of nodes that are  present in a cycle:"<<numCycle<<endl;
  //Iterator for counting Tree No.
  //Printing BSTs in properly formatted structure
  int i=1;
  listOfObjects<BST*> *curr;
  curr=BSTList;
  while(curr!=nullptr){
    cout<<"Tree :"<<i<<endl;
    cout<<"-------------"<<endl;
    curr->object->printBST(" ");
    cout<<"\n"<<endl;
    curr=curr->next;
    i++;
  }
  return;
}

#endif
