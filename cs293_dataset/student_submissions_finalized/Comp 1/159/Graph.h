#ifndef GRAPH_BST_H
#define GRAPH_BST_H

#ifndef STD_HEADERS_H
#include "std_headers.h"
#include <bits/stdc++.h>
using namespace std;
#endif
class Node1{
  public:

  int value;
  Node1 *right;
  Node1 *left;
  Node1 *parent;
  Node1(int value){
    this->value=value;
    right=nullptr;
    parent=nullptr;
    left=nullptr;
  }

};
class BST
{
  Node1 *root;
  public:
    BST(){
      root = nullptr;
    }
    BST(Node1 *x){
      root = x;
    }
    bool insert(int value) { 
    // Adding the first node
    if(root == NULL){
        root = new Node1(value);
        return true;
     }
    // Checking if similar node already exists
    Node1 *curr = root;
    while(true){
        

        // Moving to the right, if value is greater
        if(value >= curr->value){
            if(curr->right!=NULL){
                curr = curr->right;
            }else{
                curr->right = new Node1(value);
                break;
                
            }
        }else{
            // moving to left if its smaller
            if(curr->left!=NULL){
                curr = curr->left;
            }else{
                curr->left = new Node1(value);
                break;
                
            }
        }
    }
  //  this->printBST("",false);
    return true;

}
void printBST(const string& prefix, bool isLeft=false)
{
    if( root != nullptr )
    {
        cout << prefix;

        cout << (isLeft ? "|--" : "|__" );

        // print the value of the node
        cout << '('<< root->value<<')' << endl;
        Node1 *curr = root;
        root = root->left;
        // enter the next tree level - left and right branch
        printBST( prefix + (isLeft ? "│   " : "    "), true);
        root = curr->right;
        printBST( prefix + (isLeft ? "│   " : "    "), false);
        root = curr;
    }
}

// Return True, if the ticket with given attributes is found, false otherwise


};

class adjlist{
   public: 
     int value;
     adjlist* next;
     adjlist(int value){
      this->value=value;
      next=nullptr;
     }
};
adjlist *return_tail(adjlist* x){
  adjlist *r=x;
  while(r->next!=nullptr){
      r=r->next;
  }
  return r;
};

bool present(adjlist* r,int x){
  adjlist* r1=r;
  while(r1!=nullptr){
    if(r1->value==x){
      return true;
    }
    r1=r1->next;
  }
  return false;
}
int length(adjlist* x){
  adjlist* r=x;
  int s=0;
  while(r!=nullptr){
     r=r->next;
     s++;
  }
  return s;
}
void print(adjlist *x , int y){
  adjlist *r=x;
 while(r!=nullptr){
  //cout<<"node "<<y<<" its adj "<<r->value+1<<endl;
  r=r->next;
 }
 return;
}

void remove(adjlist** x , int value){
  adjlist *r= *x;
  adjlist *prev=nullptr;
  if(r!=nullptr && r->value==value){
    *x=r->next;
    delete r;
    return;
  }
  else{
    while(r!=nullptr && r->value!=value){
      prev=r;
      r=r->next;
    }
    if(r==nullptr){return;}
    prev->next=r->next;
    delete r;
    return;
  }

}
bool completed(int *arr,int s){
  for(int i=0;i<s;i++){
    if(arr[i]==0){
      return false;
    }
  }
  return true;
}

class Node
{
public:
  int value;
  adjlist* adj;
  Node(){
    value=0;
    adj=nullptr;
  }
  Node(int value){
    this->value=value;
  }

  // insert other fields and methods as appropriate
};

class Graph
{
  int numNodes;
  int numEdges;
  int conncomp=1;
  int *cycle;
  fstream graphFile;
  int *visited;
  Node *nodes;

  // Add appropriate fields as necessary for your implementation

public:
  Graph(int nNodes, int nEdges, string gFileName)
  {
    numNodes = nNodes;
    numEdges = nEdges;
    graphFile.open(gFileName, ios::out);
    if (!graphFile.is_open())
    {
      cerr << "Couldn't open graph file " << gFileName << ". Aborting ..." << endl;
      exit(-1);
    }

    graphFile << numNodes << endl;
    graphFile << numEdges << endl;

    nodes = new Node[numNodes];
    visited = new int[numNodes];
    cycle = new int[numNodes];
    if (nodes == nullptr)
    {
      cerr << "Memory allocation failure." << endl;
      exit(-1);
    }

    for (int i = 0; i < numNodes; i++)
    {
      nodes[i].value = i + 1;
      visited[i]= 0;
      cycle[i]=0;
    }

    srand(time(0));
    int n1, n2;
    int countEdges = 0;

    while (countEdges < numEdges)
    {
      do
      {
        n1 = rand() % numNodes;
        n2 = rand() % numNodes;
      } while (n1 == n2);
      //cout<<n1+1<<" "<<n2+1<<endl;
      if(!present(nodes[n1].adj,n2) || !present(nodes[n2].adj,n1)){
      if(nodes[n1].adj==nullptr && nodes[n2].adj==nullptr){
        //cout<<1<<endl;
                  nodes[n1].adj=new adjlist(n2);
                  nodes[n2].adj=new adjlist(n1);
      }
      else if(nodes[n1].adj!=nullptr && nodes[n2].adj==nullptr){
        //cout<<2<<endl;
                  adjlist* r=return_tail(nodes[n1].adj);
                  r->next=new adjlist(n2);
                  nodes[n2].adj=new adjlist(n1);
      }
      else if(nodes[n2].adj!=nullptr && nodes[n1].adj==nullptr){
        //cout<<3<<endl;
                  adjlist* r=return_tail(nodes[n2].adj);
                  r->next=new adjlist(n1);
                  nodes[n1].adj=new adjlist(n2);
      }
      else if(nodes[n2].adj!=nullptr && nodes[n1].adj!=nullptr){
        //cout<<4<<endl;
                  adjlist* r=return_tail(nodes[n2].adj);
                  r->next=new adjlist(n1);
                  adjlist* r1=return_tail(nodes[n1].adj);
                  r1->next=new adjlist(n2);
      }
      else;


      // Create an undirected edge from n1 to n2 and store in appropriate
      // adjacency list(s).  If an undirected edge from n1 to n2 (or
      // equivalently from n2 to n1) already exists, you shouldn't add
      // an edge.  Only if such an undirected edge didn't exist earlier,
      // should you add the edge and increment countEdges; otherwise,
      // do not increment countEdges;
      // Every time an edge is created, we also add that information to
      // graphFile
      graphFile << n1 + 1 << " " << n2 + 1 << endl;
      countEdges++;
      }

    }
    for(int i=0;i<numNodes;i++){
       print(nodes[i].adj,nodes[i].value);
    }
    
    // Add appropriate code as necessary for your implementation
  }

  ~Graph()
  {
    if (graphFile.is_open())
    {
      graphFile.close();
    }
    delete[] nodes;
    // Add appropriate code as necessary for your implementation
  }
  // Add appropriate method declarations as necessary for your implementation
  void DFS(int n , BST *x, adjlist *p){
    //cout<<n+1<<"source"<<endl;
    visited[n]++;
    x->insert(n+1);
    adjlist *r1=p;
    adjlist *r11=return_tail(r1);
    r11->next=new adjlist(n+1);
    adjlist *r=nodes[n].adj;
    while(r!=nullptr){   
      if(visited[r->value] <2){
        //cout<<r->value+1<<"adj"<<endl;
           //visited[r->value]++;
           remove(&nodes[r->value].adj,n);
           DFS(r->value,x,p);}
           r=r->next;  
         }
    if(r==nullptr){
      return;
    }
  }
  void modifiedDFS();
  void printResults();
};

#endif