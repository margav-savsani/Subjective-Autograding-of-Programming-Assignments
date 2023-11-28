#ifndef GRAPH_BST_CPP
#define GRAPH_BST_CPP

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef GRAPH_BST_H
#include "Graph.h"
#endif
void Graph:: DFS(Node v,int num,int check,BST*a){//This helps to traverse the graph and sets the values in the node class appropriately
  int d=v.value;
  a->insert(d);//Here I am inserting the value present in the node on which DFS is being implemented.
  nodes[d-1].visited=nodes[d-1].visited+1;
  int z=0;
  for(int k=0;k<num;k++){//This loop is used to check all the adjacent nodes of the given node
    if(store[(d-1)*num+k]==1){
      if(nodes[k].value!=check){//This will satisfy if the adjacent node is not immediately previous to the present node
        if(nodes[k].visited<2 && edges[(d-1)*num+k]<2){
          store[(k)*num+d-1]=0;
          edges[(d-1)*num+k]=edges[(d-1)*num+k]+1;
          edges[(k)*num+d-1]=edges[(k)*num+d-1]+1;
          DFS(nodes[k],numNodes,d,a);//This makes the recursive call if the above conditions are satisfied
          while(z<num){
             if(store1[(nodes[k].value-1)*num+z]==1 && nodes[z].value!=check){
               if(nodes[z].cycle==1){
                 nodes[k].cycle=1;
                 break;
               }
             }
             z=z+1;
           }
          edges[(d-1)*num+k]=edges[(d-1)*num+k]+1;
          edges[(k)*num+d-1]=edges[(k)*num+d-1]+1;
        }
        else{//This condition holds for the increment of the cycle value which indicates the cycle presence of the node.
          if(nodes[k].visited==2){
          nodes[k].cycle=1;
        }
        }
      }
    }
  }
  return;
}

// Add code as appropriate for your implementation
void Graph::modifiedDFS() {
  for(int j=0;j<numNodes;j++){//This loop is used to go through all the nodes present in the graph
    if(nodes[j].visited==0){
      BST* a=new BST();//This BST is used to insert all the nodes that are present in one connected component
      connected=connected+1;
      DFS(nodes[j],numNodes,-1,a);
      a->printBST("");
    }
  }
  for(int y=0;y<numNodes;y++){//This loop is used to indicate the presence of the node in the cycle.
    if(nodes[y].visited==2){
      nodes[y].cycle=1;
    }
  }
  return;
}

void Graph::printResults() {
  int ones=0;//This indicates the number of nodes that are visited once
  int twos=0;//This indicates the number of nodes that are visited twice.
  int numcy=0;//Number of nodes present in the cycle in the graph.
  for(int u=0;u<numNodes;u++){
    if(nodes[u].cycle==1){
      numcy=numcy+1;
    }
  }
  for(int l=0;l<numNodes;l++){
    if(nodes[l].visited==1){
      temp=temp+nodes[l].value;
      ones=ones+1;
    }
    else if(nodes[l].visited==2){
      twos=twos+1;
    }
  }
  cout<<connected<<endl;
  cout<<ones<<endl;
  cout<<twos<<endl;
  cout<<numcy<<endl;
  return;
}

#endif
