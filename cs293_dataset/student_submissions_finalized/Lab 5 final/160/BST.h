#ifndef BST_H
#define BST_H

#ifndef TREE_H
#include "Tree.h"
#endif

#ifndef STD_HEADERS
#include <iostream>
#include <stdlib.h>
#endif

using namespace std;

class BST {
private:
  TreeNode *root;
  int totalComparisonCost;
  int totalParentChildUpdateCost;
  int perComparisonCost;
  int perParentChildUpdateCost;
  
  // Recursively deletes all nodes in the binary tree rooted at currNode

	/*struct TreeNode* minvalnode(struct TreeNode* node)
	{
		struct TreeNode* c = node;
		while (c != NULL && c->left != NULL)
			c = c->left;
		return c;
	}
	struct TreeNode* deleteNode(struct TreeNode* root, int key)
	{
		TreeNode* dnode=new TreeNode(key,100);
		if (root == NULL)
			return root;

		// If the key to be deleted is smaller than the root's key, then it lies in left subtree
		if (BSTLessThan(dnode,root))
			root->left = deleteNode(root->left, key);

		// If the key to be deleted is greater than the root's key, then it lies in right subtree
		else if (BSTLessThan(root,dnode))
			root->right = deleteNode(root->right,key);

		// if key is same as root's key, then node to be deleted
		else {
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
			root->modify(temp->printcode(),temp->printprice());

			// Delete the inorder successor
			root->right = deleteNode(root->right,temp->printcode());
		}
		return root;
	}*/

  void recursiveDelete(TreeNode *currNode) {
    if (currNode != nullptr) {
      TreeNode *leftChild = currNode->left;
      TreeNode *rightChild = currNode->right;
    
      delete currNode;
      recursiveDelete(leftChild);
      recursiveDelete(rightChild);
    }
    return;
  }

  bool BSTLessThan(TreeNode* leftArg, TreeNode *rightArg) {
    if ((leftArg != nullptr) && (rightArg != nullptr)) {
      bool result = (*leftArg < *rightArg);
      totalComparisonCost += perComparisonCost;
      return result;
    }
    else {
      cerr << "Unexpected exceptional condition!" << endl;
      exit(-1);
    }
  }
  
  void updateBSTParentChild(TreeNode *childNode, TreeNode *parentNode, bool isLeftChild)
  {
    if ((childNode != nullptr) && (parentNode != nullptr)) {
      childNode->updateParentChild(parentNode, isLeftChild);
      totalParentChildUpdateCost += perParentChildUpdateCost;
    }
    else if ((childNode == nullptr) && (parentNode != nullptr)) {
      if (isLeftChild) {
	parentNode->left = nullptr;
      }
      else {
	parentNode->right = nullptr;
      }
      // No updating of totalParentChildUpdateCost needed here
    }
    else if ((childNode != nullptr) && (parentNode == nullptr)) {
      childNode->parent = nullptr;
      // No updating of totalParentChildUpdateCost needed here
    }
    else {
      // both childNode and parentNode are nullptr
      // Nothing to do really
      // No updating of totalParentChildUpdateCost needed here
      ;
    }
    return;
  }
    
public:
  // Constructors
  BST(int perCompCost, int perParntChldUpdCost) {
    root = nullptr;
    totalComparisonCost = 0;
    totalParentChildUpdateCost = 0;
    perComparisonCost = perCompCost;
    perParentChildUpdateCost = perParntChldUpdCost;
  }
  
  BST(TreeNode *newRoot, int perCompCost, int perParntChldUpdCost) {
    root = newRoot;
    totalComparisonCost = 0;
    totalParentChildUpdateCost = 0;
    perComparisonCost = perCompCost;
    perParentChildUpdateCost = perParntChldUpdCost;
  }
    
  // Destructor
  ~BST() {
    recursiveDelete(root);
  }

  bool insert(int jrnyCode, int price);
  int find(int jrnyCode);

  // Optional: Implement "remove" only for bonus marks
  
  bool remove(int jrnyCode);

  int getComparisonCost() { return totalComparisonCost; }
  int getParentChildUpdateCost() { return totalParentChildUpdateCost; }
  void print() { printBinaryTree(root, "", false); return;}
};

#endif
