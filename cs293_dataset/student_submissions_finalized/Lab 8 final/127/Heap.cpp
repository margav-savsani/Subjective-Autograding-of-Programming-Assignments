#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef HEAP_H
#include "Heap.h"
#endif

template<typename T>
void Heap<T>::relocate_cur_node() {

  if(check_power_of_two(size+1)) {
    cur_node=root;
    while(cur_node->left!=nullptr) {
      cur_node=cur_node->left;
    }
  }
  else {
    int nodes_to_travel=ffs(size+1)-1;
    for(int i=0; i<nodes_to_travel; i++) {
      cur_node=cur_node->parent;
    }
    if(cur_node->right!=nullptr) cur_node=cur_node->right;
    for(int j=0; j<nodes_to_travel-1; j++) {
      cur_node=cur_node->left;
    }
  }
}

template <typename T>
void Heap<T>::get_old_cur_node() {

  if(check_power_of_two(size+1)) {
    cur_node=root;
    while(cur_node->right->right!=nullptr) {
      cur_node=cur_node->right;
    }
  }
  else {
    int nodes_to_travel=ffs(size+1)-1;
    for(int i=0; i<nodes_to_travel; i++) {
      cur_node=cur_node->parent;
    }
    if(cur_node->left!=nullptr) cur_node=cur_node->left;
    for(int j=0; j<nodes_to_travel-1; j++) {
      cur_node=cur_node->right;
    }

    //go up and look to the right, using size
  }
}

template<typename T>
void Heap<T>::insert(T obj) {
  TreeNode<T>* child_node = new TreeNode<T>(obj);
  TreeNode<T>* parent_node = cur_node;
  T temp_obj;
  size+=1;

  if(root==nullptr) {
    root=child_node;
    cur_node=child_node;
    return;
  }

  else {
    if(parent_node->left==nullptr) {
      parent_node->left=child_node;
      child_node->parent=parent_node;
    }
    else if(parent_node->right==nullptr) {
      parent_node->right=child_node;
      child_node->parent=parent_node;
      relocate_cur_node();
    }

    while(parent_node!=nullptr && parent_node->object.rating < child_node->object.rating) {
      temp_obj=parent_node->object;
      parent_node->object=child_node->object;
      child_node->object=temp_obj;
      child_node=parent_node;
      parent_node=parent_node->parent;
    }
  }

  return;
}

template<typename T>
void Heap<T>::delMax() {
  TreeNode<T>* parent_node=root;
  TreeNode<T>* child_node;
  while(parent_node->left!=nullptr || parent_node->right!=nullptr) {
    if(parent_node->left!=nullptr && parent_node->right!=nullptr) {
      if(parent_node->left->object.rating>=parent_node->right->object.rating) {
        child_node=parent_node->left;
      }
      else {
        child_node=parent_node->right;
      }
    }
    else if(parent_node->left!=nullptr) {
      child_node=parent_node->left;
    }
    else if(parent_node->right!=nullptr) {
      child_node=parent_node->right;
    }
    parent_node->object=child_node->object;
    parent_node=child_node;
  }
  if(parent_node==nullptr) {
    return;
  }
  if(parent_node==root) {
    root=nullptr;
    size=0;
    return;
  }
  
  if(cur_node->left==nullptr) {
    get_old_cur_node();
    parent_node->object=cur_node->right->object;
    cur_node->right=nullptr;
  }
  else if(cur_node->right==nullptr) {
    parent_node->object=cur_node->left->object;
    cur_node->left=nullptr;
  }
  size-=1;

  return;
}

template<typename T>
void Heap<T>::printHeap(TreeNode<T> *node) {
  printHeapHelper(node, " ", true);
  return;
}

template<typename T>
void Heap<T>::printHeapHelper(TreeNode<T> *root, string prefix, bool isLeft)
{
  if( root != nullptr )   {
    cout << prefix;
    
    cout << (isLeft ? "|--" : "|__" );
    
    std::cout<<root->object.rating;
    cout << endl;
    TreeNode<T>* curr = root;
    root = root->left;
    printHeapHelper(root, prefix + (isLeft ? "│   " : "    "), true);
    root = curr->right;
    printHeapHelper(root, prefix + (isLeft ? "│   " : "    "), false);
    root = curr;
  }
}
