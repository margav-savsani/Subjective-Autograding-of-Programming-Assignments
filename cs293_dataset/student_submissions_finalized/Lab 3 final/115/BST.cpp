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

BST::BST()//initialising root to null initially
{
   root=NULL;
}
BST::BST(TreeNode *root)
{
    this->root=root;
}

// Returns false, if given JourneyCode is already present in the BST
// Inserts the element and returns True otherwise
bool BST::insert(int JourneyCode, int price)
{
    if(root==NULL)// if root is initially null, then adding directly at the root
    {
        root= new TreeNode;
        root->left=NULL;
        root->right=NULL;
        root->price=price;
        root->JourneyCode=JourneyCode;
        return true;
    }
    TreeNode* A=root;
    TreeNode* B=new TreeNode;
    B->JourneyCode=JourneyCode;
    B->price=price;
    B->left=NULL;
    B->right=NULL;
    while(true)//finding the place for element and then adding there
    {
        if(A->price > price)//if price is less than root, go to right and add there
        {
            if(A->left==NULL)//if left is null, just add there
            {
            B->parent=A;
            A->left=B;
            return true;  
            }
            A=A->left;
            continue;
        }
        if(A->price < price)//if price is more than root, go to left amd add there
        {
            if(A->right==NULL)//if right is null, just add there
            {
            B->parent=A;
            A->right=B;
            return true;  
            }
            A=A->right;
            continue;
        }
        if(A->price == price)
        {
            if(JourneyCode==A->JourneyCode)// if it is already there, then return false
            {
                return false;
            }
            else
            {
                if(A->right==NULL)//adding equal price elements at the right
                {
                    B->parent=A;
                    A->right=B;
                    return true;  
                }
                A=A->right;
                continue;
            }
        }
    }
}
//assumption! if same value of cost is added, then it will added to the right of old one
// Return True, if the ticket with given attributes is found, false otherwise
bool BST::find(int JourneyCode, int price)
{
    TreeNode* A=root;
    while(true)
    {
        if(A==NULL)// if root of the subtree is null then return false
        {
            return false;
        }
        if(A->price > price)//changing the point of view of root
        {
            A=A->left;
            continue;
        }
        if(A->price < price)
        {//moving to the right subtree
            A=A->right;
            continue;
        }
        if(A->price == price)
        {
            if(JourneyCode==A->JourneyCode)
            {//found
                return true;
            }
            else
            {//if different journey code,then go right
                A=A->right;
                continue;
            }
        }
    }
}
	
// Returns false, if JourneyCode isn't present
// Deletes the corresponding entry and returns True otherwise
bool BST::remove(int JourneyCode, int price)
{
    TreeNode* A=root;
    while(true)
    {
        if(A==NULL)//if root is null or element is not found 
        {
            return false;
        }
        if(A->price > price)//finding element
        {
            A=A->left;
            continue;
        }
        if(A->price < price)//finding element
        {
            A=A->right;
            continue;
        }
        if(A->price == price && JourneyCode==A->JourneyCode)//finding element
        {
            if(A->left == NULL && A->right==NULL)//delete case 1
            {
                if(A->parent==NULL)//if deleting root
                {
                    delete root;
                    root=NULL;
                }
                else if((A->parent)->left==A)//if child is at left of parent
                {
                    (A->parent)->left=NULL;
                }
                else if((A->parent)->right==A)//if child is at right of parent
                {
                    (A->parent)->right=NULL;
                }
                return true;
            }
            if(A->left != NULL && A->right == NULL)//delete case 2
            {
                if(A->parent==NULL)//if deleting root
                {
                    root=A->left;
                    delete A;
                }
                else if((A->parent)->left==A)//if child is at left of parent
                {
                    (A->parent)->left=A->left;
                    (A->left)->parent=A->parent;
                }
                else if((A->parent)->right==A)//if child is at right of parent
                {
                    (A->parent)->right=A->left;
                    (A->left)->parent=A->parent;
                }
                return true;
            }
            if(A->left == NULL && A->right != NULL)//delete case 3 
            {
                if(A->parent==NULL)//if deleting root
                {
                    root=A->right;
                    delete A;
                }
                else if((A->parent)->left==A)//if child is at left of parent
                {
                    (A->parent)->left=A->right;
                    (A->right)->parent=A->parent;
                }
                else if((A->parent)->right==A)//if child is at right of parent
                {
                    (A->parent)->right=A->right;
                    (A->right)->parent=A->parent;
                }
                return true;
            }
            if(A->left != NULL && A->right != NULL)//delete case 4-->2 children
            {
                int JourneyCode1;
                int price1;
                TreeNode* B=A->right;//first right and then all left
                while(true)
                {
                    if(B->left!= NULL)//finding successor
                    {
                        B=B->left;
                    }
                    else
                    {
                        price1=B->price;
                        JourneyCode1=B->JourneyCode;
                        remove(JourneyCode1,price1);
                        break;
                    }
                }
                A->JourneyCode=JourneyCode1;
                A->price=price1;
            }
            return true;
        }
        if(A->price==price && A->JourneyCode!=JourneyCode)//if journey code is different
        {
            A=A->right;
            continue;
        }
    }
}
	
// Functions that traverse the BST in various ways!
// type is one of PRE_ORDER, POST_ORDER or IN_ORDER
// Print on cout the journey codes at nodes of the BST in the same order as
// they are encountered in the traversal order
// Print one journey code per line

void BST::traverse(int typeOfTraversal)
{
    TreeNode* A;
    A=root;
    traverse_tree(typeOfTraversal,A);
    return;
}
void BST::traverse_tree(int typeOfTraversal,TreeNode* C)//my new function
{
    TreeNode* A;
    A=C;
    if(A==NULL)// if empty tree then return
    {
        return;
    }
    if(typeOfTraversal==0)// pre order traversal
    {
        if(A==NULL)
        {
            return;
        }
        cout << A->price<<endl;
        traverse_tree(0,A->left);
        traverse_tree(0,A->right);
        return;
    }
    if(typeOfTraversal==1)//post order traversal
    {
        if(A==NULL)
        {
            return;
        }
        traverse_tree(0,A->left);
        traverse_tree(0,A->right);
        cout << A->price<<endl;
        return;
    }
    if(typeOfTraversal==2)//inorder traversal
    {
        if(A==NULL)
        {
            return;
        }
        traverse_tree(0,A->left);
        cout << A->price<<endl;
        traverse_tree(0,A->right);
        return;
    }
    cout<<"ERROR"<<endl;//if number is not 0,1,2
}

// Returns the price of the cheapest journey
int BST::getMinimum()
{
    TreeNode* A;
    A=root;
    while(true)//all lefts
    {
        if(A==NULL)//if null means no tree
        {
            return -1;
        }
        if(A->left==NULL)
        {
            return A->price;
        }
        A=A->left;
    }
}

// Part II

// Returns the count of journeys that are at least as expensive
// as lowerPriceBound and at most as expensive as upperPriceBound,
// both bounds included.
int BST::countJourneysInPriceBound(int lowerPriceBound, int upperPriceBound)
{
    return countJourneysInPriceBound2(lowerPriceBound,upperPriceBound,root);
}
int BST::countJourneysInPriceBound2(int lowerPriceBound, int upperPriceBound,TreeNode* root)//my new function
{
    if(upperPriceBound < lowerPriceBound)//checking arguments are correct
    {
        return 0;
    }
    if(root==NULL)//if tree is null
    {
        return 0;
    }
    if(root->price > upperPriceBound)//changing point of view from full tree to left sub tree
    {
        if(root->left=NULL)
        {
            return 0;
        }
        else
        {
            return countJourneysInPriceBound2(lowerPriceBound,upperPriceBound,root->left);
        }
    }
    if(root->price == upperPriceBound)
    {
        if(root->left == NULL && root->right == NULL)
        {
            return 1;
        }
        if(root->right == NULL)
        {
            return 1+countJourneysInPriceBound2(lowerPriceBound,upperPriceBound,root->left);
        }
        if(root->left == NULL)
        {
            return 1+countJourneysInPriceBound2(upperPriceBound,upperPriceBound,root->right);
        }
        return 1+countJourneysInPriceBound2(lowerPriceBound,upperPriceBound,root->left)+countJourneysInPriceBound2(upperPriceBound,upperPriceBound,root->right);
    }
    if(root->price > lowerPriceBound && root->price < upperPriceBound)//have to take care both the subtrees
    {
        if(root->right==NULL && root->left==NULL)//checking it has 2 children or noor
        {
            return 1;
        }
        if(root->right==NULL && root->left!=NULL)
        {
            return 1+countJourneysInPriceBound2(lowerPriceBound,upperPriceBound,root->left);
        }
        if(root->right!=NULL && root->left==NULL)
        {
            return 1+countJourneysInPriceBound2(lowerPriceBound,upperPriceBound,root->left);
        }
        if(root->right!=NULL && root->left!=NULL)// if it has both children, then calculate for each separately and add
        {
            return 1+countJourneysInPriceBound2(lowerPriceBound,upperPriceBound,root->left)+countJourneysInPriceBound2(lowerPriceBound,upperPriceBound,root->right);
        }
    }
    if(root->price == lowerPriceBound)
    {
        if(root->right==NULL)
        {
            return 1;
        }
        else//have to take care root and right subtree
        {
            return 1+countJourneysInPriceBound2(lowerPriceBound,upperPriceBound,root->right);
        }
    }
    if(root->price < lowerPriceBound)//changing point of view from full tree to right sub tree
    {
        if(root->right==NULL)
        {
            return 0;
        }
        else//only right tree
        {
            return countJourneysInPriceBound2(lowerPriceBound,upperPriceBound,root->right);
        }
    }
    return 0;
}

// Store the current tree in a file called filename.  You should
// store using a scheme that uses no more disk space than that
// required to store all elements in the BST, plus perhaps a small
// constant times the number of elements.  You should also store
// in a manner such that your implementation of customLoad is as
// memory and time efficient as possible.
void BST::customStore(string filename)
{
    if(root==NULL)
    {
        return;
    }
    ofstream f1;
    f1.open(filename,std::ios_base::app);
    f1 << root->price << " " << root->JourneyCode<< " ";//storing price and journey code of each node
    f1.close();
    TreeNode* curr;
    curr=root;
    root=root->left;
    if(root!=NULL)
    {
        customStore(filename);
    }
    else
    {
        f1.open(filename,std::ios_base::app);
        f1 << "x ";//if left subtree is null i am storing character x
        f1.close();
    }
    root=curr->right;
    if(root!=NULL)
    {
        customStore(filename);
    }
    else
    {
        f1.open(filename,std::ios_base::app);
        f1 << "x ";//if right subtree is null i am storing character x
        f1.close();
    }
    root=curr;
    return;
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
 
TreeNode* BST::myinsert(int JourneyCode,int price,TreeNode* parent,int left)//i created a new insert function for ordern, because i am adding the pointer to which i have to add 
{
//    cout <<"Insert is called"<<endl;
    TreeNode* a=new TreeNode;
    a->left=NULL;
    a->right=NULL;
    a->parent=parent;
    a->JourneyCode=JourneyCode;
    a->price=price;
    if(parent==NULL)//if parent is null, just add the element to the root
    {
        root=a;
        return root;
    }
    if(left==2)//adding at the left
    {
        parent->left=a;
    }
    if(left==1)//adding at the right
    {
        parent->right=a;
    }
    return a;
}

void BST::customLoad (int flag, string filename)//loading the tree
{
    vector<int> a;
    vector<TreeNode*> b;
    TreeNode* dumm=NULL;
    int size=0;
    root=NULL;
    ifstream f1;
    f1.open(filename);
    string s;
    int dummy=0;
    int JourneyCode=0;
    int price=0;
    while(!f1.eof())
    {
        f1>>s;//taking string from the file for every while loop
        if(s=="x")
        {
            // if x is taken, we may need to delete an element in the vector because at some point all the 2 children for a node are filled.
            if(dummy==1 ||a.size()==0)
            {
                f1.close();
                return;
            }
            else
            {
                if(a[a.size()-1]==2)// if x came after inserting a leaf, then make the left to null
                {
                    b[a.size()-1]->left=NULL;
                    a[a.size()-1]=1;
                    continue;
                }
                if(a[a.size()-1]==1)//if x came after inserting left tree, then make right to null
                {
                    b[a.size()-1]->right=NULL;
                    a.pop_back();
                    b.pop_back();
                    continue;
                }
            }
        }
        else
        {
            JourneyCode=stoi(s);//assigning Journey code to local variable
            f1>>s;//taking price
            price=stoi(s);//assigning price to local variable
            if(root==NULL)
            {
                if(flag==4)//if flag is 4, then don't add tree root
                {
                    flag--;
                    continue;
                }
                else
                {
                    dumm=myinsert(JourneyCode,price,NULL,0);
                    a.push_back(2);
                    b.push_back(dumm);
                }
            }
            else
            {
                if(a.size()==0)
                {
                    f1.close();
                    return;
                }
                dumm=myinsert(JourneyCode,price,b[a.size()-1],a[a.size()-1]);
                a[a.size()-1]--;
                if(a[a.size()-1]==0)
                {
                    a.pop_back();
                    b.pop_back();
                }
                a.push_back(2);
                b.push_back(dumm);
            }
        }
    }
    f1.close();
    return;
}
// ************************************************************
// DO NOT CHANGE ANYTHING BELOW THIS LINE
// Please use the following code to replace the last part of
// BST.cpp that was provided earlier (from below the comment
// DO NOT CHANGE ANYTHING BELOW THIS LINE)
//
//

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