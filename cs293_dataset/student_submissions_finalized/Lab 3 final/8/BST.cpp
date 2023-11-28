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

bool isLeft(TreeNode* parent, TreeNode* child);
// PLEASE FILL IN THE BODIES OF THE FOLLOWING FUNCTIONS
int noOfChildren(TreeNode* node) {
    if (node->left == nullptr && node->right == nullptr) return 0;
    else if (node->left != nullptr && node->right == nullptr) return 1;
    else if (node->left == nullptr && node->right != nullptr) return 1;
    else if (node->left != nullptr && node->right != nullptr) return 2;
    return -1;
}
bool isLeft(TreeNode* parent, TreeNode* child) { 
    if(parent -> left == nullptr) return false;

    else if(parent -> right == nullptr) return true;

    else if (parent -> left == child)
    {
        return true;
    }

    else if (parent -> right == child)
    {
        return false;
    }
    return false; 
}

TreeNode *treeMin(TreeNode* rootNode) {
    TreeNode * ptr = rootNode;
    while (ptr -> left != nullptr)
    {
        ptr = ptr -> left;
    }
    
    return ptr;
}

TreeNode* successor(TreeNode* node) {
    TreeNode* ptr1 = node;
    TreeNode* ptr2 = ptr1 -> parent;
    if (node -> right != nullptr)
    {
        return treeMin(node -> right);   
    }

    else {
        while (!(ptr2 -> left == ptr1))
        {
            if(ptr2 == nullptr) break;
            ptr1 = ptr2;
            ptr2 = ptr2 -> parent;
        }
        
        if (ptr2 != nullptr)
        {
            return ptr2;
        }

        return nullptr;
        
    }
    
}

void joinNodes(TreeNode* parent, TreeNode* child, bool left = true){
    if(left == true){
        parent -> left = child;
        child -> parent = parent;
    }    

    else {
        parent -> right = child;
        child -> parent = parent;
    }
}

void joinNodes2(TreeNode* node, TreeNode* Succ) {
    // making ptr form parent of the successor to the successor null
    if(isLeft(Succ->parent,Succ)) Succ->parent->left = nullptr;
    else Succ->parent->right = nullptr;

    if(Succ -> right != nullptr) joinNodes(Succ->right,Succ->parent,true);
    joinNodes(node->parent,Succ,isLeft(node->parent,node));
    Succ -> left = node -> left;
    Succ -> right = node -> right;
    Succ -> parent = node -> parent;

}






BST::BST(){
    root = nullptr;    
}
BST::BST(TreeNode *root){
    this->root = root;
 }

// Returns false, if given JourneyCode is already present in the BST
// Inserts the element and returns True otherwise
bool BST::insert(int JourneyCode, int price) {
    TreeNode *ptr = root;
    TreeNode *ptr2 = nullptr;
    
    //cout << "inserting" << endl;
    while (ptr != nullptr)
    {
        //cout << "stuck" << endl;
       if (ptr -> price > price)
       {
            ptr2 = ptr;
            ptr  = ptr -> left;
       }

       else if (ptr -> price == price && ptr -> JourneyCode == JourneyCode)
       {
        return false;
       }
       

       else
       {
            ptr2 = ptr;
            ptr = ptr -> right;
       }
    }

    TreeNode *node = new TreeNode(JourneyCode,price);
    //if tree do not ahs a node
    if (ptr2 == nullptr)
    {
        root = node;
    }
    
    // if node was there before
    else if(ptr2 -> price > price) {
        ptr2 -> left = node;
        node -> parent = ptr2;
    }

    else
    {
        ptr2 -> right = node;
        node -> parent = ptr2;
    }

    return true;
}

//void BST::printTree() {
    //TreeNode* ptr = root
    //while (/* condition */)
    //{
        ///* code */
    //}
    
//}

// Return True, if the ticket with given attributes is found, false otherwise
bool BST::find(int JourneyCode, int price) {
    TreeNode *ptr = root;
    while (ptr != nullptr)
    {
       if (ptr -> price == price && ptr -> JourneyCode == JourneyCode)
       {
        return true;
       }

       else if (ptr -> price > price)
       {
            ptr  = ptr -> left;
       }

       

       else
       {
            ptr = ptr -> right;
       }
    
        
    }
    
    return false;
}

TreeNode* BST::findNode(int JourneyCode, int price) {
    TreeNode *ptr = root;
    while (ptr != nullptr)
    {
      //  cout << "i stuck in findNode loop" << endl;
       // cout << JourneyCode << " " << price << endl;
       // cout << endl;
       if (ptr -> price == price && ptr -> JourneyCode == JourneyCode)
       {
        return ptr;
       }

       else if (ptr -> price > price)
       {
            ptr  = ptr -> left;
       }

       

       else
       {
            ptr = ptr -> right;
       }
    }

    return nullptr;
}
	
// Returns false, if JourneyCode isn't present
// Deletes the corresponding entry and returns True otherwise
bool BST::remove(int JourneyCode, int price) { 
    TreeNode* node = findNode(JourneyCode,price);

    if (!find(JourneyCode,price))
    {
        return false;   
    }
    
    else if (node == root)
    {
       if (noOfChildren(node) == 0)
       {
        root == nullptr;
       }
       
       else if (node -> right == nullptr)
       {
        root = node -> left;
        root -> parent = nullptr;
       }

       else if (node -> left == nullptr)
       {
        root = node -> right;
        root -> parent = nullptr;
       }
       
       else {
        root = successor(root);
        root -> left = node -> left;
       }

        return true;
        
    }


    else if (noOfChildren(node) == 0)
    {
        TreeNode* parent = node->parent;
        node -> parent = nullptr;
        if (parent -> left == node)
        {
            parent -> left = nullptr;
        }
        
        else {
            parent -> right = nullptr;
        }
        return true;
    }

    else if (noOfChildren(node) == 1)
    {
        TreeNode* child = node->left == nullptr ? node->right : node->left; 
        joinNodes(node->parent,child, isLeft(node->parent,node));
        return true;
        
    }
    
    else if (noOfChildren(node) == 2) {
        //cout << successor(node) -> price << "this is the price of successor" << endl;
        joinNodes2(node, successor(node));
        return true;
    }
    
    
    
    //successor(findNode(JourneyCode,price)) ->printNode();
    return false; 
}



// Functions that traverse the BST in various ways!
// type is one of PRE_ORDER, POST_ORDER or IN_ORDER
// Print on cout the journey codes at nodes of the BST in the same order as
// they are encountered in the traversal order
// Print one journey code per line

void preOrder(TreeNode* node) {
    if(node == nullptr) return;
    cout << node -> JourneyCode << " "; 
    preOrder(node -> left);
    preOrder(node -> right);
}

void postOrder(TreeNode* node) {
    if(node == nullptr) return;
    postOrder(node -> left);
    postOrder(node -> right);
    cout << node -> JourneyCode << " ";
}

void inOrder(TreeNode* node) {
    if(node == nullptr) return;
    inOrder(node -> left);
    cout << node -> JourneyCode << " ";
    inOrder(node -> right);
}

void BST::traverse(int typeOfTraversal) {
    switch(typeOfTraversal)
    {
        case 1:
            preOrder(root);
        
        case 2:
            postOrder(root);
        
        case 3: 
            inOrder(root);
        
        default:
            return;
    }
}

// Returns the price of the cheapest journey
int BST::getMinimum() {
    return treeMin(root) -> price;
 }

// Part II

// Returns the count of journeys that are at least as expensive
// as lowerPriceBound and at most as expensive as upperPriceBound,
// both bounds included.
int recurseFindRange(int lowerBound, int upperBound, TreeNode* node) {
    int this_count = (lowerBound <= node -> price && upperBound >= node -> price);

    if(noOfChildren(node) == 0){
        return this_count;
    }

    else if(node-> price >= upperBound && node -> left != nullptr) {
        return this_count + recurseFindRange(lowerBound,upperBound, node -> left) ; //left;
    }
    
    else if(node -> price <= lowerBound && node -> right != nullptr) {
        return this_count + recurseFindRange(lowerBound, upperBound, node -> right) ; //right
    }

    else if(noOfChildren(node) == 2) {
        return this_count + recurseFindRange(lowerBound, upperBound, node -> left) + recurseFindRange(lowerBound, upperBound, node-> right); //left and right
    }

    else {
        return this_count;
    }
}

int BST::countJourneysInPriceBound(int lowerPriceBound, int upperPriceBound) {
    return(recurseFindRange(lowerPriceBound, upperPriceBound, root));
}

// Store the current tree in a file called filename.  You should
// store using a scheme that uses no more disk space than that
// required to store all elements in the BST, plus perhaps a small
// constant times the number of elements.  You should also store
// in a manner such that your implementation of customLoad is as
// memory and time efficient as possible.
void preOrderPrice(TreeNode* node, ofstream& outfile) {
    if(node == nullptr) return;
    outfile << node -> JourneyCode << " " << node -> price;

    if(node -> left != nullptr){
        outfile << '!';
        // outfile << " " << '!' << " ";
        preOrderPrice(node -> left,outfile);
        outfile<< 'e';
        // outfile << " " << 'e' << " ";
    }

    if(node -> right != nullptr) {
        outfile<<'@';
        // outfile << " " <<  '@' << " ";
        preOrderPrice(node -> right,outfile);
        outfile << 'e'; 
        // outfile << " " << "#" << " ";
    }

}

void BST::customStore(string filename)
{
  ofstream outFile;
  outFile.open(filename);

  preOrderPrice(root,outFile);
  outFile << 'e'; 
  outFile.close();
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
void makeBST (TreeNode* node, ifstream &inFile) {
    char pos;
    int JourneyCode;
    int price;

    inFile >> pos;
    // if(pos == 'e') return;
    inFile >> JourneyCode;
    inFile >> price;
    cout << pos << endl;
    



    TreeNode* curr_node = new TreeNode(JourneyCode, price);
    //cout << pos << endl;
    //curr_node->printNode();

    if(pos == '!') {
        cout << "left" << endl;
        joinNodes(node, curr_node,true);
        makeBST(curr_node,inFile);
    }
    

    inFile >> pos;
    if(pos == 'e') return;
    inFile >> JourneyCode;
    inFile >> price;
    cout << pos << endl;

    curr_node = new TreeNode(JourneyCode, price);
    if (pos == '@') {
        cout << "right" << endl;
        joinNodes(node, curr_node, false);
        makeBST(curr_node,inFile);
    }
    return;

}

TreeNode* readBST(ifstream& in){
    int code, price;
    in >> code >> price;
    TreeNode* res = new TreeNode(code, price);

    char next='a';
    while(next != 'e'){
        in >> next;
        if(next == '!'){
            res -> left = readBST(in);
            res->left->parent = res;
        }
        else if(next == '@'){
            res -> right = readBST(in);
            res->right->parent = res;
        }
    }

    return res;
}


TreeNode* readLeftBST(ifstream& in){
    int code, price;
    in >> code >> price;
    TreeNode* res = new TreeNode(code, price);

    char next='a';
    while(next != 'e'){
        in >> next;
        if(next == '!'){
            res -> left = readBST(in);
            res->left->parent = res;
        }
        else if(next == '@'){
            res -> right = readBST(in);
            res->right->parent = res;
        }
    }

    return res;
}
void BST::customLoad (int flag, string filename) {
    if (flag == LOAD_FULL_BST) {
    ifstream inFile ;
    inFile.open(filename);

    

    this->root = readBST(inFile);

    inFile.close();
    }

    else {
        ifstream inFile ;
        inFile.open(filename);

        char x;
        int var1, var2;
        inFile >> var1 >> var2;
        inFile >> x;
        this->root = readBST(inFile);
        
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
        cout << root->price<< endl;
        TreeNode *curr = root;
        root = root->left;
        // enter the next tree level - left and right branch
        printBST( prefix + (isLeft ? "│   " : "    "), true);
        //curr -> printNode();
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

        // print the value of the nod)e
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


