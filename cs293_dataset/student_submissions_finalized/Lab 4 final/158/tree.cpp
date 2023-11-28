


#include <iostream>
#include <vector>
#include <string>

using namespace std;

#include "tree.h"

// Returns false, if given JourneyCode is already present in the BST
// Inserts the element and returns True otherwise


//checks if journey is already present in tree
bool BST::journeyCheck(struct TreeNode *l, int JourneyCode){
   if (l==nullptr)return true;
   else if(l->JourneyCode == JourneyCode) return false;
   else{ 
     if(l->JourneyCode < JourneyCode) return journeyCheck(l->right, JourneyCode);
     else return journeyCheck(l->left, JourneyCode);
 		
   }
 		
}

// gets imbalance at root;
int BST::getImbalance()
{
  if (root == nullptr) return 0;
  else return root->getImbalance();
}

// inserts new node and also returns the height of the newly
// inserted branch from that node; recursive procedure
int BST::insert(int JourneyCode, int price, TreeNode* l, TreeNode* prev) {
  
  if (l == nullptr) { //base case: adds at an empty location
  
    l = new struct TreeNode;
    l->JourneyCode = JourneyCode;
    l->price = price;
    l->parent = prev;
    
    if(root != nullptr){ // placing new node at something that is not the root
    if(l->JourneyCode > prev->JourneyCode) prev->right = l;
    else prev->left = l;}
    
    else {root = l;} // placing new node at root
    return 0;
  }
  
  
  else{  // moves down into lower nodes and recurses
    int height = 1;
    if(JourneyCode > l->JourneyCode)
    height += insert(JourneyCode, price, l->right,l );
    else if (JourneyCode < l->JourneyCode)
    height += insert(JourneyCode, price, l->left, l);
    
    
    if(l->longestPathLength < height) l->longestPathLength = height;
    else if(l->shortestPathLength > height) l->shortestPathLength = height;
    
    return height;}

 
 return 0;


  
}
//************************DELETION of ELEMENTS***********************

Journey  BST :: inOrderSuccessor(TreeNode* l) {
        Journey Output;
        while (l->left != nullptr) {
            Journey Successor(l->JourneyCode, l->price);
            Output=Successor;
            l = l->left;
        }
        return Output;
    }




	
// Returns false, if JourneyCode isn't present
// Deletes the corresponding entry and returns True otherwise
TreeNode* BST::remove(int JourneyCode, int price, TreeNode* l)
{
  {

        if (l == nullptr)
            return nullptr;

        if ( JourneyCode < l->JourneyCode) {
            l->left = remove(JourneyCode, price, l->left);
        } else if (JourneyCode > l->JourneyCode) {
            l->right = remove(JourneyCode, price, l->right);
        } else {

            if (l->left == nullptr) {
                return l->right;
            } else if (l->right == nullptr)
                return l->left;

            l->JourneyCode = inOrderSuccessor(l->right).JourneyCode;
            l->price = inOrderSuccessor(l->right).price;
            l->right = remove(l->JourneyCode, l->price, l->right);
        }

        return l;

    }



    
  return nullptr;
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

