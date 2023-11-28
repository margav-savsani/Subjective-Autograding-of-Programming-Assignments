#ifndef AVL_H
#include "AVL.h"
#endif

#ifndef STD_HEADERS
#include <iostream>
#include <stdlib.h>
#include<cmath>
#include<algorithm>
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
  if(greatGrandParentNode != nullptr){
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

  if(greatGrandParentNode != nullptr){
   updateAVLParentChild(parentNode, greatGrandParentNode, isGPLeftChild);
  }
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
  if(T3 != nullptr){
    updateAVLParentChild(T3, grandParentNode, true);
  }

  // currNode->height = 1+max(getHeight(currNode->left),getHeight(currNode->right));
  // parentNode->height = 1+max(getHeight(parentNode->left),getHeight(parentNode->right));
  // grandParentNode->height = 1+max(getHeight(grandParentNode->left),getHeight(grandParentNode->right));

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

  if(greatGrandParentNode != nullptr){
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

  if(greatGrandParentNode != nullptr){
    updateAVLParentChild(currNode, greatGrandParentNode, isGPLeftChild);
  }

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

  if(T2 != nullptr){
    updateAVLParentChild(T2, parentNode, false);
  }
  // We use "true" as the third argument of the following call to indicate
  // that T3 should become the left child of grandParentNode
  if(T3 != nullptr){
    updateAVLParentChild(T3, grandParentNode, true);
  }


  // currNode->height = 1+max(getHeight(currNode->left),getHeight(currNode->right));
  // parentNode->height = 1+max(getHeight(parentNode->left),getHeight(parentNode->right));
  // grandParentNode->height = 1+max(getHeight(grandParentNode->left),getHeight(grandParentNode->right));



  return true;
}

bool AVLTree::rotateRightLeft(TreeNode *currNode, TreeNode *parentNode, TreeNode *grandParentNode)
{
  // Implement this yourself
    
    TreeNode *greatGrandParentNode = grandParentNode->parent;
    
    bool isGPLeftChild;

    if(greatGrandParentNode != nullptr){
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

    TreeNode *T2 = currNode->left;
    
    TreeNode *T3 = currNode->right;

    if(greatGrandParentNode != nullptr){
      updateAVLParentChild(currNode, greatGrandParentNode, isGPLeftChild);
    }

    updateAVLParentChild(parentNode, currNode, false);

    updateAVLParentChild(grandParentNode, currNode, true);
    
    if(T3 != nullptr){
      updateAVLParentChild(T3, parentNode, true);
    }

    if(T2 != nullptr){
      updateAVLParentChild(T2, grandParentNode, false);
    }

  // currNode->height = 1+max(getHeight(currNode->left),getHeight(currNode->right));
  // parentNode->height = 1+max(getHeight(parentNode->left),getHeight(parentNode->right));
  // grandParentNode->height = 1+max(getHeight(grandParentNode->left),getHeight(grandParentNode->right));

    return true;
}

bool AVLTree::rotateRightRight(TreeNode *currNode, TreeNode *parentNode, TreeNode *grandParentNode)
{
  // Implement this yourself
    
    TreeNode *greatGrandParentNode = grandParentNode->parent;
      
      bool isGPLeftChild;

      if(greatGrandParentNode != nullptr){
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

      TreeNode *T3 = parentNode->left;

      if(greatGrandParentNode != nullptr){
        updateAVLParentChild(parentNode, greatGrandParentNode, isGPLeftChild);
      }

      

      updateAVLParentChild(currNode, parentNode, false);

      updateAVLParentChild(grandParentNode, parentNode, true);

      if(T3 != nullptr){
        updateAVLParentChild(T3, grandParentNode, false);
      }
    
    
  // currNode->height = 1+max(getHeight(currNode->left),getHeight(currNode->right));
  // parentNode->height = 1+max(getHeight(parentNode->left),getHeight(parentNode->right));
  // grandParentNode->height = 1+max(getHeight(grandParentNode->left),getHeight(grandParentNode->right));

  return true;
}

// Returns true on successful insertion in AVL tree. Returns false otherwise.
// You may assume that no two elements being inserted have the same journey
// code, and journey code is the key for insertion and finding in the AVL
// tree.

bool AVLTree::insert(int jrnyCode, int price)
{
    
  TreeNode *currNode = root;
  TreeNode *parentNode = nullptr;

  //currNode = root;

  int i = -1;

  TreeNode *insert ;
  insert = new TreeNode(jrnyCode,price);

    while(currNode != nullptr){
      if(AVLLessThan(insert,currNode)){
        //currNode->height++;   // Increasing height when the node to be inserted traverses through the curent node.
        parentNode = currNode;
        currNode = currNode->left;
        i = 1;
      }
      else if(AVLLessThan(currNode,insert)){
        //currNode->height++;
        parentNode = currNode;
        currNode = currNode->right;
        i = 0;
      }
      else return false;
    }



    if(i == 1){   // if child is left node.
        parentNode->left = new TreeNode(jrnyCode,price);
        currNode = parentNode->left;
        parentNode->left->parent = parentNode;
        i = -1;
    }
    
    else if(i == 0){   // if child is right node
        parentNode->right = new TreeNode(jrnyCode,price);
        currNode = parentNode->right;
        parentNode->right->parent = parentNode;
        i = -1;
    }
    
    else{  // if the node to be inserted is a root.
        root = new TreeNode(jrnyCode,price);
        currNode = root;
    }
    


    // if(currNode != nullptr){
    //   currNode->parent = parentNode;
    // }
    
    

    // check for base case here
    // 1. parent with 2 child is imbalanced.
    // ==========

    
    TreeNode *z = nullptr;   // defining z y and x here.  currNode is x , parentNode is y and grandparentNode is z.
    if(parentNode != nullptr){
      parentNode->height = 1+max(getHeight(parentNode->left),getHeight(parentNode->right)); //y
      z = parentNode->parent;
        if(z != nullptr){
          z->height = 1+max(getHeight(z->left),getHeight(z->right));
        }
    }

   

    while(z != nullptr){

     
        if((getHeight(z->left)-getHeight(z->right)) > 1 ){  //then it is a LL or LR.
          // then we will have to check for x whether it is a left child of y or a right child.
          if(parentNode->left == currNode){  // LL
            rotateLeftLeft(currNode, parentNode, z);

            currNode->height = 1+max(getHeight(currNode->left),getHeight(currNode->right));   // updating height after rotation in proper order
            z->height = 1+max(getHeight(z->left),getHeight(z->right));
            parentNode->height = 1+max(getHeight(parentNode->left),getHeight(parentNode->right));

            TreeNode * prnt = parentNode->parent;

            updateHeight(prnt);

            break;

            
            
          }
          else if(parentNode->right == currNode){  // LR
            rotateLeftRight(currNode, parentNode, z);

            parentNode->height = 1+max(getHeight(parentNode->left),getHeight(parentNode->right));
            z->height = 1+max(getHeight(z->left),getHeight(z->right));
            currNode->height = 1+max(getHeight(currNode->left),getHeight(currNode->right));

            TreeNode * prnt = currNode->parent;

            updateHeight(prnt);
            break;
            
           
          }
       // else return false;
        }

        else if((getHeight(z->left)-getHeight(z->right)) < -1 ){  //then it is a RR or RL.
        // then we will have to check for x whether it is a left child of y or a right child.
          if(parentNode->left == currNode){  // RL
            rotateRightLeft(currNode, parentNode, z);

            z->height = 1+max(getHeight(z->left),getHeight(z->right));
            parentNode->height = 1+max(getHeight(parentNode->left),getHeight(parentNode->right));
            currNode->height = 1+max(getHeight(currNode->left),getHeight(currNode->right));

            TreeNode * prnt = currNode->parent;

            updateHeight(prnt);
            break;

          }
          else if(parentNode->right == currNode){  // RR 
            rotateRightRight(currNode, parentNode, z);
            
            z->height = 1+max(getHeight(z->left),getHeight(z->right));
            currNode->height = 1+max(getHeight(currNode->left),getHeight(currNode->right));
            parentNode->height = 1+max(getHeight(parentNode->left),getHeight(parentNode->right));

            TreeNode * prnt = parentNode->parent;

            updateHeight(prnt);
            break;
           
          }
          //else return false;
        }
     
      


      

        currNode = parentNode; // x

        parentNode = z; // y

        z = parentNode->parent;  // z
        if(z != nullptr){
          z->height = 1+max(getHeight(z->left),getHeight(z->right));  //updating height before rotation
        }

      
      

      
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
  return true;
}

// Returns the price on finding an element in the AVL tree that matches
// journey code. Returns -1 otherwise.
// You may assume that no two node in the tree have the same journey
// code, and journey code is the key for insertion and finding in the AVL
// tree.

int AVLTree::find(int jrnyCode)
{

  TreeNode *currNode = root;
  TreeNode *parentNode = nullptr;

  TreeNode *insert;
  insert = new TreeNode(jrnyCode,-1);

  while(currNode != nullptr){
    if(currNode->jrnyC() == jrnyCode){
      return currNode->prc();
    }
    else if(AVLLessThan(insert,currNode)){
      parentNode = currNode;
      currNode = currNode->left;
    }
    else if(AVLLessThan(currNode,insert)){
      parentNode = currNode;
      currNode = currNode->right;
    }
  }


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


