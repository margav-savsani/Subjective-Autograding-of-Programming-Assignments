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




BST::BST(){; }
BST::BST(TreeNode *root){; }

// Returns false, if given JourneyCode is already present in the BST
// Inserts the element and returns True otherwise
bool BST::insert(int JourneyCode, int price) {
    bool a ;
      a= find (JourneyCode,price);
      if( a==true)
           return false;

      
      else 
      {
          if ( root ==NULL){
           root=new TreeNode(JourneyCode, price);
           return true;}
            
      else {
         
      
    if   (price >root->price)
          root=root->right;
 
      else
      root=root->left;
          }
          return true;}
          
          
}
 
 
 
 

// Return True, if the ticket with given attributes is found, false otherwise
bool BST::find(int JourneyCode, int price) { 
             if (root ==NULL){
                  return false;}
      else {
         if ( root->JourneyCode==JourneyCode && root->price==price)
              return true;
         
             
       else 
            { if (price >root->price)
              
              root= root->right;
              

              else 
              root =root->left;
               
               }
               }
        
        
 }
	
// Returns false, if JourneyCode isn't present
// Deletes the corresponding entry and returns True otherwise

struct TreeNode* BST:: findSuccessor(struct TreeNode* node)
{
    struct TreeNode* current = node;
  
   
    while (current && current->left != NULL)
        current = current->left;
  
    return current;
}

bool BST::remove(int JourneyCode, int price) { 
       if(root==NULL)
        return false;

      else{
      
      
  
   
    if (price < root->price)
        root=root->left;
  
    
    else if (price> root->price)
        root=root->right ;
  
    
    else {
     if(JourneyCode=root->JourneyCode){
        // node has no child
        
        if (root->left==NULL && root->right==NULL)
             free(root);
        
        // node with only one child or no child
        else if (root->left == NULL) {
            struct TreeNode* temp1 = root->right;
            temp1->parent=root->parent;
            
            &temp1==&root;
             
                 
            free(root);
           
            
        }
        else if (root->right == NULL) {
            struct TreeNode* temp2 = root->left;
            temp2->parent=root->parent;
            &temp2==&root;
             
            
            free(root);
            
        }
  else {
        
        struct TreeNode* temp = findSuccessor(root->right);
         if (temp->left!=NULL){
         struct TreeNode* temp3=temp->left;
                    &temp3==&temp;}
        
       
        root->price = temp->price;
        root->JourneyCode=temp->JourneyCode;
           
        
        free(temp);
    }
    
}
    }
    return true;}
    }
	
// Functions that traverse the BST in various ways!
// type is one of PRE_ORDER, POST_ORDER or IN_ORDER
// Print on cout the journey codes at nodes of the BST in the same order as
// they are encountered in the traversal order
// Print one journey code per line

// Preorder traversal
void BST:: preorderTraversal(struct TreeNode* root) {
  if (root == NULL)
    return;

  cout << root->JourneyCode<<endl;
  preorderTraversal(root->left);
  preorderTraversal(root->right);
}

// Postorder traversal
void postorderTraversal(struct TreeNode* root) {
  if (root == NULL)
    return;

  postorderTraversal(root->left);
  postorderTraversal(root->right);
  cout << root->JourneyCode <<endl;
}

// Inorder traversal
void BST::inorderTraversal(struct TreeNode* root) {
  if (root == NULL)
    return;

  inorderTraversal(root->left);
  cout << root->JourneyCode<<endl;
  inorderTraversal(root->right);
}

void BST::traverse(int typeOfTraversal) {
       
        if  (typeOfTraversal== POST_ORDER){
        postorderTraversal( root);
        
        }
     if (typeOfTraversal== PRE_ORDER){
     preorderTraversal(root);
     }
if (typeOfTraversal== IN_ORDER){
         
inorderTraversal(root);
}


    return; }






// Returns the price of the cheapest journey
int BST::getMinimum() {
           
      while (root!= NULL) {
      root = root->left;
   }
   return(root->price);

}


// Part II

// Returns the count of journeys that are at least as expensive
// as lowerPriceBound and at most as expensive as upperPriceBound,
// both bounds included.

int BST:: heightOfTree(TreeNode* root)
{
    if(root == NULL)
        return 0;
    else
        return max(heightOfTree(root->left), heightOfTree(root->right)) + 1;
}
int BST::getNodes(TreeNode*root, int low, int high)
{
    // Base case
    if (root==NULL) return 0;
 
    
    if (root->price== high && root->price== low)
        return 1;
 
  
    if (root->price<= high && root->price >= low)
         return 1 + getNodes(root->left, low, high) +
                    getNodes(root->right, low, high);
 
    
    else if (root->price < low)
         return getNodes(root->right, low, high);
 
    
    else return getNodes(root->left, low, high);
}
 
int BST::countJourneysInPriceBound(int lowerPriceBound, int upperPriceBound) {

       int n;
    n= getNodes(root,lowerPriceBound, upperPriceBound);

        return n;
        } 
    
    
   

// Store the current tree in a file called filename.  You should
// store using a scheme that uses no more disk space than that
// required to store all elements in the BST, plus perhaps a small
// constant times the number of elements.  You should also store
// in a manner such that your implementation of customLoad is as
// memory and time efficient as possible.

void BST::storingInArrayPre(TreeNode* root, int* arr, int &n)
{int i=0;
    if(root == NULL) return; 
    while(root!=NULL){
    
    
    
        storingInArrayPre(root->left, arr,n);
    
        storingInArrayPre(root->right, arr,n);
     arr[i] = root->JourneyCode;

        i++;
}
n=i;
return ;
}
 void BST::storingInArrayIn(TreeNode* root, int* arr, int &n)
	{int i=0;
	    if(root == NULL){ return; }
	    while(root!=NULL){
	    
		storingInArrayIn(root->left, arr,n);
	            arr[i] = root->JourneyCode;
	            i++;
		storingInArrayIn(root->right, arr,n);

         }
	n=i;
	return;
	}   

void BST::customStore(string filename) {
                 int n2;
                int n1;
                int arr1[n1];
                int arr2[n2];
                
	storingInArrayPre(root,  arr1, n1);
	    ofstream outfile;
	    outfile.open("tree.txt");
	    for (int i=0; i<=n1;i++)
	       outfile << arr1[i]<< "  " ;
	        outfile<<endl;
	        
	     
	    storingInArrayIn( root,  arr2, n2);
	    
	     for (int i=0; i<=n2;i++)
	       outfile << arr2[i]<< "  " ;
	        outfile<<endl;
	     outfile.close();
	    
 return; }
	
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
 
set<TreeNode*> s;
stack<TreeNode*> st;
 
// Function to build tree using given traversal
TreeNode* buildTree(int preorder[], int inorder[],int n)
{
 
    TreeNode* root = NULL;
    for (int pre = 0, in = 0; pre < n;)
    {
 
        TreeNode* node = NULL;
        do
        {
            node = new TreeNode(preorder[pre]);
            if (root == NULL)
            {
                root = node;
            }
            if (st.size() > 0)
            {
                if (s.find(st.top()) != s.end())
                {
                    s.erase(st.top());
                    st.top()->right = node;
                    st.pop();
                }
                else
                {
                    st.top()->left = node;
                }
            }
            st.push(node);
        } while (preorder[pre++] != inorder[in] && pre < n);
 
        node = NULL;
        while (st.size() > 0 && in < n &&
                st.top()->val == inorder[in])
        {
            node = st.top();
            st.pop();
            in++;
        }
 
        if (node != NULL)
        {
            s.insert(node);
            st.push(node);
        }
    }
 
    return root;
}


void BST::customLoad (int flag, string filename) { 
        int preorder[] ;
        int inorder[];
       ifstream infile;
       infile.open("tree.txt");
        string line;
while(getline(infile, line))
{
 infile>> preorder[i];
 i++;
}
 
           file.close()
        infile >> 
      



return; }


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
        root = root->right;
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
        root = root->right;
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

