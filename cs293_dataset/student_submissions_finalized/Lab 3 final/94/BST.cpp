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


// PLEASE FILL IN THE BODIES OF THE FOLLOWING FUNCTIONS
TreeNode*f;
TreeNode*m;
BST::BST(){
    root=NULL; }
BST::BST(TreeNode *root){
    this->root=root; }

// Returns false, if given JourneyCode is already present in the BST
// Inserts the element and returns True otherwise
bool BST::insert(int jc, int pr) { 

    if(find(jc,pr)) return false;
    else{
        if(root==NULL){
            root=new TreeNode(jc,pr);
            root->parent=NULL;
        }
        else{
            insert_help(jc,pr,root);
        }
        return true;
    }
}
void BST::insert_help(int jc, int pr,TreeNode*r1){
    if(pr<=r1->price){
        if(r1->left==NULL){
            r1->left=new TreeNode(jc,pr);
            r1->left->parent=r1;
        }
        else insert_help(jc,pr,r1->left);
    }
    else{
        if(r1->right==NULL){
            r1->right=new TreeNode(jc,pr);
            r1->right->parent=r1;
        }
        else insert_help(jc,pr,r1->right);

    }
} 


// Return True, if the ticket with given attributes is found, false otherwise
bool BST::find(int jc, int pr) { 
    TreeNode* r=root;
    return find_help(jc,pr,r);
}
bool BST::find_help(int jc,int pr,TreeNode*r1){
    TreeNode*r=r1;
    if(r==NULL) return false;
    if(r->JourneyCode==jc){ 
        f=r;
        return true;
    }

    if(r->JourneyCode!=jc && r->left==NULL && r->right==NULL)
        {return false;}
    else{
        if(pr<=r->price){
            return find_help(jc,pr,r->left);
            return find_help(jc,pr,r->right);
            

        }
        else {
            return find_help(jc,pr,r->right);
        }
    }

}
	
// Returns false, if JourneyCode isn't present
// Deletes the corresponding entry and returns True otherwise
bool BST::remove(int jc, int pr) { 
    if(!find(jc,pr)) return false;
    else{
        if(f==root){
            if(m==NULL){
                root=NULL;
                return true;
            }
            if(m->right==NULL){
                cout<<"reached"<<endl;
                TreeNode*mp=m->parent;
                root->JourneyCode=m->JourneyCode;
                root->price=m->price;
                mp->left=NULL;
            }
            else{
                TreeNode*mp=m->parent;
                TreeNode*mr=m->right;
                root->JourneyCode=m->JourneyCode;
                root->price=m->price;
                mp->left=mr;
                mr->parent=mp;
            }
            return true;
        }
        TreeNode*p=f->parent;

        bool right;
        if(p->price<f->price) right=true;
        else right=false;

        if(f->left==NULL && f->right==NULL){
            if(right){
                p->right=NULL;
            }
            else p->left=NULL;
        }
        if(f->left!=NULL && f->right==NULL){
            TreeNode*l=f->left;
            if(right){
                p->right=l;
                l->parent=p;
            }
            else{
                p->left=l;
                l->parent=p;
            }
        }
        if(f->left==NULL && f->right!=NULL){
            TreeNode*l=f->right;
            if(right){
                p->right=l;
                l->parent=p;
            }
            else{
                p->left=l;
                l->parent=p;
            }
            
        }
        if(f->left!=NULL && f->right!=NULL){
            mintree(f->right);
            if(m->right==NULL){
                TreeNode*mp=m->parent;
                if(right){
                    p->right=m;
                    m->parent=p;
                    m->right=f->right;
                    m->left=f->left;
                    mp->left=NULL;
                }
                else{
                    p->left=m;
                    m->parent=p;
                    m->left=f->left;
                    m->right=f->right;
                    mp->left=NULL;
                }
            }
            else{
                TreeNode*mr=m->right;
                TreeNode*mp=m->parent;
                if(right){
                    p->right=m;
                    m->parent=p;
                    m->left=f->left;
                    m->right=f->right;
                    mp->left=mr;

                }
                else{
                    p->left=m;
                    m->parent=p;
                    m->left=f->left;
                    m->right=f->right;
                    mp->left=mr;

                }


            }
        }
    return true;
    }
}
	
// Functions that traverse the BST in various ways!
// type is one of PRE_ORDER, POST_ORDER or IN_ORDER
// Print on cout the journey codes at nodes of the BST in the same order as
// they are encountered in the traversal order
// Print one journey code per line

void BST::traverse(int typeOfTraversal) {
    if(typeOfTraversal==0){ //pre
        pre_traverse(root);

    }
    if(typeOfTraversal==1){ //post
        post_traverse(root);
    }
    if(typeOfTraversal==2){ //in
        in_traverse(root);
    }
}
void BST::pre_traverse(TreeNode*r){
    if(r==NULL) return;
    if(r!=NULL) cout<<r->price<<" "<<endl;
    pre_traverse(r->left);
    pre_traverse(r->right);
    
}
void BST::post_traverse(TreeNode*r){
    if(r==NULL) return;
    post_traverse(r->left);
    post_traverse(r->right);
    if(r!=NULL) cout<<r->price<<" "<<endl;
    
}
void BST::in_traverse(TreeNode*r){
    if(r==NULL) return;
    in_traverse(r->left);
    if(r!=NULL) cout<<r->price<<" "<<endl;
    in_traverse(r->right);
    
}

// Returns the price of the cheapest journey
int BST::getMinimum() {
    TreeNode*r=root;
    int val;
    if(root!=NULL){
        while(true){
            if(r->left==NULL){
                m=r;
                return r->price;
            }
                r=r->left;
        }
    }
}
void BST::mintree(TreeNode*r1){
    TreeNode*r=r1;
    if(r!=NULL){
        while(true){
            if(r->left==NULL){
                m=r;
                break;
            }
                r=r->left;
        }
    }
    else{
        m=NULL;
    }

}


// Part II

// Returns the count of journeys that are at least as expensive
// as lowerPriceBound and at most as expensive as upperPriceBound,
// both bounds included.
int BST::countJourneysInPriceBound(int lowerPriceBound, int upperPriceBound) {
    int c=0;
     return count(lowerPriceBound,upperPriceBound,root,c);
}
int BST::count(int lowerPriceBound, int upperPriceBound,TreeNode*r,int& c) {
    if(r==NULL){
        return c;
    }
    if(r->price==lowerPriceBound){
        c++;
        return count(lowerPriceBound,upperPriceBound,r->right,c);
    }
    if(r->price==upperPriceBound){
        c++;
        return count(lowerPriceBound,upperPriceBound,r->left,c);
    }
    if(r->price>upperPriceBound){
        return count(lowerPriceBound,upperPriceBound,r->left,c);
    }
    if(r->price<lowerPriceBound){
        return count(lowerPriceBound,upperPriceBound,r->right,c);
    }
    if(r->price>lowerPriceBound && r->price<upperPriceBound){
        int l=count(lowerPriceBound,r->price,r->left,c);
        int k=count(r->price,upperPriceBound,r->right,c);
        return l+k+1;
    }
    
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

