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

void BST::Updatepaths(TreeNode* node,int flag){// to change the shortest and longest path lengths. according to the conditions.
    TreeNode *parent,*child;
    if (flag==0){
        parent= node->parent;
        child = node;
        node->shortestPathLength = 0;
        node->longestPathLength = 0;
    } 
    else if (flag==1){
        parent= node->parent;
        child = node;
        node->shortestPathLength = node->longestPathLength;// since there is only one way to reach a leaf.
    }
    while (parent!=nullptr){
        if (parent->left == nullptr || parent->right == nullptr){// case -1 :the subtree which is null is not even considered for this path lengths.
            parent->longestPathLength = child ->longestPathLength+1;
            parent->shortestPathLength = child ->shortestPathLength+1;
        }
        else{ // case-2 it depends on the childrens.
            parent->shortestPathLength = ( (parent->left->shortestPathLength > parent->right->shortestPathLength ) ? 1 + parent->right->shortestPathLength : 1 + parent->left->shortestPathLength ); 
            parent->longestPathLength = ( parent->left->longestPathLength > parent->right->longestPathLength ) ? 1 + parent->left->longestPathLength : 1 + parent->right->longestPathLength;
        }  
        child = parent;
        parent = parent->parent;// assiging the pointers
    }
}

bool BST::insert(int JourneyCode, int price) { 
    // iterative procedure
    TreeNode *parent = nullptr;
    TreeNode *child = root;
    if (root == nullptr) {// intial case 
        root = new TreeNode(JourneyCode,price,nullptr,nullptr,nullptr);
        Updatepaths(root,0);
        return true;
    }
    while ( (child != nullptr) && (child->JourneyCode != JourneyCode) ){// traverse till you find a leaf 
        if (child->JourneyCode >= JourneyCode){ // go to left node 
            parent = child;
            child = child->left;
        }
        else if (child->JourneyCode < JourneyCode){ // go to right node
            parent = child;
            child = child->right;
        }
    }
    if (child == nullptr){// insert only if the u had found a leaf.
        TreeNode *new_node = new TreeNode(JourneyCode,price,nullptr,nullptr,parent);
        if (parent->JourneyCode  >= JourneyCode) {
            parent->left = new_node;
            child = parent->left;
        }
        else {
            parent->right = new_node;
            child = parent->right;
        }
        Updatepaths(child,0);
        return true;
    }    
    return false;
}

// Return True, if the ticket with given attributes is found, false otherwise
bool BST::find(int JourneyCode, int price) // same find function but with respect to journey code.
{
    if (root == nullptr) return false;
    if (root->price == price && root->JourneyCode == JourneyCode) return true;
    else if (root->JourneyCode >= JourneyCode) {// move to left node.
        BST leftSubTree(root->left);
        return leftSubTree.find(JourneyCode,price);
    }
    else if (root->JourneyCode< JourneyCode) {
        BST rightSubTree(root->right);// move to right node.
        return rightSubTree.find(JourneyCode,price);
    }
    return false;
}
	
// Returns false, if JourneyCode isn't present
// Deletes the corresponding entry and returns True otherwise
bool BST::remove(int JourneyCode, int price) { 
    if (root == nullptr) return false;
    if ((root->JourneyCode==JourneyCode) && (root->price==price) ){// node found
        if ( root->left == nullptr && root->right == nullptr){// no child case
            if (root->parent ==  nullptr) {
                root=nullptr;
                return true;
            }
            TreeNode *parent = root-> parent;
            if( parent->JourneyCode >= JourneyCode ) parent->left = nullptr; 
            else parent->right = nullptr;
            root = nullptr;
            Updatepaths(parent,1);// updates the path.
            return true;            
        }
        else if ( root->left ==nullptr ){// only right child case
            if (root->parent ==nullptr){// in this case we copy the child node in the node to be deleted and the delete the child.
                root=root->right;// have to take care of the case when the root has no parent
                root->parent = nullptr;                
                return true;
            }
            root->JourneyCode=root->right->JourneyCode;//coping the child into root.
            root->price = root->right->price;
            BST subtree(root->right);// removing the element from the tree. 
            return subtree.remove(root->right->JourneyCode,root->right->price);
        }
        else if ( root->right ==nullptr ){// only left child case
            if (root->parent ==nullptr){// in this case we copy the child node in the node to be deleted and the delete the child.
                root=root->left;// have to take care of the case when the root has no parent
                root->parent = nullptr;                
                return true;
            }
            root->JourneyCode=root->left->JourneyCode;
            root->price=root->left->price;
            BST subtree(root->left);
            return subtree.remove(root->left->JourneyCode,root->left->price);
        }
        else {// two child case
            TreeNode *child = root->left;// we convert this case into case of node with 1 or 0 child - case then make it into case with 0 child
            while (child->right != nullptr){
                child = child->right;
            }
            root->JourneyCode=child->JourneyCode;//coping the predecessor into root.
            root->price = child->price;
            BST leftSubTree(root->left);
            return leftSubTree.remove(root->JourneyCode,root->price);// removing the copy of predecessor
        }
    }
    else if (root->JourneyCode >= JourneyCode) {// recursion
        BST leftSubTree(root->left);
        return leftSubTree.remove(JourneyCode,price);
    }
    else if (root->JourneyCode < JourneyCode) {
        BST rightSubTree(root->right);
        return rightSubTree.remove(JourneyCode,price);
    }
    return false;
}
/*bool BST::remove(int JourneyCode, int price)
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
    
  return false;
}*/

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
        cout << root->JourneyCode <<" S: "<<root->shortestPathLength<<" L: "<<root->longestPathLength<< endl;
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

