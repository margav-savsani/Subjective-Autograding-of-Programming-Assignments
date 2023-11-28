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
  // Implement insertion in BST

  // You MUST use only BSTLessThan to compare two journey codes.  You
  // can create a new node containing the journey code to be inserted
  // and invoke BSTLessThan on the current node in the tree that you
  // are inspecting and the new node to do your comparison.

    TreeNode* x = root; //for checking
    TreeNode* y = NULL; //for pointing to the parent
    TreeNode* node = new TreeNode(jrnyCode, price);

    if(root == NULL){
        root = node;
        return true;
    }

    while(x != NULL){
        // cout<<"x not null";
        y = x;
        // if(x->price == price && x->JourneyCode == JourneyCode){
        //     return false;
        // }
        if( BSTLessThan(node, x) ){
            x = x->left;
        }
        else{
            x = x->right;
        }
    }
    
    // node->parent = y;

    if( BSTLessThan(node, y)){
        // y->left = node;
        updateBSTParentChild(node,y,true);
    }
    else{
        // y->right = node;
        updateBSTParentChild(node,y,false);
    }

    x = node->parent;
    if(x->right==NULL || x->left==NULL){
      x->height += 1;
    }

    x = x->parent;
    while(x!=NULL){
      // if(x->parent != NULL && x->parent->height==max(x->left->height, x->right->height)+1)
      if(x->right==NULL){
        x->height = x->left->height + 1;
      }
      else if(x->left==NULL){
        x->height = x->right->height + 1;
      }
      else{
        x->height = max(x->left->height, x->right->height) + 1;
      }
      // if(x->parent!=NULL){

      //           if(x->parent != NULL && x->parent->height==x->height+1)
      //     break;
      //             if(x->parent != NULL && x->parent->height==x->height+1)
      //     break;
      //             if(x->parent != NULL && x->parent->height== max(x->parent->left->height, x->parent->right->height)+1 )
      //     break;
      // }
      x = x->parent;
    }

    
    return true;

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
  // Implement find in BST

  // You MUST use only BSTLessThan to compare two journey codes.  You
  // can create a new node containing the journey code to be searched
  // (along with some arbitrary price) and invoke BSTLessThan on the
  // current node in the tree that you are inspecting and the new node
  // to do your comparison.

   TreeNode* temp = root; 
   TreeNode* dummy = new TreeNode( jrnyCode, 0); //price arbitrary since comparision is on jc

    while(temp != NULL){
        if(!BSTLessThan(temp, dummy) && !BSTLessThan(dummy, temp)){
            return 1;
        }
        if(BSTLessThan(dummy, temp)){
            temp = temp->left;
        }
        else{
            temp = temp->right;
        }
    }
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
TreeNode* BST::succ( TreeNode* x){
    if(x->right!=NULL)
        return BST::getMinimum(x->right);
    else{
        TreeNode* y = x->parent;
        if(y==NULL)
            return NULL;
        while( y != NULL && x==y->right){
            x=y;
            y=y->parent;
        }
        return y;
    }
}

TreeNode* BST::getMinimum(TreeNode* t){
    TreeNode* temp = t;
    TreeNode* temp2 = NULL;

    if(temp==NULL){
        return NULL;
    }

    while( temp != NULL){
        temp2 = temp;
        temp = temp->left;
    }
    
    return temp2; 
}

bool BST::remove(int jrnyCode)
{
  // Implement deletion in BST
  
  // You MUST use only BSTLessThan to compare two journey codes.  You
  // can create a new node containing the journey code to be searched
  // (along with some arbitrary price) and invoke BSTLessThan on the
  // current node in the tree that you are inspecting and the new node
  // to do your comparison.
        TreeNode* temp = root;
        TreeNode* x = NULL;
        TreeNode* node = new TreeNode(jrnyCode, 0);

        while( !BSTLessThan(node, temp) && !BSTLessThan(temp,node) && temp!=NULL ){
            if(BSTLessThan(node, temp) ){
                temp = temp->left;
            }
            else{
                temp = temp->right;
            }
        }
        if(temp==NULL)  
            return false;

        // if(temp->JourneyCode == JourneyCode){ //node to be deleted is found, its temp why to check again if temp is not null means found

            //------when temp is the leaf------
            if(temp->left==NULL && temp->right==NULL){ 
                
                if(temp->parent==NULL){ //deleting root node
                    root = NULL; //tree deleted
                    return true;
                }
                if(temp->parent->left == temp){ //temp is the leftchild of its parent
                    x = temp->parent;
                    updateBSTParentChild(NULL, temp->parent, true);
                    // temp->parent->left = NULL; //temp deleted
                    temp = x;
                }
                else{ 
                    x = temp->parent;
                    updateBSTParentChild(NULL, temp->parent, false);
                    // temp->parent->right = NULL; //temp being rightchild
                    temp = x;
                }
            } 
            //---------temp has only one child--------
            else if(temp->left==NULL || temp->right==NULL){

                TreeNode* p,  *notNullChild;
                p = temp->parent;  //p is the parent of temp

                //notNullChild is the only not NULL child of temp
                if(temp->left==NULL){
                    notNullChild=temp->right;
                }
                else{
                    notNullChild = temp->left;
                }
         
                if(p==NULL){
                    root = notNullChild;
                    root->parent=NULL;
                    return true;
                }
                // cout<<"oh no";
                if(p->left == temp){ //temp is the leftchild of p
                    // p->left =  notNullChild;
                    // notNullChild->parent = p;
                    x = temp->parent;
                    updateBSTParentChild( notNullChild, p, true);
                    temp = x;
                    // return true;
                }
                else{ //temp being right child  
                    // p->right = notNullChild;
                    // notNullChild->parent = p;
                    x = temp->parent;
                    updateBSTParentChild( notNullChild, p, false);
                    temp = x;
                    // return true;
                }
            }
            //---------temp has two children---------
            else{

                TreeNode* suc = BST::succ(temp);
                x = suc->parent;
                bool yes = BST::remove(suc->getjc());
                if(!yes)
                    return false;
                updateBSTParentChild(temp->left, suc, true);
                updateBSTParentChild(temp->right, suc, false);
                if(temp->parent==NULL)
                  root = suc;
                else{
                  if(temp->parent->left==temp)//temp is the left child
                    updateBSTParentChild(suc, temp->parent, true);
                  else
                    updateBSTParentChild(suc, temp->parent, false);
                }
                temp = x;
                // return true;
            }

  // REMEMBER to update the height of appropriate nodes in the tree
  // after a successful deletion.\
    x = temp;
    while(x!=NULL){
      if(x->right==NULL && x->left==NULL){
        x->height = 0;
      }
      else if(x->right==NULL)
        x->height = x->left->height+1;
      else if(x->left==NULL)
        x->height = x->right->height+1;
      else{
        //no child of x is null
        x->height = max(x->left->height, x->right->height) + 1;
      }
      x = x->parent;
    }
  
  // We use "return true" below to enable compilation.  Change this as you
  // see fit.

  return true;
}


