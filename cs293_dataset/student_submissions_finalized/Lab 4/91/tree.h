#ifndef BST_H
#define BST_H

#include "journey.h"

#include <iostream>
#include <vector>
#include <string>
#include <climits>

// using inbuilt odering operators of journey

struct TreeNode{
    Journey j           // journey
    TreeNode* left; 	// pointer to left child of this node (nullptr, if none)
    TreeNode* right;	// pointer to right child of this node (nullptr, if none)
    TreeNode* parent;	// pointer to parent node (nullptr in case of root)

    // constructors
    TreeNode();
    TreeNode(int jrnyCode, int jrnyPrice);
    TreeNode(int jrnyCode, int jrnyPrice, TreeNode* leftChild, TreeNode* rightChild, TreeNode* parent);

    // comparison operators
    bool operator<(TreeNode const& rightArgument) const;
    bool operator==(const TreeNode const& rightArgument) const;

    // returns imbalance of subtree (that has root as this node)
    int getImbalance() const;

    // finds minimum node of subtree (that has root as this node)
    TreeNode* minimum_node() const;
    // finds maximum node of subtree (that has root as this node)
    TreeNode* maximum_node() const;

    // finds that node in subtree (that has root as this node) which has given JourneyCode and price
    TreeNode* find_node(Journey j) const;
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

    // returns the imbalance in the entire tree
    int getImbalance();
};

#endif
