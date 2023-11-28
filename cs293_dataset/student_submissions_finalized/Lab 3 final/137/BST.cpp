#include <bits/stdc++.h>
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
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
    root = new TreeNode();
}
BST::BST(TreeNode *root){
    /*this->root->JourneyCode = root->JourneyCode;
    this->root->price = root->price;
    this->root->left = root->left;
    this->root->right = root->right;
    this->root->parent = root->parent;*/
    this->root = new TreeNode(root->JourneyCode,root->price,root->left,root->right,root->parent);
}

// Returns false, if given JourneyCode is already present in the BST
// Inserts the element and returns True otherwise
bool BST::insert(int JourneyCode, int price) { 
    if(root->JourneyCode == 0 && root->price == 0 && root->left == NULL && root->right == NULL)
    {
        root->JourneyCode = JourneyCode;
        root->price = price;
        return true;
    }
    if(root->price>=price)
    {
        if(root->left == NULL)
        {
            root->left = new TreeNode(JourneyCode, price);
            root->left->parent = root;
            return true;
        }
        else
        {
            root = root->left;
            bool ins = insert(JourneyCode,price);
            root = root->parent;
            return ins;
        }
    }
    else if(root->price<price)
    {
        if(root->right == NULL)
        {
            root->right = new TreeNode(JourneyCode, price);
            root->right->parent = root;
            return true;
        }
        else
        {
            root = root->right;
            bool ins = insert(JourneyCode,price);
            root = root->parent;
            return ins;
        }
    }
    if(root->JourneyCode == JourneyCode && root->price == price)
    {
        return false;
    }
}

// Return True, if the ticket with given attributes is found, false otherwise
bool BST::find(int JourneyCode, int price) { 
    if(root->JourneyCode == JourneyCode && root->price == price)
    {
        return true; 
    }
    else
    {
        if(root->price >= price && root->left != NULL)
        {
            root = root->left;
            bool fin = find(JourneyCode, price);
            root = root->parent;
            return fin;
        }
        else if(root->price<price && root->right != NULL)
        {
            root = root->right;
            bool fin = find(JourneyCode, price);
            root = root->parent;
            return fin;
        }
    }
    return false; 
}

struct TreeNode* BST::minimum(struct TreeNode* root){
    if(root->left == NULL)
    {
        return root;
    }
    else
    {
        return minimum(root->left);
    }
}

struct TreeNode* BST::succesor(struct TreeNode* root){
    if(root->right == NULL)
    {
        return NULL;
    }
    else
    {    
        return minimum(root->right);
    }
}
	
// Returns false, if JourneyCode isn't present
// Deletes the corresponding entry and returns True otherwise
bool BST::remove(int JourneyCode, int price) { 
    struct TreeNode *x = new TreeNode(root->JourneyCode,root->price,root->left,root->right,root->parent);
    while(true)
    {
        if(x->price > price && x->left != NULL)
        {
            x = x->left;
            continue;
        }
        else if(x->price < price && x->right != NULL)
        {
            x = x->right;
            continue;
        }
        else if(x->price == price && x->JourneyCode == JourneyCode)
        {
            if(x->left == NULL && x->right == NULL)
            {
                if(x->parent == NULL)
                {
                    delete root;
                }
                else
                {
                    if(x == x->parent->left)
                    {
                        x->parent->left = NULL;
                    }
                    else
                    {
                        x->parent->right = NULL;
                    }
                }
            }
            else if(x->left == NULL )
            {
                if(x->parent == NULL)
                {
                    root = x->right;
                }
                else
                {
                    if(x == x->parent->left)
                    {
                        x->parent->left = x->right;
                        x->right->parent = x->parent;
                    }
                    else
                    {
                        x->parent->right = x->right;
                        x->right->parent = x->parent;
                    }
                }
            }
            else if(x->right == NULL)
            {
                if(x->parent == NULL)
                {
                    root = x->left;
                }
                else
                {
                    if(x == x->parent->left)
                    {
                        x->parent->left = x->left;
                        x->left->parent = x->parent;
                    }
                    else
                    {
                        x->parent->right = x->left;
                        x->left->parent = x->parent;
                    }
                }
            }
            else
            {
                struct TreeNode *suc = new TreeNode(x->right->JourneyCode,x->right->price,x->right->left,x->right->right,x->right->parent);
                while(suc->left != NULL)
                {
                    suc = suc->left;
                }
                if(suc->left == NULL && suc->right == NULL)
                {
                    if(suc->parent == NULL)
                    {
                        delete root;
                    }
                    else
                    {
                        if(suc == suc->parent->left)
                        {
                            suc->parent->left = NULL;
                        }
                        else
                        {
                            suc->parent->right = NULL;
                        }
                    }
                }
                else if(suc->left == NULL )
                {
                    if(suc->parent == NULL)
                    {
                        root = suc->right;
                    }
                    else
                    {
                        if(suc == suc->parent->left)
                        {
                            suc->parent->left = suc->right;
                            suc->right->parent = suc->parent;
                        }
                        else
                        {
                            suc->parent->right = suc->right;
                            suc->right->parent = suc->parent;
                        }
                    }
                }
                else if(suc->right == NULL)
                {
                    if(suc->parent == NULL)
                    {
                        root = suc->left;
                    }
                    else
                    {
                        if(suc == suc->parent->left)
                        {
                            suc->parent->left = suc->left;
                            suc->left->parent = suc->parent;
                        }
                        else
                        {
                            suc->parent->right = suc->left;
                            suc->left->parent = suc->parent;
                        }
                    }
                }
                if(x->parent == NULL)
                {
                    root = suc;
                }
                else
                {
                    if(x == x->parent->left)
                    {
                        x->parent->left->JourneyCode = suc->JourneyCode;
                        x->parent->left->price = suc->price;
                    }
                    else
                    {
                        x->parent->right->JourneyCode = suc->JourneyCode;
                        x->parent->right->price = suc->price;
                    }
                }
            }
            return true;
        }
        else
        {
            return false;
        }
    }
}
	
// Functions that traverse the BST in various ways!
// type is one of PRE_ORDER, POST_ORDER or IN_ORDER
// Print on cout the journey codes at nodes of the BST in the same order as
// they are encountered in the traversal order
// Print one journey code per line

void BST::traverse(int typeOfTraversal) {
    if(typeOfTraversal == 0)
    {
        if(root == NULL)
        {
            return;
        }
        cout<<root->JourneyCode<<endl;
        if(root->left != NULL)
        {
            root = root->left;
            traverse(typeOfTraversal);
            root = root->parent;
        }
        if(root->right != NULL)
        {
            root = root->right;
            traverse(typeOfTraversal);
            root = root->parent;
        }
    }
    else if(typeOfTraversal == 1)
    {
        if(root->left != NULL)
        {
            root = root->left;
            traverse(typeOfTraversal);
            root = root->parent;
        }
        if(root->right != NULL)
        {
            root = root->right;
            traverse(typeOfTraversal);
            root = root->parent;
        }
        cout<<root->JourneyCode<<endl;
    }
    else if(typeOfTraversal == 2)
    {
        if(root->left != NULL)
        {
            root = root->left;
            traverse(typeOfTraversal);
            root = root->parent;
        }
        cout<<root->JourneyCode<<endl;
        if(root->right != NULL)
        {
            root = root->right;
            traverse(typeOfTraversal);
            root = root->parent;
        }
    }
    return; 
}

// Returns the price of the cheapest journey
int BST::getMinimum() {
    if(root->left == NULL)
    {
        return root->price;
    }
    else
    {
        BST root2(root->left);
        return root2.getMinimum();
    }
    return 0;
}

// Part II

// Returns the count of journeys that are at least as expensive
// as lowerPriceBound and at most as expensive as upperPriceBound,
// both bounds included.
int BST::countJourneysInPriceBound(int lowerPriceBound, int upperPriceBound) {
    int count = 0;
    if(root->left != NULL)
    {
        root = root->left;
        count = count + countJourneysInPriceBound(lowerPriceBound, upperPriceBound);
        root = root->parent;
    }
    if(root->price >= lowerPriceBound && root->price <= upperPriceBound)
    {
        count++;
    }
    if(root->right != NULL)
    {
        root = root->right;
        count = count + countJourneysInPriceBound(lowerPriceBound,upperPriceBound);
        root = root->parent;
    }
    return count; 
}

void BST::preorderfile(ofstream &outfile){
    if(root == NULL)
    {
        return;
    }
    outfile<<root->JourneyCode<<" "<<root->price<<endl;
    if(root->left != NULL)
    {
        root = root->left;
        preorderfile(outfile);
        root = root->parent;
    }
    if(root->right != NULL)
    {
        root = root->right;
        preorderfile(outfile);
        root = root->parent;
    }
    return;
}

// Store the current tree in a file called filename.  You should
// store using a scheme that uses no more disk space than that
// required to store all elements in the BST, plus perhaps a small
// constant times the number of elements.  You should also store
// in a manner such that your implementation of customLoad is as
// memory and time efficient as possible.
void BST::customStore(string filename) { 
    ofstream outfile;
    outfile.open(filename);
    preorderfile(outfile);
    outfile.close();
    return;
}

void BST::split (string str, char seperator)  
{  
    in.clear();
    int currIndex = 0, i = 0;  
    int startIndex = 0, endIndex = 0;  
    while (i <= str.length())  
    {  
        if (str[i] == seperator || i == str.length())  
        {  
            endIndex = i;
            in.push_back(str.substr(startIndex,endIndex-startIndex));
            startIndex = endIndex + 1;  
        }  
        i++;  
        }     
}  

void BST::Tree(int journey[],int price[],int &index,int val_journey,int val_price,int max,int min,int num){
    if(index>=num)
    {
        return;
    }
    if(val_price > min && val_price < max)
    {
        root->JourneyCode =  val_journey;
        root->price = val_price;
        index = index + 1;
        root->left = new TreeNode();
        root->left->parent = root;
        root = root->left;
        Tree(journey,price,index,journey[index],price[index],val_price,min,num);
        root = root->parent;
        root->right = new TreeNode();
        root->right->parent = root;
        root = root->right;
        Tree(journey,price,index,journey[index],price[index],max,val_price,num);
        root = root->parent;
        if(root->left->price == 0)
        {
            root->left = NULL;
        }
        if(root->right->price == 0)
        {
            root->right = NULL;
        }
    }
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
    string line;
    int num=0;
    ifstream infile;
    infile.open(filename);
    while(getline(infile,line))
    {
        num++;
    }
    int journey[num];
    int price[num];
    infile.close();
    infile.open(filename);
    int k=0;
    while(getline(infile,line))
    {
        split(line,' ');
        journey[k]=stoi(in[0]);
        price[k]=stoi(in[1]);
        k++;
    }
    infile.close();
    infile.open(filename);
    k=0;
    if(flag == 3)
    {
        int index=0;
        int max = 2147483647;
        int min = -2147483648;
        Tree(journey,price,index,journey[0],price[0],max,min,num);
    }
    else if(flag == 4)
    {
        for(int i=0; i<num; i++)
        {
            if(price[0]>=price[i])
            {
                k++;
            }
            else
            {
                break;
            }
        }
        int index = 1;
        int max = 2147483647;
        int min = -2147483648;
        Tree(journey,price,index,journey[1],price[1],max,min,k);
    }
    infile.close();
    return; 
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

