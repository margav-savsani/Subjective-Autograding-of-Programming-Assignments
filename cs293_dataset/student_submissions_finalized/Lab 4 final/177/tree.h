#ifndef BST_H
#define BST_H
#endif

struct TreeNode{
  int JourneyCode;
  int price;
  TreeNode *left;
  TreeNode *right;
  TreeNode *parent;
  int shortestPathLength;
  int longestPathLength;

  TreeNode() : price(0), JourneyCode(0), left(nullptr), right(nullptr), shortestPathLength(0), longestPathLength(0) {}
  
  TreeNode(int jrnyCode, int jrnyPrice) : price(jrnyPrice), JourneyCode(jrnyCode), left(nullptr), right(nullptr), shortestPathLength(0), longestPathLength(0) {}
  
  TreeNode(int jrnyCode, int jrnyPrice, TreeNode *leftChild, TreeNode *rightChild, TreeNode *parent) : price(jrnyPrice), JourneyCode(jrnyCode), left(leftChild), right(rightChild), parent(parent), shortestPathLength(0), longestPathLength(0) {}

  int getImbalance() {return (longestPathLength - shortestPathLength);}
    
};

class BST{  
  TreeNode *root;
  vector<string> result;
  
public:
  BST() {root = new TreeNode;}
  BST(TreeNode *curr_root) {root = curr_root;}

  ~BST() {};
  
  bool insert(int JourneyCode, int price);
    
  bool find(int JourneyCode, int price);
    
  bool remove(int JourneyCode, int price);

  int getImbalance();

  void printBST(const string& prefix, bool isLeft);
  
  void getBST(const string& prefix, bool isLeft);
  void clearResult();
  vector<string> getResult();
  
};
  
