#ifndef BST_H
#define BST_H

// Header file for defining a Binary Search Tree
// Reuse the binary Search Tree implemented in lab 3 as much as possible

// struct TreeNode given below is almost the same as was given to you
// in lab 3. The only exception is the addition of shortestPathLength
// and longestPathLength fields along with a member function getImbalance.
// Read the comments in the structure definition to understand the meanings
// of these.

struct TreeNode{
  int JourneyCode;	// Journey code
  int price;		// Price
  TreeNode *left;	// Left Child of this Node (NULL, if None)
  TreeNode *right;	// Right Child of this Node (NULL, if None)
  TreeNode *parent;	// The Parent Node, NULL in case of Root
  int shortestPathLength=0; // Length of shortest path from this node to a leaf
                          // where a nullptr leaf contributes a path of length 0
  int longestPathLength=0; // Length of longest path from this node to a leaf
                         // where a nullptr leaf contributes a path of length 0
  
  // Constructors: There are 3 variants of the constructor given below.
  // Please make sure you understand what each of these variants do.
  // Ask your TA or the instructor if you have a doubt.
  
  TreeNode() : price(0), JourneyCode(0), left(nullptr), right(nullptr) {}
  
  TreeNode(int jrnyCode, int jrnyPrice) : price(jrnyPrice), JourneyCode(jrnyCode), left(nullptr), right(nullptr) {}
  
  TreeNode(int jrnyCode, int jrnyPrice, TreeNode *leftChild, TreeNode *rightChild, TreeNode *parent) : price(jrnyPrice), JourneyCode(jrnyCode), left(leftChild), right(rightChild), parent(parent) {}

  // Overloaded operators
/*bool operator<(const TreeNode& rightArgument)
  {
    return (JourneyCode < rightArgument.JourneyCode);
  }

  bool operator==(const TreeNode& rightArgument)
  {
    return (JourneyCode == rightArgument.JourneyCode);
  }*/

  int getImbalance()
  {
    // Returns how imbalanced the paths starting from this node to the
    // leaves are.  A case of perfect balance would result in the
    // longest and shortest path lengths being equal, so their difference
    // will be 0 (i.e. 0 imbalance).
    // Think about when would we have a case of large imbalance.

    return (longestPathLength - shortestPathLength);
  }
  
  




 
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
  
  TreeNode *root=nullptr;
  
  	struct TreeNode* minvalnode(struct TreeNode* node)
	{
		struct TreeNode* c = node;
		while (c != NULL && c->left != NULL)
			c = c->left;
		return c;
	}
  
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
  // result variable is for testing purposes, Do not tamper with it!
  vector<string> result;
  
public:
  // ************************************************************
  // Methods for Part I
  
  // Constructors!
  BST() {root = nullptr; root->shortestPathLength =0;root->longestPathLength = 0;}
  BST(TreeNode *curr_root) {root = curr_root; root->shortestPathLength =0;root-> longestPathLength = 1;}

  // Implement your own destructor
 
 int longest(TreeNode* node){
 if(node == NULL ) return 0;
 else if(node->right==NULL) return(longest(node->left)+1);
 else if(node->left==NULL) return(longest(node->right)+1);
 else return(max(longest(node->left),longest(node->right))+1);
 }
 
  int shortest(TreeNode* node){
 if(node == NULL ) return 0;
 else if(node->right==NULL) return(shortest(node->left)+1);
 else if(node->left==NULL) return(shortest(node->right)+1);
 else return(min(shortest(node->left),shortest(node->right))+1);
 }
 
 void update(TreeNode* t){
 t->longestPathLength=longest(t);
 t->shortestPathLength=shortest(t);
 while(t->left!=NULL) update(t->left);
 while(t->right!=NULL) update(t->right);
 }
 
  
  // Returns false, if given JourneyCode is already present in the BST
  // Inserts the element and returns True otherwise
  bool insert(int JourneyCode, int price);
    
  // Return true, if the ticket with given attributes is found, false otherwise
  bool find(int JourneyCode, int price);
    
  // Returns false, if JourneyCode isn't present
  // Deletes the corresponding entry and returns True otherwise
  bool remove(int JourneyCode, int price);

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
