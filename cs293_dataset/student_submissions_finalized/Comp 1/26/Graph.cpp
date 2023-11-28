#ifndef GRAPH_BST_CPP
#define GRAPH_BST_CPP


#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif


#ifndef GRAPH_BST_H
#include "Graph.h"
#endif

void Graph::DFS(Node node, int i, listOfBST *Trees, int depttime)
{
  //Checking the recurrence for a particular node to check if its in a loop 
  // recur[i]++;
 
  listOfObjects *Adjacency = Adjacencylist[i];
  

  while (Adjacency != nullptr)
  {
    if(arrayvisited[Adjacency->value]==2 && parent1[i] != Adjacency->value && parent2[i] != Adjacency->value){
      visit2[i]=true;
    }
    //arrayvisited shouldn't be 2 and we wont go back through the path we came to this node
    if (arrayvisited[Adjacency->value] < 2 && parent1[i] != Adjacency->value && parent2[i] != Adjacency->value)
    {
      
      if (arrayvisited[Adjacency->value] == 0)
      {
        parent1[Adjacency->value] = i;
      }
      else
      {
        parent2[Adjacency->value] = i;
      }

      
      Trees->value.insert(Adjacency->value);
      // Trees->value.printBST("");
      arrayvisited[Adjacency->value]++;
      DFS(nodes[Adjacency->value], Adjacency->value, Trees, depttime);
      if(visit2[Adjacency->value]==true){
        visit2[i]=true;
      }
    }
    
    Adjacency = Adjacency->next;
    
  }
  // if the 2nd frame of the this particular node closes before its first , then its in a loop
  if (backtrack[i] == -1)
    {
      if (arrayvisited[i] == 2)
      {
        dept[i] = 1;
        backtrack[i] = 1;
      }
      else{
        
        if(visit2[i]==true){
          dept[i] = 1;
        }
        backtrack[i] = 1;
      }
    }


  // recur[i]--;
  return;
}
// Add code as appropriate for your implementation
void Graph::modifiedDFS()
{
  // For different connected componenets, if a particular node hasnt been visited it , means its in a different connected component
  for (int i = 0; i < numNodes; i++)
  {
    if (arrayvisited[i] == 0)
    {
     
      listOfBST *BSTTree = new listOfBST();
      if (Trees != nullptr)
      {
        while (Trees->next != nullptr)
        {
          
          Trees = Trees->next;
        }
        Trees->next = BSTTree;
        Trees->next->prev = Trees;
        Trees = Trees->next;
      }
      else
      {
        Trees = BSTTree;
      }

      connected++;

      Trees->value.insert(i);

      arrayvisited[i]++;
      DFS(nodes[i], i, Trees, depttime);

     
    }
  }
  //To get back to start of the list, for printing 
  while (Trees->prev != nullptr)
  {
    Trees = Trees->prev;
  }

  return;
}

void Graph::printResults()
{
  
  cout << "No. of connected components: " << connected << endl;
  listOfBST *alltrees = Trees;

  
  int singlevisit=0;
  int doublevisit=0;
  //arratvisited provides us with single and doublevisits nodes
  for (int i = 0; i < numNodes; i++)
  {
    if (arrayvisited[i] == 1)
    {
      singlevisit++;
    }
    if (arrayvisited[i] == 2)
    {
      doublevisit++;
    }
  }

  cout << "No. of nodes visited once: " << singlevisit << endl;
  cout << "No. of nodes visited twice: " << doublevisit << endl;

  
  int numcycles = 0;
  for (int i = 0; i < numNodes; i++)
  {
    // Nodes in a cycle must be visited twice
    if (arrayvisited[i] == 2)
    {//if 2 parents are different then its the orignator of a cycle
      if (parent1[i] != parent2[i])
      {
        numcycles++;
        // cout<<i<<endl;
      }
      else
      {// The 2nd frame closed before first it is in a loop
        if (dept[i] == 1)
        {
          numcycles++;
          
        }
        
      }
    }
  }

  cout << "No. of nodes that are present in a cycle: " << numcycles << endl;

  while (alltrees != nullptr)
  {
    cout << "Printing Tree" << endl;
    alltrees->value.printBST("");
    alltrees = alltrees->next;
  }
  return;
}

#endif
