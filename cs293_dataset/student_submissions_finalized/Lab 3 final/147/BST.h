#ifndef BST_H
#define BST_H

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
    TreeNode(int jrnyCode, int jrnyPrice, TreeNode *parent) : price(jrnyPrice), JourneyCode(jrnyCode), left(nullptr), right(nullptr), parent(parent) {}
    bool operator<(const TreeNode &other) const{ return price < other.price; }
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
	
	
	// The three functions below are for evaluation purposes, Do not tamper with them!
	void getBST(const string& prefix, bool isLeft);
	void clearResult();
	vector<string> getResult();
	
	// Returns false, if given JourneyCode is already present in the BST
	// Inserts the element and returns True otherwise
	bool insert(int JourneyCode, int price);


	// Return true, if the ticket with given attributes is found, false otherwise
	bool find(int JourneyCode, int price);
        TreeNode *getnode(int JourneyCode, int price) const;
	
	// Returns false, if JourneyCode isn't present
	// Deletes the corresponding entry and returns True otherwise
	bool remove(int JourneyCode, int price);
        bool del(TreeNode *loc);
	
	// Functions that traverse the BST in various ways!
	// type can be PRE_ORDER, POST_ORDER or IN_ORDER, which
        // #defined numeric constants defined in BST.cpp
        // This function prints on cout the journey codes (one per line)
        // encountered on traversing the BST in the given traversal order
	void traverse(int typeOfTraversal);

	// Returns the price of the cheapest journey
	int getMinimum();
        TreeNode *min() const;

        // ****************************************************************
	// Methods for Part II

	// Returns the count of journeys that are at least as expensive
        // as lowerPriceBound and at most as expensive as upperPriceBound,
        // both bounds included.
        int countJourneysInPriceBound(int lowerPriceBound, int upperPriceBound);
        vector<TreeNode *> positionsInSorted() const;
	
	// Store the current tree in a file called filename.  You should
        // store using a scheme that uses no more disk space than that
        // required to store all elements in the BST, plus perhaps a small
        // constant times the number of elements.  You should also store
        // in a manner such that your implementation of customLoad is as
        // memory and time efficient as possible.
	void customStore(string filename);
        void load(ofstream &out) const;
	
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


namespace mySpace{
    
template <class T>
class stack{
    std::vector<T> container;
public:
    stack(){}
    void push(const T &e){ container.push_back(e); }
    void pop(){ container.pop_back(); }
    const T &top() const{ return container.back(); }
    bool isEmpty() const{ return container.size() == 0; }
};
}

typedef std::vector<TreeNode *> vec;

// adapted from manish_s's code on StackOverflow, https://stackoverflow.com/questions/6443569/implementation-of-c-lower-bound.
namespace mySpace{
    // returns the smallest index i such that for all j >= i, a[j] >= minprice.
    int lower_bound(const vec &positions, int minprice){ // O(log n)
        int start = 0, end = positions.size();
        while (start < end) {
            int mid =  (start + end)/2;
            if (minprice <= positions[mid]->price) {
                end = mid;
            } 
            else start = mid + 1;
        }
        return start; // possibly positions.size() - if start > all elements of positions or 0 - if start <= all elements.
    }
    // returns the largest index i such that for all j <= i, a[j] <= minprice.
    int upper_bound(const vec &positions, int maxprice){ // O(log n)
        int start = 0, end = positions.size();
        while (start < end) {
            int mid =  (start + end)/2;
            if (maxprice >= positions[mid]->price) {
                start = mid + 1;
            }
            else end = mid;
        }
        return start; // possibly positions.size() - if start >= all elements or 0 - if start < all elements.
    }
}


#endif