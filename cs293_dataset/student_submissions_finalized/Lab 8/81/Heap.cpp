#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef HEAP_H
#include "Heap.h"
#endif

template<typename T>
void Heap<T>::insert(T obj) {
  TreeNode<T>* newnode = new TreeNode<T>(obj);
  TreeNode<T>* currNode = root;


  return;
}

template<typename T>
T Heap<T>::delMax() {

  // insert your code here

  return;
}
template<typename T>
void Heap<T>::Heapify(TreeNode<T>* node) {

  TreeNode<T>* parent = node->parent;
  bool IsleftChild;
  if(parent->left==nullptr){IsleftChild = false;
      if(node->object)}
  if(parent->right==nullptr){IsleftChild = true;}
  if(parent->left == node){IsleftChild = true;}
  else 

  return;
}

template<typename T>
void Heap<T>::printHeap(const string& prefix, bool isLeft=false) {


    if( root != nullptr )
    {
        cout << prefix;

        cout << (isLeft ? "|--" : "|__" );

        // print the value of the node
        cout << root->JourneyCode << endl;
        TreeNode *curr = root;
        root = root->left;
        // enter the next tree level - left and right branch
        printBST( prefix + (isLeft ? "│   " : "    "), true);
        root = curr->right;
        printBST( prefix + (isLeft ? "│   " : "    "), false);
        root = curr;
    }
}

  
