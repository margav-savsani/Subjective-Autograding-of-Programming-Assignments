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
  
  int getprice(){
    return price;
  }

  bool operator < (TreeNode const &node)
  {
    if (JourneyCode < node.JourneyCode) return true;
    else return false;
  }

  //a function to update the heights of all the nodes in way of insertion , if needed
  //for BST this function updates height of the paththat we traversed while reaching the 
  //inserted node from the root

  void update_heights(){
    if(left==nullptr && right==nullptr){
      height = 0;
    }
    else if(left==nullptr){
      height = 1+right->height;
    }
    else if(right==nullptr){
      height = 1+left->height;
    }
    else{
      height=1+max(left->height,right->height);
    }
    if(parent!=nullptr){
      parent->update_heights();
    }
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

  //need to pass pointer to the pointer as we wish to change its value
  //function to check if we need to rotate or not i.e imbalance has occured or not

  bool check_imbalance(bool &par_curr_left,bool &grand_par_left,TreeNode **curr){

    //setting the curr node to return the correct grandparent
    *curr=this;

    if(left==nullptr && right==nullptr){
      height=0;
      if(parent==nullptr){
        return false;//no imbalance
      }
      else{
        //this happens only for a leaf node and hence only par_curr_left needs to be changed
        if(parent->left==*curr){
          par_curr_left=true;
        }
        else{
          par_curr_left=false;
        }
        return parent->check_imbalance(par_curr_left,grand_par_left,curr);
      }
    }

    else if(left==nullptr){
      height=1+right->height;
      if(right->height>=1){
        return true;
      }
      else if(parent==nullptr){
        return false;
      }
      else{
        //this situation will never happen with child having height>1
        //(else we would have got a imbalance on the child itself and function wouldn't reach here)
        //and hence we do not need to worry about changing the curr_par_left 
        if(parent->left==*curr){
          grand_par_left=true;
        }
        else{
          grand_par_left=false;
        }
        return parent->check_imbalance(par_curr_left,grand_par_left,curr);
      }
    }

    else if(right==nullptr){
      height=1+left->height;
      if(left->height>=1){
        return true;
      }
      else if(parent==nullptr){
        return false;
      }
      else{
        //this situation will never happen with child having height>1
        //(else we would have got a imbalance on the child itself and function wouldn't reach here)
        //and hence we do not need to worry about changing the curr_par_left
        if(parent->left==*curr){
          grand_par_left=true;
        }
        else{
          grand_par_left=false;
        }
        return parent->check_imbalance(par_curr_left,grand_par_left,curr);
      }
    }

    else{
      height=1+max(left->height,right->height);
      if(abs(left->height - right->height)>1){
        return true;
      }
      else if(parent==nullptr){
        return false;
      }
      else{
        //here we would have to update both par_curr_left and grand_par_left
        par_curr_left=grand_par_left;
        if(parent->left==*curr){
          grand_par_left=true;
        }
        else{
          grand_par_left=false;
        }
        return parent->check_imbalance(par_curr_left,grand_par_left,curr);
      }
    }
  }

  //decrease height of the node by 2
  void decheightby2(){
    height=height-2;
  }

  //increase height of the node by 1
  void incheightby1(){
    height=height+1;
  }

  //decrease height of the node by 1
  void decheightby1(){
    height=height-1;
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
