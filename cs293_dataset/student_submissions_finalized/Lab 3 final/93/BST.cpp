#include <bits/stdc++.h>
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
// #include <stack> //need to add implementation later

using namespace std;

#include "BST.h"

#define PRE_ORDER 0
#define POST_ORDER 1
#define IN_ORDER 2
#define LOAD_FULL_BST 3
#define LOAD_LEFT_SUBTREE 4
template <typename T>
class StackNode{
//element of my_stack
public:
    T val;
    StackNode<T>* next;
    StackNode(T t, StackNode<T>* ptr):val{t},next{ptr}{}
};
template <typename T>
class my_stack{
//stack implemented as a linked list
    StackNode<T>* head = NULL;
public:
    bool empty(){ //returns if the stack is empty
        return (head!=NULL);
    }
    void push(T ptr){//adds an element to the top of the stack
        StackNode<T> *temp = head;
        head = new StackNode<T>{ptr, temp};
    }
    void pop(){ //removes the last added element from the stack
        StackNode<T>* temp = head;
        if(head==NULL) throw "Pop called on empty stack";
        head = head->next;
        delete temp;
    }
    T top(){//returns the value of the most recently added element of the stack
        if(head==NULL) throw "Pop called on empty stack";
        return head->val;
    }
};

// PLEASE FILL IN THE BODIES OF THE FOLLOWING FUNCTIONS

BST::BST(){
    root = NULL;
}
BST::BST(TreeNode *root){
    this->root = root;
}

// Returns false, if given JourneyCode is already present in the BST
// Inserts the element and returns True otherwise
bool BST::insert(int JourneyCode, int price) { 
    if(root==NULL){
        root = new TreeNode(JourneyCode, price, NULL, NULL, NULL);
        return true;
    }
    if(root->is_present_in_subtree(JourneyCode)) return false;
    root->insert_in_subtree(JourneyCode, price);
    return true;
}

// Return True, if the ticket with given attributes is found, false otherwise
bool BST::find(int JourneyCode, int price) { 
    if(root->find_in_subtree(JourneyCode, price)) return true;
    return false;
}
	
// Returns false, if JourneyCode isn't present
// Deletes the corresponding entry and returns True otherwise
bool BST::remove(int JourneyCode, int price) {
    TreeNode* t = root->find_in_subtree(JourneyCode, price);
    if(!t) return false;
    if(t!=root) t->delete_root();
    if(t==root){
        t = t->delete_root();
        if(t)
            root = t;
    }
    return true;
}
	
// Functions that traverse the BST in various ways!
// type is one of PRE_ORDER, POST_ORDER or IN_ORDER
// Print on cout the journey codes at nodes of the BST in the same order as
// they are encountered in the traversal order
// Print one journey code per line

void BST::traverse(int typeOfTraversal) {
    //if argument is 0, prints the pre order traversal
    //if argument is 2, print the inorder traversal
    //if argument is 1, print the post order traversal
    if(typeOfTraversal==0) root->print_pre_order_of_subtree();
    else if(typeOfTraversal==2) root->print_in_order_of_subtree();
    else if(typeOfTraversal==1) root->print_post_order_of_subtree();
    else cout<<"invalid argument"<<endl;
}

// Returns the price of the cheapest journey
int BST::getMinimum() {
    return root->get_min_in_subtree()->price;
}

// Part II

// Returns the count of journeys that are at least as expensive
// as lowerPriceBound and at most as expensive as upperPriceBound,
// both bounds included.
int BST::countJourneysInPriceBound(int lowerPriceBound, int upperPriceBound) {
    return root->countJourneysinPriceBoundinSubtree(lowerPriceBound, upperPriceBound);
}

// Store the current tree in a file called filename.  You should
// store using a scheme that uses no more disk space than that
// required to store all elements in the BST, plus perhaps a small
// constant times the number of elements.  You should also store
// in a manner such that your implementation of customLoad is as
// memory and time efficient as possible.
void BST::customStore(string filename) { 
    ofstream f{filename};
    root->customStoreSubTree(f);
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
    ifstream f{filename};
    my_stack<TreeNode*> S; //stack holds pointers to the nodes in which only the left ptr has been assigned to
    int data{0};
    TreeNode* prev{NULL};
    bool isFirstNode{1};
    if(flag==LOAD_LEFT_SUBTREE){
        //ignore the data of the root
        f>>data;
        if(data!=-2){
            f>>data;
            f>>data;
        }
        else return;
    }
    while(f>>data){
        if(data == -1){
            S.push(prev);
            int price, JourneyCode;
            f>>price;
            if(price == -2){
                prev->left = NULL;
            }
            else{
                f>>JourneyCode;
                prev->left = new TreeNode{JourneyCode, price, NULL, NULL, prev};
                prev = prev->left;
            }
            continue;
        }
        if(isFirstNode){
            if(data == -2){
                root = NULL;
                break;
            }
            isFirstNode = 0;
            int jcode;
            f>>jcode;
            root = new TreeNode{jcode, data, NULL, NULL, NULL};
            prev = root;
            continue;
        }
        if(flag==LOAD_LEFT_SUBTREE && S.empty()) break;
        prev = S.top();
        S.pop();
        if(data == -2){
            prev->right = NULL;
            continue;
        }
        int JourneyCode;
        f>>JourneyCode;
        prev->right = new TreeNode{JourneyCode, data, NULL, NULL, prev};
        prev = prev->right;
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


//..........................................//

// int main(){
//     BST* b1 = new BST();
//     b1->insert(100,4);
//     b1->insert(101,2);
//     b1->insert(102,1);
//     b1->insert(103,5);
//     b1->insert(104,6);
//     b1->insert(105,9);
//     b1->insert(106,7);
//     b1->insert(107,8);
//     b1->insert(108,11);
//     b1->insert(109,10);
//     b1->printBST("");
//     b1->customStore("test.ser"s);
//     b1->getBST("");
//     BST* b2 = new BST();
//     b2->customLoad(LOAD_LEFT_SUBTREE,"test.ser"s);
//     b2->printBST("");
//     b2->traverse(2);
//     b2->getBST("");
// }
