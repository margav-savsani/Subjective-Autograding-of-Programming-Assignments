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

int BST::getImbalance()
{
  if (root == nullptr) return 0;
  else return root->getImbalance();
}

bool BST::insert(int JourneyCode, int price)
{
  // The following filler code snippet is only given to facilitate
  // compilation.  You should replace/augment it with appropriate code,
  // similar to what you had done in lab assignment 3.
  
  struct TreeNode *currNode = root, *parentOfCurrNode = nullptr;
  
  while (currNode != nullptr) {
    if (currNode->JourneyCode < JourneyCode) {
      parentOfCurrNode = currNode;
      currNode = currNode->right;
    }
    else if (currNode->JourneyCode > JourneyCode) {
      parentOfCurrNode = currNode;
      currNode = currNode->left;
    }
    else { // currNode->JourneyCode == JourneyCode
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

// Return True, if the ticket with given attributes is found, false otherwise
bool BST::find(int JourneyCode, int price)
{
  if ( root == NULL || root->JourneyCode == JourneyCode ) return true;
	if ( root->price < price ) return find((root->right)->JourneyCode, (root->right)->price);
	if ( root->price > price ) return find((root->left)->JourneyCode, (root->left)->price);
	/*while (x != nullptr){
		if (x->JourneyCode==JourneyCode && x->price==price) return true;
		else {
			if (x->price > price)
				x = x->left;
			else if (root->price < price)
                                x = x->right;
		}
	}*/
  return false; 
  // The following filler code snippet is only given to facilitate
  // compilation.  You should replace it with appropriate code, very
  // similar to what you had done in lab assignment 3.
  //
  // You can look at the implementation of insert to code this part up.
}
	
// Returns false, if JourneyCode isn't present
// Deletes the corresponding entry and returns True otherwise
bool BST::remove(int JourneyCode, int price)
{
  
  int s=1;
	if (!find(JourneyCode, price)){
		s=0;
		return false;
	}
	else {
		TreeNode *trm = get(JourneyCode, price);
		if (trm->left==NULL && trm->right==NULL){
			if((trm->parent)->left==trm) ((trm->parent)->left)=NULL;
			if((trm->parent)->right==trm) ((trm->parent)->right)=NULL;
			return true;
		}
		else if (trm->left==NULL || trm->right==NULL){
			if(trm->left=NULL) int s=0;
			else int s=1;
			if(s==0){	
				if((trm->parent)->left==trm) ((trm->parent)->left)=trm->right;
                		if((trm->parent)->right==trm) ((trm->parent)->right)=trm->right;
				return true;
			}
			if(s==1){
                        	if((trm->parent)->left==trm) ((trm->parent)->left)=trm->left;
	                        if((trm->parent)->right==trm) ((trm->parent)->right)=trm->left;
        	        	return true;
			}
		}	
		else {
			TreeNode *scr=trm->right;
			while(scr->left != NULL){
				scr = scr->left;
			}
			(scr->parent)->left=scr->right;
			scr=trm;
			trm=NULL;
			return true;
		}
	}
	return false;
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
        result.push_back(root->JourneyCode + "\n");
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

