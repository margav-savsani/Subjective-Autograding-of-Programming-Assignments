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

BST::BST()
{
    root = new TreeNode;
}
BST::BST(TreeNode *root)
{
    this->root = root;
}

// Returns false, if given JourneyCode is already present in the BST
// Inserts the element and returns True otherwise
bool BST::insert(int JourneyCode, int price)
{
    if(root->JourneyCode == JourneyCode) return false;
    
    if(root->price == 0) //When we initialize a BST using BST(), the price of root node is 0. This makes sure that root is inserted before moving ahead. 
    {
        root->JourneyCode = JourneyCode;
        root->price = price;
        return true;
    }
    
    if(price >= root->price)
    {
        if(root->right == nullptr) //When the right child of root doesn't exist, we create a new one and join them.
        {
            TreeNode *right = new TreeNode(JourneyCode, price, nullptr, nullptr, root); 
            (*root).right = right;
            return true;
        }
        else
        {
            TreeNode *curr = root; //stores the value of our root
            root = root->right; //changes root to root->right. This makes our RST the BST
            bool val = BST::insert(JourneyCode, price); //recurses until the upper condition is reached.
            root = curr; //This changes our BST from RST to BST.
            return val;
        }
    }

    else
    {
        if(root->left == nullptr)//When the left child of root doesn't exist, we create a new one and join them.
        {
            TreeNode *left = new TreeNode(JourneyCode, price, nullptr, nullptr, root);
            root->left = left;
            return true;
        }    
        else
        {
            TreeNode *curr = root;//stores the value of our root
            root = root->left;//changes root to root->left. This makes our LST the BST
            bool val = BST::insert(JourneyCode, price);//recurses until the upper condition is reached.
            root = curr;//This changes our BST from LST to BST.
            return val;
        }
    }
}

// Return True, if the ticket with given attributes is found, false otherwise
bool BST::find(int JourneyCode, int price)
{
    if(root->JourneyCode == JourneyCode && root->price == price) return true; //Base Condition

    if(price >= root->price)
    {
        if(root->right == nullptr) return false; //Base condition. We reach the leaf node without finding the required node. i.e., the joureyCode and price pair doesn't exist.
        else
        {
            TreeNode *curr = root; //stores value of current root
            root = root->right; //Changes root to point to right child to recurse in RST
            bool val = BST::find(JourneyCode, price); //recurses until a Base condition is satisfied. 
            root = curr; //We come back to our original BST
            return val;
        }
    }

    else
    {
        if(root->left == nullptr) return false;//Base condition. We reach the leaf node without finding the required node. i.e., the joureyCode and price pair doesn't exist.
        else
        {
            TreeNode *curr = root;//stores value of current root
            root = root->left;//Changes root to point to left child to recurse in LST
            bool val = BST::find(JourneyCode, price);//recurses until a Base condition is satisfied. 
            root = curr;//We come back to our original BST
            return val;
        }
    }
}
//----------------------ADDITIONAL FUNCTIONS ADDED BY ME------------------------
TreeNode* BST::getMin(TreeNode *n) //Returns the node with minimum price, given a node.
{
    if(n->left == nullptr) return n;
    else
    {
        return BST::getMin(n->left);
    }
}

TreeNode* BST::findNode(int JourneyCode, int price) //Finds and returns the pointer of a node with desired JourneyCode and Price pair.
{
    if(root == nullptr) return root; //BASE CONDITION. We return nullpointer to indicate that the desired node was not found.
    TreeNode* val;
    if(root->JourneyCode == JourneyCode && root->price == price) return root;//BASE CONDITION. Returns the pointer of desired node.

    if(price >= root->price)
    {
        TreeNode* curr = root; //stores value of current root
        root = root->right;//Changes root to point to right child to recurse in RST
        val = BST::findNode(JourneyCode, price);//recurses until a Base condition is satisfied. 
        root = curr;//We come back to our original BST
        return val;
    }

    else
    {
        TreeNode* curr = root; //
        root = root->left;//Changes root to point to left child to recurse in LST
        val = BST::findNode(JourneyCode, price);//recurses until a Base condition is satisfied. 
        root = curr;//We come back to our original BST
        return val;
    }

    return val;
}
//---------------------------------------------------------------------------

// Returns false, if JourneyCode isn't present
// Deletes the corresponding entry and returns True otherwise
bool BST::remove(int JourneyCode, int price)
{
    TreeNode* n = BST::findNode(JourneyCode, price); //Finds and returns the pointer of node with desired JourneyCode and Price pair.
    if(n == nullptr) return false; //n=nullptr implies that the node wasn't found.
    


    if(n == root) //Special case when n is the root. Gave unexpected behaviour while testing, so I made a special case.
    {
       if(n->left == nullptr && n->right != nullptr)  //Has only 1 child. Right child.
       {
            n->right->parent = nullptr;
            root = n->right;
       }
       if(n->left!= nullptr && n->right == nullptr)//Has only 1 child. Left child.
       {
            n->left->parent = nullptr;
            root = n->left;
       }

       if(n->left==nullptr && n->right==nullptr) //Has 0 child.
       {
            root = new TreeNode();
       }
       if(n->left != nullptr && n->right!= nullptr) //Has 2 children. We find its successor(Minimum Prce node in RST). The successor takes the place of the node to be deleted.
       {
            TreeNode* replacement = BST::getMin(n->right);

            if(replacement == n->right) //Special case if the successor is the right child of n.
            {
                replacement->parent = nullptr;
                replacement->left = n->left;
                n->left->parent = replacement;
                root = replacement;
            }
            else{

            replacement->parent->left = replacement->right;
            replacement->right->parent = replacement->parent;
            replacement->right = n->right;
            replacement->left = n->left;
            n->right->parent = replacement;
            n->left->parent = replacement;
            root = replacement;
            }
       }
       delete n;
       return true;
    }

    if(n->left == nullptr && n->right == nullptr)//Has 0 children. Leaf Node.
    {
        if(n->price >= n->parent->price) //If th leaf node is the right child of it's parent
        {
            n->parent->right = nullptr;
        }
        else
        {
            n->parent->left = nullptr;
        }
        delete n;
        return true;
    }

    if(n->left == nullptr && n->right != nullptr)//Has 1 child, the right child.
    {
        if(n->price >= n->parent->price)//If the node is right child of it's parent.
        {
            n->parent->right = n->right;
            n->right->parent = n->parent;
        }
        else
        {
            
            n->parent->left = n->right;
            n->right->parent = n->parent;
        }
        delete n;
        return true;
    }

    if(n->left != nullptr && n->right == nullptr)//Has 1 child, the left child.
    {
        if(n->price >= n->parent->price)//If the node is the right child of it's parent.
        {
            n->parent->right = n->left;
            n->left->parent = n->parent;
        }
        else
        {
            n->parent->left = n->left;
            n->left->parent = n->parent;
        }
        delete n;
        return true;
    }

    if(n->left != nullptr && n->right != nullptr) //Has 2 children.
    {
        TreeNode *replacement = BST::getMin(n->right);//We find its successor(The node with minimum key(price) in the RST w.r.t. the node n)
        
        if(replacement == n->right)//Special case when successor is the right child of n. Noticed unexpected behaviour while testing, so I made a special case.
        {
            if(n->price >= n->parent->price)//If n is the right child of its parent.
            {
                n->parent->right = replacement;
                replacement->parent = n->parent;
                replacement->left = n->left;
                n->left->parent = replacement;
            }
            else{
                n->parent->left = replacement;
                replacement->parent = n->parent;
                replacement->left = n->left;
                n->left->parent = replacement;
            }
        }
        else{
        if(n->price>= n->parent->price) //If n is the right child of its parent.
        {
            n->parent->right = replacement;
            replacement->left = n->left;
            replacement->parent->left = replacement->right;
            replacement->right = n->right;
            replacement->parent = n->parent;

        }

        else
        {
            n->parent->left = replacement;
            replacement->left = n->left;
            replacement->parent->left = replacement->right;
            replacement->right = n->right;
            replacement->parent = n->parent;

        }
        }
        delete n;
        return true;
    }


    return true;
}
	
// Functions that traverse the BST in various ways!
// type is one of PRE_ORDER, POST_ORDER or IN_ORDER
// Print on cout the journey codes at nodes of the BST in the same order as
// they are encountered in the traversal order
// Print one journey code per line

void BST::traverse(int typeOfTraversal)
{
    if(typeOfTraversal == PRE_ORDER)
    {
        if(root == nullptr) return; //Base condition.
        cout<<root->JourneyCode<<endl; //Reads the node.
        TreeNode* curr = root;
        root = root->left;
        BST::traverse(typeOfTraversal); //Recurses in LST.
        root = curr;
        root = root->right;
        BST::traverse(typeOfTraversal);//Recurses in RST.
        root = curr;
        return;
    }

    if(typeOfTraversal == POST_ORDER)
    {
        if(root == nullptr) return;//Base condition.
        TreeNode* curr = root;
        root = root->left;
        BST::traverse(typeOfTraversal);//Recurses in LST.
        root = curr;
        root = root->right;
        BST::traverse(typeOfTraversal);//Recurses in RST.
        root = curr;
        cout<<root->JourneyCode<<endl;//Reads the node.
        return;
    }

    if(typeOfTraversal== IN_ORDER)
    {
        if(root == nullptr) return;//Base condition.
        TreeNode* curr = root;
        root = root->left;
        BST::traverse(typeOfTraversal);//Recurses in LST.
        root = curr;
        cout<<root->JourneyCode<<endl;//Reads the node.
        root = root->right;
        BST::traverse(typeOfTraversal);//Recurses in RST.
        root = curr;
        return;
    }
}

// Returns the price of the cheapest journey
int BST::getMinimum()
{
    if(root->left==nullptr) return root->price;//BASE CONDITION.
    else
    {
        TreeNode *curr = root;//Stores the pointer to current root.
        root = root->left;//We make the left child the root, to recurse in LST
        int val = BST::getMinimum();//Recursion..
        root = curr;//Back to original BST
        return val;
    }
}

// Part II

// Returns the count of journeys that are at least as expensive
// as lowerPriceBound and at most as expensive as upperPriceBound,
// both bounds included.
int BST::countJourneysInPriceBound(int lowerPriceBound, int upperPriceBound)
{
    int count=0;//Number of nodes in desired range
    if(root ==  nullptr) return 0;//BASE CONDITION. We have reached the end of the branch.
    
    if(root->price >= lowerPriceBound && root->price <= upperPriceBound)//Price of root lies in desired range.
    {
        count +=1;//increment the count.
        TreeNode* curr = root;
        root = root->left;//To recurse through the LST
        count += countJourneysInPriceBound(lowerPriceBound, upperPriceBound);//Recurses till a base condtion is triggered. Returns the count, which keeps incrementing as we come out of the recursion
        root = curr;
        root = root->right;//To recurse through the RST
        count += countJourneysInPriceBound(lowerPriceBound, upperPriceBound);//Recurses till a base condtion is triggered. Returns the count, which keeps incrementing as we come out of the recursion
        root = curr;//Back to original BST.
        return count;
    }

    if(root->price > upperPriceBound)//Price of root greater than upper bound. WE recurse only through LST since all the nodes in RST will have price outside the range.
    {
        TreeNode* curr = root;
        root = root->left;//To recurse in LST.
        count = count + countJourneysInPriceBound(lowerPriceBound, upperPriceBound);//Recursion and count increment.
        root = curr;//Back to original BST.
        return count;
    }
    if(root->price < lowerPriceBound)//Price of root less than lower bound. WE recurse only through RST since all the nodes in LST will have price outside the range.
    {
        TreeNode* curr = root;
        root = root->right;//To recurse in RST.
        count = count + countJourneysInPriceBound(lowerPriceBound, upperPriceBound);//Recursion and count increment.
        root = curr;//Back to original BST.
        return count;
    }
    return count;

}

// Store the current tree in a file called filename.  You should
// store using a scheme that uses no more disk space than that
// required to store all elements in the BST, plus perhaps a small
// constant times the number of elements.  You should also store
// in a manner such that your implementation of customLoad is as
// memory and time efficient as possible.
void BST::customStore(string filename)
{
    if(root == nullptr) return;
    ofstream f;
    if(root->parent==nullptr) f.open(filename);//Since I am using recursion, the root keeps changing. To prevent overwriting the file in each recursion, this special condition is defined.
    else{
    f.open(filename, std::ios_base::app);//Opens file in append mode if the root is not the ACTUAL ROOT of BST.
    }

    int sentinelVal=0;//This value turns -1 if the node has a right child. Will help us in customLoad.
    if(root->right !=nullptr) sentinelVal=-1;
    f<<sentinelVal<<" "<<root->JourneyCode<<" "<<root->price<<endl;
    f.close();

    //Recursion through LST
    TreeNode* curr = root;
    root = root->left;
    customStore(filename);

    //Recursion through RST.
    root = curr;
    root = root->right;
    customStore(filename);
    root = curr;

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
 
void BST::customLoad (int flag, string filename)
{
    ifstream f;
    f.open(filename);
    TreeNode* curr = root;//Stores the pointer to current root.
    int j=0;//A flag to tell that ACTUAL ROOT has been inserted.

    std::vector<TreeNode*> sentinelNodes; //Used as a stack. Stores the nodes with SentinelValue=-1. The last element is popped whenever we add a node as a right child.
    int sentinelVal, jrnyCode, price;

    if(flag==LOAD_FULL_BST)//Loads FULL BST.
    {
        while(true)
        {
            f>>sentinelVal;
            f>>jrnyCode;
            f>>price;

            if(f.eof()) break;//Reading the file is complete.
        
            if(j==0)//When j=0, we insert the ACTUAL ROOT of BST.
            {
                curr->price=price;
                curr->JourneyCode=jrnyCode;
                if(sentinelVal==-1) sentinelNodes.push_back(curr);
                j++;
            }
            else
            {
                if(price<curr->price)//This tells us if we have to add a left child or a right child.
                {
                    TreeNode* left= new TreeNode(jrnyCode,price,nullptr, nullptr, curr);//Creates a new node to insert the left child.
                    curr->left=left;//Joins the root with left child.
                    curr=left;//Sets Left child as current ROOT.
                    if(sentinelVal==-1) sentinelNodes.push_back(curr);//In our input file, if this node has a sentinelValue=-1, we know that at some point we have to add its right child, so we store it in the stack.
                }
                else
                {   //We have to add a right child.
                    TreeNode* parent = sentinelNodes.back(); //The parent node is the last element in the stack. Since the values were stored in PRE-ORDER format,
                                    //The first right child will be added to the last node with sentinelValue=-1.
                    sentinelNodes.pop_back();//after we are done fetching the last node from stack, it's work is over. Hence we pop it.
                    TreeNode* right= new TreeNode(jrnyCode, price, nullptr, nullptr, parent);//Create a new node to insert right child.
                    parent->right=right;//Join the child and parent.
                    curr=right;//Sets right child as CURRENT ROOT.
                    if(sentinelVal==-1) sentinelNodes.push_back(curr);//Inserts the node in stack if it has a right child.
                
                }
            }
        }
        f.close();
        return;
    }
    if(flag==LOAD_LEFT_SUBTREE)
    {
        int rootPrice;//Stores the price of the root of FULL BST. When we encounter a value greater than this, we know that LEFT SUBTREE is fully read and now RST will be read, so that we can stop loading.

        f>>sentinelVal;f>>jrnyCode;f>>rootPrice;//Dummy read to discard the  first value, since we have to load the left SUBTREE and the first value is not required.
        
        //Reads the value of root of lST.
        f>>sentinelVal;
        f>>jrnyCode;
        f>>price;

        if(price>=rootPrice) return;//Ends the function because LST is fully loaded.
        else //root inserted
        {
            curr->price=price;
            curr->JourneyCode=jrnyCode;
            if(sentinelVal==-1) sentinelNodes.push_back(curr);
        }

        while(true)
        {
            f>>sentinelVal;
            f>>jrnyCode;
            f>>price;

            if(price>=rootPrice) break;
            if(f.eof()) break;   

            if(price<curr->price)//ADDS LEFT CHILD
            {
                TreeNode* left= new TreeNode(jrnyCode,price,nullptr, nullptr, curr);
                curr->left=left;
                curr=left;
                if(sentinelVal==-1) sentinelNodes.push_back(curr);
            }
            else
            {
                TreeNode* parent = sentinelNodes.back();
                sentinelNodes.pop_back();
                TreeNode* right= new TreeNode(jrnyCode, price, nullptr, nullptr, parent);
                parent->right=right;
                curr=right;
                if(sentinelVal==-1) sentinelNodes.push_back(curr);
            
            }
        }
        f.close();
        return;
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


