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
void BST::change_height(TreeNode* z){
    TreeNode* y=z;
    TreeNode* x=y->parent;
    while(x!=nullptr){
        if(x->left==y){
            if(x->right==nullptr){
                x->height=x->left->height+1;
            }
            else{
                x->height=max(x->right->height+1,x->left->height+1);
            }
         }
         else{
            if(x->left==nullptr){
                x->height=x->right->height+1;
            }
            else{
                x->height=max(x->right->height+1,x->left->height+1);
            }
         }
         y=x;
         x=x->parent;
    }
}

bool BST::insert(int jrnyCode, int price){
  // Implement insertion in BST

  // You MUST use only BSTLessThan to compare two journey codes.  You
  // can create a new node containing the journey code to be inserted
  // and invoke BSTLessThan on the current node in the tree that you
  // are inspecting and the new node to do your comparison.

  // REMEMBER to update the heights of appropriate nodes in the tree
  // after an insertion.
  
  // We use "return true" below to enable compilation.  Change this as you
  // see fit.
  if(find(jrnyCode)==1) return 0;
    TreeNode* node = new TreeNode(jrnyCode, price);
    if (root == nullptr){
        root =node;
        root->parent = nullptr;
        root->height=0;
        return true;
    }
    TreeNode* n = root;
    bool i = 0;
    while (i == 0){
        if(BSTLessThan(n,node)){
            if (n->right== nullptr){
                updateBSTParentChild(node,n,0);
                node->height=0;
                i=1;
            }
            else n = n->right;
        }
        else{
            if (n->left == nullptr){
                updateBSTParentChild(node,n,1);
                node->height=0;
                i=1;
            }
            else n = n->left;
        }
    }
    change_height(node);
    return i;
}

// Returns the price on finding an element in the BST that matches
// journey code. Returns -1 otherwise.
// You may assume that no two node in the tree have the same journey
// code, and journey code is the key for insertion and finding in the BST

int BST::find(int jrnyCode){
  // Implement find in BST

  // You MUST use only BSTLessThan to compare two journey codes.  You
  // can create a new node containing the journey code to be searched
  // (along with some arbitrary price) and invoke BSTLessThan on the
  // current node in the tree that you are inspecting and the new node
  // to do your comparison.

  // We use "return -1" below to enable compilation.  Change this as you
  // see fit.
    TreeNode* node = new TreeNode(jrnyCode,10);
    if (root == nullptr) return 0;
    TreeNode * n = root;
    bool found = 0;
    while (n!=nullptr){
        if (!BSTLessThan(n,node) && !BSTLessThan(node,n)){
            found=1;
            return true;
        }
        if (BSTLessThan(n,node)){
            n= n->right;
        }
        else if (BSTLessThan(node,n)){
            n = n->left;
        }
    }
    return found;
}

// =====================================================
// OPTIONAL: Implement "remove" only for bonus marks
// =====================================================

// Returns true on successful deletion of the entry in BST with
// matching journey code. Returns false if it cannot find any such element.
//
// You may assume that no two elements in the BST have the same journey
// code, and journey code is the key for insertion and finding in the BST.

bool BST::remove(int jrnyCode){
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
   TreeNode* new_node=new TreeNode(jrnyCode,0);
   if (find(jrnyCode)==0) return 0;
   TreeNode* original_root=root;
   TreeNode* n = root;
   TreeNode* par = nullptr;
   bool a= 0;
   while (a == 0){
        if (!BSTLessThan(n,new_node) && !BSTLessThan(new_node,n)){
            if (n->left == nullptr && n->right == nullptr){
                if (n== root) {root = nullptr; a=1;}
                else if (n == par->left){
                     updateBSTParentChild(nullptr,par,true);
                     if(par->right!=nullptr){
                         par->height=par->right->height+1;
                     }
                     else{
                         par->height=0;
                     }
                     a=1;
                }
                else{
                     updateBSTParentChild(nullptr,par,false);
                     if(par->left!=nullptr){
                         par->height=par->left->height+1;
                     }
                     else{
                         par->height=0;
                     }
                     a=1;
                }
                if(root!=nullptr){
                    TreeNode* y=par;
                    change_height(y);
                }
            }
            else if (n->left != nullptr && n->right == nullptr){
                if (n == root) {root = n->left; a=1;}
                else if (n == par->left){
                     TreeNode* left_child=n->left;
                     updateBSTParentChild(left_child,par,true);
                     a=1;
                     if(par->right==nullptr){
                         par->height=1+left_child->height;
                     }
                     else{
                         par->height=max(par->right->height+1,left_child->height+1);
                     }
                     change_height(par);
                     a=1;
                }
                else{
                     TreeNode* left_child=n->left;
                     updateBSTParentChild(left_child,par,false);
                     a=1;
                     if(par->left==nullptr){
                         par->height=1+left_child->height;
                     }
                     else{
                         par->height=max(par->left->height+1,left_child->height+1);
                     }
                     change_height(par);
                     a=1;
                }
            }
            else if (n->left == nullptr && n->right != nullptr){
                if (n == root) {root = n->right; a=1;}
                else if (n == par->left){
                     TreeNode* right_child=n->right;
                     updateBSTParentChild(right_child,par,true);
                     if(par->right==nullptr){
                         par->height=1+right_child->height;
                     }
                     else{
                         par->height=max(par->right->height+1,right_child->height+1);
                     }
                     change_height(par);
                     a=1;
                }
                else{
                     TreeNode* right_child=n->right;
                     updateBSTParentChild(right_child,par,false);
                     a=1;
                     if(par->left==nullptr){
                         par->height=1+right_child->height;
                     }
                     else{
                         par->height=max(par->left->height+1,right_child->height+1);
                     }
                     change_height(par);
                     a=1;
                }
            }
            else{
                if(n==root){
                     root=n->right;
                     n->right->parent=nullptr;
                     TreeNode* f=get_Minimum(n->right);
                     TreeNode* m=n->left;
                     updateBSTParentChild(m,f,true);
                     a=1;
                     if(f->right==nullptr){
                         f->height=1+m->height;
                     }
                     else{
                         f->height=max(f->right->height+1,m->height+1);
                     }
                     change_height(f);
                     a=1;
                }
                else{
                     TreeNode* b=n->parent;
                     TreeNode* c=n->right;
                     TreeNode* d=n->left;
                     TreeNode* f=get_Minimum(c);
                     if(b->left==n){
                          updateBSTParentChild(c,b,true);
                          updateBSTParentChild(d,f,true);
                          a=1;
                     }
                     else{
                          updateBSTParentChild(c,b,false);
                          updateBSTParentChild(d,f,true);
                          a=1;
                     }
                     if(f->right==nullptr){
                         f->height=1+d->height;
                     }
                     else{
                         f->height=max(f->right->height+1,d->height+1);
                     }
                     change_height(f);
                }  
            }
        }
        if (BSTLessThan(n,new_node)){
            par = n;
            n = n->right;
        }
        else if (BSTLessThan(new_node,n)){
            par = n;
            n= n->left;
        }
    }
    return a;
}

TreeNode * BST::get_Minimum(TreeNode * n){
    if(n == nullptr) return nullptr;
    while (n->left != nullptr) n = n->left;
    return n;
}

// int main(){
//   BST a(1,1);
//   cout<<"hi";
//  a.insert(1,1);
//  cout<<a.find(1);
//  cout<<a.remove(1);
// }