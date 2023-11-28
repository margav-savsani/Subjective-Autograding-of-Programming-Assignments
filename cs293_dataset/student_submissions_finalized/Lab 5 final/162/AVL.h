#ifndef AVL_H
#define AVL_H

#ifndef TREE_H
#include "Tree.h"
#endif

#ifndef STD_HEADERS
#include <iostream>
#include <stdlib.h>
#endif

class AVLTree
{
private:
  TreeNode *root;
  int totalComparisonCost;
  int totalParentChildUpdateCost;
  int perComparisonCost;
  int perParentChildUpdateCost;

  bool rotateLeftLeft(TreeNode *currNode, TreeNode *parent, TreeNode *grandParent);
  bool rotateLeftRight(TreeNode *currNode, TreeNode *parent, TreeNode *grandParent);
  bool rotateRightLeft(TreeNode *currNode, TreeNode *parent, TreeNode *grandParent);
  bool rotateRightRight(TreeNode *currNode, TreeNode *parent, TreeNode *grandParent);

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

  bool AVLLessThan(TreeNode *leftArg, TreeNode *rightArg)
  {
    // leftArg->printInfo();
    // rightArg->printInfo();
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

  void updateAVLParentChild(TreeNode *childNode, TreeNode *parentNode, bool isLeftChild)
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
  TreeNode *remove(TreeNode *node, int jrnyCode)
  {
    TreeNode *parent = node->parent;
    if (node->left == NULL && node->right == NULL)
    {
      if (node == root)
      {
        root = NULL;
        delete node;
        return NULL;
      }
      if (node->parent->left == node)
        node->parent->left = NULL;
      else
        node->parent->right = NULL;
      setAllHeights(node->parent);

      // cout << node->parent->height << endl;
      delete node;
      return parent;
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
        return parent;
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
      return parent;
    }
    else if (node->right == NULL)
    {
      if (node == root)
      {
        root = root->left;
        root->parent = NULL;
        setHeights(root);
        delete node;
        return parent;
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
      return parent;
    }
    //It the node's left and right are not null we find its successor and
    //replace that node's values's with that of the successor, and then call
    //delete on the successor
    TreeNode *sucessor = findSuccessor(node);
    node->setJourneyCode(sucessor->journeyCode());
    node->setPrice(sucessor->Price());
    parent = remove(sucessor, sucessor->journeyCode());

    return parent;
  }

public:
  // Constructors
  AVLTree(int perCompCost, int perParntChldUpdCost)
  {
    root = nullptr;
    totalComparisonCost = 0;
    totalParentChildUpdateCost = 0;
    perComparisonCost = perCompCost;
    perParentChildUpdateCost = perParntChldUpdCost;
  }

  AVLTree(TreeNode *newRoot, int perCompCost, int perParntChldUpdCost)
  {
    root = newRoot;
    totalComparisonCost = 0;
    totalParentChildUpdateCost = 0;
    perComparisonCost = perCompCost;
    perParentChildUpdateCost = perParntChldUpdCost;
  }

  // Destructor
  ~AVLTree()
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
      if (AVLLessThan(node, comparator))
      {
        node = node->right;
      }
      else if (AVLLessThan(comparator, node))
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
  void balance(TreeNode *GP, TreeNode *P, TreeNode *C)
  {
    if (P->left == C && GP->left == P) // LL
    {
      //xyz
      rotateLeftLeft(C, P, GP);

      setHeights(GP);
      setHeights(P);
    }
    if (P->right == C && GP->left == P) // LR
    {
      rotateLeftRight(C, P, GP);

      setHeights(GP);
      setHeights(P);
      setHeights(C);
    }
    if (P->right == C && GP->right == P) // RR
    {
      rotateRightRight(C, P, GP);

      setHeights(GP);
      setHeights(P);
    }
    if (P->left == C && GP->right == P) // RL
    {
      rotateRightLeft(C, P, GP);
      setHeights(GP);
      setHeights(P);
      setHeights(C);
    }

    setAllHeights(GP->parent);
  }

  int getComparisonCost() { return totalComparisonCost; }
  int getParentChildUpdateCost() { return totalParentChildUpdateCost; }
  void print()
  {
    printBinaryTree(root, "", false);
    return;
  }
};

#endif
