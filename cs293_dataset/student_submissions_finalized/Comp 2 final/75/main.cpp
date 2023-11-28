#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

using namespace std;

#ifndef GRAPH_BST_CPP
#include "Graph.cpp"
#endif

#include<iostream>
#include<fstream>


int main(int argc, char **argv)
{
  
  int numNodes = 0;
  int numEdges = 0;
  // reading numnodes from graphFile
  ofstream outfile;
  outfile.open("outgraph.txt");
  cin>>numNodes;
  bool source[numNodes]; // stores whether the given node is a source node or not
  for(int i = 0; i< numNodes;i++){
    source[i] = true;
  }
  Graph *newGraph; // to store the edges of the new graph created from the relations specfified by the user
  newGraph = new Graph(numNodes);

  Graph *relation; // to store the relations specified by the user
  relation = new Graph(numNodes);

  if (newGraph == nullptr || relation == nullptr) {
    cerr << "Memory allocation failure." << endl;
    exit(-1);
  }

  // reading the edges from the file
  int n1,n2;
  cin>>n1; cin>>n2;
  source[n2 - 1] = false;
  while(n1 != -1 and n2 != -1){
    newGraph->insert(n1-1,n2-1);
    numEdges++;
    source[n2 - 1] = false;
    cin>>n1; cin>>n2;
  }
  // printing the source edges from the graph
  outfile<<"Source nodes: ";
  for (int i = 0; i< numNodes;i++){
    if(source[i] == true){
        outfile<<(i+1)<<" ";
        newGraph->numSource++;
    }
  }
  
  int* sourceArray = new int[newGraph->numSource];
  int j = 0;
  for (int i = 0; i<numNodes;i++){
    if(source[i] == true){
        sourceArray[j] = i+1;
        j++;
    }
  }
  // reading the relations from the file
  cin>>n1; cin>>n2;
  while(n1 != -1 and n2 != -1){
    // to insert the relation into the new graph iff it is present in the relations according to RULE 1
    if(source[n1-1] == true && source[n2-1] == true){
        relation->insert(n1-1,n2-1);
    }
    numEdges++;
    cin>>n1; cin>>n2;
  }
  newGraph->topologicalSort(sourceArray);
  outfile<<endl;
  int maxpath = 0;
  for (int i = 0; i<numNodes;i++){
    maxpath = max(maxpath, newGraph->maxDistance[i]);
  }
  for (int i = 1; i<=maxpath;i++){
    int countnum  = 0;// counts the number of nodes in a single level - seperated according to the max distances
    for (int j = 0;j<numNodes;j++){
        if (newGraph->maxDistance[j] == i){
            countnum++;
        }
    }
  
  int* levelNodes = new int[countnum]; // to store the labels of all the 
  int j = 0;

   for (int k = 0;k <numNodes;k++){
      if (newGraph->maxDistance[k] == i){
          levelNodes[j] = k+1;
          j++;
      }
    }

    for (int x = 0; x<countnum;x++){// iterating through all pairs of vertices on a level
        for (int y = x;y<countnum;y++){
            // iterating through the parents of the nodes in a level
            // iterate in the list and do find links in the relation graph
            // if correct condition then add new relation

            //checking the relations of one parent with other
            bool addRel1 = true;
            listOfObjects<int>* parentx = newGraph->parents[levelNodes[x]-1].journeys;
            while(parentx!=nullptr){
                listOfObjects<int>* parenty = newGraph->parents[levelNodes[y]-1].journeys;
                bool foundForOneParent = false;
                while(parenty!=nullptr){
                    if(relation->find(parentx->object, parenty->object)){
                        foundForOneParent = true;
                        break;
                    }
                    parenty = parenty ->next;
                }
                if(!foundForOneParent){
                    addRel1 = false;
                    break;
                }
                parentx = parentx->next;
            }

            bool addRel2 = true;
            //checking the relations of one parent with other
            listOfObjects<int>*  parenty = newGraph->parents[levelNodes[y]-1].journeys;
            while(parenty!=nullptr){
                listOfObjects<int>* parentx = newGraph->parents[levelNodes[x]-1].journeys;
                bool foundForOneParent = false;
                while(parentx!=nullptr){
                    if(relation->find(parenty->object, parentx->object)){
                        foundForOneParent = true;
                        break;
                    }
                    parentx = parentx ->next;
                }
                if(!foundForOneParent){
                    addRel2 = false;
                    break;
                }
                parenty = parenty->next;
            }

            if (addRel1 && addRel2){
                // adding relations fro both sides
                relation->insert(levelNodes[x]-1,levelNodes[y]-1);
                relation->insert(levelNodes[y]-1,levelNodes[x]-1);
            }
        }
    }
  }

  for (int i = 0; i<numNodes;i++){
    if(newGraph->inEdges[i]==1){// to check for number of incoming edges
        relation->insert(i,newGraph->parents[i].journeys->object-1);
    }
  }
  //printing similar node pairs
  outfile<<endl;
  outfile<<"Similar node Pairs: ";
  for(int i = 0; i< numNodes;i++){
    Node* currNode = relation->nodes[i].list;
    while(currNode!=nullptr){
        outfile<<"("<<(i+1)<<","<<currNode->value<<") ";
        currNode = currNode->next;
    }
  }
  outfile<<endl;

  
// Take symmetric closure
  for(int i = 0; i< numNodes;i++){
    Node* currNode = relation->nodes[i].list;
    while(currNode!=nullptr){
        relation->insert(currNode->value-1, i);
        currNode = currNode->next;
    }
  }
  relation->DFS(); // to find the connected components
  int* maxCollapse = new int[numNodes];
  int* collapsedNodes = new int[relation->numComponents-1];
  for (int i =0 ;i<relation->numComponents;i++){
    int maxNode = -1;
    for (int j = 0; j<numNodes;j++){
        if (relation->compNum[j] == i){
            maxNode = max(maxNode, (j+1));
        }
    }
    collapsedNodes[i]=maxNode; 
    for (int j = 0; j<numNodes;j++){
        if (relation->compNum[j] == i){
            maxCollapse[j] = maxNode;
        }
    }
  }
  outfile<<endl;
  outfile<<"Collapsed graph: "<<endl;
  outfile<<(relation->numComponents)<<": ";
  for(int i = 0;i<relation->numComponents;i++){
    outfile<<collapsedNodes[i]<<" ";
  }

  Graph *collapsed; // to store the relations specified by the user
  collapsed = new Graph(numNodes);

  for(int i = 0;i<numNodes;i++){
    Node* currNode = newGraph->nodes[i].list;
    while(currNode!=nullptr){
        if(maxCollapse[i]!=maxCollapse[currNode->value -1]){
            collapsed->insert(maxCollapse[i]-1, maxCollapse[currNode->value -1]-1);
        }
            currNode = currNode->next;
        
    }
  }
  outfile<<endl;
  //printing the final graph edges - collapsed graph
    for(int i = 0; i< numNodes;i++){
    Node* currNode = collapsed->nodes[i].list;
    while(currNode!=nullptr){
        outfile<<(i+1)<<" "<<currNode->value<<endl;
        currNode = currNode->next;
    }
  }    
  outfile.close();
  return 0;
}