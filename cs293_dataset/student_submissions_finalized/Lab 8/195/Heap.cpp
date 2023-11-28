#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef HEAP_H
#include "Heap.h"
#endif

template<typename T>
int* Binary(n){
    int i=0;
    int s=n;
    while(n!=0){
      n=n/2;
      i=i+1;
    }
    int arr[i];
    for(int j=0;j<i;j++){
      arr[j]=s%2;
      s=s/2;
    }
    return arr;
}
void Heap<T>::insert(T obj) {
  if(root==nullptr){
    root=TreeNode(obj);
    sz=1;
    return;
  }
  else{
    int b=0;
    int a=sz+1;
    while(a!=0){
      a=a/2;
      b=b+1;
    }
    int as[b];
    as=Binary(sz+1);
    int sa[b];
    for(int z=0;z<b;z++){
      sa[z]=as[b-1-z];
    }
    TreeNode<T> c=root;
    int k=1;
    int l=1;
    while(k!=b-1){
      if(sa[l]==1){
        c=c->right;
        l=l+1;
        k=k+1;
      }
      else{
        c=c->left;
        l=l+1;
        k=k+1;
      }
    }
    if(sa[l]==1){
      TreeNode<T> p=new TreeNode(obj);
      c->right=p;
      return;
    }
    else{
      TreeNode<T> p=new TreeNode(obj);
      c->left=p;
      return;
    }
  }
  // insert your code here

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

  
