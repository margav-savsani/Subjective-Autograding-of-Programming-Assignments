#ifndef GRAPH_BST_H
#define GRAPH_BST_H
#include <string>
#include<iostream>
#include <fstream>
#ifndef STD_HEADERS_H
#endif
using namespace std;


// class BSTNode;

// class BST {
//   // Add your own field and members here
//  public:
//   BSTNode *root;
//   BST* nextTree;
//   BST* prevTree;
//   // Feel free to use the printBST function used earlier
//   BST(){root = nullptr; nextTree = nullptr; prevTree = nullptr;}
//   bool insert(int val);
// void printBST(const string& prefix, bool isLeft);
// };

// class BSTNode{
//  public:
//   int value;
//   BSTNode *left;
//   BSTNode *right;
//   BSTNode *parent;
  

//   BSTNode(int val){value = val; left = nullptr; right = nullptr; parent = nullptr;}
//   BSTNode(){}
// };

class Node;

class LinkedList{
 public:
  Node* store;
  LinkedList* next;
  LinkedList(){store = nullptr; next = nullptr;} 
  LinkedList(Node *val){store = val; next = nullptr;}
};

class Node {
 public:
  int value;
  LinkedList *adjacentList;
  LinkedList *adjListLastEle;
  LinkedList *FromAdjListLastEle;
  LinkedList *FromAdjList;
  LinkedList *SimilarTo;
  LinkedList *SimilarFrom;

  Node(int val, int numNodes){
    value = val;
    adjacentList = nullptr; // it has valid values in indexes 1-N (not 0)
    adjListLastEle = nullptr;
    FromAdjList = nullptr;
    FromAdjListLastEle = nullptr;
    SimilarTo = nullptr;
    SimilarFrom = nullptr;
  }
  Node(){}
  // insert other fields and methods as appropriate
};

class Graph {
  int numNodes;
//   int numEdges;
  int nConnectedComponents;
//   fstream graphFile;

  Node *nodes;
  bool *marked;
  bool *sources;
    ofstream outfile;

//   int *visits;
//   int *firstPredecessor;
//   bool *incycle;
//   BST* trees;

  // Add appropriate fields as necessary for your implementation
  
 public:
  Graph(int nNodes) {
    numNodes = nNodes;
    // numEdges = nEdges;
    // nConnectedComponents = 0;
    // graphFile.open(gFileName, ios::out);
    // if (!graphFile.is_open()) {
    //   cerr << "Couldn't open graph file " << gFileName << ". Aborting ..." << endl;
    //   exit(-1);
    // }

    // outfile = f;
    // graphFile << numNodes << endl;
    // graphFile << numEdges << endl;
    nodes = new Node[numNodes];
    marked = new bool[numNodes];
    sources = new bool[numNodes];

    // visits = new int[numNodes];
    // firstPredecessor = new int[numNodes];
    // incycle = new bool[numNodes];
    // trees = nullptr;
    if (nodes == nullptr) {
      cerr << "Memory allocation failure." << endl;
      exit(-1);
    }
     for (int i = 0; i < numNodes; i++) {
       nodes[i].value = i+1;
       marked[i] = false;
       sources[i] = false;
    //   visits[i] = 0;
    //   firstPredecessor[i] = -1;
    //   incycle[i] = false;
     }

    // srand(0);
    // int n1, n2;
    // int countEdges = 0;
    
    int n1, n2;
    cin >> n1 >> n2;
    n1 --;
    n2 --;

    while (n1 != -2 && n2 != -2) {
    //   do {
	// n1 = rand() % numNodes;
	// n2 = rand() % numNodes;
    //   } while (n1 == n2);
        if(n1 < 0 || n1 >= numNodes || n2 < 0 || n2 >= numNodes){
            cin >> n1 >> n2;
            n1--; n2--;
            continue;
        }

      // Create an undirected edge from n1 to n2 and store in appropriate
      // adjacency list(s).  If an undirected edge from n1 to n2 (or
      // equivalently from n2 to n1) already exists, you shouldn't add
      // an edge.  Only if such an undirected edge didn't exist earlier,
      // should you add the edge and increment countEdges; otherwise,
      // do not increment countEdges;
      // Every time an edge is created, we also add that information to
      // graphFile

      LinkedList* currNode = nodes[n1].adjacentList;
      // if(currNode == nullptr){
      //   nodes[n1].adjacentList = new LinkedList(&nodes[n2]);
      //   nodes[n1].adjListLastEle = nodes[n1].adjacentList;
      //   //  update in list of n2 as well;
      //   if(nodes[n2].adjacentList == NULL){
      //     nodes[n2].adjacentList = new LinkedList(&nodes[n1]);
      //     nodes[n2].adjListLastEle = nodes[n1].adjacentList;
      //   }
      //   else{
      //     nodes[n2].adjListLastEle->next = new LinkedList(&nodes[n1]);
      //     nodes[n2].adjListLastEle = nodes[n2].adjListLastEle->next;
      //   }
      // }
      bool alreadyPresent = false;
      while(currNode != nullptr){
        if(currNode->store->value == n2+1){
          alreadyPresent = true;
          break;
        }
        currNode = currNode->next;
      }
      if(alreadyPresent)
        continue;

      if(nodes[n1].adjacentList == nullptr){
        nodes[n1].adjacentList = new LinkedList(&nodes[n2]);
        nodes[n1].adjListLastEle = nodes[n1].adjacentList;
      }  
      else{
        nodes[n1].adjListLastEle->next = new LinkedList(&nodes[n2]);
        nodes[n1].adjListLastEle = nodes[n1].adjListLastEle->next;
      }
      if(nodes[n2].FromAdjList == nullptr){
        nodes[n2].FromAdjList = new LinkedList(&nodes[n1]);
        nodes[n2].FromAdjListLastEle = nodes[n2].FromAdjList;
      }  
      else{
        nodes[n2].FromAdjListLastEle->next = new LinkedList(&nodes[n1]);
        nodes[n2].FromAdjListLastEle = nodes[n2].FromAdjListLastEle->next;
      }









    //   graphFile << n1+1 << " " << n2+1 << endl;
      cin >> n1 >> n2;
      n1--;
      n2--;
    }


    cin >> n1 >> n2;
    n1--; n2--;
    while (n1 != -2 && n2 != -1)
    {
      if(n1 < 0 || n1 >= numNodes || n2 < 0 || n2 >= numNodes){
            cin >> n1 >> n2;
            n1--; n2--;
            continue;
        }

      if(nodes[n1].SimilarTo == nullptr){
        nodes[n1].SimilarTo = new LinkedList(&nodes[n2]);
        // nodes[n1].adjListLastEle = nodes[n1].adjacentList;
      }  
      else{
        LinkedList *a = nodes[n1].SimilarTo;
        while(a->next != nullptr)
          a = a->next;
        a->next = new LinkedList(&nodes[n2]);
        // nodes[n1].adjListLastEle = nodes[n1].adjListLastEle->next;
      }
      if(nodes[n2].SimilarFrom == nullptr){
        nodes[n2].SimilarFrom = new LinkedList(&nodes[n1]);
        // nodes[n2].FromAdjListLastEle = nodes[n2].FromAdjList;
      }  
      else{
        LinkedList *a = nodes[n2].SimilarFrom;
        while(a->next != NULL)
          a = a->next;
        a->next = new LinkedList(&nodes[n1]);
        // nodes[n2].FromAdjListLastEle = nodes[n2].FromAdjListLastEle->next;
      }


      cin >> n1 >> n2;
      n1--; n2--;
    }
    


        // for(int j=0; j<numNodes; j++){
        //   LinkedList* a = nodes[j].adjacentList;
        //   cout << j+1 << ": ";
        //   while(a!=nullptr){
        //     cout << a->store->value << "  ";
        //     a = a->next;
        //   }
        //   cout << endl;
        //   LinkedList* b = nodes[j].FromAdjList;
        //   cout << j+1 << ": ";
        //   while(b!=nullptr){
        //     cout << b->store->value << "  ";
        //     b = b->next;
        //   }
        //   cout << endl;
        // }
    // Add appropriate code as necessary for your implementation
  }
      
  ~Graph() {
    // if (graphFile.is_open()) {
    //   graphFile.close();
    // }
    delete[] nodes;
    // Add appropriate code as necessary for your implementation
  }

  // Add appropriate method declarations as necessary for your implementation


//   void ThisDFS(int index, int from);
//   bool updateInCycle(int index, int till);
//   void seeCommonANcestorAndUpdate(int ind,int adjInd);
//   int UnvisitedNode();
//   void modifiedDFS();
//   void printResults();
void findSources();
void markNodes(int start);
void updateSimilars();
void huntSimilars(int start);
void updateIffoundSimilar(int index);
void updateAsimilarpair(int src, int dest);
void CheckandUpdateSimilarity(Node* x, Node* y);
void print();
};

#endif
