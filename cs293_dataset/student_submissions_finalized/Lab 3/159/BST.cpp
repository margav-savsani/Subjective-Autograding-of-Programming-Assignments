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
BST::BST(){
    root=nullptr;
 }
BST::BST(TreeNode *Root){
    root=Root;
 }
bool BST::insert(int JourneyCode, int price) {
    TreeNode *x;
    TreeNode *y;
    TreeNode *z=new TreeNode(JourneyCode,price);
    x=root;
    y=nullptr;
    while (x!=nullptr && price!=(x->price)){
        y=x;
        if(price<x->price){
            x=x->left;
        }
        else {x=x->right;}
    }
    if(x->JourneyCode==JourneyCode){return false;}
    z->parent=y;
    if(y==nullptr){root=z;}
    else if(price<y->price){z=y->left;}
    else {z=y->right;}
    return true;
}
bool BST::find(int JourneyCode, int price) {
    TreeNode *x;
    TreeNode *y;
    x==root;
    while (x!=nullptr && price!=(x->price)){
        if (price<(x->price)){
            x=x->left;
        }
        else x=x->right;
    }
    y==x;
    if(y==nullptr){return false;}
    else if(y->JourneyCode!=JourneyCode){return false;}
    else { return true;}
}
TreeNode* BST::treesuccesor(TreeNode *v){
    TreeNode *y;
    if(v->right!=nullptr){
        y=v->right;
        while(y->left!=nullptr){
            y=y->left;
        }
    }
    else{
        y=v->parent;
        while((y!=nullptr)&&(v==y->right)){
            v=y;
            y=y->parent;
        }
    }
    return y;
}
bool BST::remove(int JourneyCode, int price) {
    TreeNode *x;
    TreeNode *y;
    TreeNode *z;
    TreeNode *t;
    x==root;
    while (x!=nullptr && price!=(x->price)){
        if (price<(x->price)){
            x=x->left;
        }
        else x=x->right;
    }
    y==x;
    if(y==nullptr){return false;}
    else if(y->JourneyCode!=JourneyCode){return false;}
    else {
        if(y->left==nullptr || y->right==nullptr){
            z=y;
        }
        else{z=treesuccesor(y);}
        if(z->left!=nullptr){t=z->left;}
        else {t=z->right;}
        if(t!=nullptr){t->parent=z->parent;}
        if(z->parent==nullptr){root=t;}
        else if(z==((z->parent)->left)){
            (z->parent)->left=t;
        }
        else (z->parent)->right=t;
        if(z!=y){
            y=z;
        }
    }
    return true;

}
void BST::preorder(TreeNode *v){
    if(v==nullptr){return;}
    else{
        cout<<v->JourneyCode<<endl;
        preorder(v->left);
        preorder(v->right);
    }
}
void BST::postorder(TreeNode *v){
    if(v==nullptr){return;}
    else{
        postorder(v->left);
        postorder(v->right);
        cout<<v->JourneyCode<<endl;
    }
}
void BST::inorder(TreeNode *v){
    if(v==nullptr){return;}
    else{
        inorder(v->left);
        cout<<v->JourneyCode<<endl;
        inorder(v->right);
    }
}

void BST::traverse(int typeOfTraversal) {
    if(typeOfTraversal==0){preorder(root);}
    else if(typeOfTraversal==1){postorder(root);}
    else if(typeOfTraversal==2){inorder(root);}
    else;
}
int BST::getMinimum() {
    TreeNode *x;
    x=root;
    while(x->left!=nullptr){
        x=x->left;
    }
    return x->price;
}
void BST::customStore(string filename) { return; }
int BST::countJourneysInPriceBound(int lowerPriceBound, int upperPriceBound) {return 0; }
void BST::customLoad (int flag, string filename) { return; }
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
