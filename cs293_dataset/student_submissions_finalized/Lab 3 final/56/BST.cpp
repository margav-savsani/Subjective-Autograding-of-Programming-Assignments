#include <bits/stdc++.h>
#include <iostream>
#include <vector>
#include <string>
#include <cassert>

using namespace std;

#include "BST.h"

#define PRE_ORDER 0
#define POST_ORDER 1
#define IN_ORDER 2
#define LOAD_FULL_BST 3
#define LOAD_LEFT_SUBTREE 4


// PLEASE FILL IN THE BODIES OF THE FOLLOWING FUNCTIONS

//Assuming that right subtree contains elements >= root and left subtree < root

BST::BST(){
    root = new TreeNode();       
    root = NULL;    //set the root the null when no root is specified 
    N = 0;   //current size of tree is 0
   
}
BST::BST(TreeNode *root){
    this->root = root;
    root->parent = NULL;        //parent of root is NULL
    N = 1;    //current size of tree is 0
}

// Returns false, if given JourneyCode is already present in the BST
// Inserts the element and returns True otherwise
bool BST::insert(int JourneyCode, int price) { 
    bool res;       //bool to store the exit code of insert
    if(root != NULL){        
        if(price < root->price){              //insert in left subtree
            if(root->left == NULL){   //if no left node, insert at that place
                TreeNode* tempch = new TreeNode(JourneyCode, price);
                root->leftChild(tempch);
                res = true;
                N += 1;   //size increases on successful insert
                return true;
            }
            else{      //if left node, insert recursively
                TreeNode* temp = root;  
                root = root->left;     //insert in the left subtree
                res = insert(JourneyCode, price);
                root = temp;
            }
            
        }
        else if(price >= root->price){   //insert in the right subtree
            if(root->JourneyCode == JourneyCode){    //if equal, => same entry => reject
                res = false;
                return false;
            }
            if(root->right == NULL){    //if no right child, insert at the right child
                TreeNode* tempch = new TreeNode(JourneyCode, price);  
                root->rightChild(tempch);
                res = true;
                N += 1;
                return true;
            }
            else{    //if right child, then insert in right subtree
                TreeNode* temp = root;
                root = root->right;
                res = insert(JourneyCode, price);
                root = temp;
            }
        }
    }
    else{    //if root is NULL, insert the root element and set its parent to NULL
        root = new TreeNode(JourneyCode, price);    
        root->parent = NULL;
        res = true;
    }
    if(res){
        N += 1;   //increase the size by 1
    }
    return res;
}

// Return True, if the ticket with given attributes is found, false otherwise
bool BST::find(int JourneyCode, int price) { 
    bool res;
    if(root != NULL){          //can find only if root exists
        if(root->JourneyCode == JourneyCode && root->price == price){    //trivial case
            return true;
        }
        if(price < root->price){    //check in left subtree
            TreeNode* temp = root;
            root = root->left;
            res = find(JourneyCode, price);            
            root = temp;
        }
        else if(price >= root->price){   //check in right subtree
            TreeNode* temp = root;
            root = root->right;
            res = find(JourneyCode, price);
            root = temp;
        }
        
        return res;
    }
    else{  //no root, => no entries
        return false;
    }
}

TreeNode* BST::findNode(int JourneyCode, int price){   //same as find(..), but returns a pointer to the element instead of bool
    TreeNode* res;
    if(root != NULL){        
        if(root->JourneyCode == JourneyCode && root->price == price){
            return root;
        }
        if(price < root->price){
            TreeNode* temp = root;
            root = root->left;
            res = findNode(JourneyCode, price);            
            root = temp;
        }
        else if(price >= root->price){
            TreeNode* temp = root;
            root = root->right;
            res = findNode(JourneyCode, price);
            root = temp;
        }
        
        return res;
    }
    else{
        return NULL;
    }
}


// Returns false, if JourneyCode isn't present
// Deletes the corresponding entry and returns True otherwise
bool BST::remove(int JourneyCode, int price){     
    TreeNode* node = findNode(JourneyCode, price);   //find the node to be deleted
    if(node == NULL){   //doesn't exist
        return false;
    }
    if(node->left == NULL && node->right == NULL){    //if node is leaf, delete without changing the rest of the tree
        if(node == root){    //if node is root, tree becomes empty
            delete root;
            root = NULL;
        }
        else{    //if not root, exchange this node with NULL
            assert(node->parent != NULL);
            TreeNode* parent = node->parent;
            node->exchange(NULL);
            delete node;
        }
    }

    else if(node->left == NULL || node->right == NULL){    //one of left/right is NULL, attach its child to its parent and delete it 
        bool isRoot = (node == root);    //check if root
        TreeNode* child;
        if(node->left == NULL){    //if left is NULL, then attach the right subtree
            child = node->right;            
        }
        else if(node->right == NULL){   //if right is NULL, then attach left subtree
            child = node->left;            
        }
        assert(child->parent == node);     //security check
         
        node->exchange(child);    //exchange this node with its child
        if(isRoot){   //update the root
            root = child;
            child->parent = NULL;
        }        
        delete node;   //memory management
    }

    else{    //both children exist, find the successor
        bool isRoot = (node == root);    //check if root
        TreeNode* tmp = root;
        root = node->right;    
        TreeNode* succ = getMinimumNode();   //finding the successor
        root = tmp;
        if(succ != NULL) assert(succ->left == NULL);     //successor cannot have a left child
        
        if(succ->right != NULL){        
            TreeNode* child = succ->right;
            if(child != NULL) assert(child->parent == succ);
            succ->exchange(child);
            if(child != NULL) assert(child->parent != succ);                        
        }
        else{            
            succ->exchange(NULL);                
        }
        
        succ->parent = NULL;
        
        node->exchange(succ);   //exchange the node with its successor
        
        if(succ != NULL) assert(succ->parent == node->parent);    
        
        TreeNode* leftch = node->left;
        TreeNode* rightch = node->right;
        
        
        succ->leftChild(leftch);    //change the left and children off the successor to the respective children of node
        
        if(leftch != NULL) assert(leftch->parent == succ);   //security check
        succ->rightChild(rightch);
        
        if(succ != NULL) assert(succ->parent == node->parent);    //security check
        if(rightch != NULL) assert(rightch->parent == succ);
        if(isRoot){    //if node is root, parent of succ should be null, update root
            root = succ;
            succ->parent = NULL;            
        }
        delete node;   //memory management
    }

    N -= 1;
    return true;
}


	
// Functions that traverse the BST in various ways!
// type is one of PRE_ORDER, POST_ORDER or IN_ORDER
// Print on cout the journey codes at nodes of the BST in the same order as
// they are encountered in the traversal order
// Print one journey code per line

void BST::traverse(int typeOfTraversal) {  //recursive traversals
    if(root != NULL){
        if(typeOfTraversal == PRE_ORDER){     //pre order traversal, recursively
            
            cout << root->JourneyCode << endl;  //print that element
            TreeNode* temp = root;
            root = root->left;   //pre order of left subtree  
            traverse(typeOfTraversal);
            root = temp;
            root = root->right;   //pre order of right subtree
            traverse(typeOfTraversal);
            root = temp;
        }
        else if(typeOfTraversal == IN_ORDER){    //in order traversal, recursively
            TreeNode* temp = root;
            root = root->left;     //in order of left subtree
            traverse(typeOfTraversal);
            root = temp;
            cout << root->JourneyCode << endl;    //print current node
            root = root->right;       //in order of right subtree
            traverse(typeOfTraversal);
            root = temp;
        }
        else if(typeOfTraversal == POST_ORDER){   //post order traversal, recursively
            TreeNode* temp = root;
            root = root->left;
            traverse(typeOfTraversal);   //post order of left subtree
            root = temp;
            root = root->right;
            traverse(typeOfTraversal);   //post order of right subtree
            root = temp;
            cout << root->JourneyCode << endl;   //print current node
        }
    }
}

TreeNode* BST::getMinimumNode(){   //find the minimum node recursively, find the "leftmost" node
    if(root != NULL){
        TreeNode* trav = root;
        while(trav->left != NULL){
            trav = trav->left;
        }
        return trav;
    }
    else{
        return NULL;
    }
}

// Returns the price of the cheapest journey
int BST::getMinimum() {    //find the minimum price
    if(root != NULL){    
        TreeNode* trav = root;
        while(trav->left != NULL){
            trav = trav->left;
        }
        return trav->price;
    }
    return 0;   
}

// Part II

// Returns the count of journeys that are at least as expensive
// as lowerPriceBound and at most as expensive as upperPriceBound,
// both bounds included.
int BST::countJourneysInPriceBound(int lowerPriceBound, int upperPriceBound) {  //recursively count the number of journeys
    int res = 0;
    if(root == NULL || lowerPriceBound > upperPriceBound){   //impossible cases
        return 0;
    }
    if(root->price <= lowerPriceBound){   //search only in the right subtree
        if(root->price == lowerPriceBound){
            res += 1;
        }
        TreeNode* temp = root;
        root = root->right;
        res += countJourneysInPriceBound(lowerPriceBound, upperPriceBound);
        root = temp;
        return res;        
    }    
    if(root->price >= upperPriceBound){   //search only in the lefft subtree
        if(root->price == upperPriceBound){
            res += 1;
        }
        TreeNode* temp = root;
        root = root->left;
        res += countJourneysInPriceBound(lowerPriceBound, upperPriceBound);
        root = temp;
        return res;
    }   //else, check in both subtrees
    res += 1;
    TreeNode* temp = root;
    root = root->left;
    res += countJourneysInPriceBound(lowerPriceBound, upperPriceBound);
    root = temp;
    root = root->right;
    res += countJourneysInPriceBound(lowerPriceBound, upperPriceBound);
    root = temp;
    return res;

}

// Store the current tree in a file called filename.  You should
// store using a scheme that uses no more disk space than that
// required to store all elements in the BST, plus perhaps a small
// constant times the number of elements.  You should also store
// in a manner such that your implementation of customLoad is as
// memory and time efficient as possible.
void BST::customStore(string filename) {  //store each node in the form price|jrny_code|flag
                                    //flag is one of 'd', 'o', 'l', 'r'
                                    //'d' - has both children
                                    //'r' - has only a right child
                                    //'l' - has only a left child
                                    //'o' - leaf node
    vector<TreeNode*> inters(N, NULL);      //store 'd' flag nodes on a stack
    int curr_pushes = 0;
    ofstream store(filename);
    if(root != NULL){    //tree is not empty, proceed with storing
        TreeNode* trav = root;
        while(true){
            if(trav->left == NULL && trav->right == NULL){    //leaf node
                store << trav->price << "|" << trav->JourneyCode << "|o "; store.flush();
                if(curr_pushes == 0){   //if nothing on stack, storing complete, so return
                    break;
                }
                else{                    
                    trav = (inters[curr_pushes-1])->right;           //traverse from the right of the most recent branching node    
                    inters.pop_back();
                    curr_pushes -= 1;
                }
            }            
            else if(trav->left != NULL && trav->right != NULL){     //branching node, store on stack
                store << trav->price << "|" << trav->JourneyCode << "|d "; store.flush();
                inters[curr_pushes] = trav;                
                curr_pushes += 1;
                trav = trav->left;
            }
            else if(trav->left != NULL && trav->right == NULL){    //only left child
                store << trav->price << "|" << trav->JourneyCode << "|l "; store.flush();
                trav = trav->left;
            }
            else if(trav->left == NULL && trav->right != NULL){   //only right child
                store << trav->price << "|" << trav->JourneyCode << "|r "; store.flush();
                trav = trav->right;
            }
        }
    }   
    else{        //store nothing as tree is empty
        store << "";   
    } 
    //store << value;
    store.close();
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
 
void BST::customLoad(int flag, string filename) {
    
    N = 0;   //we'll update the size as the tree keeps getting filled
    deleteRoot();    //beware of segmentation faults
    ifstream load(filename);    
    assert(root == NULL);    //root becomes null after deleteRoot()
    string data;  //data in each node
    vector<TreeNode*> inters;    //store the nodes where branching happens, find flag 'd'
    TreeNode* trav = NULL;   //pointer used to traverse
    while(load >> data){
        N += 1;       
        string pricestr = "";
        string jcodestr = "";
        char bufflag;     //flag of the node
        int pipe = 0;
        for(int i = 0; i < data.size(); i++){
            if(data[i] == '|'){
                pipe += 1;
                continue;                
            }
            if(pipe == 0){
                pricestr += data[i];
            }
            else if(pipe == 1){
                jcodestr += data[i];
            }
            else{
                bufflag = data[i];
            }
        }
        if((bufflag == 'r' || bufflag == 'o') && root == NULL && flag == LOAD_LEFT_SUBTREE){    //no left subtree exists, return NULL
            return;
        }
        int price = stoi(pricestr);    //price of node
        int journey_code = stoi(jcodestr);   //jrny code of node
        TreeNode* newnode = new TreeNode(journey_code, price);    
        if(root == NULL){              //if no root, make the root
            root = newnode;
            trav = root;
            root->parent = NULL;
            if(bufflag == 'd'){    //if branching node, store it on stack for future use
                inters.push_back(newnode);
            }
            continue;
        }
        if(trav->price > price){      //store in left subtree
                   
            trav->leftChild(newnode);            
            trav = trav->left;            
        }
        else{   //store in right subtree
            trav->rightChild(newnode);
            trav = trav->right;                       
        }
        if(bufflag == 'd'){    //if branching node, store it on stack for future use
            inters.push_back(newnode);
        }
        else if(bufflag == 'o'){    //leaf node
            if(inters.size() == 0){          //if nothing is present on the stack i.e. all branches have been traversed
                if(root->right == NULL && flag == LOAD_LEFT_SUBTREE){     //loading only left subtree, so update the root to root->left
                    TreeNode* dumleft = root->left;
                    delete root;
                    root = dumleft;
                    root->parent = NULL;
                    N -= 1;
                    return;
                }       
                break;
            }
            TreeNode* temp = inters.back();    //go to the last location on stack
            if(flag == LOAD_LEFT_SUBTREE && temp == root){     //if reached root, loading only left subtree, so update the root to root->left
                TreeNode* dumleft = root->left;
                delete root;
                root = dumleft;
                root->parent = NULL;
                N -= 1;
                return;
            }
            inters.pop_back();            
            trav = temp;   //traverse from the most recent branched node
        }
        
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
