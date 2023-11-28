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

void BST::countJourneys(TreeNode* node, int lowerBound, int upperBound, int* counter){
    //base case
    if(node->price < lowerBound){
        BST::countJourneys(node->right,lowerBound, upperBound, counter);
        return;
    }
    if(node->price > upperBound){
        BST::countJourneys(node->left,lowerBound, upperBound, counter);
        return;
    }
    if((node->price >= lowerBound)&&(node->price <= upperBound)){
        (*counter)++;
        BST::countJourneys(node->left,lowerBound, upperBound, counter);
        BST::countJourneys(node->right,lowerBound, upperBound, counter);
        return;
    }
}

void BST::preorder(TreeNode* node){
    // cout<<"in";
    if(node==NULL)
        return;
    cout<<node->JourneyCode<<endl;
    BST::preorder(node->left);
    BST::preorder(node->right);
}
void BST::postorder(TreeNode* node){
    if(node==NULL)
        return;
    BST::postorder(node->left);
    BST::postorder(node->right);
    cout<<node->JourneyCode<<endl;
}
void BST::inorder(TreeNode* node){
    if(node==NULL)
        return;
    BST::inorder(node->left); 
    cout<<node->JourneyCode<<endl;
    BST::inorder(node->right);
}

TreeNode* BST::succ( TreeNode* x){
    if(x->right!=NULL)
        return BST::getMinimum(x->right);
    else{
        TreeNode* y = x->parent;
        if(y==NULL)
            return NULL;
        while( y != NULL && x==y->right){
            x=y;
            y=y->parent;
        }
        return y;
    }
}

TreeNode* BST::getMinimum(TreeNode* t){
    TreeNode* temp = t;
    TreeNode* temp2 = NULL;

    if(temp==NULL){
        return NULL;
    }

    while( temp != NULL){
        temp2 = temp;
        temp = temp->left;
    }
    
    return temp2; 
}

BST::BST(){
    this->root = NULL; 
    }
BST::BST(TreeNode *root){
    this->root = root; 
    this->root->parent = NULL;
    }

// Returns false, if given JourneyCode is already present in the BST
// Inserts the element and returns True otherwise
bool BST::insert(int JourneyCode, int price) { 
    TreeNode* x = root; //for checking
    TreeNode* y = NULL; //for pointing to the parent
    TreeNode* node = new TreeNode(JourneyCode, price, NULL, NULL, NULL);

    if(root == NULL){
        root = node;
        return true;
    }

    while(x != NULL){
        // cout<<"x not null";
        y = x;
        if(x->price == price && x->JourneyCode == JourneyCode){
            return false;
        }
        if(x->price > price){
            x = x->left;
        }
        else{
            x = x->right;
        }
    }
    node->parent = y;

    if(y->price > price){
        y->left = node;
    }
    else{
        y->right = node;
    }
    
    return true;
    }

// Return True, if the ticket with given attributes is found, false otherwise
bool BST::find(int JourneyCode, int price) { 
    TreeNode* temp = root; 
    // TreeNode* follow = NULL;


    while(temp != NULL){
        if(temp->price == price && temp->JourneyCode==JourneyCode){
            return true;
        }
        if(temp->price > price){
            temp = temp->left;
        }
        else{
            temp = temp->right;
        }
    }
    
    return false; 
    }
	
// Returns false, if JourneyCode isn't present
// Deletes the corresponding entry and returns True otherwise
bool BST::remove(int JourneyCode, int price) { 
    if( !BST::find(JourneyCode,price) ){
        return false;
    }
    else{
        TreeNode* temp = root;
        TreeNode* x = NULL;

        while( temp->JourneyCode!=JourneyCode && temp!=NULL ){
            if(temp->price > price ){
                temp = temp->left;
            }
            else{
                temp = temp->right;
            }
        }
        if(temp==NULL) //if by any chance not found 
            return false;

        if(temp->JourneyCode == JourneyCode){ //node to be deleted is found, its temp

            //------when temp is the leaf------
            if(temp->left==NULL && temp->right==NULL){ 
                
                if(temp->parent==NULL){ //deleting root node
                    root = NULL; //tree deleted
                    return true;
                }
                if(temp->parent->left == temp){ //temp is the leftchild of its parent
                    temp->parent->left = NULL; //temp deleted
                    return true;
                }
                else{ 
                    temp->parent->right = NULL; //temp being rightchild
                    return true;
                }
            } 
            //---------temp has only one child--------
            else if(temp->left==NULL || temp->right==NULL){

                TreeNode* p,  *notNullChild;
                p = temp->parent;  //p is the parent of temp

                //notNullChild is the only not NULL child of temp
                if(temp->left==NULL){
                    notNullChild=temp->right;
                }
                else{
                    notNullChild = temp->left;
                }
         
                if(p==NULL){
                    root = notNullChild;
                    root->parent=NULL;
                    return true;
                }
                // cout<<"oh no";
                if(p->left == temp){ //temp is the leftchild of p
                    p->left =  notNullChild;
                    notNullChild->parent = p;
                    return true;
                }
                else{ //temp being right child  
                    p->right = notNullChild;
                    notNullChild->parent = p;
                    return true;
                }
            }
            //---------temp has two children---------
            else{

                TreeNode* suc = BST::succ(temp);
                bool yes = BST::remove(suc->JourneyCode, suc->price);
                if(!yes)
                    return false;
                temp->JourneyCode = suc->JourneyCode;
                temp->price = suc->price;
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
    TreeNode* temp = root;

    if( typeOfTraversal == 0 ){ //pre-order
       
        BST::preorder(temp);
    }
    if( typeOfTraversal == 1 ){ //post-order
        BST::postorder(temp);
    }
    if( typeOfTraversal == 2 ){ //in-order
        BST::inorder(temp);
    }
    
     return; 
}

// Returns the price of the cheapest journey
int BST::getMinimum() {
    TreeNode* temp = root;
    TreeNode* temp2 = NULL;

    if(temp==NULL){
        return -1;
    }

    while( temp != NULL){
        temp2 = temp;
        temp = temp->left;
    }
    int min = temp2->price;
    return min; 
}

// Part II

// Returns the count of journeys that are at least as expensive
// as lowerPriceBound and at most as expensive as upperPriceBound,
// both bounds included.
int BST::countJourneysInPriceBound(int lowerPriceBound, int upperPriceBound) {
    int counter=0;
    countJourneys(BST::root, lowerPriceBound, upperPriceBound, &counter);
    return counter; 

}

TreeNode* BST::loadTree(TreeNode* node, int maxprice, vector<int>jc, int* ijc, vector<int>price, int* ip){
    
    
    if(*ijc>=jc.size() || *ip>=price.size()) {
        cout<<"noo\n";
        return NULL;
    }
    if(price[*ip] > maxprice) {
        return NULL;
    };
    TreeNode* temp = new TreeNode(jc[*ijc], price[*ip], NULL, NULL, NULL );
    (*ijc)++;
    cout<<"ijc-"<<*ijc<<endl;
    (*ip)++;
    temp->parent = node;
    temp->left = BST::loadTree(temp, temp->price, jc, ijc, price, ip);
    temp->right = BST::loadTree(temp, maxprice, jc, ijc, price, ip);   
    return temp;

}

// Store the current tree in a file called filename.  You should
// store using a scheme that uses no more disk space than that
// required to store all elements in the BST, plus perhaps a small
// constant times the number of elements.  You should also store
// in a manner such that your implementation of customLoad is as
// memory and time efficient as possible.
void BST::customStore(string filename) { 
    stack<TreeNode*> stnode;
    BST::printBST("");
    stnode.push(root);
    cout<<"can be seen"<<endl;
    fstream outfile;
    outfile.open(filename,ios::out);
    cout<<"file v open ho rha h"<<endl;
    while(stnode.empty()==false){

        TreeNode* node = stnode.top();
        outfile<<(node->JourneyCode)<<" "<<node->price<<endl; 
        stnode.pop();
        if(node->right)
            stnode.push(node->right);
        if(node->left)
            stnode.push(node->left);
    }

    outfile<<"-1"<<endl;

    stack<TreeNode*> stnodeLeft;
    BST::printBST("");
    if(root->left != NULL){
        stnodeLeft.push(root->left);
        cout<<"can be seen"<<endl;
        // ofstream outfile;
        // outfile.open(filename);
        cout<<"file v open ho rha h"<<endl;
        while(stnodeLeft.empty()==false){

            TreeNode* nodeL = stnodeLeft.top();
            outfile<<(nodeL->JourneyCode)<<" "<<nodeL->price<<endl; 
            stnodeLeft.pop();
            if(nodeL->right)
                stnodeLeft.push(nodeL->right);
            if(nodeL->left)
                stnodeLeft.push(nodeL->left);
            cout<<"off";
        }
    }
    else cout<<"left is null"<<endl;

    cout<<"custom store"<<endl;
    outfile.close();
    return; 
    
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
 
void BST::customLoad (int flag, string filename) { 
    string word ;
    cout<<"before infile"<<endl;
    fstream file;
    cout << "done \n";
    file.open(filename,ios::in);
    cout<<"ok"<<endl;
    vector <int> arrofJC;
    vector <int> arrofP;

    if (flag == LOAD_FULL_BST){ 
        cout<<"inside\n";     
        while(file>>word){
            
            if(word!="-1"){
                arrofJC.push_back(stoi(word));
                file>>word;
                arrofP.push_back(stoi(word));
            }
            else
                break;
        }
    }
    else if(flag==LOAD_LEFT_SUBTREE){
        file>>word;
        while(word!="-1"){
            file>>word;
        }
        while(file>>word){
            arrofJC.push_back(stoi(word));
            file>>word;
            arrofP.push_back(stoi(word));
        }
    }

    file.close();
    cout<<"closed"<<endl;

    //now comes the main work of loading the tree
    int *ijc, *ip;
    *ijc = 0;
    *ip = 0;
    BST::root = BST::loadTree(NULL, INT64_MAX, arrofJC, ijc, arrofP, ip );
    cout<<"return"<<endl;
    BST::printBST("");
    return; 

}


// ************************************************************
// DO NOT CHANGE ANYTHING BELOW THIS LINE

// Adapted from Adrian Schneider's code on StackOverflow
void BST::printBST(const string& prefix, bool isLeft)
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

