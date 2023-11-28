#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef HEAP_H
#include "Heap.h"
#endif

void binary(int n, int* binaryN){
  int i = 0;
  while (n > 0) {
        binaryN[i] = n % 2;
        n = n / 2;
        i++;
  }
  return;}

template<typename T>
void Heap<T>::Heapifyup(TreeNode<T> *n){
  if (num==1) return;
 TreeNode<T> *x = n;
 while ((x!= root) && (x->parent->object < x->object)){
       T temp=x->object;
       x->object=x->parent->object;
       x->parent->object=temp;
       x=x->parent;        
}}

template<typename T>
void Heap<T>::Heapifydown(TreeNode<T> *n){
  if(n->left == nullptr) return;
  if(n->right == nullptr)
  {
    if(n->object<n->left->object)
    {
             T temp=n->left->object;
             n->left->object=n->object;
             n->object=temp;
    }
    return;
  }
  TreeNode<T> *x=n;
  TreeNode<T> *l=x->left;
  TreeNode<T> *r=x->right;
 
      if (n->object < l->object || n->object < r->object){
           if (r->object<l->object){
             T temp=l->object;
             l->object=l->parent->object;
             l->parent->object=temp;
             Heapifydown(l);}
           else if(l->object<r->object){
             T temp=r->object;
             r->object=r->parent->object;
             r->parent->object=temp;
             Heapifydown(r);}
           return;
     }
     else return;
}

template<typename T>
void Heap<T>::insert(T obj) {

  // insert your code here
  TreeNode<T> *x=root;
 
  TreeNode<T> *n=new TreeNode<T> (obj);
  
    if (num==1){root=n;num++;cout<<num<<endl;return; }

  int binaryN[32];
  binary(num,binaryN);

  int k=31;//to find number of digits in binary number
  while(binaryN[k]!=1){
     k--;}
  k=k-1;
  //as the leftmost number in binary is 1
  // im starting from its next number
    
  while(k>0){
   if (binaryN[k]==0){x=x->left;}
   else if (binaryN[k]==1){x=x->right;}
   
   k--;
  }
  if (binaryN[0]==0){x->left=n;}
  
  else {x->right=n;}
  num++;
   
    n->parent=x;
  Heapifyup(n);
 
  return;
}

template<typename T>
void Heap<T>::delMax() {

  // insert your code here
  TreeNode<T> *x=root;
  if (num==2){root=nullptr;num=1;}
  else {num=num-1;
  int arr[32];
  binary(num,arr);
  int k=31;//to find number of digits in binary number
  while(arr[k]!=1){
     k--;}
  while(k>-1){
   if (arr[k]==0){x=x->left;}
   else if (arr[k]==1){x=x->right;}
   k--;
  }
  root->object=x->object;
  x=nullptr;
  Heapifydown(root);
  return;
}
return;}
  

template<typename T>
void Heap<T>::printHeap(TreeNode<T> *node) {

  return;
}

  
