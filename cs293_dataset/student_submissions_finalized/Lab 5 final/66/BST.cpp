#include "BST.h"

#ifndef STD_HEADERS
#include <iostream>
#include <stdlib.h>
#endif

// function for updating heights of ancestor nodes after inserting a element
void BST::updateheight(TreeNode *x){ 

    if(x->left==nullptr||x->right==nullptr){ 
    
        if(x->left==nullptr) {x->height=(x->right)->height+1;}
        else if(x->right==nullptr) {x->height=(x->left)->height+1;}
    }
    else{ 
    
        if((x->left)->height>(x->right)->height)  {x->height=(x->left)->height+1;}
        else  {x->height=(x->right)->height+1;} 
    }
    
    if(x->parent==nullptr) return; 
    else updateheight(x->parent);                                            
}

// function to return pointer pointing to that node if present otherwise returns nullptr
TreeNode* BST::findelement(TreeNode* x,TreeNode node){
   
   if(BSTLessThan(x,&node)){ 
   
             if(x->right==nullptr) {return nullptr;} 
             else {return findelement(x->right,node);}
        }
   else if(BSTLessThan(&node,x)) { 
   
             if(x->left==nullptr) {return nullptr;} 
             else {return findelement(x->left,node);}
        }
   else { return x; } 
}

// function for finding parentnode for element being added 
TreeNode* BST::parent(TreeNode *x,TreeNode node){
    if(BSTLessThan(&node,x)) { 
    
             if(x->left == nullptr){return x;}
             else { return parent(x->left,node);}  
         } 
         
         else if(BSTLessThan(x,&node)){	
         
             if(x->right == nullptr){return x;}
             else {return parent(x->right,node);}
         }  
         
         else{ 
         
              if(x->left==nullptr){ return x;}
              else if(x->right==nullptr) {return x;}
              else {return parent(x->right,node);}
         }
}

bool BST::insert(int jrnyCode, int price)
{
    if( root ==nullptr){
    
        root = new TreeNode(jrnyCode,price); 
        root->left=nullptr;root->right=nullptr;root->parent=nullptr;
        root->height=0;
    } 
    else{ 
        TreeNode node(jrnyCode,price);
        TreeNode* n = parent(root,node);
       
        if(BSTLessThan(&node,n)) { 
            
            n->left = new TreeNode(jrnyCode,price);
            (n->left)->parent=n; (n->left)->height=0;totalParentChildUpdateCost += perParentChildUpdateCost;
           
        }
        else {
        
            n->right=new TreeNode(jrnyCode,price);
            (n->right)->parent=n;(n->right)->height=0;totalParentChildUpdateCost += perParentChildUpdateCost;
        } 
        updateheight(n);
    }
  
  return true;
}

int BST::find(int jrnyCode)
{
  if(root==nullptr) { return -1;}
  else {  
          TreeNode node(jrnyCode,0);
          TreeNode* x=findelement(root,node);
          
          if(x==nullptr) { return -1 ;}
          else { return x->getprice();}
  }
}

bool BST::remove(int jrnyCode){
    return true;
}

