#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef HEAP_H
#include "Heap.h"
#endif

template<typename T>
void Heap<T>::insert(T obj) {
  // insert your code here
  
  //traverse down to obj
  std::vector<bool> binary;
  int temp = size;
  while( temp > 0 ){
    
    binary.push_back(temp%2);
    temp /= 2;
  }

  TreeNode<T>* currNode = root;
  while (binary.size() > 1)
  {
    if( binary.at(binary.size() - 1)){
      currNode = currNode->next;
    }
  }

  
  

  size++;
  
  return;
}

template<typename T>
T Heap<T>::delMax() {

  // insert your code here


  return;
}

template<typename T>
void Heap<T>::printHeap(TreeNode<T> *node) {

  // insert your code here
  // no you

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

  return;
}

  
