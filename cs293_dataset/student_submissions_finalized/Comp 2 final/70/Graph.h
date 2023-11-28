#ifndef GRAPH_BST_H
#define GRAPH_BST_H

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

using namespace std;

template <typename T> class listOfObjects {
 public:
  T object;
  listOfObjects<T> *next;
  listOfObjects<T> *prev;
  
  // Constructor
  listOfObjects(T initValue) {object = initValue; next = prev = nullptr;}
  
  // Destructor
  ~listOfObjects() {;}

  void insertNode(T object){
    //inserts nodes based on the sorting order of their values
    listOfObjects<T> *iterator = this;
    listOfObjects<T> *lastObject = nullptr;
    if(object->value < iterator->object->value){  //placement at first position
      iterator->next = new listOfObjects(this->object);
      this->object = object;
      return;
    }
    //placement at position other than first
    while(iterator != nullptr){
      if(object->value < iterator->object->value){
        break;
      }
      lastObject = iterator;
      iterator = iterator->next;
    }
    lastObject->next = new listOfObjects(object);
    listOfObjects<T> *currObj = lastObject->next;
    currObj->next = iterator;
  }
  void insert(T object){
    //normal insertion at the end of a list
    listOfObjects<T> *iterator = this;
    listOfObjects<T> *lastObject = nullptr;
    while(iterator != nullptr){
      lastObject = iterator;
      iterator = iterator->next;
    }
    lastObject->next = new listOfObjects(object);
  }
  bool find(T object){
    //find the object in the list
    //returns true if found
    //else returns false
    listOfObjects<T> *iterator = this;
    bool found = false;
    while(iterator != nullptr){
      if(iterator->object == object){
        found = true;
        break;
      }
      iterator = iterator->next;
    }
    return found;
  }
  bool findString(T object){
    //find for string specifically
    listOfObjects<T> *iterator = this;
    bool found = false;
    while(iterator != nullptr){
      if(*(iterator->object) == *object){
        found = true;
        break;
      }
      iterator = iterator->next;
    }
    return found;
  }
  int lengthOfList(){
    //returns the lenght of linked list starting from the position of the object
    listOfObjects<T> *iterator = this;
    int length = 0;
    while(iterator != nullptr){
      length++;
      iterator = iterator->next;
    }
    return length;
  }
};


class Node {
 public:
  int value;
  int label;
  listOfObjects<Node*> *adjacencyListTo;
  listOfObjects<Node*> *adjacencyListFrom;

  listOfObjects<Node*> *similarityList;
  
  // insert other fields and methods as appropriate
};


class Graph {
  int numNodes;
  int numEdges;

  Node *nodes;

  // Add appropriate fields as necessary for your implementation
  
 public:
  Graph(int numNodes){
    this->numNodes = numNodes;
    nodes = new Node[numNodes];

    for (int i = 0; i < numNodes; i++) {
      nodes[i].value = i+1;
      nodes[i].label = i+1;
    }
    numEdges = 0;
  }
  void insertEdge(int n1, int n2){
    numEdges++;
    if(nodes[n1 - 1].adjacencyListTo == nullptr){
      nodes[n1 - 1].adjacencyListTo = new listOfObjects(&nodes[n2 - 1]);
    }
    else{
      nodes[n1 - 1].adjacencyListTo->insertNode(&nodes[n2 - 1]);
    }
    if(nodes[n2 - 1].adjacencyListFrom == nullptr){
      nodes[n2 - 1].adjacencyListFrom = new listOfObjects(&nodes[n1 - 1]);
    }
    else{
      nodes[n2 - 1].adjacencyListFrom->insertNode(&nodes[n1 - 1]);
    }
  }
  string printSrcNodes(){
    string srcNodes = "";
    for(int i = 0; i < numNodes; i++){
      if(nodes[i].adjacencyListFrom == nullptr){
        if(srcNodes == ""){
          srcNodes += to_string(nodes[i].value);
        }
        else{
          srcNodes += " " + to_string(nodes[i].value);
        }
      }
    }
    return srcNodes;
  }

  void findNupdateLabel(Node* node){
    for(int i = 0; i < numNodes; i++){
      if(nodes[i].similarityList->find(node)){
        updateLabel(&nodes[i]);
      }
    }
  }

  void updateLabel(Node* majorNode){
    int maxLabel = majorNode->label;
    
    listOfObjects<Node*> *iterator = majorNode->similarityList;

    while(iterator != nullptr){
      if(iterator->object->label > maxLabel){
        maxLabel = iterator->object->label;
      }
      iterator = iterator->next;
    }
    iterator = majorNode->similarityList;

    if(maxLabel != majorNode->label){
      majorNode->label = maxLabel;
      findNupdateLabel(majorNode);
    }
    while(iterator != nullptr){
      if(maxLabel != iterator->object->label){
        iterator->object->label = maxLabel;
        updateLabel(iterator->object);
        findNupdateLabel(iterator->object);
      }
      iterator = iterator->next;
    }
  }

  bool checkSimilarity(Node* n1, Node* n2){
    bool similar = false;
    if(n1->adjacencyListFrom == nullptr && n2->adjacencyListFrom == nullptr && n1->similarityList->find(n2)){
      //source nodes and user specified
      return true;
    }
    else if(n1->adjacencyListFrom->find(n2) && n1->adjacencyListFrom->lengthOfList() == 1){
      //directed edge from n2 to n1
      return true;
    }
    else if(n1->adjacencyListFrom != nullptr && n2->adjacencyListFrom != nullptr){
      //non source nodes
      
      //checking similarity for from list of n1 first
      listOfObjects<Node*> *n1Iterator = n1->adjacencyListFrom;
      listOfObjects<Node*> *n2Iterator = n2->adjacencyListFrom;
      while(n1Iterator != nullptr){
        bool foundSimilar = false;
        while(n2Iterator != nullptr){
          foundSimilar = checkSimilarity(n1Iterator->object, n2Iterator->object);
          if(foundSimilar){
            break;
          }
          n2Iterator = n2Iterator->next;
        }
        if(!foundSimilar){
          return false;
        }
        n2Iterator = n2->adjacencyListFrom;
        n1Iterator = n1Iterator->next;
      }
      n1Iterator = n1->adjacencyListFrom;
      n2Iterator = n2->adjacencyListFrom;
      //checking similarity for from list of n2 now
      while(n2Iterator != nullptr){
        bool foundSimilar = false;
        while(n1Iterator != nullptr){
          foundSimilar = checkSimilarity(n2Iterator->object, n1Iterator->object);
          if(foundSimilar){
            break;
          }
          n1Iterator = n1Iterator->next;
        }
        if(!foundSimilar){
          return false;
        }
        n1Iterator = n1->adjacencyListFrom;
        n2Iterator = n2Iterator->next;
      }
      similar = true;
    }
    return similar;
  }

  void updateSimilarity(int n1, int n2){
    if(nodes[n1 - 1].similarityList == nullptr){
      nodes[n1 - 1].similarityList = new listOfObjects(&nodes[n2 - 1]);
    }
    else{
      nodes[n1 - 1].similarityList->insertNode(&nodes[n2 - 1]);
    }
  }
  void checkNupdateSimilarity(){
    for(int i = 0; i < numNodes; i++){
      for(int j = 0; j < numNodes; j++){
        if(nodes[i].similarityList->find(&nodes[j])){
          continue;
        }
        else{
          if(checkSimilarity(&nodes[i], &nodes[j])){
            updateSimilarity(nodes[i].value, nodes[j].value);
          }
        }
      }
    }
  }
  string printSimilarNodes(){
    string similarNodes = "";
    for(int i = 0; i < numNodes; i++){
      listOfObjects<Node*>* iterator = nodes[i].similarityList;
      while(iterator != nullptr){
        if(similarNodes == ""){
          similarNodes += "(" + to_string(nodes[i].value) + ", " + to_string(iterator->object->value) + ")";
        }
        else{
          similarNodes += " (" + to_string(nodes[i].value) + ", " + to_string(iterator->object->value) + ")";
        }
        iterator = iterator->next;
      }
    }
    return similarNodes;
  }

  void printCollapsedGraph(ofstream* outfile){
    for(int i = 0; i < numNodes; i++){
      updateLabel(&nodes[i]);
    }
    listOfObjects<int> *finalNodesList = new listOfObjects(0);
    int lengthOfNodesList = 1;
    listOfObjects<string*> *edgeList = new listOfObjects(new string(""));
    int lenEdgeList = 1;
    for(int i = 0; i < numNodes; i++){
      if(!finalNodesList->find(nodes[i].label)){
        finalNodesList->insert(nodes[i].label);
        lengthOfNodesList++;
      }
      listOfObjects<Node*> *iterator = nodes[i].adjacencyListTo;
      while(iterator != nullptr){
        if(iterator->object->label == iterator->object->value && nodes[i].label != iterator->object->label){
          string edge = to_string(nodes[i].label) + " " + to_string(iterator->object->value);
          string* pEdge = new string(edge);
          if(!edgeList->findString(pEdge)){
            edgeList->insert(pEdge);
            lenEdgeList++;
          }
        }
        iterator = iterator->next;
      }
    }

    string finalNodes = to_string(lengthOfNodesList-1) + ":";
    listOfObjects<int>* iterForNodes = finalNodesList;
    while(iterForNodes != nullptr){
      if(iterForNodes->object != 0){
        finalNodes += " " + to_string(iterForNodes->object);
      }
      iterForNodes = iterForNodes->next;
    }
    *outfile<<finalNodes<<endl;

    listOfObjects<string*> *iterForEdgeList = edgeList;
    for(int i = 0; i < lenEdgeList; i++){
      if(*(iterForEdgeList->object) != ""){
        *outfile<<*(iterForEdgeList->object)<<endl;
      }
      iterForEdgeList = iterForEdgeList->next;
    }
  }
};

#endif
