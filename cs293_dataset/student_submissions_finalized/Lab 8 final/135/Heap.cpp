#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef HEAP_H
#include "Heap.h"
#endif

template<typename T>
void Heap<T>::insert(T obj) {
  // insert your code here
  TreeNode<T>* toadd = new TreeNode<T>(obj);
  numberOfNodes++;
  if(root == nullptr){
    root = toadd;
    return;
  }

  int b=binary(numberOfNodes);
  TreeNode<T>* prev = nullptr;
  TreeNode<T>* currNode = root;
  bool isleft = 1;
  b=b/10;
  
  while(b>0){
    int r = b%10;
    b=b/10;
    prev = currNode;
    if(r){
      currNode = currNode->right;
      isleft = 0;
    }
    else{
      currNode = currNode->left;
      isleft = 1;
    }
  }

  while(currNode != nullptr){
    prev = currNode;
    currNode = currNode->left;
    isleft = 1;
  }

  toadd->parent = prev;
  if(isleft) prev->left = toadd;
  else prev->right = toadd;

  while(toadd->parent != nullptr && toadd->parent->object < toadd->object){
    T temp = toadd->object;
    toadd->object = toadd->parent->object;
    toadd->parent->object = temp;
    toadd = toadd->parent;
  }

  return;
}

template<typename T>
void Heap<T>::delMax() {

  // insert your code here

  // printHeap(nullptr);

  if(numberOfNodes == 0) return;
  numberOfNodes--;
  if(numberOfNodes == 0){
    root = nullptr;
    return;
  }
  
  int b=binary(numberOfNodes+1);
  TreeNode<T>* currNode = root;
  bool isleft = 1;
  b=b/10;
  
  while(b>0){
    int r = b%10;
    b=b/10;
    if(r){
      currNode = currNode->right;
      isleft = 0;
    }
    else{
      currNode = currNode->left;
      isleft = 1;
    }
  }

  while(currNode->left != nullptr){
    currNode = currNode->left;
    isleft = 1;
  }

  if(isleft) currNode->parent->left = nullptr;
  else currNode->parent->right = nullptr;

  T temp = currNode->object;
  currNode = nullptr;
  root->object = temp;
  heapify(root);

  // printHeap(nullptr);

  return;
}

template<typename T>
void Heap<T>::printHeap(TreeNode<T> *node) {

  // insert your code here
  printTree("", false);

  return;
}

template <typename T>
void Heap<T>::printTree(const string& prefix, bool isLeft)
{
    if( root != nullptr )
    {
        cout << prefix;

        cout << (isLeft ? "|--" : "|__" );

        // print the value of the node
        cout << root->object << endl;
        TreeNode<T> *curr = root;
        root = root->left;
        // enter the next tree level - left and right branch
        printTree( prefix + (isLeft ? "│   " : "    "), true);
        root = curr->right;
        printTree( prefix + (isLeft ? "│   " : "    "), false);
        root = curr;
    }
}
