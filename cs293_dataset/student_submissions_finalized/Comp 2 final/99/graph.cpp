#include "graph.h"

DirectedGraph::DirectedGraph()
{
   numNodes = 0;
   numEdges = 0;
   numSimilar = 0;
   currGroupLabel = 0;
         
   int i = 0;
   bool firstPart = true;
   bool takingInput = true;
   while (takingInput)
   {
      // first line of input
      if (i == 0) 
      {
         cin >> numNodes;
         nodeType = new int[numNodes];
         nodes = new Node[numNodes];
         similar = new OrderedPair[numNodes * numNodes];
         groupLabel = new int[numNodes];
         // initialising the nodes and nodetypes
         for (int i = 0; i < numNodes; i++)
         {
            nodes[i] = Node(i + 1, numNodes - 1, numNodes - 1);
            nodeType[i] = 0;
            groupLabel[i] = -1;
         }
         i++;
         continue;
      }
      // getting the two nodes
      int num1, num2;
      cin >> num1 >> num2;
      if (num2 == -1)
      {
         if (firstPart)
         {
            firstPart = false;
            continue;
         }
         else
         {
            takingInput = false;
            break;
         }
      }
      if (firstPart) // adding the directed edge
      {
         if (nodeType[num1 - 1] == 0) nodeType[num1 - 1] = 1;
         else if (nodeType[num1 - 1] == 2) nodeType[num1 - 1] = 3;

         if (nodeType[num2 - 1] == 0) nodeType[num2 - 1] = 2;
         else if (nodeType[num2 - 1] == 1) nodeType[num2 - 1] = 3;

         bool alreadyPresent = 0;
         for (int k = 0; k < nodes[num1 - 1].numOutgoing; k++)
         {
            if (nodes[num1 - 1].outgoingTo[k] == num2) alreadyPresent = true;
         }
         if (!alreadyPresent)
         {
            // adding the edge to the adjacency lists
            numEdges++;
            nodes[num1 - 1].outgoingTo[nodes[num1 - 1].numOutgoing] = num2;
            nodes[num1 - 1].numOutgoing++;
            nodes[num2 - 1].incomingFrom[nodes[num2 - 1].numIncoming] = num1;
            nodes[num2 - 1].numIncoming++;
         }
      }
      else // getting the pair of nodes similar according to condition 1
      {
         bool alreadyPresent = false;
         for (int k = 0; k < numSimilar; k++)
         {
            if (similar[k].isSame(OrderedPair(num1, num2))) alreadyPresent = true;
         }
         if (!alreadyPresent)
         {
            if (nodeType[num1 - 1] <= 1 && nodeType[num2 - 1] <= 1)
            {
               similar[numSimilar] = OrderedPair(num1, num2);
               numSimilar++;
            }
         }
      }
   } // finished taking input
   for (int i = 0; i < numNodes; i++) // getting the pair of nodes similar according to condition 3
   {
      if (nodes[i].numIncoming == 1)
      {
         similar[numSimilar] = OrderedPair(i + 1, nodes[i].incomingFrom[0]);
         numSimilar++;
      }
   }
   f.open("outgraph.txt", ios::out);
}

DirectedGraph::~DirectedGraph()
{
   delete[] nodes;
   delete[] nodeType;
   delete[] similar;
   delete[] groupLabel;
   f.close();
}

bool DirectedGraph::isSimilar(Node one, Node two)
{
   for (int i = 0; i < numSimilar; i++)
   {
      if (similar[i].isSame(OrderedPair(one.value, two.value))) return true;
   }
   // checking if two nodes are similar by condition 2
   // m1 ~ m2
   if (one.numIncoming == 0 || two.numIncoming == 0) return false;
   bool m1_to_m2 = true;
   for (int i = 0; i < one.numIncoming; i++)
   {
      bool foundSimilar = false;
      for (int j = 0; j < two.numIncoming; j++)
      {
         if (isSimilar(nodes[one.incomingFrom[i] - 1], nodes[two.incomingFrom[j] - 1]))
         {
            foundSimilar = true;
            break;
         }
      }
      m1_to_m2 = (m1_to_m2 && foundSimilar);
      if (!m1_to_m2) return false;
   }
   // m2 ~ m1
   bool m2_to_m1 = true;
   for (int i = 0; i < two.numIncoming; i++)
   {
      bool foundSimilar = false;
      for (int j = 0; j < one.numIncoming; j++)
      {
         if (isSimilar(nodes[two.incomingFrom[i] - 1], nodes[one.incomingFrom[j] - 1]))
         {
            foundSimilar = true;
            break;
         }
      }
      m2_to_m1 = (m2_to_m1 && foundSimilar);
      if (!m2_to_m1) return false;
   }
   if (m1_to_m2 && m2_to_m1)
   {
      similar[numSimilar] = OrderedPair(one.value, two.value);
      numSimilar++;
      return true;
   }
   return false;
}

void DirectedGraph::getSimilarNodes()
{
   for (int i = 0; i < numNodes; i++)
   {
      for (int j = 0; j < numNodes; j++)
      {
         isSimilar(nodes[i], nodes[j]);
      }
   }
}

void DirectedGraph::printSourceNodes()
{
   f << "Source nodes: ";
   for (int i = 0; i < numNodes; i++)
   {
      if (nodeType[i] == 0 || nodeType[i] == 1) f << i + 1 << ' ';
   }
   f << endl << endl;
}

void DirectedGraph::printSimilar()
{
   f << "Similar node pairs:";
   for (int i = 0; i < numSimilar; i++)
   {
      f << " (" << similar[i].a << ", " << similar[i].b << ")";
   }
   f << endl << endl;
}

void DirectedGraph::printAllNodes()
{
   for (int i = 0; i < numNodes; i++)
   {
      cout << "Node Value = " << nodes[i].value << endl;
      cout << "Edges going to ";
      for (int j = 0; j < nodes[i].numOutgoing; j++) cout << nodes[i].outgoingTo[j] << ' ';
      cout << endl << "Edges coming from ";
      for (int j = 0; j < nodes[i].numIncoming; j++) cout << nodes[i].incomingFrom[j] << ' ';
      cout << '\n' << '\n';
   }
}

int DirectedGraph::assignGroup(Node currNode, int groupNumber)
{
   if (groupLabel[currNode.value - 1] != -1) return groupLabel[currNode.value - 1];
   groupLabel[currNode.value - 1] = groupNumber;
   for (int i = 0; i < numSimilar; i++)
   {
      int p = -1, q = -1;
      if (similar[i].a == currNode.value && similar[i].b == currNode.value) continue;
      if (similar[i].a == currNode.value) p = assignGroup(nodes[similar[i].b - 1], groupNumber);
      if (similar[i].b == currNode.value) q = assignGroup(nodes[similar[i].a - 1], groupNumber);
   }
   return groupNumber;
}

void DirectedGraph::collapseSimilarNodes()
{
   for (int i = 0; i < numNodes; i++)
   {
      if (groupLabel[i] == -1)
      {
         assignGroup(nodes[i], currGroupLabel);
         currGroupLabel++;
      }
   }
}

void DirectedGraph::getCollapsedGraph()
{
   Node collapsedNodes[currGroupLabel];
   for (int i = 0; i < currGroupLabel; i++)
   {
      collapsedNodes[i] = Node(0, numNodes - 1, 1);
   }
   for (int i = numNodes - 1; i >= 0; i--)
   {
      if (collapsedNodes[groupLabel[i]].value == 0) collapsedNodes[groupLabel[i]].value = i + 1;
   }
   for (int i = numNodes - 1; i >= 0; i--)
   {
      for (int j = 0; j < nodes[i].numOutgoing; j++)
      {
         if (groupLabel[i] == groupLabel[nodes[i].outgoingTo[j] - 1]) continue;
         else
         {
            bool isPresent = false;
            for (int k = 0; k < collapsedNodes[groupLabel[i]].numOutgoing; k++)
            {
               if (collapsedNodes[groupLabel[i]].outgoingTo[k] == collapsedNodes[groupLabel[nodes[i].outgoingTo[j] - 1]].value)
               {
                  isPresent = true;
                  break;
               }
            }
            if (isPresent) continue;
            collapsedNodes[groupLabel[i]].outgoingTo[collapsedNodes[groupLabel[i]].numOutgoing] 
                     = collapsedNodes[groupLabel[nodes[i].outgoingTo[j] - 1]].value;
            collapsedNodes[groupLabel[i]].numOutgoing++;
         }
      }
   }
   f << "Collapsed graph:\n\n";
   f << currGroupLabel << ": ";
   for (int i = 0; i < currGroupLabel; i++)
   {
      f << collapsedNodes[i].value << ' ';
   }
   f << endl;
   for (int i = 0; i < currGroupLabel; i++)
   {
      for (int j = 0; j < collapsedNodes[i].numOutgoing; j++)
      {
         f << collapsedNodes[i].value << ' ' << collapsedNodes[i].outgoingTo[j] << endl;
      }
   }
}