#ifndef GRAPH_BST_H
#define GRAPH_BST_H

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

class BSTNode
{
   public:
      BSTNode * left;
      BSTNode * right;
      BSTNode * parent;
      int val;
      BSTNode()
      {
         left = right = parent = nullptr;
         val = 0;
      }
      BSTNode(int v)
      {
         left = right = parent = nullptr;
         val = v;
      }
      BSTNode(BSTNode * l, BSTNode * r, BSTNode * p, int v)
      {
         left = l;
         right = r;
         parent = p;
         val = v;
      }  
};

class BST 
{
   public:
      BSTNode * root;
      BST()
      {
         root = nullptr;
      }
      BST(BSTNode * rt)
      {
         root = new BSTNode(rt->left, rt->right, nullptr, rt->val);
      }
      bool insert(int val);
      void printBST(const string& prefix, bool isLeft);
};

template <typename T> class linkedList
{
   public:
      T object;
      linkedList * next;
      linkedList * prev;
      linkedList(T init)
      {
         object = init;
         next = prev = nullptr;
      }
};

class Node
{
   public:
      int value; // the value of the node
      int * adjacents; // stores the values of the nodes it is adjacent to
      int numAdj; // keeps count of the number of adjacent nodes
      
      Node()
      {
         value = numAdj = 0;
         adjacents = nullptr;
      }

      Node(int v, int n)
      {
         value = v;
         numAdj = 0;
         adjacents = new int[n];
      }
};

class Graph 
{
   int numNodes;
   int numEdges;
   fstream graphFile;
   Node *nodes;
   int N = 0;
   int * c;
   int * prnt;
   linkedList<BST *>* TREES = nullptr;
   linkedList<int> * forCycle = new linkedList<int>(-1);
   int visitedOnce;
   int visitedTwice; 

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
         c = new int[numNodes];
         prnt = new int[numNodes];
         if (nodes == nullptr)
         {
            cerr << "Memory allocation failure." << endl;
            exit(-1);
         }
         for (int i = 0; i < numNodes; i++)
         {
            nodes[i].value = i + 1;
            c[i] = 0;
         }
         TREES = nullptr;
         visitedOnce = visitedTwice = 0;
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

            bool alreadyPresent = false;
            if (nodes[n1].adjacents == nullptr) nodes[n1].adjacents = new int[numNodes];
            if (nodes[n2].adjacents == nullptr) nodes[n2].adjacents = new int[numNodes];
            for (int i = 0; i < nodes[n1].numAdj; i++) 
            {
               if (nodes[n1].adjacents[i] == nodes[n2].value) alreadyPresent = true;
            }
            if (alreadyPresent) continue;
            nodes[n1].adjacents[nodes[n1].numAdj] = nodes[n2].value;
            nodes[n2].adjacents[nodes[n2].numAdj] = nodes[n1].value;
            nodes[n1].numAdj++;
            nodes[n2].numAdj++;
            graphFile << n1 + 1 << " " << n2 + 1 << endl;
            countEdges++;
            // cout << "added edge between " << nodes[n1].value << " and " << nodes[n2].value << endl;
         }
      }

      ~Graph()
      {
         if (graphFile.is_open())
         {
            graphFile.close();
         }
         delete[] nodes;
         nodes = nullptr;
         numNodes = 0;
         numEdges = 0;
      }
      void modifiedDFS();
      void printResults();
      void cycle(int indx, int p);
};

#endif
