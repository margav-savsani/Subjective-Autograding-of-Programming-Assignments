// Code up the functions defined in tree.h
// Reuse the binary Search Tree implemented in lab 3 as much as possible

#include <bits/stdc++.h>
#include <iostream>
#include <vector>
#include <string>

using namespace std;

#include "tree.h"

// PLEASE FILL IN THE BODIES OF THE FOLLOWING FUNCTIONS

// Returns false, if given JourneyCode is already present in the BST
// Inserts the element and returns True otherwise

  BST :: BST() {root = nullptr; }
  BST :: BST(TreeNode *curr_root) {root = curr_root;}


int BST::shortestpath(TreeNode* T){
	if(T==nullptr) return 0;
	else if(T->left==nullptr && T->right==nullptr) return 1;
	if(T->left == nullptr) return 1+shortestpath(T->right);
	else if(T->right==nullptr) return 1+shortestpath(T->left);
	return ( 1+ min(shortestpath(T->left),shortestpath(T->right)) );
}

int BST::longestpath(TreeNode* T){
	if(T==nullptr) return 0;
	else if(T->left==nullptr && T->right==nullptr) return 1;
	if(T->left == nullptr) return 1+longestpath(T->right);
	else if(T->right==nullptr) return 1+longestpath(T->left);
        return ( 1+ max(longestpath(T->left),longestpath(T->right)) );
}

int BST::getImbalance()
{
	if (root == nullptr) return 0;
	else return root->getImbalance();
}

TreeNode* BST:: successor(TreeNode * r) {
	if(r->right != nullptr){
		TreeNode * t = r->right;
		while(t->left!=nullptr){
        		t=t->left;
		}
    		return t;
    	}
	TreeNode * y = r->parent;
	while ( y!=nullptr && r==y->right ){
		r = y;
		y = y->parent;
	}
	return y;
}

TreeNode * f;

bool BST::insert(int JourneyCode, int price)
{
  // The following filler code snippet is only given to facilitate
  // compilation.  You should replace/augment it with appropriate code,
  // similar to what you had done in lab assignment 3.
	if(find(JourneyCode,price)) return false;
	TreeNode * z = new TreeNode(JourneyCode,price);
	TreeNode * y = nullptr;
	TreeNode * x = root;
	while(x!=nullptr){
		y = x;
		if( x->JourneyCode <= JourneyCode) x = x->right;
		else x = x->left;
	}
	z->parent = y;
	if( y == nullptr) root = z;
	else if( y->JourneyCode <= JourneyCode) y->right = z;
		else y->left = z;
	cout<<shortestpath(root)<<endl;
	root->shortestPathLength=shortestpath(root);
	cout<<longestpath(root)<<endl;
	root->longestPathLength=longestpath(root);
	return true;
}
  // JourneyCode is not present in the BST.  We must now
  // insert an appropriate child of parentOfCurrNode.
  // Please implement this part yourself.
  //
  // Do not forget to update shortestPathLength and
  // longestPathLength of (possibly all) BST nodes in the
  // path from the root to the new node you are inserting
  

// Return True, if the ticket with given attributes is found, false otherwise
bool BST::find(int JourneyCode, int price)
{
  // The following filler code snippet is only given to facilitate
  // compilation.  You should replace it with appropriate code, very
  // similar to what you had done in lab assignment 3.
  //
  // You can look at the implementation of insert to code this part up.
  	TreeNode * x = root;
	while( x!=nullptr ){
		if( JourneyCode==x->JourneyCode ){
			if(price==x->price){ f = x; return true;}
			else{   x=x->right;
				continue;
			}
		}
		else if(JourneyCode < x->JourneyCode) x = x->left;
		else x = x->right;
	}
	return false;
}
	
// Returns false, if JourneyCode isn't present
// Deletes the corresponding entry and returns True otherwise
bool BST::remove(int JourneyCode, int price)
{
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
    
	TreeNode * x;
	TreeNode * y;
	if(!find(JourneyCode, price)) return false;
	else{  
		if (f->left == nullptr || f->right == nullptr) y = f;
			else y = successor(f);
		if (y->left != nullptr) x = y->left;
			else x = y->right;
		if (x != nullptr) x->parent = y->parent;
		if(y->parent == nullptr) root = x;
		else if ( y == y->parent->left) y->parent->left = x;
			else y->parent->right = x;
		if( y != f ) {
			f->price = y->price;
			f->JourneyCode = y->JourneyCode;
		}
		root->shortestPathLength=shortestpath(root);
		root->longestPathLength=longestpath(root);
		return true;
	}
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

