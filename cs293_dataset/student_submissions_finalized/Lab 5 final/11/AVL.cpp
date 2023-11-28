#ifndef AVL_H
#include "AVL.h"
#endif

#ifndef STD_HEADERS
#include <iostream>
#include <stdlib.h>
#endif



bool AVLTree::rotateLeftLeft(TreeNode *currNode, TreeNode *parentNode, TreeNode *grandParentNode)
{
  
  TreeNode *greatGrandParentNode = grandParentNode->parent; 
  bool isGPLeftChild;
  //check whether grandparent is left or right child of its parent node . 
  if (greatGrandParentNode == nullptr)  ; 
  else if (greatGrandParentNode->left == grandParentNode) {
    isGPLeftChild = true;
  }
  else if (greatGrandParentNode->right == grandParentNode) {
    isGPLeftChild = false;
  }
  else {
    cerr << "Unexpected condition encountered1!" << endl;
    return false;
  }

  TreeNode *T3 = parentNode->right;
  // make four changes for rotation : 
  updateAVLParentChild(parentNode, greatGrandParentNode, isGPLeftChild); 
  updateAVLParentChild(currNode, parentNode, true);
  updateAVLParentChild(grandParentNode, parentNode, false);
  updateAVLParentChild(T3, grandParentNode, true);
  
  //update height after update 
  grandParentNode->updateheight() ; 
  currNode->updateheight(); 
  parentNode->updateheight() ;

  return true;
}

bool AVLTree::rotateRightRight(TreeNode *currNode, TreeNode *parentNode, TreeNode *grandParentNode)
{
  
  TreeNode *greatGrandParentNode = grandParentNode->parent; 
  bool isGPLeftChild;
  //check whether grandparent is left or right child of its parent node . 
    if (greatGrandParentNode == nullptr)  ; 
    else if ( greatGrandParentNode->left == grandParentNode) {
        isGPLeftChild = true;
      }
    else if ( greatGrandParentNode->right == grandParentNode) {
        isGPLeftChild = false;
    }
    else {
        cerr << "Unexpected condition encountered2!" << endl;
        return false;
    }


  TreeNode *T3 = parentNode->left;
  updateAVLParentChild(parentNode, greatGrandParentNode, isGPLeftChild);
  updateAVLParentChild(currNode, parentNode, false);
  updateAVLParentChild(grandParentNode, parentNode, true);
  updateAVLParentChild(T3, grandParentNode, false);
  
  //update height after update
  grandParentNode->updateheight() ; 
  currNode->updateheight(); 
  parentNode->updateheight() ;

  return true;
}



bool AVLTree::rotateLeftRight(TreeNode *currNode, TreeNode *parentNode, TreeNode *grandParentNode)
{
  TreeNode *greatGrandParentNode = grandParentNode->parent;
  bool isGPLeftChild;
  //check whether grandparent is left or right child of its parent node . 
  if (greatGrandParentNode == nullptr)  ; 
  else if (greatGrandParentNode->left == grandParentNode) {
    isGPLeftChild = true;
  }
  else if (greatGrandParentNode->right == grandParentNode) {
    isGPLeftChild = false;
  }
  else {
    cerr << "Unexpected condition encountered4!" << endl;
    return false;
  }

  TreeNode *T2 = currNode->left;
  TreeNode *T3 = currNode->right;
  updateAVLParentChild(currNode, greatGrandParentNode, isGPLeftChild);
  updateAVLParentChild(parentNode, currNode, true);
  updateAVLParentChild(grandParentNode, currNode, false);
  updateAVLParentChild(T2, parentNode, false);
  updateAVLParentChild(T3, grandParentNode, true);

  //update height after update
  grandParentNode->updateheight() ; 
  parentNode->updateheight() ; 
  currNode->updateheight(); 

  return true;
}

bool AVLTree::rotateRightLeft(TreeNode *currNode, TreeNode *parentNode, TreeNode *grandParentNode)
{
  TreeNode *greatGrandParentNode = grandParentNode->parent;
  bool isGPLeftChild;
  //check whether grandparent is left or right child of its parent node . 
  if (greatGrandParentNode == nullptr)  ; 
  else if (greatGrandParentNode->left == grandParentNode) {
    isGPLeftChild = true;
  }
  else if (greatGrandParentNode->right == grandParentNode) {
    isGPLeftChild = false;
  }
  else {
    cerr << "Unexpected condition encountered3!" << endl;
    return false;
  }

  TreeNode *T2 = currNode->left;
  TreeNode *T3 = currNode->right;
  updateAVLParentChild(currNode, greatGrandParentNode, isGPLeftChild);
  updateAVLParentChild(parentNode, currNode, false);
  updateAVLParentChild(grandParentNode, currNode, true);
  updateAVLParentChild(T2, grandParentNode, false);
  updateAVLParentChild(T3, parentNode, true);
  
  //update height after update
  grandParentNode->updateheight() ; 
  parentNode->updateheight() ; 
  currNode->updateheight(); 

  return true;
}



// Returns true on successful insertion in AVL tree. Returns false otherwise.
// You may assume that no two elements being inserted have the same journey
// code, and journey code is the key for insertion and finding in the AVL
// tree.

bool AVLTree::insert(int jrnyCode, int price)
{
  TreeNode *curr = root, *parent = nullptr;
  TreeNode *child = new TreeNode(jrnyCode,price) ;
  if ( root == nullptr )   root = child ;  //base case for root .  
  else {
    //insert the element ( similar to bst insert ). 
    while (curr != nullptr) { 
      if (AVLLessThan(curr,child)) {
        parent = curr;
        curr = curr->right;
      }
      else {
         parent = curr;
         curr = curr->left;
       }
    }

    //update child's parent and the respective parents child .
    child->parent = parent ; 
    if (AVLLessThan(parent,child)) updateAVLParentChild(child,parent,false)  ; 
    else updateAVLParentChild(child,parent,true) ; 

    //increment height of the anscetors till the first imbalance . 
    TreeNode* node = parent  ; 
    int balance ; 
    while( node != nullptr ) { 
        node->updateheight();
        balance =  node->balance() ;
        if ( -1 <= balance && balance <= 1 )
                    node = node->parent ; 
        else  break ; 
     } 
     if (node == nullptr ) return true ; 
     
     // find which rotations to make . 
     if (balance > 1 && AVLLessThan(child,node->left))  rotateLeftLeft( node->left->left , node->left , node ) ; 
     else if (balance > 1 && AVLLessThan(node->left,child))  rotateLeftRight( node->left->right , node->left , node ) ; 
     else if (balance < -1 && AVLLessThan(child,node->right))  rotateRightLeft(node->right->left , node->right , node);  
     else if (balance < -1 && AVLLessThan(node->right,child))  rotateRightRight(node->right->right , node->right , node) ;
     else ; 
     
     
   }
   return true;
}

// Returns the price on finding an element in the AVL tree that matches
// journey code. Returns -1 otherwise.
// You may assume that no two node in the tree have the same journey
// code, and journey code is the key for insertion and finding in the AVL
// tree.

int AVLTree::find(int jrnyCode)
{
  TreeNode* curr = root ; 
  TreeNode* element = new TreeNode(jrnyCode,0) ;
  //similar implementaion to BST find . 
  while ( curr != nullptr ) { 
    if ( AVLLessThan(curr,element) ) 
       curr = curr->right  ; 
    else if ( AVLLessThan(element,curr) ) 
        curr = curr->left ; 
    else 
        return curr->getprice() ; 
  }
  return -1;
}

// =====================================================
// OPTIONAL: Implement "remove" only for bonus marks
// =====================================================

// Returns true on successful deletion of the entry in AVL tree with
// matching journey code. Returns false if it cannot find any such element.
//
// You may assume that no two elements in the AVL tree have the same journey
// code, and journey code is the key for insertion and finding in the AVL
// tree.

bool AVLTree::remove(int jrnyCode)
{
  // Implement deletion in AVL tree followed by balance factor restoration
  // by properly identifying x, y, z as used in Prof. Garg's lectures
  // (equivalently, currNode, parentNode, grandParentNode in our code) and
  // invoking rotateLeftLeft, rotateLeftRight, rotateRightLeft and/or
  // rotateRightRight as appropriate.

  // It is your responsibility to find out the right x, y, z (or currNode,
  // parentNode, grandParentNode) following Prof. Garg's lectures
  //
  // Once you identify these correctly, simply invoking the appropriate
  // rotation(s) should do the job.
  // You don't even need to invoke rotation twice for the double
  // rotations -- the way rotationLeftRight is implemented, and
  // rotationRightLeft should be implemented, you should be able to achieve
  // the effect of the double rotation using one invokation of the
  // appropriate member function.

  // You MUST use only AVLLessThan to compare two journey codes.  You
  // can create a new node containing the journey code to be searched
  // (along with some arbitrary price) and invoke AVLLessThan on the
  // current node in the tree that you are inspecting and the new node
  // to do your comparison.

  // REMEMBER to update the height of appropriate nodes in the tree
  // after a successful deletion.
  
  // We use "return true" below to enable compilation.  Change this as you
  // see fit.
  return true;
}


