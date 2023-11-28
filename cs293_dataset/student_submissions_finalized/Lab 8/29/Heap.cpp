#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef HEAP_H
#include "Heap.h"
#endif


// sweap two value
template<typename T>
void sweap(TreeNode<T> *a , TreeNode<T> *b) {
  T temp = a->object;
  a->object = b->object;
  b->object = temp;
}

template<typename T>
int Checker(TreeNode<T> * root) {
  // 0 if root is greater than both
  // 1 if left should be sweaped with root
  // -1 right should be sweaped with root
  TreeNode<T> * L = root->left, * R = root->right;
  if ( R == nullptr and L == nullptr ) return 0;
  else if (R == nullptr and L != nullptr and L->object > root->object) return 1;
  else if (R == nullptr and L != nullptr and L->object <= root->object) return 0;
  else if (L == nullptr and R != nullptr and R->object > root->object) return -1;
  else if (L == nullptr and R != nullptr and R->object <= root->object) return 0;
  else if (root->object >= R->object and root->object >= L->object) return 0;
  else if (R->object > L->object) return -1;
  return 1;
}



template<typename T>
void Heapify(TreeNode<T> *root) {
  if (root == nullptr) return;
  Heapify(root->left);
  Heapify(root->right);
  TreeNode<T>* currNode = root;
  while (currNode != nullptr) {
    int i = Checker(currNode);
    if ( i == 0 ) break;
    if ( i == -1) {
      sweap(currNode, currNode->right);
      currNode = currNode->right;
    }
    if ( i == 1) {
      sweap(currNode, currNode->left);
      currNode = currNode->left;
    }
  }
}


template<typename T>
void Heap<T>::insert(T obj) {
  // special cases
  if (root == nullptr) {
    root = new TreeNode<T> (obj);
    lastNode = root;
    return;
  }
  if (root->left == nullptr) {
    root->left = new TreeNode<T> (obj);
    root->left->parent = root;
    lastNode = root->left;
    Heapify(root);
    return;
  }

  // general cases
  // last node is left child of it's parent
  if (lastNode->parent->left == lastNode) {
    lastNode->parent->right = new TreeNode<T>(obj);
    lastNode->parent->right->parent = lastNode->parent;
    lastNode = lastNode->parent->right;
    return;
  }

  // last node is right child of it's parent
  TreeNode<T> * currNode = lastNode;
  TreeNode<T> * P = lastNode->parent;
  while (P != nullptr) {
    if (lastNode == P->left) {
      lastNode = P->right;
      break;
    }
    lastNode = P;
    P = P->parent;
  }
  while (lastNode->left != nullptr) lastNode = lastNode->right;
  lastNode->left = new TreeNode<T>(obj);
  lastNode->left->parent = lastNode;
  lastNode = lastNode->left;
  Heapify(root);
  return;
}

template<typename T>
void Heap<T>::delMax() {
  // special cases
  if (root == nullptr) return;
  if (root->left == nullptr and root->right == nullptr) {
    delete root;
    root = nullptr;
    lastNode = nullptr;
    return;
  }

  // general cases
  sweap(lastNode, root);
  TreeNode<T> * N = lastNode;
  TreeNode<T> * P = N->parent;

  // updating lastnode
  while (P != nullptr) {
    if (lastNode == P->right) {
      lastNode = P->left;
      break;
    }
    lastNode = P;
    P = P->parent;
  }
  while (lastNode->right != nullptr) lastNode = lastNode->right;
  if (N->parent->right == N) N->parent->right = nullptr;
  else N->parent->left = nullptr;
  // deleting last node
  delete N;
  Heapify(root);
  return;
}

template<typename T>
void Heap<T>::printHeap(TreeNode<T> *node) {

  if (node == nullptr) return;
  cout << node->object << endl;
  printHeap(node->left);
  printHeap(node->right);
  return;
}


