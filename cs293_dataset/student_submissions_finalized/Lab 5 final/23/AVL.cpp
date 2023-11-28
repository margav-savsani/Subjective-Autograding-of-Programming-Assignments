#ifndef AVL_H
#include "AVL.h"
#endif

#ifndef STD_HEADERS
#include <iostream>
#include <stdlib.h>
#endif


bool AVLTree::rotateLeftLeft(TreeNode *currNode, TreeNode *parentNode, TreeNode *grandParentNode)
{

  TreeNode *greatGrandParentNode = grandParentNode->parent;
  
 
  bool isGPLeftChild;
  if(greatGrandParentNode!=NULL){
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
  
  updateAVLParentChild(parentNode, greatGrandParentNode, isGPLeftChild);
  }
  else {parentNode->parent=NULL;
        root=parentNode;
        totalParentChildUpdateCost += perParentChildUpdateCost;}
   TreeNode *T3 = parentNode->right;

  updateAVLParentChild(currNode, parentNode, true);

  updateAVLParentChild(grandParentNode, parentNode, false);

  updateAVLParentChild(T3, grandParentNode, true);

  return true;
}

bool AVLTree::rotateLeftRight(TreeNode *currNode, TreeNode *parentNode, TreeNode *grandParentNode)
{
 
  TreeNode *greatGrandParentNode = grandParentNode->parent;
  TreeNode *T2 = currNode->left;
  
  
  TreeNode *T3 = currNode->right;

  bool isGPLeftChild;
  if(greatGrandParentNode!=NULL){
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
  updateAVLParentChild(currNode, greatGrandParentNode, isGPLeftChild);
  }
  else {currNode->parent=NULL;
  	root=currNode;
        totalParentChildUpdateCost += perParentChildUpdateCost;}
  

  updateAVLParentChild(parentNode, currNode, true);

  updateAVLParentChild(grandParentNode, currNode, false);

  updateAVLParentChild(T2, parentNode, false);


  updateAVLParentChild(T3, grandParentNode, true);

  return true;
}

bool AVLTree::rotateRightLeft(TreeNode *currNode, TreeNode *parentNode, TreeNode *grandParentNode)
{
  

  TreeNode *greatGrandParentNode = grandParentNode->parent;
   TreeNode *T2 = currNode->left;
  
  
  TreeNode *T3 = currNode->right;
  
  
  bool isGPLeftChild;
  if(greatGrandParentNode!=NULL){
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
   updateAVLParentChild(currNode, greatGrandParentNode, isGPLeftChild);}
   else {currNode->parent=NULL;
   	root=currNode;
   	totalParentChildUpdateCost += perParentChildUpdateCost;}
   
  

  updateAVLParentChild(parentNode, currNode, false);
  
 
  updateAVLParentChild(grandParentNode, currNode, true);
  
 
  updateAVLParentChild(T3, parentNode, true);

 
  updateAVLParentChild(T2, grandParentNode, false);

  return true;
}

bool AVLTree::rotateRightRight(TreeNode *currNode, TreeNode *parentNode, TreeNode *grandParentNode)
{    bool isGPLeftChild;
     TreeNode *greatGrandParentNode = grandParentNode->parent;

  if(greatGrandParentNode!=NULL){
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
  
  updateAVLParentChild(parentNode, greatGrandParentNode, isGPLeftChild);
  }
  else {parentNode->parent=NULL;
        root=parentNode;
        totalParentChildUpdateCost += perParentChildUpdateCost;}
   TreeNode *T3 = parentNode->left;

  updateAVLParentChild(currNode, parentNode, false);

  updateAVLParentChild(grandParentNode, parentNode, true);

  updateAVLParentChild(T3, grandParentNode, false);

  return true;
}


bool AVLTree::insert(int jrnyCode, int price)
{    if (find(jrnyCode)!=-1)return false;
           TreeNode *y=NULL;
           TreeNode *x=root;
           TreeNode *z;
           z=new TreeNode(jrnyCode,price);
           while(x!=NULL){
               y=x;
               if(AVLLessThan(z,x)){x=x->left;}
               else {x=x->right;}
                     }
           z->left=NULL;
           z->right=NULL;
           if(y==NULL) root=z,z->parent=y;
           else if (AVLLessThan(z,y))updateAVLParentChild(z,y,true);
           else updateAVLParentChild(z,y,false);         
           TreeNode *a=z;
           TreeNode *b;
           TreeNode *c;
           int p=0;
           int q=0;
           assignheight(root);
           b=a->parent;
           if(b!=NULL)c=b->parent;
           else c=NULL;
           if(c!=NULL){
           if(c->right!=NULL) p=c->right->height;
           if(c->left!=NULL) q=c->left->height;
           }
           while((abs(p-q)<2)){
             if(c==NULL)break;
             if(c->parent==NULL)break;
             if(c!=NULL){ if(c->parent!=NULL){
              a=a->parent;
              if(b!=NULL)b=b->parent;
              else break;
              c=c->parent;
                if(c->right!=NULL) p=c->right->height;
                else p=0;
                if(c->left!=NULL) q=c->left->height;
                else q=0;}}
               }
           //cout<<p<<q;
           
           if(abs(p-q)>1){
           
           if(c!=NULL && b!=NULL && a!=NULL){    
           if (c->left==b && b->left==a){
   		if(rotateLeftLeft(a,b,c)){
			assignheight(root);
			return true;
                	 }}
           if(c->left==b && b->right==a){
           	if(rotateLeftRight(a,b,c))
			{
			assignheight(root);
		         return true;
         		}}
           if(c->right==b && b->left==a){
   		if(rotateRightLeft(a,b,c))
			{assignheight(root);
		          return true;
         		 }}
           if(c->right==b && b->right==a){  
           	if(rotateRightRight(a,b,c)){
           	  	assignheight(root);
	          	return true;}
        	 }}
          }
          return true;
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


// Returns the price on finding an element in the AVL tree that matches
// journey code. Returns -1 otherwise.
// You may assume that no two node in the tree have the same journey
// code, and journey code is the key for insertion and finding in the AVL
// tree.

int AVLTree::find(int jrnyCode)
{         TreeNode *z;
          z=search(root,jrnyCode);
          if(z==NULL) return -1;
          else return 1;
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
TreeNode* AVLTree::search(TreeNode *d,int JourneyCode){
          TreeNode *x=d;
          TreeNode *z;
          z=new TreeNode(JourneyCode,0);
          if (x==NULL) return NULL;
          if(x->jrnyCode()==JourneyCode){
                      return x;}
          if(AVLLessThan(z,x)) return search(x->left,JourneyCode);
          else return search(x->right,JourneyCode);
          }
int  AVLTree::height(TreeNode *x){
          if(x==NULL){return 0; }
          if(x->right == NULL && x->left == NULL) return 1;
          if(x->right == NULL && x->left != NULL) {return height(x->left)+1;}
          if(x->right != NULL && x->left != NULL) return max(height(x->left),height(x->right))+1;
          if(x->right != NULL && x->left == NULL) {return height(x->right)+1;}
          return 0;
          }
void  AVLTree::assignheight(TreeNode *x){
           x->height=height(x);
           if(x->right!=NULL)assignheight(x->right);
           if(x->left!=NULL)assignheight(x->left);         
           return;
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


