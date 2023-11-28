#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef HEAP_H
#include "Heap.h"
#endif

// swaps elements of two nodes
template<typename T>
void Heap<T>::swap(TreeNode<T> *first, TreeNode<T> *second) {
  T temp = second->object;
  second->object = first->object;
  first->object = temp;
}

// insert element into heap
template<typename T>
void Heap<T>::insert(T obj) {
  if(root == nullptr){
    root = new TreeNode<T>(obj);
    n=1;
  }
  else{
    n++;

    // traverse the heap using bit representation of number of nodes currently in heap
    int max_pow_two=0;
    while(n>>(max_pow_two+1) > 0){
      max_pow_two++;
    }
    TreeNode<T> *prev=nullptr, *curr=root;
    for(int i=max_pow_two-1; i>=0; i--){
      prev = curr;
      if((n>>i)%2){
        curr = curr->right;
      }
      else{
        curr = curr->left;
      }
    }

    // inserting into correct position and updating pointers to relevant nodes
    if(n % 2){
      prev->right = new TreeNode<T>(obj);
      curr = prev->right;
      curr->parent = prev;
    }
    else{
      prev->left = new TreeNode<T>(obj);
      curr = prev->left;
      curr->parent = prev;
    }
    
    // swapping objects until new object is inserted into correct position
    while(prev != nullptr){
      if(prev->object < obj){
        swap(prev,curr);
      }
      else break;
      curr = prev;
      prev = prev->parent;
    }
  }
}

// delete maximum element (Root) from heap
template<typename T>
void Heap<T>::delMax() {
  if(root == nullptr) return;
  TreeNode<T> max = root->object;
  if(n==1){
    n = 0;
    delete root;
    root = nullptr;
  }
  else{
    // traversing to element to be deleted
    int pos=n;
    int max_pow_two=0;
    while(n>>(max_pow_two+1) > 0){
      max_pow_two++;
    }
    TreeNode<T> *prev=nullptr, *curr=root;
    for(int i=max_pow_two-1; i>=0; i--){
      prev = curr;
      if((n>>i)%2){
        curr = curr->right;
      }
      else{
        curr = curr->left;
      }
    }
    // transferring node object to root of heap
    root->object = curr->object;

    // deleting last node and resetting some pointers
    delete curr;
    curr = nullptr;
    if(n % 2){
      prev->right = nullptr;
    }
    else prev->left = nullptr;
    n--;

    // placing the object at root node in its correct position within the heap
    heapify(root);
  }
  return;
}

// recursively places the object at root node in its correct position within the heap
template<typename T>
void Heap<T>::heapify(TreeNode<T> *node) {
  if(node == nullptr) return;
  if(node->left == nullptr) return;
  else if(node->right == nullptr){
    if(node->object < node->left->object){
      T obj = node->object;
      node->object = node->left->object;
      node->left->object = obj;
      heapify(node->left);
    }
  }
  else{
    if(node->object < node->left->object && node->object < node->right->object){
      if(node->left->object < node->right->object){
        T obj = node->object;
        node->object = node->right->object;
        node->right->object = obj;
        heapify(node->right);
      }
      else{
        T obj = node->object;
        node->object = node->left->object;
        node->left->object = obj;
        heapify(node->left);
      }
    }
    else if(node->object < node->left->object){
      T obj = node->object;
      node->object = node->left->object;
      node->left->object = obj;
      heapify(node->left);
    }
    else if(node->object < node->right->object){
      T obj = node->object;
      node->object = node->right->object;
      node->right->object = obj;
      heapify(node->right);
    }
  }
}

// utilizes the printbinarytree function used to print trees in previous labs
template<typename T>
void Heap<T>::printHeap(TreeNode<T> *node) {
  printBinaryTree(node, "", 1);
  return;
}

template<typename T>
void Heap<T>::printBinaryTree(TreeNode<T> *root, const string& prefix, bool isLeft)
{
  if( root != nullptr )   {
    cout << prefix;
    
    cout << (isLeft ? "|--" : "|__" );
    
    // print the value of the node
    cout<<(root->object);
    cout << endl;
    TreeNode<T> *curr = root;
    root = root->left;
    // enter the next tree level - left and right branch
    printBinaryTree(root, prefix + (isLeft ? "│   " : "    "), true);
    root = curr->right;
    printBinaryTree(root, prefix + (isLeft ? "│   " : "    "), false);
    root = curr;
  }
  /*
  else {
    cout << "NULL tree" << endl;
  }
  */
}
  
