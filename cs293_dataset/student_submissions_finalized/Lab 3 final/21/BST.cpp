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

vector<string> sentence;
void splitting (string str, char seperator)  
{  
    sentence.clear();
    int currIndex = 0, i = 0;  
    int startIndex = 0, endIndex = 0;  
    while (i <= str.length())  
    {  
        if (str[i] == seperator || i == str.length())  
        {  
            endIndex = i;
            sentence.push_back(str.substr(startIndex,endIndex-startIndex));
            startIndex = endIndex + 1;  
        }  
        i++;  
        }     
}


// PLEASE FILL IN THE BODIES OF THE FOLLOWING FUNCTIONS

BST::BST(){
    root = NULL;
}
BST::BST(TreeNode *root){
    this->root=root ;
}

// Returns false, if given JourneyCode is already present in the BST
// Inserts the element and returns True otherwise
bool BST::insert(int JourneyCode, int price) { 
    TreeNode *insert = root;
    if (root == NULL){
        root = new TreeNode(JourneyCode,price);
        root->parent=NULL;
        return true;
    }
    else {
        TreeNode *track = new TreeNode();
        while (insert != NULL){
            if (insert->JourneyCode == JourneyCode) return false;
            if (insert->price < price){
                track = insert;
                insert = insert->right;
            }
            else if (insert->price > price){
                track = insert;
                insert = insert->left;
            }
            
        }
        insert = new TreeNode(JourneyCode,price,NULL,NULL,track);
        if (track->price < price) track->right=insert;
        else if (track->price > price) track->left=insert;
        return true;
    }

}

// Return True, if the ticket with given attributes is found, false otherwise
bool BST::find(int JourneyCode, int price) { 
    TreeNode *search = root;
    while (search != NULL){
        if (search->price < price){
                search = search->right;
        }
        else if (search->price > price){
                search = search->left;
        }
        else{
            return (search->JourneyCode==JourneyCode);
        }
    }
    return false;
}

TreeNode* BST::findandreturn(int JourneyCode, int price) { 
    TreeNode *search = root;
    while (search != NULL){
        if (search->JourneyCode==JourneyCode) return search;
        if (search->price < price){
                search = search->right;
        }
        else if (search->price > price){
                search = search->left;
        }
    }
    return NULL;
}

	
// Returns false, if JourneyCode isn't present
// Deletes the corresponding entry and returns True otherwise
bool BST::remove(int JourneyCode, int price) { 
    TreeNode* del = findandreturn(JourneyCode,price);
    if (del != NULL){
        
            TreeNode* parent = del->parent;
            if (del->left == NULL && del->right == NULL){
                if (del != root){
                    if(parent->price < price) parent->right=NULL;
                    else if(parent->price > price) parent->left=NULL;
                }
                delete del;
            }
            else if (del->left == NULL && del->right != NULL){
                if (del != root){
                    if (parent->price < price){
                        parent->right = del->right;
                        del->right->parent = parent;
                    }
                    else if (parent->price > price){
                        parent->left = del->right;
                        del->left->parent = parent;
                    }
                }
                else root = root->right;
                
                delete del;
            }
            else if (del->left != NULL && del->right == NULL){
                if (del != root){
                    if (parent->price < price){
                        parent->right = del->left;
                    }
                    else if (parent->price > price){
                        parent->left = del->left;
                    }
                }
                else root = root->left;
                delete del;
            }
            else if (del->left != NULL && del->right != NULL){
                TreeNode* track = del->right;
                while(track->left != NULL) track = track->left;
                if (track == del->right){
                    del->JourneyCode=track->JourneyCode;
                    del->price = track->price;
                    del->right = track->right;
                    if (track->right != NULL) track->right->parent = del;
                    delete track;
                }
                else{
                    del->JourneyCode=track->JourneyCode;
                    del->price = track->price;
                    track->parent->left=NULL;
                    if (track->right != NULL){
                        track->right->parent = track->parent;
                        track->parent->right = track->right;
                    }
                    delete track;
                }
            
        }
        return true;
    }

    else return false;
 }
	
// Functions that traverse the BST in various ways!
// type is one of PRE_ORDER, POST_ORDER or IN_ORDER
// Print on cout the journey codes at nodes of the BST in the same order as
// they are encountered in the traversal order
// Print one journey code per line

int preorder(TreeNode *x, bool re){
    int sum = 0;
    if (re){
        if (x == NULL) return 0;
        else {
            sum = sum + x->price;
            preorder(x->left,true);
            preorder(x->right,true);
            return sum;
        }    
    }
    else{
        if (x == NULL) return 0;
        else {
            cout << x->JourneyCode << endl;
            int a = preorder(x->left,false);
            int b = preorder(x->right,false);
            return 0;
        }
    }
    
}

int postorder(TreeNode *x, bool re){
    int sum = 0;
    if (re){
        if (x == NULL) return 0;
        else {
            preorder(x->left,true);
            preorder(x->right,true);
            sum = sum + x->price;
            return sum;
        }    
    }
    else{
        if (x == NULL) return 0;
        else {
            int a = preorder(x->left,false);
            int b = preorder(x->right,false);
            cout << x->JourneyCode << endl;
            return 0;
        }
    }
    
}

int inorder(TreeNode *x, bool re){
    int sum = 0;
    if (re){
        if (x == NULL) return 0;
        else {
            preorder(x->left,true);
            sum = sum + x->price;
            preorder(x->right,true);
            return sum;
        }    
    }
    else{
        if (x == NULL) return 0;
        else {
            int a = preorder(x->left,false);
            cout << x->JourneyCode << endl;
            int b = preorder(x->right,false);
            return 0;
        }
    }
    
}

void BST::traverse(int typeOfTraversal) {
    if (typeOfTraversal == 0){
        preorder(root,false);
    }
    if (typeOfTraversal == 1){
        postorder(root,false);
    }
    if (typeOfTraversal == 2){
        inorder(root,false);
    }

 }

// Returns the price of the cheapest journey
int BST::getMinimum() {
    TreeNode* min = root;
    while(min->left != NULL) min = min->left;
    return min->price;  
 }

// Part II

// Returns the count of journeys that are at least as expensive
// as lowerPriceBound and at most as expensive as upperPriceBound,
// both bounds included.
int BST::countJourneysInPriceBound(int lowerPriceBound, int upperPriceBound) {
    int count = 0;
    TreeNode* tracker = root;

    if( tracker == NULL ) {
        return 0;}
    if (root->price >= lowerPriceBound && root->price <= upperPriceBound){
        count++;
        root = tracker->left;
        count += countJourneysInPriceBound(lowerPriceBound,upperPriceBound);
        root = tracker->right;
        count += countJourneysInPriceBound(lowerPriceBound,upperPriceBound);
    }
    else if (root->price > upperPriceBound){
        root = tracker->left;
        count += countJourneysInPriceBound(lowerPriceBound,upperPriceBound);
    }
    else if (root->price < lowerPriceBound){
        root = tracker->right;
        count += countJourneysInPriceBound(lowerPriceBound,upperPriceBound);
    }
    root = tracker;
    return count; 
 }

// Store the current tree in a file called filename.  You should
// store using a scheme that uses no more disk space than that
// required to store all elements in the BST, plus perhaps a small
// constant times the number of elements.  You should also store
// in a manner such that your implementation of customLoad is as
// memory and time efficient as possible.
void store(ofstream& file , TreeNode* root) { 
      if (root == nullptr)  file<<"NULL NULL"<<endl  ;
      else { 
            file<<(root->JourneyCode)<<" "<< (root->price)<<endl ;
            store(file , root->left) ;  
            store(file , root->right) ;  
      } 
} 

void BST::customStore(string filename) { 
    ofstream file ; 
    file.open(filename) ;
    store(file,root) ;  
    file.close() ; 
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
void load(ifstream& file , TreeNode* child , TreeNode* parent ) { 
      string x , y ; 
      if (!file.eof()) {
        file>>x>>y  ;
        if ( x == "" ) return ; 
        if ( x == "NULL")  { 
           if (parent->left == child) parent->left = nullptr ; 
           else parent->right = nullptr ; 
           delete child ; 
        } 
        else { 
             int journey = stoi(x) ; 
             int price = stoi(y); 
             child->JourneyCode = journey ; 
             child->price = price ; 
             child->parent = parent ;
             child->left = new TreeNode() ; 
             child->right = new TreeNode() ; 
             load( file , child->left , child ); 
             load( file , child->right , child ); 
        } 
      }
}


 
void BST::customLoad(int flag, string filename) { 
    if (flag==3){
        ifstream file ; 
        file.open(filename) ;   
        root = new TreeNode() ;
        load(file,root,nullptr) ;  
        file.close() ;
    } 
    // else if(flag==4){
    //     ifstream file ; 
    //     file.open(filename) ;   
    //     root = new TreeNode() ;
    //     loadleft(file,root,nullptr) ;  
    //     file.close() ;
    // }
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

