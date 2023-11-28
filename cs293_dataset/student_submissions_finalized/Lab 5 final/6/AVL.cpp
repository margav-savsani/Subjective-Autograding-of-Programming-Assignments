#ifndef AVL_H
#include "AVL.h"
#endif

#ifndef STD_HEADERS
#include <iostream>
#include <stdlib.h>
#endif

bool AVLTree::rotateLeftLeft(TreeNode *currNode, TreeNode *parentNode, TreeNode *grandParentNode)
{
  TreeNode *greatGrandParentNode = grandParentNode->parent;
  bool isGPLeftChild;
  if (greatGrandParentNode != nullptr)
  {
    if (greatGrandParentNode->left == grandParentNode)
      isGPLeftChild = true;
    else if (greatGrandParentNode->right == grandParentNode)
      isGPLeftChild = false;
    else
    {
      cerr << "Unexpected condition encountered!" << endl;
      return false;
    }
  }
  TreeNode *T3 = parentNode->right;
  updateAVLParentChild(parentNode, greatGrandParentNode, isGPLeftChild);
  updateAVLParentChild(currNode, parentNode, true);
  updateAVLParentChild(grandParentNode, parentNode, false);
  updateAVLParentChild(T3, grandParentNode, true);

  if (greatGrandParentNode == nullptr)
    root = parentNode;

  return true;
}

bool AVLTree::rotateLeftRight(TreeNode *currNode, TreeNode *parentNode, TreeNode *grandParentNode)
{
  TreeNode *greatGrandParentNode = grandParentNode->parent;
  bool isGPLeftChild;
  if (greatGrandParentNode != nullptr)
  {
    if (greatGrandParentNode->left == grandParentNode)
      isGPLeftChild = true;
    else if (greatGrandParentNode->right == grandParentNode)
      isGPLeftChild = false;
    else
    {
      cerr << "Unexpected condition encountered!" << endl;
      return false;
    }
  }

  TreeNode *T2 = currNode->left;
  TreeNode *T3 = currNode->right;

  updateAVLParentChild(currNode, greatGrandParentNode, isGPLeftChild);
  updateAVLParentChild(parentNode, currNode, true);
  updateAVLParentChild(grandParentNode, currNode, false);
  updateAVLParentChild(T2, parentNode, false);
  updateAVLParentChild(T3, grandParentNode, true);

  if (greatGrandParentNode == nullptr)
    root = currNode;

  return true;
}

bool AVLTree::rotateRightLeft(TreeNode *currNode, TreeNode *parentNode, TreeNode *grandParentNode)
{
  TreeNode *greatGrandParentNode = grandParentNode->parent;
  bool isGPLeftChild;
  if (greatGrandParentNode != nullptr)
  {
    if (greatGrandParentNode->left == grandParentNode)
      isGPLeftChild = true;
    else if (greatGrandParentNode->right == grandParentNode)
      isGPLeftChild = false;
    else
    {
      cerr << "Unexpected condition encountered!" << endl;
      return false;
    }
  }

  TreeNode *T2 = currNode->right;
  TreeNode *T3 = currNode->left;

  updateAVLParentChild(currNode, greatGrandParentNode, isGPLeftChild);
  updateAVLParentChild(parentNode, currNode, false);
  updateAVLParentChild(grandParentNode, currNode, true);
  updateAVLParentChild(T2, parentNode, true);
  updateAVLParentChild(T3, grandParentNode, false);

  if (greatGrandParentNode == nullptr)
    root = currNode;

  return true;
}

bool AVLTree::rotateRightRight(TreeNode *currNode, TreeNode *parentNode, TreeNode *grandParentNode)
{
  TreeNode *greatGrandParentNode = grandParentNode->parent;

  bool isGPLeftChild;
  if (greatGrandParentNode != nullptr)
  {
    if (greatGrandParentNode->left == grandParentNode)
      isGPLeftChild = true;
    else if (greatGrandParentNode->right == grandParentNode)
      isGPLeftChild = false;
    else
    {
      cerr << "Unexpected condition encountered!" << endl;
      return false;
    }
  }

  TreeNode *T3 = parentNode->left;

  updateAVLParentChild(parentNode, greatGrandParentNode, isGPLeftChild);
  updateAVLParentChild(currNode, parentNode, false);
  updateAVLParentChild(grandParentNode, parentNode, true);
  updateAVLParentChild(T3, grandParentNode, false);

  if (greatGrandParentNode == nullptr)
    root = parentNode;

  return true;
}

int absol(int a, int b)
{
  if (a > b)
    return a - b;
  else
    return b - a;
}

bool AVLTree::insert(int jrnyCode, int price)
{
  TreeNode *dummy = nullptr;
  TreeNode *start = root;
  TreeNode *newnode = new TreeNode(jrnyCode, price);
  if (root == nullptr)
    root = newnode;
  else
  {
    while (start != nullptr)
    {
      dummy = start;
      if (AVLLessThan(newnode, start))
        start = start->left;
      else
        start = start->right;
    }
    if (AVLLessThan(newnode, dummy))
      updateAVLParentChild(newnode, dummy, true);
    else
      updateAVLParentChild(newnode, dummy, false);
  }

  TreeNode *leaf = dummy;
  while (true)
  {
    if (dummy == nullptr)
      break;
    else if ((dummy->right == nullptr || dummy->left == nullptr) && dummy == leaf)
      dummy->height++;
    else
    {
      int l = dummy->height;
      int rl = -1, ll = -1;
      if (dummy->right != nullptr)
        rl = dummy->right->height;
      if (dummy->left != nullptr)
        ll = dummy->left->height;
      dummy->height = max(rl, ll) + 1;
      if (l == dummy->height)
        break;
    }
    dummy = dummy->parent;
  }

  TreeNode *CurrNode = newnode;
  TreeNode *ParNode;
  TreeNode *GParNode;
  while (true)
  {
    if (CurrNode->parent == nullptr)
      break;
    else if (CurrNode->parent->parent == nullptr)
      break;

    ParNode = CurrNode->parent;
    GParNode = ParNode->parent;
    int r = -1;
    int l = -1;
    if (GParNode->right != nullptr)
      r = GParNode->right->height;
    if (GParNode->left != nullptr)
      l = GParNode->left->height;
    if (absol(r, l) > 1)
    {
      bool IsParentLeft, IsCurrLeft;

      if (ParNode == GParNode->left)
        IsParentLeft = true;
      else if (ParNode == GParNode->right)
        IsParentLeft = false;
      else
        break;

      if (CurrNode == ParNode->left)
        IsCurrLeft = true;
      else if (CurrNode == ParNode->right)
        IsCurrLeft = false;
      else
        break;

      bool single;
      if (IsParentLeft && IsCurrLeft)
      {
        rotateLeftLeft(CurrNode, ParNode, GParNode);
        single = true;
      }
      else if (IsParentLeft && !IsCurrLeft)
      {
        rotateLeftRight(CurrNode, ParNode, GParNode);
        single = false;
      }
      else if (!IsParentLeft && IsCurrLeft)
      {
        rotateRightLeft(CurrNode, ParNode, GParNode);
        single = false;
      }
      else if (!IsParentLeft && !IsCurrLeft)
      {
        rotateRightRight(CurrNode, ParNode, GParNode);
        single = true;
      }
      else
        break;

      if (single)
      {
        GParNode->height--;
        GParNode->height--;
      }
      else
      {
        GParNode->height--;
        GParNode->height--;
        ParNode->height--;
        CurrNode->height++;
      }
      TreeNode *dumm = GParNode->parent;
      while (true)
      {
        if (dumm == nullptr)
          break;
        else
        {
          int l = dumm->height;
          int rl = -1, ll = -1;
          if (dumm->right != nullptr)
            rl = dumm->right->height;
          if (dumm->left != nullptr)
            ll = dumm->left->height;
          dumm->height = max(rl, ll) + 1;
          if (l == dumm->height)
            break;
        }
        dumm = dumm->parent;
      }
      break;
    }
    CurrNode = CurrNode->parent;
  }
  return true;
}

int AVLTree::find(int jrnyCode)
{
  TreeNode *dummy = root;
  TreeNode *newnode = new TreeNode(jrnyCode, 0);

  while (dummy != nullptr && jrnyCode != dummy->get_JourneyCode()) //  loop will continue until correct node is found
  {
    // if (JourneyCode < dummy->JourneyCode) // further move forward left or right according to input price
    if (AVLLessThan(newnode, dummy))
      dummy = dummy->left;
    else
      dummy = dummy->right;
  }
  if (dummy == nullptr) // node not present
    return -1;
  if (jrnyCode == dummy->get_JourneyCode()) // node found
    return 1;
  return -1;
}

TreeNode *AVLTree::find_node(int jrnyCode)
{
  TreeNode *dummy = root;
  TreeNode *newnode = new TreeNode(jrnyCode, 0);

  while (dummy != nullptr && jrnyCode != dummy->get_JourneyCode()) //  loop will continue until correct node is found
  {
    if (AVLLessThan(newnode, dummy))
      dummy = dummy->left;
    else
      dummy = dummy->right;
  }
  if (dummy == nullptr) // node not present
    return nullptr;
  if (jrnyCode == dummy->get_JourneyCode()) // node found
    return dummy;
  return nullptr;
}

TreeNode *AVLTree::getMinimumNode(TreeNode *start)
{
  TreeNode *start_ = start;
  while (start_->left != nullptr) // Moves leftwards until a leaf occurs
  {
    start_ = start_->left;
  }
  return start_;
}

bool AVLTree::remove(int jrnyCode)
{
  if (jrnyCode == 0) // invalid node to be deleted
    return false;

  TreeNode *rem = find_node(jrnyCode); // assure the presence of node to be deleted
  if (rem == nullptr)
    return false;

  TreeNode *current;
  if (rem->left == nullptr && rem->right == nullptr) // Case 1 - node to be deleted has no children
  {
    if (rem == root)
    {
      rem->update_values(0, 0);
      current = nullptr;
    }
    else if (rem == rem->parent->left)
    {
      current = rem->parent;
      updateAVLParentChild(nullptr, current, true);
    }
    else
    {
      current = rem->parent;
      updateAVLParentChild(nullptr, current, false);
    }
    delete rem;
  }
  else if (rem->left == nullptr) // Case 2 - node to be inserted has only right child
  {

    TreeNode *dummy = rem->right;

    if (rem == root)
    {
      updateAVLParentChild(dummy, nullptr, true);
      root = dummy;
      current = nullptr;
    }
    else if (rem == rem->parent->left)
    {
      current = rem->parent;
      updateAVLParentChild(dummy, current, true);
    }
    else
    {
      current = rem->parent;
      updateAVLParentChild(dummy, current, false);
    }
    delete rem;
  }
  else if (rem->right == nullptr) // Case 2 - node to be inserted has only right child
  {
    TreeNode *dummy = rem->right;

    if (rem == root)
    {
      updateAVLParentChild(dummy, nullptr, false);
      root = dummy;
      current = nullptr;
    }
    else if (rem == rem->parent->left)
    {
      current = rem->parent;
      updateAVLParentChild(dummy, current, true);
    }
    else
    {
      current = rem->parent;
      updateAVLParentChild(dummy, current, false);
    }
    delete rem;
  }
  else // if node to be present has both children
  {
    TreeNode *min = getMinimumNode(rem->right); // min is calculated in right subtree
    current = min->parent;
    rem->update_values(min->get_JourneyCode(), min->get_price());
    if (min == rem->right)
    {
      TreeNode *temp = rem->right->right;
      updateAVLParentChild(temp, rem, false);
    }
    else if (min->right == nullptr)
      updateAVLParentChild(nullptr, current, true);
    else
    {
      TreeNode *dummy = min->right;
      updateAVLParentChild(dummy, current, true);
    }
    delete min;
  }
  TreeNode *leaf = current;
  while (true)
  {
    if (current == nullptr)
      break;
    else if (current->right == nullptr && current->left == nullptr && current == leaf)
      current->height--;
    else
    {
      int l = current->height;
      int rl = -1, ll = -1;
      if (current->right != nullptr)
        rl = current->right->height;
      if (current->left != nullptr)
        ll = current->left->height;
      current->height = max(rl, ll) + 1;
      if (l == current->height)
        break;
    }
    current = current->parent;
  }
  TreeNode *GParNode = leaf;
  TreeNode *GParNode_og = leaf;
  TreeNode *CurrNode;
  TreeNode *ParNode;

  while (true)
  {
    GParNode_og = GParNode;
    if (GParNode == nullptr)
      break;
    int r = -1;
    int l = -1;
    if (GParNode->right != nullptr)
      r = GParNode->right->height;
    if (GParNode->left != nullptr)
      l = GParNode->left->height;

    // checking for imbalance

    if (absol(r, l) > 1)
    {
      if (r > l)
        ParNode = GParNode->right;
      else if (l > r)
        ParNode = GParNode->left;
      else
        break;
      bool IsParentLeft, IsCurrLeft;
      int pl = -1, pr = -1;
      if (ParNode->left != nullptr)
        pl = ParNode->left->height;
      if (ParNode->right != nullptr)
        pr = ParNode->right->height;

      if (ParNode == GParNode->right)
      {
        IsParentLeft = false;
        if (pr >= pl)
        {
          CurrNode = ParNode->right;
          IsCurrLeft = false;
        }
        else if (pr < pl)
        {
          CurrNode = ParNode->left;
          IsParentLeft = true;
        }
        else
          break;
      }
      else if (ParNode == GParNode->left)
      {
        IsParentLeft = true;
        if (pl >= pr)
        {
          CurrNode = ParNode->left;
          IsCurrLeft = true;
        }
        else if (pl < pr)
        {
          CurrNode = ParNode->right;
          IsCurrLeft = false;
        }
        else
          break;
      }
      else
        break;

      // rotation

      bool single;
      if (IsParentLeft && IsCurrLeft)
      {
        rotateLeftLeft(CurrNode, ParNode, GParNode);
        single = true;
      }
      else if (IsParentLeft && !IsCurrLeft)
      {
        rotateLeftRight(CurrNode, ParNode, GParNode);
        single = false;
      }
      else if (!IsParentLeft && IsCurrLeft)
      {
        rotateRightLeft(CurrNode, ParNode, GParNode);
        single = false;
      }
      else if (!IsParentLeft && !IsCurrLeft)
      {
        rotateRightRight(CurrNode, ParNode, GParNode);
        single = true;
      }
      else
        break;

      // editing heights of x,y,z

      if (single)
      {
        int gl = -1, gr = -1;
        if (GParNode->left != nullptr)
          gl = GParNode->left->height;
        if (GParNode->right != nullptr)
          gr = GParNode->right->height;
        int pl = -1, pr = -1;
        if (ParNode->left != nullptr)
          pl = ParNode->left->height;
        if (ParNode->right != nullptr)
          pr = ParNode->right->height;

        GParNode->height = max(gl, gr) + 1;
        ParNode->height = max(pl, pr) + 1;
      }
      else
      {
        GParNode->height--;
        GParNode->height--;
        ParNode->height--;
        CurrNode->height++;
      }

      GParNode = GParNode_og;

      // editing other heights

      TreeNode *dumm = GParNode->parent;
      while (true)
      {
        if (dumm == nullptr)
          break;
        else
        {
          int l = dumm->height;
          int rl = -1, ll = -1;
          if (dumm->right != nullptr)
            rl = dumm->right->height;
          if (dumm->left != nullptr)
            ll = dumm->left->height;
          dumm->height = max(rl, ll) + 1;
          if (l == dumm->height)
            break;
        }
        dumm = dumm->parent;
      }
    }
    GParNode = GParNode->parent;
  }
  return true;
}
