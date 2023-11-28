#include <algorithm>
#include <cmath>
#include <set>
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

BST::BST(){root = nullptr;}
BST::BST(TreeNode *root){this->root = root;}

// Returns false, if given JourneyCode is already present in the BST
// Inserts the element and returns True otherwise
bool BST::insert(int JourneyCode, int price) 
{
    TreeNode *NEW = new TreeNode(JourneyCode,price);
    TreeNode *ins_l = root;
    TreeNode *ins_r = nullptr;
    
    while(ins_l!=nullptr){
        ins_r = ins_l;
        if(NEW->price < ins_l->price){
            ins_l = ins_l->left;
        }
        else ins_l = ins_l->right;
    }
    if(ins_r==nullptr) root = NEW;
    else if(NEW->price < ins_r->price) ins_r->left=NEW;
    else ins_r->right = NEW;
    return true;
}

// Return True, if the ticket with given attributes is found, false otherwise
bool BST::find(int JourneyCode, int price) 
{
    TreeNode *ins_l = new TreeNode();
    ins_l = root;

    if(ins_l==nullptr) return false;
    if(price > ins_l->price) {
        BST new_tree(ins_l->right);
        return new_tree.find(JourneyCode, price);
    }
    else if(price < ins_l->price) {
        BST new_tree(ins_l->left);
        return new_tree.find(JourneyCode, price);
    }
    else {
        if(JourneyCode==ins_l->JourneyCode) return true;
        BST new_tree(ins_l->right);
        return new_tree.find(JourneyCode, price);
    }
}
    
// Returns false, if JourneyCode isn't present
// Deletes the corresponding entry and returns True otherwise
bool BST::remove(int JourneyCode, int price) 
{
    if(find(JourneyCode,price)==0) return false;
    else
    {
        //finding node for given journeycode and price
        TreeNode *z = root;
        TreeNode *ab = new TreeNode();
        while(z->JourneyCode != JourneyCode && z != nullptr){
            if(price > z->price) z=z->right;
            else if (price < z->price) z=z->left;
            else break;
        }

        // deletes the node
        TreeNode *new_x = new TreeNode();
        TreeNode *new_y = new TreeNode();
        if(z->right == nullptr || z->left == nullptr) new_y = z;
        else new_y = sucessor(z);
        if(new_y->left != nullptr){
            new_x = new_y->left;
        }
        else new_x = new_y->right;
        if(new_x != nullptr){
            new_x->parent = new_y->parent;
        }
        if(new_y->parent == nullptr){
            root = new_x;
        }
        else if(new_y == new_y->parent->left){
            new_y->parent->left = new_x;
        }
        else new_y->parent->right = new_x;
        if(z!=new_y){
            z->JourneyCode = new_y->JourneyCode; z->price = new_y->price;
        }
        return true;
    }
}


//finding minimum node in the whole tree
struct TreeNode *BST::minimum(TreeNode *v){
    TreeNode *ins_l;
    ins_l = v;
    while(ins_l->left!=nullptr){
        ins_l = ins_l->left;
    }
    return ins_l;
}

//finding sucessor in the tree
struct TreeNode *BST::sucessor(TreeNode *v){
    TreeNode *min_2 = new TreeNode();
    if(v->right != nullptr) return minimum(v->right);
    min_2 = v->parent;
    while(min_2!=nullptr && min_2->right == v){
        v = min_2; 
        min_2 = min_2->parent; 
    }
    return min_2;
}

// Functions that traverse the BST in various ways!
// type is one of PRE_ORDER, POST_ORDER or IN_ORDER
// Print on cout the journey codes at nodes of the BST in the same order as
// they are encountered in the traversal order
// Print one journey code per line

void preorder(TreeNode *v)
{
    if(v!=nullptr){
        cout << v->JourneyCode << " ";
        preorder(v->left);
        preorder(v->right);
    }
}
void postorder(TreeNode *v)
{
    if(v!=nullptr){
        postorder(v->left);
        postorder(v->right);
        cout << v->JourneyCode << " ";
    }
}
void inorder(TreeNode *v)
{
    if(v!=nullptr){
        inorder(v->left);
        cout << v->JourneyCode << " ";
        inorder(v->right);
    }
}

void BST::traverse(int typeOfTraversal) 
{
    if(typeOfTraversal==0){
        preorder(root);
        cout << endl;
    }
    if(typeOfTraversal==1){
        postorder(root);
        cout << endl;
    }
    if(typeOfTraversal==2){
        inorder(root);
        cout << endl;
    }
    return; 
}

// Returns the price of the cheapest journey
int BST::getMinimum()
{
    TreeNode *get_min;
    get_min = root;
    while(get_min->left!=nullptr){
        get_min = get_min->left;
    }
    return get_min->price;
}

//PART II
// Returns the count of journeys that are at least as expensive
// as lowerPriceBound and at most as expensive as upperPriceBound,
// both bounds included.

//strong traverse in this and then using this output vector for the result
vector<int> get_inorder(TreeNode *v)
{
    vector<int> vec;
    if(v!=nullptr){
        inorder(v->left);
        vec.push_back(v->JourneyCode);
        inorder(v->right);
    }
    return vec;
}

// here used the vectors to get the part between lowerpricebound and upperpricebound
int BST::countJourneysInPriceBound(int lowerPriceBound, int upperPriceBound) 
{
    int count=0;
    TreeNode *cjipb = new TreeNode();
    cjipb = root;
    vector<int> vect;
    vect = get_inorder(cjipb);
    for(int i=0; i<vect.size(); i++){
        if(vect[i]>=lowerPriceBound && vect[i]<=upperPriceBound) count += 1;
    }
    return count; 
}

// Store the current tree in a file called filename.  You should
// store using a scheme that uses no more disk space than that
// required to store all elements in the BST, plus perhaps a small
// constant times the number of elements.  You should also store
// in a manner such that your implementation of customLoad is as
// memory and time efficient as possible.

//defined new function for the recursion and uses this to store the tree
void store(TreeNode *v, FILE *f){
    if(v==nullptr){
        fprintf(f, "%d, %d\n", -1, -1);
        return;
    }
    fprintf(f, "%d, %d\n", v->price, v->JourneyCode);
    store(v->left, f);
    store(v->right, f);
}

void BST::customStore(string filename) 
{
    char p[filename.length()];
    for (int i = 0; i < sizeof(p); i++) p[i] = filename[i];

    TreeNode *st = new TreeNode();
    st = root;

    FILE *fptr = fopen(p,"w");
    if (fptr == NULL) {
        cout << "Can't open\n"; exit(0);
    }
    else store(st,fptr);
    fclose(fptr);
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

//defined new funciton for getting the tree from the file
void destore(TreeNode *&root, FILE *fp)
{
    int pr,Jc;
    if ( !fscanf(fp, "%d, %d\n", &pr, &Jc) || (pr == -1 && Jc == -1))
       return;
    root = new TreeNode(pr,Jc);
    destore(root->left, fp);
    destore(root->right, fp);
}

void BST::customLoad (int flag, string filename) 
{
    if(flag==LOAD_FULL_BST){
        char q[filename.length()];
        for (int i = 0; i < sizeof(q); i++) q[i] = filename[i];

        TreeNode *load = new TreeNode();
        load = root;

        FILE *fpt = fopen(q,"r");
        if (fpt == NULL) {
            cout << "Can't open\n"; exit(0);
        }
        else destore(load,fpt);
        return;
    }
    if(flag==LOAD_LEFT_SUBTREE){
        char q[filename.length()];
        for (int i = 0; i < sizeof(q); i++) q[i] = filename[i];

        TreeNode *load = new TreeNode();
        load = root;

        FILE *fpt = fopen(q,"r");
        if (fpt == NULL) {
            cout << "Can't open\n"; exit(0);
        }
        else destore(load->left,fpt);
        return;
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
}