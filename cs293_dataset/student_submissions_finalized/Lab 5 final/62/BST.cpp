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
bool BST::insert(int JourneyCode, int price)
{
	TreeNode* to_ins = new TreeNode(JourneyCode,price);
	// Implement insertion in BST
	if (root==nullptr){ //insert to empty BST
		root=to_ins;
		return true;
	}
	
	TreeNode* current=root;
	while(current!=nullptr){//travel down the tree
		if (BSTLessThan(to_ins,current)){
			if (current->left==nullptr){ // if reached an empty spot, insert here
					updateBSTParentChild(to_ins,current, true);
					break ;
			}
			current=current->left; //otherwise keep moving
		}
		else { 
			if (current->right==nullptr){ // if reached an empty spot, insert here
					updateBSTParentChild(to_ins,current, false);
					break;
			}
			current=current->right; //otherwise keep moving
		}
	}  
	if (current==nullptr) return false; // a weird scenario
	return updateHeights(current);	//updates the heights
}

// Returns the price on finding an element in the BST that matches
// journey code. Returns -1 otherwise.
// You may assume that no two node in the tree have the same journey
// code, and journey code is the key for insertion and finding in the BST
int BST::find(int JourneyCode)
{
	TreeNode to_find(JourneyCode,-1);
	TreeNode* current=root;
	while(current!=nullptr){  //travelling down the tree      
		if (BSTLessThan(&to_find,current)){ // to_find < current
				current=current->left;
		}
		else if(BSTLessThan(current,&to_find)){
				current=current->right;
		} //equals
		else return (current->getPrice());
	}    
	return (-1); //did not find match
}

//made general enough to apply for both insert and delete
//keep updating the heights from leaf/bottom upward
//when the updated height does not change just exit the function
bool BST::updateHeights(TreeNode* leaf){
	TreeNode* current=leaf;
    for(;current!=nullptr;current=current->parent){
		int to_set;
        if (current->left==nullptr&&current->right==nullptr){ //leaf
            to_set=0;
        }
        //only one child
        else if (current->left==nullptr){
            to_set=(1+ current->right->height);
        }
        else if (current->right==nullptr){
            to_set= 1+ current->left->height;
        }
        //both children present
        else {
            to_set = 1+max(current->right->height,current->left->height);
        }
		//if further updatation not required exit
		if (to_set == current->height) return true;
		current->height = to_set;
    } // otherwise will go on till root
    return true;
}

// =====================================================
// OPTIONAL: Implement "remove" only for bonus marks
// =====================================================

// Returns true on successful deletion of the entry in BST with
// matching journey code. Returns false if it cannot find any such element.
//
// You may assume that no two elements in the BST have the same journey
// code, and journey code is the key for insertion and finding in the BST.

bool BST::remove(int JourneyCode) { 
	TreeNode to_remove=TreeNode(JourneyCode,-1);
    if (root==nullptr) return false;
    //handling the case where root is to be removed
    if (!(BSTLessThan(&to_remove,root)||BSTLessThan(root,&to_remove))){
        if (root->left==nullptr&&root->right==nullptr){ //no children
			delete root;
            root=nullptr;
        } 
        //one child
        else if (root->left==nullptr) { 
            root=root->right;
			delete (root->parent);
			updateBSTParentChild(root,nullptr,0);            
        }
        else if(root->right==nullptr){
            root=root->left;
			delete (root->parent);
            updateBSTParentChild(root,nullptr,0);          
        }
		//both children present
        else{ //rem node function can be called
            rem_node(root);
        }
        return true;
    }
	TreeNode* current=root;
	while(current!=nullptr){  //travelling down the tree      
			if (BSTLessThan(&to_remove,current)){ // to_remove < current
					current=current->left;
			}
			else if(BSTLessThan(current,&to_remove)){
					current=current->right;
			} //equals
			else {
				return updateHeights(rem_node(current)); //remove that node and update heights
			}
		}    
	return false; //did not find node to remove
}

//removes the node, and returns the node that was above it
TreeNode* BST::rem_node(TreeNode* node){ //helper function to remove a node, and return the parent leaf
    if (node->parent!=nullptr){ //when not root
		TreeNode* theparent = node->parent;
        if (node->left==nullptr&&node->right==nullptr){ //no children
            if(node->parent->left==node) updateBSTParentChild(nullptr,node->parent,true);
            else updateBSTParentChild(nullptr,node->parent,false);
			delete node;
			return theparent;
        }
        //one child
        else if (node->left==nullptr){ 
            if(node->parent->left==node) updateBSTParentChild(node->right,node->parent,true);
            else updateBSTParentChild(node->right,node->parent,false);
			delete node;
			return theparent;
        }
        else if(node->right==nullptr){
			if(node->parent->left==node) updateBSTParentChild(node->left,node->parent,true);
            else updateBSTParentChild(node->left,node->parent,false);
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
