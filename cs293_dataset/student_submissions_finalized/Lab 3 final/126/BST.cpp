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
    root=nullptr;
 }
BST::BST(TreeNode *root){
    this->root=root;
}

// Returns false, if given JourneyCode is already present in the BST
// Inserts the element and returns True otherwise



bool BST::insert(int JourneyCode, int price) { 
    TreeNode *ins=new TreeNode;
    ins->JourneyCode=JourneyCode;
    ins->price=price;
    ins->left=nullptr;
    ins->right=nullptr;
    TreeNode *y=nullptr; 
    TreeNode *x=root;
    while(x!=nullptr){
        y=x;
        if(JourneyCode==x->JourneyCode)
            return false;
        else if(price<(x->price)){
            x=x->left;
        }  
        else{
            x=x->right;
        }
    }
    ins->parent=y;
    if(y==nullptr){
        root=ins;
    }
    //instead of the following 4 lines, x=ins should work
    else if((y->price)>price)
        y->left=ins;
    else
        y->right=ins;
    return true;
  }
// Return True, if the ticket with given attributes is found, false otherwise
bool BST::find(int JourneyCode, int price) { 
    TreeNode *x=root;
    while(x!=nullptr){
        if((x->JourneyCode==JourneyCode)&&(x->price==price)){
            return true;
        }
        else if(x->price>price){
            x=x->left;
        }
        else{
            x=x->right;
        }
    }
    return false;
}
	
// Returns false, if JourneyCode isn't present
// Deletes the corresponding entry and returns True otherwise
bool BST::remove(int JourneyCode, int price) {
    TreeNode *t=root;
    while(t!=nullptr){
        if((t->JourneyCode==JourneyCode)&&(t->price==price)){
            break;
        }
        else if(t->price>price){
            t=t->left;
        }
        else{
            t=t->right;
        }
    }
    if(t==nullptr){
        return false;
    }
    else{
        //case1, t has 0 children
        if(t->left==nullptr&&t->right==nullptr){
            if(t->parent!=nullptr){
                if(t->parent->left==t){
                    t->parent->left=nullptr;
                }
                else{
                    t->parent->right=nullptr;
                }
            }
            else{
                root=nullptr;
            }
        }
        //case2, t has 1 child
        else if(t->left==nullptr){
            if(t->parent!=nullptr){
                if(t->parent->left==t){
                    t->parent->left=t->right;
                    t->right->parent=t->parent;
                    t=nullptr;
                }
                else{
                    t->parent->right=t->right;
                    t->right->parent=t->parent;
                    t=nullptr;
                }
            }
            else{
                root=t->right;
                root->parent=nullptr;
            }
        }
        else if(t->right==nullptr){
            if(t->parent!=nullptr){
                if(t->parent->left==t){
                    t->parent->left=t->left;
                    t->left->parent=t->parent;
                    t=nullptr;
                }
                else{
                    t->parent->right=t->left;
                    t->left->parent=t->parent;
                    t=nullptr;
                }
            }
            else{
                root=t->left;
                root->parent=nullptr;
            }
        }
        else{
            //finding the successor
            TreeNode *temp=t->right;
            while(temp->left!=nullptr){
                temp=temp->left;
            }
            
            if(temp->right==nullptr){
                t->JourneyCode=temp->JourneyCode;
                t->price=temp->price;
                if(temp->parent->left==temp){
                    temp->parent->left=nullptr;
                }
                else{
                    temp->parent->right=nullptr;
                }
            }
            else{
                if(temp->parent->left==temp){
                    temp->parent->left=temp->right;
                    temp->right->parent=temp->parent;
                }
                else{
                    temp->parent->right=temp->right;
                    temp->right->parent=temp->parent;
                }
                t->JourneyCode=temp->JourneyCode;
                t->price=temp->price;
                temp=nullptr;
            }
        }
    }
    return true;
}

void BST::pre(TreeNode* n){
    if(n==nullptr){
        return;
    }
    else{
        cout<<n->JourneyCode;
        pre(n->left);
        pre(n->right);
        return;
    }
}
void BST::post(TreeNode* n){
    if(n==nullptr){
        return;
    }
    else{
        post(n->left);
        post(n->right);
        cout<<n->JourneyCode;
        return;
    }
}
void BST::inord(TreeNode* n){
    if(n==nullptr){
        return;
    }
    else{
        inord(n->left);
        cout<<n->JourneyCode;
        inord(n->right);
        return;
    }
}

void BST::pre1(TreeNode *n, ostream& outfile){//function for printing the tree using sentinels
    if(n==nullptr){
        return;
    }
    else{
        if(n->left==nullptr&&n->right==nullptr){
            outfile<<n->price<<" "<<n->JourneyCode<<" ";//If a leaf, simply print the price and the journey code
        }
        else{
            outfile<<n->price<<" "<<n->JourneyCode<<" "<<-1<<" ";//left sentinel is -1. If we encounter this, we know that the entries following are children of the current node
            pre1(n->left, outfile);
            pre1(n->right, outfile);
            outfile<<-2<<" ";//right sentinel is -2. If we encounter this, we know that the entries that follow are the children of the first ancestor that is not the parent
        }
        return;
        
    }
}
int BST::count(TreeNode *n, int low, int up){//counts the number of journeys within price range
    if (n==nullptr){
        return 0;
    }
    if(n->price>up){
        return count(n->left, low, up);//if the price is greater than the upper limit, ignore the right subtree
    }
    else if(n->price<low){
        return count(n->right, low, up);//if the price is lower than the lower limit, ignore the left subtree
    }
    else{
        return (count(n->left, low, up)+count(n->right, low, up)+1);
    }
}
	
// Functions that traverse the BST in various ways!
// type is one of PRE_ORDER, POST_ORDER or IN_ORDER
// Print on cout the journey codes at nodes of the BST in the same order as
// they are encountered in the traversal order
// Print one journey code per line

void BST::traverse(int typeOfTraversal) {
    if(typeOfTraversal==0){
        pre(root);
    }
    else if(typeOfTraversal==1){
        post(root);
    }
    else if(typeOfTraversal==2){
        inord(root);
    }
 }

// Returns the price of the cheapest journey
int BST::getMinimum() {
    TreeNode *x=root;
    while(x->left!=nullptr){//The minimum node is the leftmost node
        x=x->left;
    }
    return x->price;
}

// Part II

// Returns the count of journeys that are at least as expensive
// as lowerPriceBound and at most as expensive as upperPriceBound,
// both bounds included.
int BST::countJourneysInPriceBound(int lowerPriceBound, int upperPriceBound) {
    return count(root, lowerPriceBound, upperPriceBound); 
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
    pre1(root, outfile);//Use pre order traversal to print the tree using sentinels
    outfile<<" -3";
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
    fstream infile(filename);
        TreeNode *first=new TreeNode;
        root= first;
        int c;
        infile>>c;
        root->price=c;
        int d;
        infile>>d;
        root->JourneyCode=d;
        TreeNode *curr=new TreeNode;
        curr=root;//store the root
        if(flag==4){//if 4, store the root as the left child of the previous root and load the tree. Return when we reach the root back so that we are as efficient as possible (here we use the fact that the left subtree is always printed before the right)
            bool truth=false;//To check if the node following the new root is indeed a part of the left subtree, or if the left subtree is simply a single root
            TreeNode *first1=new TreeNode;
            root=first1;
            int o;
            infile>>o;
            if(o==-1){//If the next entry is a left sentinel, there is hope for a left subtree
                int l;
                infile>>l;
                if(l>c){
                    cout<<"No left subtree";//If the next entry has a greater price, all hope is lost
                    return;
                }
                else{//We have a left subtree! Let's get its JourneyCode and set current to the root of the left subtree
                    int k;
                    infile>>k;
                    first1->price=l;
                    first1->JourneyCode=k;
                    curr=first1;
                }
            }
            else{//If the entry after the new root were a -2 or another price, the tree would have no left subtree
                cout<<"No left subtree";
                return;
            }
            int x;
            infile>>x;
            if(x==-1){//Check the next input, if it is -1 we know that there will be more entries in the left subtree, else our left subtree is just a single node and we must end(with a -3)
                truth=true;
            }
            else {
                root=curr;
                return;
            }
            while(infile){
                TreeNode *temp=new TreeNode;
                int k;
                if(truth){//If truth was true, we know our input was -1, so for the first iteration we will use that and set truth to false so that the remaining iterations run normally
                    k=-1;
                    truth=false;
                }
                else{
                    infile>>k;
                }
                if(k==-3){//End of file
                    return;
                }
                if(k==-1){
                    int t, r;
                    infile>>t;
                    infile>>r;
                    temp->price=t;
                    temp->JourneyCode=r;
                    if(t<c){//If the sentinel is a left sentinel and the price of the node that follows is less than the price of its parent, set the left child of the curr (parent) to temp, set temp's parent to curr and update the price)
                        curr->left=temp;
                        temp->parent=curr;
                    }
                    else{// Else, do the same for the right
                        curr->right=temp;
                        temp->parent=curr;
                    }
                    c=t;
                    curr=temp;
                }
                else if(k==-2){//If the sentinel is a right sentinel, we must move to the parent as we have exhausted the parent's nodes, we are now prepared for the following case.
                    curr=curr->parent;
                }
                else{//The next entry is not a sentinel! This means the entry is the right child of the parent
/* In some sense it is as follows

     3
    / \
   1   4

Will be represented as

3 -1 1 4 -2 -3

4 followed 1 without a sentinel, which meant when we were at 1, we knew 4 was the child of 1's parent, 3.

Another case is as follows

     5
    / \
   3   6
  / 
 2

Will be represented as

5 -1 3 -1 2 -2 6 -2 -3

3 was followed by a -1 as expected, however 2 was followed by a -2, which meant we had to go back up to 3, and -2 was followed by no sentinel, which meant 6 was the right child of 3's parent

*/
                    int r;
                    infile>>r;
                    temp->price=k;
                    temp->JourneyCode=r;
                    curr->parent->right=temp;
                    temp->parent=curr->parent;
                    c=k;
                    curr=temp;
                }
                if(curr==first1){
                    break;
                }
            }
        }
        else{
            while(!infile.eof()){
                TreeNode *temp=new TreeNode;
                int k;
                infile>>k;
                if(k==-3){
                    return;
                }
                if(k==-1){
                    int t, r;
                    infile>>t;
                    infile>>r;
                    temp->price=t;
                    temp->JourneyCode=r;
                    if(t<c){
                        curr->left=temp;
                        temp->parent=curr;
                    }
                    else{
                        curr->right=temp;
                        temp->parent=curr;
                    }
                    c=t;
                    curr=temp;
                }
                else if(k==-2){
                    curr=curr->parent;
                }
                else{
                    int r;
                    infile>>r;
                    temp->price=k;
                    temp->JourneyCode=r;
                    curr->parent->right=temp;
                    temp->parent=curr->parent;
                    c=k;
                    curr=temp;
                }
                if(curr==root){
                    break;
                }
            }
        }
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
        result.push_back(to_string(root->JourneyCode) + "\n");
        TreeNode *curr = root;
        root = root->left;
        // enter the next tree level - left and right branch
        getBST( prefix + (isLeft ? "│   " : "    "), true);
        root=curr;
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

