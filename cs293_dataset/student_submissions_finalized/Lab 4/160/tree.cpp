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
  
	if(root==NULL){
		root=new TreeNode(JourneyCode,price,NULL,NULL,NULL);
		root->shortestPathLength=0;
		root->longestPathLength=0;
		return true;
	}
	else{
		TreeNode *prev=NULL;
		TreeNode *temp=root;
		while(temp!=NULL){
			if(temp->JourneyCode==JourneyCode){
				return false;
			}
			else if(temp->price>=price){
				prev=temp;
				temp=temp->left;
				prev->shortestPathLength++;
			}
			else if(temp->price<price){
				prev=temp;
				temp=temp->right;
				prev->shortestPathLength++;
			}
		}
		if (prev->price>price) {
		prev->left =new TreeNode(JourneyCode,price,NULL,NULL,prev);
		prev->shortestPathLength=0;
		}
		else prev->right =new TreeNode(JourneyCode,price,NULL,NULL,prev);
		return true;
	}
    // JourneyCode is not present in the BST.  We must now
    // insert an appropriate child of parentOfCurrNode.
    // Please implement this part yourself.
    //
    // Do not forget to update shortestPathLength and
    // longestPathLength of (possibly all) BST nodes in the
    // path from the root to the new node you are inserting

}

// Return True, if the ticket with given attributes is found, false otherwise
bool BST::find(int JourneyCode, int price)
{
  // The following filler code snippet is only given to facilitate
  // compilation.  You should replace it with appropriate code, very
  // similar to what you had done in lab assignment 3.
  if(root==NULL) return false;
	if(root->price==price){
		if(root->JourneyCode==JourneyCode) return true;
	}
	TreeNode *prev=NULL;
	TreeNode *temp=root;
	while(temp!=NULL){
		if(temp->price>=price){
			prev=temp;
			temp=temp->left;
		}
		else if(temp->price<price){
			prev=temp;
			temp=temp->right;
		}
		if((prev->JourneyCode==JourneyCode)&&(prev->price==price)) return true;
	}
	return false;	
  // You can look at the implementation of insert to code this part up.
  
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
   	if(find(JourneyCode,price)) {
		root=deleteNode(root,price,JourneyCode);
		return true;}
	 
  return false;
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

