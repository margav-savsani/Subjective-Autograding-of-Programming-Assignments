#ifndef BST_H
#include "BST.h"
#endif

#ifndef STD_HEADERS
#include <iostream>
#include <stdlib.h>
#endif

// Returns true on successful insertion in BST. Returns false otherwise.
// You may assume that no two elements being inserted have the same journey
// code, and journey code is the key for insertion and finding in the BST

bool BST::insert(int jrnyCode, int price)
{
  // Implement insertion in BST

  // You MUST use only BSTLessThan to compare two journey codes.  You
  // can create a new node containing the journey code to be inserted
  // and invoke BSTLessThan on the current node in the tree that you
  // are inspecting and the new node to do your comparison.

  // REMEMBER to update the heights of appropriate nodes in the tree
  // after an insertion.

  // We use "return true" below to enable compilation.  Change this as you
  // see fit.
  // finder is my pointer which iterates the tree to find the element to be searched for

  // Creating a temporary temp node for comparisons
  TreeNode *element = new TreeNode(jrnyCode, price);

  TreeNode *finder;
  TreeNode *parent = nullptr;
  finder = root;
  while (finder != nullptr)
  {
    parent = finder;
    // Updating the comparison cost by 1 as equality was checked
    totalComparisonCost = totalComparisonCost + perComparisonCost;
    if (*finder == *element)
    {
      break;
    }
    else if (BSTLessThan(finder, element))
    {
      finder = finder->right;
    }
    else
    {
      finder = finder->left;
    }
  }

  // finder as null indicates that the given journey code doesn't exist already and hence we can \
  perform the addition of node
  if (finder == nullptr)
  {
    // Changing the newly added element's height

    // indicates that addition is not being done at the root position
    if (parent != nullptr)
    {
      // element->parent = parent;
      if (BSTLessThan(parent, element))
      {
        updateBSTParentChild(element, parent, false);
        // parent->right = element;
      }
      else
      {
        updateBSTParentChild(element, parent, true);
        // parent->left = element;
      }
    }

    // for the case when addition is at root position that is the added element is the \
    very first element of the Tree.
    else
    {
      root = element;
      updateBSTParentChild(element, parent, false);
      // element->parent = nullptr;
    }

    // Updating the height of all the elements up the path until we find a node where insertion don't result in height change\
    and that would be after we find the first unbalanced node or find the first node where addition hasn't changed the height\
    essentially meaning that no unbalanced node was created
    while (parent != nullptr)
    {
      if (parent->right == nullptr || parent->left == nullptr)
      {
        parent->height++;
      }
      else
      {
        // og_height stores height before insertion of new node
        int og_height = parent->height;

        // new_height stores new proposed height post insertion of new node
        int new_height = max(parent->left->height, parent->right->height) + 1;

        // If new and old are same that means we basically are at the node from which\
        any node above it won't have any height change
        if (new_height <= og_height)
        {
          break;
        }

        // For the case when height has been changed, here we must also check if\
        imbalance has been there or not
        else
        {
          parent->height = new_height;
        }
      }
      parent = parent->parent;
    }

    return true;
  }

  // Returning false as something was found with the same journey code and that is not allowed.
  return false;
}

// Returns the price on finding an element in the BST that matches
// journey code. Returns -1 otherwise.
// You may assume that no two node in the tree have the same journey
// code, and journey code is the key for insertion and finding in the BST

int BST::find(int jrnyCode)
{
  // Implement find in BST

  // You MUST use only BSTLessThan to compare two journey codes.  You
  // can create a new node containing the journey code to be searched
  // (along with some arbitrary price) and invoke BSTLessThan on the
  // current node in the tree that you are inspecting and the new node
  // to do your comparison.

  // We use "return -1" below to enable compilation.  Change this as you
  // see fit.

  // finder is my pointer which iterates the tree to find the element to be searched for

  // Creating a temporary temp node for comaprisons
  TreeNode *temp = new TreeNode(jrnyCode, 50);

  TreeNode *finder;
  finder = root;
  // Going through the tree to find the required node if present
  while (finder != NULL)
  {
    // Updating the comparison cost by 1 as equality is being checked
    totalComparisonCost = totalComparisonCost + perComparisonCost;
    if (*finder == *temp)
    {
      return finder->get_price();
    }
    else if (BSTLessThan(finder, temp))
    {
      finder = finder->right;
    }
    else
    {
      finder = finder->left;
    }
  }
  return -1;
}

// =====================================================
// OPTIONAL: Implement "remove" only for bonus marks
// =====================================================

// Returns true on successful deletion of the entry in BST with
// matching journey code. Returns false if it cannot find any such element.
//
// You may assume that no two elements in the BST have the same journey
// code, and journey code is the key for insertion and finding in the BST.

bool BST::remove(int jrnyCode)
{
  // Implement deletion in BST

  // You MUST use only BSTLessThan to compare two journey codes.  You
  // can create a new node containing the journey code to be searched
  // (along with some arbitrary price) and invoke BSTLessThan on the
  // current node in the tree that you are inspecting and the new node
  // to do your comparison.

  // REMEMBER to update the height of appropriate nodes in the tree
  // after a successful deletion.

  // We use "return true" below to enable compilation.  Change this as you
  // see fit.

  return true;
}
