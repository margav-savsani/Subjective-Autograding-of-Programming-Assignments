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

     TreeNode* z = new TreeNode(jrnyCode,price);
     if(find (jrnyCode) != -1 )return false;   
     TreeNode* y = nullptr;
      TreeNode* x = root;

      while(x != nullptr){
        y=x;
       if (BSTLessThan(z,x))
       {
        x = x->left;
       }
        else {x= x->right;}
      }
     z->parent = y;
     if (y == nullptr)
     {
      root = z;

     }
     else if (BSTLessThan(z,y)){
      y->left = z;
      }
     else {y->right = z;}

      


  //  this->printBST("",false);
    return true;

  // Implement insertion in BST

  // You MUST use only BSTLessThan to compare two journey codes.  You
  // can create a new node containing the journey code to be inserted
  // and invoke BSTLessThan on the current node in the tree that you
  // are inspecting and the new node to do your comparison.

  // REMEMBER to update the heights of appropriate nodes in the tree
  // after an insertion.
  
  // We use "return true" below to enable compilation.  Change this as you
  // see fit.
}

// Returns the price on finding an element in the BST that matches
// journey code. Returns -1 otherwise.
// You may assume that no two node in the tree have the same journey
// code, and journey code is the key for insertion and finding in the BST

int BST::find(int jrnyCode)
{
 TreeNode* x = root;
 TreeNode* y = new TreeNode(jrnyCode,0);
 while (x != nullptr )
 {    if(x->isequal(jrnyCode) ){return x->getprice(); }

   else if(BSTLessThan(y, x)){
            x=x->left;
     }
     else  x = x->right;
 }
    






    
  // Implement find in BST

  // You MUST use only BSTLessThan to compare two journey codes.  You
  // can create a new node containing the journey code to be searched
  // (along with some arbitrary price) and invoke BSTLessThan on the
  // current node in the tree that you are inspecting and the new node
  // to do your comparison.

  // We use "return -1" below to enable compilation.  Change this as you
  // see fit.
return -1;
};

 // =====================================================
 // OPTIONAL: Implement "remove" only for bonus marks
 // =====================================================

 // Returns true on successful deletion of the entry in BST with
 // matching journey code. Returns false if it cannot find any such element.
 //
 // You may assume that no two elements in the BST have the same journey
 // code, and journey code is the key for insertion and finding in the BST.

 //bool BST::remove(int jrnyCode)
// {
//   if(!find(JourneyCode,price))return false;
    
//     TreeNode* curr = root;
//     bool last = false;

//     // finding the  node to be deleted
//     while(true){
//         curr->sizeOfTree--; // Decrement size of subtree for each parent node!
//         if(curr->JourneyCode==JourneyCode && curr->price==price){
//             break;
//         }else if(curr->price > price){
//             curr = curr->left;
//             last = true;
//         }else{
//             curr = curr->right;
//             last = false;
//         }
//     }
//     // If it has no left child, just replace the node with its right child!
//     if(curr->left==NULL){
    
//         if(curr->parent!=NULL){
//             if(last){
//                 curr->parent->left = curr->right;
//             }else{
//                 curr->parent->right = curr->right;
//             }
//             if(curr->right!=NULL){
//                 curr->right->parent = curr->parent;
//             }
//             delete curr;
//         }else{
//             root = curr->right;
//             delete curr;  
//         }
//     }else if(curr->right==NULL){
//         //   If it has no right child, just replace it with left child
//         if(curr->parent!=NULL){
//             if(last){
//                 curr->parent->left = curr->left;
//             }else{
//                 curr->parent->right = curr->left;
//             }
//             curr->left->parent = curr->parent;
            
//             delete curr;
//         }else{
//             root = curr->left;
//             delete curr;     
//         }
//     }else{
//         // If its has both left and right children

//         TreeNode *todel = curr; // Marking the node which is to be deleted
        
//         // Find its predecessor
//         curr = curr->left;
//         last = false;
        
        
//         while(curr->right!=NULL){
            
//             curr->sizeOfTree--;
//             curr = curr->right;
//             last = true;
//         }

//         // Swap the node with its predecessor
//         todel->JourneyCode = curr->JourneyCode;
//         todel->price = curr->price;
//         if(!last){
//             curr->parent->left = curr->left;
//         }else{
//             curr->parent->right = curr->left;
//         }
//         if(curr->left!=NULL)curr->left->parent = curr->parent;
        
//         // Delete the node which previously represented the predecessor
//         delete curr;
        
//     }
  
//     return true; 
// }// Implement deletion in BST
  
  // You MUST use only BSTLessThan to compare two journey codes.  You
  // can create a new node containing the journey code to be searched
  // (along with some arbitrary price) and invoke BSTLessThan on the
  // current node in the tree that you are inspecting and the new node
  // to do your comparison.

  // REMEMBER to update the height of appropriate nodes in the tree
  // after a successful deletion.
  
  // We use "return true" below to enable compilation.  Change this as you
  // see fit.



