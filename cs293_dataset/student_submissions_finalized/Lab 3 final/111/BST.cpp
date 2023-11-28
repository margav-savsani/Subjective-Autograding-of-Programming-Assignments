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




BST::BST(){; }
BST::BST(TreeNode *root){; }

int height(struct TreeNode* x){
    if (x==NULL){
        return 0;
    }
    else{
        return x->height;
    }
}
int max(int a , int b){
    if(a>b){
        return a;
    }
    return b;
}
bool BST::insert(int JourneyCode, int price){
    bool t;
    if(root==NULL){
        root->JourneyCode = JourneyCode;
        root->price = price;
        t = true;
    }    
    struct TreeNode * temp = root;
    while(temp!=NULL){
        if(price==root->price){
            return false;
        }
        else if(price>=root->price){
            if(temp->right==NULL){
                temp->right=new TreeNode(JourneyCode,price);
                temp->right->parent = temp;
                t=true;
                break;
            }

            else{temp=temp->right;}
        }
        else{
            if(temp->left==NULL){
                temp->left=new TreeNode(JourneyCode,price);
                temp->left->parent = temp;
                t=true;
                break;
            }

            else{
                temp=temp->left;
            }
        }
    }
    while(temp!=nullptr){
        temp->height=1+std::max(height(temp->right),height(temp->left));
        temp=temp->parent;
    }

    return t ;

}

bool BST::find(int JourneyCode, int price) {
    if(root == NULL || price == root->price)
       {return true;}
    else if(price < root->price){
        root = root->left;
        return find(JourneyCode, price);
    }   
    else{
        root = root->right;
        return find(JourneyCode , price);
    }
}
	
struct TreeNode* BST::search(int price){
    struct TreeNode* temp = root;

    if (root == nullptr){
        return NULL;
    }

    while(temp!=NULL){
        if (price==temp->price)
        {
            return temp;
        }
        else if (price>=temp->price)
        {
            temp=temp->right;
        }
        else {
            temp=temp->left;
        }
    }
    return NULL;
}

bool BST::remove(int JourneyCode, int price) { 
	bool t;
    if(root == NULL){
     struct TreeNode* r = search(price);
    bool t;

    if (r==NULL){
        t=false;
    }
    else{
        struct TreeNode *y = new TreeNode();
        struct TreeNode *x = new TreeNode();
        if (r->left == NULL || r->right == NULL)
        {
            y=r;
        }
        else
        {
            y=successor(r);
        }

        if (y->left != NULL)
        {
            x=y->left;
        }
        else
        {
            x=y->right;
        }

        if (x != NULL)
        {
            x->parent = y->parent;
        }

        if (y->parent == NULL)
        {
            this->root=x;
        }
        else {
            if (y==y->parent->left){
                y->parent->left=x;
            }
            else{
                y->parent->right=x;
            }
        }
        delete r;
        t=true;
    }
   return t;
    }
}


void BST::traverse(int typeOfTraversal) {
        if(typeOfTraversal==PRE_ORDER){
             printPreorder(root);
        }
         if(typeOfTraversal==POST_ORDER){
             printPostorder(root);
        }
         if(typeOfTraversal==IN_ORDER){
             printInorder(root);
        }
 }
struct TreeNode* BST::printPostorder(struct TreeNode* node)
{
    if (node == NULL)
        return node;
  
    // first recur on left subtree
    printPostorder(node->left);
  
    // then recur on right subtree
    printPostorder(node->right);
  
    // now deal with the node
    cout << node->JourneyCode << " ";
} 
struct TreeNode* BST:: printInorder(struct TreeNode* node)
{
    if (node == NULL)
        return node;
  
    /* first recur on left child */
    printInorder(node->left);
  
    /* then print the data of node */
    cout << node->JourneyCode << " ";
  
    /* now recur on right child */
    printInorder(node->right);
}
  
/* Given a binary tree, print its nodes in preorder*/
struct TreeNode* BST:: printPreorder(struct TreeNode* node)
{
    if (node == NULL)
        return node;
  
    /* first print data of node */
    cout << node->JourneyCode << " ";
  
    /* then recur on left subtree */
    printPreorder(node->left);
  
    /* now recur on right subtree */
    printPreorder(node->right);
}

int BST::getMinimum() {
    while(root->left->price!=NULL){
        root->price = root->left->price;
    } 
    return root->price;
    }


/*int BST::countJourneysInPriceBound(int lowerPriceBound, int upperPriceBound) {
    if(!root)return 0;
    if(root->price==lowerPriceBound && root->price==upperPriceBound) return 1;
    if(root->left->price>=lowerPriceBound && root->right->price<=upperPriceBound){
        return 1+countJourneysInPriceBound(lowerPriceBound,root->left->price)+countJourneysInPriceBound(root->right->price,upperPriceBound);}
    if(root->right->price<=lowerPriceBound){
        root = root->right;
        countJourneysInPriceBound(lowerPriceBound,upperPriceBound);
    }
    else{
        root = root->left;
        countJourneysInPriceBound(lowerPriceBound,upperPriceBound);
    }
    
}*/

void BST::customStore(string filename) { 
    // If current node is NULL, store marker
    ofstream store;
    store.open(filename);
    if (root == NULL)
    {
        store << "TOMBSTONE";
        return;
    }
 
    // Else, store current node and recur for its children
    while(root!=NULL){
    store<<root->JourneyCode<<root->price;
    root=root->left;
    }
    while(root!=NULL){
        root=root->right;
        store<<root->JourneyCode<<root->price;
    }
    store.close();
 }
 
void BST::customLoad (int flag, string filename) { 
    ifstream in;
    in.open(filename);
    if(flag == 4){
        in>>"TOMBSTONE";
    }
    else{
        root=root->left;
        in>>customStore(filename);
    }
}


// ============================================================
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
struct TreeNode* BST::successor(struct TreeNode* n){
    if (n->right!=nullptr){
        struct TreeNode* temp=n->right;
        while(temp->left!=nullptr){
            temp=temp->left;
        }
        return temp;
    }

    struct TreeNode* p=n->parent;
    while(p!=nullptr&&n==p->right){
        n=p;
        p=p->parent;
    }
    return p;
}
struct TreeNode* BST::predecessor(struct TreeNode* n){
    if (n->left!=nullptr){
        struct TreeNode* temp=n->left;
        while(temp->right!=nullptr){
            temp=temp->right;
        }
        return temp;
    }
    
    struct TreeNode* p=n->parent;
    while(p!=nullptr&&n==p->right){
        n=p;
        p=p->parent;
    }
    return p;
}

void BST::getBST(const string& prefix,  bool isLeft=false)
{
    if( root != nullptr )
    {
        result.push_back(prefix);

        result.push_back(isLeft ? "├──" : "└──" );

        // print the value of the node
        result.push_back((root->JourneyCode + "\n"));
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

