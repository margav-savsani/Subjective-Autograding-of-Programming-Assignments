#include <bits/stdc++.h>
#include <iostream>
#include <vector>
#include <string>
#include <climits>

using namespace std;

#include "BST.h"

#define PRE_ORDER 0
#define POST_ORDER 1
#define IN_ORDER 2
#define LOAD_FULL_BST 3
#define LOAD_LEFT_SUBTREE 4


// PLEASE FILL IN THE BODIES OF THE FOLLOWING FUNCTIONS

BST::BST(){
    root = nullptr;
}
BST::BST(TreeNode *n){
    root = n;
    root->parent = nullptr;
}

// Returns false, if given JourneyCode is already present in the BST
// Inserts the element and returns True otherwise
bool BST::insert(int J, int p) {
    if(find(J, p)==1) return 0;
    TreeNode* node = new TreeNode(J, p);
    if (root == nullptr){
        root =node;
        root->parent = nullptr;
        return 1;
    }
    TreeNode* n = root;
    bool i = 0;
    while (i == 0){
        if(n->price<node->price){
            if (n->left == nullptr){
                n->left = node;
                node->parent = n;
                return 1;
            }
            else n = n->left;
        }
        else{
            if (n->right == nullptr){
                n->right = node;
                node->parent = n;
                return 1;
            }
            else n = n->right;
        }
    }
    return i;
}
    
// Return True, if the ticket with given attributes is found, false otherwise
bool BST::find(int J, int p){
   TreeNode* node = new TreeNode(J, p);
    if (root == nullptr) return 0;
    TreeNode * n = root;
    bool found = 0;
    while (n!=nullptr){
        if (n->price==p && n->JourneyCode==J){
            found=1;
            return true;
        }
        if (n->price < node->price){
            n= n->left;
        }
        else if (n->price >node->price){
            n = n->right;
        }
    }
    return found;
    //cout << "started find for " << price << endl;
}

TreeNode * BST::get_Minimum(TreeNode * n){
    if (n == nullptr) return nullptr;
    while (n->left != nullptr) n = n->left;
    return n;
}

TreeNode * BST::get_Successor(TreeNode * n){
    //cout << "successor\n";
    if (n == nullptr) return nullptr;
    if (n->right != nullptr) return get_Minimum(n->right);
    else{
        TreeNode* par = n->parent;
        if (n == par->left) return par;
        while (par != nullptr && n== par->right){
            n = par;
            par = par->parent;
        }
        return par;
    }
}
	
// Returns false, if JourneyCode isn't present
// Deletes the corresponding entry and returns True otherwise
bool BST::remove(int J, int p){
    if (find(J, p)==0) return 0;
    TreeNode * del = new TreeNode(J, p);
    TreeNode * n = root;
    TreeNode *par = nullptr;
    bool a= 0;
    while (a == 0){
        if (n->price==p && n->JourneyCode==J){
            // 3 cases ---- return 1 at the end
            //if (spot == nullptr) return 0;
            // when spot is a leaf
            if (n->left == nullptr && n->right == nullptr){
                //cout << "issame, leaf\n";
                if (n== root) {root = nullptr; return 1;}
                if (n == par->left) par->left = nullptr;
                else par->right = nullptr;
            }
            // when the spot has one child
            else if (n->left != nullptr && n->right == nullptr){
                //cout << "issame, leftonly\n";
                if (n == root) {root = n->left; return 1;}
                if (n == par->left) par->left = n->left;
                else par->right = n->left;
            }
            else if (n->left == nullptr && n->right != nullptr){
                //cout << "issame, rightonly\n";
                if (n == root) {root = n->right; return 1;}
                if (n== par->left) par->left =n->right;
                else par->right = n->right;
            }
            //when the spot has two children
            else{
                //cout << "issame, two\n";
                TreeNode* s = get_Successor(n);
                remove(s->JourneyCode, s->price);
                if (n== root) {root = s; s->left = n->left; s->right = n->right; return 1;}
                if (n == par->left) par->left = s;
                else par->right = s;
                s->left = n->left;
                s->right = n->right;
            }
            return 1;
        }
        if (n->price <del->price){
            //cout << "checkright\n";
            par = n;
            n = n->left;
        }
        else if (n->price > del->price){
            //cout << "checkleft\n";
            par = n;
            n= n->right;
        }
    }
    return a;
}

void BST::Pre_order(TreeNode * n){
    if (n== nullptr) return;
    cout << n->JourneyCode << endl;
    Pre_order(n->left);
    Pre_order(n->right);
}

void BST::In_order(TreeNode * n){
    if (n== nullptr) return;
    In_order(n->left);
    cout << n->JourneyCode << endl;
    In_order(n->right);
}

void BST::Post_order(TreeNode * n){
    if (n == nullptr) return;
    Post_order(n->left);
    Post_order(n->right);
    cout << n->JourneyCode << endl;
}

void BST::traverse(int typeOfTraversal){
    if (typeOfTraversal == 0) Pre_order(root);
    else if (typeOfTraversal == 1) Post_order(root);
    else if (typeOfTraversal == 2) In_order(root);
    return; 
}

// Returns the price of the cheapest journey
int BST::getMinimum(){
    if (get_Minimum(root) == nullptr) return INT_MAX;
    else return get_Minimum(root)->price;
}

// Part II

// Returns the count of journeys that are at least as expensive
// as lowerPriceBound and at most as expensive as upperPriceBound,
// both bounds included.
int number_of_nodes(TreeNode *n,int lower,int upper){
    if (n->price>upper){
       int final_count=0;
       if(n->left!=nullptr) final_count+=number_of_nodes(n->left,lower,upper);
       return final_count;
    }
    else if(n->price<lower){
        int final_count=0;
        if(n->right!=nullptr) final_count+=number_of_nodes(n->right,lower,upper);
        return final_count;
    }
    else{
        int final_count=1;
        if(n->right!=nullptr) final_count+=number_of_nodes(n->right,lower,upper);
        if(n->left!=nullptr) final_count+=number_of_nodes(n->left,lower,upper);
        return final_count;
    }  
}

int BST::countJourneysInPriceBound(int lowerPriceBound, int upperPriceBound) {
    TreeNode* n=root;
    if(n==nullptr) return 0;
    else return number_of_nodes(n,lowerPriceBound,upperPriceBound);
}

// Store the current tree in a file called filename.  You should
// store using a scheme that uses no more disk space than that
// required to store all elements in the BST, plus perhaps a small
// constant times the number of elements.  You should also store
// in a manner such that your implementation of customLoad is as
// memory and time efficient as possible.

void new_preorder(ofstream &f,TreeNode* N){
    TreeNode* par=N->parent;
    if(par!=nullptr){
        if(par->left==N){
            if(par->right==nullptr){
                f<<-4;
            }
            else{
                f<<-1;
            }
        }
        else{
            f<<-3;
        }
    }
    f<<" ";
    f<<N->JourneyCode;
    f<<" ";
    f<<N->price<<endl;
    if((N->left==nullptr)&&(N->right==nullptr)){
        f<<-2;
    }
    if(N->left!=nullptr) new_preorder(f,N->left);
    if(N->right!=nullptr) new_preorder(f,N->right);
    return;
}   

void BST::customStore(string f_name) { 
    ofstream o;
    TreeNode* n=root;
    o.open(f_name);
    new_preorder(o,n);
    o.close();
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
 
void BST::customLoad (int l, string f_name) { 
    ifstream i;
    i.open(f_name);
    TreeNode* n=new TreeNode;
    vector<TreeNode*> v;
    v.push_back(nullptr);
    i>>n->JourneyCode;
    i>>n->price; 
    root=n;
    int value;   
    while(i>>value){
        if(value==-4){
            int Code,Price;
            i>>Code>>Price;
            TreeNode* new_node=new TreeNode(Code,Price,nullptr,nullptr,n);
            n->left=new_node;
            v.push_back(n);
            n=n->left;
        }
        if(value==-1){
            int Price,Code;
            i>>Code>>Price;
            TreeNode* another_node=new TreeNode(Code,Price,nullptr,nullptr,n);
            n->left=another_node;
            n=n->left;
        }
        if(value==-3){
            int Code,Price;
            i>>Code>>Price;
            TreeNode *new_node=new TreeNode(Code,Price,nullptr,nullptr,n);
            n->right=new_node;
            n=n->right;
        }
        if(value==-2){
            n=n->parent;
        }
        while((n->right!=nullptr)||(v[v.size()-1]==n)){
            if(v[v.size()-1]==n){
                v.pop_back();
            }
            n=n->parent;
            if(n==nullptr) break;
        }
    }
    i.close();
    if(l==4) {
        root=root->left;
        root->parent=nullptr;
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
int main(){
   BST a;
   a.insert(200,2);
   
}