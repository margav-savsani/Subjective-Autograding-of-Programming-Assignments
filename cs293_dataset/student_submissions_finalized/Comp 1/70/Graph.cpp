#ifndef GRAPH_BST_CPP
#define GRAPH_BST_CPP

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef GRAPH_BST_H
#include "Graph.h"
#endif

void BST::printBST(const string& prefix, bool isLeft=false)
{
    if( root != nullptr )
    {
        cout << prefix;

        cout << (isLeft ? "|--" : "|__" );

        // print the value of the node
        cout << root->value << endl;
        Node *curr = root;
        root = root->left;
        // enter the next tree level - left and right branch
        printBST( prefix + (isLeft ? "│   " : "    "), true);
        root = curr->right;
        printBST( prefix + (isLeft ? "│   " : "    "), false);
        root = curr;
    }
}
bool BST::insert(Node* node2b) {
    Node* tempp = NULL;
    Node* tempn = root; 
    while(tempn != nullptr){
        tempp = tempn;
        if(node2b->value < tempn->value){
            tempn = tempn->left;
        }
        else{
            tempn = tempn->right;
        }
    }
    node2b->parent = tempp;
    if(tempp == nullptr){
        root = node2b;
    }
    else if(node2b->value < tempp->value){
        tempp->left = node2b;
    }
    else {
        tempp->right = node2b;
    }
    return true;
    }

// Add code as appropriate for your implementation
void Graph::modifiedDFS() {
  for(int i = 0; i < numNodes; i++){
    if(visited[i] == 0){
      //traversing the linked list of bst
      listOfObjects<BST*>* storeBSTList = linkListOfBSTs;
      listOfObjects<BST*>* lastBST = nullptr;
      while(linkListOfBSTs != nullptr){
        lastBST = linkListOfBSTs;
        linkListOfBSTs = linkListOfBSTs->next;
      }
      if(lastBST == nullptr){
        linkListOfBSTs = new listOfObjects(new BST);
        storeBSTList = linkListOfBSTs;
        DFS(&nodes[i], linkListOfBSTs->object, 0);
      }
      else{
        lastBST->next = new listOfObjects(new BST);
        DFS(&nodes[i], lastBST->next->object, 0);
      }
      linkListOfBSTs = storeBSTList;
      connectedComp++;
    }
  }
}

void Graph::DFS(Node* node, BST* tree, int parent){
  
  //base case
  if(node == nullptr || visited[node->value - 1] == 2){
    return;
  }
  if(visited[node->value - 1] == 1){
    visited[parent - 1]++;
    

    while(parent != node->value){
      tree->insert(new Node(parent));
      parent = parentArray[parent - 1];
      visited[parent - 1]++;
    }
    return;
  }
  parentArray[node->value - 1] = parent;
  visited[node->value - 1]++;
  tree->insert(node); //insert the node in the BST
  listOfObjects<Node*> * iterator = node->adjacencyList;
  while(iterator != nullptr){
    if(iterator->object->value != parent){
      DFS(iterator->object, tree, node->value);
    }
    iterator = iterator->next;
  }
  
}

void Graph::printResults() {

  cout<<"No. of connected components: "<<connectedComp<<endl;

  int numNodesVisitedOnce = 0;
  int numNodesVisitedTwice = 0;
  for(int i = 0; i < numNodes; i++){
    if(visited[i] == 1) numNodesVisitedOnce++;
    else if(visited[i] == 2) numNodesVisitedTwice++;
  }
  cout<<"No. of nodes visited once: "<<numNodesVisitedOnce<<endl;
  cout<<"No. of nodes visited twice: "<<numNodesVisitedTwice<<endl;
  cout<<"No. of nodes that are present in a cycle: "<<numNodesVisitedTwice<<endl;

  listOfObjects<BST*>* storeBSTList = linkListOfBSTs;
  int count = 0;
  while(linkListOfBSTs != nullptr){
    count++;
    cout<<"BST "<<count<<" :-"<<endl;
    linkListOfBSTs->object->printBST("");
    linkListOfBSTs = linkListOfBSTs->next;
  }
  linkListOfBSTs = storeBSTList;
}

#endif
