#include <bits/stdc++.h>
#include <iostream>
#include <vector>
#include <string>

using namespace std;

#include "BST.h"

#define PRE_ORDER 0
#define POST_ORDER 1
#define IN_ORDER 2
#define LOAD_FULL_BST 3
#define LOAD_LEFT_SUBTREE 4


// PLEASE FILL IN THE BODIES OF THE FOLLOWING FUNCTIONS
BST::BST(){
  root=nullptr;
   }
BST::BST(TreeNode *root1){
       root=root1; 
       }
// Returns false, if given JourneyCode is already present in the BST
// Inserts the element and returns True otherwise
bool BST::insert(int JourneyCode, int price) {
   if(find(JourneyCode,price)){return 0;}
   else{
        TreeNode *y;y=NULL;
        TreeNode *x;x=root;
        TreeNode *n;n=new TreeNode(JourneyCode,price);
        while(x!=NULL){
         y=x;
         if(price<x->price){x=x->left;}
         else{x=x->right;}
        }
         n->parent=y;
         if(y==NULL){root=n;return 1;}
         else if(price<y->price){
            y->left=n;return 1;}
            else{y->right=n;return 1;}  }        }
// Return True, if the ticket with given attributes is found, false otherwise
bool BST::find(int JourneyCode, int price) {
     TreeNode *node;
    node=root;
    if(root==NULL){
        return 0;
    }
    if(node->price==price&&node->JourneyCode==JourneyCode){//if it is matched with given data then it returns true
        return 1;
    }
    if(price<node->price){BST left(node->left);//using recursive functions to find in left or right subbranch
       return left.find(JourneyCode,price);
    }
    else{BST right(node->right);//right subbranch
        return right.find(JourneyCode,price);
    }
 }
// Returns false, if JourneyCode isn't present
// Deletes the corresponding entry and returns True otherwise
bool BST::remove(int JourneyCode, int price){ 
          TreeNode* f=NULL;
          TreeNode* k;
          if(!(find(JourneyCode,price))){//if it is not present in the BST
              return false;
              }
          else{
             if(root->price==price){
                   f=root;
                   }
             else{TreeNode* y;
                if(root->price>price){y=root->left;/*finding it's position in the BST*/} 
                 else{y=root->right;}
                  if(y->price==price){
                     f=y;
                     }
                  while(y->price!=price){
                   if(y->price>price){
                      y=y->left;
                      }
                   else{
                      y=y->right;
                      }
                   }
                 if(f==NULL){
                    f=y;
                    }
                 }
             }
             if(f->right==NULL && f->left==NULL){//no children for x
                 if(f==root){//if x is root
                  root=NULL;
                  return 1;
                  }
                 else{
                    if(f->parent->right==f){
                        f->parent->right=NULL;
                        f=NULL;
                        return 1;
                        }
                    else{
                        f->parent->left=NULL;
                        f=NULL;
                        return 1;
                        }
                     }
                  }
             else if(f->right==NULL || f->left==NULL){//if x hs 1 child
                  if(f->right!=NULL){//x has right child
                      if(f==root){//if x is root
                          root=f->right;//attaching child of x to x's parent
                          f->right->parent=NULL;
                          f=NULL;//deleting x
                          return 1;
                          }
                      else{
                         if(f->parent->right==f){//if x is right of parent
                           f->parent->right=f->right;//attaching child of x to x's parent
                           f->right->parent=f->parent;
                            f=NULL;//deleting x
                            return 1;
                            }
                         else{
                            f->parent->left=f->right;//if x is left of it's parent
                            f->right->parent=f->parent;//attaching child of x to x's parent
                            f=NULL;//deleting x
                            return 1;
                            }
                          }
                       }
                    else{
                       if(f==root){//if x is root and x has 2 children
                          root=f->left;//making left element root
                          f->left->parent=NULL;
                          f=NULL;
                          return 1;
                          }
                       else{
                          if(f->parent->right==f){
                            f->parent->right=f->left;
                            f->left->parent=f->parent;
                            f=NULL;
                            return 1;
                            }
                          else{
                            f->parent->left=f->left;
                            f->left->parent=f->parent;
                            f=NULL;
                            return 1;
                            }
                          }
                      }
                    }
                  else{
                     TreeNode* s=f->left;//finding successor
                     while(s->right!=NULL){
                       s=s->right;
                       }
                      k=s;
                     if(k->parent->right==k){
                      if(k->left!=NULL){
                         k->parent->right=k->left;
                         k->left->parent=k->parent;
                         if(f!=root){
                            if(f->parent->left==f){//changing successor to root and modifying the place of successor
                                f->parent->left=k;
                                f->left->parent=k;
                                f->right->parent=k;
                                k->right=f->right;
                                k->left=f->left;
                                return 1;
                                }
                            else{
                                f->parent->right=k;//changing successor to root and modifying the place of successor
                                f->left->parent=k;
                                f->right->parent=k;
                                k->right=f->right;
                                k->left=f->left;
                                return 1;
                                }
                             }
                          if(f==root){
                             root->JourneyCode=k->JourneyCode;
                             root->price=k->price;
                             return 1;
                             }
                           }
                        if(k->left==NULL){
                           k->parent->right=NULL;
                           if(f!=root){
                              if(f->parent->left==f){//changing successor to root and modifying the place of successor
                                f->parent->left=k;
                                f->left->parent=k;
                                f->right->parent=k;
                                k->right=f->right;
                                k->left=f->left;
                                return 1;
                                }
                            else{
                                f->parent->right=k;//changing successor to root and modifying the place of successor
                                f->left->parent=k;
                                f->right->parent=k;
                                k->right=f->right;
                                k->left=f->left;
                                return 1;
                                }
                            }
                            if(f==root){//if x is root
                             root->JourneyCode=k->JourneyCode;
                             root->price=k->price;
                             return true;
                             }
	                  }
	                 }
	                if(k->parent->left==k){
	                    if(f!=root){
	                       if(f->parent->left==f){
	                          f->parent->left=k;
	                          k->left=NULL;
	                          f->right->parent=k;
	                          k->right=f->right;
	                          k->parent=f->parent;
	                          return true;
	                          }
	                       else{
	                          f->parent->right=k;
	                          k->left=NULL;
	                          f->right->parent=k;
	                          k->right=f->right;
	                          k->parent=f->parent;
	                          return true;
	                         }
	                       }
	                    if(f==root){
	                        root->left=NULL;
	                        root->JourneyCode=k->JourneyCode;
	                        root->price=k->price;
	                        return true;
	                        }
	                }
	             }
	           }
// Functions that traverse the BST in various ways!
// type is one of PRE_ORDER, POST_ORDER or IN_ORDER
// Print on cout the journey codes at nodes of the BST in the same order as
// they are encountered in the traversal order
// Print one journey code per line
void BST::traverse(int typeOfTraversal) {
        BST le(root->left);BST ri(root->right);
        if(typeOfTraversal==2){//inoreder  by using recursive functions
        if(le.root!=NULL && ri.root!=NULL){le.traverse(2);cout<<" "<<root->JourneyCode<<" ";ri.traverse(2);}//both subtrees are not empty
        else if(le.root==NULL && ri.root!=NULL){cout<<" "<<root->JourneyCode<<" ";ri.traverse(2);}//left subtree is empty
        else if(le.root!=NULL && ri.root==NULL){le.traverse(2);cout<<" "<<root->JourneyCode<<" ";}//right subtree is empty
        else{cout<<" "<<root->JourneyCode<<" ";}}

        else if(typeOfTraversal==1){//preorder  by using recursive functions
        if(le.root!=NULL && ri.root!=NULL){le.traverse(1);ri.traverse(1);cout<<" "<<root->JourneyCode<<" ";}//both subtrees are not empty
        else if(le.root==NULL && ri.root!=NULL){ri.traverse(1);cout<<" "<<root->JourneyCode<<" ";}//left subtree is empty
        else if(le.root!=NULL && ri.root==NULL){le.traverse(1);cout<<" "<<root->JourneyCode<<" ";}//right subtree is empty
        else{cout<<" "<<root->JourneyCode<<" ";}}
        
        else if(typeOfTraversal==0){//postorder  by using recursive functions
        if(le.root!=NULL && ri.root!=NULL){cout<<" "<<root->JourneyCode<<" ";le.traverse(2);ri.traverse(2);}//both subtrees are not empty
        else if(le.root==NULL && ri.root!=NULL){cout<<" "<<root->JourneyCode<<" ";ri.traverse(2);}//left subtree is empty
        else if(le.root!=NULL && ri.root==NULL){cout<<" "<<root->JourneyCode<<" ";le.traverse(2);}//right subtree is empty
        else{cout<<" "<<root->JourneyCode<<" ";}}
}
// Returns the price of the cheapest journey
int BST::getMinimum() {
    TreeNode *x;x=root;//finding left most element
    while(x->left!=NULL){x=x->left;}
    return x->price;
     }

// Part II

// Returns the count of journeys that are at least as expensive
// as lowerPriceBound and at most as expensive as upperPriceBound,
// both bounds included.
int BST::countJourneysInPriceBound(int lowerPriceBound, int upperPriceBound) {
   BST le(root->left);BST ri(root->right);
   if(root==NULL){return 0;}
   if(root->price>=lowerPriceBound && root->price<=upperPriceBound){
      return 1+le.countJourneysInPriceBound(lowerPriceBound,upperPriceBound)+ri.countJourneysInPriceBound(lowerPriceBound,upperPriceBound);}
   else{return le.countJourneysInPriceBound(lowerPriceBound,upperPriceBound)+ri.countJourneysInPriceBound(lowerPriceBound,upperPriceBound);}
}

// Store the current tree in a file called filename.  You should
// store using a scheme that uses no more disk space than that
// required to store all elements in the BST, plus perhaps a small
// constant times the number of elements.  You should also store
// in a manner such that your implementation of customLoad is as
// memory and time efficient as possible.
void BST::customStore(string filename) { return; }
	
// While loading a tree from a file written by customStore, we
// can have one of two modes of loading.  We could either ask
// for the entire tree to be loaded or only the left subtree of
// the root (if it exists) to be loaded.  The loadMode flag
// takes one of two values LOAD_FULL_BST or LOAD_LEFT_SUBTREE,
// that are #defined in BST.cpp.
// If loadMode is LOAD_FULL_BST, customLoad should load the
// entire BST that was stored in filename using customStore.
// If loadMode is LOAD_LEFT_SUBTREE, customLoad should load
// only the left subtree of the root of the BST that was
// stored in filename using customStore.
// Your implementation of customLoad should be efficient --
// its time and space complexity should be linear in the size
// of the tree that is being loaded.  So, for example, if the
// left sub-tree of the root is small compared to the right
// sub-tree, customLoad's time and space complexity should
// be small even though the entire BST may be very large.
 
void BST::customLoad (int flag, string filename) { return; }


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
