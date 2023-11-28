// Code up the functions defined in tree.h
// Reuse the binary Search Tree implemented in lab 3 as much as possible

#include <bits/stdc++.h>
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>  

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


//inserts new node in the tree
bool BST::insert(int JourneyCode, int price)
{
   TreeNode* to= new TreeNode(JourneyCode,price);//this is the node to be searched
    TreeNode * parent_ptr;
    TreeNode * child_ptr;
    child_ptr=root;
    parent_ptr=NULL;
    //loops continues till node is found
    while(child_ptr!=NULL){
        if(child_ptr->price==price && child_ptr->JourneyCode==JourneyCode){
            //if the node is found,return false as the node is already present
            return false;
        }
        //traverse the tree to find the node
        parent_ptr=child_ptr;
        if(JourneyCode<=child_ptr->JourneyCode){
            //if the price is left move to left
            child_ptr=child_ptr->left;
        }
        else{
            //if the price is more, move to right
            child_ptr=child_ptr->right;
        }

    }
    //attatching the node to the tree
    //comparing its price with the price of the parent node and accordingly joining it in the BST
    //if the price is equal, I have added it to the left
    to->parent=parent_ptr;
  
    if(parent_ptr==NULL){
        root=to;
        // return true;
    }
    else{
        if(to->JourneyCode<=parent_ptr->JourneyCode){
            parent_ptr->left=to;
            // return true;
        }
        else{
            parent_ptr->right=to;
            // return true;
        }
    }


    //changing the shortest path length and longest path length of the nodes
    while(parent_ptr!=NULL){// traversing the tree till a parent_ptr becomes NULL
        // if the node added is the first child that is the parent_ptr is no longer NULL
        if(parent_ptr->left==NULL || parent_ptr->right==NULL){
            //then the shortest and longest path gets incremented
            (parent_ptr->shortestPathLength)=(to->shortestPathLength)+1;
            (parent_ptr->longestPathLength)=(to->longestPathLength)+1;
        }
        else{
          // changing the shortest and longest path
          int short_left=(parent_ptr->left)->shortestPathLength+1;
          int short_right=(parent_ptr->right)->shortestPathLength+1;
          //setting the shortest path of parent_ptr
          parent_ptr->shortestPathLength=min(short_left,short_right);
          int long_left=(parent_ptr->left)->longestPathLength+1;
          int long_right=(parent_ptr->right)->longestPathLength+1;
          //setting the longest path of parent_ptr
          parent_ptr->longestPathLength=max(long_left,long_right); 
        }
        // shifting the pointers
        to=parent_ptr;
        parent_ptr=parent_ptr->parent;
    }
    return true;
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
  //
  // You can look at the implementation of insert to code this part up.
  TreeNode * roo;
    roo=root;
    while(roo!=NULL){
        if( price==roo->price && JourneyCode==roo->JourneyCode){//if the journey code and price match, return true
            return true;
        }
        if(JourneyCode<=roo->JourneyCode){//else traverse the tree
            roo=roo->left;
        }
        else{
            roo=roo->right;//else traverse the tree
        }
    }

  return false;
}
	



//returns the predecessor value of the top found in the tree starting from top
TreeNode* BST::get_min(TreeNode* top){
    TreeNode * roo;
    roo=top;
    while(roo->right!=NULL){// move to right until you reach rightmost element
        roo=roo->right;
    }
    return roo; 
}





// Returns false, if JourneyCode isn't present
// Deletes the corresponding entry and returns True otherwise
bool BST::remove(int JourneyCode, int price)
{   
    //initialising the variables
    TreeNode * parent_ptr;
    parent_ptr=NULL;
    TreeNode * child_ptr;
    child_ptr=root;
// finding the node in the tree
    while(child_ptr !=NULL ){
        parent_ptr=child_ptr;
        if(JourneyCode<child_ptr->JourneyCode){
            child_ptr=child_ptr->left;
        }
        else if(price>child_ptr->price){
            child_ptr=child_ptr->right;
        }
        else {
            if(child_ptr->JourneyCode==JourneyCode){
                break;
            }
            else{
                child_ptr=child_ptr->left;
            }

        }
    }
    //if the required child is not found, function returns false
    if(child_ptr==NULL){
        return false;
    }

    //Leaf node that is teh required node has no children
   if(child_ptr->left==NULL && child_ptr->right==NULL){
    //in this case the  parent pointer simply starts poingting to null
    parent_ptr=child_ptr->parent;
        if(parent_ptr==NULL){
            root=NULL;
            return true;
        }
        if((parent_ptr->left) == (child_ptr)){
            parent_ptr->left=NULL;
        }
        else{
            parent_ptr->right=NULL;
        }
        return true;
    }
//if one child pointer is NULL
    else if(child_ptr->left==NULL || child_ptr->right==NULL){
        //initialisng the parent pointer
       parent_ptr=child_ptr->parent;
        if(parent_ptr==NULL){
            //if parent pointer is NULL that is the element to be deleted is thr root
            if(child_ptr->left!=NULL){
                root=child_ptr->left;
                root->parent=NULL;
            }
            else{
                root=child_ptr->right;
                root->parent=NULL;
            }
        }
        else{// if the required node is the left child
        if( parent_ptr->left==child_ptr){//elemnent to be deleted is the right child
            if(child_ptr->left!=NULL){//done
                parent_ptr->left=child_ptr->left;
                (child_ptr->left)->parent=parent_ptr;
            }
            else{
                parent_ptr->left=child_ptr->right;
                (child_ptr->right)->parent=parent_ptr;
            }
            
        }
        else {//if the parent has right child
            if(child_ptr->left!=NULL){//if child pointer has no right child
                parent_ptr->right=child_ptr->left;
                (child_ptr->left)->parent=parent_ptr;
            }
            else{
                parent_ptr->right=child_ptr->right;// if child pointer has no left child
                (child_ptr->right)->parent=parent_ptr;
            }
            
        }
        return true;
        }
    }
    // Having two children
    //using predecessor method
    else{
        //getting the predecessor 
       TreeNode * pre=get_min(child_ptr->left);
        TreeNode temp(pre->JourneyCode,pre->price);
        //deleting the predecessor
        remove(pre->JourneyCode,pre->price);
        //replacing the root by predecessor
        child_ptr->JourneyCode=temp.JourneyCode;
        child_ptr->price=temp.price;
        return true;
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

