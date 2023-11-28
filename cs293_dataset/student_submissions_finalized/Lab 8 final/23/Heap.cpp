#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef HEAP_H
#include "Heap.h"
#endif
template<typename T>
void Heap<T>::insert(T obj) {
  int n = sizeof(H)/sizeof(H[0]);
  if(n < 10000){
    n = n+1;
    H[n-1] = obj;
    upheapify(n , n-1);
    arraytotree(n);
  }  
}

template<typename T>
void Heap<T>::delMax() {
  n = sizeof(H)/sizeof(H[0]);
  if(n > 0){
  if (n == 1){
    H = new T[10000];
    n = 0;
  }
  else {
    n = n-1;
    H[0] = H[n];
    downheapify(n,0);
    arraytotree(n);
  }
  
 }
}
template<typename T>
void Heap<T>::upheapify(int n, int i){
  int parent = (i-1)/2;
  if(0 < parent){
    if(H[parent] < H[i]){
      T a;
      a = H[i];
      H[i] = H[parent];
      H[parent] = a;
      upheapify(n,parent);
    }
  }
}

template<typename T>
void Heap<T>::downheapify(int n, int i){
  int largest = i; 
  int l = 2 * i + 1; 
  int r = 2 * i + 2; 
  if (l < n && H[largest] < H[l])
      largest = l;
  if (r < n && H[largest] < H[r])
      largest = r;
  if (largest != i) {
      T a;
      a = H[i];
      H[i] = H[largest];
      H[largest] = a;
      downheapify(n, largest);
  }
}

template<typename T>
void Heap<T>::arraytotree(int n){
  TreeNode<T>** allnodes;
  allnodes = new TreeNode<T>*[n];
  for(int i = 0; i < n; i++){
    allnodes[i] = new TreeNode<T>(H[i]);
  }
  allnodes[0]->parent = NULL;
  root = allnodes[0];
  for(int i = 1; i < n; i++){
    allnodes[i]->parent = allnodes[(i-1)/2];
  }
  for(int i = 0; 2*i+1 < n; i++){
    allnodes[i]->left = allnodes[2*i+1];
  }
  for(int i = 0; 2*(i+1) < n; i++){
    allnodes[i]->right = allnodes[2*(i+1)];
    }
}

template<typename T>
void Heap<T>::printHeap() {
  n = sizeof(H)/sizeof(H[0]);
  for(int j = 0; j<n;j++){
    cout<<H[j]<<endl;
  }
}

  
