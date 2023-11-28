#ifndef BST_H
#define BST_H
#endif

struct TreeNode
{
  int JourneyCode;	// Journey code
  int price;		// Price
  TreeNode *left;	// Left Child of this Node (NULL, if None)
  TreeNode *right;	// Right Child of this Node (NULL, if None)
  TreeNode *parent;	// The Parent Node, NULL in case of Root
  int shortestPathLength; // Length of shortest path from this node to a leaf
                          // where a nullptr leaf contributes a path of length 0
  int longestPathLength; // Length of longest path from this node to a leaf
                         // where a nullptr leaf contributes a path of length 0
  
  TreeNode() : price(0), JourneyCode(0), left(nullptr), right(nullptr) 
  {
    shortestPathLength = longestPathLength = 0;
  }
  
  TreeNode(int jrnyCode, int jrnyPrice) : price(jrnyPrice), JourneyCode(jrnyCode), left(nullptr), right(nullptr) 
  {
    shortestPathLength = longestPathLength = 0;
  }
  
  TreeNode(int jrnyCode, int jrnyPrice, TreeNode *leftChild, TreeNode *rightChild, TreeNode *parent) : price(jrnyPrice), JourneyCode(jrnyCode), left(leftChild), right(rightChild), parent(parent)
  {
    if (leftChild == nullptr && rightChild == nullptr)
    {
      shortestPathLength = longestPathLength = 0;
    }
    else if (leftChild == nullptr)
    {
      shortestPathLength = 1 + rightChild->shortestPathLength;
      longestPathLength = 1 + rightChild->longestPathLength;
    }
    else if (rightChild == nullptr)
    {
      shortestPathLength = 1 + leftChild->shortestPathLength;
      longestPathLength = 1 + leftChild->longestPathLength;
    }
    else
    {
      shortestPathLength = 1 + min(leftChild->shortestPathLength, rightChild->shortestPathLength);
      longestPathLength = 1 + max(leftChild->longestPathLength, rightChild->longestPathLength);
    }
  }

  bool issame(TreeNode * n)
    {
        return (JourneyCode == n->JourneyCode && price == n->price);
    }

  int getImbalance()
  {
    return (longestPathLength - shortestPathLength);
  }
    
};
class BST
{
  private:
    TreeNode *root;
    vector<string> result;
  
  public:

    BST() 
    {
      root = nullptr;
    }

    BST(TreeNode *curr_root) 
    {
      root = new TreeNode(curr_root->JourneyCode, curr_root->price, 
                          curr_root->left, curr_root->right, nullptr); 
    }

    ~BST() 
    {
      delete root;
    };
    
    int shortest(TreeNode * start);

    bool updatePathLengths(TreeNode * start);

    int getshortest(TreeNode * start);

    int getlongest(TreeNode * start);

    bool insert(int JourneyCode, int price);
      
    bool find(int JourneyCode, int price);

    TreeNode * minimum(TreeNode * start);

    int minimum();
    
    TreeNode * successor(TreeNode * x);

    bool remove(int JourneyCode, int price);

    int getImbalance();

    void printBST(const string& prefix, bool isLeft);
    
    // The three functions below are for evaluation purposes, Do not tamper with them!
    void getBST(const string& prefix, bool isLeft);
    void clearResult();
    vector<string> getResult();
};
  
