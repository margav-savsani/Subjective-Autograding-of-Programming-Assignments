#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef HEAP_H
#include "Heap.h"
#endif

#include <algorithm>

string decimal_to_binary_path(int a){
  string path = "";

  while(a > 0){
    if (a%2 == 0) path += 'l';
    else path += 'r';
    a /= 2;
  }

  reverse(path.begin(), path.end());
  return path;
}

template<typename T> void swap_TreeNodes(TreeNode<T>* node_1, TreeNode<T>* node_2){
  T tmp_object_1 = node_1 -> object;
  T tmp_object_2 = node_2 -> object;

  node_1 -> object = tmp_object_2;
  node_2 -> object = tmp_object_1;
}

template<typename T> void make_parent_child(TreeNode<T>* parent_, TreeNode<T>* child_, bool isLeft){
  if (parent_ != nullptr){
    if (isLeft) parent_ -> left = child_; 
    else parent_ -> right = child_;
  }
  if (child_ != nullptr) child_ -> parent = parent_;
}

template<typename T> void Heap<T>::heapify(TreeNode<T>* node){
  if (node == nullptr) return;

  TreeNode<T>* left_ = node -> left;
  TreeNode<T>* right_ = node -> right;

  if (left_ == nullptr && right_ == nullptr) {return;}
  if (left_ != nullptr && right_ == nullptr) {if (*node < *left_) {swap_TreeNodes(left_, node); heapify(left_); return;}}
  if (left_ == nullptr && right_ != nullptr) {if (*node < *right_) {swap_TreeNodes(right_, node); heapify(right_); return;}}

  if (left_ != nullptr && right_ != nullptr){
    if(*left_ < *node && *right_ < *node) {return;}
    else{
      if (*left_ < *right_) {swap_TreeNodes(node, right_); heapify(right_);}
      else {swap_TreeNodes(node, left_); heapify(left_);}
      return;
    }
  }
}

template<typename T> void Heap<T>::insert(T obj){

  TreeNode<T>* to_insert = new TreeNode<T>(obj);

  if (size == 0) {root = to_insert; size++; return;}

  string path = decimal_to_binary_path(++size);
  int path_size = path.length();

  TreeNode<T>* current_node = root;

  for (int i = 1; i < path_size - 1; i++){
    if ((path[i] == 'l')) current_node = current_node -> left;
    else current_node = current_node -> right;
  }

  make_parent_child(current_node, to_insert, path[path_size - 1] == 'l');

  TreeNode<T>* move_up = to_insert;

  while ((move_up -> parent != nullptr) && (*(move_up -> parent) < *move_up)){
    swap_TreeNodes(move_up, move_up -> parent);
    move_up = move_up -> parent;
  }
}

template<typename T> void Heap<T>::delMax(){

  if (size == 0) return;
  if (size == 1) {root = nullptr; size--; return;}

  string path = decimal_to_binary_path(size--);
  int path_size = path.length();

  TreeNode<T>* current_node = root;

  for (int i = 1; i < path_size; i++){
    if (path[i] == 'l') current_node = current_node -> left;
    else current_node = current_node -> right;
  }

  swap_TreeNodes(current_node, root);

  make_parent_child(current_node -> parent, current_node -> left, current_node -> parent -> left == current_node);
  delete(current_node);

  heapify(root);
}

template<typename T> void print_tree(const string& prefix, TreeNode<T>* node, bool isLeft = false){
  if(node != nullptr){
    cout << prefix;
    cout << (isLeft ? "|--" : "|__" );

    cout << node -> object;
    cout << endl;

    print_tree(prefix + (isLeft ? "│   " : "    "), node -> left, true);
    print_tree(prefix + (isLeft ? "│   " : "    "), node -> right, false);
    }
  return;
} 

template<typename T> void Heap<T>::printHeap(TreeNode<T>* node){
  print_tree("", node, false);
}

  
