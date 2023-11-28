#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string>
#include <sstream>
#include <cstring>
#include <cctype>

class Node {
 public:
  int value;
  Node *next;
  Node *incoming_node ;
  Node *outgoing_node;
  Node *eq;
  int inc_cnt = 0;
  Node(){};

  Node(int val){
    value = val;
  } 
};



 
  
// class Graph {
//   int numNodes;
//   int numEdges;
//   std::fstream graphFile;
  
//   int cnt = 0 ;
//   Node *nodes;
//   int *visited ;
//   int *parent_node ;
  
//  public:
//   Graph(int nNodes, int nEdges, std::string gFileName) {
//     numNodes = nNodes;
//     numEdges = nEdges;
//     visited = new int[numNodes];
//     parent_node = new int[numNodes];
    
//     graphFile.open(gFileName, std::ios::out);
//     if (!graphFile.is_open()) {
//       std::cerr << "Couldn't open graph file " << gFileName << ". Aborting ..." << std::endl;
//       exit(-1);
//     }
//     graphFile << numNodes << std::endl;
//     graphFile << numEdges << std::endl;

//     nodes = new Node[numNodes];
//     if (nodes == nullptr) {
//       std::cerr << "Memory allocation failure." << std::endl;
//       exit(-1);
//     }

//     for (int i = 0; i < numNodes; i++) {
//       nodes[i].value = i+1;
//       visited[i]=0;
//       parent_node[i]=0;
//     }

//     srand(time(0));
//     int n1, n2;
//     int countEdges = 0;
    
//     while (countEdges < numEdges) {
//       do {
// 	      n1 = rand() % numNodes;
// 	      n2 = rand() % numNodes;
//       } while (n1 == n2);
//       Node *trav = &nodes[n1];
//       bool found = false;
//       while(trav->next!=nullptr){
//         if(trav->next->value == n2+1){
//           found = true;
//           break;
//         }
//         trav = trav->next;
//       }
      
//       if(found == true){
//         continue;
//       }

//       else{
//         trav->next = new Node(n2+1);
//         Node *temp = &nodes[n2];
//         while(temp->next != nullptr){
//           temp = temp->next;
//         }
//         temp->next = new Node(n1+1);
//       }
      
//       graphFile << n1+1 << " " << n2+1 << std::endl;

//       countEdges++;

//     }
    
//   }
      
//   ~Graph() {
//     if (graphFile.is_open()) {
//       graphFile.close();
//     }
//     delete[] nodes;
 
//   }
// };



   