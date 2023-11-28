#ifndef BST_H
#define BST_H
#endif

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
	
	
	
	void getBST(const string& prefix, bool isLeft);
	void clearResult();
	vector<string> getResult();
	
	
	bool insert(int JourneyCode, int price);


	
	bool find(int JourneyCode, int price);
	
	
	int heightOfTree(TreeNode* root);
	
	
	bool remove(int JourneyCode, int price);
	
	
	struct TreeNode*  findSuccessor(struct TreeNode* node);
	
	
	
	void  preorderTraversal(struct TreeNode* root);
	
	void storingInArrayPre(TreeNode* root, int* arr, int &n);
	
	
	void storingInArrayIn(TreeNode* root, int* arr, int &n);
	
	
	
	void postorderTraversal(struct TreeNode* root);
	
	
	void inorderTraversal(struct TreeNode* root);
	
	
	void traverse(int typeOfTraversal);




int getNodes(TreeNode*root, int low, int high);
	
	int getMinimum();

       
        int countJourneysInPriceBound(int lowerPriceBound, int upperPriceBound);
	
	
	void customStore(string filename);
	
	
  
        void customLoad (int flag, string filename);

};
