// Code up the functions defined in tree.h
// Reuse the binary Search Tree implemented in lab 3 as much as possible

#include<iostream>
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
    
    // base case handling
	if(root == nullptr){
		root = new TreeNode(JourneyCode, price, nullptr, nullptr, nullptr);
		return true;
	}

    // finding place to insert
	struct TreeNode *curr = root, *parent = nullptr;
	while (curr != nullptr) {
		if (curr->JourneyCode < JourneyCode) {
			parent = curr;
			curr = curr->right;
		}
		else if (curr->JourneyCode > JourneyCode) {
			parent = curr;
			curr = curr->left;
		}
		else { // curr->JourneyCode == JourneyCode
			return false;
		}
  	}
    // JourneyCode is not present in the BST.  We must now
    // insert an appropriate child of parentOfCurrNode.
    // Please implement this part yourself.
    //
    // Do not forget to update shortestPathLength and
    // longestPathLength of (possibly all) BST nodes in the
    // path from the root to the new node you are inserting

    // inserting the node
	curr = new TreeNode(JourneyCode, price, nullptr, nullptr, parent);
	if(parent->JourneyCode > JourneyCode){
		parent->left = curr;
	}
	else{
		parent->right = curr;
	}
	curr->shortestPathLength = 0;
	curr->longestPathLength = 0;
    
    // updating shortestPathLength and longestPathLength
	while(parent!=nullptr){
        unsigned int spl, lpl;
		if(parent->left == nullptr ){
			spl = 0;
			lpl = parent->right->longestPathLength + 1;
		}
		else if(parent->right == nullptr ){
			spl = 0;
			lpl = parent->left->longestPathLength + 1;
		}
		else{
			spl = min(parent->left->shortestPathLength, parent->right->shortestPathLength) + 1;
			lpl = max(parent->left->longestPathLength, parent->right->longestPathLength) + 1;
		}
        if(spl == parent->shortestPathLength && lpl == parent->longestPathLength){
            // no need to go up if not changed at this node
            return true;
        }
        parent->shortestPathLength = spl;
        parent->longestPathLength = lpl;

		parent = parent->parent;
	}
    return true;
}

// Return True, if the ticket with given attributes is found, false otherwise
bool BST::find(int JourneyCode, int price)
{
    // The following filler code snippet is only given to facilitate
    // compilation.  You should replace it with appropriate code, very
    // similar to what you had done in lab assignment 3.
    //
    // You can look at the implementation of insert to code this part up.

    //similar to insert
    if(root == nullptr){
        return false;
    }
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
			return true;
		}
  	}
    // if not found above
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

    // base case
    if(root == nullptr){
        return false;
    }
    // deleting the found node
    if(root->JourneyCode == JourneyCode && root->price==price){

        // if node to be deleted has 1/0 child
        if(root->left == nullptr || root->right == nullptr){
            TreeNode* child = nullptr;
            if(root->left == nullptr){
                child = root->right;
            }
            else{
                child = root->left;
            }
            if(root->parent != nullptr){
                if(root->parent->left == root){
                    root->parent->left = child;
                }
                else if(root->parent->right == root){
                    root->parent->right = child;
                }
            }
            if(child!=nullptr){
                // 1 child case
                child->parent = root->parent;
            }
            delete root;
            root = child;

            // updating the shortest and longest path
            if(root!=nullptr){
                TreeNode* curr=root;
                while(curr!=nullptr){
                    unsigned int spl, lpl;
                    if(curr->left == nullptr ){
                        spl = 0;
                        if(curr->right == nullptr){
                            // 0 child case
                            lpl = 0;
                        }
                        else{
                            lpl = curr->right->longestPathLength + 1;  
                        }
                    }
                    else if(curr->right == nullptr ){
                        spl = 0;
                        lpl = curr->left->longestPathLength + 1;
                    }
                    else{
                        spl = min(curr->left->shortestPathLength, curr->right->shortestPathLength) + 1;
                        lpl = max(curr->left->longestPathLength, curr->right->longestPathLength) + 1;
                    }
                    if(spl == curr->shortestPathLength && lpl == curr->longestPathLength){
                        // no need to go up if not changed at this node
                        return true;
                    }
                    curr->longestPathLength = lpl;
                    curr->shortestPathLength = spl;

                    curr = curr->parent;
                }
            }
            return true;
        }

        // if node has 2 childs
        TreeNode* curr = root;
        TreeNode* succesor = root->right;
        while(succesor->left != nullptr){
            succesor = succesor->left;
        }
        root->JourneyCode = succesor->JourneyCode;
        root->price = succesor->price;
        root = succesor;
        if(!remove(root->JourneyCode, root->price)){
            cout<<"MEGA ERROR\n";
            return false;
        }
        root = curr;
        return true;
    }
    // recursively calling
    TreeNode* curr = root;
    if(root->JourneyCode > JourneyCode){
        root = root->left;
    }
    else{
        root = root->right;
    }
    bool result = remove(JourneyCode, price);
    root = curr;
    return result;
}

// ************************************************************
// DO NOT CHANGE ANYTHING BELOW THIS LINE

// Adapted from Adrian Schneider's code on StackOverflow
void BST::printBST(const string& prefix, bool isLeft)
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

