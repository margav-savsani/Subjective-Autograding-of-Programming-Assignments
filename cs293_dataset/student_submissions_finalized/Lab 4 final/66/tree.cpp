
#include <bits/stdc++.h>
#include <iostream>
#include <vector>
#include <string>

using namespace std;

#include "tree.h"

TreeNode* BST::successor(TreeNode *x){
  if(x->left==nullptr||x->right==nullptr){ return x; }
  else{ return successor(x->left); }
}

void BST::pretraverse(TreeNode *x){
        
        cout << x->JourneyCode<<" "<< x->getImbalance()<<"  ";
        
        if(x->left!=nullptr) {pretraverse(x->left);}
        if(x->right!=nullptr){pretraverse(x->right);}
  }

void BST::pretraverse(){pretraverse(root);}

void BST::update(TreeNode *x){

      if(x->left==nullptr||x->right==nullptr){x->shortestPathLength=1;
            if(x->left==nullptr) {  if(x->right==nullptr) x->longestPathLength=1;
                               else x->longestPathLength=(x->right)->longestPathLength+1; }
            
            else if(x->right==nullptr) { x->longestPathLength=(x->left)->longestPathLength+1; }}
      else{  if((x->left)->shortestPathLength>(x->right)->shortestPathLength) x->shortestPathLength=(x->right)->shortestPathLength+1;
             else x->shortestPathLength=(x->left)->shortestPathLength+1;
             
             if((x->left)->longestPathLength>(x->right)->longestPathLength) x->longestPathLength=(x->left)->longestPathLength+1;
             else x->longestPathLength=(x->right)->longestPathLength+1; }
     if(x->parent==nullptr) return;
     else update(x->parent);
}




TreeNode* BST::findelement(TreeNode* x,int j,int p){
   
   if(x->JourneyCode==j){ return x; }
   else if(x->JourneyCode>j){ if(x->left==nullptr) {return nullptr;} else return findelement(x->left,j,p); }
   else { if(x->right==nullptr) {return nullptr;} else return findelement(x->right,j,p); }
    
}

TreeNode* BST::findleave(TreeNode* x){
    
    if(x->left==nullptr) {return x;}
    else { return findleave(x->left);}
}


TreeNode* BST::parent(TreeNode* x,int j,int price){

         if(x->JourneyCode> j ) {
              
             if(x->left == nullptr){return x;}
             else { return parent(x->left,j,price);}  
         } 
         
         else if(x->JourneyCode <j){
             
             if(x->right == nullptr){return x;}
             else {return parent(x->right,j,price);}
         }  
         
         else{
              if(x->left==nullptr){ return x;}
              else if(x->right==nullptr) {return x;}
              else {return parent(x->right,j,price);}
         }
}

int BST::getImbalance()
{
  if (root == nullptr) return 0;
  else return root->getImbalance();
}

bool BST::insert(int JourneyCode, int price)
{
   if(root==nullptr){ 
        root = new TreeNode();
         root->shortestPathLength=1;
        root->longestPathLength=1;
        root->price=price;
        root->JourneyCode=JourneyCode;
        
        
        }
        
   else{ 
       if(find(JourneyCode,price)==true) {return false;}
       else{
       TreeNode* n = parent(root,JourneyCode,price);
       
       if(n->JourneyCode>JourneyCode) { 
            
            n->left=new TreeNode();
            (n->left)->price=price;(n->left)->JourneyCode=JourneyCode;
            (n->left)->parent=n; 
            (n->left)->shortestPathLength=1;
            (n->left)->longestPathLength=1;
            update(n);
           
       }
       else {n->right=new TreeNode();(n->right)->price=price;(n->right)->JourneyCode=JourneyCode;
            (n->right)->parent=n;
            (n->right)->shortestPathLength=1;
            (n->right)->longestPathLength=1;
            update(n);
            }}
   }
  
 
   return true;  
  // JourneyCode is not present in the BST.  We must now
  // insert an appropriate child of parentOfCurrNode.
  // Please implement this part yourself.
  //
  // Do not forget to update shortestPathLength and
  // longestPathLength of (possibly all) BST nodes in the
  // path from the root to the new node you are inserting

}

// Return True, if the ticket with given attributes is found, false otherwise
bool BST::find(int JourneyCode, int price)
{
  if(root==nullptr) { return false;}
     else {  
          if(findelement(root,JourneyCode,price)==nullptr) { return false;}
          else { return true; }
     }  
}
	
// Returns false, if JourneyCode isn't present
// Deletes the corresponding entry and returns True otherwise
bool BST::remove(int JourneyCode, int price)
{
  if(findelement(root,JourneyCode,price)==nullptr) {return false;}
   else { TreeNode* x;TreeNode *y;TreeNode *a;int t;
         TreeNode* z = findelement(root,JourneyCode,price);
         
         if(z->left==nullptr || z->right==nullptr){y=z;t=0;}
         else   { y=successor(z->right);a=y->parent;t=1; }
         
         if(y->left !=nullptr){ x=y->left; }
         else if(y->right!=nullptr){x=y->right; }
         else { x=nullptr; }
         
         if(x!=nullptr){ x->parent=y->parent; }
         if(y->parent == nullptr){  root=x;     }
         else if(y==(y->parent)->left){ (y->parent)->left=x; }
         else {  (y->parent)->right=x;}
         
         if(y!=z){ z->price=y->price;z->JourneyCode=y->JourneyCode; }
         
         if(t==0){ update(y->parent); }
         else{ update(a); }
         return true;}
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

