
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
//   y                             parent
//   z                             grandParent
//
// Recall also that z (grandParent) is the lowest node in the path from
// the root to the inserted node or to the deleted node (as the case may be)
// where the balance factor has either become < -1 or > 1.
// To find what x (currNode) and y (parent) should be, you need to
// recall Prof. Garg's lectures.
// These are slightly differently defined when inserting nodes and when
// deleting nodes

bool AVLTree::rotateLeftLeft(TreeNode *currNode, TreeNode *parent, TreeNode *grandParent)
{
  // Going back to Prof. Naveen Garg's lecture, x is *currNode,
  // y is *parent and z is *grandParent

  // Moreover, currNode is the left child of parent, and
  // parent is the left child of grandParent
  // That's why we are doing a rotateLeftLeft

  TreeNode *greatgrandParent = grandParent->parent;
  
  // First find if grandParent is the left or right child of
  // greatgrandParent
  
  bool isGPLeftChild;
  if(greatgrandParent==NULL) isGPLeftChild=true;
   else { if (greatgrandParent->left == grandParent) {
      isGPLeftChild = true;
    }
    else if (greatgrandParent->right == grandParent) {
      isGPLeftChild = false;
    }
    else {
      cerr << "Unexpected condition encountered!" << endl;
      return false;
    }
  
}

  // Let T3 be the right child of parent (i.e. of y, using notation
  // from Prof. Garg's lectures
  TreeNode *T3 = parent->right;

  // Now replicate the single rotation for LeftLeft as from the lecture
  // notes/video using *ONLY* calls to updateAVLParentChild

  // Make parent (y in Prof. Naveen Garg's lectures) the appropriate
  // child of greatgrandParent
  updateAVLParentChild(parent, greatgrandParent, isGPLeftChild);
  
  // Make currNode (x in Prof. Garg's lectures) the left child of
  // parent (y in Prof. Garg's lectures)
  // The last parameter is "true" to indicate that currNode should be
  // made the left child of parent
  updateAVLParentChild(currNode, parent, true);
  
  // Make grandParent (z in Prof. Garg's lectures) the right child of
  // parent (y in Prof. Garg's lectures)
  // The last parameter is "false" to indicate that grandParent
  // should NOT be made the left child of parent
  updateAVLParentChild(grandParent, parent, false);
  
  // Recall from Prof. Garg's lectures that the left and right subtrees
  // of currNode (i.e. x in Prof. Garg's lectures) stay unchanged after
  // the LeftLeft rotation.  So do don't need to update the children of
  // currNode at all.
  // Similarly, the right subtree of grandParent (i.e. z in Prof.
  // Garg's lectures) stays unchanged.  Hence, the right child of
  // grandParent doesn't need to be updated at all.
  // The only update needed is that the right subtree of parent (i.e.
  // y in Prof. Garg's notes) should now become the left
  // child of grandParent (i.e. of z in Prof. Garg's notes).

  // We use "true" as the third argument of the following call to indicate
  // that T3 should become the left child of grandParent
  updateAVLParentChild(T3, grandParent, true);
  grandParent->height=parent->height-1;
  while(parent->parent!=NULL){
      parent->parent->height=parent->parent->height-1;
      parent = parent->parent;
  }
  if(greatgrandParent==NULL){root=parent;}
  return true;
}

bool AVLTree::rotateLeftRight(TreeNode *currNode, TreeNode *parent, TreeNode *grandParent)
{
  // Going back to Prof. Naveen Garg's lecture, x is *currNode,
  // y is *parent and z is *grandParent

  // Moreover, currNode is the right child of parent, and
  // parent is the left child of grandParent.  That's
  // why we are doing a rotateLeftRight

  TreeNode *greatgrandParent = grandParent->parent;
  
  // First find if grandParent is the left or right child of
  // greatgrandParent

  bool isGPLeftChild;
  if(greatgrandParent==NULL) isGPLeftChild=true;
    else{if (greatgrandParent->left == grandParent) {
      isGPLeftChild = true;
    }
    else if (greatgrandParent->right == grandParent) {
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
  // child of greatgrandParent
  updateAVLParentChild(currNode, greatgrandParent, isGPLeftChild);
  
  // Make parent (y in Prof. Garg's lectures) the left child of
  // currNode (x in Prof. Garg's lectures)
  // The last parameter is "true" to indicate that parent should be
  // made the left child of currNode
  updateAVLParentChild(parent, currNode, true);

  // Make grandParent (z in Prof. Garg's lectures) the right child of
  // currNode (x in Prof. Garg's lectures)
  // The last parameter is "false" to indicate that grandParent
  // should NOT be made the left child of currNode
  updateAVLParentChild(grandParent, currNode, false);
  
  
  // Recall from Prof. Garg's lectures that the left subtree of 
  // parent (i.e. y in Prof. Garg's lectures) and right subtree of
  // grandParent (i.e. z in Prof. Garg's lectures) stay unchanged
  // after the LeftRight rotation.  So do don't need to update the
  // left child of parent and the right child of grandParent
  // at all.
  // The only update needed is that the left subtree of currNode (i.e.
  // x in Prof. Garg's notes) should now become the right subtree of
  // parent (y in Prof. Garg's notes).  Similarly, the right subtree
  // of currNode (i.e. of x) should now become the left subtree of
  // grandParent (i.e. of z).
       
  // Let's implement these updations below.
       
  // We use "false" as the third argument of the following call to indicate
  // that T2 should NOT become the left child of parent
  updateAVLParentChild(T2, parent, false);
  
  // We use "true" as the third argument of the following call to indicate
  // that T3 should become the left child of grandParent
  updateAVLParentChild(T3, grandParent, true);
  currNode->height=currNode->height+1;
  parent->height=parent->height-1;
  grandParent->height=grandParent->height-2;
  while((currNode->parent)!=NULL){
      (currNode->parent)->height=(currNode->parent)->height-1;
      currNode = (currNode->parent);
  }
  if(greatgrandParent==NULL){root=currNode;}
  return true;
}

bool AVLTree::rotateRightLeft(TreeNode *currNode, TreeNode *parent, TreeNode *grandParent){
  TreeNode *greatgrandParent = grandParent->parent;
  bool isGPLeftChild;
  if(greatgrandParent==NULL) isGPLeftChild=true;
    else{if (greatgrandParent->left == grandParent) {
      isGPLeftChild = true;
    }
    else if (greatgrandParent->right == grandParent) {
      isGPLeftChild = false;
    }
    else {
      cerr << "Unexpected condition encountered!" << endl;
      return false;
    }
  }
  
  TreeNode *T2 = currNode->left;
  TreeNode *T3 = currNode->right;
  updateAVLParentChild(currNode, greatgrandParent, isGPLeftChild);
  updateAVLParentChild(parent, currNode, false);
  updateAVLParentChild(grandParent, currNode, true);
  updateAVLParentChild(T2, parent, true);
  updateAVLParentChild(T3, grandParent,false);
  currNode->height=currNode->height+1;
  parent->height=parent->height-1;
  grandParent->height=grandParent->height-2;
  while((currNode->parent)!=NULL){
      (currNode->parent)->height=(currNode->parent)->height-1;
      currNode = (currNode->parent);
  }
  if(greatgrandParent==NULL){root=currNode;}
  return true;
}

bool AVLTree::rotateRightRight(TreeNode *currNode, TreeNode *parent, TreeNode *grandParent)
{
  //cout<<"rightright"<<endl;
  TreeNode *greatgrandParent = grandParent->parent;
  
  bool isGPLeftChild;
  if(greatgrandParent==NULL) isGPLeftChild=true;
  else{  if (greatgrandParent->left == grandParent) {
      isGPLeftChild = true;
    }
    else if (greatgrandParent->right == grandParent) {
      isGPLeftChild = false;
    }
    else {
      cerr << "Unexpected condition encountered!" << endl;
      return false;
    }
}
  
  TreeNode *T3 = parent->left;

  updateAVLParentChild(parent, greatgrandParent, isGPLeftChild);
  
  updateAVLParentChild(currNode, parent, false);
  
  updateAVLParentChild(grandParent, parent, true);
  
  updateAVLParentChild(T3, grandParent, false);
  grandParent->height=parent->height-1;
  while(parent->parent!=NULL){
      parent->parent->height=parent->parent->height-1;
      parent = parent->parent;
  }
  if(greatgrandParent==NULL){root=parent;}
  return true;
}

// Returns true on successful insertion in AVL tree. Returns false otherwise.
// You may assume that no two elements being inserted have the same journey
// code, and journey code is the key for insertion and finding in the AVL
// tree.



//void AVLTree::setup(TreeNode * y){
//}
int AVLTree::balancefactor(TreeNode * N){
  if(N->left==NULL && N->right==NULL){return 0;}
  else if(N->right==NULL){return N->left->height+1;}
  else if(N->left==NULL){return N->right->height+1;}
  else{return N->left->height - N->right->height;}
}

bool AVLTree::insert(int jrnyCode, int price){
  TreeNode * x=root;
  TreeNode * y=nullptr;
  TreeNode * z=new TreeNode(jrnyCode,price);
  TreeNode * K;
 // cout<<"welcome"<<endl;
  if(root==nullptr){root=z; return true;}
//  cout<<"crossed welcome"<<endl;
  while(x!=nullptr){
    y=x;
    if(AVLLessThan(z,x)){x=x->left;}
    else {x=x->right;}
  }

  z->parent=y;
  K=z;
  if(y==nullptr){root=z;}
  else if(AVLLessThan(z,y)){y->left=z;}
  else{y->right=z;}
 // cout<<"inserted"<<endl;
  while(z->parent!=nullptr && z->parent->height < z->height +1 ){
    z->parent->height=z->height+1;
    z=z->parent;
  }
  //cout<<"height calculated"<<endl;
  //TreeNode *l=nullptr;
  TreeNode *kp=K->parent;
  TreeNode *currentnode=nullptr;
  TreeNode *parentnode=nullptr;
  TreeNode *grandparentnode=nullptr;
  while(K->parent!=nullptr){
    if(kp->parent==nullptr){return true;}
    else{
      //cout<<"hello1"<<endl;
     // cout<<balancefactor(kp->parent)<<endl;
      if(!(balancefactor(kp->parent)==0 || balancefactor(kp->parent)==-1 || balancefactor(kp->parent)==1)){
       // cout<<"jhvgy"<<endl;
        currentnode=K;
        parentnode=kp;
        grandparentnode=kp->parent;
        break;
      }
    }
    K=K->parent;
    kp=K->parent;
  }
 // cout<<currentnode->getprice()<<"cn"<<endl;
 // cout<<parentnode->getprice()<<"pn"<<endl;
 // cout<<grandparentnode->getprice()<<"gpn"<<endl;
  if(grandparentnode->right==parentnode && parentnode->right==currentnode){
   // cout<<"cfjhybc"<<endl;
   return rotateRightRight(currentnode, parentnode, grandparentnode);
    
  }
  else if(grandparentnode->right==parentnode && parentnode->left==currentnode){
    return rotateRightLeft(currentnode, parentnode, grandparentnode);
  }
  else if(grandparentnode->left==parentnode && parentnode->left==currentnode){
    return rotateLeftLeft(currentnode, parentnode, grandparentnode);
    
  }
  else if(grandparentnode->left==parentnode && parentnode->right==currentnode){
    return rotateLeftRight(currentnode, parentnode, grandparentnode);
    }
  return true;
}
    
   
  // Implement insertion in AVL tree followed by balance factor restoration
  // by properly identifying x, y, z as used in Prof. Garg's lectures
  // (equivalently, currNode, parent, grandParent in our code) and
  // invoking rotateLeftLeft, rotateLeftRight, rotateRightLeft and/or
  // rotateRightRight as appropriate.

  // It is your responsibility to find out the right x, y, z (or currNode,
  // parent, grandParent) following Prof. Garg's lectures
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
  


// Returns the price on finding an element in the AVL tree that matches
// journey code. Returns -1 otherwise.
// You may assume that no two node in the tree have the same journey
// code, and journey code is the key for insertion and finding in the AVL
// tree.

int AVLTree::find(int jrnyCode)
{
  TreeNode * z=new TreeNode(jrnyCode,0);
  TreeNode * s;
    s=root;
    while(s!=NULL){
        if(AVLLessThan(z,s)){
          s=s->left;
        }
        else if(AVLLessThan(s,z)){
          s=s->right;
        }
        else{
            return s->getprice();
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
  // (equivalently, currNode, parent, grandParent in our code) and
  // invoking rotateLeftLeft, rotateLeftRight, rotateRightLeft and/or
  // rotateRightRight as appropriate.

  // It is your responsibility to find out the right x, y, z (or currNode,
  // parent, grandParent) following Prof. Garg's lectures
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


