#include "std_headers.h"

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
};

//node of graph
class Node{
public:
  int value;
  listOfObjects<Node*> *childAdjacency;
  listOfObjects<Node*> *similar;
  listOfObjects<Node*> *parentAdjacency;
  listOfObjects<Node*> *similar1;
  listOfObjects<Node*> *finalParent;

  Node(int val){
    value = val;
    childAdjacency = nullptr;
    similar = nullptr;
    parentAdjacency = nullptr;
    similar1=nullptr;
    finalParent=nullptr;
  }

  Node(){
    value = 0;
    childAdjacency = nullptr;
    similar = nullptr;
    parentAdjacency = nullptr;
    similar1=nullptr;
    finalParent=nullptr;
  }
};

class Graph
{
public:
  int numNodes;
  ifstream graphFile;
  Node *nodes;
  listOfObjects<Node*>* sourceNodes;
  listOfObjects<Node*>* allNodes;

  //constructor
  Graph(int nNodes, string gFileName)
  {
    sourceNodes = nullptr;
    numNodes = nNodes;
    graphFile.open(gFileName);
    if (!graphFile.is_open())
    {
      cerr << "Couldn't open graph file " << gFileName << ". Aborting ..." << endl;
      exit(-1);
    }

    nodes = new Node[numNodes];
    if (nodes == nullptr)
    {
      cerr << "Memory allocation failure." << endl;
      exit(-1);
    }

    for (int i = 0; i <numNodes; i++)
    {
      nodes[i].value = i+1;
      if(allNodes==nullptr){
        allNodes = new listOfObjects<Node*>(&nodes[i]);
      }else{
        listOfObjects<Node*>* a = allNodes;
        while(a->next!=nullptr){
          a=a->next;
        }
        a->next=new listOfObjects<Node*>(&nodes[i]);
      }
    }

    //to take input and add edge between the nodes
    string myline;
    int k=0;
    int val1,val2;
    while (getline(graphFile, myline)){
      if(k==0){
        k++;
        continue;
      }
      if(myline[0]=='-'){
        break;
      }
      bool isSpacePresent = false;
      int spacePos=0;
      for(int i=0; i<myline.length(); i++){
          if(myline[i]==' '){
              isSpacePresent = true;
              break;
          }
          spacePos++;
      }
      if(isSpacePresent){
          int val1 = stoi(myline);
          string newLine;
          for(int i=spacePos+1; i<myline.length(); i++){
              newLine = newLine + myline[i];
          }
          int val2 = stoi(newLine);
          makeDirectedEdge(val1, val2);
      }
    }
    graphFile.close();
    graphFile.open(gFileName);
    int p=0;
    while(getline(graphFile, myline)){
      if(myline[0]!='-'){
        p++;
      }else{
        break;
      }
    }
    //taking input from file to access the similar nodes given by the user
    while(getline(graphFile, myline)){
      if(myline[0]=='-'){
        break;
      }
      bool isSpacePresent = false;
      int spacePos=0;
      for(int i=0; i<myline.length(); i++){
          if(myline[i]==' '){
              isSpacePresent = true;
              break;
          }
          spacePos++;
      }
      if(isSpacePresent){
        int val1 = stoi(myline);
        string newLine;
        for(int i=spacePos+1; i<myline.length(); i++){
            newLine = newLine + myline[i];
        }
        int val2 = stoi(newLine);
        Node* node1 = &nodes[val1-1];
        Node* node2 = &nodes[val2-1];
        if(node1->similar==nullptr){
          node1->similar = new listOfObjects<Node*>(node2);
        }else{
          listOfObjects<Node*>* a = node1->similar;
          while(a->next!=nullptr){
            a=a->next;
          }
          a->next = new listOfObjects<Node*>(node2);
        }
      }
    }
  }

  //destructor
  ~Graph()
  {
    if (graphFile.is_open())
    {
      graphFile.close();
    }
    delete[] nodes;
  }


  void makeDirectedEdge(int n1, int n2);
  void printChildAdjacencyList();
  void printParentAdjacencyList();
  void printSimilarList();
  void printSimilar1List();
  void similarRule3();
  void similarRule2a();
  void similarRule2b();
  bool isSimilar(int val1, int val2);
  void similar();
  bool condition(Node* node1, Node* node2);
  void printResults();
  void collapse1();
  void collapse2();
  void collapse3();
  void copySimilar();
  Node* collapse2nodes(Node* node1, Node* node2);
  int distinct();
};