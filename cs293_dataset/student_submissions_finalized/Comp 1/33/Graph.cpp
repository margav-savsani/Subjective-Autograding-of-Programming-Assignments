#ifndef GRAPH_BST_CPP
#define GRAPH_BST_CPP

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef GRAPH_BST_H
#include "Graph.h"
#endif

using namespace std;
void Graph::newDFS(Node *node, BST *Tree)  // new function which implements the DFS method . 
{
  if (node != nullptr)  // given node must not be nullptr .
  {
    node->num_visited = node->num_visited + 1; // updating the value of num_visited ;
    Tree->insert(node->value);  // inserting it into the tree .
    listOfObjects<Node *> *dummy = node->adjacencynodes;
    while (dummy != nullptr)
    {
      Node *currNode;
      currNode = dummy->object;
      if (currNode->num_visited < 2) // Max num of times a node can be visited is 2 .
      { 
        // listOfObjects<Node *> *temp ;
        // temp = currNode->adjacencynodes ;
        // while(temp != nullptr){
        //   if(temp->object->value == node->value){
        //     if(temp->next == nullptr){
        //       temp = nullptr ;
        //       temp->object = 0 ;
        //       break ;
        //     }
        //     else{
                
        //         temp->next=temp->prev->next;
        //         temp->next->prev=temp->next;
        //         temp->prev->next=temp->next;
        //         temp->prev=temp->next->prev;
        //         break ;
        //     }
        //   }
        //   temp = temp->next ;
        // }
        newDFS(currNode, Tree);
      }
      dummy = dummy->next;    
    }
    // listOfObjects<BST *> *newTree = new listOfObjects<BST *>(Tree);
    // newTree->next = Trees;
    // Trees = newTree;
  }
  return;
}

// Add code as appropriate for your implementation
void Graph::modifiedDFS()
{
  // srand(time(0));  // used for random number generator .
  // int pivot;  // this pivot selects the node randomly .
  // pivot = rand() % numNodes;
  Node *node;
  node = &nodes[0];  // this node is our source from where we should start DFS .
  num_connected_components = 1;
  BST *Tree;
  Tree = new BST();
  newDFS(node, Tree);
  listOfObjects<BST *> *newTree = new listOfObjects<BST *>(Tree);  // creating new Tree for storing the nodes .
  newTree->next = Trees;
  Trees = newTree; // inserting the created tree into the list of BST trees .
  for (int i = 0; i < numNodes; i++)
  {
    if ((nodes[i].num_visited == 0)) // DFS for the nodes which were not visited atleast once .
      if (nodes[i].adjacencynodes != nullptr) // DFS for the nodes which have adjacent nodes but not visited atleast once .
      {
        {
          num_connected_components++;
          BST *tree;
          tree = new BST();
          newDFS(&nodes[i], tree);
          listOfObjects<BST *> *newTree = new listOfObjects<BST *>(tree);
          newTree->next = Trees;
          Trees = newTree;
        }
      }
      else  // DFS for the nodes which doesnot have any adjacent nodes .
      {
        num_connected_components++;
        BST *tree ;
        tree = new BST();
        tree->insert(nodes[i].value) ;
        nodes[i].num_visited = nodes[i].num_visited + 1 ;
        listOfObjects<BST *> *newTree = new listOfObjects<BST *>(tree);
        newTree->next = Trees;
        Trees = newTree;
      }
  }
  return;
}

void Graph::printResults()
{
  int num_nodes_twice = 0;  // value equal to num of nodes visited only twice .
  int num_nodes_once = 0;  // value equal to num of nodes visited only once .
  int num_nodes_cycle = 0;
  for (int i = 0; i < numNodes; i++)
  {
    if (nodes[i].num_visited == 1)
    {
      num_nodes_once++;  // updating number of nodes visited only once .
    }
    else if (nodes[i].num_visited == 2)
    {
      num_nodes_twice++;  // updating number of nodes visited twice .
    }
  }
  listOfObjects<BST *> *trees;
  trees = Trees;
  std::cout<<std::endl;
  while (trees != nullptr)
  {
    trees->object->printBST(" ");  // printing all the trees stored in the list .
    std::cout<<std::endl;
    trees = trees->next;
  }
  std::cout << "Number Of Connected Components : " << num_connected_components << std::endl;
  std::cout << "Number Of Nodes Visited Once : " << num_nodes_once << std::endl;
  std::cout << "Number Of Nodes Visited Twice : " << num_nodes_twice << std::endl;
  std::cout << "Number Of Nodes in a Cycle : "<<num_nodes_twice<< std::endl ;
  std::cout<<std::endl ;
  return;
}

#endif
