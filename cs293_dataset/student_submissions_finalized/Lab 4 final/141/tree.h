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


struct TreeNode{
  int JourneyCode;	// Train Number
  int price;		// Price
  TreeNode *left;	// Left Child of this Node (NULL, if None)
  TreeNode *right;	// Right Child of this Node (NULL, if None)
  TreeNode *parent;	// The Parent Node, NULL in case of Root
  int shortestPathLength, longestPathLength; // path length from this node. 
  int shortnumber=2;

  // Constructors

  TreeNode() : price(0), JourneyCode(0), left(nullptr), right(nullptr) {
      // this constructor allocates memory only for the root  (upon usage of new)
      // allocation of memory for children is the job of insert function. 
      this->parent = nullptr;
  }
  TreeNode(int jrnyCode, int jrnyPrice) : price(jrnyPrice), JourneyCode(jrnyCode), left(nullptr), right(nullptr) {
      // this constructor again allocates memory only for root. (upon usage of new)
  }
  TreeNode(int jrnyCode, int jrnyPrice, TreeNode *leftChild, TreeNode *rightChild, TreeNode *parent) : price(jrnyPrice), JourneyCode(jrnyCode), left(leftChild), right(rightChild), parent(parent) {
      // this constructor also allocates memory only for root. (upon usage of new)
  }

  // Overloaded operators
  bool operator<(const TreeNode& rightArgument)
  {
    return (JourneyCode < rightArgument.JourneyCode);
  }

  bool operator==(const TreeNode& rightArgument)
  {
    return (JourneyCode == rightArgument.JourneyCode);
  }
  
  // to be meant only for implementing update paths
  /*
  bool chain(TreeNode* cur, TreeNode* cur1 = nullptr, TreeNode* cur2 = nullptr){
    cout << "h1";
    if ((cur1 == nullptr) && (cur2 == nullptr))
      cur1=cur2=cur;
    else{
      cur1 = cur->left;
      cur2= cur->right;
    }
    cout << "h2";

    if ((cur1->left == nullptr) && (cur1->right == nullptr)){
      if ((cur2->right == nullptr) && (cur2->left == nullptr)) return true;
      else return false;
    }
    cout << "h3";

    if ((cur2->left == nullptr) && (cur2->right == nullptr)){
      if ((cur1->right == nullptr) && (cur1->left == nullptr)) return true;
      else return false;
    }

    else if (cur1->left == nullptr){
      if (cur2->right == nullptr) {
        return chain(cur, cur1->right, cur2->left);
      }
      else if (cur2->left == nullptr){
        return chain (cur, cur1->right, cur2->right);
      }
      else 
        return chain(cur, cur1->right, cur2->left) || chain (cur, cur1->right, cur2->right);
    }
    else if (cur2->left == nullptr){
      if (cur1->right == nullptr) {
        return chain(cur, cur2->right, cur1->left);
      }
      else if (cur1->left == nullptr){
        return chain (cur, cur2->right, cur1->right);
      }
      else
        return chain(cur, cur2->right, cur1->left) || chain (cur, cur2->right, cur1->right);
    }
    else if (cur1->right == nullptr){
      if (cur2->right == nullptr) {
        return chain(cur, cur1->left, cur2->left);
      }
      else if (cur2->left == nullptr){
        return chain (cur, cur1->left, cur2->right);
      }
      else 
        return chain(cur, cur1->left, cur2->left) || chain (cur, cur1->left, cur2->right);
    }
    else if (cur2->right == nullptr){
      if (cur1->right == nullptr) {
        return chain(cur, cur2->left, cur1->left);
      }
      else if (cur1->left == nullptr){
        return chain (cur, cur2->left, cur1->right);
      }
      else 
        return chain(cur, cur2->left, cur1->left) || chain (cur, cur2->left, cur1->right);
    }
    else 
      return chain(cur, cur1->right, cur2->left) || chain (cur, cur1->right, cur2->right) || chain(cur, cur2->right, cur1->left) || chain (cur, cur2->right, cur1->right) || chain(cur, cur1->left, cur2->left) || chain (cur, cur1->left, cur2->right) || chain(cur, cur2->left, cur1->left) || chain (cur, cur2->left, cur1->right);
  }
  */

  void updatepaths(int start=1) {
    // updates longestPathLength and shortestPathLength parameters, starting from this node (path considered 1)
    // measure of current path to leaf. 
    TreeNode* cur = this;
    while (cur != nullptr){
     
      if (cur->left == nullptr && cur->right == nullptr){
        cur->shortestPathLength=cur->longestPathLength=0;
      }
      else if (cur->right == nullptr){
        cur->shortestPathLength = 0;
        cur->longestPathLength = cur->left->longestPathLength+1;
      }
      else if (cur->left == nullptr){
        cur->shortestPathLength=0;
        cur->longestPathLength=cur->right->longestPathLength+1;
      }
      else{
        cur->shortestPathLength=min(cur->left->shortestPathLength, cur->right->shortestPathLength) + 1;
        cur->longestPathLength=max(cur->left->longestPathLength, cur->right->longestPathLength) + 1;
      }

      cur = cur->parent;
    }
      /*
      // ISSUE IS HERE ! -- MENTAL NOTE -- first update the fact that another guy is adding, then the
      // cout << "ShortesT length : " << cur->shortestPathLength << endl;
      
      if (count == cur->shortestPathLength + 1){
        cout << "here "  << cur->JourneyCode << "old shortest paths " << cur->shortnumber << " ";
        // assert(cur->shortestPathLength != 0);
        if (cur->shortnumber == 1){
          cur->shortestPathLength = count;
          cout << "Shortes path length : " << cur->shortestPathLength << endl;
        }
        else {
          cur->shortnumber -= 1;
        }
        cout << "Number of shortest paths : " << cur->shortnumber << endl;
        // either the shortest path got updated or there is a better alternative. 
        // we need to remember how many "shortest paths" were there beforehand. 
      }
      
      // now that shortestpathlength is updated, shortnumber can be updated accordingly.
      // updating smallest path length -- tricky. (insertions cuz)
      if (count == cur->shortestPathLength){
        // assert(cur->shortnumber != 0);

        // WTF!!! -- if the count is equal and someone else was providing the same count (which now contributes to shortest path) then add, if the length has changed due to you, don't do anything. 
        cout << "count : " << count << " Node : " << cur->JourneyCode << endl;
        if (count != 1){
          cout << cur->JourneyCode << endl;
          if (cur->shortnumber==1){
            cout << cur->left->shortestPathLength << " Path length of small" << endl;
            
            // check if the path length is 
            if (chain(cur)something){
              // if same chain is continued, but it happens to be equal to a new chain
              cur->shortnumber ++;
              cout << "Path increased" << endl;
            }
            else{
              // do nothing -- if same chain is continued
            }
          }
          
        }
        // assert(cur->shortnumber <= 2);
      }
      */
      // END
      //cur = cur->parent;
      /* useless checking
      if (count < cur->shortestPathLength){
        // assert(cur->shortestPathLength != 0);
        cur->shortestPathLength = count;
        cur->shortnumber = 1;
      }
      */
      
      
      
    
  } 

  int getImbalance()
  {
    // Returns how imbalanced the paths starting from this node to the
    // leaves are.  A case of perfect balance would result in the
    // longest and shortest path lengths being equal, so their difference
    // will be 0 (i.e. 0 imbalance).
    // Think about when would we have a case of large imbalance.
    
    // cout << shortestPathLength << " " << longestPathLength << endl;

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
  
  TreeNode *root;
  TreeNode* p;
  // vector for the purpose of loading. 
        

	// result variable is for testing purposes, Do not tamper with it!
	vector<string> result;
  friend void Load(int flag, string filename, BST* bst, ifstream &infile);
  
public:
  // ************************************************************
  // Methods for Part I
  
  // Constructors!
  BST();
	BST(TreeNode *root, TreeNode* p=nullptr);

  // Implement your own destructor
  ~BST() {};
  
  // Returns false, if given JourneyCode is already present in the BST
  // Inserts the element and returns True otherwise
  bool insert(int JourneyCode, int price, TreeNode* p=nullptr);
    
  // Return true, if the ticket with given attributes is found, false otherwise
  bool find(int JourneyCode, int price);
    
  // Returns false, if JourneyCode isn't present
  // Deletes the corresponding entry and returns True otherwise
  bool remove(int JourneyCode, int price);
  bool remove(TreeNode* input);

  void traverse(int typeOfTraversal);
  
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

  int getMinimum();
  TreeNode* getMin();

  // The three functions below are for evaluation purposes, Do not tamper with them!
  void getBST(const string& prefix, bool isLeft);
  void clearResult();
  vector<string> getResult();
  
};
  
