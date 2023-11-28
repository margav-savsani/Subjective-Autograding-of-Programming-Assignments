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

bool AVLTree::rotateLeftLeft(TreeNode *currNode, TreeNode *parent, TreeNode *grandParent)
{
  // Going back to Prof. Naveen Garg's lecture, x is *currNode,
  // y is *parentNode and z is *grandParentNode

  // Moreover, currNode is the left child of parentNode, and
  // parentNode is the left child of grandParentNode
  // That's why we are doing a rotateLeftLeft

  TreeNode *greatGrandParentNode = grandParent->parent;
  
  // First find if grandParentNode is the left or right child of
  // greatGrandParentNode
  bool isGPLeftChild=true;
  if(greatGrandParentNode!=NULL){
           
  if (greatGrandParentNode->left == grandParent) {
    isGPLeftChild = true;
  }
  else if (greatGrandParentNode->right == grandParent) {
    isGPLeftChild = false;
  }
  else {
    cerr << "Unexpected condition encountered!" << endl;
    return false;
  }}
  // Let T3 be the right child of parentNode (i.e. of y, using notation
  // from Prof. Garg's lectures
  TreeNode *T3 = parent->right;

  // Now replicate the single rotation for LeftLeft as from the lecture
  // notes/video using *ONLY* calls to updateAVLParentChild

  // Make parentNode (y in Prof. Naveen Garg's lectures) the appropriate
  // child of greatGrandParentNode
  updateAVLParentChild(parent, greatGrandParentNode, isGPLeftChild);

  // Make currNode (x in Prof. Garg's lectures) the left child of
  // parentNode (y in Prof. Garg's lectures)
  // The last parameter is "true" to indicate that currNode should be
  // made the left child of parentNode
  updateAVLParentChild(currNode, parent, true);
  
  // Make grandParentNode (z in Prof. Garg's lectures) the right child of
  // parentNode (y in Prof. Garg's lectures)
  // The last parameter is "false" to indicate that grandParentNode
  // should NOT be made the left child of parentNode
  updateAVLParentChild(grandParent, parent, false);

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
  updateAVLParentChild(T3, grandParent, true);
 
   //change height of grandparentnode  
   grandParent->height-=2;   
   //if grandparent is root then change root to parentnode
    if(greatGrandParentNode==NULL){          
            root=parent;return true;}
  //change all heights from parentNode      
  struct TreeNode *p=parent->parent;
  while(p!=NULL){                           
          p->height-=1;
          p=p->parent;}        
           
  return true;
}
 
bool AVLTree::rotateRightRight(TreeNode *currNode, TreeNode *parent, TreeNode *grandParent)
{
  TreeNode *greatGrandParentNode = grandParent->parent;
  // First find if grandParentNode is the left or right child of
  // greatGrandParentNode
  
  bool isGPLeftChild=true;
  if(greatGrandParentNode!=NULL){
  if (greatGrandParentNode->left == grandParent) {
    isGPLeftChild = true;
  }
  else if (greatGrandParentNode->right == grandParent) {
    isGPLeftChild = false;
  }
  else {
    cerr << "Unexpected condition encountered!" << endl;
    return false;
  }}
  // Let T3 be the left child of parentNode (i.e. of y, using notation
  // from Prof. Garg's lectures
   TreeNode *T3 = parent->left;
    // Now replicate the single rotation for RightRight as from the lecture
  // notes/video using *ONLY* calls to updateAVLParentChild

  // Make parentNode (y in Prof. Naveen Garg's lectures) the appropriate
  // child of greatGrandParentNode
  updateAVLParentChild(parent, greatGrandParentNode, isGPLeftChild);
  // Make currNode (x in Prof. Garg's lectures) the right child of
  // parentNode (y in Prof. Garg's lectures)
  // The last parameter is "false" to indicate that currNode should be
  // made the right child of parentNode
  updateAVLParentChild(currNode, parent, false);
  // Make grandParentNode (z in Prof. Garg's lectures) the left child of
  // parentNode (y in Prof. Garg's lectures)
  // The last parameter is "true" to indicate that grandParentNode
  // should NOT be made the right child of parentNode
  updateAVLParentChild(grandParent, parent, true);
  // Recall from Prof. Garg's lectures that the left and right subtrees
  // of currNode (i.e. x in Prof. Garg's lectures) stay unchanged after
  // the RightRight rotation.  So do don't need to update the children of
  // currNode at all.
  // Similarly, the left subtree of grandParentNode (i.e. z in Prof.
  // Garg's lectures) stays unchanged.  Hence, the left child of
  // grandParentNode doesn't need to be updated at all.
  // The only update needed is that the left subtree of parentNode (i.e.
  // y in Prof. Garg's notes) should now become the right
  // child of grandParentNode (i.e. of z in Prof. Garg's notes).

  // We use "false" as the third argument of the following call to indicate
  // that T3 should become the right child of grandParentNode
  updateAVLParentChild(T3, grandParent, false);
  //change height of grandparentnode
  grandParent->height-=2;
  if(greatGrandParentNode==NULL){
            root=parent;return true;}
  //if grandparent is root then change root to parentnode 
  //change all heights from parentNode       
  struct TreeNode *p=parent->parent;
  while(p!=NULL){
          p->height-=1;
          p=p->parent;}
  return true;
}


bool AVLTree::rotateLeftRight(TreeNode *currNode, TreeNode *parent, TreeNode *grandParent)
{
  // Going back to Prof. Naveen Garg's lecture, x is *currNode,
  // y is *parentNode and z is *grandParentNode

  // Moreover, currNode is the right child of parentNode, and
  // parentNode is the left child of grandParentNode.  That's
  // why we are doing a rotateLeftRight

  TreeNode *greatGrandParentNode = grandParent->parent;
  
  // First find if grandParentNode is the left or right child of
  // greatGrandParentNode

  bool isGPLeftChild=true;
  if(greatGrandParentNode!=NULL){
  if (greatGrandParentNode->left == grandParent) {
    isGPLeftChild = true;
  }
  else if (greatGrandParentNode->right == grandParent) {
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
  updateAVLParentChild(currNode, greatGrandParentNode, isGPLeftChild);

  // Make parentNode (y in Prof. Garg's lectures) the left child of
  // currNode (x in Prof. Garg's lectures)
  // The last parameter is "true" to indicate that parentNode should be
  // made the left child of currNode
  updateAVLParentChild(parent, currNode, true);
  
  // Make grandParentNode (z in Prof. Garg's lectures) the right child of
  // currNode (x in Prof. Garg's lectures)
  // The last parameter is "false" to indicate that grandParentNode
  // should NOT be made the left child of currNode
  updateAVLParentChild(grandParent, currNode, false);
  
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
  updateAVLParentChild(T2, parent, false);

  // We use "true" as the third argument of the following call to indicate
  // that T3 should become the left child of grandParentNode
  updateAVLParentChild(T3, grandParent, true);
  //change height of grandparentnode,parentnode,currnode
  grandParent->height-=2;  
  currNode->height+=1;
  parent->height-=1;   
  //if grandparent is NULL then change root to currnode
  if(greatGrandParentNode==NULL){
            root=currNode;return true;}   
  //change all heights from currNode   
  struct TreeNode *p=currNode->parent;
  while(p!=NULL){
          p->height-=1;
          p=p->parent;}
  return true;
}



bool AVLTree::rotateRightLeft(TreeNode *currNode, TreeNode *parent, TreeNode *grandParent)
{
  // Implement this yourself
  TreeNode *greatGrandParentNode = grandParent->parent;
  // First find if grandParentNode is the left or right child of// greatGrandParentNode
  bool isGPLeftChild=true;
  if(greatGrandParentNode!=NULL){
  if (greatGrandParentNode->left == grandParent) {
    isGPLeftChild = true;
  }
  else if (greatGrandParentNode->right == grandParent) {
    isGPLeftChild = false;
  }
  else {
    cerr << "Unexpected condition encountered!" << endl;
    return false;
  }}
  // Let T2 be the right child of currNode (i.e. of x)
  TreeNode *T2 = currNode->right;
  
  // Let T3 be the left child of currNode (i.e. of x)
  TreeNode *T3 = currNode->left;
// Now replicate the double rotation for RightLeft as from the lecture
  // notes/video using *ONLY* calls to updateAVLParentChild
  //
  // We can directly implement the double rotation, instead of doing two
  // rotations sequentially.  So we'll look at the end-result of the
  // double rotation (refer Prof. Garg's lecture notes) and arrive at that
  // from the original tree.

  // Make currNode (x in Prof. Naveen Garg's lectures) the appropriate
  // child of greatGrandParentNode
  updateAVLParentChild(currNode, greatGrandParentNode, isGPLeftChild);
  // Make parentNode (y in Prof. Garg's lectures) the right child of
  // currNode (x in Prof. Garg's lectures)
  // The last parameter is "false" to indicate that parentNode shouldNOT be
  // made the left child of currNode
  updateAVLParentChild(parent, currNode, false);
  // Make grandParentNode (z in Prof. Garg's lectures) the left child of
  // currNode (x in Prof. Garg's lectures)
  // The last parameter is "true" to indicate that grandParentNode
  // should be made the left child of currNode
  updateAVLParentChild(grandParent, currNode, true);
  
  
  // We use "true" as the third argument of the following call to indicate
  // that T2 should  become the left child of ParentNode
  updateAVLParentChild(T2, parent, true);

  // We use "false" as the third argument of the following call to indicate
  // that T3 should  NOT become the left child of grandParentNode
  updateAVLParentChild(T3, grandParent, false);
  //change height of grandparentnode,parentnode,currnode
  grandParent->height-=2;  
  currNode->height+=1;
  parent->height-=1;
  //if grandparent is NULL then change root to currnode    
  if(greatGrandParentNode==NULL){
            root=currNode;return true;}   
  struct TreeNode *p=currNode->parent;
   //change all heights from currNode   
  while(p!=NULL){
          p->height-=1;
          p=p->parent;}
  return true;         
            
            
}

// Returns true on successful insertion in AVL tree. Returns false otherwise.
// You may assume that no two elements being inserted have the same journey
// code, and journey code is the key for insertion and finding in the AVL
// tree.

bool AVLTree::insert(int jrnyCode, int price)
{ 
  //inserting element in appropriate position 
  //if journeycoe is alredy present return false 
  struct TreeNode *currNode = root, *parentOfCurrNode = nullptr;
  int i=1;
  if(root==NULL){root=new TreeNode(jrnyCode,price);
                 return true;} //if root is null then just insert at root
  TreeNode *z=new TreeNode(jrnyCode,price);
  while (currNode != nullptr) {
  if (AVLLessThan(currNode,z)) {
      i=i+1;
      parentOfCurrNode = currNode;
      currNode = currNode->right;
    }
   else if (AVLLessThan(z,currNode)) {
      i=i+1;
      parentOfCurrNode = currNode;
      currNode = currNode->left;
    }
    else { 
      return false;
    }
  }
  currNode=new TreeNode(jrnyCode,price);
  currNode->parent=parentOfCurrNode;
  struct TreeNode*x=currNode;
  if (parentOfCurrNode==NULL){root=currNode;}                    
       else if(AVLLessThan(currNode,parentOfCurrNode)){parentOfCurrNode->left=currNode;}   //updating child of parent to inserting node
            else{parentOfCurrNode->right=currNode;}
  //updating height of necessary nodes
  while(parentOfCurrNode!=NULL){
  if(parentOfCurrNode->left==currNode){if ((parentOfCurrNode->right!=NULL)&&(parentOfCurrNode->height>currNode->height)){break;}
                                       else parentOfCurrNode->height++;
                                            parentOfCurrNode=parentOfCurrNode->parent;
                                            currNode=currNode->parent;}
  else if(parentOfCurrNode->right==currNode){
                                     if ((parentOfCurrNode->left!=NULL)&&(parentOfCurrNode->height>currNode->height)){break;}
                                       else parentOfCurrNode->height++;
                                            parentOfCurrNode=parentOfCurrNode->parent;
                                            currNode=currNode->parent;}
  } 
 //finding x,y,z 
  struct TreeNode *y=new TreeNode(0,0);
  if(x==NULL){return true;}
  else{y=x->parent;
       if(y==NULL){return true;}
       else{z=y->parent;}
       if(z==NULL){return true;}}
  i=0;
  int l=0;
  int r=0;
  while(z!=NULL){
      if(z->left==NULL){l=-1;}
      else{l=z->left->height;}
      if(z->right==NULL){r=-1;}
      else{r=z->right->height;}
      if(((l-r)<-1)||((l-r)>1)){i++;break;}
      else { x=x->parent;y=y->parent;z=z->parent;}
      }
  //if found then do rotation according to relative position of x,y
  if(i!=0){
           if((z->right==y)&&(y->left==x)){rotateRightLeft(x,y,z);}
           else if((z->right==y)&&(y->right==x)){rotateRightRight(x,y,z);}
           else if((z->left==y)&&(y->left==x)){rotateLeftLeft(x,y,z);}
           else if((z->left==y)&&(y->right==x)){rotateLeftRight(x,y,z);}}
           cout<<"r"<<root->height;
           return true;
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
}

// Returns the price on finding an element in the AVL tree that matches
// journey code. Returns -1 otherwise.
// You may assume that no two node in the tree have the same journey
// code, and journey code is the key for insertion and finding in the AVL
// tree.

int AVLTree::find(int jrnyCode)
{
   struct TreeNode *x=root;
   TreeNode *z=new TreeNode(jrnyCode,0);
      while(x!=NULL){
             if (AVLLessThan(z,x)){x=x->left;}       //if JourneyCode is less then search in left subtree
             else if(AVLLessThan(x,z)){x=x->right;} //if JourneyCode is more/equal then search in right subtree
             else{return x->getprice();}                     //if found 
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
  if(find(jrnyCode)==false){return false;}
    else{TreeNode *x=root;
         TreeNode *z=new TreeNode(jrnyCode,0);
         while(x!=NULL){
             if (AVLLessThan(z,x)){x=x->left;}       //if JourneyCode is less then search in left subtree
             else if(AVLLessThan(x,z)){x=x->right;} //if JourneyCode is more/equal then search in right subtree
             else {break;}}
    TreeNode* prev = x->parent;
    if (x->left == NULL && x->right == NULL){
       if(prev==NULL){root=NULL;return true;}
       if(x==prev->left){prev->left=NULL;}
       else{prev->right=NULL;}
       free(z);
    }
    else if (x->left == NULL || x->right == NULL) {
        TreeNode* newx;
        if (x->left == NULL){newx = x->right;}
        else {newx = x->left;}
        if (prev == NULL){root=newx;root->parent=NULL;return true;}
        if (x == prev->left){prev->left = newx;newx->parent=prev;}
        else {prev->right = newx;newx->parent=prev;}
        free(x);
    }
    else {
        TreeNode* p = NULL;
        TreeNode* temp=NULL;
        // Compute the inorder successor
        temp = x->right;
        while (temp->left != NULL) {
            p = temp;
            temp = temp->left;
        }
        if (p != NULL){p->left = temp->right;}
        else {x->right = temp->right;}
        //x->getprice() = temp->getprice();
        //x->getcode() = temp->getcode();
        free(temp);
    }
    return true;}
}
void AVLTree::preorder(TreeNode *y){
        if(y==NULL) {return;}
        else {cout<<y->getcode()<<" "<<y->height<<endl;
              preorder(y->left);
              preorder(y->right);
              }
        return;      }
void AVLTree::traverse(int typeOfTraversal) {
    if(typeOfTraversal==1){
           TreeNode *x=root;
           preorder(x);  
           cout<<endl;         
    }
    return; }



