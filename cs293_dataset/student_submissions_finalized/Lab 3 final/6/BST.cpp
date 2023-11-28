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

BST::BST()
{
    root = new TreeNode;
    root->parent = nullptr;
}
BST::BST(TreeNode *root)
{
    this->root = root;
    this->root->parent = nullptr;

}

// Returns false, if given JourneyCode is already present in the BST
// Inserts the element and returns True otherwise
bool BST::insert(int JourneyCode, int price) 
{ 
    TreeNode* dummy = nullptr;
    TreeNode* start = root;
    if(root->price==0 && root->JourneyCode==0)
    {
        root->price=price;
        root->JourneyCode=JourneyCode;
        return true;
    }
    while(start!=nullptr)
    {
        dummy = start;
        if((start->price)>price)
        start = start->left;
        else
        start = start->right;
    }
    
    /*
    if(dummy==nullptr)
    {
        root = new TreeNode(JourneyCode, price);
        //root->JourneyCode = JourneyCode;
        //root->price = price;
        root->parent = nullptr;
    }
    */
    
    if (price < dummy->price)
    {
        TreeNode* newnode = new TreeNode;
        dummy->left = newnode;
        dummy->left->price = price;
        dummy->left->JourneyCode = JourneyCode;
        (dummy->left->parent) = dummy;
    }
    else
    {
        TreeNode* newnode = new TreeNode;
        dummy->right = newnode;
        dummy->right->price = price;
        dummy->right->JourneyCode = JourneyCode;
        (dummy->right->parent) = dummy;
    }
    return true;
}


// Return True, if the ticket with given attributes is found, false otherwise
bool BST::find(int JourneyCode, int price) 
{ 
    TreeNode* dummy = root;
    while(dummy!=nullptr && price!=dummy->price)
    {
        if(price < dummy->price)
        {
            dummy = dummy->left;
        }
        else
        dummy = dummy->right;
    }
    if(dummy==nullptr)
    return false;
    if(price==dummy->price && JourneyCode==dummy->JourneyCode)
    return true;
    return false;
    
}

TreeNode* BST::find_node(int JourneyCode, int price)
{
    TreeNode* dummy = root;
    while(dummy!=nullptr && (price!=dummy->price && JourneyCode!=dummy->JourneyCode))
    {
        if(price < dummy->price)
        {
            dummy = dummy->left;
        }
        else
        dummy = dummy->right;
    }
    if(dummy==nullptr)
    {
        return nullptr;
    }
    if(price==dummy->price && JourneyCode==dummy->JourneyCode )
    return dummy;
    else
    {
        return nullptr;
    }
}

TreeNode* getMinimumNode(TreeNode* start) 
{
    TreeNode* start_ = start;
    while (start_->left != nullptr) 
    { 
        start_ = start_->left; 
    }
    return start_;
}
	
// Returns false, if JourneyCode isn't present
// Deletes the corresponding entry and returns True otherwise
bool BST::remove(int JourneyCode, int price) 
{
    if(JourneyCode==0 && price==0)
    {
        return false;
    }
    TreeNode* rem = find_node(JourneyCode,price);
    if(rem==nullptr)
    {
        return false;
    }
    if(rem->left == nullptr && rem->right == nullptr)
    {
        if(rem==root)
        {
            rem->price=0;
            rem->JourneyCode=0;
            return true;
        }
        if(rem==rem->parent->left)
        {
            rem->parent->left=nullptr;
            rem->parent=nullptr;
        }
        else
        {
            rem->parent->right=nullptr;
            rem->parent=nullptr;
        }
    }
    else if(rem->left == nullptr)
    {
        
        TreeNode* dummy = rem->right;
        
        if(rem==root)
        {
            root = rem->right;
            root->parent = nullptr;
            rem->right = nullptr;
            return true;
        }
        rem->right = nullptr;
        if(rem==rem->parent->left)
        {
            rem->parent->left = dummy;
        }
        else
        {
            rem->parent->right = dummy;
        }
        dummy->parent = rem->parent;
        rem->parent = nullptr;
        
    }
    else if(rem->right == nullptr)
    {
        TreeNode* dummy = rem->left;
        
        if(rem==root)
        {
            root = rem->left ;
            root->parent = nullptr;
            rem->left = nullptr;
            return true;
        }
        rem->left = nullptr;
        if(rem==rem->parent->left)
        {
            rem->parent->left = dummy;
        }
        else
        {
            rem->parent->right = dummy;
        }
        dummy->parent = rem->parent;
        rem->parent = nullptr;
    }
    else
    {
        TreeNode* min = getMinimumNode(rem->right);
        rem->price = min->price;
        rem->JourneyCode = min->JourneyCode;

        /*
        if(min==min->parent->left)
        {
            min->parent->left=nullptr;
            min->parent=nullptr;
        }
        else
        {
            min->parent->right=nullptr;
            min->parent=nullptr;
        }
        */
       if(min->right == nullptr)
       {
            min->parent->left = nullptr;
            min->parent = nullptr;
       }
       else
       {
            TreeNode* dummy = min->right;
            min->right = nullptr;
            if(min==min->parent->left)
            {
                min->parent->left = dummy;    
            }
            else
            {
                min->parent->right = dummy;
            }
            dummy->parent = min->parent;
            min->parent = nullptr;
        }
    }
    return true; 
}
	
// Functions that traverse the BST in various ways!
// type is one of PRE_ORDER, POST_ORDER or IN_ORDER
// Print on cout the journey codes at nodes of the BST in the same order as
// they are encountered in the traversal order
// Print one journey code per line

void traverse_new(TreeNode* start, int typeOfTraversal)
{
    if(typeOfTraversal==0)
    {
        if (start == nullptr)
        {
            return;
        }
        cout << start->price << " ";
        traverse_new(start->left,0);
        traverse_new(start->right,0);
    return;   
    }
    
    if(typeOfTraversal==1)
    {
        if (start == nullptr)
        {
            return;
        }

        traverse_new(start->left,1);
        traverse_new(start->right,1);
        cout << start->price << " ";
        return;
    }
    

    if(typeOfTraversal==2)
    {
        if (start == nullptr)
        {
            return;
        }

        traverse_new(start->left,2);
        cout << start->price << " ";
        traverse_new(start->right,2);
        return;
    }
    return;
     
}

void BST::traverse(int typeOfTraversal) 
{
    TreeNode* start = root ;
    traverse_new(start, typeOfTraversal);
}

// Returns the price of the cheapest journey
int BST::getMinimum() 
{
    TreeNode* start = root;
    while (start->left != nullptr) 
    { 
        start = start->left; 
    }
    return start->price; 
}

// Part II

// Returns the count of journeys that are at least as expensive
// as lowerPriceBound and at most as expensive as upperPriceBound,
// both bounds included.

int preorder(int lower_bound, int upper_bound, TreeNode* start)
{
    int count = 0;
    if (start == nullptr)
    {
        return 0;
    }
    if(start->price>=lower_bound && start->price<=upper_bound)
    count++;
    count = count + preorder(lower_bound, upper_bound, start->left);
    count = count + preorder(lower_bound, upper_bound, start->right);
    return count;
}

int BST::countJourneysInPriceBound(int lowerPriceBound, int upperPriceBound) 
{
    return preorder(lowerPriceBound,upperPriceBound,root);
}

// Store the current tree in a file called filename.  You should
// store using a scheme that uses no more disk space than that
// required to store all elements in the BST, plus perhaps a small
// constant times the number of elements.  You should also store
// in a manner such that your implementation of customLoad is as
// memory and time efficient as possible.
void pre_order_vectorised(TreeNode* start, vector<int> &list_JC, vector<int> &list_price)
{
    if (start == nullptr)
    {
        return;
    }
    list_JC.push_back(start->JourneyCode);
    list_price.push_back(start->price);
    pre_order_vectorised(start->left,list_JC,list_price);
    pre_order_vectorised(start->right,list_JC,list_price);
}

void BST::customStore(string filename) 
{
    ofstream out;
    out.open(filename);
    vector<int> list_JC;
    vector<int> list_price;
    pre_order_vectorised(root, list_JC, list_price);
    for(int i = 0; i < list_JC.size(); i++)
    {
        out<<list_JC[i];
        out<<list_price[i];
    }
    out.close();
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
 
void BST::customLoad (int flag, string filename) 
{
    ifstream in;
    in.open(filename);
    int JC;
    in>>JC;
    int pri;
    in>>pri;
    TreeNode* current;
    if(flag==3)
    {
        root->price = pri;
        root->JourneyCode = JC;
        current = root;
    }
    if(flag==4)
    {
        int JC;
        in>>JC;
        int pri;
        in>>pri;
        root->price = pri;
        root->JourneyCode = JC;
        current = root;
    }
    bool exit = false;
    while(!in.eof())   
    {
        int JC;
        in>>JC;
        int no;
        in>>no;
        if(exit)
        break;
        if(current->price > no)
        {
            TreeNode* newnode = new TreeNode;
            current->left = newnode;
            newnode->price = no;
            newnode->JourneyCode = JC;
            newnode->parent = current;
            current = newnode;
            continue;
        }
        else
        {
            TreeNode* dummy = current;
            while(true)
            {
                if(dummy->parent == nullptr)
                {
                    TreeNode* newnode = new TreeNode;
                    dummy->right = newnode;
                    newnode->price = no;
                    newnode->JourneyCode = JC;
                    newnode->parent = dummy;
                    current = newnode;
                    break;
                }
                /* 
                if(dummy->parent->price > dummy->price)     // left child condition
                { 
                    dummy = dummy->parent;
                    cout<<"x"<<endl;
                    continue; 
                } 
                */              
                if(dummy->parent->price < dummy->price)     // right child condition
                {
                    dummy = dummy->parent;
                    if(dummy->parent == nullptr && flag==4)
                    {
                        exit = true;
                        break;
                    }
                    continue; 
                }
                

                if(dummy->parent->price < no )      // left child but input number is bigger
                {
                    dummy = dummy->parent;
                    continue;
                }
        
                if(dummy->parent->price > no )
                {
                    TreeNode* newnode = new TreeNode;
                    dummy->right = newnode;
                    newnode->price = no;
                    newnode->JourneyCode = JC;
                    newnode->parent = dummy;
                    current = newnode;
                    break;
                }
            }
        }
    }
    in.close();
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

