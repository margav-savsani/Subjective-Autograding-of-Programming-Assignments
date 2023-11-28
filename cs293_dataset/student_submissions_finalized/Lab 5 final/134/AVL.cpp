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
  
  // First find if grandParentNode is the left or right child of
  // greatGrandParentNode
  
  bool isGPLeftChild=false;
  if(greatGrandParentNode!=NULL){
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
  }

  // Let T3 be the right child of parentNode (i.e. of y, using notation
  // from Prof. Garg's lectures
  TreeNode *T3 = parentNode->right;

  // Now replicate the single rotation for LeftLeft as from the lecture
  // notes/video using *ONLY* calls to updateAVLParentChild

  // Make parentNode (y in Prof. Naveen Garg's lectures) the appropriate
  // child of greatGrandParentNode
  updateAVLParentChild(parentNode, greatGrandParentNode, isGPLeftChild);
  if(greatGrandParentNode==NULL)
    root=parentNode;

  // Make currNode (x in Prof. Garg's lectures) the left child of
  // parentNode (y in Prof. Garg's lectures)
  // The last parameter is "true" to indicate that currNode should be
  // made the left child of parentNode
  //updateAVLParentChild(currNode, parentNode, true);
  //This is not required as the currNode is already the left child of parent node

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
  
  // First find if grandParentNode is the left or right child of
  // greatGrandParentNode

  bool isGPLeftChild=false;
  if(greatGrandParentNode!=NULL){
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
  if(greatGrandParentNode==NULL)
    root=currNode;
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
  //std::cout <<"leftrightrotationHappened\n";

  return true;
}

bool AVLTree::rotateRightLeft(TreeNode *currNode, TreeNode *parentNode, TreeNode *grandParentNode)
{
  // Implement this yourself
  TreeNode *greatGrandParentNode = grandParentNode->parent;
  
  // First find if grandParentNode is the left or right child of
  // greatGrandParentNode

  bool isGPLeftChild=false;
  if(greatGrandParentNode!=NULL){
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
  }

  TreeNode* T2=currNode->left;
  TreeNode* T3=currNode->right;

  updateAVLParentChild(currNode, greatGrandParentNode, isGPLeftChild);
  if(greatGrandParentNode==NULL)
    root=currNode;
  updateAVLParentChild(parentNode, currNode, false);
  updateAVLParentChild(grandParentNode, currNode, true);
  updateAVLParentChild(T2, grandParentNode, false);
  updateAVLParentChild(T3, parentNode, true);

  return true;
}


bool AVLTree::rotateRightRight(TreeNode *currNode, TreeNode *parentNode, TreeNode *grandParentNode)
{
  // Implement this yourself
  TreeNode *greatGrandParentNode = grandParentNode->parent;
  bool isGPLeftChild=false;

  if(greatGrandParentNode!=NULL){
    // First find if grandParentNode is the left or right child of
    // greatGrandParentNode
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
  }
  //if Greatgrandparent  is Null, isGPLeftChild value doesn't matter;
  TreeNode* T2=parentNode->left;
  updateAVLParentChild(parentNode, greatGrandParentNode, isGPLeftChild);
  if(greatGrandParentNode==NULL)
    root=parentNode;
  updateAVLParentChild(grandParentNode, parentNode, true);
  updateAVLParentChild(T2, grandParentNode, false);
  //updateAVLParentChild(currNode, parentNode, false); is of no use  
  return true;
}

// updateHeight updates height of nodes and also checks whether
// there is any imabalance.
// if theres any imbalance it returns the tree Node which is none
// other than our grandparentNode in rotation functions.

TreeNode* AVLTree::updateHeightAVL(TreeNode* currNode)
{
  if(currNode==NULL) return  NULL;
  TreeNode* updatingNode=currNode->parent; //updating its parentNode
  if(updatingNode!=NULL){
    int lChHeight=-1, rChHeight=-1; // These are bydefault values incase the node is(are) null ptrs
    if(updatingNode->left!=NULL) lChHeight=updatingNode->left->height;
    if(updatingNode->right!=NULL) rChHeight=updatingNode->right->height;

    if(updatingNode->height==max(lChHeight, rChHeight)+1){
      //std::cout <<updatingNode->JourneyCode << "caseA\n";
      return NULL; // i.e. isleft or isright but its change doesn't change
              // the height to its parent 
    }
    else if(abs(lChHeight-rChHeight) > 1){
      //std::cout<< updatingNode->JourneyCode << " " << lChHeight << " " << rChHeight << "\n";
    //  std::cout<<updatingNode->JourneyCode <<  "caseB\n";
      updatingNode->height ++ ;
      return updatingNode;
    }
    else{
      updatingNode->height ++ ; //otherwise increment the height of parent
     // std::cout <<updatingNode->JourneyCode << "caseC\n";
      return updateHeightAVL(updatingNode); //and do the same for its parent
    }
  }
  return NULL;
}

// as imbalanceNode is grandparent now, we'll find parent and curr as the children
// with greater height compared to their sibling.

bool AVLTree::resolveImbalance(TreeNode* grandParentNode){
  if(grandParentNode==NULL)
    return true;
  
  bool isParLeftChild, isCurrLeftChild;
  TreeNode* ParentNode=NULL;
  TreeNode* currNode=NULL;
  
  // This is to make sure to not get segmentation faults. 
  int GParLeftheight=-1, GParRightheight=-1;
  if(grandParentNode->left!=NULL)  GParLeftheight=grandParentNode->left->height;
  if(grandParentNode->right!=NULL)  GParRightheight=grandParentNode->right->height;
  if(GParLeftheight > GParRightheight){
    isParLeftChild = true;
    ParentNode = grandParentNode->left;
   // std::cout << ParentNode->JourneyCode << std::endl;
  }
  else{
    isParLeftChild = false;
    ParentNode = grandParentNode->right;
  }
  // We can omit "==" case because
  // heights being equal implies no change of height of their
  // parent after insertion which was already balanced which contradicts
  // the fact that this function is being called.
  //print();

  int ParLeftheight=-1, ParRightheight=-1;
  //std::cout << grandParentNode->JourneyCode << " " << ParentNode->JourneyCode << " " << ParentNode->left->JourneyCode << std::endl;

  // This is to make sure to not get segmentation faults. 
  if(ParentNode->left!=NULL)  ParLeftheight=ParentNode->left->height;
  if(ParentNode->right!=NULL)  ParRightheight=ParentNode->right->height;
 // std::cout << ParentNode->left->height <<
  if(ParLeftheight > ParRightheight){
    isCurrLeftChild = true;
   // std::cout<<"checkbefore\n";
    currNode = ParentNode->left;
   // std::cout<<"checkafter\n";
    
  }
  else{
    isCurrLeftChild = false;
    currNode = ParentNode->right;
  }
  //std::cout << grandParentNode->JourneyCode << " ";
  //std::cout << ParentNode->JourneyCode << " ";
  //std::cout << currNode->JourneyCode << "\n";

  // now calling apppropriate rotate function
  //std::cout <<"rotationHappened" << isParLeftChild << " " << isCurrLeftChild << "\n";
  if(isParLeftChild && isCurrLeftChild){
    rotateLeftLeft(currNode, ParentNode, grandParentNode);
    grandParentNode->height -= 2;
  }
  else if(isParLeftChild && !isCurrLeftChild){
    rotateLeftRight(currNode, ParentNode, grandParentNode);
    grandParentNode->height -= 2;
    ParentNode->height -= 1;
    currNode->height += 1;
  }
  else if(!isParLeftChild && isCurrLeftChild){
    rotateRightLeft(currNode, ParentNode, grandParentNode);
    grandParentNode->height -= 2;
    ParentNode->height -= 1;
    currNode->height += 1;
  }
  else{
    rotateRightRight(currNode, ParentNode, grandParentNode);
    grandParentNode->height -= 2;
  }
  // most impotant thing is to update the height of updatingNode or
  // grandparentNode.
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
  TreeNode* insertNode = new TreeNode(jrnyCode, price);
  TreeNode* varParent = NULL;
  TreeNode* varCurrent = root;
  while(varCurrent != NULL){
      //int x = varCurrent->getJourneyCode();
        if( AVLLessThan (varCurrent, insertNode)){
            varParent = varCurrent;
            varCurrent = varCurrent->right;
            //std::cout << "y\n";
        }
        else if( AVLLessThan (insertNode, varCurrent)){
                varParent = varCurrent;
                varCurrent = varCurrent->left;
                //std::cout << "x\n";
        }
        else{
            return false;
        }
    }

    if(varParent == NULL){
        root = insertNode;
        root->height = 0;
        return true;
    }

    if(AVLLessThan(varParent, insertNode)){
      updateAVLParentChild(insertNode, varParent, false);
        //varParent->right = new TreeNode(JourneyCode, price, NULL, NULL, varParent);
        //varCurrent = varParent->right;
    }
    else{
      updateAVLParentChild(insertNode, varParent, true);
        //varParent->left = new TreeNode(JourneyCode, price, NULL, NULL, varParent);
        //varCurrent = varParent->left;
    }
    insertNode->height=0;
    //print();
    //std::cout <<"beforeimbalancechcek\n";
    TreeNode* imbalanceNode=updateHeightAVL(insertNode);
    //std::cout << "imbalancecheck" << std::endl;
    //print();
    resolveImbalance(imbalanceNode);
    //std::cout <<"imbalanceresolve\n";
  return true;
}

// Returns the price on finding an element in the AVL tree that matches
// journey code. Returns -1 otherwise.
// You may assume that no two node in the tree have the same journey
// code, and journey code is the key for insertion and finding in the AVL
// tree.

int AVLTree::find(int jrnyCode)
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
    TreeNode* reqNode = new TreeNode(jrnyCode, 0); //0 is some rand journey code
    TreeNode* var = root;
    while(var != NULL){
        if(AVLLessThan(var, reqNode))
            var = var->right;
        else if(AVLLessThan(reqNode, var))
            var = var->left;
        else
          return var->getPrice();
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


