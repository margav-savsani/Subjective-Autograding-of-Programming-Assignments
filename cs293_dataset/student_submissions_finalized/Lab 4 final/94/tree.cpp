// Code up the functions defined in tree.h
// Reuse the binary Search Tree implemented in lab 3 as much as possible

#include <bits/stdc++.h>
#include <iostream>
#include <vector>
#include <string>
#include<cmath>
using namespace std;

#include "tree.h"

// PLEASE FILL IN THE BODIES OF THE FOLLOWING FUNCTIONS

// Returns false, if given JourneyCode is already present in the BST
// Inserts the element and returns True otherwise
TreeNode*f;
TreeNode*m;
void BST::reassign(){
    int a=shor(root);
    int b=lon(root);
    return;
}
int BST::getImbalance()
{  reassign();
  if (root == nullptr) return 0;
  else return root->getImbalance();
}

bool BST::insert(int JourneyCode, int price)
{
  // The following filler code snippet is only given to facilitate
  // compilation.  You should replace/augment it with appropriate code,
  // similar to what you had done in lab assignment 3.
  
  if(find(JourneyCode,price)) {  return false;}
    else{
        if(root==NULL){
            root=new TreeNode(JourneyCode,price);
            root->parent=NULL;
        }
        else{
            insert_help(JourneyCode,price,root);
        }
        return true;
    }
    // JourneyCode is not present in the BST.  We must now
    // insert an appropriate child of parentOfCurrNode.
    // Please implement this part yourself.
    //
    // Do not forget to update shortestPathLength and
    // longestPathLength of (possibly all) BST nodes in the
    // path from the root to the new node you are inserting
}
void BST::insert_help(int jc, int pr,TreeNode*r1){
    if(pr<=r1->price){
        if(r1->left==NULL){
            r1->left=new TreeNode(jc,pr);
            r1->left->parent=r1;
        }
        else insert_help(jc,pr,r1->left);
    }
    else{
        if(r1->right==NULL){
            r1->right=new TreeNode(jc,pr);
            r1->right->parent=r1;
        }
        else insert_help(jc,pr,r1->right);

    }
} 


// Return True, if the ticket with given attributes is found, false otherwise
bool BST::find(int JourneyCode, int price)
{
  // The following filler code snippet is only given to facilitate
  // compilation.  You should replace it with appropriate code, very
  // similar to what you had done in lab assignment 3.
  //
  // You can look at the implementation of insert to code this part up.
    TreeNode* r=root;
    return find_help(JourneyCode,price,r);
  
}
bool BST::find_help(int jc,int pr,TreeNode*r1){
    TreeNode*r=r1;
    if(r==NULL) return false;
    if(r->JourneyCode==jc){ 
        f=r;
        return true;
    }

    if(r->JourneyCode!=jc && r->left==NULL && r->right==NULL)
        {return false;}
    else{
        if(pr<=r->price){
            return find_help(jc,pr,r->left);
            return find_help(jc,pr,r->right);
            

        }
        else {
            return find_help(jc,pr,r->right);
        }
    }

}

	
// Returns false, if JourneyCode isn't present
// Deletes the corresponding entry and returns True otherwise
bool BST::remove(int JourneyCode, int price)
{
  // The following filler code snippet is only given to facilitate
  // compilation.  You should replace it with appropriate code, very
  // similar to what you had done in lab assignment 3.
  //
  // Recall from CS 213 lectures about the various ways in which the
  // BST can be restructured when a node is deleted. You can implement
  // any of these alternatives.
  //
  // Do not forget to update shortestPathLength and
  // longestPathLength of (possibly all) BST nodes in the
  // path from the root to nodes whose position in the BST is affected
  // by the remove.
    
  if(!find(JourneyCode,price)) return false;
    else{
        if(f==root){
            if(m==NULL){
                root=NULL;
                return true;
            }
            if(m->right==NULL){
                cout<<"reached"<<endl;
                TreeNode*mp=m->parent;
                root->JourneyCode=m->JourneyCode;
                root->price=m->price;
                mp->left=NULL;
            }
            else{
                TreeNode*mp=m->parent;
                TreeNode*mr=m->right;
                root->JourneyCode=m->JourneyCode;
                root->price=m->price;
                mp->left=mr;
                mr->parent=mp;
            }
            return true;
        }
        TreeNode*p=f->parent;

        bool right;
        if(p->price<f->price) right=true;
        else right=false;

        if(f->left==NULL && f->right==NULL){
            if(right){
                p->right=NULL;
            }
            else p->left=NULL;
        }
        if(f->left!=NULL && f->right==NULL){
            TreeNode*l=f->left;
            if(right){
                p->right=l;
                l->parent=p;
            }
            else{
                p->left=l;
                l->parent=p;
            }
        }
        if(f->left==NULL && f->right!=NULL){
            TreeNode*l=f->right;
            if(right){
                p->right=l;
                l->parent=p;
            }
            else{
                p->left=l;
                l->parent=p;
            }
            
        }
        if(f->left!=NULL && f->right!=NULL){
            mintree(f->right);
            if(m->right==NULL){
                TreeNode*mp=m->parent;
                if(right){
                    p->right=m;
                    m->parent=p;
                    m->right=f->right;
                    m->left=f->left;
                    mp->left=NULL;
                }
                else{
                    p->left=m;
                    m->parent=p;
                    m->left=f->left;
                    m->right=f->right;
                    mp->left=NULL;
                }
            }
            else{
                TreeNode*mr=m->right;
                TreeNode*mp=m->parent;
                if(right){
                    p->right=m;
                    m->parent=p;
                    m->left=f->left;
                    m->right=f->right;
                    mp->left=mr;

                }
                else{
                    p->left=m;
                    m->parent=p;
                    m->left=f->left;
                    m->right=f->right;
                    mp->left=mr;

                }


            }
        }
    return true;
    }
}
void BST::mintree(TreeNode*r1){
    TreeNode*r=r1;
    if(r!=NULL){
        while(true){
            if(r->left==NULL){
                m=r;
                break;
            }
                r=r->left;
        }
    }
    else{
        m=NULL;
    }

}
int BST::shor(TreeNode*r){
    if(r==NULL){ 
        return 0;}
    if(r!=NULL){
        if(r->left==NULL && r->right==NULL){ 
            r->shortestPathLength=0;
            return 0;}
        if(r->left!=NULL && r->right==NULL){
            r->shortestPathLength=shor(r->left)+1;
            return r->shortestPathLength;
        }
        if(r->left==NULL && r->right!=NULL){
            r->shortestPathLength=shor(r->right)+1;
            return r->shortestPathLength;
        }
        if(r->left!=NULL && r->right!=NULL){
            int a=shor(r->left);
            int b=shor(r->right);
            r->shortestPathLength=min(a,b)+1;
            return r->shortestPathLength;
        }
    }
    return 0;

}
int BST::lon(TreeNode*r){
    if(r==NULL) return 0;
    if(r!=NULL){
        if(r->left==NULL && r->right==NULL){
         r->longestPathLength=0;
         return 0;
         }
        if(r->left!=NULL && r->right==NULL){
           int a=lon(r->left);
           r->longestPathLength=a+1;
           return  r->longestPathLength;
        }
        if(r->left==NULL && r->right!=NULL){
           int a=lon(r->right);
           r->longestPathLength=a+1;
           return  r->longestPathLength;
        }
        if(r->left!=NULL && r->right!=NULL){
            int a=lon(r->left);
            int b=lon(r->right);
            r->longestPathLength=max(a,b)+1;
            return r->longestPathLength;
        }
    }
    return 0;

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

