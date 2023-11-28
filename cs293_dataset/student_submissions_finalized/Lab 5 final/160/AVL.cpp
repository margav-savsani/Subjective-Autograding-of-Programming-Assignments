#ifndef AVL_H
#include "AVL.h"
#endif

#ifndef STD_HEADERS
#include <iostream>
#include <stdlib.h>
#endif

    int getBalance(TreeNode* N){
	TreeNode* l=N->left;
	TreeNode* r=N->right;
	if(l==NULL&&r==NULL) return 0;
	else if(l==NULL) return ((-1)-(r->height));
	else if(r==NULL) return (1+(l->height));
	else return ((l->height)-(r->height));
    }


bool AVLTree::rotateLeftLeft(TreeNode *currNode, TreeNode *parentNode, TreeNode *grandParentNode)
{
 
  TreeNode *greatGrandParentNode = grandParentNode->parent;
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


  TreeNode *T3 = parentNode->right;

 
  updateAVLParentChild(parentNode, greatGrandParentNode, isGPLeftChild);

  updateAVLParentChild(currNode, parentNode, true);
  

  updateAVLParentChild(grandParentNode, parentNode, false);


  updateAVLParentChild(T3, grandParentNode, true);

  return true;
}
else{greatGrandParentNode=new TreeNode(1,1);
  TreeNode *T3 = parentNode->right;

 bool isGPLeftChild=true;
  updateAVLParentChild(parentNode, greatGrandParentNode, isGPLeftChild);

  updateAVLParentChild(currNode, parentNode, true);
  

  updateAVLParentChild(grandParentNode, parentNode, false);


  updateAVLParentChild(T3, grandParentNode, true);
  root=greatGrandParentNode->left;root->parent=NULL;
return true;
}
}

bool AVLTree::rotateLeftRight(TreeNode *currNode, TreeNode *parentNode, TreeNode *grandParentNode)
{


  TreeNode *greatGrandParentNode = grandParentNode->parent;
 
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

  // Let T2 be the left child of currNode (i.e. of x)
  TreeNode *T2 = currNode->left;
  
  // Let T3 be the right child of currNode (i.e. of x)
  TreeNode *T3 = currNode->right;


  updateAVLParentChild(currNode, greatGrandParentNode, isGPLeftChild);

  updateAVLParentChild(parentNode, currNode, true);
  

  updateAVLParentChild(grandParentNode, currNode, false);
  

  updateAVLParentChild(T2, parentNode, false);


  updateAVLParentChild(T3, grandParentNode, true);

  return true;
}
else{
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
}

bool AVLTree::rotateRightLeft(TreeNode *currNode, TreeNode *parent, TreeNode *grandParent)
{
  // Implement this yourself
   // why we are doing a rotateLeftRight

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

  // Let T2 be the left child of currNode (i.e. of x)
  TreeNode *T1 = currNode->left;
  
  // Let T3 be the right child of currNode (i.e. of x)
  TreeNode *T2 = currNode->right;

  updateAVLParentChild(currNode, greatGrandParentNode, isGPLeftChild);

  updateAVLParentChild(parent, currNode, false);
 
  updateAVLParentChild(grandParent, currNode, true);
  updateAVLParentChild(T2, parent, true);

  updateAVLParentChild(T1, grandParent, false);  
  return true;
}
else{
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
}

bool AVLTree::rotateRightRight(TreeNode *currNode, TreeNode *parent, TreeNode *grandParent)
{

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

  TreeNode *T1 = parent->left;

  updateAVLParentChild(parent, greatGrandParentNode, isGPLeftChild);

  updateAVLParentChild(currNode, parent, false);

  updateAVLParentChild(grandParent, parent, true);

  updateAVLParentChild(T1, grandParent, false);

  return true;
}
else{
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
  
	TreeNode* insnode=new TreeNode(jrnyCode,price);
	if(root==NULL){
		root=insnode;
	}
	else{
		TreeNode *prev=NULL;
		TreeNode *temp=root;
		while(temp!=NULL){
			if(AVLLessThan(insnode,temp)){
				prev=temp;
				temp=temp->left;
			}
			else if(AVLLessThan(temp,insnode)){
				prev=temp;
				temp=temp->right;
			}
		}
		if (AVLLessThan(insnode,prev)) {updateAVLParentChild(insnode, prev, true);}
		else {updateAVLParentChild(insnode, prev, false);}
		height(root);
		while(prev!=NULL){
		cout<<"Yes1"<<endl;
			if(getBalance(prev)==2){
			cout<<"Yes2"<<endl;
				TreeNode* x=prev->left;
				if(getBalance(x)>0) rotateLeftLeft(x->left,x,prev);
				else rotateLeftRight(x->right,x,prev);
				height(root);
				//break;
			}
			else if(getBalance(prev)==-2){
			cout<<"Yes3"<<endl;
				TreeNode* x=prev->right;
				if(getBalance(x)<0) rotateRightRight(x->right,x,prev);
				else rotateRightLeft(x->left,x,prev);
				height(root);
				//break;
			}
			else{cout<<"Yes4"<<endl;}
			prev=prev->parent;
		}
	}

	return true;	
}



int AVLTree::find(int jrnyCode)
{
  
  	TreeNode* insnode=new TreeNode(jrnyCode,100);
	if(root==NULL) return -1;
	if((!AVLLessThan(insnode,root))&&(!AVLLessThan(root,insnode))) return root->printprice();
	TreeNode *prev=NULL;
	TreeNode *temp=root;
	while(temp!=NULL){
		if(AVLLessThan(insnode,temp)){
			prev=temp;
			temp=temp->left;
		}
		else if(AVLLessThan(temp,insnode)){
			prev=temp;
			temp=temp->right;
		}
		else {return temp->printprice();}
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
  return true;
}


