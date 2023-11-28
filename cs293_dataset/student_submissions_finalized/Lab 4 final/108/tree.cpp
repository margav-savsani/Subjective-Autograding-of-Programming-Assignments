// Code up the functions defined in tree.h
// Reuse the binary Search Tree implemented in lab 3 as much as possible

#include "tree.h"

// PLEASE FILL IN THE BODIES OF THE FOLLOWING FUNCTIONS

// Returns false, if given JourneyCode is already present in the BST
// Inserts the element and returns True otherwise

int BST::getImbalance()
{
    if (root == nullptr) return 0;
    else return root->getImbalance();
}

void BST::update_path_lengths(TreeNode* node) {
    while(node) {
        node->shortestPathLength = 1 + min(node->left ? node->left->shortestPathLength : 0, node->right ? node->right->shortestPathLength : 0);
        node->longestPathLength = 1 + max(node->left ? node->left->longestPathLength : 0, node->right? node->right->longestPathLength : 0);
        node = node->parent;
    }
}

bool BST::insert(int JourneyCode, int price) {
    // The following filler code snippet is only given to facilitate
    // compilation.  You should replace/augment it with appropriate code,
    // similar to what you had done in lab assignment 3.
    // 
    // Do not forget to update shortestPathLength and
    // longestPathLength of (possibly all) BST nodes in the
    // path from the root to the new node you are inserting

    if (find(JourneyCode, price)) return false;

    // Create the new node
    TreeNode* new_node = new TreeNode { JourneyCode, price };
    new_node->parent = nullptr;

    // Inserting at the root
    if (!root) {
        root = new_node;
        return true;
    }

    // Insert at the right place
    TreeNode* cur { root };
    while (true) {
        if (JourneyCode > cur->JourneyCode) {
            if (cur->right) cur = cur->right;
            else {
                cur->right = new_node;
                new_node->parent = cur;
                update_path_lengths(new_node->parent);
                return true;
            }
        } else {
            if (cur->left) cur = cur->left;
            else {
                cur->left = new_node;
                new_node->parent = cur;
                update_path_lengths(new_node->parent);
                return true;
            }
        }
    }

    
}

// Return True, if the ticket with given attributes is found, false otherwise
bool BST::find(int JourneyCode, int price)
{
    // The following filler code snippet is only given to facilitate
    // compilation.  You should replace it with appropriate code, very
    // similar to what you had done in lab assignment 3.
    //
    // You can look at the implementation of insert to code this part up.
    
    TreeNode* cur { root };
    while (true) {
        if (!cur) return false;

        if (cur->JourneyCode == JourneyCode && cur->price == price) return true;

        if (JourneyCode > cur->JourneyCode) cur = cur->right;
        else cur = cur->left;
    }
}
	
// Returns false, if JourneyCode isn't present
// Deletes the corresponding entry and returns True otherwise
bool BST::remove(int JourneyCode, int price)
{
    // The following filler code snippet is only given to facilitate
    // compilation.  You should replace it with appropriate code, very
    // similar to what you had done in lab assignment 3.
    //
    // Recall from CS 213 lectures about the various ways in which the
    // BST can be restructured when a node is deleted. You can implement
    // any of these alternatives.
    //
    // Do not forget to update shortestPathLength and
    // longestPathLength of (possibly all) BST nodes in the
    // path from the root to nodes whose position in the BST is affected
    // by the remove.
      
    if (!find(JourneyCode, price)) return false;

    TreeNode* cur { root };

    while (true) {
        if (JourneyCode == cur->JourneyCode && price == cur->price) {
            if (!(cur->left) && !(cur->right)) {
                // Deleting at the leaf
                if (cur == root) root = nullptr;
                else {
                    if (cur->parent->left == cur) cur->parent->left = nullptr;
                    else cur->parent->right = nullptr;
                }

            } else if (!(cur->left) || !(cur->right)) {
                // Deleting node with one child
                TreeNode* next = cur->left ? cur->left : cur->right;
                next->parent = cur->parent;
                if (cur != root) {
                    if (cur->parent->left == cur) cur->parent->left = next;
                    else cur->parent->right = next;
                }
                else {
                    root = next;
                    root->parent = nullptr;
                }

            } else {
                // Deleting node with two children
                TreeNode* next = findmax(cur->left);  // Node to be inserted at the deleted node's place

                // Update pointers from the node
                swap(next->parent, cur->parent);
                swap(next->right, cur->right);
                swap(next->left, cur->left);
                
                // Update pointers to the node
                next->right->parent = next;
                if (next->parent) {
                    if (next->parent->left == cur) next->parent->left = next;
                    else next->parent->right = next;
                }
                else root = next;

                if (next != next->left) {
                    next->left->parent = next;
                    cur->parent->right = cur->left;
                    if (cur->left) cur->left->parent = cur->parent;
                } else {
                    next->left = cur->left;
                    if (next->left) next->left->parent = next;
                }
            }

            return true;

        } else if (JourneyCode > cur->JourneyCode) cur = cur->right;
        else cur = cur->left;
    }
}

// Finds the max element in the tree rooted at Root
TreeNode* BST::findmax(TreeNode* Root) {
    while (Root->right) Root = Root->right;
    return Root;
}

// ************************************************************
// DO NOT CHANGE ANYTHING BELOW THIS LINE

// Adapted from Adrian Schneider's code on StackOverflow
void BST::printBST(const string& prefix, bool isLeft=false)
{
    if( root != nullptr )
    {
        cout << prefix;

        cout << (isLeft ? "|--" : "|__" );

        // print the value of the node
        cout << root->JourneyCode << endl;
        TreeNode *curr = root;
        root = root->left;
        // enter the next tree level - left and right branch
        printBST( prefix + (isLeft ? "│   " : "    "), true);
        root = curr->right;
        printBST( prefix + (isLeft ? "│   " : "    "), false);
        root = curr;
    }
}

void BST::getBST(const string& prefix,  bool isLeft=false)
{
    if( root != nullptr )
    {
        result.push_back(prefix);

        result.push_back(isLeft ? "|--" : "|__" );

        // print the value of the node
        result.push_back(to_string(root->JourneyCode) + "\n");
        TreeNode *curr = root;
        root = root->left;
        // enter the next tree level - left and right branch
        getBST( prefix + (isLeft ? "│   " : "    "), true);
        root = curr->right;
        getBST( prefix + (isLeft ? "│   " : "    "), false);
        root = curr;
    }
}

void BST::clearResult(){
    result.clear();
}

vector<string> BST::getResult(){
    return result;
}
