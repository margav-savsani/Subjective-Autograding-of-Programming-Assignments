// Code up the functions defined in tree.h
// Reuse the binary Search Tree implemented in lab 3 as much as possible

#include <bits/stdc++.h>
#include <iostream>
#include <vector>
#include <string>
#include<cmath>
using namespace std;

#include "updated_tree.h"

// PLEASE FILL IN THE BODIES OF THE FOLLOWING FUNCTIONS

// Returns false, if given JourneyCode is already present in the BST
// Inserts the element and returns True otherwise

int BST::getImbalance(){
    if (root == nullptr) return 0;
    else return root->longestPathLength-root->shortestPathLength;
}
void BST::change_imbalance(TreeNode* z){
    TreeNode* y=z;
    TreeNode* x=y->parent;
    while(x!=nullptr){
        if(x->left==y){
            if(x->right==nullptr){
                x->longestPathLength=x->left->longestPathLength+1;
                x->shortestPathLength=x->left->shortestPathLength+1;
            }
            else{
                x->longestPathLength=max(x->right->longestPathLength+1,x->left->longestPathLength+1);
                x->shortestPathLength=min(x->right->shortestPathLength+1,x->left->shortestPathLength+1);
            }
         }
         else{
            if(x->left==nullptr){
                x->longestPathLength=x->right->longestPathLength+1;
                x->shortestPathLength=x->right->shortestPathLength+1;
            }
            else{
                x->longestPathLength=max(x->right->longestPathLength+1,x->left->longestPathLength+1);
                x->shortestPathLength=min(x->right->shortestPathLength+1,x->left->shortestPathLength+1);
            }
         }
         y=x;
         x=x->parent;
    }
}

bool BST::insert(int J, int p){
    if(find(J, p)==1) return 0;
    TreeNode* node = new TreeNode(J, p);
    if (root == nullptr){
        root =node;
        root->parent = nullptr;
        root->longestPathLength=1;
        root->shortestPathLength=1;
        return 1;
    }
    TreeNode* n = root;
    bool i = 0;
    while (i == 0){
        if(n->JourneyCode<=J){
            if (n->right== nullptr){
                n->right = node;
                node->parent = n;
                node->longestPathLength=1;
                node->shortestPathLength=1;
                i=1;
            }
            else n = n->right;
        }
        else{
            if (n->left == nullptr){
                n->left = node;
                node->parent = n;
                node->longestPathLength=1;
                node->shortestPathLength=1;
                i=1;
            }
            else n = n->left;
        }
    }
    change_imbalance(node);
    return i;
}
// Return True, if the ticket with given attributes is found, false otherwise

bool BST::find(int J, int p){
    TreeNode* node = new TreeNode(J, p);
    if (root == nullptr) return 0;
    TreeNode * n = root;
    bool found = 0;
    while (n!=nullptr){
        if (n->price==p && n->JourneyCode==J){
            found=1;
            return true;
        }
        if (n->price <= node->price){
            n= n->right;
        }
        else if (n->price >node->price){
            n = n->left;
        }
    }
    return found;
}
	
// Returns false, if JourneyCode isn't present
// Deletes the corresponding entry and returns True otherwise
bool BST::remove(int J, int p){
    if (find(J, p)==0) return 0;
    TreeNode* original_root=root;
    TreeNode* n = root;
    TreeNode* par = nullptr;
    bool a= 0;
    while (a == 0){
        if (n->price==p && n->JourneyCode==J){
            if (n->left == nullptr && n->right == nullptr){
                if (n== root) {root = nullptr; a=1;}
                if (n == par->left){
                     par->left = nullptr;
                     if(par->right!=nullptr){
                         par->shortestPathLength=par->right->shortestPathLength+1;
                         par->longestPathLength=par->right->longestPathLength+1;
                     }
                     else{
                         par->longestPathLength=0;
                         par->shortestPathLength=0;
                     }
                }
                else{
                     par->right = nullptr;
                     if(par->left!=nullptr){
                         par->shortestPathLength=par->left->shortestPathLength+1;
                         par->longestPathLength=par->left->longestPathLength+1;
                     }
                     else{
                         par->longestPathLength=0;
                         par->shortestPathLength=0;
                     }
                }
                TreeNode* y=par;
                change_imbalance(y);
            }
            else if (n->left != nullptr && n->right == nullptr){
                if (n == root) {root = n->left; a=1;}
                if (n == par->left){
                     TreeNode* left_child=n->left;
                     par->left = left_child;
                     left_child->parent=par;
                     a=1;
                     if(par->right==nullptr){
                         par->longestPathLength=1+left_child->longestPathLength;
                         par->shortestPathLength=1+left_child->shortestPathLength;
                     }
                     else{
                         par->longestPathLength=max(par->right->longestPathLength+1,left_child->longestPathLength+1);
                         par->shortestPathLength=min(par->right->shortestPathLength+1,left_child->shortestPathLength+1);
                     }
                     change_imbalance(par);
                }
                else{
                     TreeNode* left_child=n->left;
                     par->right = left_child;
                     left_child->parent=par;
                     a=1;
                     if(par->left==nullptr){
                         par->longestPathLength=1+left_child->longestPathLength;
                         par->shortestPathLength=1+left_child->shortestPathLength;
                     }
                     else{
                         par->longestPathLength=max(par->left->longestPathLength+1,left_child->longestPathLength+1);
                         par->shortestPathLength=min(par->left->shortestPathLength+1,left_child->shortestPathLength+1);
                     }
                     change_imbalance(par);
                }
            }
            else if (n->left == nullptr && n->right != nullptr){
                if (n == root) {root = n->right; a=1;}
                if (n == par->left){
                     TreeNode* right_child=n->right;
                     par->left =right_child;
                     right_child->parent=par;
                     a=1;
                     if(par->right==nullptr){
                         par->longestPathLength=1+right_child->longestPathLength;
                         par->shortestPathLength=1+right_child->shortestPathLength;
                     }
                     else{
                         par->longestPathLength=max(par->right->longestPathLength+1,right_child->longestPathLength+1);
                         par->shortestPathLength=min(par->right->shortestPathLength+1,right_child->shortestPathLength+1);
                     }
                     change_imbalance(par);
                }
                else{
                     TreeNode* right_child=n->right;
                     par->right = right_child;
                     right_child->parent=par;
                     a=1;
                     if(par->right==nullptr){
                         par->longestPathLength=1+right_child->longestPathLength;
                         par->shortestPathLength=1+right_child->shortestPathLength;
                     }
                     else{
                         par->longestPathLength=max(par->left->longestPathLength+1,right_child->longestPathLength+1);
                         par->shortestPathLength=min(par->left->shortestPathLength+1,right_child->shortestPathLength+1);
                     }
                     change_imbalance(par);
                }
            }
            else{
                if(n==root){
                     n->right=root;
                     TreeNode* f=get_Minimum(n->right);
                     TreeNode* m=n->left;
                     f->left=n->left;
                     m->parent=f;
                     a=1;
                     if(f->right==nullptr){
                         f->longestPathLength=1+m->longestPathLength;
                         f->shortestPathLength=1+m->shortestPathLength;
                     }
                     else{
                         f->longestPathLength=max(f->right->longestPathLength+1,m->longestPathLength+1);
                         f->shortestPathLength=min(f->right->shortestPathLength+1,m->shortestPathLength+1);
                     }
                     change_imbalance(f);
                }
                else{
                     TreeNode* b=n->parent;
                     TreeNode* c=n->right;
                     TreeNode* d=n->left;
                     TreeNode* f=get_Minimum(c);
                     if(b->left==n){
                          b->left=n->right;
                          f->left=d;
                          d->parent=f;
                          c->parent=b;
                          a=1;
                     }
                     else{
                          b->right=n->right;
                          f->left=d;
                          d->parent=f;
                          c->parent=b;
                          a=1;
                     }
                     if(f->right==nullptr){
                         f->longestPathLength=1+d->longestPathLength;
                         f->shortestPathLength=1+d->shortestPathLength;
                     }
                     else{
                         f->longestPathLength=max(f->right->longestPathLength+1,d->longestPathLength+1);
                         f->shortestPathLength=min(f->right->shortestPathLength+1,d->shortestPathLength+1);
                     }
                     change_imbalance(f);
                }  
            }
        }
        if (n->price <= p){
            par = n;
            n = n->right;
        }
        else if (n->price > p){
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

// ************************************************************
// DO NOT CHANGE ANYTHING BELOW THIS LINE

// Adapted from Adrian Schneider's code on StackOverflow
void BST::printBST(const string& prefix, bool isLeft=false)
{
    if( root != nullptr )
    {
        cout << prefix;

        cout << (isLeft ? "|--" : "|__" );

        // print the value of the node
        cout << root->JourneyCode << endl;
        TreeNode *curr = root;
        root = root->left;
        // enter the next tree level - left and right branch
        printBST( prefix + (isLeft ? "│   " : "    "), true);
        root = curr->right;
        printBST( prefix + (isLeft ? "│   " : "    "), false);
        root = curr;
    }
}

void BST::getBST(const string& prefix,  bool isLeft=false)
{
    if( root != nullptr )
    {
        result.push_back(prefix);

        result.push_back(isLeft ? "|--" : "|__" );

        // print the value of the node
        result.push_back(root->JourneyCode + "\n");
        TreeNode *curr = root;
        root = root->left;
        // enter the next tree level - left and right branch
        getBST( prefix + (isLeft ? "│   " : "    "), true);
        root = curr->right;
        getBST( prefix + (isLeft ? "│   " : "    "), false);
        root = curr;
    }
}

void BST::clearResult(){
    result.clear();
}

vector<string> BST::getResult(){
    return result;
}

