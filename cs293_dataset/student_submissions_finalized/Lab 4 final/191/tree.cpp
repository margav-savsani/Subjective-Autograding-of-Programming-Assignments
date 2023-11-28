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

int BST::getImbalance()//returns the value returned by the method of TreeNode that is getImbalance
{
  if (root == nullptr) return 0;
  else return root->getImbalance();
  return 0;
}

bool BST::insert(int JourneyCode, int price)//inserts the node 
//basically checks if the node is already present or not, if it is present, then just returns false else
//inserts the required TreeNode and returns true
{
  TreeNode *ptr = root;
	bool done{false};
	
	TreeNode *node;
	node = new TreeNode;
	node->JourneyCode = JourneyCode;
	node->price = price;
	node->left = nullptr;
	node->right = nullptr;
  node->shortestPathLength=0;
  node->longestPathLength=0;
	
	if(root == nullptr){	//special case when the insertion is the first insertion in an empty BST
		root = node;
		node->parent = nullptr;
		return true;
	}
	
	if(find(JourneyCode, price)){	//check if JourneyCode and price are already present or not, if they are return false and exit fomr this method
		return false;
	}
	
	else{
		
		while(true){
			//tracing where the insertion should be done so that prices lower than or equal to a node goes to the left subtree of that node else right subtree
			if(ptr->JourneyCode >= JourneyCode){	
				if(ptr->left == nullptr){
					node->parent = ptr;
					ptr->left = node;
					node = nullptr;
					break;
				}
				else{
					ptr = ptr->left;
				}
			}
			
			else {
				if(ptr->right == nullptr){
					node->parent = ptr;
					ptr->right = node;
					node = nullptr;
					break;
				}
				else{
					ptr = ptr->right;
				}
			}
		}
    update_length(ptr);
    
		return true;
	}
}

//updates the shortestPath Length and Longest Path Length by making cases 
void BST::update_length(TreeNode *ptr){
  if(ptr==nullptr){
    return;
  }
  int right,left;
  if(ptr->right==nullptr && ptr->left==nullptr){
    ptr->shortestPathLength=0;
    ptr->longestPathLength=0;
  }
  else if(ptr->right==nullptr){
    ptr->shortestPathLength=0;
    ptr->longestPathLength=ptr->left->longestPathLength+1;
  }
  else if(ptr->left==nullptr){
    ptr->shortestPathLength=0;
    ptr->longestPathLength=ptr->right->longestPathLength+1;
  }
  else{
	//min and max function are used in the general case 
    ptr->shortestPathLength=min(ptr->right->shortestPathLength+1,ptr->left->shortestPathLength+1);
    ptr->longestPathLength=max(ptr->right->longestPathLength+1,ptr->left->longestPathLength+1);
  }

  update_length(ptr->parent);
}

//myfind method returns the pointer of the TreeNode struct if it is found nullptr otherwise 
TreeNode* BST::myfind(int JourneyCode, int price) { 
	
	TreeNode *ptr = root;
	while(true){
		if(ptr == nullptr)
			return nullptr;
		else{
			if(ptr->JourneyCode> JourneyCode){
				ptr=ptr->left;
			}
			else if(ptr->JourneyCode<JourneyCode){
				ptr=ptr->right;
			}
			else if(ptr->JourneyCode==JourneyCode){
				if(ptr->price == price)
					return ptr;
				else ptr=ptr->left;
			}
		}
	}
}

// Return True, if the ticket with given attributes is found, false otherwise
bool BST::find(int JourneyCode, int price){
	TreeNode *ptr = myfind(JourneyCode, price); //ptr is the pointer to the node which has the required JourneyCode and price
	if(ptr == nullptr){
		return false;
	}
	else{
		return true;
	}
}
	
// Returns false, if JourneyCode isn't present
// Deletes the corresponding entry and returns True otherwise
bool BST::remove(int JourneyCode, int price) {  

	TreeNode *ptr=myfind(JourneyCode, price);//find the treeNode to be removed and pass it on to the myremove function which returns true if it is successful in deletion false otherwise.
	if(myremove(ptr))
		return true;
	else
		return false;	
}

//myremove function returns true if it is successful in deletion false otherwise.
bool BST::myremove(TreeNode *ptr){
	if(ptr==nullptr)
		return false;
	
	else{
		//case 1--without no children
		if(ptr->left == nullptr && ptr->right==nullptr){
			if(ptr->parent == nullptr)
				root = nullptr;
			if(ptr->parent->left==ptr){
				ptr->parent->left=nullptr;
        update_length(ptr->parent);
			}
			if(ptr->parent->right==ptr){
				ptr->parent->right=nullptr;
        update_length(ptr->parent);
			}
      
			ptr->parent=nullptr;
			return true;
		}	
		
		//case 2--with 1 child
		//the next 2 else if are similar ,only difference is one deals when left pointer is nullptr andthe other deals with right pointer 
		else if(ptr->left==nullptr){
			ptr->right->parent=ptr->parent;
			if(ptr->parent==nullptr){
				root=ptr->right;
				ptr->right=nullptr;
			}
			else if(ptr->parent->left==ptr){
				ptr->parent->left=ptr->right;
			}
			else if(ptr->parent->right==ptr){
				ptr->parent->right=ptr->right;
			}
      update_length(ptr->parent);
			ptr->parent=nullptr;
			ptr->right=nullptr;
			return true;
		}
		
		else if(ptr->right==nullptr){
			ptr->left->parent=ptr->parent;
			if(ptr->parent==nullptr){
				root=ptr->left;
				ptr->left=nullptr;
			}
			else if(ptr->parent->left==ptr){
				ptr->parent->left=ptr->left;
			}
			else if(ptr->parent->right==ptr){
				ptr->parent->right=ptr->left;
			}
      update_length(ptr->parent);
			ptr->parent=nullptr;
			ptr->left=nullptr;
			return true;
		}
		
		//case 3--with 2 child
		//uses recursion
		else{
			TreeNode *find_replacement = getMaxNode(ptr->left);
			ptr->price=find_replacement->price;
			ptr->JourneyCode=find_replacement->JourneyCode;
			myremove(find_replacement);
			return true;
		}
	}
	return false;
}


//function used in the myremove method which returns the pointer to the node with maximum price and root as ptr (an argument)
TreeNode * BST::getMaxNode(TreeNode* ptr){
	while(true){
		if(ptr == nullptr)
			return 0;
		if(ptr->right == nullptr)
			return ptr;
		else{
			ptr = ptr->right;
		}
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

