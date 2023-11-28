// Code up the functions defined in tree.h
// Reuse the binary Search Tree implemented in lab 3 as much as possible

#include <bits/stdc++.h>
#include <iostream>
#include <vector>
#include <string>
#include <cmath>
using namespace std;

#include "tree.h"

// PLEASE FILL IN THE BODIES OF THE FOLLOWING FUNCTIONS

// Returns false, if given JourneyCode is already present in the BST
// Inserts the element and returns True otherwise

int BST::getImbalance()
{
  if (root == nullptr) return 0;
  else  {
    // cout<<root->longestPathLength<<" "<<root->shortestPathLength<<endl;
    return root->getImbalance();
  }
}

void BST::updator(TreeNode* new_node){           

    while(new_node->parent != SENTINAL){
        if(new_node->parent->left == NULL || new_node->parent->right == NULL){                   
            new_node->parent->shortestPathLength=1+new_node->shortestPathLength;  
            new_node->parent->longestPathLength=1+new_node->longestPathLength;                                          
            new_node = new_node->parent;
        } else {                   
            new_node->parent->shortestPathLength = 1 + min(new_node->parent->left->shortestPathLength, new_node->parent->right->shortestPathLength); 
            new_node->parent->longestPathLength = 1+ max(new_node->parent->left->longestPathLength, new_node->parent->right->longestPathLength);                   
            new_node = new_node->parent;                                   
        }                                
    } 
}

bool BST::insert(int JourneyCode, int price)
{
  // The following filler code snippet is only given to facilitate
  // compilation.  You should replace/augment it with appropriate code,
  // similar to what you had done in lab assignment 3.
  // JourneyCode is not present in the BST.  We must now
  // insert an appropriate child of parentOfCurrNode.
  // Please implement this part yourself.
  //
  // Do not forget to update shortestPathLength and
  // longestPathLength of (possibly all) BST nodes in the
  // path from the root to the new node you are inserting

    TreeNode* temp1=NULL;                // used to find the location of the parent of the node which is NULL
    TreeNode* temp2=root;                // used to find the location of the node
    while(temp2 != NULL ){   
        if(temp2->JourneyCode != JourneyCode){
           temp1 = temp2;
            if(price < temp1->price){
                temp2 = temp2->left;
            }
            else temp2 = temp2->right; 
        }    
        else break;
    } 
    if(temp2 != NULL){
        return false;    
    }
    else{
        if(temp1 == NULL){           
            root = new TreeNode;
            root->JourneyCode = JourneyCode;
            root->price = price;
            root->longestPathLength=0;
            root->shortestPathLength=0;        
            root->parent = SENTINAL;
            SENTINAL->right = root;
        }
        else{
            TreeNode* new_node ;
            if(temp1->price > price){                
                temp1->left = new TreeNode;
                temp1->left->JourneyCode = JourneyCode;
                temp1->left->price = price;
                temp1->left->parent = temp1;
                temp1->left->longestPathLength=0;
                temp1->left->shortestPathLength=0; 
                if(temp1->parent->longestPathLength == 0) {
                    temp1->parent->longestPathLength++;
                    temp1->parent->shortestPathLength++;
                }
                else  temp1->parent->shortestPathLength=1;  
                new_node = temp1->left;                                               
            }
            else{
                temp1->right = new TreeNode;
                temp1->right->JourneyCode = JourneyCode;
                temp1->right->price = price;
                temp1->right->parent = temp1;
                temp1->right->longestPathLength=0;
                temp1->right->shortestPathLength=0;      
                if(temp1->parent->longestPathLength == 0) {
                    temp1->parent->longestPathLength++;
                    temp1->parent->shortestPathLength++;
                }
                else    temp1->parent->shortestPathLength=1;   
                new_node = temp1->right;                               
            }
            updator(new_node);
        }
        return true;
    }
}

// Return the node corresponding the entries.
struct TreeNode* BST::find_node(int JourneyCode, int price){
    TreeNode* temp=root;   
    while(temp != NULL){
        if(temp->price == price && temp->JourneyCode == JourneyCode) break;
        if(price < temp->price) temp = temp->left;
        else temp = temp->right;    
    }
    return temp;
}

// Return True, if the ticket with given attributes is found, false otherwise
bool BST::find(int JourneyCode, int price)
{
  // The following filler code snippet is only given to facilitate
  // compilation.  You should replace it with appropriate code, very
  // similar to what you had done in lab assignment 3.
  //
  // You can look at the implementation of insert to code this part up.
    TreeNode* temp= find_node(JourneyCode,price);      
    if(temp == NULL) return false;
    else return true;  
}

// Finds Succesor of the node
struct TreeNode* BST::find_succ(int JourneyCode, int price){
    TreeNode* temp = find_node(JourneyCode, price);
    temp=temp->right;    
    while(temp->left != NULL && temp->price > price){
        temp = temp->left;
    }  
    return temp;
}

// helps in removing an entry
void BST::remove_helper(TreeNode* temp,TreeNode* temp2){
    if(temp->right != temp2){
        if(temp2->right != NULL){
            temp2->parent->left = temp2->right;
            temp2->right->parent = temp2->parent;
            updator(temp2->right);                         
        }
        else if(temp2->right == NULL){
            temp2->parent->left = NULL;
            if(temp2->parent->right != NULL){
                updator(temp2->parent->right);                
            }
            else{
                temp2->parent->longestPathLength = 0;
                temp2->parent->shortestPathLength = 0;
                updator(temp2->parent);            
            }
        }
        temp2->right = temp->right;
        if(temp->right != NULL)                    
        temp->right->parent = temp2;
    }

    temp2->left = temp->left;
    if(temp->left != NULL)
    temp->left->parent = temp2;
}

// Returns false, if JourneyCode isn't present
// Deletes the corresponding entry and returns True otherwise
bool BST::remove(int JourneyCode, int price) { 
      
    // The following filler code snippet is only given to facilitate
    // compilation.  You should replace it with appropriate code, very
    // similar to what you had done in lab assignment 3.
    //
    // Recall from CS 213 lectures about the various ways in which the
    // BST can be restructured when a node is deleted. You can implement
    // any of these alternatives.
    //
    // Do not forget to update shortestPathLength and
    // longestPathLength of (possibly all) BST nodes in the
    // path from the root to nodes whose position in the BST is affected
    // by the remove.
    TreeNode* temp= find_node(JourneyCode,price);        
    if(temp == NULL ){
        return false;
    }    
    else{        
        if(temp->parent->left == temp){
            if(temp->left == NULL && temp->right == NULL){
                temp->parent->left = NULL;     
                if(temp->parent->right == NULL){
                    temp->parent->longestPathLength=0;
                    temp->parent->shortestPathLength=0;
                }       
                else{
                    temp->parent->longestPathLength = 1+temp->parent->right->longestPathLength;
                    temp->parent->shortestPathLength = 1+temp->parent->right->shortestPathLength;
                } 
                updator(temp->parent);   
            }
            else if(temp->left == NULL ){
                temp->parent->left = temp->right;
                temp->right->parent = temp->parent;
                updator(temp->right);
            }
            else if(temp->right == NULL){
                temp->parent->left = temp->left;
                temp->left->parent = temp->parent;
                updator(temp->left);
            }      
            else {           
                TreeNode* temp2 = find_succ(JourneyCode,price);  
                bool b = (temp->right == temp2);                    
                remove_helper(temp,temp2);                                              
                temp2->parent = temp->parent;
                temp->parent->left = temp2;      
                temp2->longestPathLength =temp->longestPathLength;
                temp2->shortestPathLength = temp->shortestPathLength;  
                if(b) updator(temp->left);                                                                                                                                                              
            } 
        }              
        if(temp->parent->right == temp){            
            if(temp->left == NULL && temp->right == NULL){
                temp->parent->right = NULL;
                if(temp == root) root = NULL;  
                else if(temp->parent->right == NULL){
                    temp->parent->longestPathLength=0;
                    temp->parent->shortestPathLength=0;
                }       
                else{
                    temp->parent->longestPathLength = 1+temp->parent->right->longestPathLength;
                    temp->parent->shortestPathLength = 1+temp->parent->right->shortestPathLength;
                }       
                updator(temp->parent);      
            }
            else if(temp->left == NULL){
                temp->parent->right = temp->right;
                temp->right->parent = temp->parent;
                if(temp == root) root = temp->right;
                else{
                    updator(temp->right);
                }
            }
            else if(temp->right == NULL){
                temp->parent->right = temp->left;
                temp->left->parent = temp->parent;
                if(temp == root) root = temp->left;
                else{
                    updator(temp->left);
                }
            }    
            else{        
                TreeNode* temp2 = find_succ(JourneyCode,price); 
                bool b = (temp->right == temp2);                             
                remove_helper(temp,temp2);                
                temp2->parent = temp->parent;
                temp->parent->right = temp2;  
                temp2->longestPathLength =temp->longestPathLength;
                temp2->shortestPathLength = temp->shortestPathLength;  
                if(temp == root) root = temp2;    
                if(b) updator(temp->left);                         
            }            
        } 
        delete temp;      
        return true;
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

