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
  
  bool isGPLeftChild;
  if(greatGrandParentNode!=nullptr){
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
  else{
    isGPLeftChild=true;
  }

  // Now replicate the single rotation for LeftLeft as from the lecture
  // notes/video using *ONLY* calls to updateAVLParentChild

  // Make parentNode (y in Prof. Naveen Garg's lectures) the appropriate
  // child of greatGrandParentNode

  updateAVLParentChild(parentNode, greatGrandParentNode, isGPLeftChild);

    // Let T3 be the right child of parentNode (i.e. of y, using notation
  // from Prof. Garg's lectures
  TreeNode *T3 = parentNode->right;

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
  
  // First find if grandParentNode is the left or right child of
  // greatGrandParentNode
  bool isGPLeftChild;
  if(greatGrandParentNode!=nullptr){
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
  else{
    isGPLeftChild=true;
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

    // Let T2 be the left child of currNode (i.e. of x)
  TreeNode *T2 = currNode->left;
  
  // Let T3 be the right child of currNode (i.e. of x)
  TreeNode *T3 = currNode->right;

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
  
  // First find if grandParentNode is the left or right child of
  // greatGrandParentNode
  bool isGPLeftChild;
  if(greatGrandParentNode!=nullptr){
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
  else{
    isGPLeftChild=true;
  }

  updateAVLParentChild(currNode, greatGrandParentNode, isGPLeftChild);
     // Let T2 be the left child of currNode (i.e. of x)
  TreeNode *T2 = currNode->left;
  
  // Let T3 be the right child of currNode (i.e. of x)
  TreeNode *T3 = currNode->right;

  updateAVLParentChild(parentNode, currNode, false);

  updateAVLParentChild(grandParentNode, currNode, true);

  // We use "true" as the third argument of the following call to indicate
  // that T3 should become the left child of ParentNode
  updateAVLParentChild(T3, parentNode, true);

  // We use "false" as the third argument of the following call to indicate
  // that T2 should NOT become the left child of grandParentNode
  updateAVLParentChild(T2, grandParentNode, false);

  return true;
}

bool AVLTree::rotateRightRight(TreeNode *currNode, TreeNode *parentNode, TreeNode *grandParentNode)
{
  // Implement this yourself
      TreeNode *greatGrandParentNode = grandParentNode->parent;
  
  // First find if grandParentNode is the left or right child of
  // greatGrandParentNode
  bool isGPLeftChild;
  if(greatGrandParentNode!=nullptr){
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
  else{
    isGPLeftChild=true;//random value
  }

  updateAVLParentChild(parentNode, greatGrandParentNode, isGPLeftChild);

  // Let T2 be the left child of parentNode (i.e. of y :)
  TreeNode *T2 = parentNode->left;

  updateAVLParentChild(grandParentNode, parentNode, true);

  updateAVLParentChild(currNode, parentNode, false);

  updateAVLParentChild(T2, grandParentNode, false);

  return true;
  
  return true;
}

// Returns true on successful insertion in AVL tree. Returns false otherwise.
// You may assume that no two elements being inserted have the same journey
// code, and journey code is the key for insertion and finding in the AVL
// tree.

bool AVLTree::insert(int jrnyCode, int price)
{   
  TreeNode *ins=new TreeNode(jrnyCode, price);
  ins->left=nullptr;
  ins->right=nullptr;
  TreeNode *y=nullptr; 
  TreeNode *x=root;
  while(x!=nullptr){
    y=x;
    if(AVLLessThan(ins, x)){
        x=x->left;
    }  
    else{
        x=x->right;
    }
  }
  ins->parent=y;
  if(y==nullptr){
    root=ins;
  }
  //instead of the following 4 lines, x=ins should work
  else{
    if(AVLLessThan(ins,y))
      y->left=ins;
    else
      y->right=ins;
    if(y->parent==nullptr){//Case1: The tree has only 2 levels
        if(y->left==nullptr||y->right==nullptr){
            y->height=1;
            return true;
        }
        else{
            y->height=(y->left->height>y->right->height)? y->left->height+1 : y->right->height+1;
            return true;
        }
    }
    else{//Case2: The tree has atleast 3 levels, in which case imbalance is now possible
        //Create three nodes that represent x, y and z (curr, parent and grandparent)
        TreeNode *check=ins;
        TreeNode *checkParent =ins->parent;
        TreeNode *checkGrandparent=ins->parent->parent;
        //Assign heights to the parent and the grandparent(note that initial height of x=0)
        if(checkParent->left==nullptr || checkParent->right==nullptr){
            checkParent->height=check->height+1;
        }
        else{
            checkParent->height=(checkParent->left->height>checkParent->right->height)? checkParent->left->height+1 : checkParent->right->height+1;
        }
        if(checkGrandparent->left==nullptr || checkGrandparent->right==nullptr){
            checkGrandparent->height=checkParent->height+1;
        }
        else{
            checkGrandparent->height=(checkGrandparent->left->height>checkGrandparent->right->height)? checkGrandparent->left->height+1 : checkGrandparent->right->height+1;
        }
        //This loop goes up the tree and finds the first node whose grandparent has an imbalance and calls the respective rotation function
        while(true){
            int leftH, rightH;
            if(checkGrandparent->left==nullptr){
                leftH=-1;//If a node has no child node at its left subtree, count the height of that subtree as -1 for checking purposes
                rightH=checkParent->height;
            }
            else if(checkGrandparent->right==nullptr){
                leftH=checkParent->height;
                rightH=-1;
            }
            else{
                leftH=checkGrandparent->left->height;
                rightH=checkGrandparent->right->height;
            }
            //In the following if statement, the rotation functions are called
            //The height of only curr, parent and grandparent ever changes in case these functions are called
            //Otherwise we update the height by going up the tree
            if(abs(leftH-rightH)>1){
                if(checkParent->parent->left==checkParent){
                    if(check->parent->left==check){
                        rotateLeftLeft(check, checkParent, checkGrandparent);
                        if(checkParent->parent==nullptr){
                            root=checkParent;//It is possible that the root changes to the parent node in rotateLeftLeft, in such a case, update the root
                        }
                        checkGrandparent->height=checkParent->height-1;//Reset the necessary heights.
                        break;
                    }
                    else{
                        rotateLeftRight(check, checkParent, checkGrandparent);
                        if(check->parent==nullptr){
                            root=check;
                        }
                        check->height=checkParent->height;              //curr goes to the top and the height of the subtree doesn't change, hence it must have been equal to the height of the parent tree
                        checkParent->height--;                          //Parent height reduces by 1 (Its subchildren have heights h and h+1)
                        checkGrandparent->height=checkParent->height;   //Grandparent's height becomes the new parent's height
                        break;
                    }
                }
                else{
                    if(check->parent->left==check){
                        rotateRightLeft(check, checkParent, checkGrandparent);
                        if(check->parent==nullptr){
                            root=check;
                        }
                        check->height=checkParent->height;
                        checkParent->height--;
                        checkGrandparent->height=checkParent->height;
                        break;
                    }
                    else{
                        rotateRightRight(check, checkParent, checkGrandparent);
                        if(checkParent->parent==nullptr){
                            root=checkParent;
                        }
                        break; 
                    }
                }
            }
            else{//This process should stop if no grandparent is imbalanced, which means insertion happened without any issue
                if(checkGrandparent->parent==nullptr){
                    return true;
                }
                else{//Updating curr, parent and grandparent nodes and prices in preparation for the next iteration
                    check=checkParent;
                    checkParent=checkGrandparent;
                    checkGrandparent=checkGrandparent->parent;
                    if(checkGrandparent->left==nullptr || checkGrandparent->right==nullptr){
                        checkGrandparent->height=checkParent->height+1;
                    }
                    else{
                        checkGrandparent->height=(checkGrandparent->left->height>checkGrandparent->right->height)? checkGrandparent->left->height+1 : checkGrandparent->right->height+1;
                    }
                }
            }
        }
        return true;
    }
  }
}

// Returns the price on finding an element in the AVL tree that matches
// journey code. Returns -1 otherwise.
// You may assume that no two node in the tree have the same journey
// code, and journey code is the key for insertion and finding in the AVL
// tree.

int AVLTree::find(int jrnyCode)
{
  TreeNode *y=new TreeNode(jrnyCode,0);
  TreeNode *x=root;
    while(x!=nullptr){
        if((AVLLessThan(x,y)==false)&&((AVLLessThan(y,x))==false)){
            return x->showPrice();
        }
        else if((AVLLessThan(y,x))){
            x=x->left;
        }
        else{
            x=x->right;
        }
    }
    return -1;
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


