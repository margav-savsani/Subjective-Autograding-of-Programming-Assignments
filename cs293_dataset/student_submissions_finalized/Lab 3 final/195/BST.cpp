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


//LEASE FILL IN THE BODIES OF THE FOLLOWING FUNCTIONS

BST::BST(){
  root=nullptr;
   }
BST::BST(TreeNode *root1){
       root=root1; 
       }

// Returns false, if given JourneyCode is already present in the BST
// Inserts the element and returns True otherwise
bool BST::insert(int JourneyCode, int price) {
        TreeNode* c;
        c=new TreeNode(JourneyCode,price);
         if(find(JourneyCode, price)){
             return false;
             }
        else{
             TreeNode* a=root;
            TreeNode* b=NULL;
           while(a!=NULL){
               b=a;
               if(c->price<a->price){
                   a=a->left;
                   }
               else{
                   a=a->right;
                   }
                 }
              c->parent=b;
              if(b==NULL){
                 root=c;
                 return true;
                 }
              else if(c->price<b->price){
                   b->left=c;
                   return true;
                   }
               else{
                   b->right=c;
                   return true;
                   }
                 }
          }
// Return True, if the ticket with given attributes is found, false otherwise
bool BST::find(int JourneyCode, int price) { 
   if(root!=NULL){
            if(root->JourneyCode==JourneyCode){
                 return true;
                 }
            else{
                if(root->price>price){
                    TreeNode* y=root->left;
                    while(y!=NULL){
                       if(y->JourneyCode==JourneyCode){
                         return true;
                         }
                       else{
                         if(y->price>price){
                            y=y->left;
                            }
                         else{
                            y=y->right;
                            }
                         }
                        }
                       return false;
                    }
                else{
                   TreeNode* y=root->right;
                    while(y!=NULL){
                       if(y->JourneyCode==JourneyCode){
                         return true;
                         }
                       else{
                         if(y->price>price){
                            y=y->left;
                            }
                         else{
                            y=y->right;
                            }
                         }
                        }
                       return false;
                   }
               }
              }
            else{
              return false;
              }
 }
  
	
// Returns false, if JourneyCode isn't present
// Deletes the corresponding entry and returns True otherwise
bool BST::remove(int JourneyCode, int price){ 
          TreeNode* f=NULL;
          TreeNode* k;
          if(!(find(JourneyCode,price))){
              return false;
              }
          else{
             if(root->price==price){
                   f=root;
                   }
             else if(root->price>price){
                 TreeNode* y=root->left;
                  if(y->price==price){
                     f=y;
                     }
                  while(y->price!=price){
                   if(y->price>price){
                      y=y->left;
                      }
                   else{
                      y=y->right;
                      }
                   }
                 if(f==NULL){
                    f=y;
                    }
                 }
             else{
                TreeNode* y=root->right;
                 if(y->price==price){
                   f=y;
                   }
                 while(y->price!=price){
                   if(y->price>price){
                     y=y->left;
                     }
                   else{
                     y=y->right;
                     }
                   }
                 if(f==NULL){
                   f=y;
                   }
                }
             if(f->right==NULL && f->left==NULL){
                 if(f==root){
                  root=NULL;
                  return true;
                  }
                 else{
                    if(f->parent->right==f){
                        f->parent->right=NULL;
                        f=NULL;
                        return true;
                        }
                    else{
                        f->parent->left=NULL;
                        f=NULL;
                        return true;
                        }
                     }
                  }
             else if(f->right==NULL || f->left==NULL){
                  if(f->right!=NULL){
                      if(f==root){
                          root=f->right;
                          f->right->parent=NULL;
                          f=NULL;
                          return true;
                          }
                      else{
                         if(f->parent->right==f){
                           f->parent->right=f->right;
                           f->right->parent=f->parent;
                            f=NULL;
                            return true;
                            }
                         else{
                            f->parent->left=f->right;
                            f->right->parent=f->parent;
                            f=NULL;
                            return true;
                            }
                          }
                       }
                    else{
                       if(f==root){
                          root=f->left;
                          f->left->parent=NULL;
                          f=NULL;
                          return true;
                          }
                       else{
                          if(f->parent->right==f){
                            f->parent->right=f->left;
                            f->left->parent=f->parent;
                            f=NULL;
                            return true;
                            }
                          else{
                            f->parent->left=f->left;
                            f->left->parent=f->parent;
                            f=NULL;
                            return true;
                            }
                          }
                      }
                    }
                  else{
                     TreeNode* s=f->left;
                     while(s->right!=NULL){
                       s=s->right;
                       }
                      k=s;
                    if(f->left==k){
                          f->JourneyCode=k->JourneyCode;
                          f->price=k->price;
                          f->left=k->left;
                          if(k->left==NULL){
                            return true;
                            }
                          else{
                            k->left->parent=f;
                            return true;
                            }
                        }
                    else{
                     if(k->parent->right==k){
                      if(k->left!=NULL){
                         k->parent->right=k->left;
                         k->left->parent=k->parent;
                         if(f!=root){
                            if(f->parent->left==f){
                                f->parent->left=k;
                                f->left->parent=k;
                                f->right->parent=k;
                                k->right=f->right;
                                k->left=f->left;
                                return true;
                                }
                            else{
                                f->parent->right=k;
                                f->left->parent=k;
                                f->right->parent=k;
                                k->right=f->right;
                                k->left=f->left;
                                return true;
                                }
                             }
                          if(f==root){
                             root->JourneyCode=k->JourneyCode;
                             root->price=k->price;
                             return true;
                             }
                           }
                        if(k->left==NULL){
                           k->parent->right=NULL;
                           if(f!=root){
                              if(f->parent->left==f){
                                f->parent->left=k;
                                f->left->parent=k;
                                f->right->parent=k;
                                k->right=f->right;
                                k->left=f->left;
                                return true;
                                }
                            else{
                                f->parent->right=k;
                                f->left->parent=k;
                                f->right->parent=k;
                                k->right=f->right;
                                k->left=f->left;
                                return true;
                                }
                            }
                            if(f==root){
                             root->JourneyCode=k->JourneyCode;
                             root->price=k->price;
                             root->right=k->right;
                             k->right->parent=root;
                             return true;
                             }
	                  }
	                 }
	                if(k->parent->left==k){
	                    if(f!=root){
	                       if(f->parent->left==f){
	                          f->parent->left=k;
	                          k->left=NULL;
	                          f->right->parent=k;
	                          k->right=f->right;
	                          k->parent=f->parent;
	                          return true;
	                          }
	                       else{
	                          f->parent->right=k;
	                          k->left=NULL;
	                          f->right->parent=k;
	                          k->right=f->right;
	                          k->parent=f->parent;
	                          return true;
	                         }
	                       }
	                    if(f==root){
	                        root->JourneyCode=k->JourneyCode;
	                        root->price=k->price;
	                        root->left=k->left;
	                        k->left->parent=root;
	                        return true;
	                        }
	                }
	               }
	             }
	           }
	         }
// Functions that traverse the BST in various ways!
// type is one of PRE_ORDER, POST_ORDER or IN_ORDER
// Print on cout the journey codes at nodes of the BST in the same order as
// they are encountered in the traversal order
// Print one journey code per line

void BST::traverse(int typeOfTraversal) {
         if(typeOfTraversal==1){
             BST left(root->left);
             BST right(root->right);
              if(left.root!=NULL && right.root!=NULL){
                left.traverse(1);
                right.traverse(1);
                cout<<root->JourneyCode<<" ";
                }
              else if(left.root!=NULL){
                  left.traverse(1);
                  cout<<root->JourneyCode<<" ";
                  }
              else if(right.root!=NULL){
                   right.traverse(1);
                   cout<<root->JourneyCode<<" ";
                   }
              else{
                  cout<<root->JourneyCode<<" ";
                  }
              }
           else if(typeOfTraversal==0){
              BST left(root->left);
              BST right(root->right);
              if(left.root!=NULL && right.root!=NULL){
                cout<<root->JourneyCode<<" ";
                left.traverse(0);
                right.traverse(0);
                }
              else if(left.root!=NULL){
                  cout<<root->JourneyCode<<" ";
                  left.traverse(0);
                  }
              else if(right.root!=NULL){
                   cout<<root->JourneyCode<<" ";
                   right.traverse(0);
                   }
              else{
                  cout<<root->JourneyCode<<" ";
                  }
               }
           else if(typeOfTraversal==2){
                BST left(root->left);
                BST right(root->right);
                if(left.root!=NULL && right.root!=NULL){
                  left.traverse(2);
                  cout<<root->JourneyCode<<" ";
                  right.traverse(2);
                 }
                else if(left.root!=NULL){
                  left.traverse(2);
                  cout<<root->JourneyCode<<" ";
                  }
                else if(right.root!=NULL){
                  cout<<root->JourneyCode<<" ";
                  right.traverse(2);
                  }
                else{
                  cout<<root->JourneyCode<<endl;
                  }
                }
               }
// Returns the price of the cheapest journey
int BST::getMinimum() {
    TreeNode* d=root;
    if(d->left==NULL){
        return d->price;
        }
    else{
     while(d->left!=NULL){
        d=d->left;
        }
     return d->price;
     }
   }
 int t=0;

// Part II

// Returns the count of journeys that are at least as expensive
// as lowerPriceBound and at most as expensive as upperPriceBound,
// both bounds included.
void BST::travel(int x,int y){
           if(root->price>=x && root->price<=y){
                  t=t+1;
                  }
              BST left(root->left);
              BST right(root->right);
              if(left.root!=NULL && right.root!=NULL){
                left.travel(x,y);
                right.travel(x,y);
                }
              else if(left.root!=NULL){
                  left.travel(x,y);
                  }
              else if(right.root!=NULL){
                   right.travel(x,y);
                   }
              else{
                  return;
                  }
               }
int BST::countJourneysInPriceBound(int lowerPriceBound, int upperPriceBound) {
	t=0;
      travel(lowerPriceBound,upperPriceBound);
      return t;
           }
       
// Store the current tree in a file called filename.  You should
// store using a scheme that uses no more disk space than that
// required to store all elements in the BST, plus perhaps a small
// constant times the number of elements.  You should also store
// in a manner such that your implementation of customLoad is as
// memory and time efficient as possible.
void BST::customStore(string filename) { return; }
	
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
 
void BST::customLoad (int flag, string filename) { return; }


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

        result.push_back(isLeft ? "├──" : "└──" );

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

