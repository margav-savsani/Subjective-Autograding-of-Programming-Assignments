#ifndef AVL_H
#include "AVL.h"
#endif

#ifndef STD_HEADERS
#include <iostream>
#include <stdlib.h>
#endif

// Left Left Case
bool AVLTree :: rotateLeftLeft(TreeNode *currNode, TreeNode *parentNode, TreeNode *grandParentNode){
	TreeNode *greatGrandParentNode = grandParentNode->parent;
	if(greatGrandParentNode != NULL){
		bool isGPLeftChild;
		if(greatGrandParentNode->left == grandParentNode){
			isGPLeftChild = true;
		}
		else if(greatGrandParentNode->right == grandParentNode){
			isGPLeftChild = false;
		}
		else{
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
	else{
		root = parentNode;
		root->parent = NULL;
		TreeNode* T1 = parentNode->right;
		updateAVLParentChild(grandParentNode, parentNode, false);
		updateAVLParentChild(T1, grandParentNode, true);
		return true;
	}
}

// Left Right Case
bool AVLTree :: rotateLeftRight(TreeNode *currNode, TreeNode *parentNode, TreeNode *grandParentNode){
	TreeNode *greatGrandParentNode = grandParentNode->parent;
	if(greatGrandParentNode != NULL){
		bool isGPLeftChild;
		if(greatGrandParentNode->left == grandParentNode){
			isGPLeftChild = true;
		}
		else if(greatGrandParentNode->right == grandParentNode){
			isGPLeftChild = false;
		}
		else{
			cerr << "Unexpected condition encountered!" << endl;
			return false;
		}
		TreeNode *T2 = currNode->left;
		TreeNode *T3 = currNode->right;
		updateAVLParentChild(currNode, greatGrandParentNode, isGPLeftChild);
		updateAVLParentChild(parentNode, currNode, true);
		updateAVLParentChild(grandParentNode, currNode, false);
		updateAVLParentChild(T2, parentNode, false);
		updateAVLParentChild(T3, grandParentNode, true);
		return true;
	}
	else{
		root=currNode;
		root->parent=nullptr;
		TreeNode* T2=currNode->left;
		TreeNode* T3=currNode->right;
		updateAVLParentChild(parentNode,currNode,true);
		updateAVLParentChild(grandParentNode,currNode,false);
		updateAVLParentChild(T2,parentNode,false);
		updateAVLParentChild(T3,grandParentNode,true);
		return true;
	}
}

// Right Left Case
bool AVLTree :: rotateRightLeft(TreeNode *currNode, TreeNode *parentNode, TreeNode *grandParentNode){
	TreeNode *greatGrandParentNode = grandParentNode->parent;
	if(greatGrandParentNode != NULL){
		bool isGPLeftChild;
		if(greatGrandParentNode->right == grandParentNode){
			isGPLeftChild = true;
		}
		else if(greatGrandParentNode->left == grandParentNode){
			isGPLeftChild = false;
		}
		else{
			cerr << "Unexpected condition encountered!" << endl;
			return false;
		}
		TreeNode *T2 = currNode->left;
		TreeNode *T3 = currNode->right;
		updateAVLParentChild(currNode, greatGrandParentNode, isGPLeftChild);
		updateAVLParentChild(parentNode, currNode, false);
		updateAVLParentChild(grandParentNode, currNode, true);
		updateAVLParentChild(T2, grandParentNode, false);	////////
		updateAVLParentChild(T3, parentNode, true);
		return true;
	}
	else{
		root=currNode;
		root->parent=nullptr;
		TreeNode* T2=currNode->left;
		TreeNode* T3=currNode->right;
		updateAVLParentChild(parentNode,currNode,false);
		updateAVLParentChild(grandParentNode,currNode,true);
		updateAVLParentChild(T2,grandParentNode,false);
		updateAVLParentChild(T3,parentNode,true);
		return true;
	}
}

// Right Right Case
bool AVLTree :: rotateRightRight(TreeNode *currNode, TreeNode *parentNode, TreeNode *grandParentNode){
	TreeNode *greatGrandParentNode = grandParentNode->parent;
	if(greatGrandParentNode != NULL){
		bool isGPLeftChild;
		if(greatGrandParentNode->left == grandParentNode){
			isGPLeftChild = true;
		}
		else if(greatGrandParentNode->right == grandParentNode){
			isGPLeftChild = false;
		}
		else{
			cerr << "Unexpected condition encountered!" << endl;
			return false;
		}
		TreeNode *T3 = parentNode->left;
		updateAVLParentChild(parentNode, greatGrandParentNode, isGPLeftChild);
		updateAVLParentChild(currNode, parentNode, false);
		updateAVLParentChild(grandParentNode, parentNode, true);
		updateAVLParentChild(T3, grandParentNode, false);
		return true;
	}
	else{
		root=parentNode;
		root->parent=nullptr;
		TreeNode* T1=parentNode->left;
		updateAVLParentChild(grandParentNode,parentNode,true);
		updateAVLParentChild(T1,grandParentNode,false);
		return true;
	}
}

// Checking Imbalance
int AVLTree :: getbalance(TreeNode* t){
	if(t == NULL){
		return 0;
	}
	return t->left->height - t->right->height;
}

bool AVLTree :: insert(int jrnyCode, int price){
	TreeNode *i = new TreeNode(jrnyCode, price);
	if(find(jrnyCode) != -1){
    	return false;
    }
	if(root == NULL){
		root = new TreeNode(jrnyCode, price);
		return true;
	}
	TreeNode *curr = root;
	while(true){
		if(jrnyCode < curr->JC()){
			if(curr->left != NULL){
				curr = curr->left;
			}else{
				curr->left = new TreeNode(jrnyCode, price);
				curr->left->parent = curr;
				break;
			}
		}
		else{
			if(curr->right != NULL){
				curr = curr->right;
			}else{
				curr->right = new TreeNode(jrnyCode, price);
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

	curr = n;
	TreeNode* Parent = curr->parent;
	TreeNode* grandParent = Parent->parent;
	while(Parent != NULL && grandParent !=NULL){
		if(getbalance(grandParent)==2 || getbalance(grandParent)== -2){
			TreeNode* t = grandParent->parent;
			t->height = t->height - 1;
			while(t->parent != nullptr){
				t->parent->height = t->parent->height - 1;
				t->parent = t->parent->parent;
			}
			if(grandParent->left == Parent && Parent->left == curr){
				rotateLeftLeft(curr, Parent, grandParent);
				grandParent->height = grandParent->height - 2;
				break;
			}
			if(grandParent->left == Parent && Parent->right == curr){
				rotateLeftRight(curr, Parent, grandParent);
				curr->height = curr->height + 1;
            	Parent->height = Parent->height - 1;
                grandParent->height = grandParent->height - 2;
				break;
			}
			if(grandParent->right == Parent && Parent->left == curr){
				rotateRightLeft(curr, Parent, grandParent);
				curr->height = curr->height + 1;
                Parent->height = Parent->height - 1;
                grandParent->height = grandParent->height - 2;
				break;
			}
			if(grandParent->right == Parent && Parent->right == curr){
				rotateRightRight(curr, Parent, grandParent);
				grandParent->height = grandParent->height - 2;
				break;
			}
		}
		curr = Parent;
		Parent = grandParent;
		grandParent = grandParent->parent;
	}

	return true;
}

TreeNode* AVLTree :: search(TreeNode* r, int jc){
	if (r == NULL || r->JC() == jc)
       return r;
    
    // Key is greater than root's key
    if (r->JC() < jc)
       return search(r->right, jc);
 
    // Key is smaller than root's key
    return search(r->left, jc);
}


int AVLTree :: find(int jrnyCode){
	TreeNode *j = new TreeNode(jrnyCode, 0);
	if(root==NULL){
		return -1;
	}
	TreeNode* curr = root;
	while(true){
		if(curr->JC() == jrnyCode){
			return 0;
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

// Returns true on successful deletion of the entry in AVL tree with
// matching journey code. Returns false if it cannot find any such element.
//
// You may assume that no two elements in the AVL tree have the same journey
// code, and journey code is the key for insertion and finding in the AVL
// tree.

TreeNode* AVLTree :: min(TreeNode *n){
    while(n->left != NULL){
        n = n->left;
    }
    return n;
}

TreeNode* AVLTree :: del(TreeNode *r, int jc){
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

bool AVLTree::remove(int jrnyCode){
  if( find(jrnyCode) == -1 ){
        return false;
    }
    else{
        root = del(root,jrnyCode);
    }
    return true;
}
