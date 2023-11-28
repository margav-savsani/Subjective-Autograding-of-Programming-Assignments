#ifndef GRAPH_BST_H
#define GRAPH_BST_H

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif
struct TreeNode
{
  int value;        // Train Number
                    // Price
  TreeNode *left;   // Left Child of this Node (NULL, if None)
  TreeNode *right;  // Right Child of this Node (NULL, if None)
  TreeNode *parent; // The Parent Node, NULL in case of Root

  // Constructors

  TreeNode() : value(0), left(nullptr), right(nullptr) {}
  TreeNode(int jrnyCode) : value(jrnyCode), left(nullptr), right(nullptr) {}
  TreeNode(int jrnyCode,  TreeNode *leftChild, TreeNode *rightChild, TreeNode *parent) : value(jrnyCode), left(leftChild), right(rightChild), parent(parent) {}
};
class BST
{

  

public:
  // ************************************************************
TreeNode *root;
  // Constructors!
  BST()
  {
    root = NULL;
  }
  BST(TreeNode *root)
  {
    this->root = root;
  }

  TreeNode *Search(TreeNode *s, int price)
  {
    while (s != NULL)
    {
      if (s->value == price)
      {

        return s;
      }
      else if (s->value > price)
      {
        s = s->left;
      }
      else
      {
        s = s->right;
      }
    }
    return NULL;
  }

  //
  void printBST(BST *T,const string &prefix, bool isLeft)
  {
    
    if (T->root != nullptr)
    {
      cout << prefix;

      cout << (isLeft ? "|--" : "|__");

      // print the value of the node
      cout << T->root->value << endl;
      TreeNode *curr = T->root;
      T->root = T->root->left;
      // enter the next tree level - left and right branch
      printBST(T,prefix + (isLeft ? "│   " : "    "), true);
      T->root = curr->right;
      printBST(T,prefix + (isLeft ? "│   " : "    "), false);
      T->root = curr;
    }
  }

  // The three functions below are for evaluation purposes, Do not tamper with them!
  void getBST(const string &prefix, bool isLeft);
  void clearResult();

  // Returns false, if given JourneyCode is already present in the BST
  // Inserts the element and returns True otherwise
  bool insert( int price)
  {
    if(root == NULL){
        root = new TreeNode(price,NULL,NULL,NULL);
        return true;
    }
    // Checking if similar node already exists
    if(find(price))return false;
    TreeNode *curr = root;
    while(true){
        // incrementing Size of subtree which is rooted at this node

        // Moving to the right, if price is greater
        if(price > curr->value){
            if(curr->right!=NULL){
                curr = curr->right;
            }else{
                curr->right = new TreeNode(price,NULL,NULL,curr);
                break;
                
            }
        }else{
            // moving to left if its smaller
            if(curr->left!=NULL){
                curr = curr->left;
            }else{
                curr->left = new TreeNode(price,NULL,NULL,curr);
                break;
                
            }
        }
    }
  //  this->printBST("",false);
    return true;

  }

  // Return true, if the ticket with given attributes is found, false otherwise
  bool find( int price)
  {
    if(root==NULL)return false;
    TreeNode* curr = root;
    while(true){
      
        if(curr->value==price){
            if(curr->value==price){
                return true;
            }else return false;
        } else if(curr->value > price){
      
            if(curr->left==NULL){
                return false;
            }else{
                curr = curr->left;
            }
        }else{
            if(curr->right==NULL){
                return false;
            }else{
                curr = curr->right;
            }
        }
    }
    return false;
  }
};
template <typename T>
class listOfObjects
{
public:
  T object;
  listOfObjects<T> *next;
  listOfObjects<T> *prev;

  // Constructor
  listOfObjects(T initValue)
  {
    object = initValue;
    next = prev = nullptr;
  }

  // Destructor
  ~listOfObjects() { ; }
};

class Node
{
public:
  int visit = 0;
  int color=0;
  int value;
  listOfObjects<Node *> *adj = nullptr;
  // insert other fields and methods as appropriate
};

class Graph
{
  int numNodes;
  int numEdges;
  fstream graphFile;
  
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
    if (nodes == nullptr)
    {
      cerr << "Memory allocation failure." << endl;
      exit(-1);
    }

    for (int i = 0; i < numNodes; i++)
    {
      nodes[i].value = i + 1;
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

      // Create an undirected edge from n1 to n2 and store in appropriate
      // adjacency list(s).  If an undirected edge from n1 to n2 (or
      // equivalently from n2 to n1) already exists, you shouldn't add
      // an edge.  Only if such an undirected edge didn't exist earlier,
      // should you add the edge and increment countEdges; otherwise,
      // do not increment countEdges;
      // Every time an edge is created, we also add that information to
      // graphFile
      bool search = false;
      bool search2 = false;
      if (nodes[n1].adj == nullptr)
      {
        nodes[n1].adj = new listOfObjects<Node *>(&nodes[n2]);
      }
      else
      {
        listOfObjects<Node *> *t = nodes[n1].adj;
        while (t == nullptr)
        {
          if (t->object->value == n2)
          {
            search = true;
            break;
          }
          else
          {
            t = t->next;
          }
        }
        if (search == false)
        {
          listOfObjects<Node *> *s = new listOfObjects<Node *>(&nodes[n2]);
          s->next = nodes[n1].adj;
          nodes[n1].adj = s;
        }
      }
      if (nodes[n2].adj == nullptr)
      {
        nodes[n2].adj = new listOfObjects<Node *>(&nodes[n1]);
      }
      else
      {
        listOfObjects<Node *> *p = nodes[n2].adj;
        while (p == nullptr)
        {
          if (p->object->value == n1)
          {
            search2 = true;
            break;
          }
          else
          {
            p = p->next;
          }
        }
        if (search2 == false)
        {
          listOfObjects<Node *> *s1 = new listOfObjects<Node *>(&nodes[n2]);
          s1->next = nodes[n1].adj;
          nodes[n1].adj = s1;
        }
      }

      graphFile << n1 + 1 << " " << n2 + 1 << endl;
      countEdges++;
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
  void DFS(Node *a);
   void DFS1(Node *a,BST *tr);
  void modifiedDFS();
  void printResults();
  void cycle(Node *a);
};

#endif
