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
   root=new TreeNode;
   root->price=0;
}

// Returns false, if given JourneyCode is already present in the BST
// Inserts the element and returns True otherwise
bool BST::insert(int JourneyCode, int price){ 
   if(find(JourneyCode,price)==0){
      TreeNode y;
      TreeNode u;
      if(root->price!=0){
          u=*root;
          while(root!=NULL){
             y=*root;
             if(root->price>price){
                root=root->left;
             }
             else{root=root->right;}         
          }
          TreeNode* z=new TreeNode;
          z->parent=&y;
          z->price=price;
          z->left=NULL;
          z->right=NULL;
          z->JourneyCode=JourneyCode;
          if(y.price>price){
             y.left=z;
          }
          else{y.right=z;}
             root=&u;
          return true;
      }
      else if(root->price==0){
          root=new TreeNode;
          root->parent=NULL;
          root->left=NULL;
          root->right=NULL;
          root->price=price;
          root->JourneyCode=JourneyCode;
          return true;
      }
  }
  else{return false;}
}

// Return True, if the ticket with given attributes is found, false otherwise
bool BST::find(int JourneyCode, int price){ 
  int found=0;
  if(root->price!=0){
      TreeNode x=*root;
      while(root!=NULL){
         if(root->price==price && root->JourneyCode==JourneyCode){
            found=1;
            return true;
         } 
         else if(root->price>price){
            root=root->left;
         }
         else if(root->price<=price){
            root=root->right;
         }
      }
      root=&x;
  }
  if(found==0)return false;
}

TreeNode* BST::get_pointer_to_node(int JourneyCode,int price){
  if(find(JourneyCode,price)==0){
      return NULL;
  }
  else{
      TreeNode a=*root;
      TreeNode b;
      while(root!=NULL){
         if(root->price==price && root->JourneyCode==JourneyCode){
            TreeNode b=*root;
            root=&a;
            return &b;
         }  
         else if(root->price>price){
            root=root->left;
         }
         else if(root->price<=price){
            root=root->right;
         }
      }
  }
}
// Returns false, if JourneyCode isn't present
// Deletes the corresponding entry and returns True otherwise
bool BST::remove(int JourneyCode, int price){ 
   if(find(JourneyCode,price)==0){
      return false;   
   }
   else{
      TreeNode* a=get_pointer_to_node(JourneyCode,price);
       if(a->left==NULL && a->right==NULL){
         a=NULL;
      }
      else if(a->left!=NULL && a->right==NULL){
         TreeNode* b=a->parent;
         TreeNode* c=a->left;
         if(b->left==a){b->left=c;}
         else b->right=c;
         c->parent=b;
         a=NULL;
      }
      else if(a->left!=NULL && a->right==NULL){
         TreeNode* b=a->parent;
         TreeNode* c=a->right;
         if(b->left==a){b->left=c;}
         else b->right=c;
         c->parent=b;
         a=NULL;
      }
      else if(a->left!=NULL && a->right!=NULL){
         TreeNode* b=a->parent;
         TreeNode* c=a->right;
         TreeNode* d=a->left;
         if(b->right==a){
            b->right=c;
         }
         else{
            b->left=c;
         }
         c->left=d;
         c->parent=b;
         d->parent=c;
         a=NULL;
      }
      return true;
   }
}

void BST::Pre_order(TreeNode* n){
   if(n==NULL) return;
   else{
      cout<<n->JourneyCode<<endl;
      TreeNode* a;
      TreeNode* b;
      a=n->left;
      b=n->right;
      Pre_order(a);
      Pre_order(b);
   }
}

void BST::Post_order(TreeNode* n){
   if(n==NULL) return;
   else{
      TreeNode* a;
      TreeNode* b;
      a=n->left;
      b=n->right;
      Pre_order(a);
      Pre_order(b);
      cout<<n->JourneyCode<<endl;
   }
}	

void BST::In_order(TreeNode* n){
   if(n==NULL) return;
   else{
      TreeNode* a;
      TreeNode* b;
      a=n->left;
      b=n->right;
      Pre_order(a);
      cout<<n->JourneyCode<<endl;
      Pre_order(b);
   }
}	
	
// Functions that traverse the BST in various ways!
// type is one of PRE_ORDER, POST_ORDER or IN_ORDER
// Print on cout the journey codes at nodes of the BST in the same order as
// they are encountered in the traversal order
// Print one journey code per line

void BST::traverse(int typeOfTraversal){
   if(typeOfTraversal==0){
      Pre_order(this->root);
   }
   if(typeOfTraversal==1){
      Post_order(this->root);
   }
   if(typeOfTraversal==2){
      In_order(this->root);
   }
   return;
}

// Returns the price of the cheapest journey
int BST::getMinimum(){
   TreeNode y;
   TreeNode z=*root;
   while(root->left!=NULL){
         y=*root;
         root=root->left;
   }
   root=&z;
   return y.price;
}

// Part II

// Returns the count of journeys that are at least as expensive
// as lowerPriceBound and at most as expensive as upperPriceBound,
// both bounds included.
int BST::countJourneysInPriceBound(int lowerPriceBound, int upperPriceBound) {return 0; }

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
        root = root->right;
        printBST( prefix + (isLeft ? "│   " : "    "), false);
        root = curr;
    }
}

void BST::getBST(const string& prefix,  bool isLeft=false)
{
    if( root != nullptr )
    {
        result.push_back(prefix);

        result.push_back(isLeft ? "├──" : "└──" );

        // print the value of the node
        result.push_back(root->JourneyCode + "\n");
        TreeNode *curr = root;
        root = root->left;
        // enter the next tree level - left and right branch
        getBST( prefix + (isLeft ? "│   " : "    "), true);
        root = root->right;
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




