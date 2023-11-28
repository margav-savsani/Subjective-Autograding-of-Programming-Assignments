#ifndef GRAPH_BST_H
#define GRAPH_BST_H

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

template <typename T> class ll { 
    //linked list
    public : 
      T obj ; 
      ll* next ; 
      ll() ;
      ll(T obj) { this->obj = obj ; this->next = nullptr ; }
      bool contains(T obj) { 
          if (obj == this->obj) return true ; 
          if( next == nullptr) return false ; 
          return next->contains(obj) ;
      }
      bool insert(T obj) { 
          if ( next == nullptr ) next = new ll<T>(obj);
          else next->insert(obj);
      }  
};


class BST {
  public :
    int value ; 
    BST* left ;     
    BST* right ;
    BST(int v) {left = nullptr ; right = nullptr ; value = v ; }
    void insert(int v) { 
         // recursive bst insert
         if ( v < value ) { 
            if (left == nullptr) left = new BST(v) ; 
            else left->insert(v); 
         }
         else { 
            if (right == nullptr) right = new BST(v) ; 
            else right->insert(v); 
         }
    }     
    void printBST(const string& prefix, bool isLeft=false)
    {
            cout << prefix;
            cout << (isLeft ? "|--" : "|__" );
            cout << value << endl;
            if (left != nullptr ) left->printBST( prefix + (isLeft ? "│   " : "    "), true);
            if (right != nullptr ) right->printBST( prefix + (isLeft ? "│   " : "    "), false);
    }
};

class Node {
 public:
  int value;
  int visited ;
  int p1 , p2 ;
  int arrtime ;
  ll<int>* adjacency ; 
  Node() { value = 0 ;   adjacency = nullptr ; visited = 0 ; p1 = -1 ; p2 = -1 ;  }
  void insert(int n) { 
     //recursive insert 
     if( adjacency == nullptr) adjacency = new ll<int>(n) ; //base case
     else { 
        adjacency->insert(n);
     } 
  }
};

class Graph {
  int numNodes;
  int numEdges;
  fstream graphFile;
  Node *nodes;
  bool* cycle ; 
  public:
   Graph(int nNodes, int nEdges, string gFileName) {
    numNodes = nNodes;
    numEdges = nEdges;
    
    graphFile.open(gFileName, ios::out);
    if (!graphFile.is_open()) {
      cerr << "Couldn't open graph file " << gFileName << ". Aborting ..." << endl;
      exit(-1);
    }

    graphFile << numNodes << endl;
    graphFile << numEdges << endl;

    nodes = new Node[numNodes];
    cycle = new bool[numNodes];
    if (nodes == nullptr) {
      cerr << "Memory allocation failure." << endl;
      exit(-1);
    }

    for (int i = 0; i < numNodes; i++) {
      nodes[i].value = i+1;
      nodes[i].arrtime = numNodes  + 1 ;
    }
    //int k = 1667053083 ; 
    int k = time(0) ;
    srand(k);
    int n1, n2;
    int countEdges = 0;
    
    while (countEdges < numEdges) {
      do {
	       n1 = rand() % numNodes;
	       n2 = rand() % numNodes;
      } while (n1 == n2);
      if (nodes[n1].adjacency == nullptr || (!nodes[n1].adjacency->contains(n2))) { 
             //these functions are implemented in the data structure
             nodes[n1].insert(n2); 
             nodes[n2].insert(n1);
             graphFile << n1+1 << " " << n2+1 << endl;
             countEdges++;
      }
    }
  }
      
  ~Graph() {
    if (graphFile.is_open()) {
      graphFile.close();
    }
    delete[] nodes;
  }

  int DFS(  int n  , int arrtime , BST* root ) {
       //the recurisve dfs function  
       int dbe = arrtime +2 ;
       arrtime += 1 ; 
       //update the dbe 
       nodes[n].arrtime = min(arrtime,nodes[n].arrtime);
       nodes[n].visited++ ; 
       ll<int>* adj = nodes[n].adjacency ; 
       while ( adj != nullptr )  { 
           //check for one direction of the edge 
           if ( adj->obj!=nodes[n].p1 && adj->obj!=nodes[n].p2) { 
             if( nodes[adj->obj].visited != 2 ) {
               //insert into bst 
               root->insert(nodes[adj->obj].value);
               //update the parent of the current node 
               if ( nodes[adj->obj].p1 != -1 ) { 
                    if (nodes[adj->obj].p1 != n) nodes[adj->obj].p2 = n ;
               } 
               else nodes[adj->obj].p1 = n ;
               //call dfs to the adjacent and it returns the updated dbe 
               int new_dbe = DFS(adj->obj,arrtime,root);
               dbe = min(new_dbe,dbe);
             } else { 
                //call dfs recursively
                dbe = min(dbe,nodes[adj->obj].arrtime);
             }
           }
           adj = adj->next ;  
      }
      //check if its in a cycle 
      if ( dbe <= nodes[n].arrtime ) { cycle[n] = 1 ; }
      return dbe ;
  }

  void modifiedDFS();
  void printResults();
};

#endif
