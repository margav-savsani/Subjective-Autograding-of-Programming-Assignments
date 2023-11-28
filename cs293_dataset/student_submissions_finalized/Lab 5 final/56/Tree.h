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

  // Destructor: Define this as per your requirements
  ~TreeNode() {}

  void updateParents(){       //update all the parents' heights
    if(parent != nullptr){     
      if(parent->right == nullptr || parent->left == nullptr){  //if either of left or right is NULL, just increment teh path lengths by 1 from the child  
        parent->height = height+1;
        parent->updateParents();
        
      }
      else if(parent->right != nullptr && parent->left != nullptr){   //if both children exist
        int temp_height = parent->height;
        if(parent->right == this){  //if it is the right element, find the min path length by comparing it with the left child
                
                parent->height = max(height+1, (parent->left)->height+1);
        }
        else{   //if it is the left element, find the min path length by comparing it with the right child                
                parent->height = max(height+1, (parent->right)->height+1);
        }
        if(parent->height != temp_height){
                parent->updateParents();
        }
      }
    }
  }

  int updateAVLParents(TreeNode* &curr, TreeNode* &parnt, TreeNode* &grandp){     //find the grandparent where first imbalance happens
    TreeNode* currNode = nullptr;
    TreeNode* parentNode = nullptr;
    TreeNode* grandParentNode = this;
    
    while(!grandParentNode->isImb()){               //iterate till a node is imbalanced
      grandParentNode->updateHeight();
      if(grandParentNode->parent == nullptr){    //root reached, break
        return -1;
      }
      currNode = parentNode;
      parentNode = grandParentNode;
      grandParentNode = grandParentNode->parent;
    }
    curr = currNode; parnt = parentNode; grandp = grandParentNode;
    
    if(curr != nullptr && parnt != nullptr && grandp != nullptr){    //find the relative positions off parent and grandparent with respect to curr node
      if(grandp->left == parnt){
        if(parnt->left == curr){
          return 0;          
        }
        else if(parnt->right == curr){
          return 1;
        }        
      }
      else if(grandp->right == parnt){
        if(parnt->left == curr){
          return 2;
        }
        else if(parnt->right == curr){
          
          return 3;
        }
      }
    }
    return -1;
  
    
  }

  void updateHeight(){    //update height based on left and right heights
    if(right == nullptr && left == nullptr){
      height = 0;
    }
    else if(right  == nullptr){
      height = left->height + 1;
    }
    else if(left == nullptr){
      height = right->height + 1;
    }
    else{
      height = max(right->height, left->height)+1;
    }
  }

  bool isImb(){    //check if a node is imbalanced
    if(left != nullptr && right != nullptr){
      return (abs(left->height-right->height) >= 2);    
    }
    else if(left == nullptr && right == nullptr){
      return false;
    }
    else if(left == nullptr){
      return (right->height >= 1);
    }
    else if(right == nullptr){
      return (left->height >= 1);
    }
    return false;
  }


  int getJourneyCode(){
    return JourneyCode;
  }

  int getPrice(){
    return price;
  }

  // Print information about tree node on cout
  void printInfo()
  {
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

  bool operator==(TreeNode const &node){
    if (JourneyCode == node.JourneyCode) return true;
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
  // else {
  //   cout << "NULL tree" << endl;
  // }
}

#endif
