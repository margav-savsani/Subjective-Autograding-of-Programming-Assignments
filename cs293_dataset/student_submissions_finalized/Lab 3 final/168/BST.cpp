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


// PLEASE FILL IN THE BODIES OF THE FOLLOWING FUNCTIONS

BST::BST(){
    root=nullptr;
}

BST::BST(TreeNode *root){
    this->root=root;
}

// Returns false, if given JourneyCode is already present in the BST
// Inserts the element and returns True otherwise
bool BST::insert(int JourneyCode, int price){
    TreeNode nodeInsert(JourneyCode,price);
    if(!root){
        root=new TreeNode(nodeInsert);
        root->parent=nullptr;
        return true;
    }

    TreeNode* parentIns=nullptr;
    TreeNode* temp=root;

    while(temp){
        parentIns=temp;
        if(nodeInsert.price>temp->price){
            temp=temp->right;
        }
        else{
            temp=temp->left;
        }
    }

    if (parentIns->price>nodeInsert.price){
        nodeInsert.parent=parentIns;
        parentIns->left=new TreeNode(nodeInsert);
    }
    else{
        nodeInsert.parent=parentIns;
        parentIns->right=new TreeNode(nodeInsert);
    }
    return true;
}

// Return True, if the ticket with given attributes is found, false otherwise
bool BST::find(int JourneyCode, int price){
    if(!root){
        return false;
    }
    //cout<<"1a"<<endl;
    if(price==root->price && JourneyCode==root->JourneyCode){
        //cout<<"2"<<endl;
        return true;
    }
    TreeNode* temp=root;
    bool found=false;
    if(price>root->price){
        //cout<<"3a"<<endl;
        root=root->right;
        found=find(JourneyCode,price);
    }
    else{
        //cout<<"4"<<endl;
        root=root->left;
        found=find(JourneyCode,price);
    }
    root=temp;
    return found;
    //return find2(JourneyCode,price,root);
}

bool BST::find2(int Jcode,int price,TreeNode* node){
    if(node == nullptr){
        return false;
    }

    if (node->JourneyCode==Jcode && node->price==price){
        return true;
    }
    if (node->price>price){
        return find2(Jcode,price,node->left);
    }
    else{
        return find2(Jcode,price,node->right);
    }
    //return ((find2(Jcode,price,node->left)) || (find2(Jcode,price,node->right)));
}
	
// Returns false, if JourneyCode isn't present
// Deletes the corresponding entry and returns True otherwise
bool BST::remove(int JourneyCode, int price){
    //if(!find(JourneyCode,price)){
    if(!find(JourneyCode,price)){
        return false;
    }
    //basecase
    //cout<<"reached"<<endl;
    if((root->JourneyCode==JourneyCode)&&(root->price==price)){
        if(!((root->left) || (root->right))){
            //cout<<"1"<<endl;
            if(root->parent){
                if((root->parent)->price>root->price){
                    (root->parent)->left=nullptr;
                }
                else{
                    (root->parent)->right=nullptr;
                }
            }
            root=nullptr;

        }
        else if (!(root->left)){
            //cout<<"2"<<endl;
            if(root->parent){
                if((root->parent)->price>root->price){
                    (root->parent)->left=root->right;
                }
                else{
                    (root->parent)->right=root->right;
                }
            }
            root->right->parent=root->parent;
            root=root->right;
            
        }
        else if(!(root->right)){
            //cout<<"3"<<endl;
            if(root->parent){
                if((root->parent)->price>root->price){
                    (root->parent)->left=root->left;
                }
                else{
                    (root->parent)->right=root->left;
                }
            }
            (root->left)->parent=root->parent;
            root=root->left;
        }
        else{
            //cout<<"4"<<endl;
            TreeNode* minnode=getMinNode(root->right);
            int jcode=minnode->JourneyCode;
            int p=minnode->price;
            remove(minnode->JourneyCode,minnode->price);
            /*
            minnode->left=root->left;
            minnode->right=root->right;
            if (root->parent){  
                if((root->parent)->price>root->price){
                    (root->parent)->left=minnode;
                }
                else{
                    (root->parent)->right=minnode;
                }
            }
            minnode->parent=root->parent;
            root=minnode;
            */
           root->price=p;
           root->JourneyCode=jcode;
        }
        return true;
    }

    TreeNode* temp=root;
    if(root->price>price){
        root=root->left;
        remove(JourneyCode,price);
    }
    else{
        root=root->right;
        remove(JourneyCode,price);
    }
    root=temp;
    return true;
}
	
// Functions that traverse the BST in various ways!
// type is one of PRE_ORDER, POST_ORDER or IN_ORDER
// Print on cout the journey codes at nodes of the BST in the same order as
// they are encountered in the traversal order
// Print one journey code per line

void BST::traverse(int typeOfTraversal) {
    if (!root){
        return;
    }
    if(typeOfTraversal==0){
        //pre
        if(root){
            cout<<root->JourneyCode<<endl;
            TreeNode* temp=root;
            root=root->left;
            traverse(typeOfTraversal);
            root=temp->right;
            traverse(typeOfTraversal);
            root=temp;
            return;
        }
    }
    else if (typeOfTraversal==1){
        //post
        TreeNode* temp=root;
        root=root->left;
        traverse(typeOfTraversal);
        root=temp->right;
        traverse(typeOfTraversal);
        root=temp;
        cout<<root->JourneyCode<<endl;
        return;
    }
    else{
        //in
        TreeNode* temp=root;
        root=root->left;
        traverse(typeOfTraversal);
        cout<<temp->JourneyCode<<endl;
        root=temp->right;
        traverse(typeOfTraversal);
        root=temp;
        return;
    }
    cout<<endl;
}

// Returns the price of the cheapest journey
int BST::getMinimum(){
    if(!root){
        return -1;
    }

    TreeNode* temp=root;
    while(temp->left){
        temp=temp->left;
    }
    return temp->price;
}

TreeNode* BST::getMinNode(TreeNode* node){
    TreeNode* temp=node;
    while(temp->left){
        temp=temp->left;
    }
    return temp;
}


// Part II

int BST::intraverse(int low,int high,int count){
    if (!root){
        return count;
    }
    TreeNode* temp=root;
    root=root->left;
    int count1=intraverse(low,high,count);
    if(temp->price>=low && temp->price<=high){
        count1++;
    }
    root=temp->right;
    int count2=intraverse(low,high,count1);
    root=temp;
    return count2;
}

// Returns the count of journeys that are at least as expensive
// as lowerPriceBound and at most as expensive as upperPriceBound,
// both bounds included.
int BST::countJourneysInPriceBound(int lowerPriceBound, int upperPriceBound){
    return intraverse(lowerPriceBound,upperPriceBound,0);
}

string BST::prestore(){
    if(!root){
        return "N%";
    }
    string a,b,c;
    b=to_string(root->JourneyCode);
    b.push_back('|');
    c=to_string(root->price);
    a+=b+c;
    a.push_back('%');
    TreeNode* temp=root;
    root=root->left;
    a+=prestore();
    a.push_back('L');
    root=temp->right;
    a+=prestore();
    a.push_back('R');
    root=temp;
    return a;
}

// Store the current tree in a file called filename.  You should
// store using a scheme that uses no more disk space than that
// required to store all elements in the BST, plus perhaps a small
// constant times the number of elements.  You should also store
// in a manner such that your implementation of customLoad is as
// memory and time efficient as possible.
void BST::customStore(string filename){
    ofstream outf;
    outf.open(filename);
    outf<<prestore();
    outf.close();
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
 
void BST::customLoad (int flag, string filename){
    if(flag==3){
        string s;
        ifstream inf;
        inf.open(filename);
        inf>>s;
        string jcode,price;
        bool hit=false;
        TreeNode* curr=nullptr;
        //bool insertLeft=true;
        for (int i=0;i<s.length();i++){
            if(s[i]=='|'){
                hit=true;
            }
            else if (s[i]=='%'){
                if(jcode.compare("N")==0){
                    i+=1;
                    /*
                    if (s[i]=='L'){
                        insertLeft=false;
                    }
                    else{
                        insertLeft=true;
                    }
                    */
                }
                else{
                    //cout<<jcode<<" "<<price<<endl;
                    int jint=stoi(jcode);
                    int pint=stoi(price);
                    if(!curr){
                        root=new TreeNode(jint,pint);
                        curr=root;
                    }
                    else{
                        if(pint<curr->price){
                            curr->left=new TreeNode(jint,pint);
                            curr->left->parent=curr;
                            curr=curr->left;
                        }
                        else{
                            curr->right=new TreeNode(jint,pint);
                            curr->right->parent=curr;
                            curr=curr->right;
                        }
                    }
                }
                //we insert jint and pint
                
                //insert(jint,pint);
                //insert2(jint,pint,curr);
                jcode.clear();
                price.clear();
                hit=false;
            }
            else if(s[i]=='L'){
                //insertLeft=false;
                curr=curr->parent;
            }
            else if(s[i]=='R'){
                //insertLeft=true;
                curr=curr->parent;
            }
            else if(hit){
                price.push_back(s[i]);
            }
            else{
                jcode.push_back(s[i]);
            }
        }
        inf.close();
    }
    else if (flag==4){
        string s;
        string newS;
        ifstream inf;
        inf.open(filename);
        inf>>s;
        bool hit=false;
        int count=0,scount=1;
        for(int i=0;i<s.length();i++){
            if(s[i]=='%'){
                count++;
                hit=true;
            }
            else if(s[i]=='L' || s[i]=='R'){
                scount++;
            }
            if(count==scount && scount>1){
                hit=false;
                break;
            }
            if(hit && count>0){
                newS.push_back(s[i]);
            }
        }
        string left;
        for (int i=0;i<newS.length()-1;i++){
            left.push_back(newS[i+1]);
        }
        inf.close();
        ofstream outf;
        outf.open("temp.txt");
        outf<<left;
        outf.close();
        customLoad(3,"temp.txt");
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
        //root=root->right;
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

