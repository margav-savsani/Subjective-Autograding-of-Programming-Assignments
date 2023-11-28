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

  if(find(JourneyCode)){		//If element already present, return false
		return false;
	}
	else if ( root == nullptr ){		//If BST is empty, assign the root
		root = new struct TreeNode (JourneyCode, price);
		this->updateLength();
		return true;
	}	
	else{								//For general case, find the appropriate place to insert
		TreeNode *x = root;
		TreeNode *y = nullptr;
		while(1){
			if ( x == nullptr ){
				break;
			}
			y = new struct TreeNode ();
                        y = x;
			if ( price < x->price ){
				x = x->left;
			}
			else{
				x = x->right;
			}

		}
		if ( price < y->price ){			//Insert the Node
			y->left = new struct TreeNode(JourneyCode,price);
			y->left->parent = new struct TreeNode();
			y->left->parent = y;
		}
		else{								//Insert the Node
			y->right = new struct TreeNode(JourneyCode, price);
			y->right->parent = new struct TreeNode();
			y->right->parent = y;
		}
	//Update the path lenghts
	this->updateLength();
	return true;
	}

  return true;
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

  TreeNode *x = root;
	while(1){
		if ( x == nullptr ){
			return false;
		}
		else if ( price < x->price ){
			x = x->left;
		}
		else if ( price > x->price ){
			x = x->right;
		}
		else if ( price == x->price && JourneyCode==x->JourneyCode){
			return true;
		}
		else if ( price == x->price && JourneyCode!=x->JourneyCode){
			x = x->right;
		}
		else{
			return false;
		}
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

  if (find(JourneyCode, price)){
		//If found, we delete it				
		TreeNode *x = root;
        	TreeNode *y = nullptr;
                while(1){
                        if ( x->price == price && x->JourneyCode == JourneyCode){
                                break;
                        }
                        y = new struct TreeNode ();
                        y = x;
                        if ( price < x->price ){
                                x = x->left;
                        }
                        else{
                                x = x->right;
                        }
                }
		
		if ( x->left == nullptr && x->right == nullptr ){		//no child
			if (y==nullptr){
				delete root;
				root = nullptr;
			}
			else if( y->right == x ){
                		y->right == nullptr;
            		}
			else if(y->left == x) {
                		y->left == nullptr;
            		}
			x = nullptr;
        	}
		else if ( (x->left==nullptr) && (x->right!=nullptr) ){		//one child
			if(y == nullptr){
				root = x->right;
				root->parent = nullptr;
			}
			else if(y->left==x){									//one child
                	y->left = x->right;
                	(x->right)->parent = y;
            		}
			else if(y->right==x){									//one child
                	y->right = x->right;
                	(x->right)->parent = y;
            		}

        	}

		else if ( (x->right==nullptr) && (x->left!=nullptr) ){		//one child
			if(y == nullptr){
                                root = x->left;
                                root->parent = nullptr;
                        }	
			else if(y->right==x){									//one child
                		y->right = x->left;
                		(x->left)->parent = y;
            		}
			else if(y->left==x){									//one child
                		y->left = x->left;
                		(x->left)->parent = y;
            		}

        	}
		else{
			TreeNode *rm = x;										//two children
			if (rm->right->left==nullptr){
				if (rm->right->right==nullptr){
					rm->price = rm->right->price;
					rm->JourneyCode = rm->right->JourneyCode;
					rm->right = nullptr;
				}
				else{
					rm->price = rm->right->price;
					rm->JourneyCode = rm->right->JourneyCode;
					rm->right = rm->right->right;
					rm->right->parent = rm;
					
				}
			}
			else{
				TreeNode *b = x;
				TreeNode *a = x->right;
				while(a->left!=nullptr){
					b = a;
					a = a->left;
				}
				int JC = a->JourneyCode;
				int pc = a->price;
				BST S(x);
				S.remove(JC,pc);
				rm->JourneyCode = JC;
				rm->price = pc;
			}
		}
		return true;
		
	}
	else{										//If not found, returns false
		return false;
	}

  return true;
}


