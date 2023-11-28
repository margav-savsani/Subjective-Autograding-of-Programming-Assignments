#ifndef GRAPH_BST_CPP
#define GRAPH_BST_CPP

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef GRAPH_BST_H
#include "Graph.h"
#endif


//DFS for each connected component
BST* Graph::myDFS(int index, int index_parent, bool visited1[], bool visited2[]){
  static int recursionLevel = -1;
  static BST *Tree = nullptr;
  static int time = 0;
  if(recursionLevel == -1)
  {
    Tree = new BST();
  }
  if(!visited1[index]){
    visited1[index]=true;
  }else{
    visited2[index]=true;
  }
  Node node = nodes[index];
  nodes[index].start = time++;
  Tree->insert(node.value);
  // cout<<node.value<<" ";
  listOfObjects<Node*>* adj = node.adjacency;
  //iterate over all the adjacents nodes of the node
  while(adj!=nullptr){
    //checking for visited_once
    if(!visited1[adj->object->value-1]){
      if(adj->object->value-1 != index_parent && &nodes[adj->object->value-1]!=nodes[index].parent1 && &nodes[adj->object->value-1]!=nodes[index].parent2){
        recursionLevel++;
        nodes[adj->object->value-1].parent1 = &nodes[index];
        myDFS(adj->object->value-1, index, visited1, visited2);
        recursionLevel--;
      }
    }
    //checking for visited_twice
    if(!visited2[adj->object->value-1]){
      if(adj->object->value-1 != index_parent && &nodes[adj->object->value-1]!=nodes[index].parent1 && &nodes[adj->object->value-1]!=nodes[index].parent2){
        recursionLevel++;
        nodes[adj->object->value-1].parent2 = &nodes[index];
        myDFS(adj->object->value-1, index, visited1, visited2);
        recursionLevel--;
      }
    }
    adj = adj->next;
  }
  if(recursionLevel == -1)
  {
    cout<<endl;
    Tree->printBST("");
  }
}


void Graph::modifiedDFS(){
  bool visited_once[numNodes];
  for(int i=0; i<numNodes; i++){
    visited_once[i]=false;
  }

  bool visited_twice[numNodes];
  for(int i=0; i<numNodes; i++){
    visited_twice[i]=false;
  }
  for(int i=0; i<numNodes; i++){
    if(!nodes[i].visited1){
      myDFS(i, -1, visited_once, visited_twice);
      for(int i=0; i<numNodes; i++){
        if(visited_once[i]){
          nodes[i].visited1=1;
        }else{
          nodes[i].visited1=0;
        }
        if(visited_twice[i]){
          nodes[i].visited2=1;
        }else{
          nodes[i].visited2=0;
        }
      }
      numConnected++;
    }
    if(nodes[i].visited2==0 || nodes[i].isEndNode()==1){
      nodes[i].isInCycle=0;
    }
    if(nodes[i].isInCycle){
      numCycles++;
    }
  }
}

void Graph::printResults(){
  int nodesVisitedOnce=0;
  int nodesVisitedTwice=0;
  for(int i=0; i<numNodes; i++){
    if(nodes[i].visited1){
      nodesVisitedOnce++;
    }
    if(nodes[i].visited2){
      nodesVisitedTwice++;
    }
  }
  cout<<"No. of connected components: "<<numConnected<<endl;
  cout<<"No. of nodes visited once: "<<numNodes-nodesVisitedTwice<<endl;
  cout<<"No. of nodes visited twice: "<<nodesVisitedTwice<<endl;
  cout<<"No. of nodes that are present in a cycle: "<<numCycles<<" ( ";
  //checking for nodes in cycle
  for(int i=0; i<numNodes; i++){
    if(nodes[i].isInCycle){
      cout<<nodes[i].value<<" ";
    }
  }cout<<")"<<endl;
}

// void Graph::DFS(int index)
// {
//     // Initially mark all vertices as not visited
//     // vector<bool> visited1(numNodes+1, false);
//     bool visited1[numNodes+1];
//     bool visited2[numNodes+1];
//     for(int i=0; i<numNodes+1; i++){
//       visited1[i]=false;
//       visited2[i]=false;
//     }

//     // vector<bool> visited2(numNodes, false);
//     // Create a stack for DFS

//     stack<Node*> stack;
//     Node* parentTemp = nullptr;
//     Node* popTemp = nullptr;

//     // Push the current source node.
//     Node* node = &nodes[index];
//     stack.push(node);

//     while (!stack.empty())
//     {
//         // Pop a vertex from stack and print it
//         Node* s = stack.top();
//         if(popTemp!=nullptr){
//           if(s==popTemp->parent1 || s==popTemp->parent2){
//             stack.pop();
//             continue;
//           }
//         }
//         popTemp=s;
//         if(!visited1[s->value] || !visited2[s->value]){
//           if(s->parent1==nullptr){
//             s->parent1 = parentTemp;
//           }else{
//             s->parent2 = parentTemp;
//           }
//           parentTemp = s;
//         }

//         stack.pop();

//         if (!visited1[s->value])
//         {
//             cout << s->value << " ";
//             visited1[s->value] = true;
//         }
//         else{
//           if(!visited2[s->value]){
//             cout<< s->value <<" ";
//             visited2[s->value] = true;
//           }
//         }

//         // Get all adjacent vertices of the popped vertex s
//         // If a adjacent has not been visited, then push it
//         // to the stack.
//         listOfObjects<Node*> *a = s->adjacency;
//         while(a!=nullptr){
//           if(!visited1[a->object->value] || !visited2[a->object->value]){
//             stack.push(a->object);
//           }
//           a=a->next;
//         }
//     }
//     cout<<endl;
//     for(int i=0; i<numNodes; i++){
//       if(nodes[i].parent1!=nullptr){
//         cout<<"parent1 of "<<nodes[i].value<<" is "<<nodes[i].parent1->value<<endl;
//       }else{
//         cout<<"parent1 of "<<nodes[i].value<<" is "<<"noone"<<endl;
//       }
//     }

//     for(int i=0; i<numNodes; i++){
//       if(nodes[i].parent2!=nullptr){
//         cout<<"parent2 of "<<nodes[i].value<<" is "<<nodes[i].parent2->value<<endl;
//       }else{
//         cout<<"parent2 of "<<nodes[i].value<<" is "<<"noone"<<endl;
//       }
//     }
// }


#endif