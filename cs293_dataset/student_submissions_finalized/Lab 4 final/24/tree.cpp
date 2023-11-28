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
 BST::BST() {root = nullptr; }
 BST::BST(TreeNode * curr_root) {root = curr_root;}

int BST::shorter(TreeNode* r){
  
    if(r==nullptr){return 0;}
    else if((r->left=nullptr)&&(r->right=nullptr)){return 1;}
    
    if(r->left=nullptr){
      return 1+shorter(root->right);
    } 
    if(r->right=nullptr){
      return 1+shorter(root->left);
    } 
    return 1+min(shorter(root->right),shorter(root->left));
}

int BST::longer(TreeNode* r){
  
    if(r==nullptr){return 0;}
    else if((r->left=nullptr)&&(r->right=nullptr)){return 1;}
    if(r->left=nullptr){
      return 1+longer(root->right);
    } 
    if(r->right=nullptr){
      return 1+longer(root->left);
    } 
    return 1+max(longer(root->right),longer(root->left));
}

int BST::getImbalance()
{
  if (root == nullptr) return 0;
  else return root->getImbalance();
}

void BST :: setforall(TreeNode* x){
    TreeNode * y=x;
    if(y==nullptr)return;
    else{
        y->longestPathLength=longer(x);
        y->shortestPathLength=shorter(x);
        setforall(y->left);
        setforall(y->right);
    }
}
bool BST::insert(int JourneyCode, int price){

  TreeNode *parentOfCurrNode=nullptr;
  TreeNode *currNode=root;

  if(find(JourneyCode,price)){ 
    return false;
  }
  else{
    while(currNode!=nullptr){
      parentOfCurrNode=currNode;
      if(JourneyCode <  currNode->JourneyCode){
        currNode=currNode->left;
      }
      else {
        currNode=currNode->right;
      }
    }
    TreeNode *z=new TreeNode(JourneyCode,price);
    z->parent=parentOfCurrNode;
    if(parentOfCurrNode==nullptr){
      root=z;
    }
    else if(z->JourneyCode < parentOfCurrNode->JourneyCode){
      parentOfCurrNode->left=z;
    }
    else{
      parentOfCurrNode->right=z;
    }

    //cout<<"inserted....."<<endl;
    //cout<<"gt";
    setforall(root);
    //cout<<"insert"<<endl;
    return true;
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
  TreeNode * s;
    s=root;
    //if(s==nullptr) return false;
    while(s!=NULL){
        //cout<<"entersed while loop  in find"<<endl;
        if((s->price==price) && (s->JourneyCode==JourneyCode)){
            return true;
        }
        else if(JourneyCode< s->JourneyCode){
            s=s->left;
        }
        else{
            s=s->right;
        }
    }
    return false;
  // The following filler code snippet is only given to facilitate
  // compilation.  You should replace it with appropriate code, very
  // similar to what you had done in lab assignment 3.
  //
  // You can look at the implementation of insert to code this part up.
}
	
// Returns false, if JourneyCode isn't present
// Deletes the corresponding entry and returns True otherwise
TreeNode* BST :: nextto(TreeNode* x){
    if(x->right!=nullptr){
        return mini(x->right);
    }
    TreeNode* p=x->parent;
    while((x=p->right)&&(p!=nullptr)){  //parent null case missed
        //cout<<"nknj"<<endl;
        x=p;
        p=p->parent;
    }
    return p;
}
TreeNode* BST :: mini(TreeNode *x){
    while(x->left!=nullptr){
        x=x->left;
    }
    return x;
}
bool BST::remove(int JourneyCode, int price)
{
  if(find(JourneyCode,price)){
        TreeNode *c;
        c=root;
        //cout<<"entered remove function"<<endl;
        while(true){
            if (c==nullptr) return false;//ROOT NULL ......................
            else if((c->price==price) && (c->JourneyCode==JourneyCode)){
                //cout<<"fnke";

                //no kids case
                if((c->right==nullptr)&&(c->left==nullptr)){
                    if(c->parent!=nullptr){
                        if((c->parent)->price < c->price) (c->parent)->right=nullptr;
                        else c->parent->left=nullptr;
                    }
                else c=NULL;
                delete c;
                }
                
                //one kid case
                else if((c->right==nullptr)&&(c->left!=nullptr)){
                    //cout<<"njf1";
                    if(c->parent!=nullptr){
                        if((c->parent)->price < c->price) (c->parent)->right=c->left;
                        else (c->parent)->right=c->right;
                    }
                else root=c->left;
                delete c;
                }
                else if((c->right!=nullptr)&&(c->left==nullptr)){
                    //cout<<"njf2";
                    if(c->parent!=NULL){
                        if((c->parent)->price < c->price) (c->parent)->left=c->left;
                        else (c->parent)->left=c->right;
                    }
                else root=c->right;
                delete c;
                }

                //two kids cases
                else{
                    //cout<<"entered two kids case";
                    TreeNode *d=nextto(c); //successor
                    //cout<<"hvvhjvj";
                    int p=d->JourneyCode;
                    int q=d->price;
                    remove(d->JourneyCode,d->price);
                    c->price=q;
                    c->JourneyCode=p;

                }
            return true;
            }
     {
        if(c->price>price)c=c->left;
        else c=c->right;
     }
        }
       // return false;
    }

    else{
       return false;
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

