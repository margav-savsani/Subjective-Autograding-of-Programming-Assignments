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

  // REMEMBER to update the heights of appropriate nodes in the tree
  // after an insertion.
  
  // We use "return true" below to enable compilation.  Change this as you
  // see fit.
  TreeNode* x=new TreeNode(jrnyCode,price);
    if(root==nullptr){
        root=x;
        return true;
    }
    else if(find(jrnyCode)!=-1){
        return false;
    }
    else{
        TreeNode* currNode=root;
        while(currNode->left!=nullptr || currNode->right!=nullptr){
            if(!BSTEqualto(x,currNode)&& !BSTLessThan(currNode,x)){
                if(currNode->left==nullptr){
                    updateBSTParentChild(x,currNode,true);
                    updateheight(x);
                    return true;
                }
                currNode=currNode->left;
            }
            else{
                if(currNode->right==nullptr){
                    updateBSTParentChild(x,currNode,false);
                    updateheight(x);
                    return true;
                }
                currNode=currNode->right;
            }
        }
        if(!BSTEqualto(x,currNode)&& !BSTLessThan(currNode,x)){
            updateBSTParentChild(x,currNode,true);
            updateheight(x);
            return true;
        }
        else{
            updateBSTParentChild(x,currNode,false);
            updateheight(x);
            return true;
        }
    }
  return true;
}

// Returns the price on finding an element in the BST that matches
// journey code. Returns -1 otherwise.
// You may assume that no two node in the tree have the same journey
// code, and journey code is the key for insertion and finding in the BST
void BST::updateheight(TreeNode *r){
  if(r==root){
    return ;
  }
  else{
    if(r->parent->left==nullptr){
      r->parent->height++;
      updateheight(r->parent);
      return;
    }
    else if(r->parent->right==nullptr){
      r->parent->height++;
      updateheight(r->parent);
      return;
    }
    else if(r->parent->left->height>r->parent->right->height){
    r->parent->height=r->parent->left->height+1;
    updateheight(r->parent);
    return;}
    else{
    r->parent->height=r->parent->right->height+1;  
    updateheight(r->parent);
    return;
    }
  }
}
void BST::updateheight1(TreeNode *r){
    if(r==nullptr){
        return ;
    }
    if(r->right==nullptr && r->left==nullptr){
        r->height=0;
        return;
    }
    else if(r->right==nullptr){
        updateheight1(r->left);
        r->height=r->left->height+1;
        return;
    }
    else if(r->left==nullptr){
        updateheight1(r->right);
        r->height=r->right->height+1;
        return;
    }
    else{
        updateheight1(r->left);
        updateheight1(r->right);
        if(r->left->height>r->right->height){
            r->height=r->left->height+1;
        }
        else{
            r->height=r->right->height+1;
        }
        return;
    }
}
int BST::find(int jrnyCode)
{
  // Implement find in BST

  // You MUST use only BSTLessThan to compare two journey codes.  You
  // can create a new node containing the journey code to be searched
  // (along with some arbitrary price) and invoke BSTLessThan on the
  // current node in the tree that you are inspecting and the new node
  // to do your comparison.

  // We use "return -1" below to enable compilation.  Change this as you
  // see fit.
  if(root==nullptr){
        return -1;
    }
    else{
        TreeNode t(jrnyCode,10);
        TreeNode *currNode=root;
        while(currNode!=nullptr){
            if(BSTEqualto(&t,currNode)){
                return currNode->getPrice();
            }
            else if(BSTLessThan(&t,currNode)){
                currNode=currNode->left;
            }
            else{
                currNode=currNode->right;
            }
        }
        return -1;
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

bool BST::remove(int jrnyCode)
{
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
      if(find(jrnyCode)==-1){
        return false;
    }
    TreeNode *currNode=root;
    TreeNode d(jrnyCode,10);
    TreeNode *p;
        while(currNode!=nullptr){
            if(BSTEqualto(currNode,&d)){
                break;
            }
            else if(BSTLessThan(&d,currNode)){
                currNode=currNode->left;
            }
            else{
                currNode=currNode->right;
            }
        }
    if(currNode->left==nullptr && currNode->right==nullptr){
        if(currNode==root){
            root=nullptr;
            updateheight1(root);
            return true;
        }
        if(currNode->parent->left==currNode){
            currNode->parent->left=nullptr;
            currNode=nullptr;
            updateheight1(root);
            return true;
        }
        else{
            currNode->parent->right=nullptr;
            currNode=nullptr;
            updateheight1(root);
            return true;
        }
    }
    else if(currNode->left==nullptr || currNode->right==nullptr){
        if(currNode->left==nullptr){
            if(currNode==root){
                root->right->parent=nullptr;
                root=root->right;
                updateheight1(root);
                return true;
            }
            else{
                currNode->right->parent=currNode->parent;
                if(currNode->parent->right==currNode){
                    currNode->parent->right=currNode->right;
                }
                else{
                    currNode->parent->left=currNode->right;
                }
                updateheight1(root);
                return true;
            }
        }
        else{
            if(currNode==root){
                root->left->parent=nullptr;
                root=root->left;
                updateheight1(root);
                return true;
            }
            else{
                currNode->left->parent=currNode->parent;
                if(currNode->parent->left==currNode){
                currNode->parent->left=currNode->left;}
                else{
                    currNode->parent->right=currNode->left;
                }
                updateheight1(root);
                return true;
            }
        }
    }
    else {
        if(currNode==root){
            if(currNode->left->right==nullptr){
                p=currNode->left;
                if(p->left==nullptr){
                    p->right=root->right;
                    root->right->parent=p;
                    root=p;
                    updateheight1(root);
                    return true;
                }
                else{
                    p->right=root->right;
                    root->right->parent=p;
                    root=p;
                    p->left->parent=p->parent;
                    updateheight1(root);
                    return true;
                }
            }
            else{
            p=currNode->left;
            while(p->right!=nullptr){
                p=p->right;
            }
            currNode->change(p);
            p->parent->right=p->left;
            if(p->left==nullptr){
                updateheight1(root);
                return true;
            }
            else{
                p->left->parent=p->parent;
                updateheight1(root);
                return true;
            }
        }
        }
        else{
            p=currNode->left;
            if(p->right==nullptr){
                currNode->change(p);
                p->parent->left=p->left;
                if(p->left==nullptr){
                    updateheight1(root);
                    return true;
                }
                else{
                    p->left->parent=p->parent;
                    updateheight1(root);
                    return true;
                }
            }
            else{
                while(p->right!=nullptr){
                 p=p->right;
                }
                currNode->change(p);
                p->parent->right=p->left;
                if(p->left==nullptr){
                    updateheight1(root);
                    return true;
                }
                else{
                    p->left->parent=p->parent;
                    updateheight1(root);
                    return true;
                }
            }
        }
    }
  updateheight1(root);
  return true;
}


