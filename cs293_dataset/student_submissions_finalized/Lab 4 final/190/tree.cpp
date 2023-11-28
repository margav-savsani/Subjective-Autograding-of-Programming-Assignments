#include <bits/stdc++.h>
#include <iostream>
#include <vector>
#include <string>
#include "tree.h"
using namespace std;




int BST::getImbalance()
{
  if (root == nullptr) return 0;
  else return root->getImbalance();
}









bool BST::insert(int JourneyCode, int price)
{
    cout << "inserting " << JourneyCode << " in tree..." <<endl;
    
    if(find(JourneyCode, price)){
        return false;
    }
    
    if(root == NULL){
        root = new TreeNode();
        root->JourneyCode = JourneyCode;
        root->price = price;
        root->shortestPathLength = root->longestPathLength = 1;
        return true;
    }
    
    TreeNode *z = new TreeNode();
    z->price = price;
    z->JourneyCode = JourneyCode;
    z->shortestPathLength = z->longestPathLength = 1;

    TreeNode *y = new TreeNode();
    y = NULL;
    TreeNode *x = new TreeNode();
    x = root;

    while(x != NULL){
        y = x;
        if(z->JourneyCode   <   x->JourneyCode){
            x = x->left;
        }
        else{
            x = x->right;
        }
    }

    z->parent = y;

    if(y == NULL){
        root = z;
    }
    else if(z->JourneyCode   <    y->JourneyCode){
        y->left = z;
    }
    else{
        y->right = z;
    }
    updatePathLength(z->parent);

    return true;

    
}








void BST::updatePathLength(TreeNode *parent){
  TreeNode *x = parent;
  // x can never be leaf.

  while(true){
    if (x == NULL){
      break;
    }
    else if(x->left == NULL){
    //   x->shortestPathLength = x->right->shortestPathLength + 1;
      x->shortestPathLength = 1;
      x->longestPathLength = x->right->longestPathLength + 1;
    }
    else if(x->right == NULL){
    //   x->shortestPathLength = x->left->shortestPathLength + 1;
      x->shortestPathLength = 1;
      x->longestPathLength = x->left->longestPathLength + 1;
    }
    else {
      x->shortestPathLength = min(x->left->shortestPathLength, x->right->shortestPathLength) + 1;
      x->longestPathLength = max(x->left->longestPathLength, x->right->longestPathLength) + 1;
    }

    x = x->parent;
  }

}









// Return True, if the ticket with given attributes is found, false otherwise
bool BST::find(int JourneyCode, int price)
{
  TreeNode *x = root;

  // This loop is infinite loop
  while (x != NULL && x->JourneyCode !=JourneyCode)
  {
    if (JourneyCode < x->JourneyCode)
    {
      x = x->left;
    }
    else
    {
      x = x->right;
    }
  }

  if (x == NULL)
  {
    return false;
  }

  while (x->price != price)
  {
    if (x->JourneyCode !=JourneyCode)
    {
      return false;
    }
    else
    {
      x = x->right;
    }

    if (x == NULL)
    {
      return false;
    }
  }

  // Fact that you reached here is proof that x is the right match!
  return true;
}








	
// Returns false, if JourneyCode isn't present
// Deletes the corresponding entry and returns True otherwise
bool BST::remove(int JourneyCode, int price)
{

    // FINDING PART-------------------
    TreeNode *z = root;
    while( z != NULL && z->JourneyCode != JourneyCode){
        if( JourneyCode   <   z->JourneyCode){
            z = z->left;
        }
        else {
            z = z->right;
        }
    }

    if(z == NULL){
        return false;
    }

    while(z->price != price){

        if(z->JourneyCode != JourneyCode){
            return false;
        }
        else{
            z = z->right;
        }

        if( z == NULL ){
            return false;
        }
    }




    // REMOVING PART ---------------------------
    TreeNode *y = new TreeNode();
    TreeNode *x = new TreeNode();

    if( z->left == NULL   ||    z->right == NULL){
        y =  z;
    }
    else{
        y = TreeSuccessor(z);
    }

    if( y->left != NULL ){
        x = y->left;
    }
    else{
        x = y->right;
    }

    if(x != NULL){
        x->parent = y->parent;
        
    }

    if(y->parent == NULL){
        root = x;
    }
    else if( y == y->parent->left ){
        y->parent->left = x;
    }
    else {
        y->parent->right = x;
    }

    if( y != z ){
        *z = *y;        //Copying all values of y into z
    } 

    updatePathLength(y->parent);

    return true;
}











TreeNode* BST::TreeSuccessor(TreeNode *x){
    if( x->right != NULL ) {
        TreeMinimum(x->right);
    } 

    TreeNode *y;
    y = x->parent;

    while(  y != NULL    &&    x == y->right ){
        x = y;
        y = y->parent;
    }

    return y;

}







TreeNode* BST::TreeMinimum(TreeNode *x){
    while( x->left != NULL ){
        x = x->left;
    }

    return x;
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

