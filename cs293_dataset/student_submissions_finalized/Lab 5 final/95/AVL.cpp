#ifndef AVL_H
#include "AVL.h"
#endif

#ifndef STD_HEADERS
#include <iostream>
#include <stdlib.h>
#endif









// for rotating the leftleft
bool AVLTree::rotateLeftLeft(TreeNode *currNode, TreeNode *parentNode, TreeNode *grandParentNode)
{
  // T3 is right node of parentNode
  TreeNode *T3 = parentNode->right;

  if (grandParentNode->parent != NULL)
  {
    TreeNode *greatGrandParentNode = grandParentNode->parent;
    bool isGPLeftChild;
    if (greatGrandParentNode->left == grandParentNode)
    {
      isGPLeftChild = true;
    }
    else if (greatGrandParentNode->right == grandParentNode)
    {
      isGPLeftChild = false;
    }
    else
    {
      cerr << "Unexpected condition encountered!" << endl;
      return false;
    }

    updateAVLParentChild(parentNode, greatGrandParentNode, isGPLeftChild);
  }
  else
  {
    parentNode->parent = NULL;
  }

  updateAVLParentChild(grandParentNode, parentNode, false);

  if (T3 != NULL)
  {

    updateAVLParentChild(T3, grandParentNode, true);
  }
  else
  {
    grandParentNode->left = NULL;
  }

  return true;
}





// rotating the node leftright
bool AVLTree::rotateLeftRight(TreeNode *currNode, TreeNode *parentNode, TreeNode *grandParentNode)
{
  TreeNode *T2 = currNode->left;
  TreeNode *T3 = currNode->right;

  TreeNode *greatGrandParentNode = grandParentNode->parent;
  if (greatGrandParentNode != NULL)
  {

    bool isGPLeftChild;
    if (greatGrandParentNode->left == grandParentNode)
    {
      isGPLeftChild = true;
    }

    else if (greatGrandParentNode->right == grandParentNode)
    {
      isGPLeftChild = false;
    }
    else
    {
      cerr << "Unexpected condition encountered!" << endl;
      return false;
    }

    updateAVLParentChild(currNode, greatGrandParentNode, isGPLeftChild);
  }
  else
  {
    currNode->parent = NULL;
  }

  updateAVLParentChild(parentNode, currNode, true);

  updateAVLParentChild(grandParentNode, currNode, false);

  if (T2 != NULL)
  {
    updateAVLParentChild(T2, parentNode, false);
  }
  else
  {
    parentNode->right = NULL;
  }

  if (T3 != NULL)
  {
    updateAVLParentChild(T3, grandParentNode, true);
  }
  else
  {
    grandParentNode->left = NULL;
  }

  return true;
}





// rotating the node rightleft
bool AVLTree::rotateRightLeft(TreeNode *currNode, TreeNode *parentNode, TreeNode *grandParentNode)
{
  TreeNode *greatGrandParentNode = grandParentNode->parent;
  TreeNode *T2 = currNode->left;
  TreeNode *T3 = currNode->right;
  bool isGPLeftChild;
  if (greatGrandParentNode != NULL)
  {
    if (greatGrandParentNode->left == grandParentNode)
    {
      isGPLeftChild = true;
    }
    else if (greatGrandParentNode->right == grandParentNode)
    {
      isGPLeftChild = false;
    }
    else
    {
      cerr << "Unexpected condition encountered!" << endl;
      return false;
    }
    updateAVLParentChild(currNode, greatGrandParentNode, isGPLeftChild);
  }
  else
  {
    currNode->parent = NULL;
  }
  updateAVLParentChild(parentNode, currNode, false);
  updateAVLParentChild(grandParentNode, currNode, true);

  if (T3 != NULL)
  {
    updateAVLParentChild(T3, parentNode, true);
  }
  else
  {
    parentNode->left = NULL;
  }
  if (T2 != NULL)
  {
    updateAVLParentChild(T2, grandParentNode, false);
  }
  else
  {
    grandParentNode->right = NULL;
  }

  return true;
}






// rotating the node rightright
bool AVLTree::rotateRightRight(TreeNode *currNode, TreeNode *parentNode, TreeNode *grandParentNode)
{
  TreeNode *T3 = parentNode->left;

  TreeNode *greatGrandParentNode = grandParentNode->parent;
  if (greatGrandParentNode != NULL)
  {
    bool isGPLeftChild;
    if (greatGrandParentNode->left == grandParentNode)
    {
      isGPLeftChild = true;
    }
    else if (greatGrandParentNode->right == grandParentNode)
    {
      isGPLeftChild = false;
    }
    else
    {
      cerr << "Unexpected condition encountered!" << endl;
      return false;
    }
    updateAVLParentChild(parentNode, greatGrandParentNode, isGPLeftChild);
  }
  else
  {
    parentNode->parent = NULL;
  }
  updateAVLParentChild(currNode, parentNode, right);
  updateAVLParentChild(grandParentNode, parentNode, true);
  if (T3 != NULL)
  {
    updateAVLParentChild(T3, grandParentNode, false);
  }
  else
  {
    grandParentNode->right = NULL;
  }
  return true;
}






// to rotate node
//  self define fucntion
void AVLTree::rotate(TreeNode *node)
{
  if (node->gebalnce() > 1 && node->left->gebalnce() == 1)
  {

    if (node == root)
    {

      root = node->left;
    }

    rotateLeftLeft(node->left->left, node->left, node);

    node->height--;
  }
  else if (node->gebalnce() > 1 && node->left->gebalnce() == -1)
  {

    if (node == root)
    {

      root = node->left->right;

    }

    TreeNode *parent = node->left;

    TreeNode *curr = node->left->right;

    rotateLeftRight(node->left->right, node->left, node);

    // updating the heights
    curr->height++;
    parent->height--;
    node->height--;


  }
  else if (node->gebalnce() < -1 && node->left->gebalnce() == -1)
  {
    if (node == root)
    {
      root = node->right;
    }
    rotateRightRight(node->right->right, node->right, node);
    node->height--;
  }
  else if (node->gebalnce() < -1 && node->left->gebalnce() == 1)
  {
    if (node == root)
    {
      root = node->right->left;
    }
    TreeNode *parent = node->right;
    TreeNode *curr = node->right->left;
    rotateRightLeft(node->right->left, node->right, node);
    curr->height++;
    parent->height--;
    node->height--;
  }
  return;
}





//for checking condition in insert while
bool get_truth(TreeNode *a)
{
  if (a == NULL)
  {
    return false;
  }
  else if (a->right == NULL && a->left == NULL)
  {
    return false;
  }
  else
    return true;
}




//insert function
bool AVLTree::insert(int jrnyCode, int price)
{
  TreeNode *a = root;
  TreeNode *q = new TreeNode(jrnyCode, price);

  while (get_truth(a))
  {
    if (AVLLessThan(a, q))
    {

      a = a->right;
    }
    else if (AVLLessThan(q, a))
    {

      a = a->left;
    }
    else
    {
      return false;
    }
  }

  q->parent = a;
  if (a == NULL)
  {
    this->root = q;
    return true;
  }

  else
  {
    if (AVLLessThan(a, q))
    {
      a->right = q;
    }
    else if (AVLLessThan(q, a))
    {
      a->left = q;
    }
  }

  while (a != NULL)
  {
    if (a->gebalnce() == 0)
    {
      return true;
    }
    else if (abs(a->gebalnce()) == 1)
    {
      a->height++;
      a = a->parent;
    }
    else if (abs(a->gebalnce()) > 1)
    {
      rotate(a);
      return true;
    }
  }

  return true;
}





//for finding elements
int AVLTree::find(int jrnyCode)
{
  TreeNode *find_node = root;
  TreeNode *b = new TreeNode(jrnyCode, 0);
  while (find_node != NULL)
  {
    if (AVLLessThan(find_node, b))
    {
      find_node = find_node->right;
    }
    else if (AVLLessThan(b, find_node))
    {
      find_node = find_node->left;
    }
    else
    {
      return 1;
    }
  }
  return 0;
}

bool AVLTree::remove(int jrnyCode)
{

  return true;
}
