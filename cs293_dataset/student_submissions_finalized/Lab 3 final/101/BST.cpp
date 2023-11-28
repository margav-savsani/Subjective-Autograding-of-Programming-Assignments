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

BST::BST(){ root = nullptr; }
BST::BST(TreeNode *root){ this->root=root ; }

// Returns false, if given JourneyCode is already present in the BST
// Inserts the element and returns True otherwise
bool BST::insert(int JourneyCode, int price) { 
	if(find(JourneyCode, price)){
		return false;
	}
	else if ( root == nullptr ){
		root = new struct TreeNode (JourneyCode, price);
		return true;
	}
	else{
		TreeNode *x = root;
		TreeNode *y = nullptr;
		while(1){
			if ( x == nullptr ){
				break;
			}
			y = new struct TreeNode ();
                        y = x;
			if ( price < x->price ){
				x = x->left;
			}
			else{
				x = x->right;
			}

		}
		if ( price < y->price ){
			y->left = new struct TreeNode(JourneyCode,price);
			y->left->parent = new struct TreeNode();
			y->left->parent = y;
		}
		else{
			y->right = new struct TreeNode(JourneyCode, price);
			y->right->parent = new struct TreeNode();
			y->right->parent = y;
		}
	return true;
	}
}

// Return True, if the ticket with given attributes is found, false otherwise
bool BST::find(int JourneyCode, int price) { 
	TreeNode *x = root;
	while(1){
		if ( x == nullptr ){
			return false;
		}
		else if ( price < x->price ){
			x = x->left;
		}
		else if ( price > x->price ){
			x = x->right;
		}
		else if ( price == x->price && JourneyCode==x->JourneyCode){
			return true;
		}
		else if ( price == x->price && JourneyCode!=x->JourneyCode){
			x = x->right;
		}
		else{
			return false;
		}
	}
}
	
// Returns false, if JourneyCode isn't present
// Deletes the corresponding entry and returns True otherwise
bool BST::remove(int JourneyCode, int price) {
	if (find(JourneyCode, price)){
		TreeNode *x = root;
        	TreeNode *y = nullptr;
                while(1){
                        if ( x->price == price && x->JourneyCode == JourneyCode){
                                break;
                        }
                        y = new struct TreeNode ();
                        y = x;
                        if ( price < x->price ){
                                x = x->left;
                        }
                        else{
                                x = x->right;
                        }
                }
		
		if ( x->left == nullptr && x->right == nullptr ){
			if (y==nullptr){
				delete root;
				root = nullptr;
			}
			else if( y->right == x ){
                		y->right == nullptr;
            		}
			else if(y->left == x) {
                		y->left == nullptr;
            		}
			x = nullptr;
        	}
		else if ( (x->left==nullptr) && (x->right!=nullptr) ){
			if(y == nullptr){
				root = x->right;
				root->parent = nullptr;
			}
			else if(y->left==x){
                	y->left = x->right;
                	(x->right)->parent = y;
            		}
			else if(y->right==x){
                	y->right = x->right;
                	(x->right)->parent = y;
            		}

        	}

		else if ( (x->right==nullptr) && (x->left!=nullptr) ){
			if(y == nullptr){
                                root = x->left;
                                root->parent = nullptr;
                        }
			else if(y->right==x){
                		y->right = x->left;
                		(x->left)->parent = y;
            		}
			else if(y->left==x){
                		y->left = x->left;
                		(x->left)->parent = y;
            		}

        	}
		else{
			TreeNode *rm = x;
			if (rm->right->left==nullptr){
				if (rm->right->right==nullptr){
					rm->price = rm->right->price;
					rm->JourneyCode = rm->right->JourneyCode;
					rm->right = nullptr;
				}
				else{
					rm->price = rm->right->price;
					rm->JourneyCode = rm->right->JourneyCode;
					rm->right = rm->right->right;
					rm->right->parent = rm;
					
				}
			}
			else{
			TreeNode *b = x;
			TreeNode *a = x->right;
			while(a->left!=nullptr){
				b = a;
				a = a->left;
			}
			int JC = a->JourneyCode;
			int pc = a->price;
			BST S(x);
			S.remove(JC,pc);
			rm->JourneyCode = JC;
			rm->price = pc;
			}
		}
		return true;
		
	}
	else{
		return false;
	}
}

// Functions that traverse the BST in various ways!
// type is one of PRE_ORDER, POST_ORDER or IN_ORDER
// Print on cout the journey codes at nodes of the BST in the same order as
// they are encountered in the traversal order
// Print one journey code per line

void BST::traverse(int typeOfTraversal) {
if(typeOfTraversal==0){
        //preorder
        BST S(root);
        traverse_pre(S);
    }
    if(typeOfTraversal==1){
        //postorder
        BST S(root);
        traverse_post(S);
    }
    if(typeOfTraversal==2){
        //interorder
        BST S(root);
        traverse_int(S);
    }
}

void BST::traverse_pre(BST S){
    if (S.root==nullptr){
        return;
    }
    cout << S.root->JourneyCode;
    BST S1(S.root->left);
    BST S2(S.root->right);
    traverse_pre(S1);
    traverse_pre(S2);
}


void BST::traverse_post(BST S){
    if (S.root==nullptr){
        return;
    }
    BST S1(S.root->left);
    BST S2(S.root->right);
    traverse_post(S1);
    traverse_post(S2);
    cout << S.root->JourneyCode;
}

void BST::traverse_int(BST S){
    if (S.root==nullptr){
        return;
    }
    BST S1(S.root->left);
    BST S2(S.root->right);
    traverse_int(S1);
    cout << S.root->JourneyCode;
    traverse_int(S2);
}

// Returns the price of the cheapest journey
int BST::getMinimum() {
    TreeNode *x = root;
    TreeNode *y = nullptr;
    while ( x!=nullptr ){
        y = x;
        x = x->left;
    }
    return y->price;
}

// Part II

// Returns the count of journeys that are at least as expensive
// as lowerPriceBound and at most as expensive as upperPriceBound,
// both bounds included.

int BST::countJourneysInPriceBound(int lowerPriceBound, int upperPriceBound) {	
	//this will be part of a tree; base case is tree does not exist --> return 0
	//when tree exists, return left + right
	if (root==nullptr){
		return 0;
	}

	else{
		BST S1(root->left);
		BST S2(root->right);
		int i = 0;
		if ( root->price >= lowerPriceBound && root->price <=upperPriceBound){
			i = 1;
		}

		return ( S1.countJourneysInPriceBound(lowerPriceBound, upperPriceBound) + S2.countJourneysInPriceBound(lowerPriceBound, upperPriceBound) + i );
	}
}

// Store the current tree in a file called filename.  You should
// store using a scheme that uses no more disk space than that
// required to store all elements in the BST, plus perhaps a small
// constant times the number of elements.  You should also store
// in a manner such that your implementation of customLoad is as
// memory and time efficient as possible.

void BST::customStore(string filename) {
	ofstream o;
	o.open(filename);
	store(&o, root);
	o.close();
}

void BST::store(ofstream *o, TreeNode *root){
	if (root==nullptr){
		return;
	}
	*o << "(" ;
	*o << root->JourneyCode << "," << root->price ;
	TreeNode* L = root->left;
	TreeNode* R = root->right;
	store(o, L);
	store(o, R);
	*o << ")";
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
 
void BST::customLoad (int flag, string filename) {
	if(flag==3){
		ifstream i;
		i.open(filename);
		string str;
		i >> str;
		bool a = 0;
		string jc, pc;
		TreeNode * active = nullptr;
		for ( int i=1; i<str.length() ; i++ ){
			if (str[i]==','){
				a = 1;
			}
			else if (str[i]=='(' || str[i]==')'){
				int jcode = stoi(jc);
				int pcode = stoi(pc);
				insert(jcode,pcode);
				jc.clear();
				pc.clear();
				a = 0;
			}
			else if(a){
				pc.push_back(str[i]);
			}
			else{
				jc.push_back(str[i]);
			}
		}
		i.close();
	}
}
	
	//arguments will include an address of treenode
	
	//read from file string
	//till hits , store number into JC
	//till hits )or( store number into pc

	//load address into node
	//root = new TreeNode(JC,pc,nullptr,nullptr, parent)

	//call left if next openening has number less than value
	//read value
	//if(price < root->price ){
//		load("vector of characters","array of strings containing first ( =i", )
//	}
	//read value
//	if (price > )
	//call right if next openeing has number greater than value
	

	//delete till closing brackets
	//return
//}


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

// int main(){
// 	BST S;
// 	S.insert(3,3);
// 	S.insert(10,10);
// 	S.insert(1,1);
// 	S.insert(5,5);
// 	S.customStore("a.txt");
// }