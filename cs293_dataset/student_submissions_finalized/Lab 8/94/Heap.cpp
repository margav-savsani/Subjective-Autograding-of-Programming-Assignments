#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif
#include<vector>
using namespace std;
#ifndef HEAP_H
#include "Heap.h"
#include<cmath>
#endif

template<typename T>
void Heap<T>::insert(T obj) {
  // insert your code here
  if(num==0){
    root=new TreeNode(obj);
    num++;
    return;
  }
  else{
    vector<int>k=convert(num+1);
    reverse(k.begin(),k.end());
    TreeNode<T> curr=root;
    for(int i=0;i<k.size()-1;i++){
      if(k[i]==0) curr=curr.left;
      else curr=curr.right;
    }
    if(k[k.size()-1]==0){
      curr.left=new TreeNode(obj);
      curr.left->parent=curr;
      return;
    }
    else{
      curr.right=new TreeNode(obj);
      curr.right->parent=curr;
      return;
    }

  }
  return;
}
vector<int> convert(int n){
    vector<int> a;
    while(n!=1){
        a.push_back(n%2);
        n=n/2;
    }
    return a;

}

template<typename T>
void Heap<T>::delMax() {
  vector<int> k=convert(num);
  TreeNode<T> curr=root;
  T obj1=root.object;
  for(int i=0;i<k.size()-1;i++){
      if(k[i]==0) curr=curr.left;
      else curr=curr.right;
  }
  if(k[k.size()-1]==0){
    T obj2=curr.left->object;
    curr.left->object=obj1;
    root.object=obj2;
    curr.left=NULL;
  }
  else{
    T obj2=curr.right>object;
    curr.right->object=obj1;
    root.object=obj2;
    curr.right=NULL;
  }

  // insert your code here

  return;
}
template<typename T>
void Heap<T>::Heapify(TreeNode<T> r1){;
  TreeNode<T> r=r1;
  if(r.left==NULL && r.right==NULL) return;
  else if(r.left!=NULL && r.right==NULL){
    exchange(r,*(r.left));
    Heapify(*(r.left));
    return;
  }
  else(r.left!=NULL && r.right!=NULL){
    
  }

  return;

}
template<typename T>
void exchange(TreeNode<T> a,TreeNode<T>b){
  T obj=a.object;
  a.object=b.object;
  b.object=T;
  return;
}

template<typename T>
void Heap<T>::printHeap(TreeNode<T> *node) {

  // insert your code here

  return;
}

  
