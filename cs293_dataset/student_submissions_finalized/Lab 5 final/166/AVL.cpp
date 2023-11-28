#ifndef AVL_H
#include "AVL.h"
#endif

#ifndef STD_HEADERS
#include <iostream>
#include <stdlib.h>
#endif

// Recall from Prof. Naveen Garg's lectures how the various rotations are
// applied to restore the balance factor at all nodes of an AVL tree
// to either 0, 1 or -1, after an insert or delete.
// The correspondence between the terminology in Prof. Garg's lectures and
// our terminology in this code is as follows:
//
// Prof. Garg's lectures           Our code
// ---------------------           --------
//   x                             currNode
//   y                             parentNode
//   z                             grandParentNode
//
// Recall also that z (grandParentNode) is the lowest node in the path from
// the root to the inserted node or to the deleted node (as the case may be)
// where the balance factor has either become < -1 or > 1.
// To find what x (currNode) and y (parentNode) should be, you need to
// recall Prof. Garg's lectures.
// These are slightly differently defined when inserting nodes and when
// deleting nodes

bool AVLTree::rotateLeftLeft(TreeNode *currNode, TreeNode *parentNode, TreeNode *grandParentNode)
{

  TreeNode *greatGrandParentNode = grandParentNode->parent;
  
  // First find if grandParentNode is the left or right child of
  // greatGrandParentNode
  
  bool isGPLeftChild;
  TreeNode *T3 = parentNode->right;

  if(greatGrandParentNode==nullptr){
    parentNode->parent=nullptr;
    root=parentNode;
  }
  else{
    if (greatGrandParentNode->left == grandParentNode) {
    isGPLeftChild = true;
  }
  else if (greatGrandParentNode->right == grandParentNode) {
    isGPLeftChild = false;
  }
  else {
    cerr << "Unexpected condition encountered!" << endl;
    return false;
  }

  
  updateAVLParentChild(parentNode, greatGrandParentNode, isGPLeftChild);
  }

  updateAVLParentChild(currNode, parentNode, true);
  
  updateAVLParentChild(grandParentNode, parentNode, false);

  
  updateAVLParentChild(T3, grandParentNode, true);

  return true;
}

bool AVLTree::rotateLeftRight(TreeNode *currNode, TreeNode *parentNode, TreeNode *grandParentNode)
{
  

  TreeNode *greatGrandParentNode = grandParentNode->parent;
  
  

  bool isGPLeftChild;
  if(greatGrandParentNode==nullptr){
    currNode->parent=nullptr;
    root=currNode;
  }
  else {
    if (greatGrandParentNode->left == grandParentNode) {
    isGPLeftChild = true;
  }
  else if (greatGrandParentNode->right == grandParentNode) {
    isGPLeftChild = false;
  }
  else {
    cerr << "Unexpected condition encountered!" << endl;
    return false;
  }
  updateAVLParentChild(currNode, greatGrandParentNode, isGPLeftChild);

  }

  TreeNode *T2 = currNode->left;
  TreeNode *T3 = currNode->right;
  
  updateAVLParentChild(parentNode, currNode, true);
  
  updateAVLParentChild(grandParentNode, currNode, false);
  
  
 
  updateAVLParentChild(T2, parentNode, false);

  updateAVLParentChild(T3, grandParentNode, true);
  return true;
}

bool AVLTree::rotateRightLeft(TreeNode *currNode, TreeNode *parent, TreeNode *grandParent)
{
   TreeNode *greatGrandParentNode = grandParent->parent;

  bool isGPLeftChild;
  if(greatGrandParentNode==nullptr){
    currNode->parent=nullptr;
    root=currNode;
  }
  else{
    if (greatGrandParentNode->left == grandParent) {
    isGPLeftChild = true;
  }
  else if (greatGrandParentNode->right == grandParent) {
    isGPLeftChild = false;
  }
  else {
    cerr << "Unexpected condition encountered!" << endl;
    return false;
  }
  
  

    updateAVLParentChild(currNode, greatGrandParentNode, isGPLeftChild);
  }

  TreeNode *T2 = currNode->right;
  TreeNode *T3 = currNode->left;
  
  updateAVLParentChild(parent, currNode, false);
  
  
  updateAVLParentChild(grandParent, currNode, true);
  
  
  updateAVLParentChild(T2, parent, true);

  
  updateAVLParentChild(T3, grandParent, false);  
  return true;
}

bool AVLTree::rotateRightRight(TreeNode *currNode, TreeNode *parent, TreeNode *grandParent)
{
    TreeNode *greatGrandParentNode = grandParent->parent;
  
  
  bool isGPLeftChild;
  TreeNode *T3 = parent->left;
  if(greatGrandParentNode==nullptr){
    parent->parent=nullptr;
    root=parent;
  }
  else{
    if (greatGrandParentNode->left == grandParent) {
      isGPLeftChild = true;
    }
    else if (greatGrandParentNode->right == grandParent) {
      isGPLeftChild = false;
    }
    else {
      cerr << "Unexpected condition encountered!" << endl;
      return false;
    }
  

  
    updateAVLParentChild(parent, greatGrandParentNode, isGPLeftChild);
  }
  
  updateAVLParentChild(currNode, parent, false);
  
  updateAVLParentChild(grandParent, parent, true);

 
  updateAVLParentChild(T3, grandParent, false);
  
  
  return true;
}


//function to update heights everytime we insert an element into the tree irrespective to anything

void AVLTree::updateheights(TreeNode *arey){
  arey->height=0;
  while(arey->parent != nullptr){
    if(arey->parent->left == arey && arey->parent->right ==nullptr){
      arey->parent->height=arey->height+1;
      arey= arey->parent;
    }
    else if(arey->parent->right == arey && arey->parent->left ==nullptr){
      arey->parent->height=arey->height+1;
      arey=arey->parent;
    }
    else if(arey == arey->parent->right){ 
      if(arey->height >= arey->parent->left->height){
      arey->parent->height=arey->height+1;
      arey=arey->parent;
    }
      else if(arey->height < arey->parent->left->height){
        arey->parent->height=arey->parent->left->height+1;
        arey= arey->parent;
    }
    }
    else if(arey == arey->parent->left){
      if(arey->height >= arey->parent->right->height){
      arey->parent->height = arey->height+1;
      arey=arey->parent;
    }
    else if(arey->height <= arey->parent->right->height){
      arey->parent->height = arey->parent->right->height+1;
      arey=arey->parent;
    }
    }
  }
  return;
}

//function which checks the balance of the tree and rotates the nodes to make the tree balanced

void AVLTree::balancetree(TreeNode *rey){
  
  bool fk=true;//a bool to drive the while loop
  while(fk==true && (root->left != nullptr || root->right != nullptr) && rey->parent!=root){
    if(rey->parent->parent->left==rey->parent && rey->parent->parent->right==nullptr){
        if(rey->parent->left == rey){
        rotateLeftLeft(rey,rey->parent,rey->parent->parent);
            rey->parent->right->height=rey->parent->right->height-2;
            updateheights(rey);
      }
        else if (rey->parent->right == rey){
          rotateLeftRight(rey,rey->parent,rey->parent->parent);
                      rey->height = rey->height +1;
            rey->left->height=rey->left->height - 1;
            rey->right->height = rey->right->height -2;
            updateheights(rey->left);

      }
      fk=false;
    }
    
    else if(rey->parent->parent->right==rey->parent && rey->parent->parent->left== nullptr){
      if(rey->parent->left == rey){
        rotateRightLeft(rey,rey->parent,rey->parent->parent);
                    rey->height = rey->height +1;
            rey->right->height=rey->right->height - 1;
            rey->left->height = rey->left->height -2;
            updateheights(rey->left);
      }
        else if (rey->parent->right == rey){
          rotateRightRight(rey,rey->parent,rey->parent->parent);
                      rey->parent->left->height=rey->parent->left->height-2;
            updateheights(rey);
      }
      fk=false;
    }
    else {
      if(rey->parent->left==rey){
        if(rey->parent->parent->left==rey->parent){
          if(rey->parent->height - rey->parent->parent->right->height == 2){
            rotateLeftLeft(rey,rey->parent,rey->parent->parent);
            rey->parent->right->height=rey->parent->right->height-2;
            updateheights(rey->parent->left);
            fk=false;
          }
          else rey = rey->parent;
        }
        else if(rey->parent->parent->right == rey->parent){
          if(rey->parent->height - rey->parent->parent->right->height == 2){
            rotateRightLeft(rey,rey->parent,rey->parent->parent);
            rey->height = rey->height +1;
            rey->right->height=rey->right->height - 1;
            rey->left->height = rey->left->height -2;
            updateheights(rey->left);
            fk=false;
          }
          else rey= rey->parent;
        }
      }
      else{
        if(rey->parent->parent->left==rey->parent){
          if(rey->parent->height - rey->parent->parent->left->height == 2){
            rotateLeftRight(rey,rey->parent,rey->parent->parent);
            rey->height = rey->height +1;
            rey->left->height=rey->left->height - 1;
            rey->right->height = rey->right->height -2;
            updateheights(rey->left);
            fk=false;
          }
          else rey=rey->parent;
        }
        else{
          if(rey->parent->height - rey->parent->parent->left->height == 2){
            rotateRightRight(rey,rey->parent,rey->parent->parent);
            rey->parent->left->height=rey->parent->left->height-2;
            updateheights(rey);
            fk=false;
          }
          else rey=rey->parent;
        }
      }
    }
  }
  return; 
}

// Returns true on successful insertion in AVL tree. Returns false otherwise.
// You may assume that no two elements being inserted have the same journey
// code, and journey code is the key for insertion and finding in the AVL
// tree.

bool AVLTree::insert(int jrnyCode, int price)
{ 
  TreeNode *trailer = new TreeNode(jrnyCode,price);
  if (root == nullptr){
    TreeNode *tr;
    tr=new TreeNode(0,0);
    tr->insj(jrnyCode);
    tr->insp(price);
    tr->left=nullptr;
    tr->right=nullptr;
    tr->parent=nullptr;
    root=tr;
    return true;
  }
  else {
    if (find(jrnyCode)) return false;
    else{
      TreeNode *curr;
      curr = root;
      while(true){ // incrementing Size of subtree which is rooted at this node

        // Moving to the right, if price is greater
        if(!AVLLessThan(trailer,curr)){
            if(curr->right!=NULL){
                curr = curr->right;
            }else{
              TreeNode *tre;
              tre= new TreeNode(0,0);
                tre->insj(jrnyCode);
                tre->insp(price);
                tre->parent=curr;
                curr->right=tre;
                updateheights(curr->right);
                balancetree(curr->right);
                break;
            }
        }
        else{
            if(curr->left!=NULL){
                curr = curr->left;
            }else{
                TreeNode *tre;
                tre= new TreeNode(0,0);
                tre->insj(jrnyCode);
                tre->insp(price);
                tre->parent=curr;
                curr->left=tre;
                updateheights(curr->left);
                balancetree(curr->left);
                break;
            }
        }
    }
        return true;
  }
  // Implement insertion in AVL tree followed by balance factor restoration
  // by properly identifying x, y, z as used in Prof. Garg's lectures
  // (equivalently, currNode, parentNode, grandParentNode in our code) and
  // invoking rotateLeftLeft, rotateLeftRight, rotateRightLeft and/or
  // rotateRightRight as appropriate.

  // It is your responsibility to find out the right x, y, z (or currNode,
  // parentNode, grandParentNode) following Prof. Garg's lectures
  //
  // Once you identify these correctly, simply invoking the appropriate
  // rotation should do the job.
  // You don't even need to invoke rotation twice for the double
  // rotations -- the way rotationLeftRight is implemented, and
  // rotationRightLeft should be implemented, you should be able to achieve
  // the effect of the double rotation using one invokation of the
  // appropriate member function.

  // You MUST use only AVLLessThan to compare two journey codes.  You
  // can create a new node containing the journey code to be inserted
  // and invoke AVLLessThan on the current node in the tree that you
  // are inspecting and the new node to do your comparison.

  // REMEMBER to update the heights of appropriate nodes in the tree
  // after an insertion.
  
  // We use "return true" below to enable compilation.  Change this as you
  // see fit.
}
}

// Returns the price on finding an element in the AVL tree that matches
// journey code. RETURNS 1 if found and 0 else.
// You may assume that no two node in the tree have the same journey
// code, and journey code is the key for insertion and finding in the AVL
// tree.

int AVLTree::find(int jrnyCode)
{
 TreeNode* trail = new TreeNode(jrnyCode,0);
  int bruh=0;
  TreeNode *trump;
  trump=root;
  while(bruh == 0 && trump!=nullptr){
    if(trump->getjrny() == jrnyCode){
      bruh=1;
    }
    else if(!AVLLessThan(trump,trail)){
      trump=trump->left;
    }
    else if(AVLLessThan(trump,trail)){
      trump=trump->right;
    }
  }
  return bruh;
  // Implement find in AVL tree.
  // This is really no different from finding in a binary search tree.
  // This operation cannot cause any balance factor disturbances.

  // You MUST use only AVLLessThan to compare two journey codes.  You
  // can create a new node containing the journey code to be searched
  // (along with some arbitrary price) and invoke AVLLessThan on the
  // current node in the tree that you are inspecting and the new node
  // to do your comparison.

  
}


