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
  if(greatGrandParentNode!=NULL){
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

  if(greatGrandParentNode==NULL){
    greatGrandParentNode=new TreeNode(1,1);
     TreeNode *T3 = parentNode->right;
     bool isGPLeftChild=true;
    parentNode=root;
    updateAVLParentChild(parentNode, greatGrandParentNode, isGPLeftChild);
    updateAVLParentChild(currNode, parentNode, true);
    updateAVLParentChild(grandParentNode, parentNode, false);
    updateAVLParentChild(T3, parentNode, true);
    root=greatGrandParentNode->left;
    root->parent=NULL;
    return true;
  }

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
if (greatGrandParentNode!=NULL){
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
  updateAVLParentChild(T3, grandParentNode, true);}
  
  if(greatGrandParentNode){
  
  greatGrandParentNode=new TreeNode(1,1);
 bool isGPLeftChild=true;
  TreeNode *T2 = currNode->left;
  // Let T3 be the right child of currNode (i.e. of x)
  TreeNode *T3 = currNode->right;
  updateAVLParentChild(currNode, greatGrandParentNode, isGPLeftChild);
  updateAVLParentChild(parentNode, currNode, true);
  updateAVLParentChild(grandParentNode, currNode, false);
  updateAVLParentChild(T2, parentNode, false);
  updateAVLParentChild(T3, grandParentNode, true);
  root=greatGrandParentNode->left;root->parent=NULL;
  return true;
  }

  return true;
}

bool AVLTree::rotateRightLeft(TreeNode *currNode, TreeNode *parent, TreeNode *grandParent)
{
  // Implement this yourself
  TreeNode *greatGrandParentNode = grandParent->parent;
  
  // First find if grandParentNode is the left or right child of
  // greatGrandParentNode
  if(greatGrandParentNode!=NULL){
  bool isGPLeftChild;
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

  updateAVLParentChild(currNode, greatGrandParentNode, isGPLeftChild);

  updateAVLParentChild(parent,currNode,false);

  updateAVLParentChild(grandParent,currNode,true);
  
  // Let T2 be the left child of currNode (i.e. of x)
  TreeNode *T2 = currNode->left;
  
  // Let T3 be the right child of currNode (i.e. of x)
  TreeNode *T3 = currNode->right;

   // We use "true" as the third argument of the following call to indicate
  // that T2 should  become the left child of ParentNode
  updateAVLParentChild(T2, parent, true);

  // We use "false" as the third argument of the following call to indicate
  // that T3 should NOT become the left child of grandParentNode
  updateAVLParentChild(T3, grandParent, false);

  return true;}
  if(greatGrandParentNode==NULL){
   greatGrandParentNode=new TreeNode(1,1);
  bool isGPLeftChild=true;
  // Let T2 be the left child of currNode (i.e. of x)
  TreeNode *T1 = currNode->left;
  
  // Let T3 be the right child of currNode (i.e. of x)
  TreeNode *T2 = currNode->right;
  updateAVLParentChild(currNode, greatGrandParentNode, isGPLeftChild);
  updateAVLParentChild(parent, currNode, false);
  updateAVLParentChild(grandParent, currNode, true);
  updateAVLParentChild(T2, parent, true);
  updateAVLParentChild(T1, grandParent, false);  
  root=greatGrandParentNode->left;root->parent=NULL;
  return true;
  }
  return true;
}

bool AVLTree::rotateRightRight(TreeNode *currNode, TreeNode *parent, TreeNode *grandParent)
{
  // Implement this yourself
  TreeNode *greatGrandParentNode = grandParent->parent;
  
  // First find if grandParentNode is the left or right child of
  // greatGrandParentNode
  if(greatGrandParentNode!=NULL){
  bool isGPLeftChild;
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
  updateAVLParentChild(parent, greatGrandParentNode, isGPLeftChild);


  updateAVLParentChild( currNode,parent,false);

  updateAVLParentChild(grandParent,parent,true);

  TreeNode *T3 = parent->left;

  updateAVLParentChild(T3, grandParent, false);

  return true;}
  if(greatGrandParentNode==NULL){
  greatGrandParentNode=new TreeNode(1,1);
  TreeNode *T1 = parent->left;

 bool isGPLeftChild=true;
  updateAVLParentChild(parent, greatGrandParentNode, isGPLeftChild);
  updateAVLParentChild(currNode, parent, false);
  updateAVLParentChild(grandParent, parent, true);
  updateAVLParentChild(T1, grandParent, false);
  root=greatGrandParentNode->left;root->parent=NULL;
return true;

  }
 return true;
}

// Returns true on successful insertion in AVL tree. Returns false otherwise.
// You may assume that no two elements being inserted have the same journey
// code, and journey code is the key for insertion and finding in the AVL
// tree.

int AVLTree::height( TreeNode*node)
{
if(node == NULL)
return 0;
else if((node->left==NULL)&&(node->right==NULL)){
  return 0;}
else return ((max(height(node->left),height(node->right))) + 1);
}

void AVLTree:: update(TreeNode*t){
  TreeNode*x;
  TreeNode*y;
  t->height = height(t);
  x=t->left;
  y=t->right;
  if(x!=NULL)
  {update(x);}
  if(y!=NULL){
  update(y);}
}

int AVLTree::dif(TreeNode*t) {
   TreeNode* l=t->left;
	TreeNode* r=t->right;
	if(l==NULL&&r==NULL) return 0;
	else if(l==NULL) return ((-1)-(r->height));
	else if(r==NULL) return (1+(l->height));
	else return ((l->height)-(r->height));
}


bool AVLTree::insert(int jrnyCode, int price)
{
  if(find(jrnyCode)==1) return false;

   TreeNode *z;
    if (root==NULL){
       z=new TreeNode(jrnyCode,price);
       root=z;
      return true;
    }
    TreeNode *x = new TreeNode(jrnyCode,price);
    TreeNode *y;
    TreeNode *t =root;
    
    while(t!=NULL){
      if(AVLLessThan(x, t)){
        y=t;
        t=t->left;}
      else if(AVLLessThan(t,x)){
        y=t ;
        t=t->right;}
        else{return false;}
    }
    if(AVLLessThan(x, y)) y->left = x;
    else y->right =  x;
    update(root);
    while(y!=NULL){
		 cout<<"Yes1"<<endl;
     cout<<height(y)<<endl;
     cout<<dif(y)<<endl;
     y->printInfo();
			if(dif(y)==2){
			cout<<"Yes2"<<endl;
				TreeNode* p=y->left;
				if(dif(p)>0) rotateLeftLeft(p->left,p,y);
				else rotateLeftRight(p->right,p,y);
				update(root);
			}
			else if(dif(y)==-2){
			cout<<"Yes3"<<endl;
				TreeNode* p=y->right;
				if(dif(p)<0) rotateRightRight(p->right,p,y);
				else rotateRightLeft(p->left,p,y);
				update(root);
				
			}
			else{cout<<"Yes4"<<endl;}
		
      y=y->parent;
    
		}
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
int AVLTree::find2(TreeNode*root,int jrnyCode){
    if(root==NULL){return -1;}
    TreeNode*t=root;
    TreeNode*x=new TreeNode(jrnyCode,1);
    if(AVLLessThan(x,t))return find2(t->left,jrnyCode);
    if(AVLLessThan(t,x))return find2(t->right,jrnyCode);
    if((!AVLLessThan(x, t))&&(!AVLLessThan(t,x))) return  t->getprice();
    
       return  t->getprice(); }

int AVLTree::find(int jrnyCode)
{
  return find2(root,jrnyCode);
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


