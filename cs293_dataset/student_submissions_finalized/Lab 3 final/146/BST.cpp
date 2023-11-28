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

BST::BST(){
    root = NULL; //If it is an empty tree the root points to NULL
}

BST::BST(TreeNode *root){
    BST::root = root ; 
}

// Returns false, if given JourneyCode is already present in the BST
// Inserts the element and returns True otherwise
bool BST::insert(int JourneyCode, int price) { 
    
    //First we check if tree is empty in which case we add root with parent pointing to NULL
    if(root == NULL){
        root = new TreeNode;
        root->parent = NULL;
        root->left = NULL;
        root->right = NULL;
        root->price = price;
        root->JourneyCode = JourneyCode;
        return true;
    }
    return insert(JourneyCode,price,root) ;
}

//Constructed in such a way that the root passed here never points to null
bool BST::insert(int JourneyCode, int price, TreeNode *root){
    if(root->JourneyCode == JourneyCode) return false ; //Check if journey code is same 
    
    if(root->price>=price){ 
        if(root->left == NULL){
            root->left = new TreeNode;
            root->left->left = NULL;
            root->left->right = NULL;
            root->left->parent = root;
            root->left->JourneyCode = JourneyCode;
            root->left->price = price ;
            return true;
        }
        return insert(JourneyCode,price,root->left);
    }
    else{
        if(root->right == NULL){
            root->right = new TreeNode;
            root->right->left = NULL;
            root->right->right = NULL;
            root->right->parent = root;
            root->right->JourneyCode = JourneyCode;
            root->right->price = price ;
            return true;
        }
        return insert(JourneyCode,price,root->right);
        
    }
}

// Return True, if the ticket with given attributes is found, false otherwise
bool BST::find(int JourneyCode, int price) { 
    return find(JourneyCode,price,root);
}

bool BST::find(int JourneyCode, int price, TreeNode *root){
    if(root == NULL) return false;
    if(root->JourneyCode == JourneyCode && root->price == price) return true;
    if(root->price >= price) return find(JourneyCode,price,root->left);
    else return find(JourneyCode,price,root->right);
} 
	
// Returns false, if JourneyCode isn't present
// Deletes the corresponding entry and returns True otherwise
bool BST::remove(int JourneyCode, int price) { 
    return remove(JourneyCode,price,root); 
}
	
bool BST::remove(int JourneyCode, int price, TreeNode *root){
    if(root == NULL) return false;
    if (root->JourneyCode == JourneyCode && root->price == price){
        if(root->left == NULL){
            //In this case we can simply remove this root
            if(root->parent==NULL){
                BST::root = root->right;
            }
            else if(root->parent->right == root){
                root->parent->right = root->right;
                if(root->right!=NULL) root->right->parent = root->parent;
            }
            else if(root->parent->left == root){
                root->parent->left = root->right;
                if(root->right!=NULL) root->right->parent = root->parent;
            }
        }
        else {
            if(root->left->right==NULL){
                //Here remove root and add its right to root->left->right
                root->left->right = root->right;
                root->left->parent = root->parent;
                if(root->right!=NULL) root->right->parent = root->left;

                if(root->parent == NULL){
                    BST::root = root->left;
                }
                else if(root->parent->right == root){
                    root->parent->right = root->left;
                }
                else if(root->parent->left == root){
                    root->parent->left = root->left;
                }
            }
            
            //In this case we need to locate the predcessor which is the rightmost node in left branch
            else{
                TreeNode *curr = root->left;
                while(curr->right != NULL){
                    curr = curr->right;
                }
                curr->right = root->right;
                root->left->parent = root->parent;

                if(root->right != NULL) root->right->parent = curr;

                if(root->parent==NULL) {
                    BST::root = root->left;
                }
                else if(root->parent->right == root){
                    root->parent->right = root->left;
                }
                else if(root->parent->left == root){
                    root->parent->left = root->left;
                }
            }
        }
        return true;
    }
    if(root->price >= price) return remove(JourneyCode,price,root->left);
    else return remove(JourneyCode,price,root->right);
}
// Functions that traverse the BST in various ways!
// type is one of PRE_ORDER, POST_ORDER or IN_ORDER
// Print on cout the journey codes at nodes of the BST in the same order as
// they are encountered in the traversal order
// Print one journey code per line

void BST::traverse(int typeOfTraversal) {
    traverse(typeOfTraversal,root);
    return;
}

void BST::traverse(int typeOfTraversal, TreeNode *root){
    if(root == NULL) return ;
    if(typeOfTraversal == 0) cout<<root->JourneyCode<<endl ;
    traverse(typeOfTraversal , root->left);
    if(typeOfTraversal == 2) cout<<root->JourneyCode<<endl ;
    traverse(typeOfTraversal , root->right);
    if(typeOfTraversal == 1) cout<<root->JourneyCode<<endl;
}

// Returns the price of the cheapest journey
int BST::getMinimum() {
    if(root == NULL) return 0;
    TreeNode *curr = root;
    while(curr->left != NULL){
        curr = curr->left; // got to the leftmost node 
    } 
    return curr->price;
}

// Part II

// Returns the count of journeys that are at least as expensive
// as lowerPriceBound and at most as expensive as upperPriceBound,
// both bounds included.
int BST::countJourneysInPriceBound(int lowerPriceBound, int upperPriceBound) {
    int ans = 0;
    countJourneysInPriceBound(lowerPriceBound, upperPriceBound , root , ans);
    return ans;
}

void BST::countJourneysInPriceBound(int &lowerPriceBound, int &upperPriceBound , TreeNode *rooter , int &ans){
    if(rooter!=NULL) {
        if(rooter->price>= lowerPriceBound && rooter->price<=upperPriceBound) ans ++;
        if(rooter->price >= lowerPriceBound ) countJourneysInPriceBound(lowerPriceBound, upperPriceBound , rooter->left , ans);
        if(rooter->price <= upperPriceBound ) countJourneysInPriceBound(lowerPriceBound, upperPriceBound , rooter->right , ans);
    }
}
// Store the current tree in a file called filename.  You should
// store using a scheme that uses no more disk space than that
// required to store all elements in the BST, plus perhaps a small
// constant times the number of elements.  You should also store
// in a manner such that your implementation of customLoad is as
// memory and time efficient as possible.
void BST::customStore(string filename) { 
    ofstream f;
    f.open(filename);
    storeTraverse(root, f);
    f<<"E";
    f.close();
    return; 
}

void BST::storeTraverse(TreeNode *node, ofstream &f){
    if(node == NULL) return;
    f<<"D "<<node->JourneyCode<<" "<<node->price<<" ";
    if(node->left!=NULL){
        f<<"L"<<endl;
    }
    storeTraverse(node->left, f);
    if(node->right!=NULL){
        f<<"R"<<endl;
    }
    storeTraverse(node->right , f);
    f<<"U"<<endl;
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
    ifstream infile;
    root = NULL;
    char c,d;
    int x,y;
    infile.open(filename);
    if(flag==LOAD_FULL_BST){
        infile>>c;
        if(c=='E'){
            infile.close();
            return;
        }
        infile>>x>>y;
        root = new TreeNode;
        root->parent=NULL;
        TreeNode *curr;
        curr = root;
        curr->JourneyCode = x;
        curr->price = y;
        infile>>d;
        
        if(d=='L') {
            curr->left = new TreeNode;
            curr->left->parent = curr;
            curr = curr->left;
        }
        if(d=='R'){
            curr->right = new TreeNode;
            curr->right->parent = curr;
            curr = curr->right;
        }
        if(d == 'U'){
            infile.close();
            return;
        }
        while(true){
            infile>>c;
            if(c=='E') break;
            if(c=='D'){
                infile>>x>>y;
                curr->JourneyCode = x;
                curr->price = y;
                infile>>d;
                if(d=='L') {
                    curr->left = new TreeNode;
                    curr->left->parent = curr;
                    curr = curr->left;
                }
                if(d=='R'){
                    curr->right = new TreeNode;
                    curr->right->parent = curr;
                    curr = curr->right;
                }
                if(d == 'U'){
                    curr = curr->parent;
                }
            }
            if(c=='R'){
                curr->right = new TreeNode;
                curr->right->parent = curr;
                curr = curr->right;
            }
            if(c=='U'){
                curr=curr->parent;
            }
        }
    }
    else if(flag = LOAD_LEFT_SUBTREE){
        infile>>c;
        if(c=='E'){
            infile.close();
            return;
        }
        infile>>x>>y;
        infile>>d;
        if(d!='L'){
            infile.close();
            return;
        }
        infile>>c>>x>>y>>d; 
        root = new TreeNode;
        root->parent = NULL;
        TreeNode *curr;
        curr = root;
        curr->JourneyCode = x;
        curr->price = y;

        if(d=='L') {
            curr->left = new TreeNode;
            curr->left->parent = curr;
            curr = curr->left;
        }
        if(d=='R'){
            curr->right = new TreeNode;
            curr->right->parent = curr;
            curr = curr->right;
        }
        if(d == 'U'){
            infile.close();
            return;
        }

        while(true){
            infile>>c;
            if(c=='E') break;
            if(c=='D'){
                infile>>x>>y;
                curr->JourneyCode = x;
                curr->price = y;
                infile>>d;
                if(d=='L') {
                    curr->left = new TreeNode;
                    curr->left->parent = curr;
                    curr = curr->left;
                }
                if(d=='R'){
                    curr->right = new TreeNode;
                    curr->right->parent = curr;
                    curr = curr->right;
                }
                if(d == 'U'){
                    if(curr->parent == NULL) break;
                    curr = curr->parent;
                }
            }
            if(c=='R'){
                curr->right = new TreeNode;
                curr->right->parent = curr;
                curr = curr->right;
            }
            if(c=='U'){
                if(curr->parent==NULL) break;
                curr=curr->parent;
            }
        }

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
        root = curr;
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
        root = curr;
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

