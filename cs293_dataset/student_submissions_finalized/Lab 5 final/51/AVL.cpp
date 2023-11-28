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
  if(greatGrandParentNode != NULL)
  { 
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

  
  TreeNode *T3 = parentNode->right;

  
  updateAVLParentChild(parentNode, greatGrandParentNode, isGPLeftChild);

  updateAVLParentChild(currNode, parentNode, true);
  updateAVLParentChild(grandParentNode, parentNode, false);

  
  updateAVLParentChild(T3, grandParentNode, true);
  update(grandParentNode);
  return true;}
  if(grandParentNode -> parent == NULL)
  {
    parentNode ->parent =NULL;
    TreeNode *T3 = parentNode->right;


  updateAVLParentChild(currNode, parentNode, true);
  updateAVLParentChild(grandParentNode, parentNode, false);

  
  updateAVLParentChild(T3, grandParentNode, true);
  update(grandParentNode);
  return true;
  }
 /* {
    parentNode ->parent =NULL;

    if(parentNode->right !=NULL){
       TreeNode *dummy = parentNode->right;
       parentNode -> right = grandParentNode;
       grandParentNode->left = dummy;
       cout<<"yeah"<<endl;
       grandParentNode -> parent = new TreeNode();
       grandParentNode -> parent = parentNode;
    }
    if(parentNode -> right == NULL){
      parentNode -> right = new TreeNode();
      parentNode -> right  = grandParentNode;
      grandParentNode->left = NULL;
      cout<<"hell yeah" <<endl;
      grandParentNode -> parent = new TreeNode();
       grandParentNode -> parent = parentNode;
    }
    update(grandParentNode);
  }*/
}

bool AVLTree::rotateLeftRight(TreeNode *currNode, TreeNode *parentNode, TreeNode *grandParentNode)
{
  
  TreeNode *greatGrandParentNode = grandParentNode->parent;
  
  
 if(greatGrandParentNode != NULL){ 
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

  
  updateAVLParentChild(currNode, greatGrandParentNode, isGPLeftChild);

  
  updateAVLParentChild(parentNode, currNode, true);
  
  // Make grandParentNode (z in Prof. Garg's lectures) the right child of
  // currNode (x in Prof. Garg's lectures)
  // The last parameter is "false" to indicate that grandParentNode
  // should NOT be made the left child of currNode
  updateAVLParentChild(grandParentNode, currNode, false);
  
  
  updateAVLParentChild(T2, parentNode, false);

  // We use "true" as the third argument of the following call to indicate
  // that T3 should become the left child of grandParentNode
  updateAVLParentChild(T3, grandParentNode, true);
  update(grandParentNode);
  update(parentNode);
  return true;}
}

bool AVLTree::rotateRightLeft(TreeNode *currNode, TreeNode *parentNode, TreeNode *grandParentNode)
{  


  TreeNode *greatGrandParentNode = grandParentNode->parent;
  
  
 if(greatGrandParentNode != NULL){ 
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

  TreeNode *T2 = currNode->left;
  TreeNode *T3 = currNode->right;

  updateAVLParentChild(currNode, greatGrandParentNode, isGPLeftChild); 
  updateAVLParentChild(parentNode, currNode, false);
  updateAVLParentChild(grandParentNode, currNode, true);
  updateAVLParentChild(T3, parentNode, true);

  // We use "true" as the third argument of the following call to indicate
  // that T3 should become the left child of grandParentNode
  updateAVLParentChild(T2, grandParentNode, false);

  // Implement this yourself
  update(grandParentNode);
  update(parentNode);
  return true;}
}

bool AVLTree::rotateRightRight(TreeNode *currNode, TreeNode *parentNode, TreeNode *grandParentNode)
{    

  TreeNode *greatGrandParentNode = grandParentNode->parent;
  if(greatGrandParentNode!= NULL){ 
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

  
  TreeNode *T2 = currNode->left;
  TreeNode *T3 = currNode->right;

  updateAVLParentChild(parentNode, greatGrandParentNode, isGPLeftChild);
  updateAVLParentChild(currNode, parentNode, false);
  updateAVLParentChild(grandParentNode, parentNode, true);
  updateAVLParentChild(T2, grandParentNode, false);
  // Implement this yourself
  update(grandParentNode);
  return true;}
}



int AVLTree::get_imbalance(TreeNode* A){
  if(A->right != NULL && A->left != NULL){
   return ((A->left)->height) - ((A->right)->height);
  }
  if(A->right == NULL && A->left != NULL){
    return A->left->height;
  }
  if(A->right !=NULL && A->left ==NULL){
    return 0 - ((A->right)->height);
  }
  if(A->right ==NULL && A->left == NULL){
    return 0;
  }
}

bool AVLTree::find_rotation(TreeNode* A,TreeNode* dummy){
  if(AVLLessThan(A,dummy) && AVLLessThan(A->right,dummy)){
    return rotateRightRight(A->right->right,A->right,A);
  }
  if(AVLLessThan(A,dummy) && AVLLessThan(dummy,A->right)){
    return rotateRightLeft(A->right->left,A->right,A);
  }
  if(!AVLLessThan(A,dummy) && !AVLLessThan(A->left,dummy)){
    return rotateLeftLeft(A->left->left,A->left,A);
  }
  if(!AVLLessThan(A,dummy) && AVLLessThan(A->left,dummy)){
    return rotateLeftRight(A->left->right,A->left,A);
  }
}
TreeNode* AVLTree::first_imbalance(TreeNode* A){
  if(A != NULL){
    
    if(A-> left != NULL && A->right == NULL)
    {
      if(A->left->height >= 1 ){
        return A;
      }
    }

    else if(A-> left == NULL && A->right != NULL)
    { 
      if(A->right->height >= 1 ){
        return A;
      }
    }
    

   if(A-> left != NULL && A->right != NULL)
    { 
      if(((A->left)->height) - ((A->right)->height) > 1 || ((A->left)->height) - ((A->right)->height) <-1){
        return A;
      }
    }
    
  
      
      return first_imbalance(A->parent);
    

  }
  
  return NULL;
}


void AVLTree:: update(TreeNode* A){
  if(A != NULL)
  { if(A->left != NULL && A->right != NULL){ 
      A->height = max((A->left)->height,(A->right)->height) + 1;
    }

    if(A -> left != NULL && A->right ==NULL){
      A->height = (A->left)->height+1;
    } 

    if(A -> left == NULL && A->right !=NULL){
     A->height = (A->right)->height+1;
    } 

    if(A -> left == NULL && A->right ==NULL){
     A->height = 0;
    }
    update(A->parent);
    
    }
    
}
bool AVLTree::insert(int jrnyCode, int price)
{ 
  TreeNode *curr =root;
  TreeNode *dummy;
  dummy= new TreeNode(jrnyCode,price);
  dummy->height =0;
  if(root == NULL)
  { 
    root =new TreeNode(jrnyCode,price);
    root->height = 0;
    root->parent =NULL;
    return true;
    AVLTree(root,perComparisonCost,perParentChildUpdateCost);
  }
  if(find(jrnyCode) != -1)
  {
    return false;
  }
  else{ 

 
  if(AVLLessThan(root,dummy))
  { 
    
    if(root->right == NULL){
        
      root->right = new TreeNode(jrnyCode,price);
      root->right ->parent = root;
      root ->right ->height =0;
      root->right->parent = root;
      update(root->right);
      
      if(first_imbalance(root->right) != NULL){
      TreeNode* GP= first_imbalance(root->right);
        find_rotation(GP,root->right);
      }

      return true;
    }

    else{ 
    root = root->right;
    insert(jrnyCode,price);}
  }
  
  else if(!AVLLessThan(root,dummy)){
    if(root->left == NULL){
      root->left = new TreeNode(jrnyCode,price);
      root ->left->height =0;
      root->left->parent = root;
      update(root->left);
      if(first_imbalance(root->left) != NULL){
      TreeNode* GP= first_imbalance(root->left);
    
      find_rotation(GP,root->left);
      }
      
      return true;}
    else{
      root = root->left;
      insert(jrnyCode,price);

    }
  
  }
  
  
  root =curr;
  
 }
  return true;
}




int AVLTree::find(int jrnyCode)
{  
   TreeNode* curr = root;
   TreeNode* dummy1;
   dummy1 = new TreeNode(jrnyCode,123);
   if(root != NULL) { 
   if(!AVLLessThan(root,dummy1) && !AVLLessThan(dummy1,root)){
          return root->getprice();
   }
   else if(!AVLLessThan(root,dummy1))
        { root = root->left;
          find(jrnyCode);}
   else if(AVLLessThan(root,dummy1))
        { root = root->right;
          find(jrnyCode);}
   }
   root = curr; 
 
  return -1;
}



bool AVLTree::remove(int jrnyCode)
{
  
  return true;
}


