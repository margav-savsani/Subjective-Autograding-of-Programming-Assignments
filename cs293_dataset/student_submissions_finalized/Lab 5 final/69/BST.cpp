#ifndef BST_H
#include "BST.h"
#endif

#ifndef STD_HEADERS
#include <iostream>
#include <stdlib.h>
#endif

int BST :: max(int a, int b){
    if(a>b){
        return a;
    }
    else if(a<b){
        return b;
    }
    else
        return a;
}

// Returns true on successful insertion in BST. Returns false otherwise.
// You may assume that no two elements being inserted have the same journey
// code, and journey code is the key for insertion and finding in the BST

TreeNode* BST :: search(TreeNode* r, int jc){
	if(r == NULL || r->JC() == jc)
       return r;
    
    // Key is greater than root's key
    // Here I use this because if I use BSTLessThan, it will unneccessarily increase cost
    if(r->JC() < jc)
       return search(r->right, jc);
 
    // Key is smaller than root's key
    return search(r->left, jc);
}

bool BST :: insert(int jrnyCode, int price){
	TreeNode *i = new TreeNode(jrnyCode, price);
	if(root == NULL){
		root = new TreeNode(jrnyCode, price);
		return true;
	}
    // Checking if similar node already exists
	TreeNode *curr = root;
	while(true){
		// incrementing Size of subtree which is rooted at this node
        // jrnyCode < curr->JC()
		if(BSTLessThan(i,curr)){
			if(curr->left != NULL){
				curr = curr->left;
			}else{
				curr->left = i;
				curr->left->parent = curr;
				break;
			}
		}
		else{
			if(curr->right != NULL){
				curr = curr->right;
			}else{
				curr->right = i;
				curr->right->parent = curr;
				break;
			}
		}
	}
	
	TreeNode* n = search(root, jrnyCode);
    if(n->parent != NULL){
        TreeNode* p = n->parent;
        while(p != NULL){
            if(p->left == NULL){
                p->height = max(0, p->right->height) + 1;
            }
            else if(p->right == NULL){
                p->height = max(p->left->height, 0) + 1;
            }
            else{
                p->height = max(p->left->height, p->right->height) + 1;
            }
            p = p->parent;          
        }
    }
	return true;
}

// Returns the price on finding an element in the BST that matches
// journey code. Returns -1 otherwise.
// You may assume that no two node in the tree have the same journey
// code, and journey code is the key for insertion and finding in the BST

int BST :: find(int jrnyCode){
	TreeNode *j = new TreeNode(jrnyCode, 0);
	if(root==NULL){
		return -1;
	}
	TreeNode* curr = root;
	while(true){
		if(curr->JC() == jrnyCode){
			return curr->PC();
		}else if(jrnyCode < curr->JC()){
			if(curr->left == NULL){
				return -1;
			}else{
				curr = curr->left;
			}
		}else{
			if(curr->right == NULL){
				return -1;
			}else{
				curr = curr->right;
			}
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

TreeNode* BST :: min(TreeNode *n){
    while(n->left != NULL){
        n = n->left;
    }
    return n;
}

TreeNode* BST :: del(TreeNode *r, int jc){
    if(r == NULL){
        return r;
    }
    if(jc < r->JC()){
        r->left = del(r->left, jc);
    }
    else if(jc > r->JC()){
        r->right = del(r->right, jc);
    }
    else{
        if(r->left == NULL && r->right == NULL){
            return NULL;
        }
        else if(r->left == NULL){
            TreeNode *temp = r->right;
            free(r);
            return temp;
        }
        else if(r->right == NULL){
            TreeNode *temp = r->left;
            free(r);
            return temp;
        }
        else if(r->left != NULL && r->right != NULL){
            TreeNode *temp = min(r->right);
            r->jc(temp->JC());
            r->pc(temp->PC());
            r->height = temp->height;
            r->right = del(r->right, temp->JC());
        }
    }
    return r;
}

bool BST :: remove(int jrnyCode){
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

    if(find(jrnyCode) == -1){
        return false;
    }
    else{
        root = del(root,jrnyCode);
    }
    return true;
}