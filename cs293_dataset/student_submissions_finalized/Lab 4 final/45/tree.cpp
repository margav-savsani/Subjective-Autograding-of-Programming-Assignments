// Code up the functions defined in tree.h
// Reuse the binary Search Tree implemented in lab 3 as much as possible

#include <bits/stdc++.h>
#include <iostream>
#include <vector>
#include <string>

using namespace std;

#include "tree.h"

// PLEASE FILL IN THE BODIES OF THE FOLLOWING FUNCTIONS

// Returns false, if given JourneyCode is already present in the BST
// Inserts the element and returns True otherwise

int BST::getImbalance()
{
  if (root == nullptr) return 0;
  else return root->getImbalance();
}

bool BST::insert(int JourneyCode, int price)
{
  // The following filler code snippet is only given to facilitate
  // compilation.  You should replace/augment it with appropriate code,
  // similar to what you had done in lab assignment 3.
  
  if(find(JourneyCode,price)){ return false;}
  else{
    
        if(root==nullptr){
            
            TreeNode* x;
            //x.JourneyCode=JourneyCode;
            //x.price=price;
            
            x=new TreeNode(JourneyCode, price);
            
            root=x; 
            
            root->parent=nullptr;
                        
        }
        else{
            if(root->JourneyCode < JourneyCode){
                if(root->right==nullptr){
                    (root->right) = new TreeNode(JourneyCode,price);     
                    (root->right)->parent=root;      
                }
                else{
                    BST b(root->right);
                    b.insert(JourneyCode,price);                    
                }
            }
            else if(root->JourneyCode > JourneyCode){
                if(root->left==nullptr){
                    (root->left) = new TreeNode(JourneyCode,price);     
                    (root->left)->parent=root;                                      
                }
                else{
                    BST b(root->left);
                    b.insert(JourneyCode,price);                   
                }
            }
        }
        return true;
  }
}


// Return True, if the ticket with given attributes is found, false otherwise
bool BST::find(int JourneyCode, int price) { 
        // finding the given element iteratively.
        TreeNode* x=root;
        while(x!=nullptr and x->price!=price){
            if(x->price > price){
                x=x->left;
            }
            else{
                x=x->right;
            }
        }
        if(x!=nullptr && x->price==price and x->JourneyCode==JourneyCode){
            return true;
        }
        else{return false;}  
}
	
// Returns false, if JourneyCode isn't present
// Deletes the corresponding entry and returns True otherwise
bool BST::remove(int JourneyCode, int price) {

    if(!find(JourneyCode,price)){return false;}
    // finding the location of node that is to be removed
    TreeNode* x=root;
    TreeNode* del;
    while(x!=nullptr and x->price!=price){
        if(x->price > price){
            x=x->left;
        }
        else{
            x=x->right;
        }
    }
    if(x!=nullptr && x->price==price and x->JourneyCode==JourneyCode){
        del=x;
    }
    // stored the node in variable called del.
    //in case of no children
    if(del->left==nullptr && del->right==nullptr){
        if(del->parent==nullptr){del=nullptr;root=del;}

        else if(del->parent!=nullptr){
            if(del->parent->price > del->price){del->parent->left=nullptr;}
            else if(del->parent->price < del->price){del->parent->right=nullptr;}
        }
    }
    //1child
    else if(del->left==nullptr && del->right!=nullptr){
        if(del->parent==nullptr){del=del->right;del->parent=nullptr;root=del;}

        else if(del->parent!=nullptr){
            if(del->parent->price > del->price){
                del->parent->left=del->right;
            }
            else if(del->parent->price < del->price){
                del->parent->right=del->right;
            }
            del->right->parent=del->parent;
        }
    }
    else if(del->left!=nullptr && del->right==nullptr){
        if(del->parent==nullptr){del=del->left;del->parent=nullptr;root=del;}

        else if(del->parent!=nullptr){
            if(del->parent->price > del->price){
                del->parent->left=del->left;
            }
            else if(del->parent->price < del->price){
                del->parent->right=del->left;
            }
            del->left->parent=del->parent;
        }
    }
    //2children
    else if(del->left!=nullptr && del->right!=nullptr){
        TreeNode* x=del->left; 
        while(x->right!=nullptr){
            x=x->right;
        }                                 // x is successor of del.
        int pri=x->price;              // store values of x in new variables
        int Jcode=x->JourneyCode;
        remove(x->JourneyCode,x->price);               // remove successor recursively
        del->price=pri;                     // overwrite value of root with above stored values.
        del->JourneyCode=Jcode;
    }
    return true;
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
