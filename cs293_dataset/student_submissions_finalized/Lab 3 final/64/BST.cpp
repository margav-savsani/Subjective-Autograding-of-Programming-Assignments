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
    A = new int[5];
}
BST::BST(TreeNode *root1){
    root=root1;
}

// Return True, if the ticket with given attributes is found, false otherwise
bool BST::find(int JourneyCode, int price){
    TreeNode *x = root;


    while(x!=nullptr && x->JourneyCode!=JourneyCode && x->price!=price){
        if(price < x->price){
            x=x->left;
        }else{
            x=x->right;
        }
    }
    if(x==nullptr){
        return false;
    }
    else if(x->JourneyCode==JourneyCode && x->price==price){
        return true;
    }else{
        return false;
    }
}

// Returns false, if given JourneyCode is already present in the BST
// Inserts the element and returns True otherwise
bool BST::insert(int JourneyCode, int price) {
    if(find(JourneyCode, price)==true){
        return false;
    }
    else{
        if(root!=nullptr){
        }
        TreeNode *y=nullptr;
        TreeNode *x=root;
        while(x!=nullptr){
            y=x;
            if(price < x->price){
                x=x->left;
            }else if(price > x->price){
                x=x->right;
            }else{
                return false;
            }
        }
        TreeNode* z = new TreeNode(JourneyCode,price,NULL,NULL,y);
        if(y==nullptr){
            root=z;
            return true;
        }else if(price < y->price){
            y->left=z;
            return true;
        }else if(price > y->price){
            y->right=z;
            return true;
        }else{
            return false;
        }
    }
}


TreeNode* BST::min(TreeNode* x){
    TreeNode *y=x;
    while(y->left!=nullptr){
        y=y->left;
    }
    return y;
}	


TreeNode* BST::successor(TreeNode *x){
    return min(x->right);
}

bool BST::remove(int JourneyCode, int price) {
    if(find(JourneyCode,price)) {
        return false;
    }
    else{
        TreeNode *x = root;
        long int nodes=0;
        while(x!=nullptr){
            if((x->price==price) && (x->JourneyCode==JourneyCode)){
                if((x->left==nullptr) && (x->right==nullptr)){
                    if(nodes==0){
                        root = nullptr;
                    }
                    else if(nodes!=0){
                        TreeNode* y=x->parent;
                        if(y->price >= price){
                            y->left = nullptr;
                            y = nullptr;
                        }
                        else{
                            y->right = nullptr;
                            y = nullptr;
                        }
                    }
                }
                else if((x->left==nullptr) || (x->right==nullptr)){
                    if(nodes==0){
                        if(x->left==nullptr){
                            root = x->right;
                            (x->right)->parent = nullptr;
                            x->right = nullptr;
                        }
                        else{
                            root = x->left;
                            x->left->parent = nullptr;
                            x->left = nullptr;
                        }
                    }
                    else{
                        if(x->left==nullptr){
                            TreeNode* y=x->parent;
                            if(y->price >= x->price){
                                y->left = x->right;
                                (x->right)->parent = x->parent;
                                x = nullptr;
                            }
                            else{
                                y->right = x->right;
                                (x->right)->parent = x->parent;
                                x = nullptr;
                            }
                        }
                        else{
                            TreeNode* y=x->parent;
                            if(y->price >= x->price){
                                y->left = x->left;
                                (x->left)->parent = x->parent;
                                x = nullptr;
                            }
                            else{
                                y->right = x->left;
                                (x->left)->parent = x->parent;
                                x = nullptr;
                            }
                        }
                    }
                }
                else{
                        TreeNode* z=successor(x);
                        if(x->parent == nullptr){
                            TreeNode* temp = z;
                            remove(z->JourneyCode,z->price);
                            root->JourneyCode = temp->JourneyCode;
                            root->price = temp->price;
                            return true;
                        }
                        else{
                            TreeNode* temp = z;
                            remove(z->JourneyCode,z->price);
                            x->JourneyCode = temp->JourneyCode;
                            x->price = temp->price;
                            return true;
                        }
                }
                return true;
            }
            else if(price < x->price){
                nodes++;
                x = x->left;
            }
            else if(price > x->price){
                nodes++;
                x = x->right;
            }
        }
    }
    return false;
}
	
// Functions that traverse the BST in various ways!
// type is one of PRE_ORDER, POST_ORDER or IN_ORDER
// Print on cout the journey codes at nodes of the BST in the same order as
// they are encountered in the traversal order
// Print one journey code per line

void BST::preorder(TreeNode* node){
    if(node==nullptr){
        return;
    }
    cout<<node->JourneyCode<<endl;
    preorder(node->left);
    preorder(node->right);
}

void BST::postorder(TreeNode* node){
    if(node==nullptr){
        return;
    }
    postorder(node->left);
    postorder(node->right);
    cout<<node->JourneyCode<<endl;
}

void BST::inorder(TreeNode* node){
    if(node==nullptr){
        return;
    }
    inorder(node->left);
    cout<<node->JourneyCode<<endl;
    inorder(node->right);
}

void BST::traverse(int typeOfTraversal) {
    if(typeOfTraversal==0){
        preorder(root);
    }else if(typeOfTraversal==1){
        postorder(root);
    }else if(typeOfTraversal==2){
        inorder(root);
    }
}

// Returns the price of the cheapest journey
int BST::getMinimum() {
    TreeNode *x=root;
    while(x->left!=nullptr){
        x=x->left;
    }
    return x->price;; 
}

// Part II
// Returns the count of journeys that are at least as expensive
// as lowerPriceBound and at most as expensive as upperPriceBound,
// both bounds included.
 
int BST::countJourneysInPriceBound(int lowerPriceBound, int upperPriceBound) {
    int count=0;
    if(root->left!=NULL){
        root=root->left;
        count=count+countJourneysInPriceBound(lowerPriceBound, upperPriceBound);
        root=root->parent;
    }
    if(root->price>=lowerPriceBound && root->price<=upperPriceBound){
        count++;
    }
    if(root->right!=NULL){
        root=root->right;
        count=count+countJourneysInPriceBound(lowerPriceBound, upperPriceBound);
        root=root->parent;
    }
    return count;
}

// Store the current tree in a file called filename.  You should
// store using a scheme that uses no more disk space than that
// required to store all elements in the BST, plus perhaps a small
// constant times the number of elements.  You should also store
// in a manner such that your implementation of customLoad is as
// memory and time efficient as possible.

void BST::preorderstore(ofstream &outfile){
    if(root==NULL){
        return;
    }
    outfile<<root->JourneyCode<<" "<<root->price<<endl;
    if(root->left!=NULL){
        root=root->left;
        preorderstore(outfile);
        root=root->parent;
    }
    if(root->right!=NULL){
        root=root->right;
        preorderstore(outfile);
        root=root->parent;
    }
    return;
}
void BST::customStore(string filename) {
    ofstream outfile;
    outfile.open(filename);
    preorderstore(outfile);
    outfile.close();
    ifstream fin("input.txt");
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

vector<string> parse1;
void BST::split (string str, char seperator)  
{  
    parse1.clear();
    int currIndex = 0, i = 0;  
    int startIndex = 0, endIndex = 0;  
    while (i <= str.length())  
    {  
        if (str[i] == seperator || i == str.length())  
        {  
            endIndex = i;
            parse1.push_back(str.substr(startIndex,endIndex-startIndex));
            startIndex = endIndex + 1;  
        }  
        i++;  
        }     
} 

TreeNode* BST::newNode(int price, int JourneyCode)
{
    TreeNode* node = new TreeNode;
    node->JourneyCode = JourneyCode;
    node->price = price;
    node->left = node->right = NULL;
    return node;
}

TreeNode* BST::BuildTree(int preorder2[],int journey_code[], int start, int end)
{
    if (start > end) {
        return NULL;
    }
    TreeNode* node = newNode(preorder2[start], journey_code[start]);
    int i;
    for (i = start; i <= end; i++)
    {
        if (preorder2[i] > node->price) {
            break;
        }
    }
 
    node->left = BuildTree(preorder2,journey_code, start + 1, i - 1);
 
    node->right = BuildTree(preorder2,journey_code, i, end);
 
    return node;
}
 
void BST::customLoad (int flag, string filename){
    string line;
    int number_of_lines=0;
    ifstream infile;
    infile.open(filename);
        if(infile.is_open()){
        while(getline(infile,line)){
            
            number_of_lines++;
        }
        infile.close();
    }
    int preorder1[number_of_lines];
    int journey_codes[number_of_lines];
    infile.open(filename);
        if(infile.is_open()){
            int i=0;
            while(getline(infile,line)){
                
                split(line,' ');
                preorder1[i]=stoi(parse1[1]);
                journey_codes[i]=stoi(parse1[0]);
                i++;
            }
            infile.close();
        }
    int n=number_of_lines;
    if(flag==3){
        root = BuildTree(preorder1, journey_codes, 0, n-1);
    }else if(flag==4){
        if(root==NULL){
            root=NULL;
        }else{
            root=root->left;
        }
    }
}


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
