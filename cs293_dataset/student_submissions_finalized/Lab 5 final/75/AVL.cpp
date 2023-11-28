#include<cmath>
using namespace std;

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
  if(greatGrandParentNode!=NULL){
    if (greatGrandParentNode->left == grandParentNode) {
      isGPLeftChild = true;
    }
    else if (greatGrandParentNode->right == grandParentNode) {
      isGPLeftChild = false;
    }
    else {
      cerr << "Unexpected condition encountered! Left Left" << endl;
      return false;
    }
  }

  // Let T3 be the right child of parentNode (i.e. of y, using notation
  // from Prof. Garg's lectures
  TreeNode *T3 = parentNode->right;

  if (greatGrandParentNode!=NULL){
    updateAVLParentChild(parentNode, greatGrandParentNode, isGPLeftChild);
  }
  else {
    root = parentNode;
    root->parent = NULL;
  }
  updateAVLParentChild(currNode, parentNode, true);

  updateAVLParentChild(grandParentNode, parentNode, false);

  updateAVLParentChild(T3, grandParentNode, true);

  updateHeight(currNode);
  //cout<<currNode->JourneyCode<<" height "<<currNode->height<<endl;
  updateHeight(grandParentNode);
  //cout<<grandParentNode->JourneyCode<<" height "<<grandParentNode->height<<endl;
  updateHeight(parentNode);
  //cout<<parentNode->JourneyCode<<" height "<<parentNode->height<<endl;
 

  return true;
}

bool AVLTree::rotateLeftRight(TreeNode *currNode, TreeNode *parentNode, TreeNode *grandParentNode)
{

  TreeNode *greatGrandParentNode = grandParentNode->parent;

  bool isGPLeftChild;
  if (greatGrandParentNode!=NULL){
    if (greatGrandParentNode->left == grandParentNode) {
      isGPLeftChild = true;
    }
    else if (greatGrandParentNode->right == grandParentNode) {
      isGPLeftChild = false;
    }
    else {
      cerr << "Unexpected condition encountered! Left Right" << endl;
      return false;
    }
  }

  TreeNode *T2 = currNode->left;

  TreeNode *T3 = currNode->right;

  if (greatGrandParentNode!=NULL){
    updateAVLParentChild(currNode, greatGrandParentNode, isGPLeftChild);
  }
  else {
    root = currNode;
    root->parent = NULL;
  }

  updateAVLParentChild(parentNode, currNode, true);

  updateAVLParentChild(grandParentNode, currNode, false);

  updateAVLParentChild(T2, parentNode, false);

  updateAVLParentChild(T3, grandParentNode, true);


  updateHeight(grandParentNode);
  //cout<<grandParentNode->JourneyCode<<" height "<<grandParentNode->height<<endl;
  updateHeight(parentNode);
  //cout<<parentNode->JourneyCode<<" height "<<parentNode->height<<endl;
  updateHeight(currNode);
  //cout<<currNode->JourneyCode<<" height "<<currNode->height<<endl;
  

  return true;
}

bool AVLTree::rotateRightLeft(TreeNode *currNode, TreeNode *parent, TreeNode *grandParent)
{
  TreeNode *greatGrandParentNode = grandParent->parent;

  bool isGPLeftChild;
  if (greatGrandParentNode!=NULL){
    if (greatGrandParentNode->left == grandParent) {
      isGPLeftChild = true;
    }
    else if (greatGrandParentNode->right == grandParent) {
      isGPLeftChild = false;
    }
    else {
      cerr << "Unexpected condition encountered! Right Left" << endl;
      return false;
    }
  }

  // Let T2 be the left child of currNode (i.e. of x)
  TreeNode *T2 = currNode->left;
  
  // Let T3 be the right child of currNode (i.e. of x)
  TreeNode *T3 = currNode->right;

  if (greatGrandParentNode!=NULL){
    updateAVLParentChild(currNode, greatGrandParentNode, isGPLeftChild);
  }
  else{
    root = currNode;
    root->parent = NULL;
  }
  // attaching the parent to the current node to the right
  updateAVLParentChild(parent, currNode, false);
  // attach grandparent to current node to the left
  updateAVLParentChild(grandParent, currNode, true);
  // attach the left child of the current node to the parent node
  updateAVLParentChild(T2, parent, true);
  // attach the right child to the grandparent node to the right
  updateAVLParentChild(T3, grandParent, false);


  updateHeight(grandParent);
  //cout<<grandParent->JourneyCode<<" height "<<grandParent->height<<endl;
  updateHeight(parent);
  //cout<<parent->JourneyCode<<" height "<<parent->height<<endl;
  updateHeight(currNode);
  //cout<<currNode->JourneyCode<<" height "<<currNode->height<<endl;
  
  return true;
}

bool AVLTree::rotateRightRight(TreeNode *currNode, TreeNode *parent, TreeNode *grandParent)
{
  TreeNode *greatGrandParentNode = grandParent->parent;
  
  // First find if grandParentNode is the left or right child of
  // greatGrandParentNode
  
  bool isGPLeftChild;
  if (greatGrandParentNode!=NULL){
    if (greatGrandParentNode->left == grandParent) {
      isGPLeftChild = true;
    }
    else if (greatGrandParentNode->right == grandParent) {
      isGPLeftChild = false;
    }
    else {
      cerr << "Unexpected condition encountered! Right Right" << endl;
      return false;
    }
  }
  // stores the left child of parent
  TreeNode *T3 = parent->left;
  // attach parent to the great grand parent at the correct position
  if (greatGrandParentNode!=NULL){
    updateAVLParentChild(parent, greatGrandParentNode, isGPLeftChild);
  }
  else{
    //cout<<"I am called"<<endl;
    root = parent;
    root->parent = NULL;
  }
  // attach the current node to its parent at the right
  updateAVLParentChild(currNode, parent, false);
  // attach the grandparent to parent at the left
  updateAVLParentChild(grandParent, parent, true);
  // attach the left child of parent, to the grandparent at the right
  updateAVLParentChild(T3, grandParent, false);

  updateHeight(currNode);
  //cout<<currNode->JourneyCode<<" height "<<currNode->height<<endl;
  updateHeight(grandParent);
  //cout<<grandParent->JourneyCode<<" height "<<grandParent->height<<endl;
  updateHeight(parent);
  //cout<<parent->JourneyCode<<" height "<<parent->height<<endl;
  
  return true;
}
 
bool AVLTree::insert(int jrnyCode, int price)
{ 
  if (find(jrnyCode)==1){
    //cout<<"Journey already present "<<find(jrnyCode)<<endl;
    return false; // node already present
  }

  TreeNode* toInsert = new TreeNode(jrnyCode, price);
  if(root == NULL){
    root = toInsert;
    //cout<<"root is null"<<endl;
    TreeNode* curr = toInsert;
    while(curr!=NULL){
      updateHeight(curr);
      curr = curr->parent;
    }
    return true;
  }
  TreeNode* x = root;
  TreeNode* y = new TreeNode(0,0);
    //cout<<"checkpoint 1"<<endl;
  while(x!= NULL){
    y = x;
    //cout<<y->JourneyCode<<endl;
    //cout<<y->price<<endl;
    if (AVLLessThan(toInsert, x)){
      x = x->left;
    }
    else {
      x = x->right;
    }
  }
    //cout<<"checkpoint 2"<<endl;
  toInsert->parent = y;

  if (y==NULL){
    root=toInsert;
    // updating the heights of the trees in the path connecting root to the current leaf
    TreeNode* curr = toInsert;
    while(curr!=NULL){
      updateHeight(curr);
      curr=curr->parent;
    }
    return true;
  }
  else if(AVLLessThan(toInsert, y)){
    // y->left = toInsert;
    updateAVLParentChild(toInsert, y, true); // insert left child to the left
              //printBinaryTree(root, "", false);
    // updating the heights of the trees in the path connecting root to the current leaf
    TreeNode* curr = toInsert;
    while(curr!=NULL){
     updateHeight( curr);
      int balance = getBalance(curr);
      // Rebalancing the tree
      // Left Left Case
      //cout<<"Left Left"<<(curr->left != NULL)<<endl;
      if (balance > 1 && AVLLessThan(toInsert, curr->left)){
          rotateLeftLeft(curr->left->left, curr->left, curr);
          //cout<<"Left Left called!"<<endl;
          break;
      }
      // Right Right Case
      ///cout<<"Right Right"<<(curr->right != NULL)<<endl;
      if (balance < -1 && AVLLessThan(curr->right, toInsert)){
          rotateRightRight(curr->right->right, curr->right, curr);
          //cout<<"Right Right called!"<<endl;
          break;
      }
  
      // Left Right Case
      //cout<<"Left Right"<<(curr->left!= NULL)<<endl;
      if (balance > 1 && AVLLessThan(curr->left, toInsert)){
          rotateLeftRight(curr->left->right, curr->left, curr);
          //cout<<"Left Right called!"<<endl;
          break;
      }
  
      // Right Left Case
      //cout<<"Right Left"<<(curr->right!= NULL)<<endl;
      if (balance < -1 && AVLLessThan(toInsert, curr->right)){
          rotateRightLeft(curr->right->left, curr->right, curr);
          //cout<<"Right Left called!"<<endl;
          break;
      }
        curr=curr->parent;
      }
    return true;
  }
  else {
    //y->right = toInsert;
    updateAVLParentChild(toInsert, y, false); // insert right child to the right
              //printBinaryTree(root, "", false);
     // updating the heights of the trees in the path connecting root to the current leaf
    TreeNode* curr = toInsert;
    while(curr!=NULL){
      updateHeight(curr);
      //cout<<"Current node height: "<<curr->height<<endl;
      int balance = getBalance(curr);
      //cout<<"Balance of current: "<<balance<<endl;
      // Rebalancing the tree
      
      //cout<<"Left Left"<<(curr->left != NULL)<<endl;
      if (balance > 1 && AVLLessThan(toInsert, curr->left)){
          rotateLeftLeft(curr->left->left, curr->left, curr);
          //cout<<"Left Left called!"<<endl;
          break;
      }
      // Right Right Case
      //cout<<"Right Right"<<(curr->right != NULL)<<endl;
      if (balance < -1 && AVLLessThan(curr->right, toInsert)){
        //cout<<(curr->right==NULL)<<endl;
        //cout<<(toInsert==NULL)<<endl;
        //cout<<(curr->right->right==NULL)<<endl;
        //cout<<"current code "<<curr->JourneyCode<<endl;

          //cout<<"Calling right right "<<endl;
          rotateRightRight(curr->right->right, curr->right, curr);
          //cout<<"Right Right called!"<<endl;
         // printBinaryTree(root, "", false);
          break;
      }
  
      // Left Right Case
      //cout<<"Left Right"<<(curr->left!= NULL)<<endl;
      if (balance > 1 && AVLLessThan(curr->left, toInsert)){
          rotateLeftRight(curr->left->right, curr->left, curr);
          //cout<<"Left Right called!"<<endl;
          break;
      }
  
      // Right Left Case
      //cout<<"Right Left"<<(curr->right!= NULL)<<endl;
      if (balance < -1 && AVLLessThan(toInsert, curr->right)){
          rotateRightLeft(curr->right->left, curr->right, curr);
          //cout<<"Right Left called!"<<endl;
          break;
      }
      //cout<<"Is parent NULL? "<<(curr->parent==NULL)<<endl;
      //if (curr->parent !=NULL){
        //cout<<"Parent is: "<<curr->parent->JourneyCode<<endl;
      //}
      //cout<<"-----------------------------------------------------"<<endl;
      curr=curr->parent;

    }
    return true;
  }
}
// Get Balance factor of node N
int AVLTree:: getBalance(TreeNode *curr)
{
    if (curr == NULL)
        return 0;
    if (curr->left==NULL && curr->right==NULL){
      return 0;
    }
    else if (curr->left!=NULL && curr->right==NULL){ // only left child is non empty
      return 1+ curr->left->height;
    }
    else if (curr->left==NULL && curr->right!=NULL){ // only right child is non empty
      return (-(1+ curr->right->height));
    }
    else {
      return (curr->left->height - curr->right->height);
    }
}

void AVLTree:: updateHeight(TreeNode* curr){
  if (curr==NULL){
    cerr << "Unexpected condition encountered!" << endl;
  }
  if (curr->left==NULL && curr->right==NULL){
    curr->height = 0;
  }
  else if (curr->left!=NULL && curr->right==NULL){ // only left child is present
    curr->height = 1 + curr->left->height;
  }
  else if(curr->left==NULL && curr->right!=NULL){ // only right child is present
    curr->height = 1 + curr->right->height;
  }
  else { // both children are present
    curr->height = 1 + max(curr->right->height, curr->left->height);
  }
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
  TreeNode* toInsert = new TreeNode(jrnyCode, 0); // setting the journey price to arbitrary value (here, 0)
  if (root == NULL){
    return -1; // tree is empty
  }
  TreeNode* curr = root;

  //tree is not empty
  while (curr!=NULL){
    if (AVLLessThan(toInsert,curr)){
      curr = curr->left;
    }
    else if (AVLLessThan(curr, toInsert)){
      curr = curr->right;
    }
    else {
      delete toInsert;
      return 1; // node found
    }
  }

  // You MUST use only AVLLessThan to compare two journey codes.  You
  // can create a new node containing the journey code to be searched
  // (along with some arbitrary price) and invoke AVLLessThan on the
  // current node in the tree that you are inspecting and the new node
  // to do your comparison.

  // We use "return -1" below to enable compilation.  Change this as you
  // see fit.
  delete toInsert;
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
    TreeNode* toDelete = new TreeNode(jrnyCode,0); // to make a dummy node to compare with other nodes
    
    if (myRemove(toDelete,root, jrnyCode)){
      return true;
    }
    else{
      return false;
    }
}

bool AVLTree:: myRemove(TreeNode* toDelete, TreeNode* curr, int jrnyCode){
    if (curr==NULL){
      return false;
    }
    

    if (find(jrnyCode)==-1){
      return false;
    }

    if ( AVLLessThan(toDelete, curr)){
        // curr->left = myRemove(toDelete, curr->left,jrnyCode);
        myRemove(toDelete, curr->left,jrnyCode);
    }
    else if( AVLLessThan( curr, toDelete) ){
        // curr->right = myRemove(toDelete, curr->right,jrnyCode);
        myRemove(toDelete, curr->right,jrnyCode);
    }
    else{ // the current node is the node to be deleted
      if (curr->left == NULL && curr->right == NULL){ // node to be deleted is leaf
        if (curr==root){ // the leaf is the root of the tree
      
          root = NULL;
          return true;
         
          
        }

        if (curr->parent->left == curr){ // left child is to be deleted
          curr->parent->left = NULL;
          curr->parent = NULL;
          return true;

          
        }
        else {
          curr->parent->right = NULL; // right child is to be deleted
          curr->parent = NULL;
          return true;

          
        }

      }
      else if (curr->right !=NULL && curr->left ==NULL){
        if (curr == root){
          root = curr->right;
          curr->right->parent = NULL;
          curr->right = NULL;
          return true;
        }
        else {
          // parent exists
          if (curr->parent->left == curr)// current is left child
          {
              curr->right->parent = curr->parent;
              curr->parent->left = curr->right;
              return true;
          } 
          else { // current is right child
              curr->right->parent = curr->parent;
              curr->parent->right = curr->right;
              return true;
          }
        }

      
      }
      else if (curr->left!=NULL && curr->right == NULL){
        if (curr == root){
          root = curr->left;
          curr->left->parent = NULL;
          curr->left = NULL;
          return true;
        }
        else {
          // parent exists
          if (curr->parent->left == curr)// current is left child
          {
              curr->left->parent = curr->parent;
              curr->parent->left = curr->left;
              return true;
          } 
          else { // current is right child
              curr->left->parent = curr->parent;
              curr->parent->right = curr->left;
              return true;
          }
        }

      }
      else{
        // cout<<"I am here"<<endl;
        TreeNode* succ = minValueNode(curr->right);
        // cout<<"Is null?"<<(succ==NULL)<<endl;

        curr->setJourneyCode(succ->getJourneyCode());
        curr->setprice(succ->getprice());

        TreeNode* toDeleteSucc = new TreeNode(succ->getJourneyCode(),0);

        myRemove(toDeleteSucc, curr->right,succ->getJourneyCode());
        return true;
      }

    }

    if (curr == NULL)
      return false;

    updateHeight(curr);

    int balance = getBalance(root);

    // Left Left Case
    if (balance > 1 &&
        getBalance(curr->left) >= 0){
          // cout<<"rotate"<<endl;
          // cout<<"balance = "<<balance<<endl;
          // cout<<"is null?"<<(curr->left == NULL)<<endl;
        rotateLeftLeft(curr->left->left, curr->left, curr);
        }
 
    // Left Right Case
    if (balance > 1 &&
        getBalance(curr->left) < 0)
    {   
      // cout<<"rotate"<<endl;
        rotateLeftRight(curr->left->right, curr->left, curr);
    }
 
    // Right Right Case
    if (balance < -1 &&
        getBalance(curr->right) <= 0){
          // cout<<"rotate"<<endl;
        rotateRightRight(curr->right->right, curr->right, curr);
        }
 
    // Right Left Case
    if (balance < -1 &&
        getBalance(curr->right) > 0)
    {   
      // cout<<"rotate"<<endl;
        rotateRightLeft(curr->right->left, curr->right, curr);
    }


  return true;
}



TreeNode * AVLTree:: minValueNode(TreeNode* node)
{
    TreeNode* current = node;
 
    /* loop down to find the leftmost leaf */
    while (current->left != NULL)
        current = current->left;
 
    return current;
}


