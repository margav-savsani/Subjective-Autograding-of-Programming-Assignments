#ifndef AVL_H
#include "AVL.h"
#endif

#ifndef STD_HEADERS
#include <iostream>
#include <stdlib.h>
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
  // cout<<"Entered Left Left Rotation\n";
  // Going back to Prof. Naveen Garg's lecture, x is *currNode,
  // y is *parentNode and z is *grandParentNode

  // Moreover, currNode is the left child of parentNode, and
  // parentNode is the left child of grandParentNode
  // That's why we are doing a rotateLeftLeft

  TreeNode *greatGrandParentNode = grandParentNode->parent;
  // cout<<"Assigned ggp node\n";
  bool flag=1;
  if (greatGrandParentNode==NULL) {flag=0;}
  // cout<<"ggp is null\n";
  // else {cout<<"ggp node is not null\n";}
  // First find if grandParentNode is the left or right child of
  // greatGrandParentNode
  
  bool isGPLeftChild;
  if(flag){
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
  if(flag){
  updateAVLParentChild(parentNode, greatGrandParentNode, isGPLeftChild);}
  else{root=parentNode;root->parent=NULL;}

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
  TreeNode *T1=currNode->left,*T2=currNode->right,*T4=grandParentNode->right;
  int T1height,T2height,T3height,T4height;
  if(T1!=NULL){T1height=T1->height;}else{T1height=-1;}
  if(T2!=NULL){T2height=T2->height;}else{T2height=-1;}
  if(T3!=NULL){T3height=T3->height;}else{T3height=-1;}
  if(T4!=NULL){T4height=T4->height;}else{T4height=-1;}
  // int h=min(min(min(T1height,T2height),T3height),T4height);
  int h=max(max(max(T1height,T2height),T3height),T4height);
  currNode->height=h+1;
  grandParentNode->height=h+1;
  parentNode->height=h+2;
  // cout<<"Left Left Rotation Done"<<endl;
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
  bool flag=1;
  if (greatGrandParentNode==NULL) {flag=0;}
  // First find if grandParentNode is the left or right child of
  // greatGrandParentNode

  bool isGPLeftChild;
  if(flag){
  if (greatGrandParentNode->left == grandParentNode) {
    isGPLeftChild = true;
  }
  else if (greatGrandParentNode->right == grandParentNode) {
    isGPLeftChild = false;
  }
  else {
    cerr << "Unexpected condition encountered!" << endl;
    return false;
  }}

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
  if(flag){
  updateAVLParentChild(currNode, greatGrandParentNode, isGPLeftChild);}
  else{root=currNode;root->parent=NULL;}

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

  TreeNode *T1=parentNode->left,*T4=grandParentNode->right;
  int T1height,T2height,T3height,T4height;
  if(T1!=NULL){T1height=T1->height;}else{T1height=-1;}
  if(T2!=NULL){T2height=T2->height;}else{T2height=-1;}
  if(T3!=NULL){T3height=T3->height;}else{T3height=-1;}
  if(T4!=NULL){T4height=T4->height;}else{T4height=-1;}
  // int h=min(min(min(T1height,T2height),T3height),T4height);
  int h=max(max(max(T1height,T2height),T3height),T4height);
  currNode->height=h+2;
  parentNode->height=h+1;
  grandParentNode->height=h+1;

  return true;
}

bool AVLTree::rotateRightLeft(TreeNode *currNode, TreeNode *parentNode, TreeNode *grandParentNode)
{
  // Implement this yourself
  TreeNode *greatGrandParentNode=grandParentNode->parent;
  bool flag=1;
  if (greatGrandParentNode==NULL) {flag=0;}

  bool isGPLeftChild;
  if(flag){
  if (greatGrandParentNode->left == grandParentNode) {
    isGPLeftChild = true;
  }
  else if (greatGrandParentNode->right == grandParentNode) {
    isGPLeftChild = false;
  }
  else {
    cerr << "Unexpected condition encountered!" << endl;
    return false;
  }}

  TreeNode *T2=currNode->right,*T1=currNode->left,*T3=parentNode->right,*T4=grandParentNode->left;
  if(flag){
  updateAVLParentChild(currNode,greatGrandParentNode,isGPLeftChild);}
  else{root=currNode;root->parent=NULL;}

  updateAVLParentChild(grandParentNode,currNode,true);

  updateAVLParentChild(parentNode,currNode,false);

  updateAVLParentChild(T2,parentNode,true);

  updateAVLParentChild(T1,grandParentNode,false);

  int T1height,T2height,T3height,T4height;
  if(T1!=NULL){T1height=T1->height;}else{T1height=-1;}
  if(T2!=NULL){T2height=T2->height;}else{T2height=-1;}
  if(T3!=NULL){T3height=T3->height;}else{T3height=-1;}
  if(T4!=NULL){T4height=T4->height;}else{T4height=-1;}
  // int h=min(min(min(T1height,T2height),T3height),T4height);
  int h=max(max(max(T1height,T2height),T3height),T4height);
  currNode->height=h+2;
  parentNode->height=h+1;
  grandParentNode->height=h+1;

  return true;
}

bool AVLTree::rotateRightRight(TreeNode *currNode, TreeNode *parentNode, TreeNode *grandParentNode)
{
  // Implement this yourself
  TreeNode* greatGrandParentNode=grandParentNode->parent;
  bool flag=1;
  if (greatGrandParentNode==NULL) {flag=0;}

  bool isLeftChild;
  if(flag){
  if(greatGrandParentNode->left==grandParentNode){isLeftChild=true;}
  else if (greatGrandParentNode->right==grandParentNode){isLeftChild=false;}
  else {
    cerr << "Unexpected condition encountered!" << endl;
    return false;
  }}

  TreeNode* T3=parentNode->left;
  if(flag){
  updateAVLParentChild(parentNode,greatGrandParentNode,isLeftChild);}
  else{root=parentNode;root->parent=NULL;}

  updateAVLParentChild(grandParentNode,parentNode,true);

  updateAVLParentChild(T3,grandParentNode,false);

  updateAVLParentChild(currNode,parentNode,false);

  TreeNode *T1=currNode->left,*T2=currNode->right,*T4=grandParentNode->left;
  int T1height,T2height,T3height,T4height;
  if(T1!=NULL){T1height=T1->height;}else{T1height=-1;}
  if(T2!=NULL){T2height=T2->height;}else{T2height=-1;}
  if(T3!=NULL){T3height=T3->height;}else{T3height=-1;}
  if(T4!=NULL){T4height=T4->height;}else{T4height=-1;}
  // int h=min(min(min(T1height,T2height),T3height),T4height);
  int h=max(max(max(T1height,T2height),T3height),T4height);
  currNode->height=h+1;
  grandParentNode->height=h+1;
  parentNode->height=h+2;
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
  TreeNode* newnode;
  newnode=new TreeNode(jrnyCode,price);

  TreeNode *y=NULL;
  TreeNode *x=root;
  while(x!=NULL){
    y=x;
    if(AVLLessThan(newnode,x)){
      x=x->left;
    }
    else{x=x->right;}
  }
  if(y==NULL){
    root=newnode;
  }
  else if(AVLLessThan(newnode,y)){
    updateAVLParentChild(newnode,y,true);
  }
  else {
    updateAVLParentChild(newnode,y,false);
  }

  // print();
  // int junk;cin>>junk;

  TreeNode* node=newnode->parent;
  // TreeNode *currNode=newnode,*parentNode=newnode->parent,*grandParentNode;
  // if(node!=NULL){grandParentNode=newnode->parent->parent;}
  TreeNode *currNode,*parentNode,*grandParentNode;
  grandParentNode=node;
  parentNode=newnode;
  currNode=NULL;
  while(node!=NULL){

    if(node->left==NULL&&node->right!=NULL){node->height=1+node->right->height;}
    else if (node->right==NULL&&node->left!=NULL){node->height=1+node->left->height;}
    else {node->height=1+max(node->left->height,node->right->height);}

    int leftheight,rightheight;
    if(grandParentNode->left==nullptr){leftheight=-1;} else {leftheight=grandParentNode->left->height;}
    if(grandParentNode->right==nullptr){rightheight=-1;} else {rightheight=grandParentNode->right->height;}    
    if(abs(rightheight-leftheight)>1){
      // cout<<"abs(rightheight-leftheight)="<<abs(rightheight-leftheight)<<endl;
      if(parentNode==grandParentNode->left){
        if(currNode==parentNode->left){
          // cout<<"Rotating Left Left\n";
          rotateLeftLeft(currNode,parentNode,grandParentNode);
          break;  // print();
  // int junk;cin>>junk;
        }
        else{
          // cout<<"Rotating Left Right\n";
          rotateLeftRight(currNode,parentNode,grandParentNode);break;
        }
      }
      else{
        if(currNode==parentNode->left){
          // cout<<"Rotating Right Left\n";
          rotateRightLeft(currNode,parentNode,grandParentNode);break;
        }
        else{
          // cout<<"Rotating Right Right\n";
          rotateRightRight(currNode,parentNode,grandParentNode);break;
        }
      }
    }
    

    currNode=parentNode;parentNode=node;grandParentNode=node->parent;
    node=node->parent;
    // cout<<"grandParentNode: ";if(grandParentNode!=NULL){grandParentNode->printInfo();}else {cout<<"null";}cout<<endl;
    // cout<<"parentNode: ";if(parentNode!=NULL){parentNode->printInfo();}else {cout<<"null";}cout<<endl;
    // cout<<"currNode: ";if(currNode!=NULL){currNode->printInfo();}else {cout<<"null";}cout<<endl;
  }
  // print();
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
  TreeNode* newnode;
  newnode=new TreeNode(jrnyCode,71);
  TreeNode* node=root;
  while(node!=NULL){
    if(AVLLessThan(newnode,node)){node=node->left;}
    else if(AVLLessThan(node,newnode)){node=node->right;}
    else{return 1;}
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

  bool found=false;
  TreeNode *node=root;
  TreeNode *temp;temp=new TreeNode(jrnyCode,31);
   // TreeNode *temproot=root;
  while(node!=NULL){
    if(AVLLessThan(node,temp)) node=node->right;
    else if(AVLLessThan(temp,node)) node=node->left;
    else {found=true;break;}
  }
  delete temp;
  if(!found){return false;}
  TreeNode *y,*x,*z,*w;
  if(node->left==NULL || node->right==NULL)
  {
    y=node;
  }
  else{
      y=treePred(node);
  }
  z=y->parent;
  if(y->left!=NULL){
      x=y->left;
  }
  else{
      x=y->right;
  }
  if(x!=NULL){
      x->parent=y->parent;
  }
  w=x;
  if(y->parent==NULL){
      root=x;
  }
  else if(y==y->parent->left){
      y->parent->left=x;
  }
  else{
      y->parent->right=x;
  }
  if (y!=node){
      node->updateValues(y->getJrnyCode(),y->getPrice());
  }
  // return true;



  // TreeNode* node=newnode->parent;
  // TreeNode *currNode=newnode,*parentNode=newnode->parent,*grandParentNode;
  // if(node!=NULL){grandParentNode=newnode->parent->parent;}
  // TreeNode *currNode,*parentNode,*grandParentNode;
  // grandParentNode=z;
  // parentNode=w;
  // currNode=NULL;



  while(z!=NULL){
    if(z->left==NULL&&z->right!=NULL){z->height=1+z->right->height;}
    else if (z->right==NULL&&z->left!=NULL){z->height=1+z->left->height;}
    else if (z->left==NULL && z->right==NULL){z->height=0;}
    else {z->height=1+max(z->left->height,z->right->height);}

    int leftheight,rightheight;
    if(z->left==nullptr){leftheight=-1;} else {leftheight=z->left->height;}
    if(z->right==nullptr){rightheight=-1;} else {rightheight=z->right->height;}    
    if(abs(rightheight-leftheight)>1){
      // cout<<"abs(rightheight-leftheight)="<<abs(rightheight-leftheight)<<endl;

      TreeNode* parentNode,*currNode,*grandParentNode;
      grandParentNode=z;

      if(leftheight>=rightheight){parentNode=grandParentNode->left;} else parentNode=grandParentNode->right;


      int lht,rht;
      if(parentNode->left==nullptr){lht=-1;} else {lht=parentNode->left->height;}
      if(parentNode->right==nullptr){rht=-1;} else {rht=parentNode->right->height;}  
      if(lht>=rht){currNode=parentNode->left;} else currNode=parentNode->right;



      if(parentNode==grandParentNode->left){
        if(currNode==parentNode->left){
          // cout<<"Rotating Left Left\n";
          rotateLeftLeft(currNode,parentNode,grandParentNode);
          // break;  // print();
  // int junk;cin>>junk;
        }
        else{
          // cout<<"Rotating Left Right\n";
          rotateLeftRight(currNode,parentNode,grandParentNode);
          // break;
        }
      }
      else{
        if(currNode==parentNode->left){
          // cout<<"Rotating Right Left\n";
          rotateRightLeft(currNode,parentNode,grandParentNode);
          // break;
        }
        else{
          // cout<<"Rotating Right Right\n";
          rotateRightRight(currNode,parentNode,grandParentNode);
          // break;
        }
      }
    }






  //   int leftheight,rightheight;
  //   if(grandParentNode->left==nullptr){leftheight=-1;} else {leftheight=grandParentNode->left->height;}
  //   if(grandParentNode->right==nullptr){rightheight=-1;} else {rightheight=grandParentNode->right->height;}    
  //   if(abs(rightheight-leftheight)>1){
  //     // cout<<"abs(rightheight-leftheight)="<<abs(rightheight-leftheight)<<endl;
  //     if(parentNode==grandParentNode->left){
  //       if(currNode==parentNode->left){
  //         // cout<<"Rotating Left Left\n";
  //         rotateLeftLeft(currNode,parentNode,grandParentNode);
  //         break;  // print();
  // // int junk;cin>>junk;
  //       }
  //       else{
  //         // cout<<"Rotating Left Right\n";
  //         rotateLeftRight(currNode,parentNode,grandParentNode);break;
  //       }
  //     }
  //     else{
  //       if(currNode==parentNode->left){
  //         // cout<<"Rotating Right Left\n";
  //         rotateRightLeft(currNode,parentNode,grandParentNode);break;
  //       }
  //       else{
  //         // cout<<"Rotating Right Right\n";
  //         rotateRightRight(currNode,parentNode,grandParentNode);break;
  //       }
  //     }
  //   }
    

    // currNode=parentNode;parentNode=z;grandParentNode=z->parent;
    z=z->parent;







    // z=z->parent;
  }

  return true;
}

TreeNode* AVLTree::treePred(TreeNode *node){
    TreeNode *pred=node->left;
    while(pred->right!=NULL){
        pred=pred->right;
    }
    return pred;
}


