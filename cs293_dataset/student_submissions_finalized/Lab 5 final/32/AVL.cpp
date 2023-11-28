 #ifndef AVL_H
#include "AVL.h"
#endif

#ifndef STD_HEADERS
#include <iostream>
#include <stdlib.h>
#endif

bool AVLTree::rotateLeftLeft(TreeNode *currentNode, TreeNode *parentNode, TreeNode *grandParentNode)
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
  
  if (greatGrandParentNode->left == grandParentNode) 
    isGPLeftChild = true;
  
  
  else if (greatGrandParentNode->right == grandParentNode)   
    isGPLeftChild = false;
  
  
  else 
  {
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
  updateAVLParentChild(currentNode, parentNode, true);
  
  // Make grandParentNode (z in Prof. Garg's lectures) the right child of
  // parentNode (y in Prof. Garg's lectures)
  // The last parameter is "false" to indicate that grandParentNode
  // should NOT be made the left child of parentNode
  updateAVLParentChild(grandParentNode, parentNode, false);
  updateAVLParentChild(T3, grandParentNode, true);

  return true;
}

bool AVLTree::rotateLeftRight(TreeNode *currentNode, TreeNode *parentNode, TreeNode *grandParentNode)
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
  
  if (greatGrandParentNode->left == grandParentNode)  
    isGPLeftChild = true;
  
  else if (greatGrandParentNode->right == grandParentNode)   
    isGPLeftChild = false;
  
  
  else 
  {
    cerr << "Unexpected condition encountered!" << endl;
    return false;
  }

  // Let T2 be the left child of currNode (i.e. of x)
  TreeNode *T2 = currentNode->left;
  
  // Let T3 be the right child of currNode (i.e. of x)
  TreeNode *T3 = currentNode->right;
 
  updateAVLParentChild(currentNode, greatGrandParentNode, isGPLeftChild);
  updateAVLParentChild(parentNode, currentNode, true);
  updateAVLParentChild(grandParentNode, currentNode, false);
  updateAVLParentChild(T2, parentNode, false);
  updateAVLParentChild(T3, grandParentNode, true);

  return true;
}

bool AVLTree::rotateRightLeft(TreeNode *currentNode, TreeNode *parentNode, TreeNode *grandParentNode)
{
  //Checking for greatgrandparent
  TreeNode *greatGrandParentNode = grandParentNode->parent;
  bool isGPLeftChild;
  
  if (greatGrandParentNode->left == grandParentNode)   
    isGPLeftChild = true;
  
  
  else if (greatGrandParentNode->right == grandParentNode)   
    isGPLeftChild = false;
  
  
  else 
  {
    cerr << "Unexpected condition encountered!" << endl;
    return false;
  }
  
  //Storing right child of curr node in T2
  TreeNode *T2 = currentNode->right;
  //Storing left child of curr node in T3
  TreeNode *T3 = currentNode->left;
  //Updating Acc to steps followed in rotaion
  updateAVLParentChild(currentNode, greatGrandParentNode, isGPLeftChild);
  updateAVLParentChild(parentNode, currentNode, false);
  updateAVLParentChild(grandParentNode, currentNode, true);
  updateAVLParentChild(T2, parentNode, true);
  updateAVLParentChild(T3, grandParentNode, false);
  
  return true;
}

bool AVLTree::rotateRightRight(TreeNode *currentNode, TreeNode *parentNode, TreeNode *grandParentNode)
{
  // Implement this yourself
  //Checking for greatgrandparent
  TreeNode *greatGrandParentNode = grandParentNode->parent;
  bool isGPLeftChild;
  
  if (greatGrandParentNode->left == grandParentNode)   
    isGPLeftChild = true;
  
  
  else if (greatGrandParentNode->right == grandParentNode)   
    isGPLeftChild = false;
  
  
  else 
  {
    cerr << "Unexpected condition encountered!" << endl;
    return false;
  }
  //Storing left child of parent node in T3
  TreeNode *T3 = parentNode->left;
  //Updating Acc to steps followed in rotaion
  updateAVLParentChild(parentNode, greatGrandParentNode, isGPLeftChild);
  updateAVLParentChild(currentNode, parentNode, false);
  updateAVLParentChild(grandParentNode, parentNode, true);
  updateAVLParentChild(T3, grandParentNode, false);
  return true;
}

// Returns true on successful insertion in AVL tree. Returns false otherwise.
// You may assume that no two elements being inserted have the same journey
// code, and journey code is the key for insertion and finding in the AVL
// tree.

bool AVLTree::insert(int jrnyCode, int price)
{
  //temp will store a temporary greatgrandparent if the same is null
  TreeNode *temp;   
  //stores the node to be added
  TreeNode *node = new TreeNode(jrnyCode,price);
  // Adding the first node
  if(root == nullptr)
  {
    root = node;
    return true;
  }
  //Adding subsequent nodes
  TreeNode *current = root;
  
  while(true)
  {
    if(AVLLessThan(node, current))
    {
      if(current->left != nullptr)      
        current = current->left;
           
      else
      {
        //Making k the left child
        updateAVLParentChild(node, current, true);
        current = current->left;
        break;
      }
    }
    
    else
    {
      if(current->right != nullptr)      
        current = current->right;
           
      else
      {
        //Making k the right child
        updateAVLParentChild(node, current, false);
        current = current->right;
        break;
      }
    } 
  }
  //Stores whether we have used the temp pointer or not
  bool check = false;
  //Looping from the newly inserted node to the loop to find out
  //the first point of imbalance
  while(true)
  {
    //Storing accordingly in x y z
    TreeNode *x,*y,*z;
    x=current;
    y=current->parent;
    z=current->parent->parent;
    //If grandparent is nullptr
    //then no need to rotate
    if(z == nullptr)
    {
      //Updating height of parent node
      updateheight(y);
      return true;
    }
    //Updating height of parent node
    updateheight(y);
    //Checking imbalance at grandparent z
    if(checkimbalance(z))
    {
      //If greatgrandparent is nullptr
      //then using temp to create a dummy greatgrandparent
      if(z->parent == nullptr)
      {
        temp = new TreeNode(1,1);
        updateAVLParentChild(z,temp,true);
        check = true;
      }
      //CHECKING ROTATION 
      //1 for LEFT LEFT
      //2 for LEFT RIGHT
      //3 for RIGHT RIGHT
      //4 for RIGHT LEFT
      if(checkrotation(z,y,x) == 1)
      {
        rotateLeftLeft(x,y,z);
        //Updating heights of x y z accordingly after rotation
        updateheight(x);
        updateheight(z);
        updateheight(y);
        //Breaking the loop after rotation
        break;
      }
      
      else if(checkrotation(z,y,x) == 2)
      {
        rotateLeftRight(x,y,z);
        //Updating heights of x y z accordingly after rotation
        updateheight(y);
        updateheight(z);
        updateheight(x);
        //Breaking the loop after rotation
        break;
      }
      
      else if(checkrotation(z,y,x) == 3)
      {
        rotateRightRight(x,y,z);
        //Updating heights of x y z accordingly after rotation
        updateheight(x);
        updateheight(z);
        updateheight(y);
        //Breaking the loop after rotation
        break;
      }
      
      else if(checkrotation(z,y,x) == 4)
      {
        rotateRightLeft(x,y,z);
        //Updating heights of x y z accordingly after rotation
        updateheight(z);
        updateheight(y);
        updateheight(x);
        //Breaking the loop after rotation
        break;
      }
    }
    //If imbalance not found at z then going one step up
    current = current->parent;
  }
  //If dummy greatgrandparent was used 
  //then deleting it
  if(check)
  {
    temp->left->parent = nullptr;
    root = temp->left;
    delete temp;
  }

  return true;
}


int AVLTree::find(int jrnyCode)
{
  // We use "return -1" below to enable compilation.  Change this as you
  // see fit.
  //If root is nullptr then returning -1
  if(root == nullptr)  
     return -1;
  
  //Otherwise
  //Starting from root
  TreeNode* current = root;
  //k is the dummy node with the journey code to be searched for
  //price is -1  
  TreeNode *node = new TreeNode(jrnyCode,-1);
  
  while(true)
  {
    //Comparing whether k-jrnycode is less than curr-jrnycode
    //Going into the left subtree
    if(AVLLessThan(node, current))
    {
      if(current->left == nullptr)             
        return -1; //If not found returning -1
           
      else     
        current = current->left;      
    }
    
    //Going into the right subtree
    else if(AVLLessThan(current, node))
    {
      if(current->right==nullptr)              
        return -1; //if not found returning -01
            
      else      
        current = current->right;      
    }
    
    else          
      return current->getprice(); //If found then returning price    
  }
}


bool AVLTree::remove(int jrnyCode)
{
  return true;
}


