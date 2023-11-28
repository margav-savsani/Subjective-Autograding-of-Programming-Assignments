#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef HEAP_H
#include "Heap.h"
#endif

template<typename T> void Heap<T>::Heapifyup(TreeNode<T> *x){
  // Heapify up implements function of moving element up if its greater than its parent
  if(x->parent == nullptr ) return;                           
  if((x->parent)->object < x->object){
    T obj = x->object;
    x->object = (x->parent)->object;
    (x->parent)->object = obj;    
    Heapifyup(x->parent);
  }
  return;
}

template <typename T> int Heap<T> :: maxheight(TreeNode<T> *x){
  // calculates maximum height of heap from TreeNode x
  if(x == NULL)return -1;
  return 1 + maxheight(x->left);
}

template <typename T> int Heap<T> :: minheight(TreeNode<T> *x){
   // calculates minimum height of heap from TreeNode x
  if(x == NULL)return -1;
  return 1 + minheight(x->right);
}

template<typename T> void Heap<T>::insertNode(TreeNode<T> *x, T obj){
  // inserts node in a heap whose root is x
  if((x->left!=NULL)&&(x->right!=NULL)){
    if((maxheight(x->left)==minheight(x->left))){
      if(maxheight(x->left)==(maxheight(x->right))){
        if(maxheight(x->right)==(minheight(x->right))){
          insertNode(x->left,obj);
        }
        else{
          insertNode(x->right,obj);
        }
      }
      else insertNode(x->right,obj);
    }
    else insertNode(x->left,obj);
  }
  else if((x->left)==NULL){
    x->left = new TreeNode<T>(obj);
    (x->left)->parent = x;    
    Heapifyup(x->left);
  }  
  else{
    x->right = new TreeNode<T>(obj);
    (x->right)->parent = x;    
    Heapifyup(x->right);
  }
  return;
}

template<typename T> void Heap<T>::insert(T obj) {
  // insert your code here
  // inserts node into heap 
   if(root == nullptr){
    root = new TreeNode<T>(obj);
    return;    
  }
  insertNode(root, obj);
  return;
}

template<typename T> void Heap<T>::Heapifydown(TreeNode<T> *x){
  // moves an element down if its less than any of them
  if(((x->left)==NULL)&&((x->right)==NULL))return ;
  else if((x->right)==NULL){
    if(x->object < (x->left)->object){
      T obj = x->object;
      x->object = (x->left)->object;
      (x->left)->object = obj;      
    }   
    return;  
  }
  else if(((x->left)!=NULL)&&((x->right)!=NULL)){
    if(((x->left)->object < x->object)&&((x->right)->object < x->object))return;
    if(((x->left)->object)<((x->right)->object)){
      if(x->object < (x->right)->object){
        T obj = x->object;
        x->object = (x->right)->object;
        (x->right)->object = obj;
        Heapifydown(x->right);
      }     
    }
    else{
      if(x->object < (x->left)->object){
        T obj = x->object;
        x->object = (x->left)->object;
        (x->left)->object = obj;
        Heapifydown(x->left);
      }     
    } 
  }  
  return; 
}

template<typename T> TreeNode<T>* Heap<T>::lastinsert(TreeNode<T> *x){
  // function to find lastinsert
  if((x->left!=NULL)&&(x->right!=NULL)){
    if((maxheight(x->left)==minheight(x->left))){
      if(maxheight(x->left)==(maxheight(x->right))){
        if(maxheight(x->right)==(minheight(x->right))){
          return lastinsert(x->right);
        }
        else{
          return lastinsert(x->right);
        }
      }
      else return lastinsert(x->left);
    }
    else return lastinsert(x->left);
  }
  else if((x->left!=NULL)&&(x->right==NULL)) return x->left;
  return x;   
} 

template<typename T> void Heap<T>::delMax() {

  // insert your code here
  // deletes the maximum element
  TreeNode<T>* x = lastinsert(root);  
  if(x==root){ 
    root = nullptr;   
    return;
  }
  root->object = x->object;
  if((x->parent)->left == x)(x->parent)->left = NULL;
  else (x->parent)->right = NULL;
  Heapifydown(root);  
  return;
}

template<typename T> void Heap<T>::printHeapTree(TreeNode<T> *root,const string& prefix, bool isLeft) {
   if( root != nullptr )   {
    cout << prefix;
    
    cout << (isLeft ? "|--" : "|__" );
    
    // print the value of the node
    cout << "[Rt: " << (root->object).rating << ", id: " << (root->object).revId << "]";
    cout << endl;
    TreeNode<T> *curr = root;
    root = root->left;
    // enter the next tree level - left and right branch
    printHeapTree(root, prefix + (isLeft ? "│   " : "    "), true);
    root = curr->right;
    printHeapTree(root, prefix + (isLeft ? "│   " : "    "), false);
    root = curr;
  }
  else {
    cout << "NULL Heap" << endl;
  }
}

template<typename T> void Heap<T>::printHeap() {

  // insert your code here 
  printHeapTree(root," ",false);
  return;
}

template<typename T> void Heap<T>::recursivedelete(TreeNode<T>*x){
  if(x==nullptr){
    return;
  }
  else{
    TreeNode<T> *currNode = x->left;
    recursivedelete(currNode);
    x->left = nullptr;
    currNode = x->right;
    recursivedelete(currNode);
    x->right = nullptr;
    if(x!=root){
      delete x;
    }
    return;
  }
}  


  