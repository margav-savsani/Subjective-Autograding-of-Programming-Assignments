#ifndef AVL_H
#include "AVL.h"
#endif

#ifndef STD_HEADERS
#include <iostream>
#include <stdlib.h>
#endif

//function for knowing which subtree have greater height at given TreeNode
int AVLTree::higher(TreeNode *x){

    if(x->left==nullptr) {return 1;}
    else if(x->right==nullptr) {return 0;}
    else { if((x->left)->height>(x->right)->height) return 0; else return 1; }
}

//function for calculating difference between left and right subtrees at given TreeNode.
int AVLTree::hd(TreeNode *x){

    if(x->left==nullptr&&x->right==nullptr){ return 0;}
    else if( x->left==nullptr) { return (x->right)->height+1; }
    else if(x->right==nullptr) { return (x->left)->height+1; }
    else { return abs((x->left)->height,(x->right)->height);}
}

// function for calculating absolute difference between integers
int AVLTree::abs(int x,int y){ 

    if(x>y) return x-y; 
    else return y-x; 
}

//function for updating heights after inserting a element
void AVLTree::updateheight(TreeNode *x){ 

    if(x->left==nullptr||x->right==nullptr){ 
    
        if(x->left==nullptr) {x->height=(x->right)->height+1;}
        else if(x->right==nullptr) {x->height=(x->left)->height+1;}   
     }
    else { 
    
        if((x->left)->height>(x->right)->height) x->height=(x->left)->height+1;
        else x->height=(x->right)->height+1;
     }
     
    if(x->parent==nullptr) return; 
    else updateheight(x->parent);                                            
}

// function for finding parentnode for element being added
TreeNode* AVLTree::parent(TreeNode *x,TreeNode node){
        if(AVLLessThan(&node,x)) { 
              
             if(x->left == nullptr){return x;}
             else { return parent(x->left,node);}  
         } 
         
         else if(AVLLessThan(x,&node)){	
             
             if(x->right == nullptr){return x;}
             else {return parent(x->right,node);}
         }  
         
         else{
              if(x->left==nullptr){ return x;}
              else if(x->right==nullptr) {return x;}
              else {return parent(x->right,node);}
         }
}

// function to return pointer pointing to that node if present otherwise returns nullptr
TreeNode* AVLTree::findelement(TreeNode* x,TreeNode node){
   
   if(AVLLessThan(x,&node)){
   
       if(x->right==nullptr) return nullptr; 
       else return findelement(x->right,node);
   }
   else if(AVLLessThan(&node,x)) {
   
       if(x->left==nullptr) return nullptr; 
       else return findelement(x->left,node);
   }
   else { return x; } 
}

bool AVLTree::rotateLeftLeft(TreeNode *currNode, TreeNode *parentNode, TreeNode *grandParentNode)
{

  TreeNode *greatGrandParentNode = grandParentNode->parent;
  
  bool isGPLeftChild;
  if(greatGrandParentNode!=nullptr){
  if (greatGrandParentNode->left == grandParentNode) {
    isGPLeftChild = true;
  }
  else if (greatGrandParentNode->right == grandParentNode) {
    isGPLeftChild = false;
  }
  else {                                                                    
    cerr << "Unexpected condition encountered!" << endl;
    return false;
  }

  updateAVLParentChild(parentNode, greatGrandParentNode, isGPLeftChild); }

  updateAVLParentChild(currNode, parentNode, true);
  
   TreeNode *T3 = parentNode->right;
  
  updateAVLParentChild(grandParentNode, parentNode, false);

  updateAVLParentChild(T3, grandParentNode, true);
  
  if(greatGrandParentNode==nullptr) root=parentNode;root->parent=nullptr;
  
  grandParentNode->height-=2;updateheight(parentNode);

  return true;
}

bool AVLTree::rotateRightRight(TreeNode *currNode, TreeNode *parent, TreeNode *grandParent)
{
  TreeNode *greatGrandParentNode = grandParent->parent;
  
  bool isGPLeftChild;
  if(greatGrandParentNode!=nullptr){
  if (greatGrandParentNode->left == grandParent) {
    isGPLeftChild = true;
  }
  else if (greatGrandParentNode->right == grandParent) {
    isGPLeftChild = false;
  }
  else {
    cerr << "Unexpected condition encountered!" << endl;
    return false;
  }
  
  updateAVLParentChild(parent, greatGrandParentNode, isGPLeftChild);}
  
  updateAVLParentChild(currNode, parent, false);
  
   TreeNode *T3 = parent->left;
   
  updateAVLParentChild(grandParent, parent, true);
  
  updateAVLParentChild(T3, grandParent, false);
  
  if(greatGrandParentNode==nullptr) root=parent;root->parent=nullptr;
  
  grandParent->height-=2;updateheight(parent);
  
  return true;
}

bool AVLTree::rotateLeftRight(TreeNode *currNode, TreeNode *parentNode, TreeNode *grandParentNode)
{

  TreeNode *greatGrandParentNode = grandParentNode->parent;

  bool isGPLeftChild;
  if(greatGrandParentNode!=nullptr){
  if (greatGrandParentNode->left == grandParentNode) {
    isGPLeftChild = true;
  }
  else if (greatGrandParentNode->right == grandParentNode) {
    isGPLeftChild = false;
  }
  else {
    cerr << "Unexpected condition encountered!" << endl;
    return false;
  }

  updateAVLParentChild(currNode, greatGrandParentNode, isGPLeftChild);}
  
  TreeNode *T2 = currNode->left;
  
  TreeNode *T3 = currNode->right;

  updateAVLParentChild(parentNode, currNode, true);
  
  updateAVLParentChild(grandParentNode, currNode, false);

  updateAVLParentChild(T2, parentNode, false);

  updateAVLParentChild(T3, grandParentNode, true);
  
  if(greatGrandParentNode==nullptr) root=parentNode;root->parent=nullptr;

  grandParentNode->height-=2; parentNode->height-=1;updateheight(currNode);
  
  return true;
}

bool AVLTree::rotateRightLeft(TreeNode *currNode, TreeNode *parent, TreeNode *grandParent)
{
  TreeNode *greatGrandParentNode = grandParent->parent;

  bool isGPLeftChild;
  if(greatGrandParentNode!=nullptr){
  if (greatGrandParentNode->left == grandParent) {
    isGPLeftChild = true;
  }
  else if (greatGrandParentNode->right == grandParent) {
    isGPLeftChild = false;
  }
  else {
    cerr << "Unexpected condition encountered!" << endl;
    return false;
  }
  
  updateAVLParentChild(currNode, greatGrandParentNode, isGPLeftChild);}
  
  TreeNode *T2 = currNode->left;
  
  TreeNode *T3 = currNode->right;
  
  updateAVLParentChild(parent, currNode, false);
  
  updateAVLParentChild(grandParent, currNode, true);
  
  updateAVLParentChild(T3, parent, true);

  updateAVLParentChild(T2, grandParent, false);
  
  if(greatGrandParentNode==nullptr) root=parent;root->parent=nullptr;
  
  grandParent->height-=2; parent->height-=1;updateheight(currNode);
  
  return true;
}

bool AVLTree::insert(int jrnyCode, int price)
{
    bool imbalanced=false;
  
    if( root ==nullptr){
        root = new TreeNode(jrnyCode,price); 
        root->left=nullptr;root->right=nullptr;root->parent=nullptr;
        root->height=0;
    }
    else{  
       TreeNode node(jrnyCode,price);
       TreeNode* n = parent(root,node);
       
       if(AVLLessThan(&node,n)) { 
            
             n->left=new TreeNode(jrnyCode,price);
            (n->left)->parent=n; (n->left)->height=0;
           
       }
       else {
             
             n->right=new TreeNode(jrnyCode,price);
            (n->right)->parent=n;(n->right)->height=0;
       } 
            
         updateheight(n);
        
       //while loop for checking any imbalanced TreeNode     
       while(true){
       
           if(hd(n)>1) {    imbalanced = true;
           
               if(higher(n)==0){
               
                   if(higher(n->left)==0){rotateLeftLeft((n->left)->left, n->left, n);}
                   else{rotateLeftRight((n->left)->right, n->left, n);}
               }
               else{
               
                   if(higher(n->right)==0){rotateRightLeft((n->right)->left, n->right, n);}
                   else {rotateRightRight((n->right)->right, n->right, n);}
               }
          
           }
      
          if(n->parent==nullptr||imbalanced==true) break;    
          n=n->parent;   
       }
   
     }
  return true;
}

int AVLTree::find(int jrnyCode)
{
  if(root==nullptr) { return -1;}
  else {  
          TreeNode node(jrnyCode,0);
          TreeNode* x=findelement(root,node);
          
          if(x==nullptr) { return -1;}
          else { return x->getprice(); }
  }
}

bool AVLTree::remove(int jrnyCode){
   return true;
}
