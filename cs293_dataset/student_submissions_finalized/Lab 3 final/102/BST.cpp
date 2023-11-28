#include <bits/stdc++.h>
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
using namespace std;

#include "BST.h"

#define PRE_ORDER 0
#define POST_ORDER 1
#define IN_ORDER 2
#define LOAD_FULL_BST 3
#define LOAD_LEFT_SUBTREE 4


// PLEASE FILL IN THE BODIES OF THE FOLLOWING FUNCTIONS

BST::BST(){
    root=new TreeNode();
    root->parent=nullptr;

};
BST::BST(TreeNode *root){
    this->root=root;
}

bool actualInsert(int JourneyCode, int price , TreeNode*(*currentNode) , TreeNode*(*currentParent)){
    // cout<<"Reached checkpoint 2 \n";
    if(*currentNode==nullptr){
        //cout<<"Address:"<<&*currentNode<<endl;
        *currentNode=new TreeNode(JourneyCode,price,nullptr,nullptr,(*currentParent));
        return true;
    }
    else if((*currentNode)->price > price && (*currentNode)->price!=0){
        //cout<<"Going left in insert \n";
        return actualInsert(JourneyCode,price,&((*currentNode)->left),&(*currentNode));
    }
    else if((*currentNode)->price <= price && (*currentNode)->price!=0){
        //cout<<"Going right in insert \n";
        return actualInsert(JourneyCode,price,&((*currentNode)->right),&(*currentNode));
    }
    else{
        return false;
    }
};

bool actualFind(int JourneyCode, int price , TreeNode*currentNode , TreeNode*currentParent){
    //cout<<"Reached checkpoint 4 \n";
    if(currentNode==nullptr){
        return false;
    }
    else if(currentNode->price == price && currentNode->price!=0 && currentNode->JourneyCode==JourneyCode){
        return true;
        //actualInsert(JourneyCode,price,currentNode->left,currentNode);
    }
    else if(currentNode->price <= price && currentNode->price!=0){
        // cout<<"Going right in find \n";
        return actualFind(JourneyCode,price,currentNode->right,currentNode);
    }
    else if(currentNode->price > price && currentNode->price!=0){
        //cout<<"Going left in find \n";
        return actualFind(JourneyCode,price,currentNode->left,currentNode);
    }
}



bool actualRemove(int JourneyCode, int price , TreeNode*(*currentNode) , TreeNode*(*currentParent)){

    if((*currentNode)->price == price && (*currentNode)->price!=0 && (*currentNode)->JourneyCode==JourneyCode){
        if((*currentNode)->right==nullptr && (*currentNode)->left==nullptr){
            (*currentNode)=nullptr;
            return true;
        }
        //if has one child only either right or left
        else if((*currentNode)->left==nullptr && (*currentNode)->right!=nullptr){
            (*currentNode)=(*currentNode)->right;
        }
        else if((*currentNode)->left!=nullptr && (*currentNode)->right==nullptr){
            (*currentNode)=(*currentNode)->left;
            return true;
        }
        //if has two childs;
        else if((*currentNode)->left!=nullptr && (*currentNode)->right!=nullptr){
            TreeNode*temp;
            temp=(*currentNode)->left;
            if(temp->right==nullptr){
                return false;
            }
            // temp=(*currentNode)->left->right;
            while(true){
                if(temp!=nullptr && temp->right==nullptr){
                    //temp->parent->right=nullptr;
                    temp->parent->left=nullptr;
                    temp->parent=nullptr;
                    temp->parent=(*currentNode)->parent;
                    temp->right=(*currentNode)->right;
                    temp->left=(*currentNode)->left;
                    *currentNode=temp;
                    return true;
                }
                else {
                    temp=temp->right;
                }
            }
        }
    }
    else if((*currentNode)->price > price && (*currentNode)->price!=0){
        return actualRemove(JourneyCode,price,&((*currentNode)->left),&(*currentNode));
    }
    else if((*currentNode)->price <= price && (*currentNode)->price!=0){
        return actualRemove(JourneyCode,price,&((*currentNode)->right),&(*currentNode));   
    }
}


// Returns false, if given JourneyCode is already present in the BST
// Inserts the element and returns True otherwise
bool BST::insert(int JourneyCode, int price){
    if(find(JourneyCode,price)){
        return false;
    }
    //cout<<"Reached checkpoint 1 \n";
    if(root->price==0){
        root->JourneyCode=JourneyCode;
        root->price=price;
        return true;
    }
    return actualInsert(JourneyCode,price,&root,nullptr);
};

// Return True, if the ticket with given attributes is found, false otherwise
bool BST::find(int JourneyCode, int price){
    //cout<<"Reached checkpoint 3 \n";
    return actualFind(JourneyCode,price,root,nullptr);
};
	
// Returns false, if JourneyCode isn't present
// Deletes the corresponding entry and returns True otherwise
bool BST::remove(int JourneyCode, int price){
    if(!find(JourneyCode,price)){
        return false; 
    }
    else{
        return actualRemove(JourneyCode,price,&root,nullptr);
    }
}
	
// Functions that traverse the BST in various ways!
// type is one of PRE_ORDER, POST_ORDER or IN_ORDER
// Print on cout the journey codes at nodes of the BST in the same order as
// they are encountered in the traversal order
// Print one journey code per line

void preorder(TreeNode*currentNode , TreeNode*currentParent) {
    if(currentNode==nullptr){
        return;
    }
  cout << currentNode->JourneyCode<<endl;
  preorder(currentNode->left,currentNode);
  preorder(currentNode->right,currentNode);
}

void inorder(TreeNode*currentNode , TreeNode*currentParent){
    if(currentNode==nullptr){
        return;
    }
    inorder(currentNode->left,currentNode);
    cout << currentNode->JourneyCode<<endl;
    inorder(currentNode->right,currentNode);
};

void postorder(TreeNode*currentNode , TreeNode*currentParent) {
    if (currentNode==nullptr){
        return;
    }   
    postorder(currentNode->left,currentNode);
    postorder(currentNode->right,currentNode);
    cout<<currentNode->JourneyCode<<endl;
}

void BST::traverse(int typeOfTraversal) {
    if(typeOfTraversal==0){
        preorder(root,nullptr);
    }
    if(typeOfTraversal==1){
        postorder(root,nullptr);
    }
    if(typeOfTraversal==2){
        inorder(root,nullptr);
    }
};

int actualMin(TreeNode*currentNode , TreeNode*currentParent){
    if (currentNode==nullptr){
        return currentParent->price;
    }  
    else {
        return actualMin(currentNode->left,currentNode);
    }
}

// Returns the price of the cheapest journey
int BST::getMinimum(){ 
    return actualMin(root,nullptr);
}
// Part II

int actualcount(int lowerPriceBound, int upperPriceBound,TreeNode*currentNode , TreeNode*currentParent){
    int count=0;
    if (currentNode==nullptr){
        return count;
    }   
    else if(currentNode->price<=upperPriceBound && currentNode->price>=lowerPriceBound){
        count++;
        return actualcount(lowerPriceBound,upperPriceBound,currentNode->left,currentParent);
    }
}

// Returns the count of journeys that are at least as expensive
// as lowerPriceBound and at most as expensive as upperPriceBound,
// both bounds included.
int BST::countJourneysInPriceBound(int lowerPriceBound, int upperPriceBound) {
    return actualcount(lowerPriceBound,upperPriceBound,root,nullptr);
}

void preorder1(TreeNode*currentNode , TreeNode*currentParent , ostream &file) {   
    if(currentNode==nullptr){
        file<<-1;
        return;
    }
    file << currentNode->JourneyCode<<endl;
    preorder1(currentNode->left,currentNode,file);
    preorder1(currentNode->right,currentNode,file);
}

void inorder1(TreeNode*currentNode , TreeNode*currentParent , ostream &file){
    if(currentNode==nullptr){
        file<<-1;
        return;
    }
    inorder1(currentNode->left,currentNode,file);
    file << currentNode->JourneyCode<<endl;
    inorder1(currentNode->right,currentNode,file);
};

// Store the current tree in a file called filename.  You should
// store using a scheme that uses no more disk space than that
// required to store all elements in the BST, plus perhaps a small
// constant times the number of elements.  You should also store
// in a manner such that your implementation of customLoad is as
// memory and time efficient as possible.
void BST::customStore(string filename){
    
    ofstream file;
    file.open(filename);
    inorder1(root,nullptr,file);
    file<<-1<<endl;
    preorder1(root,nullptr,file);
    file<<-1<<endl;
    file.close();

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

