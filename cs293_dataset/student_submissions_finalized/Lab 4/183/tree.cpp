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

bool BST:check(int &i,int &j,TreeNode *y){
   if(j>i) {return false;}
   else{  if(y==NULL) return true;
          else{ 
               check(i,j+1,y->left);
               check(i,j+1,y->right);
}}
}

bool BST:checkl(int &i,int &j,TreeNode *y){
   if (j>i) {return false;}
   if(j=i) { if (y!=NULL) return true;}
       else {checkl(i,j+1,y->left);
              checkl(i,j+1,y->right;}
}
             
bool BST::insert(int JourneyCode, int price)
{
  // The following filler code snippet is only given to facilitate
  // compilation.  You should replace/augment it with appropriate code,
  // similar to what you had done in lab assignment 3.
  
  struct TreeNode *currNode = root, *parentOfCurrNode = nullptr;
  int i=0;
  if(root==NULL){root=new TreeNode(JourneyCode,price);return true;} //if root is null then just insert at root
  while (currNode != nullptr) {
    if (currNode->JourneyCode < JourneyCode) {
      i=i+1
      parentOfCurrNode = currNode;
      currNode = currNode->right;
    }
    else if (currNode->JourneyCode > JourneyCode) {
      i=i+1
      parentOfCurrNode = currNode;
      currNode = currNode->left;
    }
    else { // currNode->JourneyCode == JourneyCode
      return false;
    }}
    currNode=new TreeNode(JourneyCode,price);
    currNode->parent=parentOfCurrNode;
    if (parentOfCurrNode==NULL){root=currNode;}                    
          else if((currNode->price)<(parentOfCurrNode->price)){parentOfCurrNode->left=currNode;}   //updating child of parent to inserting node
               else{parentOfCurrNode->right=currNode;}
    if(i>longestPathLength){longestPathLength=i;}
          int j=smallestPathLength;
          if(i-j==1){int k=0;TreeNode *x=root;if(check(j,k,x)==0){smallestPathLength=i;}} 
   
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
  // The following filler code snippet is only given to facilitate
  // compilation.  You should replace it with appropriate code, very
  // similar to what you had done in lab assignment 3.
  //
  // You can look at the implementation of insert to code this part up.
  struct TreeNode *x=root;
      while(x!=NULL){
             if((JourneyCode==x->JourneyCode)&&(price==x->price)){return true;} //if found
             if (price<(x->price)){x=x->left;}       //if price is less then search in left subtree
             else{x=x->right;}                       //if price is more/equal then search in right subtree
             }
       return false; 
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
   if(find(JourneyCode,price)==false){return false;}   //if element is not found the delete it.
    else{
         TreeNode *z=root;
         while(z!=NULL){
             if((JourneyCode==z->JourneyCode)&&(price==z->price)){break;} //finding element to be deleted in BST
             if (price<(z->price)){z=z->left;}
             else{z=z->right;}
             }
    TreeNode* prev = z->parent;
    if(z->left ==NULL && z->right ==NULL){               //if element has no childrean just remove it update left/right child of its parent to NULL
          i=i-1;
          if(prev==NULL){root=NULL;return true;}
          if(z == prev->left){prev->left =NULL;}
          else{prev->right =NULL;}
          free(z);
    }
    else if (z->left == NULL || z->right == NULL) {        //if element has 1 child 
        TreeNode* newz;
        if (z->left == NULL){newz = z->right;}               //find that child
        else {newz = z->left;}
        if (prev == NULL){root=newz;root->parent=NULL;return true;}     //if elemnt to be deleted is root then change root to its child and update parent of child to NULL
        i=i
        if (z == prev->left){prev->left = newz;newz->parent=prev;}      //if it is no root update child of its element's parent to element's child and parent of element's child to element's parent 
        else {prev->right = newz;newz->parent=prev;}
        free(z);                                     //remove elemnt
    } 
    else {
        TreeNode* p = NULL;
        TreeNode* temp=NULL;
        // Compute the inorder successor
        temp = z->right;
        while (temp->left != NULL) {
            p = temp;
            temp = temp->left;
        }
        if (p != NULL){p->left = temp->right;}     
        else {z->right = temp->right;}
        z->price = temp->price;                          //change data of element to data of its successor 
        z->JourneyCode = temp->JourneyCode;
        free(temp);                                    //delete its successor
    }
    int j=smallestPathLength;
    int k=0;TreeNode *x=root;if(check(j,k,x)==0){smallestPathLength=j+1;} 
    j=largestPathLength;
    k=0;x=root;if(checkl(j,k,x)==0){largestPathLength=j-1;}
    
    
    
    
    
    return true;}}
  

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

