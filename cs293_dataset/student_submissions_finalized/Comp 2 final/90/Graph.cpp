#ifndef GRAPH_BST_CPP
#define GRAPH_BST_CPP

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef GRAPH_BST_H
#include "Graph.h"
#endif

//Prints the source Nodes
//Done in O(n), linear time, where n is numNodes
void Graph::printSourceNodes(){
  myfile << "Source Nodes: ";
  for(int i=0;i<numNodes;i++){
    //Those nodes which have no nodes incidenting
    //on them are source nodes, hence here,
    //if the adjacentfrom list is empty then it is
    //a source node
    if(nodes[i].adjacencyfrom.size() == 0){
      nodes[i].sourceNode = true;
      myfile << nodes[i].value << " ";
    }
  }
  myfile << endl << endl;
}

//Prints similar nodes and number of components
//for the new graph ideated as earlier
void Graph::printSimilarNodes(){
  bool similar[numNodes][numNodes]; // A boolean of size n^2, to store if [i,j] is similar
  // Initial values being false
  for(int i=0; i<numNodes; i++){
    for(int j=0; j<numNodes; j++){
      similar[i][j] = false;
    }
  }
  //Similarity according to condition 3
  for(int i=0; i<numNodes; i++){
    if(nodes[i].adjacencyfrom.size() == 1){
      //nodes with a single node incident on them
      nodes[i].similarnodes.push(nodes[i].adjacencyfrom.get(0)->value);
      similar[i][nodes[i].adjacencyfrom.get(0)->value-1] = true; //updating similar boolean
    }
  }
  //Similarity according to condition 2
  for(int i=0; i<numNodes;i++){
    for(int j=0;j<numNodes;j++){
      if(i != j && !nodes[i].sourceNode && !nodes[j].sourceNode && !similar[i][j]){
        if(check_similarity_recursively(&nodes[i], &nodes[j]) && check_similarity_recursively(&nodes[j], &nodes[i])){
          nodes[i].similarnodes.push(j+1);
          nodes[j].similarnodes.push(i+1);
          // Updating similar boolean
          similar[i][j] = true;
          similar[j][i] = true;
        }
      }
    }
  }
  myfile << "Similar Nodes: ";
  for(int i=0; i<numNodes; i++){
    //Printing the similar nodes
    for(int j=0; j < nodes[i].similarnodes.size();j++){
      //As we push, we simultaneously develop the newsimilarnodes list
      //as follows, now we just collapse similar nodes, so if a is similar to b
      //now b is also similar to a for the new graph designed, and in this new graph
      //the similarity represents the edges
      nodes[i].newsimilarnodes.push(nodes[i].similarnodes.get(j));
      nodes[nodes[i].similarnodes.get(j)-1].newsimilarnodes.push(i+1);
      myfile << "(" << i+1 << " " << nodes[i].similarnodes.get(j) << ")" << " ";
    }
  } 
  myfile << endl << endl;
}

// Does DFS on a new graph
// This new graph is an undirected graph with 
// Edges defined by the similar relation
// i.e., there is an edge between n1 and n2
// iff n1 is similar to n2 in the original graph
// the user had input
int Graph::DFS(int index){
  nodes[index].visited = true; //marking visited true
  newlyvisit[index] = true; //temporary new visit marked true to show that it belongs to this component
  int maximum = index+1;
  for(int i=0; i<nodes[index].newsimilarnodes.size();i++){
    int adj_index = nodes[index].newsimilarnodes.get(i)-1;
    if(!nodes[adj_index].visited){
      maximum = max(maximum,DFS(adj_index)); //Recursively computing the maximum by doing DFS on unvisited children nodes
    }
  }
  return maximum;
}


// Our newly created graph may not be connected
// Hence we shall do DFS to cover all points and 
// count all connected components and 
//collapses them to the maximum value in the component
//and prints the vertices of this collapsed graph
void Graph::doDFS(){
  myfile << "Collapsed Graph:\n";
  int count = 0; //counting for number of compoenent in the new graph
  string str = ""; //stores list of vertices in new graph
  while(true){
    int unvisited = -1; //unvisited node
    for(int i=0; i<numNodes; i++){
      if(!nodes[i].visited){
        unvisited = i;
        break;
      }
    }
    if(unvisited == -1) break; //break if all nodes visited atleast once
    int maximum = DFS(unvisited);
    for(int i=0; i<numNodes; i++){
      if(newlyvisit[i]) leader[i] = maximum; //leader for all the elements of this compoenent set to maximums
    }
    reset_newly_visit(); //resetting the newlyvisit boolean for next round of DFS
    str += to_string(maximum) + " "; //storing the output in a string
    count++; //counting for number of compoenent in the new graph
  }
  myfile << count << ": " <<  str << endl;
}

//Prints the edges of the collapsed graph
void Graph::printCollapsedGraph(){

  bool edges[numNodes][numNodes]; //Another boolean to just check the existence of edges of size n^2
  //Intialily all elements in edges are false
  for(int i=0; i<numNodes;i++){
    for(int j=0; j<numNodes;j++){
      edges[i][j]=false;
    }
  }

  //Adding edges, but calculated with their leaders, as they 
  //have collapsed to it
  for(int i=0; i<numNodes; i++){
    for(int j=0; j<nodes[i].adjacencyto.size();j++){
      edges[leader[i]-1][leader[nodes[i].adjacencyto.get(j)->value-1]-1] = true;
    }
  }

  //Finally printing the edges
  for(int i=0; i<numNodes;i++){
    for(int j=0; j<numNodes;j++){
      if(edges[i][j] && i!=j)
        myfile << i+1 << " " << j+1 << endl;
    }
  }
}  

#endif
