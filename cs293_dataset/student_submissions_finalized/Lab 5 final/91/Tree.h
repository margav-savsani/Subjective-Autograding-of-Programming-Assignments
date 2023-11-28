#ifndef TREE_H
#define TREE_H

#include <iostream>
#include <stdlib.h>

class TreeNode {
  public:
    int JourneyCode;    // Journey code: This is the key for BST and AVL tree
    int price;          // Price
    TreeNode* left;     // Pointer to left child  (nullptr, if no left child)
    TreeNode* right;    // Pointer to right child (nullptr, if no right child)
    TreeNode* parent;   // Parent of this node    (nullptr, if no parent)
    int height;         // Height of the tree rooted at this node. A leaf has height 0. 
    
    // Constructor:
    TreeNode(int jrnyCode, int jrnyPrice)
    {
        JourneyCode = jrnyCode;
        price = jrnyPrice;
        left = nullptr;
        right = nullptr;
        parent = nullptr;
        height = 0;
    }

    // Destructor: Define this as per your requirements
    ~TreeNode()
    {
    }

    // Print information about tree node on cout
    void printInfo()
    {
        std::cout << "[JC: " << JourneyCode << ", P: " << price << ", H: " << height << "]";
    }
    
    // Overloaded < operator
    // Usage: tree_node1 < tree_node2
    // Returns true if tree_node1.JourneyCode < tree_node2.JourneyCode
    // Returns false otherwise.
    //
    // Note that since JourneyCode is a private member of TreeNode,
    // we can't directly use tree_node1.JourneyCode < tree_node2.JourneyCode
    // from outside this class.
    
    bool operator<(TreeNode const& node)
    {
        return (JourneyCode < node.JourneyCode);
    }

    // Makes current node the left child of parentNode if
    // isLeftChild is set to true; otherwise, it makes current node
    // the right child of parentNode.    In either case, the function
    // returns true.
    //
    // If parentNode is NULL, the function returns false.
    //
    // Note that if parentNode already had a left child, say x, and if
    // you are setting current node to be the new left child of
    // parentNode, then x will no longer be the left child of parentNode.
    // In fact, unless you save a pointer to x, you may no longer be able
    // to access x at all by walking down the tree from its root.
    // A similar observation applies if parentNode already had a right child,
    // and you are setting current node to be the new right child of
    // parentNode.
    
    bool updateParentChild(TreeNode *parentNode, bool isLeftChild)
    {
        if (parentNode != nullptr) {
            parent = parentNode;
            if (isLeftChild) {
            	parentNode->left = this;
            }
            else {
            	parentNode->right = this;
            }
            return true;
        }
        else {
            return false;
        }
    }
};

// The following function is effectively the same as printBST used in
// earlier labs.    The only difference is that this is not a member
// function of any class, and hence the root must be explicitly supplied
// as a parameter

void printBinaryTree(TreeNode* root, std::string const& prefix, bool isLeft)
{
    if (root != nullptr) {
        std::cout << prefix;
        
        std::cout << (isLeft ? "|--" : "|__" );
        
        // print the value of the node
        root->printInfo();
        std::cout << '\n';
        TreeNode* curr = root;
        root = root->left;
        // enter the next tree level - left and right branch
        printBinaryTree(root, prefix + (isLeft ? "│     " : "        "), true);
        root = curr->right;
        printBinaryTree(root, prefix + (isLeft ? "│     " : "        "), false);
        root = curr;
    }
//    else {
//        std::cout << "NULL tree\n";
//    }
}

#endif
