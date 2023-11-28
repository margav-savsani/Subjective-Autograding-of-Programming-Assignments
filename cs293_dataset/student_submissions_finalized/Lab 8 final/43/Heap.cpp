#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#include<string>

#ifndef HEAP_H
#include "Heap.h"
#endif

string convert(int p){
  string s="";
  while(p != 1){
    s = to_string(p%2) + s;
    p = p/2;
  }
  return s;
}

template<typename T>  
void Heap<T>::insert(T obj) {
  // insert your code here
  TreeNode<T> * r = new TreeNode<T>(obj);
  if(root == nullptr){
    root = r;
    k++;
  }
  else if(k == 2){
    root->left = r;
    r->parent = root;
    k++;
  }
  else if(k == 3){
    root->right = r;
    r->parent = root;
    k++;
  }
  else{
    int p = k/2;
    TreeNode<T> *n = root;

    string s = convert(p);
    for(int i = 0;i < s.length();i++){
      if(s[i] == '0'){
        n = n->left;
      }
      else{
        n = n->right;
      }
    }

    if(k%2 == 0 ){
      n->left = r;
      r->parent = n;
      k++;
    }
    else{
      n->right = r;
      r->parent = n;
      k++;
    }
  }

  while(r->parent != nullptr){
    if(r->object < r->parent->object){
      break;
    }
    else{
      T exc = r->object;
      r->object = r->parent->object;
      r->parent->object = exc;
      r = r->parent;
    }
  }
  return;
}

template<typename T>
void Heap<T>::delMax() {
  if(k == 2){
    root = nullptr;
    k--;
  }
  else{
    int p = k-1;
    TreeNode<T> *last = root;
    
    string s = convert(p);
    for(int i = 0;i < s.length();i++){
      if(s[i] == '0'){
        last = last->left;
      }
      else{
        last = last->right;
      }
    }
     
    root->object = last->object;
    if(last->parent->left == last){
      last->parent->left = nullptr;
      k--;
    }
    else{
      last->parent->right = nullptr;
      k--;
    }

    TreeNode<T> *r = root;
    while(r->left != nullptr || r->right != nullptr){
      if(r->left == nullptr || r->right == nullptr){
        if(r->left == nullptr){
          if(r->object < r->right->object){
            T exec = r->right->object;
            r->right->object = r->object;
            r->object = exec;
            r = r->right;
          }
          else{
            break;
          }
        }
        else{
          if(r->object < r->left->object){
            T exec = r->left->object;
            r->left->object = r->object;
            r->object = exec;
            r = r->left;
          }
          else{
            break;
          }
        }
      }
      else{
        if(r->left->object < r->right->object){
          if(r->object < r->right->object){
            T exec = r->right->object;
            r->right->object = r->object;
            r->object = exec;
            r = r->right;
          }
          else{
            break;
          }
        }
        else{
          if(r->object < r->left->object){
            T exec = r->left->object;
            r->left->object = r->object;
            r->object = exec;
            r = r->left;
          }
          else{
            break;
          }
        }
      }
    }
  }
  // insert your code here

  return;
}

template<typename T> void printHeapTree(TreeNode<T> *root, const string& prefix, bool isLeft){
  if( root != nullptr )   {
    cout << prefix;
    
    cout << (isLeft ? "|--" : "|__" );
    
    // print the value of the node
    cout<< root->object<<endl;
    
    TreeNode<T> *curr = root;
    root = curr->left;
    // enter the next tree level - left and right branch
    printHeapTree(root, prefix + (isLeft ? "│   " : "    "), true);
    root = curr->right;
    printHeapTree(root, prefix + (isLeft ? "│   " : "    "), false);
    root = curr;
  }
  return;
}

template<typename T>
void Heap<T>::printHeap(TreeNode<T> *node) {

  printHeapTree(node,"",false);
  return;
  // insert your code here

  
}

  
