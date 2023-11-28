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
  // Going back to Prof. Naveen Garg's lecture, x is *currNode,
  // y is *parentNode and z is *grandParentNode

  // Moreover, currNode is the left child of parentNode, and
  // parentNode is the left child of grandParentNode
  // That's why we are doing a rotateLeftLeft

  TreeNode *greatGrandParentNode = grandParentNode->parent;
  
  if(greatGrandParentNode==NULL){
    //special case where grandparent is the actual root of the tree, and thus GGP doesn't exist
    root = parentNode;
    updateAVLParentChild(parentNode->right,grandParentNode,true);
    updateAVLParentChild(grandParentNode,parentNode,false);
    root->parent = NULL;
    return true;
  }

  // First find if grandParentNode is the left or right child of
  // greatGrandParentNode
  
  bool isGPLeftChild;
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

  // Let T3 be the right child of parentNode (i.e. of y, using notation
  // from Prof. Garg's lectures
  TreeNode *T3 = parentNode->right;

  // Now replicate the single rotation for LeftLeft as from the lecture
  // notes/video using *ONLY* calls to updateAVLParentChild

  // Make parentNode (y in Prof. Naveen Garg's lectures) the appropriate
  // child of greatGrandParentNode
  updateAVLParentChild(parentNode, greatGrandParentNode, isGPLeftChild);

  // Make currNode (x in Prof. Garg's lectures) the left child of
  // parentNode (y in Prof. Garg's lectures)
  // The last parameter is "true" to indicate that currNode should be
  // made the left child of parentNode
  updateAVLParentChild(currNode, parentNode, true);
  
  // Make grandParentNode (z in Prof. Garg's lectures) the right child of
  // parentNode (y in Prof. Garg's lectures)
  // The last parameter is "false" to indicate that grandParentNode
  // should NOT be made the left child of parentNode
  updateAVLParentChild(grandParentNode, parentNode, false);

  // Recall from Prof. Garg's lectures that the left and right subtrees
  // of currNode (i.e. x in Prof. Garg's lectures) stay unchanged after
  // the LeftLeft rotation.  So do don't need to update the children of
  // currNode at all.
  // Similarly, the right subtree of grandParentNode (i.e. z in Prof.
  // Garg's lectures) stays unchanged.  Hence, the right child of
  // grandParentNode doesn't need to be updated at all.
  // The only update needed is that the right subtree of parentNode (i.e.
  // y in Prof. Garg's notes) should now become the left
  // child of grandParentNode (i.e. of z in Prof. Garg's notes).

  // We use "true" as the third argument of the following call to indicate
  // that T3 should become the left child of grandParentNode
  updateAVLParentChild(T3, grandParentNode, true);

  return true;
}

bool AVLTree::rotateLeftRight(TreeNode *currNode, TreeNode *parentNode, TreeNode *grandParentNode)
{
  // Going back to Prof. Naveen Garg's lecture, x is *currNode,
  // y is *parentNode and z is *grandParentNode

  // Moreover, currNode is the right child of parentNode, and
  // parentNode is the left child of grandParentNode.  That's
  // why we are doing a rotateLeftRight

  TreeNode *greatGrandParentNode = grandParentNode->parent;
  
  if(greatGrandParentNode==NULL){
    //special case where grandparent is the actual root of the tree, and thus GGP doesn't exist
    root = currNode;
    updateAVLParentChild(currNode->right,grandParentNode,true);
    updateAVLParentChild(currNode->left,parentNode,false);
    updateAVLParentChild(parentNode,currNode,true);
    updateAVLParentChild(grandParentNode,currNode,false);
    root->parent = NULL;
    return true;
  }

  // First find if grandParentNode is the left or right child of
  // greatGrandParentNode

  bool isGPLeftChild;
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

  // Let T2 be the left child of currNode (i.e. of x)
  TreeNode *T2 = currNode->left;
  
  // Let T3 be the right child of currNode (i.e. of x)
  TreeNode *T3 = currNode->right;

  // Now replicate the double rotation for LeftRight as from the lecture
  // notes/video using *ONLY* calls to updateAVLParentChild
  //
  // We can directly implement the double rotation, instead of doing two
  // rotations sequentially.  So we'll look at the end-result of the
  // double rotation (refer Prof. Garg's lecture notes) and arrive at that
  // from the original tree.

  // Make currNode (x in Prof. Naveen Garg's lectures) the appropriate
  // child of greatGrandParentNode
  updateAVLParentChild(currNode, greatGrandParentNode, isGPLeftChild);

  // Make parentNode (y in Prof. Garg's lectures) the left child of
  // currNode (x in Prof. Garg's lectures)
  // The last parameter is "true" to indicate that parentNode should be
  // made the left child of currNode
  updateAVLParentChild(parentNode, currNode, true);
  
  // Make grandParentNode (z in Prof. Garg's lectures) the right child of
  // currNode (x in Prof. Garg's lectures)
  // The last parameter is "false" to indicate that grandParentNode
  // should NOT be made the left child of currNode
  updateAVLParentChild(grandParentNode, currNode, false);
  
  // Recall from Prof. Garg's lectures that the left subtree of 
  // parentNode (i.e. y in Prof. Garg's lectures) and right subtree of
  // grandParentNode (i.e. z in Prof. Garg's lectures) stay unchanged
  // after the LeftRight rotation.  So do don't need to update the
  // left child of parentNode and the right child of grandParentNode
  // at all.
  // The only update needed is that the left subtree of currNode (i.e.
  // x in Prof. Garg's notes) should now become the right subtree of
  // parentNode (y in Prof. Garg's notes).  Similarly, the right subtree
  // of currNode (i.e. of x) should now become the left subtree of
  // grandParentNode (i.e. of z).
       
  // Let's implement these updations below.
       
  // We use "false" as the third argument of the following call to indicate
  // that T2 should NOT become the left child of ParentNode
  updateAVLParentChild(T2, parentNode, false);

  // We use "true" as the third argument of the following call to indicate
  // that T3 should become the left child of grandParentNode
  updateAVLParentChild(T3, grandParentNode, true);

  return true;
}

bool AVLTree::rotateRightLeft(TreeNode *currNode, TreeNode *parentNode, TreeNode *grandParentNode)
{
  // Implement this yourself

  TreeNode *greatGrandParentNode = grandParentNode->parent;
  
  if(greatGrandParentNode==NULL){
    //special case where grandparent is the actual root of the tree, and thus GGP doesn't exist
    root = currNode;
    updateAVLParentChild(currNode->left,grandParentNode,false);
    updateAVLParentChild(currNode->right,parentNode,true);
    updateAVLParentChild(parentNode,currNode,false);
    updateAVLParentChild(grandParentNode,currNode,true);
    root->parent = NULL;
    return true;
  }

  // First find if grandParentNode is the left or right child of
  // greatGrandParentNode

  bool isGPLeftChild;
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

  updateAVLParentChild(currNode->left,grandParentNode,false);
  updateAVLParentChild(currNode->right,parentNode,true);
  updateAVLParentChild(parentNode,currNode,false);
  updateAVLParentChild(grandParentNode,currNode,true);
  updateAVLParentChild(currNode,greatGrandParentNode,isGPLeftChild);

  return true;
}

bool AVLTree::rotateRightRight(TreeNode *currNode, TreeNode *parentNode, TreeNode *grandParentNode)
{
  TreeNode *greatGrandParentNode = grandParentNode->parent;
  
  if(greatGrandParentNode==NULL){
    //special case where grandparent is the actual root of the tree, and thus GGP doesn't exist
    root = parentNode;
    updateAVLParentChild(parentNode->left,grandParentNode,false);
    updateAVLParentChild(grandParentNode,parentNode,true);
    root->parent = NULL;
    return true;
  }

  // First find if grandParentNode is the left or right child of
  // greatGrandParentNode
  
  bool isGPLeftChild;
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

  updateAVLParentChild(parentNode->left,grandParentNode,false);
  updateAVLParentChild(grandParentNode,parentNode,true);
  updateAVLParentChild(parentNode,greatGrandParentNode,isGPLeftChild);

  return true;
}

// Returns true on successful insertion in AVL tree. Returns false otherwise.
// You may assume that no two elements being inserted have the same journey
// code, and journey code is the key for insertion and finding in the AVL
// tree.

bool AVLTree::insert(int jrnyCode, int price)
{
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
  if(root==NULL){
    //insert the first node in tree
    TreeNode* newNode = new TreeNode(jrnyCode, price);
    root = newNode;
    return true;
  }
  if(find(jrnyCode)!=-1){
    //Don't insert if a journey with same code already present
    return false;
  }
  TreeNode* newNode = new TreeNode(jrnyCode,price); //node to be inserted
  TreeNode* trueRoot = root;
  if(AVLLessThan(newNode, root)){
    //insert in left subtree if journeyCode less than root's code
    if(root->left==NULL){
      updateAVLParentChild(newNode,root,true);
      int height = 0;
      root = root->left;
      while(root->parent!=NULL){
        root = root->parent;
        int l_height=-1;
        int r_height=-1;
        if(root->left!=NULL) l_height=root->left->height;
        if(root->right!=NULL) r_height=root->right->height;

        //check for imbalance and rotate if imbalance found
        if(l_height>r_height+1){
          TreeNode* child = root->left;
          if(child->left!=NULL&&child->left->height==r_height+1){
            root->height--;
            bool rotated = rotateLeftLeft(child->left,child,root);
            return rotated;
          }
          if(child->right!=NULL&&child->right->height==r_height+1){
            root->height--;
            child->right->height++;
            child->height--;
            bool rotated = rotateLeftRight(child->right,child,root);
            return rotated;
          }
          break;
        }
        if(r_height>l_height+1){
          TreeNode* child = root->right;
          if(child->left!=NULL&&child->left->height==l_height+1){
            root->height--;
            child->left->height++;
            child->height--;
            bool rotated = rotateRightLeft(child->left,child,root);
            return rotated;
          }
          if(child->right!=NULL&&child->right->height==l_height+1){
            root->height--;
            bool rotated = rotateRightRight(child->right,child,root);
            return rotated;
          }
          break;
        }

        //go up the tree if no imbalance found
        height++;
        if(height>root->height) root->height = height;
      }
    }
    else{
      root = trueRoot->left;
      insert(jrnyCode, price);
      if(root->parent!=NULL) root = trueRoot;
    }
  }
  else{
    //insert in right subtree if journeyCode larger than root's code
    if(root->right==NULL){
      updateAVLParentChild(newNode,root,false);
      int height = 0;
      root = root->right;
      while(root->parent!=NULL){
        root = root->parent;
        int l_height=-1;
        int r_height=-1;
        if(root->left!=NULL) l_height=root->left->height;
        if(root->right!=NULL) r_height=root->right->height;

        //check for imbalance and rotate if imbalance found
        if(l_height>r_height+1){
          TreeNode* child = root->left;
          if(child->left!=NULL&&child->left->height==r_height+1){
            root->height--;
            bool rotated = rotateLeftLeft(child->left,child,root);
            return rotated;
          }
          if(child->right!=NULL&&child->right->height==r_height+1){
            root->height--;
            child->right->height++;
            child->height--;
            bool rotated = rotateLeftRight(child->right,child,root);
            return rotated;
          }
          break;
        }
        if(r_height>l_height+1){
          TreeNode* child = root->right;
          if(child->left!=NULL&&child->left->height==l_height+1){
            root->height--;
            child->left->height++;
            child->height--;
            bool rotated = rotateRightLeft(child->left,child,root);
            return rotated;
          }
          if(child->right!=NULL&&child->right->height==l_height+1){
            root->height--;
            bool rotated = rotateRightRight(child->right,child,root);
            return rotated;
          }
          break;
        }

        //go up the tree if no imbalance found
        height++;
        if(height>root->height) root->height = height;
      }
    }
    else{
      root = trueRoot->right;
      insert(jrnyCode, price);
      if(root->parent!=NULL) root = trueRoot;
    }
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
  // Implement find in BST

  // You MUST use only BSTLessThan to compare two journey codes.  You
  // can create a new node containing the journey code to be searched
  // (along with some arbitrary price) and invoke BSTLessThan on the
  // current node in the tree that you are inspecting and the new node
  // to do your comparison.

  // We use "return -1" below to enable compilation.  Change this as you
  // see fit.
  if(root==NULL) return -1; //Node not found
  TreeNode* temp_node = new TreeNode(jrnyCode,-1);
  if((!AVLLessThan(root,temp_node))&&(!AVLLessThan(temp_node,root))) return 1; //Node found
  TreeNode* true_root = root;
  if(AVLLessThan(root,temp_node)){
    //Search in right if value of node required is greater than root
      root = true_root->right;
      int ans = find(jrnyCode);
      root = true_root;
      delete temp_node;
      return ans;
  }
  else{
    //Search in left if value of node required is smaller than root
      root = true_root->left;
      int ans = find(jrnyCode);
      root = true_root;
      delete temp_node;
      return ans;
  }
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


