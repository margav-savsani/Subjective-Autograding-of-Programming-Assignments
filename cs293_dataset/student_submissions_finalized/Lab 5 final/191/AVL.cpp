#ifndef AVL_H
#include "AVL.h"
#endif

#ifndef STD_HEADERS
#include <iostream>
#include <stdlib.h>
#endif


//given a grandparent node whose left child is the parent node and currNode is the left child of the parent node, this function rotates this combination and brings parent node to the top(of grandparent and child node)
bool AVLTree::rotateLeftLeft(TreeNode *currNode, TreeNode *parentNode, TreeNode *grandParentNode)
{
  TreeNode *greatGrandParentNode = grandParentNode->parent;
  
  //if greatGrandParentNode is a nullptr that means that grandparent node was the root of the AVL tree and which in turn means that the parent node after rotation will become the root of the parent tree 
  if(greatGrandParentNode !=nullptr){
	  bool isGPLeftChild;
	  //finding whether the grandParentNode is the left or right child of greatGrandParentNode
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
	  //make the greatGrandParentNode as the parent of parentNode in place of grandParentNode
	  updateAVLParentChild(parentNode, greatGrandParentNode, isGPLeftChild);
	  //make the grandParentNode the child of parent node parent node as the parent of grandparent node
	  updateAVLParentChild(grandParentNode, parentNode, false);
	  //make the initial right child of parent node the left child of grandParentNode
	  updateAVLParentChild(T3, grandParentNode, true);
  }
  else{
  	  TreeNode *T3 = parentNode->right;
      root=parentNode;
      updateAVLParentChild(parentNode, nullptr, 0); // make parentNode->parent as nullptr
      updateAVLParentChild(grandParentNode, parentNode, false);//make grandParentNode the child of parentNode and ParentNode the parent of grandParentNode
	  updateAVLParentChild(T3, grandParentNode, true);//make the initial right child of parent node the left child of grandParentNode
  }

  return true;
}

//given a grandparent node whose left child is the parent node and currNode is the right child of the parent node, this function rotates this combination and brings currNode to the top(of grandparent and parentnode)
bool AVLTree::rotateLeftRight(TreeNode *currNode, TreeNode *parentNode, TreeNode *grandParentNode)
{
	//make the currNode the parent of parentNode and parentNode as the left child of the currNode
 	updateAVLParentChild(currNode, grandParentNode, 1);
 	updateAVLParentChild(currNode->left, parentNode, 0);
 	updateAVLParentChild(parentNode, currNode, 1);
 	//now grandparentnode has left child as currNode whose left child is the parentNode and hence we call rotateLeftLeft function already created
 	rotateLeftLeft(parentNode, currNode, grandParentNode);
 	return true;
}

//given a grandparent node whose right child is the parent node and currNode is the left child of the parent node, this function rotates this combination and brings currNode to the top(of grandparent and parent node)
bool AVLTree::rotateRightLeft(TreeNode *currNode, TreeNode *parent, TreeNode *grandParent)
{
	//make the currNode the parent of parentNode and parentNode as the right child of the currNode
	updateAVLParentChild(currNode, grandParent, 0);
 	updateAVLParentChild(currNode->right, parent, 1);
 	updateAVLParentChild(parent, currNode, 0);
 	//now grandparentnode has right child as currNode whose right child is the parentNode and hence we call rotateRightRight function already created
 	rotateRightRight(parent, currNode, grandParent);
	return true;
}

//given a grandparent node whose right child is the parent node and currNode is the right child of the parent node, this function rotates this combination and brings parent node to the top(of grandparent and child node)
bool AVLTree::rotateRightRight(TreeNode *currNode, TreeNode *parentNode, TreeNode *grandParentNode)
{
	TreeNode *greatGrandParentNode = grandParentNode->parent;
  	//finding whether the grandParentNode is the left or right child of greatGrandParentNode
	if(greatGrandParentNode !=nullptr){
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
	  
	  TreeNode *T3 = parentNode->left;
	  //make the greatGrandParentNode as the parent of parentNode in place of grandParentNode
	  updateAVLParentChild(parentNode, greatGrandParentNode, isGPLeftChild);
	  //make the grandParentNode the child of parent node parent node as the parent of grandparent node
	  updateAVLParentChild(grandParentNode, parentNode, true);
	  //make the initial left child of parent node the right child of grandParentNode
	  updateAVLParentChild(T3, grandParentNode, false);
	}
	else{
	  root=parentNode;
	  TreeNode *T3 = parentNode->left;
	  updateAVLParentChild(parentNode, nullptr, 1);// make parentNode->parent as nullptr
	  updateAVLParentChild(grandParentNode, parentNode, true);//make grandParentNode the child of parentNode and ParentNode the parent of grandParentNode
	  updateAVLParentChild(T3, grandParentNode, false);//make the initial left child of parent node the right child of grandParentNode
	}  
	return true;
}

//whenever the user has to call a member method to insert an element in an AVL tree, he/she calls this method
bool AVLTree::insert(int jrnyCode, int price)
{
	if(find(jrnyCode)!=-1){
		return false;//if jrnyCode is already present return false,meaning that insertion hasn;t happened
	}
	
	TreeNode *ptr=new TreeNode(jrnyCode, price);//the ptr to be inserted 
	if(root==nullptr){//checking the corner case which is a an empty tree
		root=ptr;
		return true;
	}
	
	TreeNode* p=root;
	//We find the place where ptr should be placed for the simple BST Tree 
	//After placing there, we look for any position in the tree where condition for AVL Tree is unsatisfied and remove it, by calling avl_insert member method
	while(true){
		if(AVLLessThan(p, ptr)){
			if(p->right==nullptr){
				updateAVLParentChild(ptr, p, false);
				break;
			}
			else{
				p=p->right;
			}
		}
		else{
			if(p->left==nullptr){
				updateAVLParentChild(ptr, p, true);
				break;
			}
			else{
				p=p->left;
			}
		}
	}
	update_height(p,1);//update the height of every node from p to root as only these nodes can have change in height
	avl_insert(ptr);
	return true;
}

//checks for imbalance and corrects it and makes it an AVL Tree again
void AVLTree::avl_insert(TreeNode* ptr){
	TreeNode *parent=ptr->parent;
	TreeNode *grandparent=parent->parent;
	if(grandparent == nullptr)
		return;//base case for stopping recursion
	
	//condition for imbalance
	if(grandparent->h_diff!=0 && grandparent->h_diff!=1){
		//appropriate rotate functions called
		if(grandparent->left==parent && parent->left==ptr){
			rotateLeftLeft(ptr, parent, grandparent);
		}
		else if(grandparent->right==parent && parent->right==ptr){
			rotateRightRight(ptr, parent, grandparent);
		}
		else if(grandparent->right==parent && parent->left==ptr){
			rotateRightLeft(ptr, parent, grandparent);
		}
		else{
			rotateLeftRight(ptr, parent, grandparent);
		}
		//After correcting the imbalance of the tree, updates the height properties of all the nodes lying in the path from the root this imbalance position
		update_height(grandparent, 0);
		update_height(ptr, 0);
		update_height(parent, 1);
	}
	else{
		avl_insert(ptr->parent);//recursion
	}
}

//updates height attributes of the nodes of the tree where a change in height is anticipated 
void AVLTree::update_height(TreeNode *ptr, bool recur){ // recur is the flag used to know whether we want to update the hieght properties of only the given node or all nodes from the given node to the root node.
	if(ptr==nullptr)
		return;
	int h=ptr->height;
	int right,left;
	if(ptr->right==nullptr)right=0;//base case when right child is nullptr
	else right=ptr->right->height+1;
	if(ptr->left==nullptr)left=0;//base case when the left child is nullptr
	else left=ptr->left->height+1;
	ptr->h_diff=abs(right-left);
	ptr->height=max(right, left);
	if(h==ptr->height)
		return;
	else{
		if(recur)
			update_height(ptr->parent, 1);
		else
			return;
	}
}
// Returns the price on finding an element in the AVL tree that matches
// journey code. Returns -1 otherwise.
// You may assume that no two node in the tree have the same journey
// code, and journey code is the key for insertion and finding in the AVL
// tree.

//find function
int AVLTree::find(int jrnyCode)
{
  TreeNode *ptr=myfind(jrnyCode);//calls myfind function which returns the pointer to the object if found or else nullptr
  if(ptr==nullptr)
  	return -1;
  else{
  	return ptr->getPrice();
  }
}

//myfind function which is responsible for finding the object with the given JourneyCode. If found return the pointer the repsective object, else return nullptr.
TreeNode* AVLTree::myfind(int jrnyCode){
	TreeNode *p=new TreeNode(jrnyCode, 0);
	TreeNode *ptr=root;
	while(ptr!=nullptr){
		if(AVLLessThan(ptr, p))
			ptr=ptr->right;
		else if(AVLLessThan(p, ptr))
			ptr=ptr->left;
		else
			return ptr;
	}
	return nullptr;
}


// =====================================================
// OPTIONAL: Implement "remove" only for bonus marks
// =====================================================

// Returns true on successful deletion of the entry in AVL tree with matching journey code. Returns false if it cannot find any such element.
bool AVLTree::remove(int jrnyCode)
{

	TreeNode* ptr= myfind(jrnyCode);
	if(ptr==nullptr)return false;
	//case 0:with no children, i.e. deleting a leaf node
	if(ptr->right==nullptr && ptr->left==nullptr){
		if(ptr->parent==nullptr){//checking for the case with tree with only one node and deleting that node itself
			root=nullptr;
		}
		else{//general deletion of leaves 
			if(ptr->parent->right==ptr)
				updateAVLParentChild(nullptr, ptr->parent, false);
			else
				updateAVLParentChild(nullptr, ptr->parent, true);
			//updating the height attributes of the tree after deletion
			update_height(ptr->parent, 1);
			avl_delete(ptr->parent);
		}
		
	}//case 1:with 1 child, i.e., deleting a node with only one child
	//We do it in two cases, the object to be deleted has right child pointer as nullptr or the object to be deleted has the left child as nullptr.
	else if(ptr->right==nullptr){
		if(ptr->parent==nullptr){
			updateAVLParentChild(ptr->left, nullptr, true);
			root = ptr->left;
		}
		else{
			if(ptr->parent->left==ptr)
				updateAVLParentChild(ptr->left, ptr->parent, true);
			else
				updateAVLParentChild(ptr->left, ptr->parent, false);
			//updating the height attributes of the tree after deletion
			update_height(ptr->parent, 1);
			avl_delete(ptr->parent);
		}
		
	}
	else if(ptr->left==nullptr){
		if(ptr->parent==nullptr){
			updateAVLParentChild(ptr->right, nullptr, false);
			root=ptr->right;
		}
		else{
			if(ptr->parent->left==ptr)
				updateAVLParentChild(ptr->right, ptr->parent, true);
			else
				updateAVLParentChild(ptr->right, ptr->parent, false);
			//updating the height attributes of the tree after deletion
			update_height(ptr->parent, 1);
			avl_delete(ptr->parent);
		}
		
	}//case 2:with 2 children, i.e., deleting the tree node with two children, i.e. none of right/left has value equal to nullptr.
	else{
		TreeNode *avl_ptr;
		TreeNode *p=getMaxNode(ptr->left);
		if(p->parent==ptr)avl_ptr=p;
		else avl_ptr=p->parent;
		if(p->parent->right==p)
			updateAVLParentChild(p->left, p->parent, false);
		else
			updateAVLParentChild(p->left, p->parent, true);
		
		if(ptr->parent==nullptr){
			root=p;
			updateAVLParentChild(p, nullptr, 0);
		}
		else{
			if(ptr->parent->right==ptr)
				updateAVLParentChild(p, ptr->parent, false);
			else
				updateAVLParentChild(p, ptr->parent, true);
		}
		updateAVLParentChild(ptr->right, p, false);
		updateAVLParentChild(ptr->left, p, true);
		//updating the height attributes of the tree after deletion
		update_height(avl_ptr, 1);	
		avl_delete(avl_ptr);
	}
	
	delete ptr;
	ptr=nullptr;
	return true;
	
}

// Used for balance factor restoration in AVL Tree by properly identifying x, y, z  (equivalently, currNode, parentNode, grandParentNode in our code) and invoking rotateLeftLeft, rotateLeftRight, rotateRightLeft and/or rotateRightRight as appropriate.
void AVLTree::avl_delete(TreeNode *ptr){
	if(ptr==nullptr)return;//base case for stopping recursion 
	//case for imblance in AVL Tree
	else if(ptr->h_diff!=0 && ptr->h_diff!=1){
		TreeNode *child;
		TreeNode *grandchild;
		int right,left;
		if(ptr->right!=nullptr)right=ptr->right->height+1;
		else right=0;
		if(ptr->left!=nullptr)left=ptr->left->height+1;
		else left=0;
		if(right>left)
			child=ptr->right;
		else
			child=ptr->left;
			
		if(child->right!=nullptr)right=child->right->height+1;
		else right=0;
		if(child->left!=nullptr)left=child->left->height+1;
		else left=0;
		if(right>left)
			grandchild=child->right;
		else
			grandchild=child->left;
		
		if(grandchild==child->left && child==ptr->left){
			rotateLeftLeft(grandchild, child, ptr);
		}
		else if(grandchild==child->right && child==ptr->right){
			rotateRightRight(grandchild, child, ptr);
		}
		else if(grandchild==child->right && child==ptr->left){
			rotateLeftRight(grandchild, child, ptr);
		}
		else{
			rotateRightLeft(grandchild, child, ptr);
		}
		//updation of heights after balanace ins restored in AVLTree through required rotations
		update_height(ptr, 0);
		update_height(child, 0);
		update_height(grandchild, 1);	
		avl_delete(child->parent);	
		
	}else{
		avl_delete(ptr->parent);
	}
}

//getMaxNode returns the node (with maximum JoureyCode) of the tree/subtree rooted at ptr 
TreeNode * AVLTree::getMaxNode(TreeNode* ptr){
	while(true){
		if(ptr == nullptr)
			return 0;
		if(ptr->right == nullptr)
			return ptr;
		else{
			ptr = ptr->right;
		}
	}
}

