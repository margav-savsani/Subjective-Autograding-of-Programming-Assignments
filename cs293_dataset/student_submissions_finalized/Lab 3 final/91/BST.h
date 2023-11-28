// Arnav Aditya Singh
// 210050018
#ifndef BST_H
#define BST_H

#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <climits>

using namespace std;

struct TreeNode{
    int JourneyCode;	// train number
    int price;  		// price
    TreeNode* left; 	// pointer to left child of this node (nullptr, if none)
    TreeNode* right;	// pointer to right child of this node (nullptr, if none)
    TreeNode* parent;	// pointer to parent node (nullptr in case of root)

    // Constructors
    TreeNode();
    TreeNode(int jrnyCode, int jrnyPrice);
    TreeNode(int jrnyCode, int jrnyPrice, TreeNode* leftChild, TreeNode* rightChild, TreeNode* parent);

    // finds minimum node of subtree (that has root as this node)
    TreeNode* minimum_node();
    // finds maximum node of subtree (that has root as this node)
    TreeNode* maximum_node();

    // finds that node in subtree (that has root as this node) which has given JourneyCode and price
    TreeNode* find_node(int JourneyCode, int price);

    // traverses the subtree (that has root as this node) according to specified type of traversal
    void traverse(int typeOfTraversal);

    // append the subtree in a file
    void customStore(std::string const& filename);
};

class BST{
	TreeNode* root;

    // returns pointer to successor node
    TreeNode* successor(TreeNode* v);
    // returns pointer to predecessor node
    TreeNode* predecessor(TreeNode* v);
    
                // result variable is for testing purposes, Do not tamper with it!
	vector<std::string> result;

public:
        // ****************************************************************
    // Methods for Part I

	// Constructors!
	BST();
	BST(TreeNode* root);
    // Destructor
    ~BST();

    // This function prints the BST using ASCII characters using the
    // format:
    //
    //   root
    //       |-- left subtree
    //       |__ right subtree
    //
    // where the left and right subtrees are printed recursively in
    // the same format.
	void printBST(std::string const& prefix, bool isLeft);
	
	
	// The three functions below are for evaluation purposes, Do not tamper with them!
	void getBST(std::string const& prefix, bool isLeft);
	void clearResult();
	vector<std::string> getResult();
	
	// returns false, if given JourneyCode is already present in the BST
	// inserts the element and returns true otherwise
	bool insert(int JourneyCode, int price);


	// returns true, if the ticket with given attributes is found, false otherwise
	bool find(int JourneyCode, int price);
	
	// returns false, if JourneyCode isn't present
	// deletes the corresponding entry and returns true otherwise
	bool remove(int JourneyCode, int price);
	
	// Functions that traverse the BST in various ways!
	// type can be PRE_ORDER, POST_ORDER or IN_ORDER, which
        // #defined numeric constants defined in BST.cpp
        // This function prints on cout the journey codes (one per line)
        // encountered on traversing the BST in the given traversal order
	void traverse(int typeOfTraversal);

	// returns the price of the cheapest journey
	int getMinimum();

        // ****************************************************************
	// Methods for Part II
    
    // returns the count of journeys that are at least as expensive
    // as lowerPriceBound and at most as expensive as upperPriceBound,
    // both bounds included
    int countJourneysInPriceBound(int lowerPriceBound, int upperPriceBound);
	
    // stores BST in file filename
	void customStore(std::string const& filename);
	
    // loads BSt from file filename
    void customLoad (int flag, std::string const& filename);
    
    // load subtree utility function
    TreeNode* constructTree(std::vector<int> const& jcs, std::vector<int> const& prs, int& Index, int jc, int pr, int min, int max);
};

#endif
