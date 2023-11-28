#ifndef AVL_H
#include "AVL.h"
#endif

#ifndef STD_HEADERS
#include <iostream>
#include <stdlib.h>
#endif

// Recall from Prof. Naveen Garg's lectures how the various rotations are
// applied to restore the balance factor at all nodes of an AVL tree
// to either 0, 1 or -1, after an insert or delete.
// The correspondence between the terminology in Prof. Garg's lectures and
// our terminology in this code is as follows:
//
// Prof. Garg's lectures           Our code
// ---------------------           --------
//   x                             currNode
//   y                             parentNode
//   z                             grandParentNode
//
// Recall also that z (grandParentNode) is the lowest node in the path from
// the root to the inserted node or to the deleted node (as the case may be)
// where the balance factor has either become < -1 or > 1.
// To find what x (currNode) and y (parentNode) should be, you need to
// recall Prof. Garg's lectures.
// These are slightly differently defined when inserting nodes and when
// deleting nodes

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
  }
  else{
      root=parentNode;
      isGPLeftChild=true;
  }
      TreeNode *T3 = parentNode->right;
      updateAVLParentChild(parentNode, greatGrandParentNode, isGPLeftChild);
      updateAVLParentChild(currNode, parentNode, true);
      updateAVLParentChild(grandParentNode, parentNode, false);
      updateAVLParentChild(T3, grandParentNode, true);
  return true;
}

bool AVLTree::rotateLeftRight(TreeNode *currNode, TreeNode *parentNode, TreeNode *grandParentNode){
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
  }
  else{
      isGPLeftChild=true;
      root=currNode;
  }
      TreeNode *T2 = currNode->left;
      TreeNode *T3 = currNode->right;
      updateAVLParentChild(currNode, greatGrandParentNode, isGPLeftChild);
      updateAVLParentChild(parentNode, currNode, true);
      updateAVLParentChild(grandParentNode, currNode, false);
      updateAVLParentChild(T2, parentNode, false);
      updateAVLParentChild(T3, grandParentNode, true);
  return true;
}

bool AVLTree::rotateRightLeft(TreeNode *currNode, TreeNode *parentNode, TreeNode *grandParentNode){
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
  }
  else{
      isGPLeftChild=true;
      root=currNode;
  }
  TreeNode *T2 = currNode->left;
  TreeNode *T3 = currNode->right;
  updateAVLParentChild(currNode, greatGrandParentNode, isGPLeftChild);
  updateAVLParentChild(parentNode, currNode,false);
  updateAVLParentChild(grandParentNode, currNode, true);
  updateAVLParentChild(T2,grandParentNode,false);
  updateAVLParentChild(T3, parentNode,true);
  return true;
}

bool AVLTree::rotateRightRight(TreeNode *currNode, TreeNode *parentNode, TreeNode *grandParentNode){
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
  }
  else{
      isGPLeftChild=true;
      root=parentNode;
  }
      TreeNode *T3 = parentNode->left;
      updateAVLParentChild(parentNode, greatGrandParentNode, isGPLeftChild);
      updateAVLParentChild(currNode, parentNode, false);
      updateAVLParentChild(grandParentNode, parentNode, true);
      updateAVLParentChild(T3, grandParentNode, false);
  return true;
}

// Returns true on successful insertion in AVL tree. Returns false otherwise.
// You may assume that no two elements being inserted have the same journey
// code, and journey code is the key for insertion and finding in the AVL
// tree.
int get_imbalance(TreeNode* n){
  int imbalance;
  if(n==nullptr) imbalance=0;
  else{
      if(n->right!=nullptr && n->left!=nullptr) imbalance=abs(n->right->height-n->left->height);
      else if(n->right==nullptr && n->left!=nullptr) imbalance=n->left->height+1;
      else if(n->left==nullptr && n->right!=nullptr) imbalance=n->right->height+1;
      else if(n->left==nullptr && n->right==nullptr) imbalance=0;
  }
  return imbalance;
}

void AVLTree::change_height(TreeNode* z){
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

void AVLTree::update_height(TreeNode* n){
    if(n->left!=nullptr && n->right!=nullptr){
         n->height=max(n->left->height+1, n->right->height+1);
    }
    else if(n->left==nullptr && n->right!=nullptr){
         n->height=n->right->height+1;
    }
    else if(n->left!=nullptr && n->right==nullptr){
         n->height=n->left->height+1;
    }
    else if(n->left==nullptr && n->right==nullptr){
         n->height=0;
    }
}
bool AVLTree::insert(int jrnyCode, int price){
  // Implement insertion in AVL tree followed by balance factor restoration
  // by properly identifying x, y, z as used in Prof. Garg's lectures
  // (equivalently, currNode, parentNode, grandParentNode in our code) and
  // invoking rotateLeftLeft, rotateLeftRight, rotateRightLeft and/or
  // rotateRightRight as appropriate.

  // It is your responsibility to find out the right x, y, z (or currNode,
  // parentNode, grandParentNode) following Prof. Garg's lectures
  //
  // Once you identify these correctly, simply invoking the appropriate
  // rotation should do the job.
  // You don't even need to invoke rotation twice for the double
  // rotations -- the way rotationLeftRight is implemented, and
  // rotationRightLeft should be implemented, you should be able to achieve
  // the effect of the double rotation using one invokation of the
  // appropriate member function.

  // You MUST use only AVLLessThan to compare two journey codes.  You
  // can create a new node containing the journey code to be inserted
  // and invoke AVLLessThan on the current node in the tree that you
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
        if(AVLLessThan(n,node)){
            if (n->right== nullptr){
                updateAVLParentChild(node,n,false);
                node->height=0;
                node->left=nullptr;
                node->right=nullptr;
                i=1;
            }
            else n = n->right;
        }
        else{
            if (n->left == nullptr){
                updateAVLParentChild(node,n,true);
                node->height=0;
                node->left=nullptr;
                node->right=nullptr;
                i=1;
            }
            else n = n->left;
        }
    }
    change_height(node);
    TreeNode* z=node->parent->parent;
    TreeNode* child=node->parent;
    TreeNode* grand_child=node;
    int iterations=0;
    while(z!=nullptr){
        if(get_imbalance(z)>1){
            if(z->left==child && child->left==grand_child){
                rotateLeftLeft(grand_child,child,z);
                update_height(grand_child);
                update_height(z);
                update_height(child);
            }
            else if(z->right==child && child->left==grand_child){
                rotateRightLeft(grand_child,child,z);
                update_height(z);
                update_height(child);
                update_height(grand_child);
            }
            else if(z->left==child && child->right==grand_child){
                rotateLeftRight(grand_child,child,z);
                update_height(z);
                update_height(child);
                update_height(grand_child);
            }
            else if(z->right==child && child->right==grand_child){
                rotateRightRight(grand_child,child,z);
                update_height(grand_child);
                update_height(z);
                update_height(child);
            }
            break;
        }
        grand_child=grand_child->parent; 
        child=z;
        z=z->parent;
        iterations=iterations+1;
    }
    return i; 
}

// Returns the price on finding an element in the AVL tree that matches
// journey code. Returns -1 otherwise.
// You may assume that no two node in the tree have the same journey
// code, and journey code is the key for insertion and finding in the AVL
// tree.

int AVLTree::find(int jrnyCode){
  // Implement find in AVL tree.
  // This is really no different from finding in a binary search tree.
  // This operation cannot cause any balance factor disturbances.

  // You MUST use only AVLLessThan to compare two journey codes.  You
  // can create a new node containing the journey code to be searched
  // (along with some arbitrary price) and invoke AVLLessThan on the
  // current node in the tree that you are inspecting and the new node
  // to do your comparison.

  // We use "return -1" below to enable compilation.  Change this as you
  // see fit.
  TreeNode* node = new TreeNode(jrnyCode,0);
    if (root == nullptr) return 0;
    TreeNode * n = root;
    bool found = 0;
    while (n!=nullptr){
        if (!AVLLessThan(node,n) && !AVLLessThan(n,node)){
            found=1;
            return true;
        }
        if (AVLLessThan(n,node)){
            n= n->right;
        }
        else if (AVLLessThan(node,n)){
            n = n->left;
        }
    }
    return found;
}

// =====================================================
// OPTIONAL: Implement "remove" only for bonus marks
// =====================================================

// Returns true on successful deletion of the entry in AVL tree with
// matching journey code. Returns false if it cannot find any such element.
//
// You may assume that no two elements in the AVL tree have the same journey
// code, and journey code is the key for insertion and finding in the AVL
// tree.

void AVLTree::rebalance(TreeNode* p){
    while(p!=nullptr){
        TreeNode* q=p->parent;
        if(get_imbalance(p)>1){
             TreeNode* child;
             int right_1,right_2;
             TreeNode* grand_child;
             if(p->left!=nullptr && p->right!=nullptr){
                if(p->left->height>p->right->height){child=p->left;right_1=0;}
                else{child=p->right;right_1=1;}
             }
             else if(p->left==nullptr && p->right!=nullptr){child=p->right; right_1=1;}
             else if(p->left!=nullptr && p->right==nullptr){child=p->left; right_1=0;}
             if(child->left!=nullptr && child->right!=nullptr){
                if(child->left->height>child->right->height){grand_child=child->left;right_2=0;}
                else{grand_child=child->right;right_2=1;}
             }
             else if(child->left==nullptr && child->right!=nullptr){grand_child=child->right; right_2=1;}
             else if(child->left!=nullptr && child->right==nullptr){grand_child=child->left; right_2=0;}
             if(right_1==0 && right_2==0){
                   rotateLeftLeft(grand_child,child,p);
                   update_height(grand_child);
                   update_height(p);
                   update_height(child);
                   change_height(child);
             }
             else if(right_1==1 && right_2==0){
                   rotateRightLeft(grand_child,child,p);
                   update_height(p);
                   update_height(child);
                   update_height(grand_child);
                   change_height(grand_child);
             }
             else if(right_1==0 && right_2==1){
                   rotateLeftRight(grand_child,child,p);
                   update_height(p);
                   update_height(child);
                   update_height(grand_child);
                   change_height(grand_child);
             }
             else if(right_1==1 && right_2==1){
                   rotateRightRight(grand_child,child,p);
                   update_height(grand_child);
                   update_height(p);
                   update_height(child);
                   change_height(child);
             }
        }
        p=q;
    } 
}
bool AVLTree::remove(int jrnyCode)
{
  // Implement deletion in AVL tree followed by balance factor restoration
  // by properly identifying x, y, z as used in Prof. Garg's lectures
  // (equivalently, currNode, parentNode, grandParentNode in our code) and
  // invoking rotateLeftLeft, rotateLeftRight, rotateRightLeft and/or
  // rotateRightRight as appropriate.

  // It is your responsibility to find out the right x, y, z (or currNode,
  // parentNode, grandParentNode) following Prof. Garg's lectures
  //
  // Once you identify these correctly, simply invoking the appropriate
  // rotation(s) should do the job.
  // You don't even need to invoke rotation twice for the double
  // rotations -- the way rotationLeftRight is implemented, and
  // rotationRightLeft should be implemented, you should be able to achieve
  // the effect of the double rotation using one invokation of the
  // appropriate member function.

  // You MUST use only AVLLessThan to compare two journey codes.  You
  // can create a new node containing the journey code to be searched
  // (along with some arbitrary price) and invoke AVLLessThan on the
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
        if (!AVLLessThan(n,new_node) && !AVLLessThan(new_node,n)){
            if(n->left == nullptr && n->right == nullptr){
                if (n== root) {root = nullptr; a=1;}
                else if (n == par->left){
                     par->left=nullptr;
                     if(par->right!=nullptr){
                         par->height=par->right->height+1;
                     }
                     else{
                         par->height=0;
                     }
                     a=1;
                }
                else{
                     par->right=nullptr;
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
                     TreeNode* p=par;
                     rebalance(p);
                }
            }
            else if (n->left != nullptr && n->right == nullptr){
                if (n == root) {root = n->left; a=1;}
                else if (n == par->left){
                     TreeNode* left_child=n->left;
                     updateAVLParentChild(left_child,par,true);
                     if(par->right==nullptr){
                         par->height=1+left_child->height;
                     }
                     else{
                         par->height=max(par->right->height+1,left_child->height+1);
                     }
                     change_height(par);
                     rebalance(par);
                     a=1;
                }
                else{
                     TreeNode* left_child=n->left;
                     updateAVLParentChild(left_child,par,false);
                     if(par->left==nullptr){
                         par->height=1+left_child->height;
                     }
                     else{
                         par->height=max(par->left->height+1,left_child->height+1);
                     }
                     change_height(par);
                     rebalance(par);
                     a=1;
                }
            }
            else if (n->left == nullptr && n->right != nullptr){
                if (n == root) {root = n->right; a=1;}
                else if (n == par->left){
                     TreeNode* right_child=n->right;
                     updateAVLParentChild(right_child,par,true);
                     if(par->right==nullptr){
                         par->height=1+right_child->height;
                     }
                     else{
                         par->height=max(par->right->height+1,right_child->height+1);
                     }
                     change_height(par);
                     rebalance(par);
                     a=1;
                }
                else{
                     TreeNode* right_child=n->right;
                     updateAVLParentChild(right_child,par,false);
                     cout<<par->left->height<<right_child->height;
                     if(par->left==nullptr){
                         par->height=1+right_child->height;
                     }
                     else{
                         par->height=max(par->left->height+1,right_child->height+1);
                     }
                     change_height(par);
                     rebalance(par);
                     a=1;
                }
            }
            else{
                if(n==root){
                     root=n->right;
                     n->right->parent=nullptr;
                     TreeNode* f=get_Minimum(n->right);
                     TreeNode* m=n->left;
                     updateAVLParentChild(m,f,true);
                     if(f->right==nullptr){
                         f->height=1+m->height;
                     }
                     else{
                         f->height=max(f->right->height+1,m->height+1);
                     }
                     change_height(f);  
                     rebalance(f);
                     a=1;
                }
                else{
                     TreeNode* b=n->parent;
                     TreeNode* c=n->right;
                     TreeNode* d=n->left;
                     TreeNode* f=get_Minimum(c);
                     if(b->left==n){
                          updateAVLParentChild(c,b,true);
                          updateAVLParentChild(d,f,true);
                          a=1;
                     }
                     else{
                          updateAVLParentChild(c,b,false);
                          updateAVLParentChild(d,f,true);
                          a=1;
                     }
                     if(f->right==nullptr){
                         f->height=1+d->height;
                     }
                     else{
                         f->height=max(f->right->height+1,d->height+1);
                     }
                     change_height(f);
                     rebalance(f);
                }  
            }
        }
        if (AVLLessThan(n,new_node)){
            par = n;
            n = n->right;
        }
        else if (AVLLessThan(new_node,n)){
            par = n;
            n= n->left;
        }
    }
    return a;
}

TreeNode* AVLTree::get_Minimum(TreeNode * n){
    if(n == nullptr) return nullptr;
    while (n->left != nullptr) n = n->left;
    return n;
}

// int main(){
//  AVLTree a(1,1);
//  a.insert(10,1);
//  a.insert(11,1);
//  cout<<a.remove(10);
// }