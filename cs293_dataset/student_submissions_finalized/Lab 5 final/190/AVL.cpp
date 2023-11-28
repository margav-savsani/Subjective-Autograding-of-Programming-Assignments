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
  TreeNode *T3 = parentNode->right;
  

  bool isGPLeftChild;
  if(greatGrandParentNode == NULL){
    isGPLeftChild = true;
    root = parentNode;
  }
  else if (greatGrandParentNode->left == grandParentNode) {
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
  updateAVLParentChild(currNode, parentNode, true);
  updateAVLParentChild(grandParentNode, parentNode, false);
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
  
  // Let T2 be the left child of currNode (i.e. of x)
  TreeNode *T2 = currNode->left;
  
  // Let T3 be the right child of currNode (i.e. of x)
  TreeNode *T3 = currNode->right;
  // First find if grandParentNode is the left or right child of
  // greatGrandParentNode

  bool isGPLeftChild;
  if(greatGrandParentNode == NULL){
    isGPLeftChild = true;
    root = currNode;
  }
  else if (greatGrandParentNode->left == grandParentNode) {
    isGPLeftChild = true;
  }
  else if (greatGrandParentNode->right == grandParentNode) {
    isGPLeftChild = false;
  }
  else {
    cerr << "Unexpected condition encountered!" << endl;
    return false;
  }

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
  TreeNode *greatGrandParentNode = grandParentNode->parent;
  TreeNode *T2 = currNode->left;
  TreeNode *T3 = currNode->right;

  
  
  bool isGPLeftChild;
  if(greatGrandParentNode == NULL){
    isGPLeftChild = true;
    root = currNode;
  }
  else if (greatGrandParentNode->left == grandParentNode) {
    isGPLeftChild = true;
  }
  else if (greatGrandParentNode->right == grandParentNode) {
    isGPLeftChild = false;
  }
  else {
    cerr << "Unexpected condition encountered!" << endl;
    return false;
  }


  // STEP 1-------------
  updateAVLParentChild(currNode, greatGrandParentNode, isGPLeftChild);

  // STEP 2-------------
  updateAVLParentChild(parentNode, currNode, false);

  //STEP 3--------------
  updateAVLParentChild(grandParentNode, currNode, true);
  //STEP 4--------------
  updateAVLParentChild(T3, parentNode, true);

  //STEP 5--------------
  updateAVLParentChild(T2, grandParentNode, false);
  
  return true;
}













bool AVLTree::rotateRightRight(TreeNode *currNode, TreeNode *parentNode, TreeNode *grandParentNode)
{
  TreeNode *greatGrandParentNode = grandParentNode->parent;
  TreeNode *T2 = parentNode->left;
  bool isGPLeftChild;
  if(greatGrandParentNode == NULL){
    isGPLeftChild = true;
    root = parentNode;
  }
  else if (greatGrandParentNode->left == grandParentNode) {
    isGPLeftChild = true;
  }
  else if (greatGrandParentNode->right == grandParentNode) {
    isGPLeftChild = false;
  }
  else {
    cerr << "Unexpected condition encountered!" << endl;
    return false;
  }

  // STEP 1-------------
  updateAVLParentChild(parentNode, greatGrandParentNode, isGPLeftChild);

  // STEP 2-------------
  updateAVLParentChild(currNode, parentNode, false);  // I think its redundant, READ the updateAVLParentChild function to clarify!

  // STEP 3-------------
  updateAVLParentChild(grandParentNode, parentNode, true);

  // STEP 4-------------
// cout << parentNode->getJourneyCode() << endl;
// cout << T2->getJourneyCode() << endl;
  updateAVLParentChild(T2, grandParentNode, false);

  // cout << grandParentNode->getJourneyCode() << endl;
  // cout << grandParentNode->right->getJourneyCode() << endl;

  return true;
}















// Returns true on successful insertion in AVL tree. Returns false otherwise.
// You may assume that no two elements being inserted have the same journey
// code, and journey code is the key for insertion and finding in the AVL
// tree.

bool AVLTree::insert(int JourneyCode, int price)
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



  // SIMPLE INSERT ****************************************
  if (find(JourneyCode) >= 0)
  {
      return false;
  }
  if (root == NULL)
  {
      root = new TreeNode(JourneyCode, price);
      return true;
  }
  TreeNode *z = new TreeNode(JourneyCode, price);
  TreeNode *y;
  y = NULL;
  TreeNode *x;
  x = root;
  while (x != NULL)
  {
      y = x;
      // if(z->JourneyCode   <   x->JourneyCode){
      if (AVLLessThan(z, x))
      {
          x = x->left;
      }
      else
      {
          x = x->right;
      }
  }
  // z->parent = y;
  if (y == NULL)
  {
      root = z;
  }
  // else if(z->JourneyCode < y->JourneyCode){
  else if (AVLLessThan(z, y))
  {
      // y->left = z;
      updateAVLParentChild(z, y, true);
  }
  else
  {
      // y->right = z;
      updateAVLParentChild(z, y, false);
  }




  // INITIAL HEIGHT UPDATION*****************************************
  TreeNode *P = z->parent;

  updateHeight(P);


  // FINDING currNode, parentNode, grandParentNode (to avoid confusion with upper code)*******
  TreeNode *currNode, *parentNode, *grandParentNode;

  currNode = z;
  parentNode = currNode->parent;
  grandParentNode = parentNode->parent;


  while(true){
    if(grandParentNode == NULL) return true;

    if(grandParentNode->left == NULL){
      if(grandParentNode->right->height > 0) break;
    }
    else if(grandParentNode->right == NULL){
      if(grandParentNode->left->height > 0) break;
    }
    else{
      if(abs(grandParentNode->left->height - grandParentNode->right->height) > 1) break;
    }


    currNode = parentNode;
    parentNode = grandParentNode;
    grandParentNode = grandParentNode->parent;
  }



  // PROPER ROTATIONS AND FINAL UPDATION OF HEIGHTS**********************************************
  bool left1; //true if parentNode is left child of grandParentNode
  bool left2; //true if currNode is left child of parentNode

  if(grandParentNode->left == parentNode) left1 = true;
  else left1 = false;

  if(parentNode->left == currNode) left2 = true;
  else left2 = false;

  // cout << left1 << " " << left2 << endl;

  if(left1 && left2) {
    rotateLeftLeft(currNode, parentNode, grandParentNode);
    grandParentNode->height -= 2;
    updateHeight(parentNode->parent);
  }
  else if(left1 && (!left2)) {
    rotateLeftRight(currNode, parentNode, grandParentNode);
    currNode->height++;
    parentNode->height--;
    grandParentNode->height -= 2;
  }
  else if((!left1) && left2) {
    rotateRightLeft(currNode, parentNode, grandParentNode);
    currNode->height++;
    parentNode->height--;
    grandParentNode->height -= 2;
  }
  else {
    rotateRightRight(currNode, parentNode, grandParentNode);
    grandParentNode->height -= 2;
    updateHeight(parentNode->parent);
  }


  return true;
}











// Returns the price on finding an element in the AVL tree that matches
// journey code. Returns -1 otherwise.
// You may assume that no two node in the tree have the same journey
// code, and journey code is the key for insertion and finding in the AVL
// tree.

int AVLTree::find(int JourneyCode)
{
  // Implement find in AVL tree.
  // This is really no different from finding in a binary search tree.
  // This operation cannot cause any balance factor disturbances.

  // You MUST use only AVLLessThan to compare two journey codes.  You
  // can create a new node containing the journey code to be searched
  // (along with some arbitrary price) and invoke AVLLessThan on the
  // current node in the tree that you are inspecting and the new node
  // to do your comparison.

  // We use "return -1" below to enable compilation.  Change this as you
  // see fit.
  TreeNode *z = new TreeNode(JourneyCode, 0);

  TreeNode *x = root;

  // while( x != NULL && x->JourneyCode != JourneyCode){
  while (x != NULL && (AVLLessThan(z, x) || AVLLessThan(x, z)))
  {
      // if( JourneyCode   <   x->JourneyCode){
      if (AVLLessThan(z, x))
      {
          x = x->left;
      }
      else
      {
          x = x->right;
      }
  }

  if (x == NULL)
  {
      return -1;
  }
  // Fact that you reached here is proof that x is the right match!
  return x->getPrice();
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





void AVLTree::updateHeight(TreeNode *P){
    while (true)
    {
        if (P == NULL)
        {
            break;
        }
        else if (P->left == NULL)
        {
            P->height = P->right->height + 1;
        }
        else if (P->right == NULL)
        {
            P->height = P->left->height + 1;
        }
        else
        {
            P->height = max(P->left->height, P->right->height) + 1;
        }
        P = P->parent;
    }
}



void AVLTree::printAVL(const string& prefix="", bool isLeft=false)
{
    if( root != NULL )
    {
        cout << prefix;

        cout << (isLeft ? "|--" : "|__" );

        // print the value of the node
        cout << root->getJourneyCode() << endl;
        TreeNode *curr = root;
        root = root->left;
        // enter the next tree level - left and right branch
        printAVL( prefix + (isLeft ? "│   " : "    "), true);
        root = curr->right;
        printAVL( prefix + (isLeft ? "│   " : "    "), false);
        root = curr;
    }
}


TreeNode* AVLTree::getRoot(){
    return root;
}


