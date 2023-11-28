#ifndef GRAPH_BST_CPP
#define GRAPH_BST_CPP

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef GRAPH_BST_H
#include "Graph.h"
#endif


using namespace std;

void BST::insert(int val){
  // Simply call the other insert function with root
  if(root == NULL){
    root = new BSTNode(val);
  }
  else insert(val, root);
}

void BST::insert(int val, BSTNode* top){
  
  // Standard insert operation in a BST
  if(val>top->vertex){
    if(top->right==NULL){
      top->right = new BSTNode(val);
      top->right->parent = top;
    }
    else insert(val, top->right);
  }
  else{
    if(top->left==NULL){
      top->left = new BSTNode(val);
      top->left->parent = top;
    }
    else insert(val, top->left);
  }

}

void BST::printBST(const string& prefix, bool isLeft=false){
      // Print function directly copied
      if( root != nullptr )
      {
          cout << prefix;

          cout << (isLeft ? "|--" : "|__" );

          // print the value of the node
          cout << root->vertex << endl;
          BSTNode *curr = root;
          root = root->left;
          // enter the next tree level - left and right branch
          printBST( prefix + (isLeft ? "│   " : "    "), true);
          root = curr;
          root = root->right;
          printBST( prefix + (isLeft ? "│   " : "    "), false);
          root = curr;
      }
  }


void Graph::modifiedDFS() {
  for(int i=0;i<numNodes; i++){
    // We call DFS for each component
    if(nodes[i].numVisited==0){
      numConnectedComponents++; // Increment number of components

      // Create a new BST and pass it to the DFS
      if(BSTList == NULL){
        BST *x = new BST;
        BSTList =  new SLL<BST*>(x);
        modifiedRecDFS(&nodes[i],0, BSTList->v);
      }
      else{
        SLL<BST*>* temp = BSTList;
        while(temp->next !=NULL){
          temp = temp->next;
        }
        BST* x = new BST;
        temp->next = new SLL<BST*>(x);
        modifiedRecDFS(&nodes[i],0, temp->next->v);
      }
      
      
    }
  }
  return;
}

void Graph::modifiedRecDFS(Node* ver,int prevValue, BST* tree){
  // cout<<ver->value<<endl;
  // If a vertex is visited again while its first call has not been ended then it is part of a cycle
  if(ver->inCall){
    ver->isInCycle = true;
  }
  ver->inCall = true;
  ver->numVisited++;//Increment num Visited
  tree->insert(ver->value); //Insert it in the BFS
  

  // Now we add the parent to the currParents list in a stack fashion
  SLL<int>* newElem = new SLL<int>(prevValue);
  newElem->next = ver->currParents;
  ver->currParents = newElem;



  SLL<int>* temp = ver->adjList; //Go through its neighbours
  while(temp!=NULL){
    // Check if the edge is in the parents list
    bool isValid = true;
    int x = nodes[temp->v-1].value ;
    SLL<int>* tempparent = ver->currParents;
    while(tempparent!=NULL){
      if(tempparent->v == x) isValid = false;
      tempparent=tempparent->next;
    }
    if(isValid){

      if(nodes[temp->v -1 ].numVisited >= 2){
        // In this case vertex is definitely part of a cycle
        ver->isInCycle = true;
      }
      else {
        // If its neighbour hasn't been visited twice yet then visit it
        modifiedRecDFS(&nodes[temp->v - 1],ver->value, tree);
      }
    }
    temp = temp->next;
  }
  ver->inCall = false; //Set it to false finally after this reccursive call is over 

  // Also pop the parent 

  ver->currParents = ver->currParents->next;
}

void Graph::printResults() {
  cout<<"Number of connected components: "<<numConnectedComponents<<endl;
  int one=0,two=0, cycles=0;
  for(int i=0;i<numNodes;i++){
    if(nodes[i].numVisited == 1) one++;
    else two++;

    if(nodes[i].isInCycle)cycles++;
  }
  cout<<"Number of nodes visited once: "<<one<<endl;
  cout<<"Number of nodes visited twice: "<<two<<endl;
  cout<<"Number of nodes present in cycle: "<<cycles<<endl;
  SLL<BST *>* curr = BSTList;
  while(curr!= NULL){
    curr->v->printBST("");
    curr = curr->next;
  }
  return;
}

#endif
