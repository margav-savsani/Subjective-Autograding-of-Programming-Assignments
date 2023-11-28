#include <bits/stdc++.h>
#include <iostream>
#include <vector>
#include <string>

using namespace std;

#include "tree.h"

#define PRE_ORDER 0
#define POST_ORDER 1
#define IN_ORDER 2
#define LOAD_FULL_BST 3
#define LOAD_LEFT_SUBTREE 4

// Constructors
BST::BST(){ root = nullptr; }
BST::BST(TreeNode *root){ this->root=root ; }

// Returns false, if given JourneyCode is already present in the BST
// Inserts the element and returns True otherwise
bool BST::insert(int JourneyCode, int price) { 
	if(find(JourneyCode, price)){		//If element already present, return false
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
}


void BST::updateLength(){				//Function to update the path lengths of nodes
	//Uses post order traversal
	if (root == nullptr ){
		return;
	}
	BST L(root->left);
	BST R(root->right);
	L.updateLength();
	R.updateLength();
	root->longestpath = longestPath();
	root->shortestpath = shortestPath();
}

// Return True, if the ticket with given attributes is found, false otherwise
bool BST::find(int JourneyCode, int price) { 
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
}

//Returns the root of the tree
TreeNode* BST::get_root(){
		return root;
}

// Returns false, if JourneyCode isn't present
// Deletes the corresponding entry and returns True otherwise
bool BST::remove(int JourneyCode, int price) {
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
}

//Path difference between shortest and longtest paths
int BST::pathDifference(){
	return longestPath()-shortestPath();
}


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

void BST::clearResult(){			//Clears the result
    result.clear();
}

vector<string> BST::getResult(){	//Return the result
    return result;
}

int BST::shortestPath(){			//Find the shortest path from root to leaf
	if(root==nullptr){
		return 0;
	}
	BST L(root->left);
	BST R(root->right);
	if ( L.shortestPath() < R.shortestPath() )
	{
		return 1 + L.shortestPath();
	}
	else
	{
		return 1 + R.shortestPath();
	}
}


int BST::longestPath(){				//Find the longest path from root to leaf
	
	if(root==nullptr){
		return 0;
	}
	
	BST L(root->left);
	BST R(root->right);
	
	if ( L.longestPath() < R.longestPath() )
	{
		return 1 + R.longestPath();
	}
	else
	{
		return 1 + L.longestPath();
	}
}
