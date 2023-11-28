#include <iostream>
#include <fstream>
#include <string> 
#include <sstream>
using namespace std;


class Node{
  public:
  int value;
   Node *prev;	// Left Child of this Node (NULL, if None)
    Node *next;	// Right Child of this Node (NULL, if None)
  Node() : value(-1), prev(nullptr), next(nullptr) {}
  Node(int value) : value(value), prev(nullptr), next(nullptr) {}
  Node(int value, Node *prevNode, Node *nextNode ): value(value), prev(prevNode), next(nextNode){}
};


class pairs{
  public:  
    int p1;
    int p2;
   pairs* next;
   pairs* prev;
   pairs(int p1,int p2) : p1(p1),p2(p2),prev(nullptr), next(nullptr) {}
};


class f{
public:
bool* source;
Node *node;
int numNodes;
pairs *Similarity= new pairs(0,0);
bool similar(int n1,int n2);
void readfile(string filename);
};

