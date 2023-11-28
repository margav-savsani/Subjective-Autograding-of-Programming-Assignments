#ifndef BST_H
#define BST_H
#endif
#include <string.h>
#include <fstream>
#include <vector>
using namespace std;
// Default Node struct
// You may add more variables/function signatures, but make sure you do not rename/delete what's already present.

struct TreeNode{
    int JourneyCode;	// Train Number
    int price;		// Price
    TreeNode *left;	// Left Child of this Node (NULL, if None)
    TreeNode *right;	// Right Child of this Node (NULL, if None)
    TreeNode *parent;	// The Parent Node, NULL in case of Root
    int longestpath;
    int shortestpath;
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
	vector <string> result;

public:
        // ************************************************************
        // Methods for Part I

	// Constructors!
	BST();
	BST(TreeNode *root);
	
	void printBST(const string& prefix, bool isLeft);
	
        int longestPath();
        int shortestPath();
	int pathDifference();
	
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
	
        //updates the nodes and their path lengths
        void updateLength();
	TreeNode* get_root();
};
