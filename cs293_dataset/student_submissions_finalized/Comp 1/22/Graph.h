#ifndef GRAPH_BST_H
#define GRAPH_BST_H

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

//=======================================================================================================//

#define CONST_GROWTH 1000
#define INIT_SIZE 1000

template <typename T>
class DynamicQueue
{
private:
  T *A;              // the array used for implementing the dynamic dequeue
  unsigned int N;    // the current size of array A
  unsigned int head; // index where next element of queue will be deleted from
  unsigned int tail; // index where next element will be inserted
  unsigned int nextSize() { return N + CONST_GROWTH; }

public:
  DynamicQueue() // default constructor
  {
    A = new T[INIT_SIZE];
    if (A != nullptr)
      N = INIT_SIZE;
    else
      N = 0;
    head = tail = 0;
  }
  // ~DynamicQueue() { delete[] A; }; // default destructor

  bool isEmpty();      // is the queue empty?
  bool isFull();       // is the queue full?
  void grow();         // grow the queue to its next size
  unsigned int size(); // return the current number of elements in the queue
  bool QInsert(T x);   // insert given element at tail of the queue; grow array size as necessary
  bool QDelete(T *x);  // delete element at head of the queue and place it in *T; returns false if queue is empty, true otherwise
  T returnHead() { return A[head]; }
  bool isPresent(T x);
  T* returnArray(){return A;}
};

template <typename T>
bool DynamicQueue<T>::isPresent(T x)
{
  if (size() == 0)
    return false;

  for (int j = head; ((j) % N) != tail; j = (j + 1) % N)
  {
    if (x == A[j])
      return true;
  }
  return false;
}

template <typename T>
bool DynamicQueue<T>::isEmpty()
{
  return size() == 0; // If size = 0, empty
}

template <typename T>
bool DynamicQueue<T>::isFull()
{
  return size() == N; // If size = N, full
}

template <typename T>
void DynamicQueue<T>::grow()
{
  if (isFull())
  {
    unsigned int old = N;
    N = nextSize();
    T *p = new T[N]; // new array of larger size
    int i = 0, j = 0;
    for (i = 0, j = head; ((j + 1) % old) != tail; i++, j = (j + 1) % old)
    {
      p[i] = A[j]; // Copying element by element into new array
    }
    head = 0;     // Setting head at 0
    tail = i + 1; // Setting tail at N + 1
    delete[] A;   // Freeing up older array
    A = p;
  }
  else
    return;
}

template <typename T>
unsigned int DynamicQueue<T>::size()
{
  if (tail == -1)
    return N; // Return N if tail is dummy value
  else
    return (tail - head + N) % N;
}

template <typename T>
bool DynamicQueue<T>::QInsert(T x)
{
  if (isPresent(x))
    return false;

  if (isFull())
    grow();

  A[tail] = x;
  tail = (tail + 1) % N;

  if (tail == head) // If N, set tail at -1 to resolve ambiguity
    tail = -1;

  return true;
}

template <typename T>
bool DynamicQueue<T>::QDelete(T *x)
{
  if (isEmpty())
    return false;
  *x = A[head];

  if (tail == -1) // Queue no longer has N elements, hence "normal" use of tail
    tail = head;

  head = (head + 1) % N;
  return true;
}

//============================================================================================//

struct TreeNode
{
  // int JourneyCode;  // Train Number
  int price;        // Price
  TreeNode *left;   // Left Child of this Node (NULL, if None)
  TreeNode *right;  // Right Child of this Node (NULL, if None)
  TreeNode *parent; // The Parent Node, NULL in case of Root

  // Constructors

  TreeNode() : price(0), left(nullptr), right(nullptr) {}
  TreeNode(int jrnyPrice) : price(jrnyPrice), left(nullptr), right(nullptr) {}
  TreeNode(int jrnyPrice, TreeNode *leftChild, TreeNode *rightChild, TreeNode *parent) : price(jrnyPrice), left(leftChild), right(rightChild), parent(parent) {}
};

class BST
{
  // Add your own field and members here
  TreeNode *root;

  // result variable is for testing purposes, Do not tamper with it!
  // vector<string> result;
public:
  void printBST(const string& prefix, bool isLeft);
  BST()
  {
    root = new TreeNode;
  }
  BST(TreeNode *root)
  {
    this->root = root;
  }

  bool insert(int price)
  {
    // if (root->JourneyCode == JourneyCode)
      // return false;

    if (root->price == 0) // When we initialize a BST using BST(), the price of root node is 0. This makes sure that root is inserted before moving ahead.
    {
      // root->JourneyCode = JourneyCode;
      root->price = price;
      return true;
    }

    if (price >= root->price)
    {
      if (root->right == nullptr) // When the right child of root doesn't exist, we create a new one and join them.
      {
        TreeNode *right = new TreeNode(price, nullptr, nullptr, root);
        (*root).right = right;
        return true;
      }
      else
      {
        TreeNode *curr = root;                      // stores the value of our root
        root = root->right;                         // changes root to root->right. This makes our RST the BST
        bool val = BST::insert(price); // recurses until the upper condition is reached.
        root = curr;                                // This changes our BST from RST to BST.
        return val;
      }
    }

    else
    {
      if (root->left == nullptr) // When the left child of root doesn't exist, we create a new one and join them.
      {
        TreeNode *left = new TreeNode(price, nullptr, nullptr, root);
        root->left = left;
        return true;
      }
      else
      {
        TreeNode *curr = root;                      // stores the value of our root
        root = root->left;                          // changes root to root->left. This makes our LST the BST
        bool val = BST::insert(price); // recurses until the upper condition is reached.
        root = curr;                                // This changes our BST from LST to BST.
        return val;
      }
    }
  }

  // Feel free to use the printBST function used earlier
};

void BST::printBST(const string& prefix, bool isLeft=false)
{
    if( root != nullptr )
    {
        cout << prefix;

        cout << (isLeft ? "|--" : "|__" );

        // print the value of the node
        cout << root->price << endl;
        TreeNode *curr = root;
        root = root->left;
        // enter the next tree level - left and right branch
        printBST( prefix + (isLeft ? "│   " : "    "), true);
        root = curr->right;
        printBST( prefix + (isLeft ? "│   " : "    "), false);
        root = curr;
    }
}


class Node
{
public:
  int value;
  DynamicQueue<int> neighbours;
  DynamicQueue<int> predIndices;
  DynamicQueue<int> dontVisit;

  Node()
  {
    value = 0;
  }

  Node(int val)
  {
    value = val;
  }
  // insert other fields and methods as appropriate
};

class Graph
{
  int numNodes;
  int numEdges;
  fstream graphFile;

  Node *nodes;
  int *visited;
  int connectedComponents=0,visitedOnce=0,visitedTwice=0;
  DynamicQueue<BST *> trees;
  DynamicQueue<int> inCycle;

  // Add appropriate fields as necessary for your implementation

public:
  Graph(int nNodes, int nEdges, std::string gFileName)
  {
    numNodes = nNodes;
    numEdges = nEdges;
    graphFile.open(gFileName, ios::out);
    if (!graphFile.is_open())
    {
      std::cerr << "Couldn't open graph file " << gFileName << ". Aborting ..." << std::endl;
      exit(-1);
    }

    graphFile << numNodes << endl;
    graphFile << numEdges << endl;
    // graphFile.close(pr);

    nodes = new Node[numNodes];
    visited = new int[numNodes];
    if (nodes == nullptr)
    {
      std::cerr << "Memory allocation failure." << std::endl;
      exit(-1);
    }

    for (int i = 0; i < numNodes; i++)
    {
      nodes[i].value = i + 1;
      visited[i] = 0;
    }

    srand(time(0));
    int n1=0, n2=0;
    int countEdges = 0;

    while (countEdges < numEdges)
    {
      do
      {
        n1 = rand() % numNodes;
        n2 = rand() % numNodes;
        // std::cin>>n1>>n2;
        // n1 -=1;
        // n2 -=1;
        // graphFile << n1 <<endl;
        // graphFile << n2 <<endl;
        // n1 -=1;
        // n2 -=1;

      } while (n1 == n2);

      // Create an undirected edge from n1 to n2 and store in appropriate
      // adjacency list(s).  If an undirected edge from n1 to n2 (or
      // equivalently from n2 to n1) already exists, you shouldn't add
      // an edge.  Only if such an undirected edge didn't exist earlier,
      // should you add the edge and increment countEdges; otherwise,
      // do not increment countEdges;
      // Every time an edge is created, we also add that information to
      // graphFile
      if (nodes[n1].neighbours.QInsert(n2))
      {
        nodes[n2].neighbours.QInsert(n1);
        int *A = nodes[n2].neighbours.returnArray();
        // cout<<n1<<' '<<n2<<endl;
        // for(int i=0;i<nodes[n2].neighbours.size();i++) cout<<A[i]<<endl;

        graphFile << n1 + 1 << " " << n2 + 1 << endl;
        countEdges++;
      }
    }
    // graphFile.close();

    // Add appropriate code as necessary for your implementation
  }

  ~Graph()
  {
    if (graphFile.is_open())
    {
      graphFile.close();
    }
    // delete[] nodes;
    // Add appropriate code as necessary for your implementation
  }

  // Add appropriate method declarations as necessary for your implementation

  void modifiedDFS();
  void dfs(int n, BST *tree, int prevNodeIndex);
  void printResults();
};

#endif
