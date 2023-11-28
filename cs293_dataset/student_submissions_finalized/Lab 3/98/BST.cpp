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

BST::BST()
{ 
    root = new TreeNode();
    root->parent=NULL;
}
BST::BST(TreeNode *root)
{
    this->root = root;
}

// Returns false, if given JourneyCode is already present in the BST
// Inserts the element and returns True otherwise
bool BST::insert(int JourneyCode, int price)
{
    if(find(JourneyCode,price))
    {
        return false;
    }
    if(root->JourneyCode==0 && root->price==0)
    {
        root->JourneyCode=JourneyCode;
        root->price=price;
        return true;
    }
    TreeNode* ptr_parent=NULL;
    TreeNode* ptr=root;
    
    while(ptr!=NULL)
    {
        if(price>ptr->price)
        {  
            ptr_parent=ptr;
            ptr = ptr->right;
            continue;
        }
        else
        {
            ptr_parent=ptr;
            ptr=ptr->left;
            continue;
        }
    }
    if(ptr_parent->price>=price)
    {
        ptr_parent->left=new TreeNode(JourneyCode,price);
        ptr_parent->left->parent=ptr_parent;
    }
    else
    {
        ptr_parent->right= new TreeNode(JourneyCode,price);
        ptr_parent->right->parent=ptr_parent;
    }
    return true;

}

// Return True, if the ticket with given attributes is found, false otherwise
bool BST::find(int JourneyCode, int price)
{   
    TreeNode* ptr = root;
    while (ptr!=NULL)
    {
        if(price==ptr->price)
        {
            if(JourneyCode==ptr->JourneyCode)
            {
                return true;
            }
            else
            {
                ptr=ptr->left;
                continue;
            }
        }
        else if(price>ptr->price)
        {
            ptr = ptr->right;
            continue;
        }
        else
        {
            ptr=ptr->left;
            continue;
        }
    }
    return false;
   
}

TreeNode* BST::get(int JourneyCode,int price)
{
    TreeNode* ptr = root;
    while (ptr!=NULL)
    {
        if(price==ptr->price)
        {
            if(JourneyCode==ptr->JourneyCode)
            {
                return ptr;
            }
            else
            {
                ptr=ptr->left;
                continue;
            }
        }
        else if(price>ptr->price)
        {
            ptr = ptr->right;
            continue;
        }
        else
        {
            ptr=ptr->left;
            continue;
        }
    }
    return NULL;
   
}
	
// Returns false, if JourneyCode isn't present
// Deletes the corresponding entry and returns True otherwise
bool BST::remove(int JourneyCode, int price)
{
    if(!find(JourneyCode,price))
    {
        return false;
    }
    TreeNode* element = get(JourneyCode,price);
    if(element->left==NULL && element->right==NULL)
    {
        if(element==element->parent->left)
        {
            element->parent->left=NULL;
        }
        else
        {
            element->parent->right=NULL;
        }
    }
    else if(element->left==NULL || element->right==NULL)
    {
        if(element->parent==NULL)
        {
            if(element->left==NULL)
            {
                root=element->right;
                element->right->parent=NULL;
            }
            else
            {
                root=element->left;
                element->left->parent=NULL;
            }
            return true;
        }
        if(element->left==NULL)
        {
            if(element==element->parent->left)
        {
            element->parent->left=element->right;
        }
        else
        {
            element->parent->right=element->right;
        }
        }
        else
        {
            if(element==element->parent->left)
        {
            element->parent->left=element->left;
        }
        else
        {
            element->parent->right=element->left;
        }
        }
    }
    if(element->left!=NULL && element->right!=NULL)
    {   
        TreeNode* succ = successor(JourneyCode,price);
        element->JourneyCode=succ->JourneyCode;
        element->price=succ->price;
        succ->parent->left=succ->right;
    }
    return true;

}

TreeNode* BST::successor(int JourneyCode,int price)
{
    TreeNode* element = get(JourneyCode,price);
    if(element->right!=NULL)
    {
        TreeNode* ptr1=element->right;
        TreeNode* ptr1_parent = element;
        while(ptr1!=NULL)
        {
            ptr1_parent = ptr1;
            ptr1=ptr1->left;
        }
        return ptr1_parent;
    }
    else
    {
        TreeNode* ptr = element->parent;
        while (ptr!=NULL && element==ptr->right)
        {
            element=ptr;
            ptr=ptr->parent;
        }
        return ptr;
    }


}
	
// Functions that traverse the BST in various ways!
// type is one of PRE_ORDER, POST_ORDER or IN_ORDER
// Print on cout the journey codes at nodes of the BST in the same order as
// they are encountered in the traversal order
// Print one journey code per line

void BST::traverse(int typeOfTraversal)
{
    if(typeOfTraversal==0)
    {
        preorder(root);
    }
    else if(typeOfTraversal==1)
    {
        postorder(root);

    }
    else if(typeOfTraversal==2)
    {
       inorder(root);
    }
}

void BST::preorder(TreeNode* ptr)
{
    cout<<ptr->JourneyCode<<endl;
        if(ptr->left==NULL)
        {
            return;
        }
        else
        {
            preorder(ptr->left);
        }
        if(ptr->right==NULL)
        {
            return;
        }
        else
        {
            preorder(ptr->right);
        }

}

void BST::postorder(TreeNode* ptr)
{
    if(ptr->left==NULL)
        {
            return;
        }
        else
        {
            postorder(ptr->left);
        }
        if(ptr->right==NULL)
        {
            return;
        }
        else
        {
            postorder(ptr->right);
        }
        cout<<ptr->JourneyCode<<endl;
}

void BST::inorder(TreeNode* ptr)
{
     if(ptr->left==NULL)
        {
            return;
        }
        else
        {
            inorder(ptr->left);
        }
        cout<<ptr->JourneyCode<<endl;
        if(ptr->right==NULL)
        {
            return;
        }
        else
        {
            inorder(ptr->right);
        }
    
}



// Returns the price of the cheapest journey
int BST::getMinimum() 
{
    TreeNode* ptr_parent = NULL;
    TreeNode* ptr = root;
    while(ptr!=NULL)
    {
        ptr_parent=ptr;
        ptr=ptr->left;
    }
    return ptr_parent->price;
}

TreeNode* BST::getroot()
{
    return root;
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
        root=curr;
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

