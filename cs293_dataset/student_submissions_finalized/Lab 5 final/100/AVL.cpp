#ifndef AVL_H
#include "AVL.h"
#endif

#ifndef STD_HEADERS
#include <iostream>
#include <stdlib.h>
#endif

//this updateAVLHeight function updates height of tree rooted at node
//this function can be used to update height of partial/subtree
int updateAVLHeight(TreeNode* node){      
  if(node==nullptr)return 0;
  int lheight=updateAVLHeight(node->left);      //calculates and updates height of left 
  int rhieght=updateAVLHeight(node->right);     //and right subtree and updates height of
  node->height=1+max(lheight,rhieght);          //node.
  return node->height;
}

bool AVLTree::rotateLeftLeft(TreeNode *currNode, TreeNode *parentNode, TreeNode *grandParentNode)
{

  TreeNode *greatGrandParentNode = grandParentNode->parent;
  
  // First find if grandParentNode is the left or right child of
  // greatGrandParentNode. If imbalance is at root then greatgrandparent can be null
  //so first if greatgrandparent is not null then-
  bool isGPLeftChild=true;                    //set default value to true to use if greatgrandparent is null.
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
  updateAVLParentChild(parentNode, greatGrandParentNode, isGPLeftChild);
  
  //making current node child of parentnode 
  //here true implies currnode will be left of parentnode
  updateAVLParentChild(currNode, parentNode, true);
  
  // Making grandParentNode the right child of
  // parentNode. The last parameter is "false" to indicate that grandParentNode
  // should be made the right child of parentNode
  //but first we will store the right subtree of parentnode in a variable so that 
  //while grandparentnode child of parent node information does not lost.
  // Let T3 be the right child of parentNode
  TreeNode *T3 = parentNode->right;
  updateAVLParentChild(grandParentNode, parentNode, false);

  // We use "true" as the third argument of the following call to indicate
  // that T3 should become the left child of grandParentNode
  updateAVLParentChild(T3, grandParentNode, true);

  //now update heights of nodes of subtree rooted on parentnode cause now it became 
  //highest node after rotation.
  parentNode->height=updateAVLHeight(parentNode);

  //checking if root is also involved in rotation then updating new root
  if(greatGrandParentNode==nullptr)root=parentNode;

  return true;
}

bool AVLTree::rotateLeftRight(TreeNode *currNode, TreeNode *parentNode, TreeNode *grandParentNode)
{
  TreeNode *greatGrandParentNode = grandParentNode->parent;
  
  // First find if grandParentNode is the left or right child of
  // greatGrandParentNode. If imbalance is at root then greatgrandparent can be null
  //so first if greatgrandparent is not null then-
  bool isGPLeftChild=true;              //set default value to true to use if greatgrandparent is null.
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
  updateAVLParentChild(currNode, greatGrandParentNode, isGPLeftChild);
  // Make parentNode the left child of
  // currNode The last parameter is "true" to indicate that parentNode should be
  // made the left child of currNode

  // Let T2 be the left child of currNode (i.e. of x)
  TreeNode *T2 = currNode->left;
  
  // Let T3 be the right child of currNode (i.e. of x)
  TreeNode *T3 = currNode->right;

  updateAVLParentChild(parentNode, currNode, true);
  
  // Make grandParentNode the right child of
  // currNode The last parameter is "false" to indicate that grandParentNode
  // should NOT be made the left child of currNode
  updateAVLParentChild(grandParentNode, currNode, false);
       
  // We use "false" as the third argument of the following call to indicate
  // that T2 should NOT become the left child of ParentNode
  updateAVLParentChild(T2, parentNode, false);

  // We use "true" as the third argument of the following call to indicate
  // that T3 should become the left child of grandParentNode
  updateAVLParentChild(T3, grandParentNode, true);

  //now update heights of nodes of subtree rooted on parentnode cause now it became 
  //highest node after rotation.
  currNode->height=updateAVLHeight(currNode);

  //checking if root is also involved in rotation then updating new root
  if(greatGrandParentNode==nullptr)root=currNode;

  return true;
}

bool AVLTree::rotateRightLeft(TreeNode *currNode, TreeNode *parent, TreeNode *grandParent)
{
  TreeNode *greatGrandParentNode = grandParent->parent;
  
  // First find if grandParentNode is the left or right child of
  // greatGrandParentNode
  //so first if greatgrandparent is not null then-
  bool isGPLeftChild=true;              //set default value to true to use if greatgrandparent is null.
  if(greatGrandParentNode!=nullptr){
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
  }
  
  updateAVLParentChild(currNode, greatGrandParentNode, isGPLeftChild);

  // Let T2 be the left child of currNode (i.e. of x)
  TreeNode *T2 = currNode->left;
  
  // Let T3 be the right child of currNode (i.e. of x)
  TreeNode *T3 = currNode->right;

  // Make parentNode the left child of
  // currNode The last parameter is "true" to indicate that parentNode should be
  // made the left child of currNode
  updateAVLParentChild(parent, currNode, false);
  
  // Make grandParentNode the right child of currNode
  // The last parameter is "false" to indicate that grandParentNode
  // should NOT be made the left child of currNode
  updateAVLParentChild(grandParent, currNode, true);

  // We use "false" as the third argument of the following call to indicate
  // that T2 should NOT become the left child of ParentNode
  updateAVLParentChild(T2, grandParent, false);

  // We use "true" as the third argument of the following call to indicate
  // that T3 should become the left child of grandParentNode
  updateAVLParentChild(T3, parent, true);

  //now update heights of nodes of subtree rooted on parentnode cause now it became 
  //highest node after rotation.
  currNode->height=updateAVLHeight(currNode);

  //checking if root is also involved in rotation then updating new root
  if(greatGrandParentNode==nullptr)root=currNode;

  return true;
}

bool AVLTree::rotateRightRight(TreeNode *currNode, TreeNode *parent, TreeNode *grandParent)
{
  TreeNode *greatGrandParentNode = grandParent->parent;
  
  // First find if grandParentNode is the left or right child of
  // greatGrandParentNode
  //so first if greatgrandparent is not null then-
  bool isGPLeftChild=true;              //set default value to true to use if greatgrandparent is null.
  if(greatGrandParentNode!=nullptr){
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
  }
  updateAVLParentChild(parent, greatGrandParentNode, isGPLeftChild);

  // Make currNode the left child of parentNode
  // The last parameter is "true" to indicate that currNode should be
  // made the left child of parentNode
  updateAVLParentChild(currNode, parent, false);
  
  // Let T3 be the right child of parentNode 
  TreeNode *T3 = parent->left;

  // Make grandParentNode the right child of parentNode
  // The last parameter is "false" to indicate that grandParentNode
  // should NOT be made the left child of parentNode
  updateAVLParentChild(grandParent, parent, true);

  // We use "true" as the third argument of the following call to indicate
  // that T3 should become the left child of grandParentNode
  updateAVLParentChild(T3, grandParent, false);

  //now update heights of nodes of subtree rooted on parentnode cause now it became 
  //highest node after rotation.
  parent->height=updateAVLHeight(parent);
  //checking if root is also involved in rotation then updating new root
  if(greatGrandParentNode==nullptr)root=parent;

  return true;
}

//returns 0 if node is null else returns height of that node. 
int height(TreeNode* node){
  if(node==nullptr)return 0;
  else return node->height;
}

// Returns true on successful insertion in AVL tree. Returns false otherwise.
// You may assume that no two elements being inserted have the same journey
// code, and journey code is the key for insertion and finding in the AVL
// tree.
bool AVLTree::insert(int jrnyCode, int price)
{
  TreeNode *newnode=new TreeNode(jrnyCode,price);
  if(root==nullptr){
    root=newnode;
    return true;
  }
  struct TreeNode *currNode = root, *parentOfCurrNode = nullptr;
  while (currNode != nullptr) {
    if (AVLLessThan(currNode,newnode)) {
      parentOfCurrNode = currNode;
      currNode = currNode->right;
    }
    else if (AVLLessThan(newnode,currNode)) {
      parentOfCurrNode = currNode;
      currNode = currNode->left;
    }
    else { // currNode->JourneyCode == JourneyCode
      return false;
    }
  }
  
  if(parentOfCurrNode==nullptr)root=newnode;
  else if(AVLLessThan(newnode,parentOfCurrNode))updateAVLParentChild(newnode,parentOfCurrNode,true);
  else updateAVLParentChild(newnode,parentOfCurrNode,false);

  //updating height of root and it's subtree where new node is added
  bool  isleft;
  if(AVLLessThan(newnode,root)){
    root->height=1+max(updateAVLHeight(root->left),height(root->right));
    isleft=true;
  }
  else {
    root->height=1+max(updateAVLHeight(root->right),height(root->left));
    isleft=false;
  }

  //now checking node which is imbalanced
  TreeNode* node=newnode;
  int balance;
  do{
    node=node->parent;
    int lheight=height(node->left);
    int rheight=height(node->right);
    balance=lheight-rheight;
    if(abs(balance)>1)break;
  }while(node!=root);

  // now rotating imbalanced tree by checking cases
  if(balance >1 && AVLLessThan(newnode,node->left))rotateLeftLeft(node->left->left,node->left,node);
  else if(balance <-1 && AVLLessThan(node->right,newnode)) rotateRightRight(node->right->right,node->right,node);
  else if(balance <-1 && AVLLessThan(newnode,node->right)) rotateRightLeft(node->right->left,node->right,node);
  else if(balance >1 && AVLLessThan(node->left,newnode)) rotateLeftRight(node->left->right,node->left,node);
  
  if(isleft){
    root->height=1+max(updateAVLHeight(root->left),height(root->right));
  }
  else {
    root->height=1+max(updateAVLHeight(root->right),height(root->left));
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
  TreeNode* temp=new TreeNode(jrnyCode,0);
  TreeNode *x =root;
    while(x!=NULL){
      if(AVLLessThan(temp,x)) x=x->left;
      else if(AVLLessThan(x,temp))x=x->right;
      else return x->getPrice();
    }
  return -1;
}

// =====================================================
// OPTIONAL: Implement "remove" only for bonus marks
// =====================================================

//balances subtree rooted on given node
void AVLTree::balanceTree(TreeNode* node){
  if(node==nullptr)return;
  int lheight=height(node->left);
  int rheight=height(node->right);
  int balance=lheight-rheight;            //checks of imbalance of node

  balanceTree(node->left);                //first balances left subtree 
  balanceTree(node->right);               //balances right subtree

  // now rotating imbalanced tree by checking cases
  if(balance >1 && (height(node->left->left)-height(node->left->right))>=0){
    rotateLeftLeft(node->left->left,node->left,node);
  }
  else if(balance <-1 && (height(node->right->left)-height(node->right->right))<=0){
    rotateRightRight(node->right->right,node->right,node);
  }
  else if(balance <-1 && (height(node->right->left)-height(node->right->right))>0){
    rotateRightLeft(node->right->left,node->right,node);
  }
  else if(balance >1 && (height(node->left->left)-height(node->left->right))<0){
    rotateLeftRight(node->left->right,node->left,node);
  }
}

// Returns true on successful deletion of the entry in AVL tree with
// matching journey code. Returns false if it cannot find any such element.
//
// You may assume that no two elements in the AVL tree have the same journey
// code, and journey code is the key for insertion and finding in the AVL
// tree.

bool AVLTree::remove(int jrnyCode)
{
  TreeNode* z=getNode(jrnyCode);
  if(z==NULL)return false;
  TreeNode* y,*x;
  if(z->left==NULL || z->right==NULL)y=z;
  else y=successor(z);
  TreeNode* p=y->parent;
  if(y->left!=NULL)x=y->left;
  else x=y->right;
  if(x!=NULL)x->parent=y->parent;
  if(y->parent==NULL)root=x;
  else if(y==y->parent->left)y->parent->left=x;
  else y->parent->right=x;
  TreeNode* newnode=new TreeNode(jrnyCode,0);
  if(y!=z){
    z->changeData(y);
  }
  //updating heights
  if(root!=nullptr)root->height=updateAVLHeight(root);
  //balancing tree
  balanceTree(root);
  return true;
}


