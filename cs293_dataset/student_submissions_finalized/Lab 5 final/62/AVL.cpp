#ifndef AVL_H
#include "AVL.h"
#endif

#ifndef STD_HEADERS
#include <iostream>
#include <stdlib.h>
#endif


//   x                             currNode
//   y                             parentNode
//   z                             grandParentNode

//pre-implemented
bool AVLTree::rotateLeftLeft(TreeNode *currNode, TreeNode *parentNode, TreeNode *grandParentNode)
{

	// Moreover, currNode is the left child of parentNode, and
	// parentNode is the left child of grandParentNode
	// That's why we are doing a rotateLeftLeft

	TreeNode *greatGrandParentNode = grandParentNode->parent;
	
	// First find if grandParentNode is the left or right child of
	// greatGrandParentNode
	// arbitrarily handle null greatgrandparent here as it will be taken care later
	bool isGPLeftChild;
	if (greatGrandParentNode==nullptr||greatGrandParentNode->left == grandParentNode) {
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

//pre-implemented
bool AVLTree::rotateLeftRight(TreeNode *currNode, TreeNode *parentNode, TreeNode *grandParentNode)
{
	// First find if grandParentNode is the left or right child of
	// greatGrandParentNode
	// arbitrarily handle null greatgrandparent here as it will be taken care later

	TreeNode *greatGrandParentNode = grandParentNode->parent;

	bool isGPLeftChild;
	if (greatGrandParentNode==nullptr||greatGrandParentNode->left == grandParentNode) {
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
	updateAVLParentChild(T3, grandParentNode, true);

	return true;
}

//implemented by me
bool AVLTree::rotateRightLeft(TreeNode *currNode, TreeNode *parentNode, TreeNode *grandParentNode)
{
	
	// Moreover, currNode is the right child of parentNode, and
	// parentNode is the left child of grandParentNode.  That's
	// why we are doing a rotateLeftRight

	TreeNode *greatGrandParentNode = grandParentNode->parent;
	
	// First find if grandParentNode is the left or right child of
	// greatGrandParentNode
	// arbitrarily handle null greatgrandparent here as it will be taken care later

	bool isGPLeftChild;
	if (greatGrandParentNode==nullptr||greatGrandParentNode->left == grandParentNode) {
		isGPLeftChild = true;
	}
	else if (greatGrandParentNode->right == grandParentNode) {
		isGPLeftChild = false;
	}
	else {
		cerr << "Unexpected condition encountered!" << endl;
		return false;
	}

	// Let T2 be the right child of currNode (i.e. of x)
	TreeNode *T2 = currNode->right;
	
	// Let T3 be the left child of currNode (i.e. of x)
	TreeNode *T3 = currNode->left;

	// Now replicate the double rotation for LeftRight as from the lecture
	
	// Make currNode (x) the appropriate
	// child of greatGrandParentNode
	updateAVLParentChild(currNode, greatGrandParentNode, isGPLeftChild);

	// Make parentNode (y) the right child of
	// currNode (x in Prof. Garg's lectures)
	updateAVLParentChild(parentNode, currNode, false);
	
	// Make grandParentNode (z) the right child of
	// currNode (x)
	updateAVLParentChild(grandParentNode, currNode, true);
	
	//  "true" as the third argument of the following call to indicate
	// that T2 should become the left child of ParentNode
	updateAVLParentChild(T2, parentNode, true);

	// "false" as the third argument of the following call to indicate
	// that T3 should NOT become the left child of grandParentNode
	updateAVLParentChild(T3, grandParentNode, false);

	return true;
}

bool AVLTree::rotateRightRight(TreeNode *currNode, TreeNode *parentNode, TreeNode *grandParentNode)
{ 
	// currNode is the right child of parentNode, and
	// parentNode is the right child of grandParentNode

	TreeNode *greatGrandParentNode = grandParentNode->parent;
	
	// First find if grandParentNode is the left or right child of
	// greatGrandParentNode
	
	bool isGPLeftChild;
	if (greatGrandParentNode==nullptr||greatGrandParentNode->left == grandParentNode) {
		isGPLeftChild = true;
	}
	else if (greatGrandParentNode->right == grandParentNode) {
		isGPLeftChild = false;
	}
	else {
		cerr << "Unexpected condition encountered!" << endl;
		return false;
	}

	// Let T3 be the left child of parentNode (i.e. of y)
	TreeNode *T3 = parentNode->left;

	// Replicate the single rotation for LeftLeft as from the lecture
	// Make parentNode (y) the appropriate
	// child of greatGrandParentNode
	updateAVLParentChild(parentNode, greatGrandParentNode, isGPLeftChild);

	// Make currNode (x) the right child of
	// parentNode (y)
	updateAVLParentChild(currNode, parentNode, false);
	
	// Make grandParentNode (z) the left child of
	// parentNode (y)
	updateAVLParentChild(grandParentNode, parentNode, true);

	// We use "false" as the third argument of the following call to indicate
	// that T3 should NOT become the left child of grandParentNode
	updateAVLParentChild(T3, grandParentNode, false);

	return true;
}

// Returns true on successful insertion in AVL tree. Returns false otherwise.
// You may assume that no two elements being inserted have the same journey
// code, and journey code is the key for insertion and finding in the AVL
// tree.
bool AVLTree::insert(int JourneyCode, int price)
{
	TreeNode* to_ins = new TreeNode(JourneyCode,price);
	// Implement insertion in BST
	if (root==nullptr){ //insert to empty BST
		root=to_ins;
		return true;
	}
	
	TreeNode* current=root;
	while(current!=nullptr){//travel down the tree
		if (AVLLessThan(to_ins,current)){
			if (current->left==nullptr){ // if reached an empty spot, insert here
					updateAVLParentChild(to_ins,current, true);
					break ;
			}
			current=current->left; //otherwise keep moving
		}
		else { 
			if (current->right==nullptr){ // if reached an empty spot, insert here
					updateAVLParentChild(to_ins,current, false);
					break;
			}
			current=current->right; //otherwise keep moving
		}
	}  
	if (current==nullptr) return false; // a weird scenario

	//the following function will update the heights of the nodes from the bottom upwards
	//when the imbalance is found it calls the relevant rotate function as well
	return updateHeights(current);
}

// Returns the price on finding an element in the AVL tree that matches
// journey code. Returns -1 otherwise.
// You may assume that no two node in the tree have the same journey
// code, and journey code is the key for insertion and finding in the AVL
// tree.
int AVLTree::find(int JourneyCode)
{
	TreeNode to_find(JourneyCode,-1);
	TreeNode* current=root;
	while(current!=nullptr){  //travelling down the tree      
		if (AVLLessThan(&to_find,current)){ // to_find < current
				current=current->left;
		}
		else if(AVLLessThan(current,&to_find)){
				current=current->right;
		} //equals
		else return (current->getPrice());
	}    
	return (-1); //did not find match
}
// handles heigh updatation AND calls the respective rotate when required, 
//generalised for both insert and delete
bool AVLTree::updateHeights(TreeNode* bottom){
	TreeNode* current=bottom;
		for(;current!=nullptr;current=current->parent){
			//imbalance case
			if (abs(getHeight(current->left)-getHeight(current->right))>1.5){
				//current is the grandparent node
				//we identify x,y,z - generalised to apply to both insertion and deletion
				//for each case we apply the respective rotate function
				TreeNode* child,*gchild;
				if (getHeight(current->left)<getHeight(current->right)){
					child = (current->right);
					if (getHeight(child->left)<=getHeight(child->right)){
						gchild = (child->right);
						rotateRightRight(gchild,child,current);
					}
					else{
						gchild = (child->left);
						rotateRightLeft(gchild,child,current);
					}
				}
				else{
					child = (current->left);
					if (getHeight(child->left)<getHeight(child->right)){
						gchild = (child->right);
						rotateLeftRight(gchild,child,current);
					}
					else{
						gchild = (child->left);
						rotateLeftLeft(gchild,child,current);
					}
				}
				//rotation has happened
				//now current becomes a child of the parent node, we update the heights of the new childs
				if (current==root) root=current->parent;
				current=current->parent;
				current->right->height=1+max(getHeight(current->right->right),getHeight(current->right->left));
				current->left->height=1+max(getHeight(current->left->right),getHeight(current->left->left));

			}
			int to_set = 1+max(getHeight(current->right),getHeight(current->left));
			if (to_set == current->height) return true;// no need to look futher
			current->height = to_set;
		} //otherwise keeps updating till the root
		return true;
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
bool AVLTree::remove(int JourneyCode)
{
	TreeNode to_remove=TreeNode(JourneyCode,-1);
	if (root==nullptr) return false;
	//handling the case where root is to be removed
	if (!(AVLLessThan(&to_remove,root)||AVLLessThan(root,&to_remove))){
		if (root->left==nullptr&&root->right==nullptr){ //no children
			delete root;
			root=nullptr;
		} 
		//one child
		else if (root->left==nullptr) { 
			root=root->right;
			delete (root->parent);
			updateAVLParentChild(root,nullptr,0);             
		}
		else if(root->right==nullptr){
			root=root->left;
			delete (root->parent);
			updateAVLParentChild(root,nullptr,0);             
		}
		else{ //rem function can be called
			rem_node(root);
		}
		return true;
	}
	TreeNode* current=root;
	while(current!=nullptr){  //travelling down the tree      
		if (AVLLessThan(&to_remove,current)){ // to_remove < current
			current=current->left;
		}
		else if(AVLLessThan(current,&to_remove)){
			current=current->right;
		} //equals
		else {
			return updateHeights(rem_node(current)); //remove that node and update heights
			//also handles rotations required
			//rem_node is a static function in TreeNode struct
		}
	}    
	return false; //did not find node to remove
}

//removes the node, and returns the node that was above it
TreeNode* AVLTree::rem_node(TreeNode* node){ //helper function to remove a node, and return the parent leaf
    if (node->parent!=nullptr){ //when not root
		TreeNode* theparent = node->parent;
        if (node->left==nullptr&&node->right==nullptr){ //no children
            if(node->parent->left==node) updateAVLParentChild(nullptr,node->parent,true);
            else updateAVLParentChild(nullptr,node->parent,false);
			delete node;
			return theparent;
        }
        //one child
        else if (node->left==nullptr){ 
            if(node->parent->left==node) updateAVLParentChild(node->right,node->parent,true);
            else updateAVLParentChild(node->right,node->parent,false);
			delete node;
			return theparent;
        }
        else if(node->right==nullptr){
			if(node->parent->left==node) updateAVLParentChild(node->left,node->parent,true);
            else updateAVLParentChild(node->left,node->parent,false);
			delete node;
			return theparent;
        }

    }
    
    //both children present
    TreeNode* successor=node->right; //find the successor below, first move to right subtree
    if (successor!=nullptr){ 
		for(;successor->left!=nullptr;successor=successor->left){}//travel through each left child
		*node=*successor; //move successor data to node
        return(rem_node(successor));//delete successor -> will be done within the first part of the function
    }
	return nullptr;
    
}
	