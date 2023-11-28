// Code up the functions defined in tree.h
// Reuse the binary Search Tree implemented in lab 3 as much as possible

#include "tree.h"

// PLEASE FILL IN THE BODIES OF THE FOLLOWING FUNCTIONS

// Returns false, if given JourneyCode is already present in the BST
// Inserts the element and returns True otherwise

int BST::getImbalance()
{
	if (root == nullptr) return 0;
	else return root->getImbalance();
}

bool BST::insert(int JourneyCode, int price) {    
    if (root==NULL){ //insert to empty BST
        root = new TreeNode(JourneyCode, price);
        return true;
    }
    //if (root->copies(JourneyCode)) return false; // returns false if journey code is already present
    TreeNode* current=root;
    while(current!=NULL){//travel down the tree
        if (price<current->price){
            if (current->left==NULL){ // if reached an empty spot, insert here
                current->left=new TreeNode(JourneyCode, price, NULL,NULL,current);
                return true;
            }
            current=current->left; //otherwise keep moving
        }
        else { // >=
            if (current->right==NULL){ // if reached an empty spot, insert here
                current->right=new TreeNode(JourneyCode, price, NULL,NULL,current);
                return true;
            }
            current=current->right; //otherwise keep moving
        }
    }  
    return false;

	// JourneyCode is not present in the BST.  We must now
		// insert an appropriate child of parentOfCurrNode.
		// Please implement this part yourself.
		//
		// Do not forget to update shortestPathLength and
		// longestPathLength of (possibly all) BST nodes in the
		// path from the root to the new node you are inserting
}


// Return True, if the ticket with given attributes is found, false otherwise
bool BST::find(int JourneyCode, int price)
{
	// The following filler code snippet is only given to facilitate
	// compilation.  You should replace it with appropriate code, very
	// similar to what you had done in lab assignment 3.
	//
	// You can look at the implementation of insert to code this part up.
	
	TreeNode* current=root;
    while(current!=NULL&&current->JourneyCode!=JourneyCode){  //travelling down the tree      
        if (price<current->price){
            current=current->left;
        }
        else{ // equal prices go to the right by this convention
            current=current->right;
        }
    }    
    if (current==NULL) return false; //did not find match
    if (current->JourneyCode==JourneyCode) return true;
    else return false; //for safety    
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
		
	if (root==NULL) return false;
    //handling the case where root is to be removed
    if (root->JourneyCode==JourneyCode&&root->price==price){
        if (root->left==NULL&root->right==NULL){ //no children
            root=NULL;
        } 
        //one child
        else if (root->left==NULL) { 
            root=root->right;
            root->parent=NULL;            
        }
        else if(root->right==NULL){
            root=root->left;
            root->parent=NULL;            
        }
        else{ //rem function can be called
            root->rem();
        }
        return true;
    }

    TreeNode* current=root;
    while(current!=NULL&&current->JourneyCode!=JourneyCode){
        if (price<current->price){
            current=current->left;
        }
        else{
            current=current->right;
        }
    }    
    if (current==NULL) return false; //found no matches
    if (current->price!=price) return false; //Journey code implied to be same
    
    current->rem(); //remove that node
    return true; 
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

