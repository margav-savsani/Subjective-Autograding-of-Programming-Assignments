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


void heightchange( TreeNode* root, AVLTree* t){
	
	
	t->comparisioncost(1);
  	if ( root == NULL ) return;
  	t->comparisioncost(1);
	if (  root->right == NULL && root->left == NULL ) root->height= 1;

	if ( root->right != NULL && root->left != NULL ) {
	
		heightchange( root->left , t);
		heightchange( root->right, t );
		root->height = max( (root->left)->height, (root->right)->height ) +1;
	}
	else if ( root->right == NULL && root->left != NULL){
	
		heightchange( root->right, t );
		root->height = (root->left)->height +1;
	}
	else if ( root->right != NULL && root->left == NULL){
	
		heightchange( root->left, t );	
		root->height = (root->right)->height +1;
	}
}	

bool AVLTree::rotateLeftLeft(TreeNode *currNode, TreeNode *parentNode, TreeNode *grandParentNode)
{
  // Going back to Prof. Naveen Garg's lecture, x is *currNode,
  // y is *parentNode and z is *grandParentNode

  // Moreover, currNode is the left child of parentNode, and
  // parentNode is the left child of grandParentNode
  // That's why we are doing a rotateLeftLeft
  if ( grandParentNode->parent != nullptr ){
  totalComparisonCost+=perComparisonCost;
  TreeNode *greatGrandParentNode = grandParentNode->parent;
  
  // First find if grandParentNode is the left or right child of
  // greatGrandParentNode
  
  bool isGPLeftChild;
  if (greatGrandParentNode->left == grandParentNode) {
    totalComparisonCost+=perComparisonCost;
    isGPLeftChild = true;
    
  }
  else if (greatGrandParentNode->right == grandParentNode) {
    totalComparisonCost+=perComparisonCost;
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
  totalParentChildUpdateCost+= (4*perParentChildUpdateCost);
  currNode->parent = parentNode;
  grandParentNode->parent = parentNode;
  }
  else{
  
  	TreeNode *T3 = parentNode->right;
   	root = parentNode;
        root->parent = NULL;
        currNode->parent = parentNode;
        grandParentNode->parent = parentNode;
   	updateAVLParentChild(currNode, parentNode, true);
  	updateAVLParentChild(grandParentNode, parentNode, false);
   	updateAVLParentChild(T3, grandParentNode, true);
   	totalParentChildUpdateCost+= (3*perParentChildUpdateCost);
   	
   }
    heightchange(root, this);    
  return true;
}

bool AVLTree::rotateLeftRight(TreeNode *currNode, TreeNode *parentNode, TreeNode *grandParentNode)
{
  // Going back to Prof. Naveen Garg's lecture, x is *currNode,
  // y is *parentNode and z is *grandParentNode

  // Moreover, currNode is the right child of parentNode, and
  // parentNode is the left child of grandParentNode.  That's
  // why we are doing a rotateLeftRight
  if ( grandParentNode->parent != nullptr ){ // if the grandparent is not null.
  totalComparisonCost+=perComparisonCost;
  TreeNode *greatGrandParentNode = grandParentNode->parent;
  
  // First find if grandParentNode is the left or right child of
  // greatGrandParentNode

  bool isGPLeftChild;
  if (greatGrandParentNode->left == grandParentNode) {
    totalComparisonCost+=perComparisonCost;
    isGPLeftChild = true;
  }
  else if (greatGrandParentNode->right == grandParentNode) {
    totalComparisonCost+=(2*perComparisonCost);
    isGPLeftChild = false;
  }
  else {
    totalComparisonCost+=(3*perComparisonCost);
    cerr << "Unexpected condition encountered!" << endl;
    return false;
  }

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
  TreeNode *T2 = currNode->left;
  
  // Let T3 be the right child of currNode (i.e. of x)
  TreeNode *T3 = currNode->right;
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
       
  // Let T2 be the left child of currNode (i.e. of x)
  

  // We use "false" as the third argument of the following call to indicate
  // that T2 should NOT become the left child of ParentNode
  updateAVLParentChild(T2, parentNode, false);

  // We use "true" as the third argument of the following call to indicate
  // that T3 should become the left child of grandParentNode
  updateAVLParentChild(T3, grandParentNode, true);
  totalParentChildUpdateCost+= (5*perParentChildUpdateCost);
  parentNode->parent = currNode;
  grandParentNode->parent = currNode;
  }
  
  else { // if the grandparent is null.
  
 	totalComparisonCost+=perComparisonCost;// increasing comparsion cost for the if condition
  	TreeNode *T2 = currNode->left;
  	TreeNode *T3 = currNode->right;
  	root = currNode;
  	currNode->parent = NULL;
  	parentNode->parent = currNode;
  	grandParentNode->parent = currNode;
  	updateAVLParentChild(parentNode, currNode, true);
  	updateAVLParentChild(grandParentNode, currNode, false);
  	updateAVLParentChild(T2, parentNode, false);
  	updateAVLParentChild(T3, grandParentNode, true);
  	totalParentChildUpdateCost+= (4*perParentChildUpdateCost) ;
  }
  
  heightchange(root, this); // change the 
  return true;
}

bool AVLTree::rotateRightLeft(TreeNode *currNode, TreeNode *parent, TreeNode *grandParent)
{
  // Implement this yourself
  
  
 if ( grandParent->parent != nullptr ){  
 totalComparisonCost+=perComparisonCost;
 TreeNode *greatGrandParentNode = grandParent->parent;
   bool isGPLeftChild;
  if (greatGrandParentNode->left == grandParent) {
    totalComparisonCost+=perComparisonCost;
    isGPLeftChild = true;
  }
  else if (greatGrandParentNode->right == grandParent) {
    totalComparisonCost+=(2*perComparisonCost);
    isGPLeftChild = false;
  }
  else {
    totalComparisonCost+=(2*perComparisonCost);
    cerr << "Unexpected condition encountered!" << endl;
    return false;
  }
  updateAVLParentChild(currNode, greatGrandParentNode, isGPLeftChild);
  TreeNode *T1 = currNode->left;
  TreeNode *T2 = currNode->right;
  updateAVLParentChild(parent, currNode, false);
  updateAVLParentChild(grandParent, currNode, true);
  parent->parent = currNode;
  grandParent->parent = currNode;
  
  updateAVLParentChild(T1, grandParent, false);
  updateAVLParentChild(T2, parent, true);
  totalParentChildUpdateCost+= (5*perParentChildUpdateCost);
  
  }
  
  else {
  
  totalComparisonCost+=perComparisonCost;
  TreeNode *T1 = currNode->left;
  TreeNode *T2 = currNode->right;
  root = currNode;
  currNode->parent = NULL;
  updateAVLParentChild(parent, currNode, false);
  parent->parent = currNode;
  grandParent->parent = currNode;
  updateAVLParentChild(grandParent, currNode, true);
  updateAVLParentChild(T1, grandParent, false);
  updateAVLParentChild(T2, parent, true);
  
  totalParentChildUpdateCost+= (4*perParentChildUpdateCost);
  
  }
   heightchange(root, this);
  return true;
  
}

bool AVLTree::rotateRightRight(TreeNode *currNode, TreeNode *parent, TreeNode *grandParent)
{
  // Implement this yourself
       
    if (grandParent->parent != nullptr ){
    
    totalComparisonCost+=perComparisonCost;
    TreeNode *greatGrandParentNode = grandParent->parent;
    bool isGPLeftChild;
      // No updating of totalParentChildUpdateCost needed hered;

    if (greatGrandParentNode->left == grandParent){
      totalComparisonCost+=(2*perComparisonCost);
      isGPLeftChild = true;
    }
    else if (greatGrandParentNode->right == grandParent) {
      totalComparisonCost+=(2*perComparisonCost);
      isGPLeftChild = false;
    }
    else {
      cerr << "Unexpected condition encountered!" << endl;
    return false;
    }
  TreeNode *T3 = parent->left;
   updateAVLParentChild(parent, greatGrandParentNode, isGPLeftChild);
   updateAVLParentChild(currNode, parent, false);
   updateAVLParentChild(grandParent, parent, true);
   updateAVLParentChild(T3, grandParent, false);
   totalParentChildUpdateCost+= (4*perParentChildUpdateCost);
   currNode->parent = parent;
   grandParent->parent = parent;
   }
   else {
   	
   	totalComparisonCost+=(perComparisonCost);
   	TreeNode *T3 = parent->left;
   	root = parent;
        root->parent = NULL;
        currNode->parent = parent;
        grandParent->parent = parent;
   	updateAVLParentChild(currNode, parent, false);
  	updateAVLParentChild(grandParent, parent, true);
   	updateAVLParentChild(T3, grandParent, false);
   	totalParentChildUpdateCost+= (3*perParentChildUpdateCost);
   	
   }
    heightchange(root, this);	


  return true;
}

// Returns true on successful insertion in AVL tree. Returns false otherwise.
// You may assume that no two elements being inserted have the same journey
// code, and journey code is the key for insertion and finding in the AVL
// tree.

TreeNode* add2(TreeNode* root, int JourneyCode, int price, AVLTree* t){


	TreeNode* x;
	x = new TreeNode(JourneyCode, 0);
	 if( root == NULL){
	       
		TreeNode* n= new TreeNode(JourneyCode,price);
		root = n;
		root->height=1;
		return root;
	}
	
	if( t->AVLLessThan(root, x) == true ){
	
		root->right = add2(root->right, JourneyCode, price, t);
    		(root->right)->parent = root;


	}
	else if( t->AVLLessThan(x, root) == true ){

		root->left = add2(root->left, JourneyCode, price, t);
    		(root->left)->parent = root;
	}
	
	if ( root->right != NULL && root->left != NULL ) {
	
		root->height = max( (root->left)->height, (root->right)->height ) +1;
	}
	else if ( root->right == NULL && root->left != NULL){
	
		root->height = (root->left)->height +1;
	}
	else if ( root->right != NULL && root->left == NULL){
	
		root->height = (root->right)->height +1;
	}
	return root;
}

TreeNode* findd2( TreeNode* root, int JourneyCode, AVLTree* t){


	TreeNode* x;
	x = new TreeNode(JourneyCode, 0);
	
	if( root == NULL){
	
		return NULL;
	}
	if(!(t->AVLLessThan(root, x) == true) && !(t->AVLLessThan(x, root) == true )){
		
			return root;
	}
	
	else if(t->AVLLessThan(root, x) == true ){
	
		return findd2(root->right, JourneyCode,  t);
	}
	
	else if(t->AVLLessThan(x, root) == true ){
	
		return findd2(root->left, JourneyCode, t);
	}
	return root;
	
}

bool AVLTree::insert(int jrnyCode, int price)
{


  int found = find(jrnyCode);
  if(found != -1 ) return false;
  root = add2(root, jrnyCode, price, this);
  TreeNode* x = findd2(root, jrnyCode, this);
  TreeNode *y;
  TreeNode *ychild = NULL;
  TreeNode *ygchild = NULL;
  y=x;
  bool found1 = false;
  while(!found1 && y!= NULL){
  
  	totalComparisonCost+=perComparisonCost;
  	if ( y->left != NULL && y-> right !=NULL){
  	 totalComparisonCost+=(2*perComparisonCost);
  	if( !(((y->left)->height - (y->right)->height >=-1) && ((y->left)->height - (y->right)->height <=1))){
  	  found1 = true;
  		break;
  	} 
  	}
  	else if ( y->left == NULL && y-> right !=NULL ){
  		 totalComparisonCost+= (2*perComparisonCost);
  		if ( (y->right)->height > 1){
  		
  			found1 = true;
  			break;
  		} 
       }
       else if ( y->left != NULL && y-> right ==NULL ){
  		totalComparisonCost+= (2*perComparisonCost);
  		if ( (y->left)->height > 1){
  		
  			found1 = true;
  			break;
  		} 
       }
       
   if (y-> parent != NULL){
   	
   	totalComparisonCost+= (perComparisonCost);
        ygchild = ychild;
  	 ychild = y;
  	 y = y->parent;
   }
  else{
   	totalComparisonCost+= (perComparisonCost);
  	break;
  }
  }
  
  if ( found1 == true ){
  bool childleft;
  bool grandchildleft;

  if ( y->left == ychild ) { totalComparisonCost+= (perComparisonCost) ; childleft= true; }
  else childleft= false;
  
  if ( ychild->left == ygchild ) { totalComparisonCost+= (perComparisonCost); grandchildleft = true; }
  else grandchildleft= false;
  
  if ( childleft == true && grandchildleft == true) return rotateLeftLeft( ygchild, ychild, y);
  else if ( childleft == false && grandchildleft == false ) return rotateRightRight( ygchild, ychild, y);
  else if ( childleft == true && grandchildleft == false) return rotateLeftRight( ygchild, ychild, y);
  else return rotateRightLeft(ygchild, ychild, y);
 
  
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
  return true;
}

// Returns the price on finding an element in the AVL tree that matches
// journey code. Returns -1 otherwise.
// You may assume that no two node in the tree have the same journey
// code, and journey code is the key for insertion and finding in the AVL
// tree.

int AVLTree::find(int jrnyCode)
{

   if( findd2(root, jrnyCode, this)!=NULL ){
   
   	return findd2(root, jrnyCode, this)->pricereturn();
   }
   else{
   
   	return -1;
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


