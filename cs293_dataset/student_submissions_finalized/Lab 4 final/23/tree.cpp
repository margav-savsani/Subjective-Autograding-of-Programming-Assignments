// Code up the functions defined in tree.h
// Reuse the binary Search Tree implemented in lab 3 as much as possible

#include <bits/stdc++.h>
#include <iostream>
#include <vector>
#include <string>

using namespace std;

#include "tree.h"

// PLEASE FILL IN THE BODIES OF THE FOLLOWING FUNCTIONS

// Returns false, if given JourneyCode is already present in the BST
// Inserts the element and returns True otherwise

int BST::getImbalance()
{ longest(root);
  shortest(root);
  if (root == nullptr) return 0;
  else return root->getImbalance();
}

bool BST::insert(int JourneyCode, int price)
{         if (find(JourneyCode,price))return false;
           TreeNode *y=NULL;
           TreeNode *x=root;
           TreeNode *z;
           z=new TreeNode();
           z->JourneyCode=JourneyCode;
           z->price=price;
           while(x!=NULL){
               y=x;
               if(JourneyCode<x->JourneyCode) x=x->left;
               else x=x->right;}
           z->parent=y;
           z->left=NULL;
           z->right=NULL;
           if(y==NULL) root=z;
           else if (z->JourneyCode<y->JourneyCode) y->left=z;
           else y->right=z;
           assign(root);
           return true;
           }
  // JourneyCode is not present in the BST.  We must now
  // insert an appropriate child of parentOfCurrNode.
  // Please implement this part yourself.
  //
  // Do not forget to update shortestPathLength and
  // longestPathLength of (possibly all) BST nodes in the
  // path from the root to the new node you are inserting
  



bool BST::find(int JourneyCode, int price)
{         TreeNode *x;
          x=root;
          if(search(x,JourneyCode,price)==NULL) return false;
          else return true;
}


TreeNode* BST::search(TreeNode *d,int JourneyCode,int price){
          TreeNode *x=d;
          if (x==NULL) return NULL;
          if(x->price==price&&x->JourneyCode==JourneyCode){
                      return x;}
          if(x->JourneyCode>JourneyCode) return search(x->left,JourneyCode,price);
          else return search(x->right,JourneyCode,price);
          }
	
TreeNode* BST::getsuc(TreeNode *f) {
                        TreeNode *x=f;
                        TreeNode *y;
                        if(x->right !=NULL){
                            while(x->left !=NULL){
                                  x=x->left;}
                                  return x;}
                        y=x->parent;
                        while (y != NULL && x == y->right){
                          x=y;
                          y=y->parent;}
                        return y;
                                  }


bool BST::remove(int JourneyCode, int price)
{          TreeNode *x;
           TreeNode *y;
           TreeNode *z=search(root,JourneyCode,price);
           if(find(JourneyCode,price)){
           if(z->left == NULL || z->right == NULL)
                 y=z;
           else y=getsuc(z);
           if (y->left != NULL)
              x = y->left;
           else x = y->right;
           if (x != NULL)
              x->parent=y->parent;
           if (y->parent==NULL)
              root = x;
              else if ( y == y->parent->left )
                    y->parent->left = x;
                    else  y->parent->right = x; 
           if (y !=z)
              z->price = y->price;
              z->JourneyCode=y->JourneyCode;
              assign(root);
              return true;}
           else return false;
  
  // Do not forget to update shortestPathLength and
  // longestPathLength of (possibly all) BST nodes in the
  // path from the root to nodes whose position in the BST is affected
  // by the remove.
}
int BST::longest(TreeNode *d){
           if (d==NULL) return 0;
           if(d->right==NULL && d->left==NULL) return 1;
           else 
           return 1+max(longest(d->right),longest(d->left));
           }
           
int BST::shortest(TreeNode *e){
           if(e==NULL) return 0;
           else if((e->right=NULL)&&(e->left==NULL))
                   return 1;
           else if(e->right==NULL && e->left!=NULL) 
                   return 1+shortest(e->left);
           else if(e->right!=NULL&&e->left==NULL)
                   return 1+shortest(e->right);
           else 
                   return 1+min(shortest(e->right),shortest(e->left));
           }
           
void BST::assign(TreeNode *g){
     g->longestPathLength=longest(g);
     g->shortestPathLength=shortest(g);
     assign(g->right);
     assign(g->left);
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
        result.push_back(to_string(root->JourneyCode) + "\n");
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

