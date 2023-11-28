#ifndef BST_H
#define BST_H

struct TreeNode{
  int value;	// Journey code
  TreeNode *left;	// Left Child of this Node (NULL, if None)
  TreeNode *right;	// Right Child of this Node (NULL, if None)
  TreeNode *parent;	// The Parent Node, NULL in case of Root
  int height;
  int h_diff;
  TreeNode() : value(0), left(nullptr), right(nullptr), height(0), h_diff(0) {}
    
};
class BST{
  TreeNode *root;
  vector<string> result;
  
public:
  BST() {root = nullptr;}
  BST(TreeNode *curr_root) {root = curr_root;}
  ~BST() {};
  bool insert(int value);
  void avl_insert(TreeNode *ptr);
  bool find(int value);
  TreeNode* myfind(int value);
  bool remove(int value);
  bool myremove(TreeNode *ptr);
  TreeNode *getMaxNode(TreeNode *ptr);

  void rotate(TreeNode* parent, TreeNode* child);
  void printBST(const string& prefix, bool isLeft);
  void update_length(TreeNode *ptr, int recur);
  void getBST(const string& prefix, bool isLeft);
  void clearResult();
  vector<string> getResult();
  int height_diff();
  void avl_delete(TreeNode *ptr);
  
};
  
#endif
