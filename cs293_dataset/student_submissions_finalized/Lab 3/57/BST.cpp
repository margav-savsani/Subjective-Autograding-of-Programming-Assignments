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

BST::BST(){root=new TreeNode(); }
BST::BST(TreeNode *a){root=a; }

// Returns false, if given JourneyCode is already present in the BST
// Inserts the element and returns True otherwise
bool BST::insert(int jc, int pc) { 
    if(find(jc,pc))return false;

   TreeNode *tempNode ;tempNode= new TreeNode();
   TreeNode *current=root;
   
   TreeNode *add;add=new TreeNode(jc,pc);
   if(root->price==0){root=add;return true;}
   
   while(current !=nullptr){
      tempNode= current;
      if (pc <=current->price){
         current=current->left;
       }
      else {current=current->right;}
      }
   add->parent=tempNode;

  if (add->price <= tempNode->price){tempNode->left=add;}
    else {tempNode->right=add;}
    
   return true;
}


// Return True, if the ticket with given attributes is found, false otherwise
bool BST::find(int jc, int pc) { struct TreeNode *current =root;
   if(root->price==0){return false;}
   while(current!=nullptr){
    if((current->price==pc)&&(current->JourneyCode=jc)){return true;}

    if( current->price >= pc){
        current=current->left;}
     else{current=current->right;}
    }
   return false;
   }
struct TreeNode*BST :: minimum(struct TreeNode*base){
    while(base-> left !=nullptr){
        base= base->left;
    };return base;}


struct TreeNode* BST:: delete1(struct TreeNode*base,int jc,int pc){
    if (base ==nullptr)
        return base ;
  
    // If the key to be deleted is 
    // smaller than the root's
    // key, then it lies in left subtree
    if (pc < base->price)
        base->left = delete1(base->left, jc,pc);
  
    // If the key to be deleted is
    // greater than the root's
    // key, then it lies in right subtree

    else if (pc> base->price)
        base->right = delete1(base->right, jc,pc);
  
    // if key is same as root's key, then This is the node
    // to be deleted
    else {
        // node has no child
        if (base->left==nullptr && base->right==nullptr)
            return nullptr;
        
        // node with only one child or no child
        else if (base->left == nullptr) {
            struct TreeNode* temp = base->right;
            free(base);
            return temp;
        }
        else if (root->right == nullptr) {
            struct TreeNode* temp = base->left;
            free(root);
            return temp;
} struct TreeNode* temp=minimum(base->right);
        base->JourneyCode = temp ->JourneyCode;  base->price=temp->price;
        base->right = delete1(base->right,temp->JourneyCode,temp->price);
    }return base;
    

}

 bool BST::remove(int jc, int pc) { 
    if(!find(jc,pc)){return false;}
    struct TreeNode* base =root; struct TreeNode* z; struct TreeNode* y;struct TreeNode* x;struct TreeNode *k;
   delete1(base,jc,pc);
   return true;
    
}
 
 int BST::getMinimum() {struct TreeNode* current = root; 
  
/* loop down to find the leftmost leaf */
while (current->left != nullptr) 
{ 
    current = current->left; 
} 
return(current->price); }

 void BST :: preorder(struct TreeNode*base){
     if (base == nullptr)
        return;
  
    /* first print data of node */
    cout <<base->price << " ";
  
    /* then recur on left subtree */
    preorder(base->left);
  
    /* now recur on right subtree */
    preorder(base->right);

 }
 void BST ::postorder(struct TreeNode*base){
    if (base == nullptr)
        return;
  
    // first recur on left subtree
    postorder(base->left);
  
    // then recur on right subtree
    postorder(base->right);
  
    // now deal with the node
    cout << base->price << " ";

 }
 void BST ::inorder(struct TreeNode*base){
     if (base == nullptr)
        return;
  
    /* first recur on left child */
    inorder(base->left);
  
    /* then print the data of node */
    cout << base->price << " ";
  
    /* now recur on right child */
    inorder(base->right);

 }

void BST::traverse(int typeOfTraversal) {int p=typeOfTraversal;
     switch (p){
        case 0 :{preorder(root);break;}
        case 1 :{postorder(root);break;}
        case 2 :{inorder(root);break;}
    }
 }





// Part II

// Returns the count of journeys that are at least as expensive
// as lowerPriceBound and at most as expensive as upperPriceBound,
// both bounds included.
int BST ::inorderc(struct TreeNode*base,int cnt,int lowerbound,int upperbound){int p;int q;
     if (base == nullptr)
        return 0;
  
    /* first recur on left child */
    cnt=cnt+inorderc(base->left,0,lowerbound,upperbound);
  
    /* then print the data of node */
    if(lowerbound<=base->price && upperbound>= base->price)cnt=cnt+1;
  
    /* now recur on right child */
    cnt=cnt+inorderc(base->right,0,lowerbound,upperbound);
    return cnt;

 }
int BST::countJourneysInPriceBound(int lowerPriceBound, int upperPriceBound) {
    int k=inorderc(root,0,lowerPriceBound,upperPriceBound);
    return k; }

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

        result.push_back(isLeft ? "├──" : "└──" );

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

