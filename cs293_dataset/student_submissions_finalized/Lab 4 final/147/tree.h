#ifndef BST_H
#define BST_H

// Header file for defining a Binary Search Tree
// Reuse the binary Search Tree implemented in lab 3 as much as possible

// struct TreeNode given below is almost the same as was given to you
// in lab 3. The only exception is the addition of shortestPathLength
// and longestPathLength fields along with a member function getImbalance.
// Read the comments in the structure definition to understand the meanings
// of these.
//

struct TreeNode{
    int JourneyCode;	// Journey code
    int price;		// Price
    TreeNode *left = nullptr;	// Left Child of this Node (NULL, if None)
    TreeNode *right = nullptr;	// Right Child of this Node (NULL, if None)
    TreeNode *parent = nullptr;	// The Parent Node, NULL in case of Root
    int shortestPathLength = 0; // Length of shortest path from this node to a leaf
    int longestPathLength = 0; // Length of longest directed path from this node to a leaf
    // A leaf has a shortest and longest path length of length 0
    // path length := number of edges (usual definition of path length)

    // Constructors: There are 3 variants of the constructor given below.
    TreeNode() : price(0), JourneyCode(0){}
    TreeNode(int jrnyCode, int jrnyPrice) : price(jrnyPrice), JourneyCode(jrnyCode){}
    TreeNode(int jrnyCode, int jrnyPrice, TreeNode *parent) : price(jrnyPrice), JourneyCode(jrnyCode), parent(parent){}
    TreeNode(int jrnyCode, int jrnyPrice, TreeNode *leftChild, TreeNode *rightChild, TreeNode *parent)
    : price(jrnyPrice), JourneyCode(jrnyCode), left(leftChild), right(rightChild), parent(parent){}
    ~TreeNode(){ 
        delete left; delete right; // we mustn't do `delete parent` since parent has already been freed.
    }

    // Overloaded operators
    bool operator<(const TreeNode& other) const{ return (JourneyCode < other.JourneyCode); }
    bool operator==(const TreeNode& other) const{ return (JourneyCode == other.JourneyCode); }

    int getImbalance()
    {
      // Returns how imbalanced the paths starting from this node to the
      // leaves are.  A case of perfect balance would result in the
      // longest and shortest path lengths being equal, so their difference
      // will be 0 (i.e. 0 imbalance).
      // Think about when would we have a case of large imbalance.

      return (longestPathLength - shortestPathLength);
    }
      
    // aside: Note that the inline initializers are called as fallback, if the ctor init list does not initialize the member, instead of calling the default constructor on the member. Of course, if the inline initialization is just a declaration, the default ctor will still be called on the member.
};

// class BST given below is a slight modification of what it was in
// lab 3.  A few new fields have been introduced, and some member functions
// have been removed, since they are no longer needed for the current
// assignment.

// Note however that unlike in lab 3 where you had to build the BST using
// ordering of prices, this time we will build the BST using ordering of
// journey codes.

class BST{
    // Feel free to add more private/public variables and/or functions
    // But do not modify the pre-existing function signatures
    
    TreeNode *root;
    
    // result variable is for testing purposes, Do not tamper with it!
    vector<string> result;
  
public:
    // ************************************************************
    // Methods for Part I
    
    // Constructors!
    BST(): root(nullptr){}
    BST(TreeNode *root): root(root){}//{ root->shortestPathLength = root->longestPathLength = 1;} // no need of this, since *root is already initialized.

    // Implement your own destructor
    ~BST(){ delete root; }
    
    // inserts an element given its parent and whether it is a left child or not.
    // we expect that parent is a valid node of the tree.
    TreeNode *insert(int journeyCode, int price, TreeNode *parent, bool left);
       
    // // Return true, if the ticket with given attributes is found, false otherwise
    // bool find(int JourneyCode, int price);
      
    // // Returns false, if JourneyCode isn't present
    // // Deletes the corresponding entry and returns True otherwise
    // bool remove(int JourneyCode, int price);

    // Returns the imbalance of the root node of the BST
    int getImbalance();

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
    
};
  
#endif
