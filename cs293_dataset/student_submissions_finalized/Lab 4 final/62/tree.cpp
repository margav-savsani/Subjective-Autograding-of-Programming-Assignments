// Code up the functions defined in tree.h
// Reuse the binary Search Tree implemented in lab 3 as much as possible

#include "tree.h"

// PLEASE FILL IN THE BODIES OF THE FOLLOWING FUNCTIONS

// see the imbalance of the tree
int BST::getImbalance() 
{
	if (root == nullptr) return 0;
	else return ((root->longestPathLength)-(root->shortestPathLength));
}

// Returns false, if given JourneyCode is already present in the BST
// Inserts the element and returns True otherwise
bool BST::insert(int JourneyCode, int price) {    
    if (root==NULL){ //insert to empty BST
        root = new TreeNode(JourneyCode, price);
        return true;
    }
    TreeNode toins(JourneyCode,price);
    //if (root->copies(JourneyCode)) return false; // returns false if journey code is already present
    TreeNode* current=root;
    while(current!=NULL){//travel down the tree
        if (toins<*current){
            if (current->left==NULL){ // if reached an empty spot, insert here
                current->left=new TreeNode(JourneyCode, price, NULL,NULL,current);
                break ;
            }
            current=current->left; //otherwise keep moving
        }
        else if (*current<toins) { 
            if (current->right==NULL){ // if reached an empty spot, insert here
                current->right=new TreeNode(JourneyCode, price, NULL,NULL,current);
                break;
            }
            current=current->right; //otherwise keep moving
        }
        else {
            return false;

        }
    }  
    if (current==NULL) return false; 
    current->recountLength();
    
    return true;

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
    TreeNode toins(JourneyCode,price);
	TreeNode* current=root;
    while(current!=NULL&& !(toins==*current)){  //travelling down the tree      
        if (toins<*current){
            current=current->left;
        }
        else{
            current=current->right;
        }
    }    
    if (current==NULL) return false; //did not find match
    else return true;
}

//update the values of shortest and longest path lengths
void TreeNode::recountLength(){//can optimise this
    TreeNode* current=this;
    for(;current!=NULL;current=current->parent){
        if (current->left==NULL&&current->right==NULL){ //leaf
            current->shortestPathLength=current->longestPathLength=1;
        }
        //only one child
        else if (current->left==NULL){
            current->shortestPathLength=1;
            current->longestPathLength=(1+ current->right->longestPathLength);
        }
        else if (current->right==NULL){
            current->shortestPathLength=1;
            current->longestPathLength=(1+ current->left->longestPathLength);
        }
        //both children present
        else {
            current->shortestPathLength=1+min(current->right->shortestPathLength,current->left->shortestPathLength);
            current->longestPathLength=1+max(current->right->longestPathLength,current->left->longestPathLength);
        }
    }
    return;
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

