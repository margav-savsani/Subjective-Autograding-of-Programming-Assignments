#ifndef BST_H
#define BST_H

#include <iostream>
#include <vector>
#include <string>
#include <climits>

#include "journey.h"

// using inbuilt ordering operators of journey

struct TreeNode{
    Journey journey;        // journey
    TreeNode* left; 	    // pointer to left child of this node (nullptr, if none)
    TreeNode* right;	    // pointer to right child of this node (nullptr, if none)
    TreeNode* parent;	    // pointer to parent node (nullptr in case of root)
    int shortestPathLength; // length of shortest path from this node to a leaf (where a nullptr leaf contributes a path of length 0)
    int longestPathLength; // length of longest path from this node to a leaf (where a nullptr leaf contributes a path of length 0)


    // constructors
    TreeNode();
    TreeNode(int jrnyCode, int jrnyPrice);
    TreeNode(int jrnyCode, int jrnyPrice, TreeNode* leftChild, TreeNode* rightChild, TreeNode* parent);
    TreeNode(Journey journey, TreeNode* leftChild, TreeNode* rightChild, TreeNode* parent);

    // returns imbalance of subtree (that has root as this node)
    int getImbalance();

    // finds minimum node of subtree (that has root as this node)
    TreeNode* minimum_node();
    // finds maximum node of subtree (that has root as this node)
    TreeNode* maximum_node();

    // finds that node in subtree (that has root as this node) which has given JourneyCode and price
    TreeNode* find_node(Journey j);

    // updates path lengths
    void updatePathLengths();
};

class BST {
	TreeNode* root;

    // returns pointer to successor node
    TreeNode* successor(TreeNode* v);
    // returns pointer to predecessor node
    TreeNode* predecessor(TreeNode* v);
    
    // result variable is for testing purposes, Do not tamper with it!
    std::vector<std::string> result;

  public:
	// constructors
	BST();
	BST(TreeNode* root);
    // destructor
    ~BST();

    // prints the BST using ASCII characters using the
    // format:
    //   root
    //       |-- left subtree
    //       |__ right subtree
    // where the left and right subtrees are printed recursively in
    // the same format.
	void printBST(std::string const& prefix, bool isLeft = false);
	
	
	// The three functions below are for evaluation purposes, Do not tamper with them!
	void getBST(std::string const& prefix, bool isLeft);
	void clearResult();
    std::vector<std::string> getResult();
	
	// returns false, if given JourneyCode is already present in the BST
	// inserts the element and returns true otherwise
	bool insert(Journey journey);

	// returns true, if the ticket with given attributes is found, false otherwise
	bool find(Journey journey);
	
	// returns false, if JourneyCode isn't present
	// deletes the corresponding entry and returns true otherwise
	bool remove(Journey journey);

    // returns the imbalance in the entire tree
    int getImbalance();
};

#endif
