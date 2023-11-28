#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string>
#include <sstream>
#include <cstring>
#include <cctype>

using namespace std;

class OrderedPair
{
   public:
      int a, b;

      OrderedPair()
      {
         a = b = 0;
      }
      OrderedPair(int a, int b)
      {
         this->a = a;
         this->b = b;
      }

      bool isSame(OrderedPair other)
      {
         if ((other.a == a && other.b == b)) return true;
         else return 0;
      }
};

class Node
{
   public:
      int value; // value of the node
      int * outgoingTo; // values of the nodes to which this node has an edge
      int numOutgoing; // number of adjacent nodes
      int * incomingFrom;
      int numIncoming;
      
      Node()
      {
         value = numOutgoing = numIncoming = 0;
         outgoingTo = incomingFrom = nullptr;
      }
      Node(int v, int no, int ni)
      {
         value = v;
         numOutgoing = 0;
         numIncoming = 0;
         outgoingTo = new int[no];
         incomingFrom = new int[ni];
      }
};

class DirectedGraph
{
   public:
      int numNodes;
      int numEdges;
      Node * nodes;
      int * nodeType; // 0 means no incoming and no outgoing
                      // 1 means no incoming but outgoing
                      // 2 means no outgoing, but incoming
                      // 3 means both
      OrderedPair * similar; // stores the values of OrderedPairs of similar nodes
      int numSimilar;
      fstream f;
      int * groupLabel;
      int currGroupLabel;

      DirectedGraph();
      ~DirectedGraph();
      bool isSimilar(Node one, Node two);
      void getSimilarNodes();
      void printSourceNodes();
      void printAllNodes();
      void printSimilar();
      int assignGroup(Node currNode, int goupNumber);
      void collapseSimilarNodes();
      void getCollapsedGraph();
};
