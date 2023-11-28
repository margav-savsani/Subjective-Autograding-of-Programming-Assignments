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
 if(find(jrnyCode)!=-1){return false;} 
 else{
   TreeNode *N;
   N=new TreeNode(jrnyCode,price);
   TreeNode *x=root;
   TreeNode *T=NULL;
   while(x!=NULL){ 
     T=x;          
     if(BSTLessThan(N,x)) x=x->left;
     else x=x->right;        
     
      }
   N->parent=T;
   if(T==NULL){
           root=N;          
        }
   else {
        if(BSTLessThan(T,N)){
             T->right=N;
             TreeNode *p=T->right;
             if(T->left==NULL){
                while(p->parent!=NULL && (p->parent)->height < p->height + 1){   
                   (p->parent)->height=p->height+1;            //updating the height of all nodes in tree 
                   p=p->parent;
                }
             }
             
            }
        else{
            T->left=N;
            TreeNode *p=T->left;
             if(T->right==NULL){
                while(p->parent!=NULL && (p->parent)->height < p->height + 1){
                   (p->parent)->height=p->height+1;
                   p=p->parent;                     //updating the height of all nodes in tree 
                }
             }
            }
        
    }
    
   return true; 
   }

  // Implement insertion in BST

  // You MUST use only BSTLessThan to compare two journey codes.  You
  // can create a new node containing the journey code to be inserted
  // and invoke BSTLessThan on the current node in the tree that you
  // are inspecting and the new node to do your comparison.

  // REMEMBER to update the heights of appropriate nodes in the tree
  // after an insertion.
  
  // We use "return true" below to enable compilation.  Change this as you
  // see fit.
  //return true;
}

// Returns the price on finding an element in the BST that matches
// journey code. Returns -1 otherwise.
// You may assume that no two node in the tree have the same journey
// code, and journey code is the key for insertion and finding in the BST

int BST::find(int jrnyCode)
{ 
  TreeNode *x=root;
  TreeNode *N;
  
   N=new TreeNode(jrnyCode,10);
     while(x != nullptr ){
         if (BSTLessThan(N,x)) {
             
             if(x->left!= NULL) x=x->left;
             else break;
          }
         else if (BSTLessThan(x,N)){ 
            
            if(x->right!= NULL) x=x->right;
            else break;
          } 
          else return x->getprice(); //returns the price of the corresponding journeycode
         }
  return -1;
  // Implement find in BST

  // You MUST use only BSTLessThan to compare two journey codes.  You
  // can create a new node containing the journey code to be searched
  // (along with some arbitrary price) and invoke BSTLessThan on the
  // current node in the tree that you are inspecting and the new node
  // to do your comparison.

  // We use "return -1" below to enable compilation.  Change this as you
  // see fit.
  //return -1;
}

// =====================================================
// OPTIONAL: Implement "remove" only for bonus marks
// =====================================================

// Returns true on successful deletion of the entry in BST with
// matching journey code. Returns false if it cannot find any such element.
//
// You may assume that no two elements in the BST have the same journey
// code, and journey code is the key for insertion and finding in the BST.

bool BST::remove(int jrnyCode)
{ /*TreeNode* k=NULL;
 TreeNode* x=root;
 while(1){
 if(x==NULL)return false;
 else if(x->JourneyCode == JourneyCode ){         
	   if(x->left == nullptr && x->right == nullptr){
	     
             if(x->parent !=NULL){
	       if(BSTLessThan((x->parent)->price,x->price))
		       (x->parent)->right=NULL;    
	       else 
	       (x->parent)->left=NULL;
	     }
	     else x=NULL;
	     delete x;
      
      }
   else if(x->left != nullptr && x->right == nullptr){
             
	       if(x->parent !=NULL){
	         if(BSTLessThan((x->parent)->price,x->price))
	            (x->parent)->right=x->left;
	         else  
	            (x->parent)->right=x->right;}
	       else root=x->left;
	       delete x;
      }
   else if(x->left == nullptr && x->right != nullptr){
            
             if(x->parent !=NULL){
	       if(BSTLessThan((x->parent)->price,x->price))
		     (x->parent)->left=x->left;
	      else 
	            (x->parent)->left=x->right;
	          }
	     else root=x->right;
	     delete x;
      }
   else {
     TreeNode* T=x;
     TreeNode* P=successor(T);
     int a,b;
     a=P->JourneyCode;
     b=P->price;
     
     remove(P->JourneyCode,P->price);
     T->JourneyCode=a;
     T->price=b;
     
     }
     return true;
     }
  else {
       if (BSTLessThan( price , x->price )) {x=x->left;}
       else {x=x->right;}
      }
     
   }*/
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
/*
TreeNode* BST :: min(TreeNode* k){
  while(k->left !=NULL){
     k=k->left;}
  return k;
}
TreeNode* BST :: successor(TreeNode* k){
 if(k->right!=NULL)
       return min(k->right);
  TreeNode* t=k->parent;
  while((t!=NULL)&&(k=t->right)){ 
  t=t->parent;
  k=t;
  }
  return t;

}*/


