#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef HEAP_H
#include "Heap.h"
#endif

#include "circularQueue.cpp"

template<typename T>
void Heap<T>::insert(T obj) {
  // insert your code here

  // Creating a new Node
  TreeNode<T> *newNode = new TreeNode<T>;
  newNode->object = obj;

  // If Heap is initially empty.
  if(root == nullptr)
  {
    root = newNode;
    return;
  }

  // A QUEUE q to help find the first empty location. i.e. The first empty location in the last level of the heap.
  DynamicQueue< TreeNode<T>* > helperQueue;
  helperQueue.QInsert(root);

  // We keep removing from the queue. Then check if left child is null ,then it is the place to create new node and break. Else check for right child and do the same. If none of them happens, then first push left chld, then right child into the queue.
  while(true)
  {
    TreeNode<T> *node = helperQueue.front();
    helperQueue.QDelete();

    if(node->left == nullptr)
    {
      node->left = newNode;
      newNode->parent = node; 
      break;
    }
    else if(node->right == nullptr)
    {
      node->right = newNode;
      newNode->parent = node;
      break;
    }

    helperQueue.QInsert(node->left);
    helperQueue.QInsert(node->right);

  }

  // Now we use trav pointer to traverse up the heap and swap values if necessary. After the first position where swap is not required found, we exit the loop.
  TreeNode<T> *trav = newNode;

  while(true)
  {
    TreeNode<T>* parentNode = trav->parent;
    if(parentNode == nullptr) break;

    if(parentNode->object < trav->object)
    {
      T temp = trav->object;
      trav->object = parentNode->object;
      parentNode->object = temp;
      trav = parentNode;
    }
    else
    {
      // No swap required, so exit.
      break;
    }
  }

  return;
}




template<typename T>
void Heap<T>::delMax() {

  // insert your code here

  // If heap is empty, return
  if(root == nullptr) return;

  TreeNode<T> *trav = root;
  // If only one node in the heap, then make root nullptr.
  if(root->left == nullptr && root->right == nullptr)
  {
    root = nullptr;
    delete trav;
    return;
  } 

  // We use queue to find first empty location in the last level. But but we also store the just left node at the level .
  DynamicQueue< TreeNode<T>* > helperQueue;
  helperQueue.QInsert(root);
  TreeNode<T> *lastNode = root;

  // Keep updating the lastNode, and check if left or right is null.
  while(true)
  {
    TreeNode<T> *node = helperQueue.front();
    helperQueue.QDelete();

    if(node->left == nullptr)
    {
      break;
    }
    lastNode = node->left;

    if(node->right == nullptr)
    {
      break;
    }
    lastNode = node->right;

    helperQueue.QInsert(node->left);
    helperQueue.QInsert(node->right);

  }

  // Now we have found the last node in the heap. So swap values of lastnode and root. 
  T val = root->object;
  root->object = lastNode->object;

  //and delete the last node
  TreeNode<T> *parentNode = lastNode->parent;
  if(parentNode->left == lastNode) parentNode->left = nullptr;
  else parentNode->right = nullptr;
  delete lastNode;


  // Now we traverse from root to its child and keep heapifying.
  while(trav != nullptr && (trav->left != nullptr || trav->right != nullptr))
  {
    if(trav->object < trav->left->object || trav->object < trav->right->object)
    {
        if(trav->object < trav->left->object)
        {
          T temp = trav->object;
          trav->object = trav->left->object;
          trav->left->object = temp;
          trav = trav->left;
        }
        else
        {
          T temp = trav->object;
          trav->object = trav->right->object;
          trav->right->object = temp;
          trav = trav->right;
        }
    }
    else break;
  } 

  return;
}

template<typename T>
void Heap<T>::printHeap(TreeNode<T> *node) {

  // insert your code here

  return;
}

  
