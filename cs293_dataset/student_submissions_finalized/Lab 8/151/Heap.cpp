#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef HEAP_H
#include "Heap.h"
#endif

template<typename T>
void Heap<T>::insert(T obj) {
  // insert your code here

  noOfChildren++;
  int currPos = noOfChildren;

  stack<bool> goLeft; // true if left child, else false

  while(currPos != 1){
    goLeft.push(currPos % 2);
    currPos /= 2;
  }

  TreeNode<T> currNode = root;
  
  if(goLeft.size == 0){
    root->object = obj;
    return;
  } else if(goLeft.size == 1){
    if(goLeft.top())
      currNode->left = new TreeNode<T>(obj);
    else
      currNode->right = new TreeNode<T>(obj);
    return;
  } else {
    if(goLeft.top())
      currNode = currNode->left;
    else
      currNode = currNode->right;
    goLeft.pop();
  }


  return;
}

template<typename T>
void Heap<T>::delMax() {

  // insert your code here

  return;
}

template<typename T>
void Heap<T>::printHeap() {

  // insert your code here

  preOrder(root);


}

template<typename T>
void Heap<T>::preOrder(TreeNode<T>* x){

    	if(x == nullptr) return;
    else {
        cout << x->object << endl;
        preOrder(x->left);
        preOrder(x->right);
    }
}


  
