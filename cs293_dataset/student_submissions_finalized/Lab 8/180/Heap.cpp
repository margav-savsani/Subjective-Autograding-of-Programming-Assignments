#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef HEAP_H
#include "Heap.h"
#endif

void swap (TreeNode<int> *a,TreeNode<int> *b){
  int temp = a->object;
  a->object = b->object;
  b->object = temp;
}
template<typename T>
void Heap<T>::insert(T obj) {
  // insert your code here
  TreeNode<T> *temp = root;
  if(temp == nullptr){
    TreeNode<T> *first = new TreeNode<T>(obj);
    root = first;
    last = first;
    cout << "here" << endl;
  }
  else{
    TreeNode<T> *p = last->parent;
    TreeNode<T> *ins = new TreeNode<T>(obj);
    if(p == nullptr){    
      root->left = ins;
      ins->parent = root;
      last = ins;
    }
    else if(p->left == last){
      p->right = ins;
      ins->parent = p;
      last = ins;
    }
    else{
      bool breaked = false;
      while(p->parent != nullptr){
        if(p->parent->left == p){
          TreeNode<T> *k = p->parent;
          while(k->right != nullptr){
            k = k->right;
          }
          k->right = ins;
          ins->parent = k;
          breaked = true;
          break;
        }
        p = p->parent;
      }
      if(breaked == false){
          while(p->left != nullptr){
            p = p->left;
          }
          p->left = ins;
          ins->parent = p;
      }
      last = ins;
    }

  while(ins->parent != nullptr){
    if(ins->parent->object < ins->object){
      swap(ins,ins->parent);
    }
    ins = ins->parent;
  }  
  }
  this->printHeap(this->root);
  cout << "root: " <<root->object << endl;
  cout << "last :" << last->object << endl;
  cout << "------------------------------------------------" << endl;
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
  if(node == nullptr){
    cout <<"null" <<endl;
    return;
  }
  cout << node->object << endl;
  printHeap(node->left);
  printHeap(node->right);

  return;
}

  
