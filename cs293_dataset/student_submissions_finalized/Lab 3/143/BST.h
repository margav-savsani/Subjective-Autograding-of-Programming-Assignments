#ifndef BST_H
#define BST_H
#endif

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
	
        TreeNode *root;

	// result variable is for testing purposes, Do not tamper with it!
	vector<string> result;

public:
	BST();
	BST(TreeNode *root);
	void printBST(const string& prefix, bool isLeft);
	void getBST(const string& prefix, bool isLeft);
	void clearResult();
	vector<string> getResult();
	bool insert(int JourneyCode, int price);
	bool find(int JourneyCode, int price);
	bool remove(int JourneyCode, int price);
	void traverse(int typeOfTraversal);
	int getMinimum();
        void preorder(TreeNode *root);
        void postorder(TreeNode *root);
        void inorder(TreeNode *root);
        TreeNode* successor(int JourneyCode,int price);
        

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
