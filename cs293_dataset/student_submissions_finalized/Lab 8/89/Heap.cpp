#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef HEAP_H
#include "Heap.h"
#endif

template<typename T>
void Heap<T>::insert(T obj) {
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
   if(node==NULL) return
   cout<<node->object<<" "<<endl;
   printHeap(node->left);
   printHeap(node->right) 
  // insert your code here

}

template<typename T>
void Heap<T>::Heapify(TreeNode<T> *node){
   if(T==NULL) return;
   if((node->object < node->left->object) || (T->object < T->right->object))
       {
         TreeNode<T> *X = node;
         if(node->left->object > node->right->object)
             {
               node->object=node->left->object;
               node->left->object=X->object;
                Heapify(T->left); 
               }
         else if(node->left->object > node->right->object)      
             {
               node->object=node->right->object;
               node->right->object=X->object; 
               Heapify(T->right);            
              }
         }
   else return;           

}  
