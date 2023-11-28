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

class BST
{
private:
  TreeNode *root;
  int totalComparisonCost;
  int totalParentChildUpdateCost;
  int perComparisonCost;
  int perParentChildUpdateCost;

  // Recursively deletes all nodes in the binary tree rooted at currNode

  void recursiveDelete(TreeNode *currNode)
  {
    if (currNode != nullptr)
    {
      TreeNode *leftChild = currNode->left;
      TreeNode *rightChild = currNode->right;

      delete currNode;
      recursiveDelete(leftChild);
      recursiveDelete(rightChild);
    }
    return;
  }

  bool BSTLessThan(TreeNode *leftArg, TreeNode *rightArg)
  {
    if ((leftArg != nullptr) && (rightArg != nullptr))
    {
      bool result = (*leftArg < *rightArg);
      totalComparisonCost += perComparisonCost;
      return result;
    }
    else
    {
      cerr << "Unexpected exceptional condition!" << endl;
      exit(-1);
    }
  }

  void updateBSTParentChild(TreeNode *childNode, TreeNode *parentNode, bool isLeftChild)
  {
    if ((childNode != nullptr) && (parentNode != nullptr))
    {
      childNode->updateParentChild(parentNode, isLeftChild);
      totalParentChildUpdateCost += perParentChildUpdateCost;
    }
    else if ((childNode == nullptr) && (parentNode != nullptr))
    {
      if (isLeftChild)
      {
        parentNode->left = nullptr;
      }
      else
      {
        parentNode->right = nullptr;
      }
      // No updating of totalParentChildUpdateCost needed here
    }
    else if ((childNode != nullptr) && (parentNode == nullptr))
    {
      childNode->parent = nullptr;
      // No updating of totalParentChildUpdateCost needed here
    }
    else
    {
      // both childNode and parentNode are nullptr
      // Nothing to do really
      // No updating of totalParentChildUpdateCost needed here
      ;
    }
    return;
  }

  void remove(TreeNode *node, int jrnyCode)
  {
    if (node->left == NULL && node->right == NULL)
    {
      if (node == root)
      {
        root = NULL;
        delete node;
        return;
      }
      if (node->parent->left == node)
        node->parent->left = NULL;
      else
        node->parent->right = NULL;
      setAllHeights(node->parent);
      // cout<<node->parent->height<<endl;
      delete node;
      return;
    }
    //If left is  NULL or right is NULL, deletion is simple,
    //but we need to handle a few cases
    else if (node->left == NULL)
    {
      if (node == root)
      {
        root = root->right;
        root->parent = NULL;
        setHeights(root);
        delete node;
        return;
      }
      if (node->parent->left == node)
      {
        node->parent->left = node->right;
        node->right->parent = node->parent;
      }
      else
      {
        node->parent->right = node->right;
        node->right->parent = node->parent;
      }
      setAllHeights(node->parent);
      delete node;
      return;
    }
    else if (node->right == NULL)
    {
      if (node == root)
      {
        root = root->left;
        root->parent = NULL;
        setHeights(root);
        delete node;
        return;
      }
      if (node->parent->left == node)
      {
        node->parent->left = node->left;
        node->left->parent = node->parent;
      }
      else
      {
        node->parent->right = node->left;
        node->left->parent = node->parent;
      }
      setAllHeights(node->parent);
      delete node;
      return;
    }
    //It the node's left and right are not null we find its successor and
    //replace that node's values's with that of the successor, and then call
    //delete on the successor
    TreeNode *sucessor = findSuccessor(node);
    node->setJourneyCode(sucessor->journeyCode());
    node->setPrice(sucessor->Price());
    remove(sucessor, sucessor->journeyCode());

    return;
  }

public:
  // Constructors
  BST(int perCompCost, int perParntChldUpdCost)
  {
    root = nullptr;
    totalComparisonCost = 0;
    totalParentChildUpdateCost = 0;
    perComparisonCost = perCompCost;
    perParentChildUpdateCost = perParntChldUpdCost;
  }

  BST(TreeNode *newRoot, int perCompCost, int perParntChldUpdCost)
  {
    root = newRoot;
    totalComparisonCost = 0;
    totalParentChildUpdateCost = 0;
    perComparisonCost = perCompCost;
    perParentChildUpdateCost = perParntChldUpdCost;
  }

  // Destructor
  ~BST()
  {
    recursiveDelete(root);
  }

  bool insert(int jrnyCode, int price);
  int find(int jrnyCode);

  TreeNode *findNode(TreeNode *node, int JourneyCode)
  {
    // search until null or the node with the proper price
    //and journey specifications is found
    TreeNode *comparator = new TreeNode(JourneyCode, 100);
    while (node != nullptr)
    {
      if (BSTLessThan(node, comparator))
      {
        node = node->right;
      }
      else if (BSTLessThan(comparator, node))
      {
        node = node->left;
      }
      else
      { 
        delete comparator;
        return node;
      }
    }
    delete comparator;
    return nullptr;
  }
  // Optional: Implement "remove" only for bonus marks
  bool remove(int jrnyCode);

  int getComparisonCost() { return totalComparisonCost; }
  int getParentChildUpdateCost() { return totalParentChildUpdateCost; }
  void print()
  {
    printBinaryTree(root, "", false);
    return;
  }
};

#endif
