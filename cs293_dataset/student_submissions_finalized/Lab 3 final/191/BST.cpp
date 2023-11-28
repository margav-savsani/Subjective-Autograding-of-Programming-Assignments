#include <bits/stdc++.h>
#include <iostream>
#include <vector>
#include <string>
#include<fstream>
#include<sstream>

using namespace std;

#include "BST.h"

#define PRE_ORDER 0
#define POST_ORDER 1
#define IN_ORDER 2
#define LOAD_FULL_BST 3
#define LOAD_LEFT_SUBTREE 4


// PLEASE FILL IN THE BODIES OF THE FOLLOWING FUNCTIONS

BST::BST(){
	 root = nullptr; //makes root  nullptr
}
BST::BST(TreeNode *root){
	this->root = root; 	//makes root of this tree point to the given root
}

// Returns false, if given JourneyCode is already present in the BST
// Inserts the element and returns True otherwise
bool BST::insert(int JourneyCode, int price) { 
	
	
	TreeNode *ptr = root;
	bool done{false};
	
	TreeNode *node;
	node = new TreeNode;
	node->JourneyCode = JourneyCode;
	node->price = price;
	node->left = nullptr;
	node->right = nullptr;
	
	if(root == nullptr){	//special case when the insertion is the first insertion in an empty BST
		root = node;
		node->parent = nullptr;
		return true;
	}
	
	if(find(JourneyCode, price)){	//check if JourneyCode and price are already present or not, if they are return false and exit fomr this method
		return false;
	}
	
	else{
		
		while(true){
			//tracing where the insertion should be done so that prices lower than or equal to a node goes to the left subtree of that node else right subtree
			if(ptr->price >= price){	
				if(ptr->left == nullptr){
					node->parent = ptr;
					ptr->left = node;
					node = nullptr;
					break;
				}
				else{
					ptr = ptr->left;
				}
			}
			
			else {
				if(ptr->right == nullptr){
					node->parent = ptr;
					ptr->right = node;
					node = nullptr;
					break;
				}
				else{
					ptr = ptr->right;
				}
			}
		}
		return true;
	}
}

bool BST::find(int JourneyCode, int price){
	TreeNode *ptr = myfind(JourneyCode, price); //ptr is the pointer to the node which has the required JourneyCode and price
	if(ptr == nullptr){
		return false;
	}
	else{
		return true;
	}
}

// Return True, if the ticket with given attributes is found, false otherwise
//myfind method returns the pointer of the TreeNode struct if it is found nullptr otherwise 
TreeNode* BST::myfind(int JourneyCode, int price) { 
	
	TreeNode *ptr = root;
	while(true){
		if(ptr == nullptr)
			return nullptr;
		else{
			if(ptr->price> price){
				ptr=ptr->left;
			}
			else if(ptr->price<price){
				ptr=ptr->right;
			}
			else if(ptr->price==price){
				if(ptr->JourneyCode == JourneyCode)
					return ptr;
				else ptr=ptr->left;
			}
		}
	}
}


// Returns false, if JourneyCode isn't present
// Deletes the corresponding entry and returns True otherwise
bool BST::remove(int JourneyCode, int price) {  

	TreeNode *ptr=myfind(JourneyCode, price);//find the treeNode to be removed and pass it on to the myremove function which returns true if it is successful in deletion false otherwise.
	if(myremove(ptr))
		return true;
	else
		return false;	
}

//myremove function returns true if it is successful in deletion false otherwise.
bool BST::myremove(TreeNode *ptr){
	if(ptr==nullptr)
		return false;
	
	else{
		//case 1--without no children
		if(ptr->left == nullptr && ptr->right==nullptr){
			if(ptr->parent == nullptr)
				root = nullptr;
			if(ptr->parent->left==ptr){
				ptr->parent->left=nullptr;
			}
			if(ptr->parent->right==ptr){
				ptr->parent->right=nullptr;
			}
			ptr->parent=nullptr;
			return true;
		}	
		
		//case 2--with 1 child
		//the next 2 else if are similar ,only difference is one deals when left pointer is nullptr andthe other deals with right pointer 
		else if(ptr->left==nullptr){
			ptr->right->parent=ptr->parent;
			if(ptr->parent==nullptr){
				root=ptr->right;
				ptr->right=nullptr;
			}
			else if(ptr->parent->left==ptr){
				ptr->parent->left=ptr->right;
			}
			else if(ptr->parent->right==ptr){
				ptr->parent->right=ptr->right;
			}
			ptr->parent=nullptr;
			ptr->right=nullptr;
			return true;
		}
		
		else if(ptr->right==nullptr){
			ptr->left->parent=ptr->parent;
			if(ptr->parent==nullptr){
				root=ptr->left;
				ptr->left=nullptr;
			}
			else if(ptr->parent->left==ptr){
				ptr->parent->left=ptr->left;
			}
			else if(ptr->parent->right==ptr){
				ptr->parent->right=ptr->left;
			}
			ptr->parent=nullptr;
			ptr->left=nullptr;
			return true;
		}
		
		//case 3--with 2 child
		//uses recursion
		else{
			TreeNode *find_replacement = getMaxNode(ptr->left);
			ptr->price=find_replacement->price;
			ptr->JourneyCode=find_replacement->JourneyCode;
			myremove(find_replacement);
			return true;
		}
	}
	return false;
}
	
// Functions that traverse the BST in various ways!
// type is one of PRE_ORDER, POST_ORDER or IN_ORDER
// Print on cout the journey codes at nodes of the BST in the same order as
// they are encountered in the traversal order
// Print one journey code per line

//traversal of a BST is done using this method
void BST::traverse(int typeOfTraversal) {
	if(root == nullptr)
		return;
	TreeNode *ptr=root;
	if(typeOfTraversal == 0){
		traverse_pre(root); //pre-order traversal
	}
	
	if(typeOfTraversal == 1){
		traverse_post(root);//post-order traversal
	}
	
	if(typeOfTraversal == 2){
		traverse_in(root);//inorder traversal
	}
}


//recursive funciton for performing pre order traversal
void BST::traverse_pre(TreeNode *ptr){
	if(ptr == nullptr)
		return;
	cout<< ptr->JourneyCode <<endl;
	traverse_pre(ptr->left);
	traverse_pre(ptr->right);
}

//recursive function for performing in order traversal 
void BST::traverse_in(TreeNode *ptr){
	if(ptr == nullptr)
		return;
	traverse_in(ptr->left);
	cout<< ptr->JourneyCode <<endl;
	traverse_in(ptr->right);
}

//recursive function for performing post order traversal 
void BST::traverse_post(TreeNode *ptr){
	if(ptr == nullptr)
		return;
	traverse_post(ptr->left);
	traverse_post(ptr->right);
	cout<< ptr->JourneyCode <<endl;
}	

// Returns the price of the cheapest journey
int BST::getMinimum() {
	TreeNode *ptr = root;
	while(true){
		if(ptr == nullptr)
			return 0;
		if(ptr->left == nullptr)
			return ptr->price;
		else{
			ptr = ptr->left;
		}
	}
}

//function used in the myremove method which returns the pointer to the node with maximum price and root as ptr (an argument)
TreeNode * BST::getMaxNode(TreeNode* ptr){
	while(true){
		if(ptr == nullptr)
			return 0;
		if(ptr->right == nullptr)
			return ptr;
		else{
			ptr = ptr->right;
		}
	}
}


// Part II

// Returns the count of journeys that are at least as expensive
// as lowerPriceBound and at most as expensive as upperPriceBound,
// both bounds included.
int BST::countJourneysInPriceBound(int lowerPriceBound, int upperPriceBound){
	return myrange(lowerPriceBound, upperPriceBound, root);	
}


//checks with a node, node price can be in three intervals between upper bound and lower bound or lower than the lower bound or higher than the higher bound. Makes comparisons on the basis of where in the three ranges is it and hence tries to save time since we are not traversing the full tree
int BST::myrange(int lowerPriceBound, int upperPriceBound, TreeNode *ptr){
	int answer{0};
	if(ptr==nullptr)
		return 0;
	else{
		int price = ptr->price;
		if(price>=lowerPriceBound && price<=upperPriceBound){
				answer++;
				answer+=myrange(lowerPriceBound, upperPriceBound, ptr->left);
				answer+=myrange(lowerPriceBound, upperPriceBound, ptr->right);
		}
		
		else if(price<lowerPriceBound){
			answer+=myrange(lowerPriceBound, upperPriceBound, ptr->right);
		}
		
		else if(price>upperPriceBound){
			answer+=myrange(lowerPriceBound, upperPriceBound, ptr->left);
		}
		
		return answer;
	}
}


// Store the current tree in a file called filename.  You should
// store using a scheme that uses no more disk space than that
// required to store all elements in the BST, plus perhaps a small
// constant times the number of elements.  You should also store
// in a manner such that your implementation of customLoad is as
// memory and time efficient as possible.

//store function
void BST::customStore(string filename) { 
	ofstream file;
	file.open(filename);
	mystore(file, root);
	file.close();
}

//mystore function 
//storing is done in the following manner :
//left subtree is between () and right subtree is between is between is between {} 
void BST::mystore(ofstream &file, TreeNode *ptr){

	if(ptr == nullptr)
		return;
	file<< ptr->JourneyCode <<" "<< ptr->price <<endl;
	if(ptr->left != nullptr){
		file<<"("<<endl;
		mystore(file, ptr->left);
		file<<")"<<endl;
	}
	if(ptr->right != nullptr){
		file<<"{"<<endl;
		mystore(file, ptr->right);
		file<<"}"<<endl;
	}
	
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
	//custom load is done on the basis of strategy of the customStore member method
	// flag is there to choose from full BST or just left subtree of full BST
	//implemetation:	if see a '(' then just make a left child of the current pointer. ')' represents go to the parent , '{' implies make a right child of the current pointer . '}' this represents go to the parent
	if(flag != 3 && flag != 4)
		return;
	
	root = nullptr;
	ifstream file;
	file.open(filename);
	string line;
	
	if(!file){
		cout<<"File not found"<<endl;
		return;
	}
	
	//for full BST
	if(flag == 3){
		
		
		//getline gets line by line string 
		//stringstream objects are used to extract journeyCode and prices from a single line
		if(getline(file, line)){
			stringstream s{line};
			string code;
			string price;
			s>>code>>price;
			TreeNode *p = new TreeNode();
			root = p;
			root->parent =nullptr;
			root->left=nullptr;
			root->right=nullptr;
			root->price = stoi(price);
			root->JourneyCode = stoi(code);
			p = nullptr;
		}
		
		TreeNode *ptr=root;
		while(getline(file, line)){
			
			if(line=="("){
				TreeNode* p=new TreeNode();
				ptr->left = p;
				p->parent = ptr;
				p->left=nullptr;
				p->right=nullptr;
				p=nullptr;
				ptr = ptr->left;
			}
			
			else if(line=="{"){
				TreeNode* p=new TreeNode();
				ptr->right = p;
				p->parent = ptr;
				p->left=nullptr;
				p->right=nullptr;
				p=nullptr;
				ptr = ptr->right;
			}
			
			else if(line==")"||line=="}"){
				ptr = ptr->parent;
			}
			
			else{
				stringstream s{line};
				string code;
				string price;
				s>>code>>price;
				ptr->price = stoi(price);
				ptr->JourneyCode = stoi(code);
			}
		}
	}
		
		//For left subtree only
		//Similar to the case of full BST only differs in the starting 
	if(flag == 4){
		
		int arr{0};
		
		if(getline(file, line)){
			if(getline(file,line)){
				if(line=="("){
					arr++;
				}
				else{
					return;
				}
			}	
		}
		
		root = new TreeNode();
		root->parent=nullptr;
		root->left=nullptr;
		root->right=nullptr;
		
		TreeNode *ptr=root;
		while(getline(file, line)){
		
			
			if(line=="("){
				TreeNode* p=new TreeNode();
				ptr->left = p;
				p->parent = ptr;
				p->left=nullptr;
				p->right=nullptr;
				p=nullptr;
				ptr = ptr->left;
				arr++;
			}
			
			else if(line=="{"){
				TreeNode* p=new TreeNode();
				ptr->right = p;
				p->parent = ptr;
				p->left=nullptr;
				p->right=nullptr;
				p=nullptr;
				ptr = ptr->right;
			}
			
			else if(line==")"){
				arr--;
				if(arr!=0)
					ptr = ptr->parent;
				else
					break;
			}
			
			else if(line=="}"){
				ptr = ptr->parent;
			}
			
			else{
				stringstream s{line};
				string code;
				string price;
				s>>code>>price;
				ptr->price = stoi(price);
				ptr->JourneyCode = stoi(code);
			}
		}
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
