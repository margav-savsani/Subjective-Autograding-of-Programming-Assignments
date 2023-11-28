#ifndef GRAPH_BST_CPP
#define GRAPH_BST_CPP

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef GRAPH_BST_H
#include "Graph.h"
#endif

bool BST::insert(int val)
{
   BSTNode * newNode = new BSTNode(val);
   if (root == nullptr)
   {
      root = newNode;
      return true;
   }
   BSTNode * where = root;
   bool inserted = false;
   while (!inserted)
   {
      if (newNode->val > where->val)
      {
         if (where->right == nullptr)
         {
            where->right = newNode;
            newNode->parent = where;
            inserted = true;
         }
         else where = where->right;
      }
      else
      {
         if (where->left == nullptr)
         {
            where->left = newNode;
            newNode->parent = where;
            inserted = true;
         }
         else where = where->left;
      }
   }
   return inserted;
}

void BST::printBST(const string & prefix, bool isLeft = false)
{
   if (root != nullptr)
   {
      cout << prefix;
      cout << (isLeft ? "|--" : "|__");
      cout << root->val << endl;
      BSTNode * curr = root;
      root = root->left;
      printBST(prefix + (isLeft ? "|   " : "    "), true);
      root = curr->right;
      printBST(prefix + (isLeft ? "|   " : "    "), false);
      root = curr;
   }
}

void Graph::modifiedDFS()
{
   if (nodes == nullptr) return;
   int visitCount[numNodes];
   int parent[numNodes];
   bool backtracked[numNodes];
   for (int i = 0; i < numNodes; i++) 
   {
      visitCount[i] = 0;
      parent[i] = -1;
      backtracked[i] = false;
      if (nodes[i].numAdj == 1) backtracked[i] = true;
   }
   linkedList<BST *> * trees = nullptr;
   for (int i = 0; i < numNodes; i++)
   {
      linkedList<BST *> * nextTree = new linkedList<BST *>(new BST());
      bool newTreeFormed = false;
      if (visitCount[i] == 0)
      {
         cycle(i, -1);
         newTreeFormed = true;
         linkedList<Node> * stack = new linkedList<Node>(nodes[i]);
         while (stack != nullptr)
         {
            linkedList<Node> * s2 = stack;
            Node s = stack->object;
            stack = stack->next;
            int index = s.value - 1;
            if (parent[index] != -1)
            {
               if (backtracked[parent[index] - 1] && nodes[index].numAdj == 2) backtracked[index] = true;
            }
            if (visitCount[index] == 0 || (visitCount[index] > 0 && !backtracked[index] && visitCount[index] != 2))
            {
               nextTree->object->insert(s.value);
               visitCount[index]++;
            }
            int added = 0;
            for (int j = 0; j < s.numAdj; j++)
            {
               int nextNodeIndex = s.adjacents[j] - 1;
               if (s.adjacents[j] == parent[index]) continue;
               added++;
               if (visitCount[nextNodeIndex] >= 2) continue;
               parent[nextNodeIndex] = s.value;
               linkedList<Node> * newInit = new linkedList<Node>(nodes[nextNodeIndex]);
               newInit->next = stack;
               if (stack != nullptr) stack->prev = newInit;
               stack = newInit;
            }
            if (added == 0) 
            {
               backtracked[index] = true;
               int pval = parent[index];
               bool x = false;
               while (!x)
               {
                  if (nodes[pval - 1].numAdj > 2) x = true;
                  else if (pval <= 0) break;
                  else backtracked[nodes[pval - 1].value - 1] = true;
                  pval = parent[nodes[pval - 1].value - 1];
               }
            }
         }
      }
      
      if (newTreeFormed)
      {
         if (trees == nullptr) trees = nextTree;
         else 
         {
            linkedList<BST *>* tmp = trees;
            while (tmp->next != nullptr) tmp = tmp->next;
            tmp->next = nextTree;
         }
      }
   }
   for (int i = 0; i < numNodes; i++)
   {
      if (visitCount[i] == 1) visitedOnce++;
      else if (visitCount[i] == 2) visitedTwice++;
   }
   TREES = trees;
}

void Graph::cycle(int indx, int p)
{
   if (c[indx] == 2) return;
   if (c[indx] == 1)
   {
      int curr = p;
      // N++;
      linkedList<int> * cp1 = forCycle;
      bool found1 = false;
      while (cp1 != nullptr && !found1)
      {
         if (cp1->object == curr) found1 = true;
         cp1 = cp1->next;
      }
      if (!found1)
      {
         linkedList<int> * cp21 = forCycle;
         while (cp21->next != nullptr) cp21 = cp21->next;
         linkedList<int> * lst1 = new linkedList<int>(curr);
         lst1->prev = cp21;
         cp21->next = lst1;
         N++;
      }
      while (curr != indx)
      {
         curr = prnt[curr];
         linkedList<int> * cp = forCycle;
         bool found = false;
         while (cp != nullptr && !found)
         {
            if (cp->object == curr) found = true;
            cp = cp->next;
         }
         if (!found)
         {
            linkedList<int> * cp2 = forCycle;
            while (cp2->next != nullptr) cp2 = cp2->next;
            linkedList<int> * lst = new linkedList<int>(curr);
            lst->prev = cp2;
            cp2->next = lst;
            N++;
         }
      }
      return;
   }
   prnt[indx] = p;
   c[indx] = 1;
   for (int i = 0; i < nodes[indx].numAdj; i++)
   {
      int nxt = nodes[indx].adjacents[i] - 1;
      if (nxt == prnt[indx]) continue;
      cycle(nxt, indx);
   }
   c[indx] = 2;
}
void Graph::printResults()
{
   int numConnectedComponents = 0;
   linkedList<BST *>* tmp = TREES;
   while (tmp != nullptr)
   {
      numConnectedComponents++;
      tmp = tmp->next;
   }
   cout << "Number of connected components: " << numConnectedComponents << endl;
   cout << "Number of nodes visited once: " << visitedOnce << endl;
   cout << "Number of nodes visited twice: " << visitedTwice << endl;
   cout << "Number of nodes that are present in a cycle: " << N << endl;
   tmp = TREES;
   int i = 1;
   while (tmp != nullptr)
   {
      cout << "Connected Component " << i << endl;
      i++;
      tmp->object->printBST("", false);
      tmp = tmp->next;
   }
   return;
}

#endif
