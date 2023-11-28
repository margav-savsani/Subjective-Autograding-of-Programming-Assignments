// Code up the functions defined in tree.h
// Reuse the binary Search Tree implemented in lab 3 as much as possible

#include <bits/stdc++.h>
#include <iostream>
#include <vector>
#include <string>
#include "tree.h"

using namespace std;

// PLEASE FILL IN THE BODIES OF THE FOLLOWING FUNCTIONS

int BST :: getImbalance(){
	if(root == nullptr)
		return 0;
	else
		return root->getImbalance();
}

// Returns false, if given JourneyCode is already present in the BST
// Inserts the element and returns True otherwise

bool BST :: insert(int JourneyCode, int price){
	// The following filler code snippet is only given to facilitate
	// compilation.  You should replace/augment it with appropriate code,
	// similar to what you had done in lab assignment 3.

	struct TreeNode *currNode = root, *parentOfCurrNode = nullptr;

	while(currNode != nullptr){
		if(currNode->JourneyCode < JourneyCode){
			parentOfCurrNode = currNode;
			currNode = currNode->right;
		}
		else if(currNode->JourneyCode > JourneyCode){
			parentOfCurrNode = currNode;
			currNode = currNode->left;
		}
		// currNode->JourneyCode == JourneyCode
		else{
			return false;
		}

		// JourneyCode is not present in the BST.  We must now
    	// insert an appropriate child of parentOfCurrNode.
    	// Please implement this part yourself.
    	//
    	// Do not forget to update shortestPathLength and
    	// longestPathLength of (possibly all) BST nodes in the
    	// path from the root to the new node you are inserting

		return true;
	}
	return true;
}

bool BST :: findfunc(TreeNode *p, int JourneyCode, int price){
    if(price == p->price){
        if(JourneyCode == p->JourneyCode){
            return true;
        }
        else{
            return false;
        }
    }
    if(price > p->price){
        if(p->right == NULL){
            return false;
        }
        return findfunc(p->right, JourneyCode, price);
    }
    if(price < p->price){
        if(p->left == NULL){
            return false;  
        }
        return findfunc(p->left, JourneyCode, price);
    }
    return false;
}

// Return True, if the ticket with given attributes is found, false otherwise
bool BST :: find(int JourneyCode, int price){
    // The following filler code snippet is only given to facilitate
    // compilation.  You should replace it with appropriate code, very
    // similar to what you had done in lab assignment 3.
    //
    // You can look at the implementation of insert to code this part up.
    TreeNode *f = root;
    return findfunc(f, JourneyCode, price);
}

TreeNode* BST :: min(TreeNode *n){
    while(n->left != NULL){
        n = n->left;
    }
    return n;
}

TreeNode* BST :: del(TreeNode *r, int key){
    if(r == NULL){
        return r;
    }
    if(key < r->price){
        r->left = del(r->left, key);
    }
    else if(key > r->price){
        r->right = del(r->right, key);
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
            r->JourneyCode = temp->JourneyCode;
            r->price = temp->price;
            r->right = del(r->right, temp->price);
        }
    }
    return r;
}


// Returns false, if JourneyCode isn't present
// Deletes the corresponding entry and returns True otherwise
bool BST :: remove(int JourneyCode, int price){
 	// The following filler code snippet is only given to facilitate
 	// compilation.  You should replace it with appropriate code, very
 	// similar to what you had done in lab assignment 3.
	//
	// Recall from CS 213 lectures about the various ways in which the
	// BST can be restructured when a node is deleted. You can implement
	// any of these alternatives.
	//
	// Do not forget to update shortestPathLength and
	// longestPathLength of (possibly all) BST nodes in the
	// path from the root to nodes whose position in the BST is affected
	// by the remove.
 	if( !(find(JourneyCode,price)) ){
		return false;
	}
	else{
		root = del(root,price);
	}
	return true;
}

// ************************************************************
// DO NOT CHANGE ANYTHING BELOW THIS LINE

// Adapted from Adrian Schneider's code on StackOverflow
void BST::printBST(const string& prefix, bool isLeft=false)
{
    if( root != nullptr )
    {
        cout << prefix;

        cout << (isLeft ? "|--" : "|__" );

        // print the value of the node
        cout << root->JourneyCode << endl;
        TreeNode *curr = root;
        root = root->left;
        // enter the next tree level - left and right branch
        printBST( prefix + (isLeft ? "│   " : "    "), true);
        root = curr->right;
        printBST( prefix + (isLeft ? "│   " : "    "), false);
        root = curr;
    }
}

void BST::getBST(const string& prefix,  bool isLeft=false)
{
    if( root != nullptr )
    {
        result.push_back(prefix);

        result.push_back(isLeft ? "|--" : "|__" );

        // print the value of the node
        result.push_back(to_string(root->JourneyCode) + "\n");
        TreeNode *curr = root;
        root = root->left;
        // enter the next tree level - left and right branch
        getBST( prefix + (isLeft ? "│   " : "    "), true);
        root = curr->right;
        getBST( prefix + (isLeft ? "│   " : "    "), false);
        root = curr;
    }
}

void BST::clearResult(){
    result.clear();
}

vector<string> BST::getResult(){
    return result;
}
