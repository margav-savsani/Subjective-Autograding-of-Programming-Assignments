#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef HEAP_H
#include "Heap.h"
#endif

int position = 0;
int b = 0;

template<typename T>
void Heap<T>::insert(T obj) {
  // insert your code here
  if(b == 1){
    position=0;
    root = nullptr;
    b = 0;
  }
  TreeNode<T> * t = new TreeNode <T> (obj);
  if(root == nullptr){
    root = t;
  }
  else{
    TreeNode<T> * last = root;
    bool* b = new bool[1000];
    int a = position+1;
    int i;
    for(i=0; a/2 > 0; i++){
      if(a%2 == 0) b[i] = true ;
      else b[i] = false;
      a = a/2;
    }
    for(int j=1; j <= i;j++){
      if(b[i-j] == true){
        if(j == i) {
          last->left = t;
          last->left->parent = last;
        }
        last = last->left;
      }
      else {
        if(j == i){
          last->right = t;
          last->right->parent = last;
        }
        last = last->right;
      }
    }
    while(last->parent!=nullptr && !(last->object < last->parent->object)){
      T temp = last->object;
      last->object = last->parent->object;
      last->parent->object = temp;
      last = last->parent;
    }
  }
  position++;
}

template<typename T>
void Heap<T>::delMax() {
  // insert your code here
  if(b==0)b=1;
  TreeNode<T> * lost = root;
  if((root->left==nullptr)&&(root->right==nullptr)){root=nullptr;return;}
  bool* b = new bool[100];
  int a = position;
  int i;
  for(i=0; a/2 > 0; i++){
    if(a%2 == 0) b[i] = true ;
    else b[i] = false;
    a = a/2;
  }
  for(int j=1; j <= i;j++){
    if(b[i-j] == true) lost = lost->left;
    else lost = lost->right;
  }

  T t = lost->object;
  lost->object = root->object;
  root->object = t;
  if(lost == lost->parent->left)lost->parent->left = nullptr;
  else lost->parent->right = nullptr;
  position--;

  TreeNode<T> * first = root;
  if(first->right == nullptr && first->left == nullptr)return;
  else if(first->right == nullptr){
    if(first->object < first->left->object){
      T t1 = first->left->object;
      first->left->object = first->object;
      first->object = t1;
      first = first->left;
      return;
    }
    else return ;
  }
  while(first->object < first->right->object || first->object < first->left->object ){
    if(first->object < first->right->object && first->object < first->left->object){
      if(first->right->object < first->left->object){
        T t1 = first->left->object;
        first->left->object = first->object;
        first->object = t1;
        first = first->left;
        if(first->right == nullptr || first->left == nullptr)return;
      }
      else{
        T t2 = first->right->object;
        first->right->object = first->object;
        first->object = t2;
        first = first->right;
        if(first->right == nullptr || first->left == nullptr)return;
      }
    }
    else if(first->object < first->right->object){
      T t3 = first->right->object;
      first->right->object = first->object;
      first->object = t3;
      first = first->right;
      if(first->right == nullptr || first->left == nullptr)return;
    }
    else{
      T t4 = first->left->object;
      first->left->object = first->object;
      first->object = t4;
      first = first->left;
      if(first->right == nullptr || first->left == nullptr)return;
    }
  }
}

template<typename T>
void Heap<T>::printHeap(TreeNode<T> *node){
  static string pre = "";
  static bool left = false;
  static int recursion_level = 0;

  recursion_level++;
  if (recursion_level == 1)
  {
      pre = "";
      left = false;
  }

  if (node != nullptr)
  {
      if (left) cout << pre <<"|--" << node->object << "\n";
      else cout << pre << "|__" << node->object << "\n";
      string x=pre;
      pre=pre+"   ";
      left = true;
      printHeap(node->left);
      x=x+"   ";
      pre=x;
      left = false;
      printHeap(node->right);
  }
  recursion_level--;

  return;
}