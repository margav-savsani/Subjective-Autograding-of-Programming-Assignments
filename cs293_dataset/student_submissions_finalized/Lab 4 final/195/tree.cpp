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
int TreeNode::shortest(TreeNode* c){
           if(c->left==NULL && c->right==NULL){
              return 1;
              }
           else if(c->left==NULL || c->right==NULL){
                if(c->left==NULL){
                   int p=shortest(c->right);
                   return 1+p;
                   }
                else{
                   int k=shortest(c->left);
                   return 1+k;
                   }
                 }
           else{
              int a=shortest(c->left);
              int b=shortest(c->right);
              if(a<b){
                 return 1+a;
                 }
              else{
                 return 1+b;
                 }
             }
          }
int  TreeNode::longest(TreeNode* c){
            if(c->left==NULL && c->right==NULL){
              return 1;
              }
            else if(c->left==NULL || c->right==NULL){
               if(c->left==NULL){
                   int p=longest(c->right);
                   return 1+p;
                  }
               else{
                   int k=longest(c->left);
                   return 1+k;
                   }
               }
           else{
              int a=longest(c->left);
              int b=longest(c->right);
              if(a>b){
                 return 1+a;
                 }
              else{
                 return 1+b;
                 }
             }
          }
bool BST::insert(int JourneyCode, int price)
{
    TreeNode* c;
        c=new TreeNode(JourneyCode,price);
        if(find(JourneyCode,price)){
           return false;
           }
        else{
         if(root==nullptr){
            root=c;
            return true;
            }
         else{
             TreeNode* d=root;
             TreeNode* e=nullptr;
             while(d!=nullptr){
                e=d;
                if(d->price>price){
                   d=d->left;
                   }
                 else{
                   d=d->right;
                   }
                }
             c->parent=e;
             if(e==nullptr){
                root=c;
                return true;
                }
       
                else if(e->price>c->price){
                    e->left=c;
                    return true;
                    }
                else{
                  e->right=c;
                  return true;
                  }         
           }
         }
              }
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
  

// Return True, if the ticket with given attributes is found, false otherwise
bool BST::find(int JourneyCode, int price)
{
    if(root==nullptr){
       return false;
       }
     else{
       TreeNode* x=root;
       while(x!=nullptr){
         if(x->JourneyCode==JourneyCode && x->price==price){
           return true;
           }
         else{
           if(x->price>price){
             x=x->left;
             }
           else{
             x=x->right;
             }
           }
         }
       return false;
      }
              
 }
  // The following filler code snippet is only given to facilitate
  // compilation.  You should replace it with appropriate code, very
  // similar to what you had done in lab assignment 3.
  //
  // You can look at the implementation of insert to code this part up.
  
	
// Returns false, if JourneyCode isn't present
// Deletes the corresponding entry and returns True otherwise
bool BST::remove(int JourneyCode, int price)
{
     if(find(JourneyCode,price)==false){
        return false;
    }
    TreeNode *currNode=root;
    TreeNode *k;
        while(currNode!=nullptr){
            if(currNode->price==price && currNode->JourneyCode==JourneyCode){
                break;
            }
            else if(currNode->price>price){
                currNode=currNode->left;
            }
            else{
                currNode=currNode->right;
            }
        }
     TreeNode* f=currNode;
    if(currNode->left==nullptr && currNode->right==nullptr){
        if(currNode==root){
            root=nullptr;
            return true;
        }
        if(currNode->parent->left==currNode){
            currNode->parent->left=nullptr;
            currNode=nullptr;
            return true;
        }
        else{
            currNode->parent->right=nullptr;
            currNode=nullptr;
            return true;
        }
    }
    else if(f->right==nullptr || f->left==nullptr){
                  if(f->left!=nullptr){
                      if(f==root){
                         root->left->parent=nullptr;
                         root=root->left;
                         return true;
                         }
                      else{
                         if(f->parent->right==f){
                            f->left->parent=f->parent;
                            f->parent->right=f->left;
                            f=nullptr;
                            return true;
                            }
                         else{
                            f->left->parent=f->parent;
                            f->parent->left=f->left;
                            f=nullptr;
                            return true;
                            }
                         }
                      }
                   else{
                      if(f==root){
                         root->right->parent=nullptr;
                         root=root->right;
                         return true;
                         }
                      else{
                         if(f->parent->right==f){
                            f->right->parent=f->parent;
                            f->parent->right=f->right;
                            return true;
                            }
                          else{
                            f->right->parent=f->parent;
                            f->parent->left=f->right;
                            return true;
                            }
                         }
                      }
                   }
    else{
               k=f->left;
                   while(k->right!=nullptr){
                     k=k->right;
                     }
                  if(f!=root){
                   if(k->left!=nullptr){
                       if(k->parent->right==k){
                          k->parent->right=k->left;
                          k->left->parent=k->parent;
                              f->JourneyCode=k->JourneyCode;
                              f->price=k->price;
                              return true;
                          }
                       else{
                          k->parent->left=k->left;
                          k->left->parent=k->parent;
                          f->JourneyCode=k->JourneyCode;
                          f->price=k->price;
                          return true;
                          }
                        }
                     else{
                        if(k->parent->right==k){
                            k->parent->right=nullptr;
                            f->JourneyCode=k->JourneyCode;
                            f->price=k->price;
                            return true;
                             }
                        else{
                          k->parent->left=nullptr;
                          f->JourneyCode=k->JourneyCode;
                          f->price=k->price;
                          return true;
                          }
                         }
                       }
                     if(f==root){
                        if(k->left!=nullptr){
                          if(k->parent->right==k){
                            k->parent->right=k->left;
                            k->left->parent=k->parent;
                            root->JourneyCode=k->JourneyCode;
                            root->price=k->price;
                            k=nullptr;
                            return true;
                            }
                          else{
                             root->left=k->left;
                             k->left->parent=root;
                             root->JourneyCode=k->JourneyCode;
                             root->price=k->price;
                             k=nullptr;
                             return true;
                             }
                          }
                        else{
                           if(k->parent->right==k){
                                k->parent->right=nullptr;
                                root->JourneyCode=k->JourneyCode;
                                root->price=k->price;
                                k=nullptr;
                                return true;
                                }
                           else{
                               root->left=nullptr;
                               root->JourneyCode=k->JourneyCode;
                               root->price=k->price;
                               k=nullptr;
                               return true;
                               }
                            }
                          }
                      }
     
	         }
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

