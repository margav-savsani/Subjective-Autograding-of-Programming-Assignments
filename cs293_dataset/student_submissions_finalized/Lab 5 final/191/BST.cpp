#ifndef BST_H
#include "BST.h"
#endif

#ifndef STD_HEADERS
#include <iostream>
#include <stdlib.h>
#endif


// Returns true on successful insertion in BST. Returns false otherwise.
// You may assume that no two elements being inserted have the same journey
// code, and journey code is the key for insertion and finding in the BST

//insert method to insert in the BST a TreeNode object 
bool BST::insert(int jrnyCode, int price)
{
	//find if a node exists with given jrnyCode. 
	//If it does, return false indicating no insertion 
	if(find(jrnyCode)!=-1){
		return false;
	}
	
	TreeNode *ptr=new TreeNode(jrnyCode, price);//the node to be inserted
	if(root==nullptr){//checking the case where the tree is empty
		root=ptr;
		return true;
	}
	
	
	TreeNode* p=root;
	
	while(true){
		if(BSTLessThan(p, ptr)){
			if(p->right==nullptr){
				updateBSTParentChild(ptr, p, false);
				break;
			}
			else{
				p=p->right;
			}
		}
		else{
			if(p->left==nullptr){
				updateBSTParentChild(ptr, p, true);
				break;
			}
			else{
				p=p->left;
			}
		}
	}
	//updates the height attributes of all the nodes whose height attirbutes may have changed 
	update_height(p);
	return true;
	
}

// Returns the price on finding an element in the BST that matches
// journey code. Returns -1 otherwise.

int BST::find(int jrnyCode)
{
  //calls the myfind member method which finds the required object, returns the pointer to the object if found, returns nullptr otherwise
  TreeNode *ptr=myfind(jrnyCode);
  if(ptr==nullptr)
  	return -1;
  else{
  	return ptr->getPrice();
  }
}

//myfind member method finds the required object, returns the pointer to the object if found, returns nullptr otherwise
TreeNode* BST::myfind(int jrnyCode){
	TreeNode *p=new TreeNode(jrnyCode, 0);
	TreeNode *ptr=root;
	while(ptr!=nullptr){
		if(BSTLessThan(ptr, p))
			ptr=ptr->right;
		else if(BSTLessThan(p, ptr))
			ptr=ptr->left;
		else
			return ptr;
	}
	return nullptr;
}

//update the height attributes of the TreeNode objects from the ptr given to the root of the tree
void BST::update_height(TreeNode *ptr){
	if(ptr==nullptr)//base case for stop of recursion 
		return;
	int h=ptr->height;
	int right,left;
	if(ptr->right==nullptr)right=0;
	else right=ptr->right->height+1;
	if(ptr->left==nullptr)left=0;
	else left=ptr->left->height+1;
	
	ptr->height=max(right, left);
	if(h==ptr->height)
		return;//stops the recusrion since we now know that no height attributes have changed from this ptr to root of the tree
	else{
		update_height(ptr->parent);//recursion 
	}
	ptr->h_diff=abs(right-left);
}
// =====================================================
// OPTIONAL: Implement "remove" only for bonus marks
// =====================================================


// Returns true on successful deletion of the entry in BST with matching journey code. Returns false if it cannot find any such element.
bool BST::remove(int jrnyCode)
{
	TreeNode *ptr=myfind(jrnyCode);
	if(ptr==nullptr)return false;//if ptr is not found return false implying that the object to be deleted is not found
	else{
		//case 0:with no children, i.e. deleting a leaf node
		if(ptr->right==nullptr && ptr->left==nullptr){
			if(ptr->parent==nullptr){
				root=nullptr;
			}
			else{
				if(ptr->parent->right==ptr)
					updateBSTParentChild(nullptr, ptr->parent, false);
				else
					updateBSTParentChild(nullptr, ptr->parent, true);
				//updating the height attributes of the tree after deletion
				update_height(ptr->parent);
			}
		}//case 1:with 1 child, i.e., deleting a node with only one child
	//We do it in two cases, the object to be deleted has right child pointer as nullptr or the object to be deleted has the left child as nullptr.
		else if(ptr->right==nullptr){
			if(ptr->parent==nullptr){
				updateBSTParentChild(ptr->left, nullptr, true);
				root = ptr->left;
			}
			else{
				if(ptr->parent->left==ptr)
					updateBSTParentChild(ptr->left, ptr->parent, true);
				else
					updateBSTParentChild(ptr->left, ptr->parent, false);
				//updating the height attributes of the tree after deletion
				update_height(ptr->parent);
			}
		}
		else if(ptr->left==nullptr){
			if(ptr->parent==nullptr){
				updateBSTParentChild(ptr->right, nullptr, false);
				root=ptr->right;
			}
			else{
				if(ptr->parent->left==ptr)
					updateBSTParentChild(ptr->right, ptr->parent, true);
				else
					updateBSTParentChild(ptr->right, ptr->parent, false);
			}
			//updating the height attributes of the tree after deletion
			update_height(ptr->parent);
		}//case 2:with 2 children, i.e., deleting the tree node with two children, i.e. none of right/left has value equal to nullptr.
		else{
			TreeNode *update_ptr;
			TreeNode *p=getMaxNode(ptr->left);
			if(p->parent==ptr)update_ptr=p;
			else update_ptr=p->parent;
			if(p->parent->right==p)
				updateBSTParentChild(p->left, p->parent, false);
			else
				updateBSTParentChild(p->left, p->parent, true);
			
			if(ptr->parent==nullptr){
				root=p;
				updateBSTParentChild(p, nullptr, 0);
			}
			else{
				if(ptr->parent->right==ptr)
					updateBSTParentChild(p, ptr->parent, false);
				else
					updateBSTParentChild(p, ptr->parent, true);
			}
			updateBSTParentChild(ptr->right, p, false);
			updateBSTParentChild(ptr->left, p, true);
			//updating the height attributes of the tree after deletion
			update_height(update_ptr);	
		}
		
		//freeing the space that the deleted object took
		delete ptr;
		ptr=nullptr;
		return true;
	}

}

//getMaxNode returns the node (with maximum JoureyCode) of the tree/subtree rooted at ptr 
TreeNode * BST::getMaxNode(TreeNode* ptr){
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

