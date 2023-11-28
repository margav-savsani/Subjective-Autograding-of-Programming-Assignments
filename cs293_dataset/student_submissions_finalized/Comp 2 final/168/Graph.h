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
};

class Node {
 public:
  int value;
  listOfObjects<int>* adjacencyList = nullptr;
  listOfObjects<int>* prevList = nullptr;
  bool isSource = true;   //if a node is a source node
  bool classed = false;   //if a node has been added to one of the equivalence classes
  int max;    //the max value of the class
};

class Graph {
  int numNodes;
  int numEdges;
  int numComponents=0;
  fstream graphFile;
  listOfObjects<int>* path; 
  listOfObjects<listOfObjects<int>*>*classes = nullptr;   //the list of all classes

  Node *nodes;

  // Add appropriate fields as necessary for your implementation

 public:
  Graph(int nNodes, string gFileName) {
    path=nullptr;
    numNodes = nNodes;
    graphFile.open(gFileName, ios::out);
    if (!graphFile.is_open()) {
      cerr << "Couldn't open graph file " << gFileName << ". Aborting ..." << endl;
      exit(-1);
    }

    graphFile << numNodes << endl;
    graphFile << numEdges << endl;

    nodes = new Node[numNodes];
    if (nodes == nullptr) {
      cerr << "Memory allocation failure." << endl;
      exit(-1);
    }

    for (int i = 0; i < numNodes; i++) {
      nodes[i].value = i+1;
    }

    int n1, n2;

    int nEdges=0;
    while(true){
      cin>>n1>>n2;
      if(n1==-1){
        break;
      }
      else{
        nEdges++;
      }
      n1=n1-1;
      n2=n2-1;
      nodes[n2].isSource=false;
      //adding nodes to the adjacency lists of n1
      if(nodes[n1].adjacencyList){
        auto temp=nodes[n1].adjacencyList;
        while(temp->next){
          temp=temp->next;
        }
        temp->next=new listOfObjects<int>(n2);
        temp->next->prev=temp;
      }
      else{
        nodes[n1].adjacencyList=new listOfObjects<int>(n2);
      }

      //adding nodes to the prevList of n2
      if(nodes[n2].prevList){
        auto tempprev=nodes[n2].prevList;
        while(tempprev->next){
          tempprev=tempprev->next;
        }
        tempprev->next=new listOfObjects<int>(n1);
        tempprev->next->prev=tempprev;
      }
      else{
        nodes[n2].prevList=new listOfObjects<int>(n1);
      }

      // do {
      //   n1 = rand() % numNodes;
      //   n2 = rand() % numNodes;
      // } while (n1 == n2);

      //   if(nodes[n1].adjacencyList){
      //     listOfObjects<int>* temp= nodes[n1].adjacencyList;
      //     bool found=false;
      //     while(true){
      //       if(temp->object==n2){
      //         found=true;
      //         break;
      //       }
      //       else{
      //         if(temp->next){
      //           temp=temp->next;
      //         }
      //         else{
      //           break;
      //         }
      //       }
      //     }
      //     if(found){
      //       continue;
      //     }
      //     else{
      //       temp->next=new listOfObjects<int>(n2);
      //       temp->next->prev=temp;
      //     }
      //   }
      //   else{
      //     nodes[n1].adjacencyList=new listOfObjects<int>(n2);
      //   }

      //   if(nodes[n2].adjacencyList){
      //     listOfObjects<int>* temp=nodes[n2].adjacencyList;
      //     while(true){
      //       if(temp->next){
      //         temp=temp->next;
      //       }
      //       else{
      //         break;
      //       }
      //     }
      //     temp->next=new listOfObjects<int>(n1);
      //     temp->next->prev=temp;
      //   }
      //   else{
      //     nodes[n2].adjacencyList=new listOfObjects<int>(n1);
      //   }

      //   graphFile << n1+1 << " " << n2+1 << endl;
      //   countEdges++;
      // }
    }

    numEdges=nEdges;
    // a 2d array which keeps track of the similarity relations
    bool** similar = new bool*[numNodes];
    for(int i=0;i<numNodes;i++){
      similar[i]= new bool[numNodes];
    }
    for (int x=0;x<numNodes;x++){
      for(int y=0;y<numNodes;y++){
        similar[x][y]=0;
      }
    }

    // a copy of similar to check if our process is over
    bool ** similar2;
    while(true){
      similar2=similar;
      similar=similarity(similar);
      bool flag = true;
      //we check to see if similar and similar2 are the same, then we stop
      for(int i=0;i<numNodes;i++){
        for(int j=0;j<numNodes;j++){
          if(similar[i][j]!=similar2[i][j]){
            flag = false;
            break;
          }
        }
        if(!flag){
          break;
        }
      }
      if(flag){
        break;
      }
    }
    // cout<<similar[3][0]<<"h"<<endl;

    //PRINTING RESULTS
    cout<<"Source Nodes: ";
    for(int counter=0;counter<numNodes;counter++){
      if(nodes[counter].isSource){
        cout<<counter+1<<" ";
      }
    }
    cout<<endl;
    cout<<endl;
    cout<<"Similar node pairs: ";
    for(int x=0;x<numNodes;x++){
      for(int y=0;y<numNodes;y++){
        if(similar[x][y]==1){
          cout<<"("<<x+1<<","<<y+1<<")"<<" ";
        }
      }
    }
    cout<<endl;
    cout<<endl;
    cout<<"Collapsed Graph:"<<endl;
    cout<<endl;

    //collapsing the nodes:

    //making similar symmetric
    for(int x=0;x<numNodes;x++){
      for(int y=0;y<numNodes;y++){
        if(similar[x][y]){
          similar[y][x]=1;
        }
      }
    }

    // for(int x=0;x<numNodes;x++){
    //   for(int y=0;y<numNodes;y++){
    //     cout<<similar[x][y]<<" ";
    //   }
    //   cout<<endl;
    // }


    //calling the collapse function on each node until all nodes are collapsed
    auto a = new listOfObjects<int>(-1);
    classes = new listOfObjects<listOfObjects<int>*>(a);
    a = nullptr;
    for(int i=0;i<numNodes;i++){
      if(nodes[i].classed){
        continue;
      }
      classes->next = new listOfObjects<listOfObjects<int>*>(a);
      classes->next->prev=classes;
      collapse(similar,i);
      classes=classes->next;
    }

    while(classes->prev){
      classes=classes->prev;
    }
    classes=classes->next;
    classes->prev=nullptr;

    listOfObjects<int>* maxes;
    int count = 0;
    auto temp1 = classes;
    while(temp1){
      auto temp = temp1->object;
      int max=0;
      while(temp){
        // cout<<temp->object+1<<" ";
        if(temp->object>max){
          max=temp->object;
        }
        temp=temp->next;
      }
      // cout<<endl;
      if(maxes){
        maxes->next = new listOfObjects<int>(max); //computing the max value for each class
        count++;
        maxes->next->prev=maxes;
        maxes=maxes->next;
      }
      else{
        maxes = new listOfObjects<int>(max);
      }
      temp1=temp1->next;
    }

    // bool** adj = new bool*[count];
    // for(int i=0;i<count;i++){
    //   adj[i] = new bool[count];
    // }

    // for(int x=0;x<count;x++){
    //   for(int y=0;y<count;y++){
    //     adj[x][y]=0;
    //   }
    // }

    while(maxes->prev){
      maxes=maxes->prev;
    }
    maxes=maxes->next;
    cout<<count<<": ";
 

    while(maxes->next){
      // auto temp = classes->object;
      // while(temp){
      //   cout<<temp->object<<" ";
      // }
      // cout<<"done"<<endl;
      cout<<maxes->object+1<<" ";   //printing out the collapsed nodes

      // classes=classes->next;
      maxes=maxes->next;
    }
    cout<<maxes->object+1<<" ";
    cout<<endl;

    while(maxes->prev){
      maxes=maxes->prev;
    }

    printEdges(classes,maxes->next,count);    //printing the edges of the collapsed graph
  }

  ~Graph() {
    if (graphFile.is_open()) {
      graphFile.close();
    }
    delete[] nodes;
    // Add appropriate code as necessary for your implementation
  }

  // Add appropriate method declarations as necessary for your implementation
  bool ** similarity(bool** similar);
  void collapse(bool** similar,int n);
  void printEdges(listOfObjects<listOfObjects<int>*>*eqclasses,listOfObjects<int>* maxes,int count);

};

#endif
