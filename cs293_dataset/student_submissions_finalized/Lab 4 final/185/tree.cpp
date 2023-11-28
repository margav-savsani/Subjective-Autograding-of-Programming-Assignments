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
    if (root == nullptr)
        return 0;
    else
        return root->getImbalance();
}

int BST::longestpath(TreeNode* nod){

    if(nod == NULL){
        return 0;
    }
    else{
        return 1 + max(longestpath(nod->right),longestpath(nod->left));
    }

}

int BST::shortestpath(TreeNode* nod){
    if(nod == NULL){
        return 0;
    }
    else{
        return 1 + min(shortestpath(nod->right),shortestpath(nod->left));
    }


}

bool BST::insert(int JourneyCode, int price)
{
    // The following filler code snippet is only given to facilitate
    // compilation.  You should replace/augment it with appropriate code,
    // similar to what you had done in lab assignment 3.

    TreeNode *present = NULL; // declare a null TreeNode
    TreeNode *search = root;  // root of the tree
    // TreeNode *given;           //node for the given values
    // given->JourneyCode = JourneyCode;  //assign passed journeycode and price to "given" treenode
    // given->price = price;

    TreeNode *given = new TreeNode(JourneyCode, price);

    while (search != NULL)
    {                     // while root of the tree is not null, repeat the loop. finally "search" will give the correct insertion position for the "given" node.
        present = search; // stores parent of "search" in "present"
        if (search->JourneyCode > JourneyCode)
        {                          // if price of root is greater than the given price
            search = search->left; // go to the left subtree
        }
        else
        {                           // if price of root is less than the given price
            search = search->right; // go to the right subtree
        }
    }

    given->parent = present; // make "present" the parent node of the given node.

    if (present == NULL)
    {                 // if "present" is still NULL means our root of the tree was NULL
        root = given; // store the "given" node into root.
        // root->shortestPathLength = 0;
        // root->longestPathLength = 0;
        return true; // insertion complete
    }
    else if (given->JourneyCode < present->JourneyCode)
    { // if "present" is not NULL and given price is less than the parent's price
        present->left = given;
        // the "given" node will be left node of the parent.
        root->shortestPathLength = shortestpath(root);
        root->longestPathLength = longestpath(root);
        return true; // inserton complete
    }
    else if (given->JourneyCode > present->JourneyCode)
    { // else the "given" node will be right node of the parent.
        present->right = given;
        root->shortestPathLength = shortestpath(root);
        root->longestPathLength = longestpath(root);
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
    //
    // You can look at the implementation of insert to code this part up.

   TreeNode *current_root = root;  //store root in TreeNode "current_root"

    while(current_root!=NULL && current_root->JourneyCode!=JourneyCode && current_root->price!=price){ //loop till current_root does not contain the given data
        if(current_root->price < price){
            current_root =  current_root->right;  //if given price is greater than price in current_root, store pointer of current_root->right into current_root 
        }
        else{
            current_root =  current_root->left;  // else store pointer of current_root->left into current_root
        }
    }
    if(current_root==NULL) return false;  // after looping if current_root is again NULL, then ticket not present and return false

    else if(current_root->JourneyCode==JourneyCode && current_root->price==price){  // else ticket is present and return true
        return true;
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

     if(find( JourneyCode, price)){  //if journeycode is present in the tree, go on

        TreeNode *found = root;   // store root of tree into TreeNode "found"
        TreeNode *assign;         
        TreeNode *current = NULL;   //y
        TreeNode *x = NULL;   //x
        TreeNode *succ = NULL;  //successor of assign
        TreeNode *mini = root;  //minimum of the tree
        TreeNode *ex = NULL;  //just declared to use as extra 

        while(found!=NULL && found->JourneyCode!=JourneyCode && found->price!=price){   //loop to find the left and right and parent node of given attributes.
            if(found->price < price){   //if given price is greater than price in found, store pointer of found->right into found 
                found =  found->right;
            }
            else{
                found = found->left;   // else do opposite
            }
        }
    if(found==NULL) return false;  // after looping if current_root is again NULL, then ticket not present and return false

    else if(found->JourneyCode == JourneyCode && found->price == price){   //if after looping, found contains the given attributes, store it in assign
        assign = new TreeNode(JourneyCode,price,found->left,found->right ,found->parent);  //now assign is the node with given attributes and it needs to be deleted
    }

    if(assign->left == NULL || assign->right == NULL){  // if the left or right node of assign is NULL, then store assign in "current"
        current = assign;
    }
    else{                                      //else store the successor of assign in "current" and delete current
        if(assign->right != NULL){  
            //if(mini==NULL) return 0;
                while(mini->left != NULL){
                mini = mini->left;
                }
            succ = mini;            //mini is the node with minimum price in the tree
        }
        ex = assign->parent;
        while( ex != NULL && assign == ex->right){
            assign = ex;
            ex = ex->parent;
        }
        succ = ex;                    
        current = succ;           //succ is the successor of assign. here we have stored it in current
    }

    if(current->left != NULL){     //now if left of cuurent is not empty
        x = current->left;         //assign current->left to x
    }
    else{
        x = current->right;        // else assign current->right to x
    }

    if(x != NULL){
        x->parent = current->parent;  //if left of current is not equal to null, change the pointer and make current->parent parent of current->left
    }

    if(current->parent == NULL){     //but if current->parent is NULL, change root to x
        root = x;
    }
    else if(current == current->parent->left){    //else if current = current's parent->left
        current->parent->left = x;                //then current's parent->left = x.
    }
    else{
        current->parent->right = x;
    }

    if(current != assign){                              //finally replace node to be deleted wit the appropriate node
        assign->JourneyCode = current->JourneyCode;
        assign->price = current->price;
    }
    return true;                                        // and return true
}
    return false;            //if node with given attributes not find, return false
}

// ************************************************************
// DO NOT CHANGE ANYTHING BELOW THIS LINE

// Adapted from Adrian Schneider's code on StackOverflow
void BST::printBST(const string &prefix, bool isLeft = false)
{
    if (root != nullptr)
    {
        cout << prefix;

        cout << (isLeft ? "|--" : "|__");

        // print the value of the node
        cout << root->JourneyCode << endl;
        TreeNode *curr = root;
        root = root->left;
        // enter the next tree level - left and right branch
        printBST(prefix + (isLeft ? "│   " : "    "), true);
        root = curr->right;
        printBST(prefix + (isLeft ? "│   " : "    "), false);
        root = curr;
    }
}

void BST::getBST(const string &prefix, bool isLeft = false)
{
    if (root != nullptr)
    {
        result.push_back(prefix);

        result.push_back(isLeft ? "|--" : "|__");

        // print the value of the node
        result.push_back(to_string(root->JourneyCode) + "\n");
        TreeNode *curr = root;
        root = root->left;
        // enter the next tree level - left and right branch
        getBST(prefix + (isLeft ? "│   " : "    "), true);
        root = curr->right;
        getBST(prefix + (isLeft ? "│   " : "    "), false);
        root = curr;
    }
}

void BST::clearResult()
{
    result.clear();
}

vector<string> BST::getResult()
{
    return result;
}
