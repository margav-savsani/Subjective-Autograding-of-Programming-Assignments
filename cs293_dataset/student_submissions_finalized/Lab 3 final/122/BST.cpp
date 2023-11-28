#include <bits/stdc++.h>

#include <iostream>

#include <vector>

#include <string>
#include<fstream>

using namespace std;

#include "BST.h"

#define PRE_ORDER 0
#define POST_ORDER 1
#define IN_ORDER 2
#define LOAD_FULL_BST 3
#define LOAD_LEFT_SUBTREE 4
 
// PLEASE FILL IN THE BODIES OF THE FOLLOWING FUNCTIONS

/*void BST::serialize(string filename,TreeNode*pt){
    if(root==nullptr){
    ofstream outfile;
    outfile.open("filename");
    outfile << "root->Price = -1 "<<"root->upperPriceBound =-1";
    }
    else {
        ofstream outfile;
    outfile.open("filename");
    outfile << root->Price  <<root->upperPriceBound =-1;
       serialize(filename,root->left);
       serialize(filename,root->right); 
    }

}
*/

/*int  BST::preordersum(TreeNode *ptr,int lowerPriceBound, int upperPriceBound){
  if(ptr->price > upperPriceBound)  {
    TreeNode*pt = ptr->left;
    return preorder(pt,lowerPriceBound,uppercase);
  }
  if(ptr->price <lowerPriceBound){
    TreeNode*u =ptr->right;
    return preorder(u,lowerPriceBound,upperPriceBound);
  }
if(ptr==NULL){
return 0;}
else{ 
 return 1+preorder( ptr->left,lowerPriceBound,upperPriceBound)+preorder( ptr ->right,lowerPriceBound,upperPriceBound);}}*/


void BST::preorder(TreeNode *ptr){
if(ptr==NULL){
return ;}
else{ cout<<ptr->JourneyCode;}
preorder( ptr->left);
preorder( ptr ->right);}

void BST:: postorder(TreeNode *ptr){
if(ptr == NULL){
return ;
}
else{
postorder(ptr->left);
postorder( ptr->right);
cout<< ptr->JourneyCode;}
}
void BST::inorder(TreeNode *ptr){
if(ptr ==NULL) {
return;}
else inorder( ptr->left);
cout << ptr->JourneyCode;
inorder( ptr->right);}

  int BST::func(TreeNode *ptr )
   {

                if (ptr -> left == NULL) {
                    return ptr -> price;
                } else {
                    TreeNode *pt = ptr -> left;
                   return func(pt);
                }

            }
 bool BST::fun(TreeNode *ptr,int JourneyCode,int price) {
if(ptr ==nullptr){
return false;}
           if (price == ptr -> price) {
               
               if(JourneyCode == ptr -> JourneyCode){
                            return true;}
                    else return false;
            }
            
            
            
            if (price > ptr -> price) {
                if (ptr -> right == nullptr) {
                
                    return false;
                }
                TreeNode *pt = ptr -> right;
                return fun( pt,JourneyCode,price);
            } else {
                if (ptr -> left == nullptr) {
                    return false;
                }
                
                TreeNode *pt = ptr -> left;
                 return fun(pt,JourneyCode,price);
            }
        }
        
  bool BST::function(TreeNode *ptr,int JourneyCode,int price) {
  if(root==nullptr){
TreeNode *y;
y =new TreeNode();
y->price =price;
y->JourneyCode=JourneyCode;
y->left=nullptr;
y->right=nullptr;
y->parent=nullptr;
root=y;
return true;}
else{
        if (price == ptr -> price) {
            if (JourneyCode == ptr -> JourneyCode) {
                return false;
            } 
        }
        if (price > ptr -> price) {
       
        
            if (ptr -> right == nullptr) {
            TreeNode *val;
            val = new TreeNode();
           
            val->price=price;
            val->JourneyCode=JourneyCode;
              ptr->right = val;
              return true;
            }
            TreeNode *pt = ptr -> right;
          return  function(pt,JourneyCode,price);
        } else {
            if (ptr -> left == nullptr) {
           
            TreeNode *value;
            value=new TreeNode();
            value->price= price;
             value->JourneyCode=JourneyCode; 
             ptr ->left = value;
              return true;  
            }
            TreeNode *pt = ptr -> left;
          return  function(pt,JourneyCode,price);
        }
        }
    }

BST::BST() {
   root = NULL ;
}
BST::BST(TreeNode *root) {
  this -> root =root  ;
}

// Returns false, if given JourneyCode is already present in the BST
// Inserts the element and returns True otherwise
bool BST::insert(int JourneyCode, int price) {
    
    TreeNode *npr = root;
    
  return   function(npr,JourneyCode,price);
}

// Return True, if the ticket with given attributes is found, false otherwise
bool BST::find(int JourneyCode, int price) {
         
         
        
       return  fun(root, JourneyCode,price);}

        // Returns false, if JourneyCode isn't present
        // Deletes the corresponding entry and returns True otherwise
      
           TreeNode* min(TreeNode *n);
TreeNode* del(TreeNode *r, int key);
bool remove(int JourneyCode, int price);

TreeNode* BST :: min(TreeNode *n){
    while(n->left != NULL){
        n = n->left;
    }
    return n;
}

TreeNode* BST :: del(TreeNode *r, int key){
    if(r == NULL){
        return r;
    }
    if(key < r->price){
        r->left = del(r->left, key);
    }
    else if(key > r->price){
        r->right = del(r->right, key);
    }
    else{
        if(r->left == NULL && r->right == NULL){
            return NULL;
        }
        else if(r->left == NULL){
            TreeNode *temp = r->right;
            free(r);
            return temp;
        }
        else if(r->right == NULL){
            TreeNode *temp = r->left;
            free(r);
            return temp;
        }
        else if(r->left != NULL && r->right != NULL){
            TreeNode *temp = min(r->right);
            r->JourneyCode = temp->JourneyCode;
            r->price = temp->price;
            r->right = del(r->right, temp->price);
        }
    }
    return r;
}

bool BST :: remove(int JourneyCode, int price){
    if( !(find(JourneyCode,price)) ){
        return false;
    }
    else{
        root = del(root,price);
    }
    return true;
}
        

        // Functions that traverse the BST in various ways!
        // type is one of PRE_ORDER, POST_ORDER or IN_ORDER
        // Print on cout the journey codes at nodes of the BST in the same order as
        // they are encountered in the traversal order
        // Print one journey code per line

        void BST::traverse(int typeOfTraversal) {
        TreeNode *ptr =root;
        if(typeOfTraversal==0){
       preorder( ptr);}
        if(typeOfTraversal==1){
       postorder( ptr);}
        if(typeOfTraversal==2){
       inorder( ptr);}       
        }

        // Returns the price of the cheapest journey
        int BST::getMinimum() {
            
            TreeNode *ptrl = root;
          return   func(ptrl);
        }

        // Part II

        // Returns the count of journeys that are at least as expensive
        // as lowerPriceBound and at most as expensive as upperPriceBound,
        // both bounds included.
        int BST::countJourneysInPriceBound(int lowerPriceBound, int upperPriceBound) {
           /* if (root==nullptr){
                return 0;
            }
            else {
            return preordersum(root,lowerPriceBound,upperPriceBound);}*/
            
                return 0;
            }
        

        // Store the current tree in a file called filename.  You should
        // store using a scheme that uses no more disk space than that
        // required to store all elements in the BST, plus perhaps a small
        // constant times the number of elements.  You should also store
        // in a manner such that your implementation of customLoad is as
        // memory and time efficient as possible.
        void BST::customStore(string filename) {
            












        }

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

        void BST::customLoad(int flag, string filename) {
            return;
        }

        // ************************************************************
        // DO NOT CHANGE ANYTHING BELOW THIS LINE

        // Adapted from Adrian Schneider's code on StackOverflow
        void BST::printBST(const string & prefix, bool isLeft = false) {
            if (root != nullptr) {
                cout << prefix;

                cout << (isLeft ? "|--" : "|__");

                // print the value of the node
                cout << root -> JourneyCode << endl;
                TreeNode * curr = root;
                root = root -> left;
                // enter the next tree level - left and right branch
                printBST(prefix + (isLeft ? "│   " : "    "), true);
                root = root -> right;
                printBST(prefix + (isLeft ? "│   " : "    "), false);
                root = curr;
            }
        }

        void BST::getBST(const string & prefix, bool isLeft = false) {
            if (root != nullptr) {
                result.push_back(prefix);

                result.push_back(isLeft ? "├──" : "└──");

                // print the value of the node
                result.push_back(root -> JourneyCode + "\n");
                TreeNode * curr = root;
                root = root -> left;
                // enter the next tree level - left and right branch
                getBST(prefix + (isLeft ? "│   " : "    "), true);
                root = root -> right;
                getBST(prefix + (isLeft ? "│   " : "    "), false);
                root = curr;
            }
        }

        void BST::clearResult() {
            result.clear();
        }

        vector < string > BST::getResult() {
            return result;
        }
