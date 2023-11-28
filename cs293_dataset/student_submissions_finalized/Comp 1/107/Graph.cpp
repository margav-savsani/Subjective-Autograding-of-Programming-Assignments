#ifndef GRAPH_BST_CPP
#define GRAPH_BST_CPP

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef GRAPH_BST_H
#include "Graph.h"
#endif

// DFS on node start
// parent is node which has called dfs on start
// bst is BST to which this node is to be added
void Graph::modifiedDFSComponent(Node *start, Node *parent, BST *bst) {
  if(start->visited==2) // already visited twice
    return;
  start->visited++; // increase number of visits
  if(start->arrTime==-1)  // first visit
  {
    start->parent=parent;
    start->arrTime=counter++;
  }
  bst->insert(start->value);  // Insert into bst
  listOfObjects<Node*> *curr=start->adjacencyStart; // adjacency of start
  while(curr!=nullptr)
  {
    if(curr->object!=parent && curr->object!=start->parent) // DFS is not to be called on Node which has called DFS on start
    {
      if(curr->object->arrTime < start->arrTime && curr->object->arrTime!=-1) // Cycle is formed
      {
        Node *nodeNow=start;  // all Nodes from start, start->parent, start->parent->parent, ..., curr->object are in cycle
        while(nodeNow!=curr->object && nodeNow!=nullptr)
        {
          nodeNow=nodeNow->parent;
        }
        if(nodeNow!=nullptr)
        {
          nodeNow=start;
          while(nodeNow!=curr->object)
          {
            nodeNow->inCycle=true;
            nodeNow=nodeNow->parent;
          }
          curr->object->inCycle=true;
        }
      }
      modifiedDFSComponent(curr->object, start, bst);
    }
    curr=curr->next;
  }
}



// Add code as appropriate for your implementation
void Graph::modifiedDFS() {
  for(int i=0; i<numNodes; i++)
  {
    if(nodes[i].visited==0) // New component begins
    {
      BST *newBST= new BST(); // BST for this component
      counter=0;
      nodes[i].isRoot=true;
      modifiedDFSComponent(&nodes[i], nullptr, newBST); // run DFS on this node
      listOfObjects<BST*> *toAdd= new listOfObjects<BST*>(newBST);
      if(allBSTs==nullptr)  // first component
        allBSTs=toAdd;
      else  // add to end of the list
      {
        listOfObjects<BST*> *end= allBSTs;
        while(end->next!=nullptr)
          end=end->next;
        toAdd->prev=end;
        end->next=toAdd;
      }
      components++;
    }
  }
  return;
}

void Graph::printResults() {
  cout<<"No. of connected components: "<<components<<endl;
  for(int i=0; i<numNodes; i++)
  {
    if(nodes[i].visited==1)
      once++;
    else
      twice++;
    cycle=cycle+nodes[i].inCycle;
  }
  cout<<"No. of nodes visited once: "<<once<<endl;
  cout<<"No. of nodes visited twice: "<<twice<<endl;
  cout<<"No. of nodes that are present in a cycle: "<<cycle<<endl;
  int i=1;
  listOfObjects<BST*> *curr=allBSTs;
  while(curr!=nullptr)
  {
    cout<<"BST for component "<<i<<endl;
    curr->object->printBST("");
    curr=curr->next;
    i++;
  }
  return;
}

#endif
