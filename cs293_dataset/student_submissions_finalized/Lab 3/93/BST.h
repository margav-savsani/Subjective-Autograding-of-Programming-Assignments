#ifndef BST_H
#define BST_H
#endif

using namespace std;

// Default Node struct
// You may add more variables/function signatures, but make sure you do not rename/delete what's already present.

struct TreeNode{
    int JourneyCode;	// Train Number
    int price;		// Price
    TreeNode *left;	// Left Child of this Node (NULL, if None)
    TreeNode *right;	// Right Child of this Node (NULL, if None)
    TreeNode *parent;	// The Parent Node, NULL in case of Root

    // Constructors
  
    TreeNode() : price(0), JourneyCode(0), left(nullptr), right(nullptr) {}
    TreeNode(int jrnyCode, int jrnyPrice) : price(jrnyPrice), JourneyCode(jrnyCode), left(nullptr), right(nullptr) {}
    TreeNode(int jrnyCode, int jrnyPrice, TreeNode *leftChild, TreeNode *rightChild, TreeNode *parent) : price(jrnyPrice), JourneyCode(jrnyCode), left(leftChild), right(rightChild), parent(parent) {}
    
	TreeNode* is_present_in_subtree(int jcode){
		//returns the address of the TreeNode with the same JourneyCode as jcode
		//returns NULL if not present
		if(JourneyCode==jcode)
			return this;
		if(left){
			TreeNode* a = left->is_present_in_subtree(jcode);
			if(a) return a;
		}
		if(right){
			TreeNode* a = right->is_present_in_subtree(jcode);
			if(a) return a;
		}
		return NULL;
	}
	TreeNode* find_in_subtree(int jcode, int pr){
		if(price==pr){
			if(JourneyCode==jcode)
				return this;
			else if (left) return left->find_in_subtree(jcode, pr);
			else return NULL;
		}
		if(price>pr){
			if(left)
				return left->find_in_subtree(jcode, pr);
			else return NULL;
		}
		else{
			if(right)
				return right->find_in_subtree(jcode, pr);
			else return NULL;
		}
		return NULL;
	}

	TreeNode* get_min_in_subtree(){
		if(left) return left->get_min_in_subtree();
		else return this;
	}

	void print_pre_order_of_subtree(){
		cout<<JourneyCode<<endl;
		if(left) left->print_pre_order_of_subtree();
		if(right) right->print_pre_order_of_subtree();
	}	

	void print_in_order_of_subtree(){
		if(left) left->print_in_order_of_subtree();
		cout<<JourneyCode<<endl;
		if(right) right->print_in_order_of_subtree();
	}

	void print_post_order_of_subtree(){
		if(left) left->print_post_order_of_subtree();
		if(right) right->print_post_order_of_subtree();
		cout<<JourneyCode<<endl;
	}

	TreeNode* delete_root(){
		if(left && right){
			TreeNode* min = right->get_min_in_subtree();
			JourneyCode = min->JourneyCode;
			price = min->price;
			min->delete_root();
		}
		else if(left){
			if(!parent) {left->parent = NULL; return left;}
			else{
				left->parent = parent;
				if(parent->left == this) parent->left = left;
				else if(parent->right == this) parent->right = left;
				return NULL;
			}
		}
		else if(right){
			if(!parent) {right->parent = NULL; return right;}
			else{
				right->parent = parent;
				if(parent->left == this) parent->left = right;
				else if(parent->right == this) parent->right = right;
			}
		}
		else if(parent){
			if(parent->left==this) parent->left = NULL;
			else if(parent->right==this) parent->right = NULL;
			return NULL;
		}
		return NULL;
	}
	bool insert_in_subtree(int jcode, int pr){
		if(price >= pr){
			if(!left) left = new TreeNode(jcode, pr, NULL, NULL, this);
			else left->insert_in_subtree(jcode, pr);
		}
		else if(price < pr){
			if(!right) right = new TreeNode(jcode, pr, NULL, NULL, this);
			else right->insert_in_subtree(jcode, pr);
		}
		return true;
	}
};



class BST{
	// Feel free to add more private/public variables and/or functions
	// But do not modify the pre-existing function signatures
	// You'd be evaluated only on your ability to implement those
	// You don't need anything more than the root of your Tree!
	// The BST is ordered by prices and not train Numbers.

	TreeNode *root;

	// result variable is for testing purposes, Do not tamper with it!
	vector<string> result;

public:
        // ************************************************************
        // Methods for Part I
  
	// Constructors!
	BST();
	BST(TreeNode *root);
	
        // This function prints the BST using ASCII characters using the
        // format:
        //
        //   root
        //       |-- left subtree
        //       |__ right subtree
        //
        // where the left and right subtrees are printed recursively in
        // the same format.
        //
	// We have done this for you! Please see BST.cpp for details
	// You may use this for debugging purposes.
        //
	void printBST(const string& prefix, bool isLeft);
	
	
	// The three functions below are for evaluation purposes, Do not tamper with them!
	void getBST(const string& prefix, bool isLeft);
	void clearResult();
	vector<string> getResult();
	
	// Returns false, if given JourneyCode is already present in the BST
	// Inserts the element and returns True otherwise
	bool insert(int JourneyCode, int price);


	// Return true, if the ticket with given attributes is found, false otherwise
	bool find(int JourneyCode, int price);
	
	// Returns false, if JourneyCode isn't present
	// Deletes the corresponding entry and returns True otherwise
	bool remove(int JourneyCode, int price);
	
	// Functions that traverse the BST in various ways!
	// type can be PRE_ORDER, POST_ORDER or IN_ORDER, which
        // #defined numeric constants defined in BST.cpp
        // This function prints on cout the journey codes (one per line)
        // encountered on traversing the BST in the given traversal order
	void traverse(int typeOfTraversal);

	// Returns the price of the cheapest journey
	int getMinimum();

        // ****************************************************************
	// Methods for Part II

	// Returns the count of journeys that are at least as expensive
        // as lowerPriceBound and at most as expensive as upperPriceBound,
        // both bounds included.
        int countJourneysInPriceBound(int lowerPriceBound, int upperPriceBound);
	
	// Store the current tree in a file called filename.  You should
        // store using a scheme that uses no more disk space than that
        // required to store all elements in the BST, plus perhaps a small
        // constant times the number of elements.  You should also store
        // in a manner such that your implementation of customLoad is as
        // memory and time efficient as possible.
	void customStore(string filename);
	
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
  
        void customLoad (int flag, string filename);

};

