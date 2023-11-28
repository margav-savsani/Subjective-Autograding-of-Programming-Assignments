#ifndef AVL_H
#include "AVL.h"
#endif

#ifndef STD_HEADERS
#include <bits/stdc++.h>
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

int AVLTree::height(TreeNode *node)
{
  if(node == nullptr) return -1;

  return max(height(node->left), height(node->right)) + 1;
}

bool AVLTree::rotateLeftLeft(TreeNode *currNode, TreeNode *parentNode, TreeNode *grandParentNode)
{
  // Going back to Prof. Naveen Garg's lecture, x is *currNode,
  // y is *parentNode and z is *grandParentNode

  // Moreover, currNode is the left child of parentNode, and
  // parentNode is the left child of grandParentNode
  // That's why we are doing a rotateLeftLeft

  TreeNode *greatGrandParentNode = grandParentNode->parent;
  
  //Determine is grandParentNode is left or right child of greatGrandParentNode
  // In case greatGrandParentNode is null, then is GPLeftChild has default value false
  bool isGPLeftChild = false, isImbalanceAtRootNode = false;
  if(greatGrandParentNode == nullptr) isImbalanceAtRootNode = true;

  if(!isImbalanceAtRootNode)
  {
    if(greatGrandParentNode->left == grandParentNode) isGPLeftChild = true;
    else if(greatGrandParentNode->right == grandParentNode) isGPLeftChild= false;
    else
    {
      cerr<<"Unexpected error occured!\n";
      return false;
    }

    updateAVLParentChild(parentNode, greatGrandParentNode, isGPLeftChild);

    updateAVLParentChild(currNode, parentNode, true);

    TreeNode *T3 = parentNode->right;

    updateAVLParentChild(grandParentNode, parentNode, false);

    updateAVLParentChild(T3, grandParentNode, true);

  }
  else
  {
     updateAVLParentChild(parentNode, greatGrandParentNode, isGPLeftChild);
     updateAVLParentChild(currNode, parentNode, true);

    TreeNode *T3 = parentNode->right;

    updateAVLParentChild(grandParentNode, parentNode, false);

    updateAVLParentChild(T3, grandParentNode, true);

    root = parentNode;
  }

  int heightT1 , heightT2 , heightT3, heightT4;
  
  heightT3 = height(grandParentNode->left);
  heightT4 = height(grandParentNode->right);
  heightT1 = height(currNode->left);
  heightT2 = height(currNode->right);

  grandParentNode->height = max(heightT3 , heightT4) + 1;
  currNode->height = max(heightT1, heightT2) + 1;

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
  
  //Determine is grandParentNode is left or right child of greatGrandParentNode
  // In case greatGrandParentNode is null, then is GPLeftChild has default value false
  bool isGPLeftChild = false, isImbalanceAtRootNode = false;
  if(grandParentNode == nullptr) isImbalanceAtRootNode = true;

  if(!isImbalanceAtRootNode)
  {
    if(greatGrandParentNode->left == grandParentNode) isGPLeftChild = true;
    else if(greatGrandParentNode->right == grandParentNode) isGPLeftChild= false;
    else
    {
      cerr<<"Unexpected error occured!\n";
      return false;
    }

        TreeNode *T2 = currNode->left;

        TreeNode *T3 = currNode->right;

        updateAVLParentChild(currNode, greatGrandParentNode, isGPLeftChild);

        updateAVLParentChild(parentNode, currNode, true);

        updateAVLParentChild(grandParentNode, currNode, false);

        updateAVLParentChild(T2, parentNode, false);

        updateAVLParentChild(T3, grandParentNode, true);
  }
  else 
  {

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

    root = currNode;
  }
  assert(root == currNode);
   int heightT1 , heightT2 , heightT3, heightT4;
  
  heightT3 = height(grandParentNode->left);
  heightT4 = height(grandParentNode->right);
  heightT1 = height(currNode->left);
  heightT2 = height(currNode->right);

  grandParentNode->height = max(heightT3 , heightT4) + 1;
  currNode->height = max(heightT1, heightT2) + 1;

  return true;
}

bool AVLTree::rotateRightLeft(TreeNode *currNode, TreeNode *parentNode, TreeNode *grandParentNode)
{
  // Implement this yourself

   TreeNode *greatGrandParentNode = grandParentNode->parent;
  
  //Determine is grandParentNode is left or right child of greatGrandParentNode
  // In case greatGrandParentNode is null, then is GPLeftChild has default value false
  bool isGPLeftChild = false, isImbalanceAtRootNode = false;
  if(!isImbalanceAtRootNode)
  {
    if(greatGrandParentNode->left == grandParentNode) isGPLeftChild = true;
    else if(greatGrandParentNode->right == grandParentNode) isGPLeftChild= false;
    else
    {
      cerr<<"Unexpected error occured!\n";
      return false;
    }

  // Let T2 be the left child of currNode (i.e. of x)
   TreeNode *T2 = currNode->left;
  
   // Let T3 be the right child of currNode (i.e. of x)
   TreeNode *T3 = currNode->right;

 
  
  updateAVLParentChild(currNode, greatGrandParentNode, isGPLeftChild);

  updateAVLParentChild(parentNode, currNode, false);

  updateAVLParentChild(grandParentNode, currNode, true);

  updateAVLParentChild(T2, grandParentNode, false);

  updateAVLParentChild( T3, parentNode, true);  
  }
  else
  {

   // Let T2 be the left child of currNode (i.e. of x)
   TreeNode *T2 = currNode->left;
  
   // Let T3 be the right child of currNode (i.e. of x)
   TreeNode *T3 = currNode->right;

 
  
  // updateAVLParentChild(currNode, greatGrandParentNode, isGPLeftChild);

  updateAVLParentChild(parentNode, currNode, false);

  updateAVLParentChild(grandParentNode, currNode, true);

  updateAVLParentChild(T2, grandParentNode, false);

  updateAVLParentChild( T3, parentNode, true);

  root = currNode;
  }

  int heightT1 , heightT2 , heightT3, heightT4;
  
  heightT3 = height(grandParentNode->left);
  heightT4 = height(grandParentNode->right);
  heightT1 = height(currNode->left);
  heightT2 = height(currNode->right);

  grandParentNode->height = max(heightT3 , heightT4) + 1;
  currNode->height = max(heightT1, heightT2) + 1;


  return true;
}

bool AVLTree::rotateRightRight(TreeNode *currNode, TreeNode *parentNode, TreeNode *grandParentNode)
{
  // Implement this yourself

  TreeNode *greatGrandParentNode = grandParentNode->parent;


  //Determine is grandParentNode is left or right child of greatGrandParentNode
  // In case greatGrandParentNode is null, then is GPLeftChild has default value false
  bool isGPLeftChild = false, isImbalanceAtRootNode = false;;

  if(greatGrandParentNode == nullptr) isImbalanceAtRootNode = true;
  if(!isImbalanceAtRootNode)
  {
        if(greatGrandParentNode->left == grandParentNode) isGPLeftChild = true;
        else if(greatGrandParentNode->right == grandParentNode) isGPLeftChild= false;
        else
        {
          cerr<<"Unexpected error occured!\n";
          return false;
        }

        updateAVLParentChild(parentNode, greatGrandParentNode, isGPLeftChild);

        updateAVLParentChild(currNode, parentNode, false);


        TreeNode *T2 = parentNode->left;

        updateAVLParentChild(grandParentNode, parentNode, true);

        updateAVLParentChild(T2, grandParentNode, false);
  }
  else
  {
      updateAVLParentChild(parentNode, greatGrandParentNode, isGPLeftChild);
        updateAVLParentChild(currNode, parentNode, false);


        TreeNode *T2 = parentNode->left;
        
        updateAVLParentChild(grandParentNode, parentNode, true);

        updateAVLParentChild(T2, grandParentNode, false);

        root = parentNode;
  }

  int heightT1 , heightT2 , heightT3, heightT4;
  
  heightT3 = height(grandParentNode->left);
  heightT4 = height(grandParentNode->right);
  heightT1 = height(currNode->left);
  heightT2 = height(currNode->right);

  grandParentNode->height = max(heightT3 , heightT4) + 1;
  currNode->height = max(heightT1, heightT2) + 1;

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

  // Make a node with journey code and price
  TreeNode* node = new TreeNode(jrnyCode, price);
  
  // If initially the AVL tree is empty
  if( root == nullptr )
  { // If node is the first Journey entered, then change root
    root = node;
    return true;
  } 
  
  TreeNode* temp = root , *parent = nullptr;
  
  // Searching if given journey already exist in the AVL tree
  while(temp != nullptr)
  {
    if(AVLLessThan(node, temp))
    { 
      parent = temp;
      temp = temp->left;
    }
    else
    {
      parent = temp;
      temp = temp->right;
    }
  }
  
  
  // journey not found, so enter it in AVL tree
  if(AVLLessThan(node, parent))
  {
    updateAVLParentChild(node, parent ,true);    
  }
  else
  {
    updateAVLParentChild(node, parent, false);
  }

  // Now, we move up the Tree from parent node and update the height of trees rooted at that location.  
  while(parent != nullptr)
    {
      int leftSubTreeHeight , rightSubTreeHeight;

      if(parent->left == nullptr) leftSubTreeHeight = -1;
      else leftSubTreeHeight = parent->left->height;

      if(parent->right == nullptr) rightSubTreeHeight = -1;
      else rightSubTreeHeight = parent->right->height;

      parent->height = max(leftSubTreeHeight, rightSubTreeHeight) + 1;
      parent = parent->parent;
    }




  // Now we have to traverse up the AVL tree from node inserted initially using currNode, parentNode, grandParentNode to check where the first imbalance occurs. And make appropriate rotations
  TreeNode *currNode = node, *parentNode = node->parent, *grandParentNode = parentNode->parent;

  bool findImbalance = false;

  while(!findImbalance && grandParentNode != nullptr)
  {
    // IF imbalance is found at grandParent node, then do some rotations to restore height balance

    int leftSubTreeHeight, rightSubTreeHeight;

    leftSubTreeHeight = height(grandParentNode->left);

    rightSubTreeHeight = height(grandParentNode->right);

    if(abs(leftSubTreeHeight - rightSubTreeHeight) > 1){ if
    (grandParentNode->left == parentNode && parentNode->left == currNode)
    { rotateLeftLeft(currNode, parentNode, grandParentNode); } else if
    (grandParentNode->left == parentNode && parentNode->right == currNode)
    { rotateLeftRight(currNode, parentNode, grandParentNode); } else if
    (grandParentNode->right == parentNode && parentNode->left == currNode)
    { rotateRightLeft(currNode, parentNode, grandParentNode); } else
    { rotateRightRight(currNode, parentNode, grandParentNode); assert
    (root != nullptr); }


      findImbalance = true;

    }
    else
      //Just keep moving up the AVL tree till you find first findImbalance
    {
      currNode = parentNode;
      parentNode = grandParentNode;
      grandParentNode = grandParentNode->parent;
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
  // Implement find in AVL tree.
  // This is really no different from finding in a binary search tree.
  // This operation cannot cause any balance factor disturbances.

  // You MUST use only AVLLessThan to compare two journey codes.  You
  // can create a new node containing the journey code to be searched
  // (along with some arbitrary price) and invoke AVLLessThan on the
  // current node in the tree that you are inspecting and the new node
  // to do your comparison.

  TreeNode *node = new TreeNode(jrnyCode , 100); // Just some arbitrary price for comparison

  TreeNode *temp = root;
  while(temp != nullptr)
  {
    if(AVLLessThan(node , temp)) temp = temp->left;
    else if(AVLLessThan(temp, node)) temp = temp->right;
    else return temp->price; // Means we found the Jrny code
  }

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


