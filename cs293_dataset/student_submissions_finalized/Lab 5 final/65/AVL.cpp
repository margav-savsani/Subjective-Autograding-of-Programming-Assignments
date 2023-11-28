#ifndef AVL_H
#include "AVL.h"
#endif

#ifndef STD_HEADERS
#include <iostream>
#include <stdlib.h>
#include <cmath>
#endif

bool AVLTree::rotateLeftLeft(TreeNode *currNode, TreeNode *parentNode, TreeNode *grandParentNode)
{
  

  TreeNode *greatGrandParentNode = grandParentNode->parent;
   TreeNode *T3 = parentNode->right; 
  
  if(greatGrandParentNode!=NULL){
  bool isGPLeftChild;
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

 
  updateAVLParentChild(parentNode, greatGrandParentNode, isGPLeftChild);
  }
  if(greatGrandParentNode==NULL){
    root=parentNode;
    root->parent=NULL;
  }
  
  updateAVLParentChild(currNode, parentNode, true);
    
  updateAVLParentChild(grandParentNode, parentNode, false);

  if(T3!=NULL){
  updateAVLParentChild(T3, grandParentNode, true);
  }
  else {grandParentNode->left=NULL;}
  return true;
}

bool AVLTree::rotateLeftRight(TreeNode *currNode, TreeNode *parentNode, TreeNode *grandParentNode)
{
  

  TreeNode *greatGrandParentNode = grandParentNode->parent;
  TreeNode *T2 = currNode->left;
  TreeNode *T3 = currNode->right;
  
  if(greatGrandParentNode!=NULL){
  bool isGPLeftChild;
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

  updateAVLParentChild(currNode, greatGrandParentNode, isGPLeftChild);
  }
  if(greatGrandParentNode==NULL){
    root=currNode;
    root->parent=NULL;
  }
  
  updateAVLParentChild(parentNode, currNode, true);
  
  updateAVLParentChild(grandParentNode, currNode, false);
  
  if(T2!=NULL){
  updateAVLParentChild(T2, parentNode, false);
  }
  else{parentNode->right=NULL;}

  if(T3!=NULL){
  updateAVLParentChild(T3, grandParentNode, true);
  }
  else {grandParentNode->left=NULL;}
  return true;
}

bool AVLTree::rotateRightLeft(TreeNode *currNode, TreeNode *parentNode, TreeNode *grandParent)
{
  // Implement this yourself
  TreeNode *greatGrandParentNode = grandParent->parent;
  TreeNode *T2 = currNode->left;
  TreeNode *T3 = currNode->right;
 
  
  if(greatGrandParentNode!=NULL){
  bool isGPLeftChild;
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

  updateAVLParentChild(currNode,greatGrandParentNode,isGPLeftChild);
  }
  if(greatGrandParentNode==NULL){
      root=currNode;
      root->parent=NULL;
  }
  updateAVLParentChild(grandParent,currNode,true);

  updateAVLParentChild(parentNode,currNode,false);

  if(T2!=NULL){
  updateAVLParentChild(T2,grandParent,false);
  }
  else{grandParent->right=NULL;}
  if(T3!=NULL){
  updateAVLParentChild(T3,parentNode,true);
  }
  else {grandParent->left=NULL;}

  return true;
}

bool AVLTree::rotateRightRight(TreeNode *currNode, TreeNode *parentNode, TreeNode *grandParent)
{
  // Implement this yourself
  TreeNode *greatGrandParentNode = grandParent->parent;
  TreeNode *T2 = parentNode->left;
if(greatGrandParentNode!=NULL)
  {
  
  bool isGPLeftChild;
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
  
  updateAVLParentChild(parentNode,greatGrandParentNode,isGPLeftChild);
  }
  if(greatGrandParentNode==NULL){
    root=parentNode;
    root->parent=NULL;
  }
  
  updateAVLParentChild(currNode,parentNode,false);

  updateAVLParentChild(grandParent,parentNode,true);
  
  if(T2!=NULL){
  updateAVLParentChild(T2,grandParent,false);
  }
  else {grandParent->right=NULL;}
  return true;
}
//********

//Change height:
// This will take a treenode as an argument and checks the height of the 
//children, and takes the value of the highest height added with 1 as its height.

//********
void AVLTree::changeheightAVL(TreeNode *node){
  
  if(node->right==NULL && node->left!=NULL){
    node->height=node->left->height+1;
  }
  else if(node->left==NULL && node->right!=NULL){
    node->height=node->right->height+1;
  }
  else if(node->left==NULL && node->right==NULL){
    node->height=1;
  }
  else if(node->right->height>=node->left->height){
    node->height=node->right->height +1 ;
  }
  else if(node->right->height<node->left->height){
    node->height=node->left->height +1 ;
  }
  
  if(node->parent != NULL){
    changeheightAVL(node->parent);
  }
}

//returns the first node where there is an imbalance

TreeNode* AVLTree::findfirst(TreeNode *node){
  
    TreeNode *dummyparent=node->parent;
    if(dummyparent==NULL){
      return NULL;
    }
    else if(dummyparent->left==NULL && dummyparent->right==NULL){
       return findfirst(dummyparent);
    }
    else if(dummyparent->left==NULL && dummyparent->right !=NULL){
      if(dummyparent->right->height>1){
      return dummyparent;
      }
      else return findfirst(dummyparent);
    }
    else if(dummyparent->right==NULL && dummyparent->left!=NULL){
     
      if(dummyparent->left->height>1){
      return dummyparent;
      }
       else return findfirst(dummyparent);
    }
    
    else if(abs(dummyparent->right->height - dummyparent->left->height)>1){
      return dummyparent;
    }
}


bool AVLTree::insert(int jrnyCode, int price)
{
  
  if( find(jrnyCode)!= -1){
            return false;
    }
         TreeNode *A=new TreeNode(jrnyCode,price);

         TreeNode *y=NULL;
         TreeNode *x=root;

         while(x!=NULL){
            y=x;
            if(AVLLessThan(A,x)){
                x=x->left;

            }
            else x=x->right;
         }
        
        if(y==NULL){
            root=A;
            root->parent=y;
            root->height=1;
        }
        else if(AVLLessThan(A,y)){
          y->left=A;
          y->left->updateParentChild(y,true);
          y->left->height=1;  
          changeheightAVL(y);

          TreeNode* grandParent=findfirst(A);
          cout<<grandParent->getJourneyCode()<<endl;
              if(grandParent!=NULL){

                if(AVLLessThan(A,grandParent)){
                  TreeNode* par=grandParent->left;
                  
                  if(AVLLessThan(A,par)){
                    TreeNode* curr=par->left;
                    //******
                    //rotation
                    //******
                    rotateLeftLeft(curr,par,grandParent);
                    //****
                    //changing heights after rotation.
                    //*****
                    if(curr->left!=NULL){
                    changeheightAVL(curr->left);
                    }
                    else{
                      changeheightAVL(curr);
                    }
                    if(grandParent->left!=NULL){
                    changeheightAVL(grandParent->left);
                    }
                    else {changeheightAVL(grandParent);}
                  }
                  else if(!AVLLessThan(A,par)){
                    TreeNode* curr=par->right;
                    rotateLeftRight(curr,par,grandParent);
                    if(par->left!=NULL){
                    changeheightAVL(par->left);
                    }
                    else{changeheightAVL(par);}
                    if(grandParent->left!=NULL){
                    changeheightAVL(grandParent->left);
                    }
                    
                    else{changeheightAVL(grandParent);}
                  } 
                }

                else if(!AVLLessThan(A,grandParent)){
                  
                  TreeNode* par=grandParent->right;
                  
                  if(AVLLessThan(A,par)){
                  
                    TreeNode* curr=par->left;
                    rotateRightLeft(curr,par,grandParent);
                    if(grandParent->left!=NULL){
                    changeheightAVL(grandParent->left);
                    }
                    else {changeheightAVL(grandParent);}
                    if(par->left!=NULL){
                    changeheightAVL(par->left);
                    }
                    else {changeheightAVL(par);}
                  }
                  else if(!AVLLessThan(A,par)){
                    TreeNode* curr=par->right;
                    rotateRightRight(curr,par,grandParent);

                    if(grandParent->left!=NULL){
                    changeheightAVL(grandParent->left);
                    }
                    else{changeheightAVL(grandParent);}

                    if(curr->left!=NULL){
                    changeheightAVL(curr->left);
                    }
                    else{changeheightAVL(curr);}
                  } 
                }
              }
         }
        else {
          y->right=A;
          y->right->updateParentChild(y,false);
          y->right->height=1;
          changeheightAVL(y);
  
      
          TreeNode* grandParent=findfirst(A);
              if(grandParent!=NULL){
        
                if(AVLLessThan(A,grandParent)){

                  TreeNode* par=grandParent->left;
                  
                  if(AVLLessThan(A,par)){
                  
                    TreeNode* curr=par->left;
                    rotateLeftLeft(curr,par,grandParent);
                    if(curr->left!=NULL){
                    changeheightAVL(curr->left);
                    }
                    else {changeheightAVL(curr);}
                    if(grandParent->left!=NULL){
                    changeheightAVL(grandParent->left);
                    }
                    else{changeheightAVL(grandParent);}
                  }
                  else if(!AVLLessThan(A,par)){
                    TreeNode* curr=par->right;
                    rotateLeftRight(curr,par,grandParent);
                    if(par->left!=NULL){
                    changeheightAVL(par->left);
                    }
                    else{changeheightAVL(par);}
                    if(grandParent->left!=NULL){
                    changeheightAVL(grandParent->left);
                    }
                    else{changeheightAVL(grandParent);}
                  } 
                }

                else if(!AVLLessThan(A,grandParent)){
                  
                  TreeNode* par=grandParent->right;
          
                  
                  if(AVLLessThan(A,par)){
                  
                    TreeNode* curr=par->left;
                    rotateRightLeft(curr,par,grandParent);
                    if(grandParent->left!=NULL){
                    changeheightAVL(grandParent->left);
                    }
                    else{changeheightAVL(grandParent);}
                    if(par->left!=NULL){
                    changeheightAVL(par->left);
                    }
                    else{changeheightAVL(par);}
                  }
                  else if(!AVLLessThan(A,par)){
                    TreeNode* curr=par->right;
            
                    rotateRightRight(curr,par,grandParent);
                    
                  
                    if(grandParent->left!=NULL){
                    changeheightAVL(grandParent->left);
                    }
                    else {
                      changeheightAVL(grandParent);
                      } 
                  
                    if(curr->left!=NULL){
                    changeheightAVL(curr->left);
                    }
                    else {changeheightAVL(curr);} 
                  } 
                }
              }
        }
    return true; 
}
int AVLTree::find(int jrnyCode)
{ 
  TreeNode *A=new TreeNode(jrnyCode,0);
     TreeNode *x;
     x=root;
     while(x!=NULL && A->getJourneyCode()!=x->getJourneyCode()){
        if(AVLLessThan(A,x)){
            x=x->left;
        }
        else {x=x->right;}
     }
     if(x==NULL){
        return -1;
     }
     else {return x->getprice();}

}
bool AVLTree:: remove(int jrnyCode){return true;}
