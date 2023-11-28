#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef HEAP_H
#include "Heap.h"
#endif
#include<vectors>



template<typename T>
void Heap<T>::insert(T obj) {
  // insert your code here
  if(N==0){
    root = new TreeNode(obj);
    N++;
  }
  else{
    vector<int>k = DecimalForm(N+1);
    reverse(k.begin(),k.end());
    TreeNode<T> currNode=root;
    for(int i=0;i<k.size()-1;i++){
      
    }
  }
  return;
}

template<typename T>
void Heap<T>::delMax() {

  // insert your code here

  return;
}

template<typename T>
void Heap<T>::printHeap(TreeNode<T> *node) {

  // insert your code here

  return;
}

  
