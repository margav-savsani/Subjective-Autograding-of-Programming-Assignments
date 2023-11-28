#ifndef TREE_H
#define TREE_H

#ifndef STD_HEADERS
#define STD_HEADERS
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#endif

using namespace std;

class TreeNode {
private:
  int JourneyCode; // Journey code: This is the key for BST and AVL tree
  int price;       // Price
public:
  TreeNode* left;  // Pointer to left child  (NULL, if no left child)
  TreeNode* right; // Pointer to right child (NULL, if no right child)
  TreeNode* parent;// Parent of this node (NULL, if no parent)
  int height;      // Height of the tree rooted at this node.  A leaf
                   // has height 0. 
  
  // Constructor:
  TreeNode(int jrnyCode, int jrnyPrice)
  {
    JourneyCode = jrnyCode;
    price = jrnyPrice;
    left = nullptr;
    right = nullptr;
    parent = nullptr;
    height = 0;
  }

  // function which returns height of the node
  // uses a recursive way to find longestPath
  int setheight(TreeNode *v){               
    int l=0; 
    if((v->left!=NULL&&v->right==NULL)){
      l++;
      l+=setheight(v->left);
      
    } 
    if((v->left==NULL&&v->right!=NULL)){
      l++;
      l+=setheight(v->right);
    }       
    if((v->left!=NULL&&v->right!=NULL)){
      l++;
      int le = l+setheight(v->left);
      int r = l+setheight(v->right);
      if(le>r)l = le;
      else l = r;
    }
    return l;
  }

  // calculates balance by comparing height of left and right 
  // returns true if balanced else false
  bool balance(){
    if((left==NULL)&&(right==NULL))return true;
    if((left!=NULL)&&(right==NULL))return setheight(left)<1;
    if((right!=NULL)&&(left==NULL))return setheight(right)<1;
    else{
      int l=setheight(left);
      int r=setheight(right);
      if((l==r)||(l==r+1)||(l==r-1)) return true;
      else return false;
    }  
  }

  // Destructor: Define this as per your requirements
  ~TreeNode() {}

  // Print information about tree node on cout
  void printInfo()
  {
    height=setheight(this);// calculates height of node before deleting
    cout << "[JC: " << JourneyCode << ", P: " << price << ", H: " << height << "]";
  }
  
  // Overloaded < operator
  // Usage: tree_node1 < tree_node2
  // Returns true if tree_node1.JourneyCode < tree_node2.JourneyCode
  // Returns false otherwise.
  //
  // Note that since JourneyCode is a private member of TreeNode,
  // we can't directly use tree_node1.JourneyCode < tree_node2.JourneyCode
  // from outside this class.
  
  bool operator < (TreeNode const &node)
  {
    if (JourneyCode < node.JourneyCode) return true;
    else return false;
  }
    
  // Makes current node the left child of parentNode if
  // isLeftChild is set to true; otherwise, it makes current node
  // the right child of parentNode.  In either case, the function
  // returns true.
  //
  // If parentNode is NULL, the function returns false.
  //
  // Note that if parentNode already had a left child, say x, and if
  // you are setting current node to be the new left child of
  // parentNode, then x will no longer be the left child of parentNode.
  // In fact, unless you save a pointer to x, you may no longer be able
  // to access x at all by walking down the tree from its root.
  // A similar observation applies if parentNode already had a right child,
  // and you are setting current node to be the new right child of
  // parentNode.
  
  bool updateParentChild(TreeNode *parentNode, bool isLeftChild)
  {
    if (parentNode != nullptr) {
      parent = parentNode;
      if (isLeftChild) {
	        parentNode->left = this;
      }
      else {
	        parentNode->right = this;
      }
      return true;
    }
    else {
      return false;
    }
  }

  // this function is just used to compare equality
  int jrCode(){
    return JourneyCode;
  }

  // used near find to return price
  int pri(){
    return price;
  }
};

// The following function is effectively the same as printBST used in
// earlier labs.  The only difference is that this is not a member
// function of any class, and hence the root must be explicitly supplied
// as a parameter

void printBinaryTree(TreeNode *root, const string& prefix, bool isLeft)
{
  if( root != nullptr )   {
    cout << prefix;
    
    cout << (isLeft ? "|--" : "|__" );
    
    // print the value of the node
    root->printInfo();
    cout << endl;
    TreeNode *curr = root;
    root = root->left;
    // enter the next tree level - left and right branch
    printBinaryTree(root, prefix + (isLeft ? "│   " : "    "), true);
    root = curr->right;
    printBinaryTree(root, prefix + (isLeft ? "│   " : "    "), false);
    root = curr;
  }
  else {
    cout << "NULL tree" << endl;
  }
}

#endif
