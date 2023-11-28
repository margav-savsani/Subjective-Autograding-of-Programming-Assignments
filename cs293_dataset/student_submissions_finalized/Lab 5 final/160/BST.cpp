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

bool BST::insert(int jrnyCode, int price)
{
  // Implement insertion in BST

  // You MUST use only BSTLessThan to compare two journey codes.  You
  // can create a new node containing the journey code to be inserted
  // and invoke BSTLessThan on the current node in the tree that you
  // are inspecting and the new node to do your comparison.

  // REMEMBER to update the heights of appropriate nodes in the tree
  // after an insertion.
  
  // We use "return true" below to enable compilation.  Change this as you
  // see fit.
  
	TreeNode* insnode=new TreeNode(jrnyCode,price);
	if(root==NULL){
		root=insnode;
		return true;
	}
	else{
		TreeNode *prev=NULL;
		TreeNode *temp=root;
		while(temp!=NULL){
			if(BSTLessThan(insnode,temp)){
				prev=temp;
				temp=temp->left;
			}
			else if(BSTLessThan(temp,insnode)){
				prev=temp;
				temp=temp->right;
			}
		}
		if (BSTLessThan(insnode,prev)) {updateBSTParentChild(insnode, prev, true);}//prev->left =insnode;(prev->left)->parent=prev;}
		else {updateBSTParentChild(insnode, prev, false);}//prev->right =insnode;(prev->right)->parent=prev;}
		height(root);
		return true;
	}
}

// Returns the price on finding an element in the BST that matches
// journey code. Returns -1 otherwise.
// You may assume that no two node in the tree have the same journey
// code, and journey code is the key for insertion and finding in the BST

int BST::find(int jrnyCode)
{
  // Implement find in BST

  // You MUST use only BSTLessThan to compare two journey codes.  You
  // can create a new node containing the journey code to be searched
  // (along with some arbitrary price) and invoke BSTLessThan on the
  // current node in the tree that you are inspecting and the new node
  // to do your comparison.

  // We use "return -1" below to enable compilation.  Change this as you
  // see fit.
  	TreeNode* insnode=new TreeNode(jrnyCode,100);
	if(root==NULL) return -1;
	if((!BSTLessThan(insnode,root))&&(!BSTLessThan(root,insnode))) return root->printprice();
	TreeNode *prev=NULL;
	TreeNode *temp=root;
	while(temp!=NULL){
		if(BSTLessThan(insnode,temp)){
			prev=temp;
			temp=temp->left;
		}
		else if(BSTLessThan(temp,insnode)){
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

// Returns true on successful deletion of the entry in BST with
// matching journey code. Returns false if it cannot find any such element.
//
// You may assume that no two elements in the BST have the same journey
// code, and journey code is the key for insertion and finding in the BST.

bool BST::remove(int jrnyCode)
{
  // Implement deletion in BST
  
  // You MUST use only BSTLessThan to compare two journey codes.  You
  // can create a new node containing the journey code to be searched
  // (along with some arbitrary price) and invoke BSTLessThan on the
  // current node in the tree that you are inspecting and the new node
  // to do your comparison.

  // REMEMBER to update the height of appropriate nodes in the tree
  // after a successful deletion.
  
  // We use "return true" below to enable compilation.  Change this as you
  // see fit.

    //if(find(jrnyCode)==-1) return false;
    //root=deleteNode(root,jrnyCode);
//return true;
  // Returning false, if the node doesn't exist!
    if(find(jrnyCode)==-1)return false;
    
    TreeNode* curr = root;
    bool last = false;
	TreeNode* dnode=new TreeNode(jrnyCode,100);
    // finding the  node to be deleted
    while(true){
         // Decrement size of subtree for each parent node!
        if(BSTLessThan(dnode,curr)){
        	curr = curr->left;
        	last = true;
        }
        else if(BSTLessThan(curr,dnode)){
        	curr = curr->right;
        	last = false;
        }
        else break;
    }
    // If it has no left child, just replace the node with its right child!
    if(curr->left==NULL){
    
        if(curr->parent!=NULL){
            /*if(last){
                curr->parent->left = curr->right;
            }else{
                curr->parent->right = curr->right;
            }*/
            updateBSTParentChild(curr->right,curr->parent,last);
            if(curr->right!=NULL){
                curr->right->parent = curr->parent;
            }
            delete curr;
        }else{
            root = curr->right;
            delete curr;  
        }
    }else if(curr->right==NULL){
        //   If it has no right child, just replace it with left child
        if(curr->parent!=NULL){
            /*if(last){
                curr->parent->left = curr->left;
            }else{
                curr->parent->right = curr->left;
            }*/
            updateBSTParentChild(curr->left,curr->parent,last);
            curr->left->parent = curr->parent;
            
            delete curr;
        }else{
            root = curr->left;
            delete curr;     
        }
    }else{
        // If its has both left and right children

        TreeNode *todel = curr; // Marking the node which is to be deleted
        
        // Find its predecessor
        curr = curr->left;
        last = false;
        
        
        while(curr->right!=NULL){
            
            curr = curr->right;
            last = true;
        }

        // Swap the node with its predecessor
        //todel->JourneyCode = curr->JourneyCode;
        //todel->price = curr->price;
        todel->modify(curr->printcode(),curr->printprice());
        /*if(!last){
            curr->parent->left = curr->left;
        }else{
            curr->parent->right = curr->left;
        }*/
        updateBSTParentChild(curr->left,curr->parent,!last);
        if(curr->left!=NULL)curr->left->parent = curr->parent;
        
        // Delete the node which previously represented the predecessor
        delete curr;
        
    }
  height(root);
    return true;
}


