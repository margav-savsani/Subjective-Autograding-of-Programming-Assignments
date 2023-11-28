#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef HEAP_H
#include "Heap.h"
#endif

template <typename T>
class listOf
{
public:
  T object;
  listOf<T> *next;
  listOf<T> *prev;

  // Constructor
  listOf(T initValue)
  {
    object = initValue;
    next = prev = nullptr;
  }

  // Destructor
  ~listOf() { ; }
};

template <typename T>
void recursiveDelete(listOf<T> *root)
{
  while (root != NULL)
  {
    listOf<T> *deleteMe = root;
    root = root->next;
    delete deleteMe;
  }
}

// the directions to follow to get from root to position in heap. root is at position 0.
listOf<bool> *getDirections(int position)
{
  if (position == 0)
  {
    return NULL; // no need of any instructions. we are already at root.
  }
  else
  {
    position = position + 1; // reindexing from 1
    listOf<bool> *fullDirections = new listOf<bool>(position % 2 == 1);
    position = position / 2;
    while (position > 0) // we will get the directions in reverse order
    {
      fullDirections->prev = new listOf<bool>(position % 2 == 1);
      fullDirections->prev->next = fullDirections;
      position = position / 2;
      fullDirections = fullDirections->prev;
    }
    listOf<bool> *returnMe = fullDirections->next;
    returnMe->prev = NULL;
    delete fullDirections;
    return returnMe;
  }
}

template <typename T>
void Heap<T>::insert(T obj)
{
  if (root == NULL)
  {
    root = new TreeNode<T>(obj);
    size++;
    return;
  }
  TreeNode<T> *insertUnderMe = root;
  TreeNode<T> *insertedNode = NULL;
  listOf<bool> *directionsToNewNode = getDirections(size);
  listOf<bool> *direction = directionsToNewNode;
  while (direction->next != NULL) // save the last direction
  {
    if (direction->object)
    {
      insertUnderMe = insertUnderMe->right;
    }
    else
    {
      insertUnderMe = insertUnderMe->left;
    }
    direction = direction->next;
  }
  if (direction->object) // may have to insert in either left or right
  {
    insertUnderMe->right = new TreeNode<T>(obj);
    insertUnderMe->right->parent = insertUnderMe;
    insertedNode = insertUnderMe->right;
  }
  else
  {
    insertUnderMe->left = new TreeNode<T>(obj);
    insertUnderMe->left->parent = insertUnderMe;
    insertedNode = insertUnderMe->left;
  }
  recursiveDelete(directionsToNewNode); // preventing resource leak
  while (insertedNode->parent != NULL && insertedNode->parent->object < insertedNode->object)
  {
    T temp = insertedNode->object;
    insertedNode->object = insertedNode->parent->object;
    insertedNode->parent->object = temp;
    insertedNode = insertedNode->parent;
  }
  size++;
  return;
}

template <typename T>
void Heap<T>::delMax()
{
  if (size == 1)
  {
    delete root;
    root = NULL;
    size--;
    return;
  }
  listOf<bool> *directionsToLastNode = getDirections(size - 1);
  TreeNode<T> *lastNode = root;
  listOf<bool> *direction = directionsToLastNode;
  while (direction != NULL) // read all directions
  {
    if (direction->object)
    {
      lastNode = lastNode->right;
    }
    else
    {
      lastNode = lastNode->left;
    }
    direction = direction->next;
  }
  // lastNode has been identified
  root->object = lastNode->object;
  if (size % 2 == 1) // lastNode is a right child
  {
    lastNode->parent->right = NULL;
  }
  else
  {
    lastNode->parent->left = NULL;
  }
  recursiveDelete(directionsToLastNode); // preventing resource leak
  delete lastNode;
  size--;
  TreeNode<T> *hiker = root;                             // hike this pointer down the heap
  while (!(hiker->left == NULL && hiker->right == NULL)) // has atleast one child
  {
    bool hasLeft = hiker->left != NULL;
    bool hasRight = hiker->right != NULL;
    if (!hasLeft) // has only right child
    {
      if (!(hiker->object < hiker->right->object))
      {
        break;
      }
      // swap with right and update hiker
      T temp = hiker->object;
      hiker->object = hiker->right->object;
      hiker->right->object = temp;
      hiker = hiker->right;
    }
    else if (!hasRight) // has only left child
    {
      if (!(hiker->object < hiker->left->object))
      {
        break;
      }
      // swap with left and update hiker
      T temp = hiker->object;
      hiker->object = hiker->left->object;
      hiker->left->object = temp;
      hiker = hiker->left;
    }
    else // has both children
    {
      // first check if heap property is violated
      if (!(hiker->object < hiker->left->object || hiker->object < hiker->right->object))
      {
        break; // there is no need for us to do any more
      }
      if (hiker->left->object < hiker->right->object) // swap with the right child and update hiker
      {
        T temp = hiker->object;
        hiker->object = hiker->right->object;
        hiker->right->object = temp;
        hiker = hiker->right;
      }
      else
      {
        T temp = hiker->object;
        hiker->object = hiker->left->object;
        hiker->left->object = temp;
        hiker = hiker->left;
      }
    }
  }
  return;
}

// Lab5 Tree.h printBinaryTree function
template <typename T>
void printBinaryTree(TreeNode<T> *root, const string &prefix, bool isLeft)
{
  if (root != nullptr)
  {
    cout << prefix;

    cout << (isLeft ? "|--" : "|__");

    // print the value of the node
    cout << root->object;
    cout << endl;
    TreeNode<T> *curr = root;
    root = root->left;
    // enter the next tree level - left and right branch
    printBinaryTree(root, prefix + (isLeft ? "│   " : "    "), true);
    root = curr->right;
    printBinaryTree(root, prefix + (isLeft ? "│   " : "    "), false);
    root = curr;
  }
  else
  {
    cout << prefix << "NULL heap" << endl;
  }
}

template <typename T>
void Heap<T>::printHeap(TreeNode<T> *node)
{
  // insert your code here
  printBinaryTree(root, "[", false);
  return;
}
