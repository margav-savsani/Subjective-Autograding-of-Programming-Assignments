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

BST::BST()      //keeping the nullptr as root
{
    this->root=nullptr;
    N=0;
}
BST::BST(TreeNode *root)        //given node as root
{
    this->root=root;
    N=1; 
}

// Returns false, if given JourneyCode is already present in the BST
// Inserts the element and returns True otherwise
bool BST::insert(int JourneyCode, int price) 
{ 
    if (this->find(JourneyCode,price))
        return false;
    TreeNode *node;         //creating node with given values
    node=new TreeNode(JourneyCode,price);
    node->parent=nullptr;
    TreeNode *sample,*sample2;      //to point next and current node form starting
    sample=new TreeNode;
    sample2=nullptr;            //null pointer
    sample=root;
    while(sample!=nullptr)  //searching for leaf
    {
        sample2=sample;
        if (node->price > sample->price)
            sample=sample->right;
        else
            sample=sample->left;
    }
    node->parent=sample2;       //keeping the node in tree
    N++;
    if (sample2==nullptr)       //in case no node is added 
    {
        root=node;
        return true;
    }
    else if (node->price > sample2->price)  //adding node
    {
        sample2->right=node;
        return true;
    }
    else 
    {
        sample2->left=node;
        return true;
    }
    return false;
}

// Return True, if the ticket with given attributes is found, false otherwise
bool BST::find(int JourneyCode, int price) 
{
    TreeNode *sample=this->root;        //checking from root
    if (sample==nullptr)        //nothing is added
        return false;
    while(sample!=nullptr && price!=sample->price)  //checking for equal price or it will go to nullptr
    {
        if (price > sample->price)
            sample=sample->right;
        else
            sample=sample->left;
    }
    if (sample==nullptr)        //if nullptr return false
        return false;
    if (sample->JourneyCode==JourneyCode)   //if same price then check Journy Code
        return true;
    return false;
}
TreeNode *BST::getnode(int JourneyCode,int price)   //this will return node with same Journy Code and price
{
    if (!find(JourneyCode,price))   //if not present then return nullptr
    {
        return nullptr;
    }
    else
    {       //if present checkmin similar manner as in above function 
        TreeNode *sample=this->root;
        if (sample==nullptr)
            return nullptr;
        while(sample!=nullptr && price!=sample->price)
        {
            if (price > sample->price)
                sample=sample->right;
            else
                sample=sample->left;
        }
        if (sample==nullptr)
            return nullptr;
        if (sample->JourneyCode==JourneyCode)
            return sample;
        return nullptr;
    }
};
// Returns false, if JourneyCode isn't present
// Deletes the corresponding entry and returns True otherwise
TreeNode *BST::getSuccessor(int JourneyCode,int price)
{   //checking for successor that is rigth subtress's min value
    if (!find(JourneyCode,price))
        return nullptr;
    TreeNode *node=this->getnode(JourneyCode,price);
    if (node->right!=nullptr)
    {
        node=node->right;
        while(node->left!=nullptr)
            node=node->left;
        return node;
    }
    TreeNode *sample=node->parent;
    while( sample!=nullptr && node==sample->right )
    {
        node=sample;
        sample=sample->parent;
    }
    return sample;
}
bool BST::remove(int JourneyCode, int price) 
{ 
    if (!find(JourneyCode,price))
        return false;
    TreeNode *node=this->getnode(JourneyCode,price);
    TreeNode *sample1,*sample2;
    if (node->right==nullptr || node->left==nullptr)    //if it is leaf or having one child
        sample1=node;
    else
        sample1=getSuccessor(JourneyCode,price);        //if it has 2 childs
    if (sample1->left==nullptr)         //0 or 1 child
        sample2=sample1->left;
    else
        sample2=sample1->right;
    if (sample2!=nullptr)       
        sample2->parent=sample1->parent;
    if (sample1->parent==nullptr)
        this->root=sample2;
    else if ( sample1=sample1->parent->left)
        sample1->parent->left=sample2;
    else
        sample1->parent->right=sample2;
    if (sample1!=node)
    {
        node->JourneyCode=sample1->JourneyCode;
        node->price=sample1->price;
    }
    N--;
    return true;
}
	
// Functions that traverse the BST in various ways!
// type is one of PRE_ORDER, POST_ORDER or IN_ORDER
// Print on cout the journey codes at nodes of the BST in the same order as
// they are encountered in the traversal order
// Print one journey code per line
void BST::printpreorder(TreeNode *node)
{   //printing preorder
    if (node==nullptr)
        return;
    else
    {       //printing node then left subtree and rigtht subtree
        cout<<node->JourneyCode<<endl;
        printpreorder(node->left);
        printpreorder(node->right);
    }
}
void BST::printpostorder(TreeNode *node)
{   //printing post order
    if (node==nullptr)
        return;
    else
    {   //print left sub tree rigth and node
        printpreorder(node->left);
        printpreorder(node->right);
        cout<<node->JourneyCode<<endl;
    }
}
void BST::printinorder(TreeNode *node)
{   //printing inorder
    if (node==nullptr)
        return;
    else
    {   //print left node and rigth
        printpreorder(node->left);
        cout<<node->JourneyCode<<endl;
        printpreorder(node->right);
    }
}

void BST::traverse(int typeOfTraversal) 
{   //using above 3 fuctions and combine them
    if(typeOfTraversal==0)
        printpreorder(root);
    else if(typeOfTraversal==1)
        printpostorder(root);
    else
        printinorder(root);
    return;
}

// Returns the price of the cheapest journey
int BST::getMinimum() 
{   //min is the left most node in the tree
    TreeNode *min;
    min=root;
    while(min->left!=nullptr)
    {
        min=min->left;
    }
    return min->price;
}

// Part II

// Returns the count of journeys that are at least as expensive
// as lowerPriceBound and at most as expensive as upperPriceBound,
// both bounds included.
int BST::counter(int lp,int up,int &num,TreeNode *node)
{   //making a function to count the required num similar to pre order
    if (node==nullptr)
        return 0;
    else
    {
        if ( node->price <= up && node->price >= lp)
            num++;
        counter(lp,up,num,node->left);
        counter(lp,up,num,node->right);
        return num;
    }
}
int BST::countJourneysInPriceBound(int lowerPriceBound, int upperPriceBound) 
{   //using the below function here 
    if (lowerPriceBound>upperPriceBound)
        return 0;
    int num;
    num=0;  //starting from 0
    int k=counter(lowerPriceBound,upperPriceBound,num,root);
    return k;
}

// Store the current tree in a file called filename.  You should
// store using a scheme that uses no more disk space than that
// required to store all elements in the BST, plus perhaps a small
// constant times the number of elements.  You should also store
// in a manner such that your implementation of customLoad is as
// memory and time efficient as possible.
void BST::customStore(string filename) 
{       //storing the data
    Store(filename,root);
    return;
}
	
void BST::Store(string filename,TreeNode *node)
{   // # is nullptr
    ofstream infile;
    infile.open(filename,std::ios_base::app | std::ios_base::in);
    if (node==nullptr)
    {
        infile<<0<<endl;    //store 0 if nullptr
        infile.close();
        return;
    }
    infile<<node->price;infile<<" ";infile<<node->JourneyCode<<endl;
    infile<<1<<endl;        //store if L
    Store(filename,node->left);
    infile<<-1<<endl;       //store if R
    Store(filename,node->right);
    infile.close();
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
    fstream file;
    file.open(filename);
    TreeNode *node=new TreeNode();
    TreeNode *sample;
    while(!file.eof())
    {
        string line;
        getline(file,line);
        if (line.compare("0")==0)
        {
            sample=sample->parent;
            node=node->parent;
            continue;
        }
        if (line.compare("-1")==0)
        {
            sample=node;
            node=node->left;
            continue;
        }
        if (line.compare("1")==0)
        {
            sample=node;
            node=node->right;
            continue;
        }
        string word[2];
        istringstream ss(line);
        string check;
        for (int i=0;i<2;i++)
            ss >> word[i];
        int num[2];
        cout<<word[0]<<" "<<word[1]<<endl;
        num[0]=stoi(word[0]);
        num[1]=stoi(word[1]);
        node->JourneyCode=num[1];
        node->price=num[0];
        node->parent=sample;
    }

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
}       //by saran 210050036