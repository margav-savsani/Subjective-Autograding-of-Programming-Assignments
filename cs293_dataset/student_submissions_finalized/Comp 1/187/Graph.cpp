#ifndef GRAPH_BST_CPP
#define GRAPH_BST_CPP
#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif
#ifndef GRAPH_BST_H
#include "Graph.h"
#endif
// Add code as appropriate for your implementation
bool Graph::Cycle(int a, int val)
{// This function will give the presence of node with value a+1 is present in a cycle or not. 
    nodes[a].incycle = true;// Making the node to true in cycle.
    for(int i=0;i<nodes[a].adj.size();i++)
    {// looping in adjacency list of node to recurse for cycle function.
        if (!nodes[i].incycle)
        {
            Cycle(i, val);
        }
        else
        {// if visited checking the presense of actual node in adjcancey list of present node.
            Node s = nodes[i];
            for(int j = 0; j<s.adj.size();j++)
            {
                if (nodes[j].value == val)
                {
                    return true;
                }
            }
        }
    }
  return false;
}

void Graph::DFS(int a, BST *t){// This function will do DFS on 
  Node s = nodes[a];
  count[a]++;
  t->insert(a+1);
  vectorClass<int> l = s.list;
  for(int i=0;i<l.size();i++){// looping through adjacency list of node.
    if(count[l.get(i)] == 0){
      nodes[l.get(i)].list.remove(a);
      DFS(l.get(i), t);// calling DFS function on adjacent nodes if not visited.
    }
    else if(count[l.get(i)] == 1){
      nodes[l.get(i)].list.remove(a);
      DFS(l.get(i), t);// calling DFS on adjacent nodes if already visited once.
    }
  }
}

bool isequals(vectorClass<int> A, vectorClass<int> B){// This function checks the equality between two vectors.
  if(A.size() != B.size()){// checks the size of two vectors.
    return false;
  }
  else{// If same then checks all elements.
    int count = 0;
    for(int i=0;i<A.size();i++){
      if(A.get(i) == B.get(i)){
        count++;
      }
    }
    if(count == A.size()){// returns accordingly
      return true;
    }
    return false;
  }
  return false;
}

void Graph::modifiedDFS()
{// This function calls the DFS function as above and enters the BST trees into a new vector trees as member of class graph.
    int i = 0;  
    while(i < numNodes)
    {// looping through all nodes
        if (isequals(nodes[i].adj, nodes[i].list))
        {
            if (count[i] == 0 or count[i] == 1)
            {// checks the count of node.
                BST *t = new BST();
                DFS(i, t);
                trees.push_back(t);// inserts tree into vector
                connected++;// finds number of connected components
            }
        }
      i++;
  }
  }

void Graph::printResults() {// This function will print the number of connected components and cycles and node based on visiting and BST's.
    int count1=0, count2=0, count3=0;
    cout << "No of Connected Components: " << connected << endl;
    for(int i=0;i<numNodes;i++){
      if(count[i] == 1){// Number of nodes visited once
        count1++;
      }
      else if(count[i] == 2){// Number of nodes visited twice.
        count2++;
      }
    }
    for(int i=0;i<trees.size();i++){// Printing all trees present in trees.
        (trees.get(i))->printBST("");
      }
    int numCycles = 0;
    for (int i = 0; i < numNodes; i++)
    {// Finding total number of nodes present in cycles in graph.
        if (Cycle(i, nodes[i].value))// Checks the presence of node in cycle or not.
        {
            numCycles++;// increments if present in cycle.
        }
    }
    cout << "No. of Nodes in cycles: " << numCycles << endl;// Prints number of nodes in cycles in grapjh.
    cout << "One time visited: " << count1 << endl;// Prints number of nodes visited once in grapjh.
    cout << "Two Time visited: " << count2 << endl;// Prints number of nodes visited twice in graph.
}
#endif
