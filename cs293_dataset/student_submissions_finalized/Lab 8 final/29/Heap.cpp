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
  // this function will return 
  // 0 if root is greater or equal than both
  // 1 if left should be sweaped with root
  // -1 right should be sweaped with root
  TreeNode<T> * L = root->left, * R = root->right;
  if ( R == nullptr and L == nullptr ) return 0;
  else if (R == nullptr and L != nullptr and root->object < L->object) return 1;
  else if (L == nullptr and R != nullptr and root->object < R->object) return -1;
  else if (R != nullptr and L != nullptr) {
    if (L->object < R->object) {
      if (root->object < R->object) return -1;
    }
    else{
      if (root->object < L->object) return 1;
    }
  }
  return 0;
}



template<typename T>
void Heapify(TreeNode<T> *root) { // Heapify full heap
  if (root == nullptr) return;    // base cases
  Heapify(root->left);            // recursion on left
  Heapify(root->right);           // recursion on right
  TreeNode<T>* currNode = root;   //
  while (currNode != nullptr) {   // switching all value
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
void Heap<T>::insert(T obj) { // this fucntion will insert a new node
  // special cases  
  if (root == nullptr) { // root is null
    root = new TreeNode<T> (obj);
    lastNode = root;
    return;
  }
  if (root->left == nullptr) { // root left is null
    root->left = new TreeNode<T> (obj);
    root->left->parent = root;
    lastNode = root->left;
    Heapify(root);  // after insertion heapify full tree
    return;
  }

  // general cases
  // last node is left child of it's parent
  if (lastNode->parent->left == lastNode) {
    lastNode->parent->right = new TreeNode<T>(obj); // if lastnode is null
    lastNode->parent->right->parent = lastNode->parent; // it's parent's 
    lastNode = lastNode->parent->right; // right should be null
    Heapify(root); // heapify full tree
    return;
  }

  // last node is right child of it's parent
  TreeNode<T> * currNode = lastNode;
  TreeNode<T> * P = lastNode->parent;
  while (P != nullptr) { // find currect position
    if (lastNode == P->left) {
      lastNode = P->right;
      break;
    }
    lastNode = P;
    P = P->parent;
  }
  while (lastNode->left != nullptr) lastNode = lastNode->left;
  lastNode->left = new TreeNode<T>(obj); // insert new node
  lastNode->left->parent = lastNode; // assigning parent
  lastNode = lastNode->left; 
  Heapify(root); // heapify full tree
  return;
}

template<typename T>
void Heap<T>::delMax() {  // delete first element 
  // special cases
  if (root == nullptr) return; // if root is null
  if (root->left == nullptr and root->right == nullptr) { 
    delete root;  // if root has no children
    root = nullptr;
    lastNode = nullptr;
    return;
  }

  // general cases
  sweap(lastNode, root); // sweap last node with root
  TreeNode<T> * N = lastNode; // storing last node
  TreeNode<T> * P = N->parent;// parent of last node

  // updating lastnode
  while (P != nullptr) { // find currect position
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
  Heapify(root); // heapify full tree
  return;
}

template<typename T>
void Heap<T>::printHeap(const string &prefix, bool isLeft) {
    if (root != NULL) {
        cout << prefix;
        cout << (isLeft ? "|--" : "|__");
        // print the value of the node
        cout << root->object << endl;
        TreeNode<T> *curr = root;
        root = root->left;
        // enter the next tree level - left and right branch
        printHeap(prefix + (isLeft ? "│   " : "    "), true);
        root = curr->right;
        printHeap(prefix + (isLeft ? "│   " : "    "), false);
        root = curr;
    }
}