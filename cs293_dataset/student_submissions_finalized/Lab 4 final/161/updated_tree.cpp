// Code up the functions defined in tree.h
// Reuse the binary Search Tree implemented in lab 3 as much as possible

#include <bits/stdc++.h>
#include <iostream>
#include <vector>
#include <string>

using namespace std;

#include "updated_tree.h"

// PLEASE FILL IN THE BODIES OF THE FOLLOWING FUNCTIONS

// Returns false, if given JourneyCode is already present in the BST
// Inserts the element and returns True otherwise

// BST::BST(){
//   cout<<"1st one"<<endl;
//     this->root = NULL; 
//     }
// BST::BST(TreeNode *root){
//   cout<<"2nd one"<<endl;
//     this->root = root; 
//     this->root->parent = NULL;
//   }

int BST::getImbalance()
{
  if (root == nullptr) return 0;
  else return root->getImbalance();
}

bool BST::insert(int JourneyCode, int price)
{
  // cout<<"hmm"<<JourneyCode<<endl;
  // The following filler code snippet is only given to facilitate
  // compilation.  You should replace/augment it with appropriate code,
  // similar to what you had done in lab assignment 3.

    TreeNode* x = this->root; //for checking
    TreeNode* y = NULL; //for pointing to the parent
    TreeNode* node = new TreeNode(JourneyCode, price, NULL, NULL, NULL);
    node->shortestPathLength = 0;
    node->longestPathLength = 0;
    if(this->root == NULL){
        this->root = node;
        root->longestPathLength = 0;
        root->shortestPathLength = 0;
        return true;
    }

    while(x != NULL){
        // cout<<"x not null";
        y = x;
        // if(x->JourneyCode == JourneyCode){
        //     return false;
        // }
        if(x->JourneyCode > JourneyCode){
            x = x->left;
        }
        else{
            x = x->right;
        }
    }
    node->parent = y;

    if(y->JourneyCode > JourneyCode){
        y->left = node;
    }
    else{
        y->right = node;
    }
    TreeNode *otherchild;
    x=node;
    while(y!=NULL){

        if(x==y->left)
          otherchild = y->right;
        else
          otherchild = y->left;

        if(otherchild==NULL){
          y->shortestPathLength = 0;
          y->longestPathLength = x->longestPathLength + 1;
        }
        else{
          if(otherchild->shortestPathLength > x->shortestPathLength){
            y->shortestPathLength = x->shortestPathLength + 1;
          }
          else{
            y->shortestPathLength = otherchild->shortestPathLength + 1;
          }

          if(otherchild->longestPathLength < x->longestPathLength){
            y->longestPathLength = x->longestPathLength + 1;
          }
          else{
            y->longestPathLength = otherchild->longestPathLength + 1;
          }
        }
         x = y;
         y = y->parent;
         
    }


    
  // JourneyCode is not present in the BST.  We must now
  // insert an appropriate child of parentOfCurrNode.
  // Please implement this part yourself.
  //
  // Do not forget to update shortestPathLength and
  // longestPathLength of (possibly all) BST nodes in the
  // path from the root to the new node you are inserting
  
  
  return true;
}

// Return True, if the ticket with given attributes is found, false otherwise
bool BST::find(int JourneyCode, int price)
{
  // The following filler code snippet is only given to facilitate
  // compilation.  You should replace it with appropriate code, very
  // similar to what you had done in lab assignment 3.
  //
  // You can look at the implementation of insert to code this part up.
  TreeNode* temp = root;

    while(temp != NULL){
        if(temp->price == price && temp->JourneyCode==JourneyCode){
            return true;
        }
        if(temp->price > price){
            temp = temp->left;
        }
        else{
            temp = temp->right;
        }
    }
  
  return false;
}
	
// Returns false, if JourneyCode isn't present
// Deletes the corresponding entry and returns True otherwise
bool BST::remove(int JourneyCode, int price)
{
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
    
    if( !BST::find(JourneyCode,price) ){
        return false;
    }
    else{
        TreeNode* temp = root;
        TreeNode* x = NULL;

        while( temp->JourneyCode!=JourneyCode && temp!=NULL ){
            if(temp->price > price ){
                temp = temp->left;
            }
            else{
                temp = temp->right;
            }
        }
        if(temp==NULL) //if by any chance not found 
            return false;

        if(temp->JourneyCode == JourneyCode){ //node to be deleted is found, its temp

            //------when temp is the leaf------
            if(temp->left==NULL && temp->right==NULL){ 
                
                if(temp->parent==NULL){ //deleting root node
                    root = NULL; //tree deleted
                    return true;
                }
                if(temp->parent->left == temp){ //temp is the leftchild of its parent
                    temp->parent->left = NULL; //temp deleted
                    return true;
                }
                else{ 
                    temp->parent->right = NULL; //temp being rightchild
                    return true;
                }
            } 
            //---------temp has only one child--------
            else if(temp->left==NULL || temp->right==NULL){

                TreeNode* p,  *notNullChild;
                p = temp->parent;  //p is the parent of temp

                //notNullChild is the only not NULL child of temp
                if(temp->left==NULL){
                    notNullChild=temp->right;
                }
                else{
                    notNullChild = temp->left;
                }
         
                if(p==NULL){
                    root = notNullChild;
                    root->parent=NULL;
                    return true;
                }
                // cout<<"oh no";
                if(p->left == temp){ //temp is the leftchild of p
                    p->left =  notNullChild;
                    notNullChild->parent = p;
                    return true;
                }
                else{ //temp being right child  
                    p->right = notNullChild;
                    notNullChild->parent = p;
                    return true;
                }
            }
            //---------temp has two children---------
            else{

                TreeNode* suc = BST::succ(temp);
                bool yes = BST::remove(suc->JourneyCode, suc->price);
                if(!yes)
                    return false;
                temp->JourneyCode = suc->JourneyCode;
                temp->price = suc->price;
                return true;
            }

        }

    }  

  return false;
}

TreeNode* BST::succ( TreeNode* x){
    if(x->right!=NULL)
        return BST::getMinimum(x->right);
    else{
        TreeNode* y = x->parent;
        if(y==NULL)
            return NULL;
        while( y != NULL && x==y->right){
            x=y;
            y=y->parent;
        }
        return y;
    }
}

TreeNode* BST::getMinimum(TreeNode* t){
    TreeNode* temp = t;
    TreeNode* temp2 = NULL;

    if(temp==NULL){
        return NULL;
    }

    while( temp != NULL){
        temp2 = temp;
        temp = temp->left;
    }
    
    return temp2; 
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

