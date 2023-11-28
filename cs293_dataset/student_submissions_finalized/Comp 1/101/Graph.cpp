#ifndef GRAPH_BST_CPP
#define GRAPH_BST_CPP

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef GRAPH_BST_H
#include "Graph.h"
#endif

//Function which takes the current path in DFS, and the node which marks the start of a cycle
//Will be accessed later in DFS function
void markCyclic(IntNodeList *list, Node *node){
  IntNode* iter = list->last;
  while ( iter->value!=node ){
    iter = iter->prev;
  }
  while (iter!=nullptr){
    iter->value->isCyclic = true;
    iter=iter->next;
  }
}

//ModifiedDFS -> A wrapper function which runs the DFS on each connected component of graph
void Graph::modifiedDFS() {

  for ( int i = 0 ; i < numNodes ; i++ ){
    //Node part of connected component on which DFS has been performed
    if (nodes[i].visisted_times > 0){
      continue;
    }
    //Node part of a new connected compontent
    connectedComponents++;
    DFS(&nodes[i], nullptr , &Trees[i], nullptr);
  }
  return;
}

//Runs the actual modified DFS on each connected Component of graph
void Graph::DFS(Node *source, Node* parent, BST* component, IntNodeList *currlist) {
  
  //Maintaining the current path of DFS
  if (currlist  == nullptr ){
    currlist = new IntNodeList (source);
  }
  else{
    currlist->Insert(source);
  }
  source->currPath++;

  //PRINT THE PATH TILL HERE, FUNCTION USED FOR DEBUGGIN
  //currlist->Print();

  //Marking that this node has been part of a DFS
  component->insert(source->price);

  //Updating number of times node has been visited, and nodes visited once, vs nodes visited twice
  source->visisted_times++;
  if (source->visisted_times == 1 ){
    visitOnceNodes++;
  }
  else if ( source->visisted_times == 2 ){
    visitOnceNodes--;
    visitTwiceNodes++;
  }
  
  //Updating the list of parents a nodes has in this modified DFS
  if (parent != nullptr ){
    if ( source->nParents == 0 ){
      source->nParents++;
      source->parent1 = parent;
    }
    else if ( source->nParents ==1 ){
      source->nParents++;
      source->parent2  = parent;
    }
  }

  //If there are no neighbours then just return back
  AdjacencyList *neighbour = source->adjList;
  if ( neighbour == nullptr ){
    currlist->Delete();
    source->currPath--;
    return;
  }
  //Go to all the neighbours except the parent, and perform the modified DFS on them
  while( neighbour != nullptr ){
    if(neighbour->node != source->parent1 && neighbour->node != source->parent2 ){
      if (neighbour->node->visisted_times < 2){
        if ( neighbour->node->currPath ){
          //If a node is part of the current path, and we are visiting it again, then a cycle will be complete
          markCyclic(currlist, neighbour->node);
        }
        DFS(neighbour->node, source ,component, currlist);
      }
      else if ( neighbour->node->currPath ){
        //If a node is a neighbour and part of the current path, then also a cycle is completed, although we are not visiting it
        markCyclic(currlist, neighbour->node);
      }
    }
    neighbour = neighbour->next;
  }
  //Update the currlist while returning
  currlist->Delete();
  source->currPath--;
} 

//A wrapper function which prints the required output
void Graph::printResults() {
  int cyclicNodes = 0;
  for ( int i = 0 ; i < numNodes ; i++ ){
    if (nodes[i].isCyclic){
      cyclicNodes++;
    }
  }
  cout << "Seperate connected components of a graph " << connectedComponents << endl;
  cout << "Nodes visited once " << visitOnceNodes << endl;
  cout << "Nodes visited twice " << visitTwiceNodes << endl;
  cout << "Cyclic nodes " << cyclicNodes << endl;
  cout << "BSTs of Graphs " << endl;
  for ( int i = 0 ; i < numNodes ; i++ ){
    if ( Trees[i].root != nullptr ){
      Trees[i].printBST("");
      cout << endl;
    }
  }
  return;
}

//Function that is used to print the BST. Taken from previous lab
void BST::printBST(const string& prefix, bool isLeft)
{
  if( root != nullptr )
  {
      cout << prefix;

      cout << (isLeft ? "|--" : "|__" );

      // print the value of the node
      cout << '('<< root->price<<')' << endl;
      BSTNode *curr = root;
      root = root->left;
      // enter the next tree level - left and right branch
      printBST( prefix + (isLeft ? "│   " : "    "), true);
      root = curr->right;
      printBST( prefix + (isLeft ? "│   " : "    "), false);
      root = curr;
  }
}

#endif
