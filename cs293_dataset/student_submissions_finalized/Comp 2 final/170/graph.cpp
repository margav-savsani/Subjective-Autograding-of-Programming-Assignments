#ifndef GRAPH_BST_CPP
#define GRAPH_BST_CPP

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef GRAPH_BST_H
#include "graph.h"
#endif

bool Graph::similar(int a , int b){
  for(int i=0; left[i] != -1; i++){       //checking whether the elements are in the similarity list
    if(left[i] == a && right[i] == b)return true;
  }
  if(nodes[a-1].incoming[0] == -1 || nodes[b-1].incoming[0] == -1) return false;    //if elements are source nodes then return

  for(int i=0; nodes[a-1].incoming[i] != -1; i++){        //checking for the similarity condition from incoming elements of a to b
    int count1 = 0;
    for(int j=0; nodes[b-1].incoming[j] != -1; j++){
      if(similar(nodes[a-1].incoming[i], nodes[b-1].incoming[j]))count1++;
    }
    if(count1 == 0)return false;
  }

  for(int i=0; nodes[b-1].incoming[i] != -1; i++){        //checking for the similarity condition from incoming elements of b to a
    int count2 = 0;
    for(int j=0; nodes[a-1].incoming[j] != -1; j++){
      if(similar(nodes[a-1].incoming[i], nodes[b-1].incoming[j]))count2++;
    }
    if(count2 == 0)return false;
  }

  graphone<<"("<<a<<", "<<b<<")"<<" ";        //printing the pair
  int c = 0;
  while(left[c] > -1){            //if above two satisfies then append the pair to the similarity list
    c++;
  }
  left[c] = a;
  right[c] = b;
  return true;
}

void Graph::similar_nodes(){

  while(true){              //taking input-source pairs which are similar
    int n1;
    cin>>n1;
    if(n1 == -1) break;
    int n2;
    cin>>n2;
    graphone<<"("<<n1<<", "<<n2<<")"<<" ";        //printing the pairs
    int a = 0;
    while(left[a] > -1){          //storing the pairs
      a++;
    }
    left[a] = n1;
    right[a] = n2;
  }

  for(int i=0; i<numNodes; i++){        //checking for all the 
    if(nodes[i].incoming[0] == -1) continue;
    if((nodes[i].incoming[0] > -1) && (nodes[i].incoming[1] == -1)){
      graphone<<"("<<i+1<<", "<<nodes[i].incoming[0]<<")"<<" ";
      int b = 0;
      while(left[b] > -1){
        b++;
      }
      left[b] = i+1;
      right[b] = nodes[i].incoming[0];
      if(nodes[nodes[i].incoming[0]-1].incoming[0] > -1){
        for(int j=0; j<numNodes; j++){
          similar(i+1, j+1);
        }
      }
    }
    else{
      for(int j=0; j<numNodes; j++){
        similar(i+1, j+1);
      }
    }
  }
}

void Graph::printResults() {
  graphone<<"Source nodes:";
  for(int i=0; i<numNodes; i++){
    if(nodes[i].incoming[0] == -1)graphone<<i+1<<" ";
    if(i == numNodes-1)graphone<<endl;
  }

  graphone<<"Similar node pairs:";
  similar_nodes();
  graphone<<endl;
}

#endif