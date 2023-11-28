#ifndef BST_H
#include "BST.h"
#endif

#ifndef STD_HEADERS
#include <iostream>
#include <stdlib.h>
#endif


// Returns true on successful insertion in BST. Returns false otherwise.
// You may assume that no two elements being inserted have the same journey
// code, and journey code is the key for insertion and finding in the BST

bool BST::insert(int jrnyCode, int price)
{

  TreeNode * B[1000];
   int m=0;
    TreeNode *z= new TreeNode(jrnyCode,price); //make a fake node which is to be inserted 
    TreeNode *y=nullptr;  //these are not the x, y,z mentioned in the lectures
    TreeNode *x=root;
    while(x!=nullptr){
        y=x;  
        m++;
         B[m]=x;   // store the pointers  to the ancestors in an array 
        if (BSTLessThan(z,x)) //using the BST Less than function here
           x=x->left;
        else {x=x->right;}

    }

     m++;
     B[m]= z;
    z->parent=y; //assign the paren to the new node 

    if (y==nullptr) 
      {root=z;
      B[0]=root;}
    else if (BSTLessThan(z,y))  // check if the key of the new node is less than its parent
      updateBSTParentChild(z,y,true);
    else updateBSTParentChild(z,y,false);
        
    int ancestors=m;
    
    while(m>0){  //iterate over all the ansectors 

      B[m]->height= nodelong(B[m]);  ;  // update heights of the ancestors here 
      m--;} 
      
  // Implement insertion in BST

  // You MUST use only BSTLessThan to compare two journey codes.  You
  // can create a new node containing the journey code to be inserted
  // and invoke BSTLessThan on the current node in the tree that you
  // are inspecting and the new node to do your comparison.

  // REMEMBER to update the heights of appropriate nodes in the tree
  // after an insertion.
  
  // We use "return true" below to enable compilation.  Change this as you
  // see fit.
  return true;
}
int BST :: nodelong (TreeNode *x){  //to find the height of the node
 if (x==nullptr) return -1;// as height of leaf is 0

 return max(nodelong(x->left),nodelong( x->right))+1; //recursive
}
// Returns the price on finding an element in the BST that matches
// journey code. Returns -1 otherwise.
// You may assume that no two node in the tree have the same journey
// code, and journey code is the key for insertion and finding in the BST

int BST::find(int jrnyCode)
{  TreeNode *n= new TreeNode(jrnyCode, 100); //create a fake node with the input journey code
  TreeNode *x=root; 
    while(x!=nullptr && jrnyCode!=x->getJourneyCode()){ //iterate over the tree till the journey code is found
        if (BSTLessThan(n, x) ) x=x->left;
        else x=x->right; //compare journey code with each node at each step
    }
    if (x==nullptr) {return -1;} //journey code not found
    else return x->getPrice(); //return the price
  // Implement find in BST

  // You MUST use only BSTLessThan to compare two journey codes.  You
  // can create a new node containing the journey code to be searched
  // (along with some arbitrary price) and invoke BSTLessThan on the
  // current node in the tree that you are inspecting and the new node
  // to do your comparison.

  // We use "return -1" below to enable compilation.  Change this as you
  // see fit.
  return -1;
}

// =====================================================
// OPTIONAL: Implement "remove" only for bonus marks
// =====================================================

// Returns true on successful deletion of the entry in BST with
// matching journey code. Returns false if it cannot find any such element.
//
// You may assume that no two elements in the BST have the same journey
// code, and journey code is the key for insertion and finding in the BST.

TreeNode * BST ::TreeMinimum(TreeNode * x) {    //find the node with minimum journey code
    while (x->left != nullptr){  // go left untill we find a node which does not have a left child
          x=x->left;
    }
    return x;} // return pointer to the node

bool BST::remove(int jrnyCode)
{
  TreeNode * B[1000]; // crete an array of pointers to store the pointers to the node that are the 
  int m=0;          //ancestors of the node to be deleted
  TreeNode *n= new TreeNode(jrnyCode, 100);  //create a fake node with the input journey code
  TreeNode *x=root;
  B[0]=root;     // set the first element of the array as the root pointer
  while(x!=nullptr && jrnyCode!=x->getJourneyCode()){  //find the journey code in the tree
        if (BSTLessThan(n, x) ) {m++ ; B[m]=x->left; x=x->left ;}//simultaneously update the array B as the nodes
        else {m++ ; B[m]=x->left;x=x->right;}                    // encountered on the path will be the ancestors
  }  
  
  if (x==nullptr){    //return false if journey code not found
        return false;
  }
 
  if( (x->left == nullptr) || (x->right == nullptr) ) // check if the node has at most one child
     {  TreeNode *temp ;
        if (x->left == nullptr){ // store the child in a temporary location
            temp=x->right;    
        }
        else {
            temp=x->left;         
        }
            
        if (temp == nullptr){ //the node to be deleted is a leaf
            temp =x; // check whether the leaf was a right or a left child of its parent 
            updateBSTParentChild(nullptr,x->parent,x->parent->left==x);
       }
        else  
        updateBSTParentChild(temp,x->parent,x->parent->left==x);
        
     }

  else
      {  
          TreeNode * temp1 = TreeMinimum(x->right);  //find the  pointer to the successor of the node
          TreeNode temp =*temp1;  //store the values of the successor in a temp node
          remove(temp1->getJourneyCode()); //remove the successor
          TreeNode *left = x->left ; //store the values of the jorney code to be deleted in temporary variables 
          TreeNode *right = x->right ;//which will remain unchanged
          TreeNode *parent = x->parent ;
          
          *x =temp; // copy all values of the successor 
          x->left =left; // update the values that should not have changed
          x->right =right;
          x->parent =parent;
          x->height=nodelong(x); 
          
      }

    m--;
    int ancestors=m;

    while(m>=0){
      
        B[m]->height= nodelong(B[m]);  
        // change values of the height of the ancestors here 
        m--;} 

  // Implement deletion in BST
  
  // You MUST use only BSTLessThan to compare two journey codes.  You
  // can create a new node containing the journey code to be searched
  // (along with some arbitrary price) and invoke BSTLessThan on the
  // current node in the tree that you are inspecting and the new node
  // to do your comparison.

  // REMEMBER to update the height of appropriate nodes in the tree
  // after a successful deletion.
  
  // We use "return true" below to enable compilation.  Change this as you
  // see fit.

  return true;
}


