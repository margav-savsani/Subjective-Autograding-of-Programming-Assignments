#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef HEAP_H
#include "Heap.h"
#endif

template<typename T>
void myswap(TreeNode<T> *a, TreeNode<T> *b){
  T temp = a->object;
  a->object = b->object;
  b->object = temp;
  return;
}

template<typename T>
void heapify(TreeNode<T> *node){
  if(node->left == nullptr && node->right == nullptr) return;
  if(node->left != nullptr && node->right == nullptr){
    if(node->object < node->left->object){
      myswap(node->left, node);
      heapify(node->left);
      return;
    }
  }
  if(node->right != nullptr && node->left != nullptr){
    if(node->right->object < node->left->object && node->object < node->left->object){
      myswap(node, node->left);
      heapify(node->left);
      return;
    }
    if(node->left->object < node->right->object && node->object < node->right->object){
      myswap(node, node->right);
      heapify(node->right);
      return;
    }
  }
}

template<typename T>
void Heap<T>::insert(T obj) {
  // insert your code here
  TreeNode<T> *ins;
  ins = new TreeNode<T>(obj);
  if(root == nullptr){
    root = ins;
    last = ins;
    return;
  }
  TreeNode<T> *curr = root;
  while(curr != nullptr){
    if(curr == last){
      curr = root;
      while(curr->left != nullptr){
        curr = curr->left;
      }
      curr->left = ins;
      ins->parent = curr;
      last = curr->left;
      curr = last;
      while(curr->parent->object < curr->object){
        myswap(curr, curr->parent);
        curr = curr->parent;
        if(curr == root) break;
      }
      return;
    }
    curr = curr->right;
  }
  curr = last;
  if(curr->parent->left == curr){
    curr->parent->right = ins;
    ins->parent = curr->parent;
    last = curr->parent->right;
    curr = last;
    while(curr->parent->object < curr->object){
      myswap(curr, curr->parent);
      curr = curr->parent;
      if(curr == root) break;
    }
    return;
  }
  while(curr->parent->right == curr){
    curr = curr->parent;
  }
  curr = curr->parent->right;
  while(curr->left != nullptr){
    curr = curr->left;
  }
  curr->left = ins;
  ins->parent = curr;
  last = curr->left;
  curr = last;
  while(curr->parent->object < curr->object){
    myswap(curr, curr->parent);
    curr = curr->parent;
    if(curr == root) break;
  }
  return;
}

template<typename T>
void Heap<T>::delMax() {
  // insert your code here
  if(root == nullptr) return;
  TreeNode<T> *del = last;
  if(root == last){
    root = nullptr;
    last = nullptr;
    delete del;
    return;
  }
  myswap(root, last);

  TreeNode<T> *p = last->parent;
  if(last->parent->left == last){
    if(p == root){
      last = root;
      delete del;
      return;
    }
    last->parent->left = nullptr;
    while(p->parent->left == p){
      p = p->parent;
      if(p == root){
        while(p->right != nullptr) p = p->right;
        last = p;
        delete del;
        heapify(root);
        return;
      }
    }
    p = p->parent->left;
    while(p->right != nullptr) p = p->right;
        last = p;
        delete del;
        heapify(root);
        return;
  }
  if(last->parent->right == last){
    last->parent->right = nullptr;
    last = p->left;
  }
  delete del;
  heapify(root);
}

template<typename T>
void Heap<T>::printHeap(TreeNode<T> *node, const string& prefix, bool isLeft) {

  // insert your code here
  if( node != nullptr )
    {
        cout << prefix;

        cout << (isLeft ? "|--" : "|__" );

        // print the value of the node
        cout << node->object<< endl;
        TreeNode<T> *curr = node;
        node = node->left;
        // enter the next tree level - left and right branch
        printHeap(node, prefix + (isLeft ? "│   " : "    "), true);
        node = curr->right;
        printHeap(node, prefix + (isLeft ? "│   " : "    "), false);
        node = curr;
    }
  return;
}

  
