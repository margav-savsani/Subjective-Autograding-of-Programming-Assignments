#ifndef BST_H
#define BST_H
#endif
#include <string>
#include <fstream>
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
};



class BST{
	// Feel free to add more private/public variables and/or functions
	// But do not modify the pre-existing function signatures
	// You'd be evaluated only on your ability to implement those
	// You don't need anything more than the root of your Tree!
	// The BST is ordered by prices and not train Numbers.

	TreeNode *root;
	
//this gives minimum value node in the tree node
	struct TreeNode* minvalnode(struct TreeNode* node)
	{
		struct TreeNode* c = node;
		while (c != NULL && c->left != NULL)
			c = c->left;
		return c;
	}


	int getCount(TreeNode *root, int l, int u){

		if (!root) return 0;

		//case for improving efficiency
		if (root->price == u && root->price == l)
			return 1;

		// If current node is in range, then include it and recurr for left and right children
		if (root->price <= u && root->price >= l)
			return 1 + getCount(root->left, l, u) + getCount(root->right, l, u);

		// If current node is smaller than l, then recurr for right child and vice-reversa
		else if (root->price < l)
			return getCount(root->right, l, u);

		else return getCount(root->left, l, u);
	}

	// Given a binary search tree and a key, this function deletes the key and returns the new root
	struct TreeNode* deleteNode(struct TreeNode* root, int key, int value)
	{
		
		if (root == NULL)
			return root;

		// If the key to be deleted is smaller than the root's key, then it lies in left subtree
		if (key < root->price)
			root->left = deleteNode(root->left, key,value);

		// If the key to be deleted is greater than the root's key, then it lies in right subtree
		else if (key > root->price)
			root->right = deleteNode(root->right, key,value);

		// if key is same as root's key, then node to be deleted
		else if(root->JourneyCode==value && key == root->price) {
			// case-1:node has no child
			if (root->left==NULL and root->right==NULL)
				return NULL;

			// case-2:node with only one child
			else if (root->left == NULL) {
				struct TreeNode* temp = root->right;
				free(root);
				return temp;
			}
			else if (root->right == NULL ) {
				struct TreeNode* temp = root->left;
				free(root);
				return temp;
			}

			// case-3:node with two children. Get the inorder successor (smallest in the right subtree)
			struct TreeNode* temp = minvalnode(root->right);

			// Copy the inorder successor's content to this node
			root->price = temp->price;
			root->JourneyCode= temp->JourneyCode;

			// Delete the inorder successor
			root->right = deleteNode(root->right, temp->price, temp->JourneyCode);
		}
		return root;
	}


	void storePreorder(struct TreeNode* node,string f){
		ofstream outfile;
		outfile.open(f);
		if (node == NULL)
			return;

		outfile << node->JourneyCode << " "<<node->price<<endl;
		storePreorder(node->left,f);
		storePreorder(node->right,f);
		outfile.close();
	}

//function to construct BST from preorder
TreeNode* construct(int code[], int price[], int* i, int key,int min, int max, int size)
{
	// Base case
	if (*i >= size)
		return NULL;

	TreeNode* node = NULL;


	if (key > min && key < max) {

		node = new TreeNode(code[*i],price[*i]);
		*i = *i + 1;

		if (*i < size) {
// All nodes which are in range {min .. key} will go in left subtree, and first such node will be root of left subtree
			node->left = construct(code,price, i,price[*i],min, key, size);
		}
		if (*i < size) {
// All nodes which are in range {key .. max} will go in right subtree, and first such node will be root of right subtree
			node->right = construct(code,price, i,price[*i],key, max, size);
		}
	}

	return node;
}

	void printPreorder(struct TreeNode* node){
		if (node == NULL)
			return;

		cout << node->JourneyCode << " ";

		printPreorder(node->left);
		printPreorder(node->right);
	}
	void printPostorder(struct TreeNode* node){
		if (node == NULL)
			return;

		printPreorder(node->left);
		printPreorder(node->right);

		cout << node->JourneyCode << " ";    
	}
	void printInorder(struct TreeNode* node){
		if (node == NULL)
			return;

		printPreorder(node->left);

		cout << node->JourneyCode << " ";

		printPreorder(node->right);
	}

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
