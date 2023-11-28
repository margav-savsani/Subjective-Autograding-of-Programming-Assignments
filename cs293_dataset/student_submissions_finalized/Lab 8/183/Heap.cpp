#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef HEAP_H
#include "Heap.h"
#endif

template<typename T>
void Heap<T>::insert(T obj) {
  // insert your code here
  
}
TreeNode<T> *Heap<T>::find(int l,TreeNode<T> *node,TreeNode<T> *prev){
  if ((node==NULL)&&(l==0)){return prev;}
  else{
    find(int l-1,node->right,node);
    find(int l-1,node->leftt,node)
    }
}
template<typename T>
void Heap<T>::delMax() {
  
  // insert your code here
  int l=0;
  while(node!=NULL){node=node->left;l++;}
  int p=0;
  TreeNode<T> *x=node;
  TreeNode<T> *p=find(l,node,NULL);
  node=p;
  if(p->prev->right==NULL){p->prev->left=NULL;}
  else{p->prev->right=NULL;}
  delete(p);
}

template<typename T>
void Heap<T>::printHeap(TreeNode<T> *node) {

  // insert your code here
  if(node==nullptr)
              return;
  cout<<node->object<<" "<<endl;
  if(node->left->object>node->right->object){
  printHeap(node->left);
  printHeap(node->right);}
  else{ printHeap(node->right);
        printHeap(node->left);}
  return;
}
void Heap<T>::Heapify(TreeNode<T> *node){
  if(t==nullptr) return;
  if((node->object<node->left->object)||(node->object<node->right->object)){
    TreeNode<T> *x=node;
    if(node->left->object<node->right->object){node->object=node->right->object;
                                                node->right->object=x->object;
                                                Heapify(node->left);}
    else{node->object=node->left->object;
          node->leftt->object=x->object;
          Heapify(node->right);}
  }
  else return;

  }
 
  
