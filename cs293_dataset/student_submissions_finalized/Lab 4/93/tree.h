#ifndef BST_H
#define BST_H
#endif

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
  TreeNode *left;	// Left Child of this Node (NULL, if None)
  TreeNode *right;	// Right Child of this Node (NULL, if None)
  TreeNode *parent;	// The Parent Node, NULL in case of Root
  int shortestPathLength; // Length of shortest path from this node to a leaf
                          // where a nullptr leaf contributes a path of length 0
  int longestPathLength; // Length of longest path from this node to a leaf
                         // where a nullptr leaf contributes a path of length 0
  
  // Constructors: There are 3 variants of the constructor given below.
  // Please make sure you understand what each of these variants do.
  // Ask your TA or the instructor if you have a doubt.
  
  TreeNode() : price(0), JourneyCode(0), left(nullptr), right(nullptr) {}
  
  TreeNode(int jrnyCode, int jrnyPrice) : price(jrnyPrice), JourneyCode(jrnyCode), left(nullptr), right(nullptr) {}
  
  TreeNode(int jrnyCode, int jrnyPrice, TreeNode *leftChild, TreeNode *rightChild, TreeNode *parent) : price(jrnyPrice), JourneyCode(jrnyCode), left(leftChild), right(rightChild), parent(parent) {}

  int getImbalance()
  {
    // Returns how imbalanced the paths starting from this node to the
    // leaves are.  A case of perfect balance would result in the
    // longest and shortest path lengths being equal, so their difference
    // will be 0 (i.e. 0 imbalance).
    // Think about when would we have a case of large imbalance.

    return (longestPathLength - shortestPathLength);
  }
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
		//finds an element in the subtree
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
		//returns the minimum element in the subtree(including the root)
		if(left) return left->get_min_in_subtree();
		else return this;
	}

	TreeNode* get_max_in_subtree(){
		//returns the maximum element in the subtree(including the root)
		if(right) return right->get_max_in_subtree();
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
	int get_size(){
		int size = 1;
		if(left) size+=left->get_size();
		if(right) size+=right->get_size();
		return size;
	}
	int countJourneysinPriceBoundinSubtree(int lowerPriceBound, int upperPriceBound){
		int count = 0;
		if(price<lowerPriceBound){
			if(right) count+=right->countJourneysinPriceBoundinSubtree(lowerPriceBound, upperPriceBound);
		}
		else if(price>upperPriceBound){
			if(left) count+=left->countJourneysinPriceBoundinSubtree(lowerPriceBound, upperPriceBound);
		}
		else{
			count+=1;
			if(left) count+=left->countJourneysinPriceBoundinSubtree(lowerPriceBound, upperPriceBound);
			if(right) count+=right->countJourneysinPriceBoundinSubtree(lowerPriceBound, upperPriceBound);
		}
		return count;
	}
	void customStoreSubTree(ofstream &f){
		//adds a -1 if the left branch is being added
		//adds a -2 if any branch is empty
		//if the root is a leaf, adds only the root
		f<<price<<" "<<JourneyCode<<endl;
		if(!left&&!right) return;
		f<<"-1"<<endl;
		if(left) left->customStoreSubTree(f);
		else f<<"-2"<<endl;
		if(right) right->customStoreSubTree(f);
		else f<<"-2"<<endl;
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
  
  TreeNode *root;
  
  // result variable is for testing purposes, Do not tamper with it!
  vector<string> result;
  
public:
  // ************************************************************
  // Methods for Part I
  
  // Constructors!
  BST() {root = nullptr; root->shortestPathLength = root->longestPathLength = 0;}
  BST(TreeNode *curr_root) {root = curr_root; root->shortestPathLength = root->longestPathLength = 1;}

  // Implement your own destructor
  ~BST() {};
  
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
  
