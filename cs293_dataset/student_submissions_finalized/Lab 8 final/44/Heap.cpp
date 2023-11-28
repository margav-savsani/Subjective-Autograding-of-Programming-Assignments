#include <cmath>

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef HEAP_H
#include "Heap.h"
#endif

template<typename T>
void Heap<T>::insert(T obj) {
  int M = N+1; //the node to be added is Mth node.
  // insert your code here
  int no_of_digits = 1+floor(log2(M)); // number of digits in binary representaion of M. 
  int array[no_of_digits-1] ;
  int trailing_M=0;
  TreeNode<T> * currNode = root;
  TreeNode<T> * trailing_pointer = nullptr;
  if(currNode == nullptr){
    TreeNode<T> * newNode = new TreeNode<T>(obj);
    currNode = newNode;
    root = currNode;
  }
  else{
    int K = M;
    for(int i = no_of_digits-2; i>=0; i--){
      array[i] = K%2;
      K=K/2;
    }
    for(int i = 0; i < no_of_digits-1; i++){
      trailing_pointer=currNode;
      if(array[i]==0) currNode=currNode->left;
      else if(array[i]==1) currNode=currNode->right;
      if(currNode==nullptr) break;
    }
      TreeNode<T>* newNode = new TreeNode<T>(obj);
      currNode = newNode;
  }
  
  currNode->parent=trailing_pointer;
  if(trailing_pointer!=nullptr){
    if(array[no_of_digits-2]==0) trailing_pointer->left = currNode;
    else trailing_pointer->right = currNode;
  }

  //now currNode is not nullptr , and trailing pointer may or may not be nullptr, depending on whether currNode is a root or not
  if(currNode->parent == nullptr) {;} //trailing pointer is null pointer
  else {
    while(trailing_pointer!=nullptr){
      if(trailing_pointer->object < currNode->object){
        T temp = currNode->object;
        currNode->object = trailing_pointer->object;
        trailing_pointer->object = temp;
        currNode = trailing_pointer;
        trailing_pointer = trailing_pointer->parent;
      }
      else if(currNode->object < trailing_pointer->object) break;
    }
    if(trailing_pointer==nullptr) root = currNode;

  }
  N++;
}

template<typename T>
void Heap<T>::delMax() {
  TreeNode<T> * currNode = root;
  TreeNode<T> * trailing_pointer = nullptr;
  int M = N; //no. of nodes in the heap currently
  int no_of_digits = 1 + floor(log2(N));
  int array[no_of_digits-1];
  for(int i = no_of_digits-2; i >=0; i--){
    array[i] = M%2;
    M = M/2;
  }
  for(int i = 0; i <= no_of_digits-2; i++){
    if(array[i]==1) {
        trailing_pointer = currNode;
        currNode = currNode->right;
    }
    else if(array[i]==0) {
        trailing_pointer = currNode;
        currNode = currNode->left;
    }
  }
  root->object = currNode->object;
  if(trailing_pointer!=nullptr){
      if(currNode == trailing_pointer->right) trailing_pointer->right = nullptr;
      else if(currNode == trailing_pointer->left) trailing_pointer->left = nullptr;
  }
  delete currNode;
  currNode = nullptr;
  N--;
//   printBST("", false);
  TreeNode<T> * heapify_root_node = root;
  // if(heapify_root_node == nullptr) {;}
    while(heapify_root_node! =nullptr){
        if(heapify_root_node->left==nullptr) break;
        else if(heapify_root_node->right == nullptr && heapify_root_node->left->object<heapify_root_node->object) break;
        else if(heapify_root_node->right!=nullptr && heapify_root_node->left->object < heapify_root_node->object && heapify_root_node->right->object < heapify_root_node->object) break;
        if(heapify_root_node->left!=nullptr && heapify_root_node->right!=nullptr &&  heapify_root_node->right->object < heapify_root_node->left->object){
            T temp = heapify_root_node->object;
            heapify_root_node->object = heapify_root_node->left->object;
            heapify_root_node->left->object = temp;
            heapify_root_node = heapify_root_node->left;
        }
        else if(heapify_root_node->left!=nullptr && heapify_root_node->right!=nullptr && heapify_root_node->left->object < heapify_root_node->right->object){
            T temp = heapify_root_node->object;
            heapify_root_node->object = heapify_root_node->right->object;
            heapify_root_node->right->object = temp;
            heapify_root_node = heapify_root_node->right;
        }
        else if(heapify_root_node->left!=nullptr && heapify_root_node->right==nullptr && heapify_root_node->object < heapify_root_node->left->object){
            T temp = heapify_root_node->object;
            heapify_root_node->object = heapify_root_node->left->object;
            heapify_root_node->left->object = temp;
            heapify_root_node = heapify_root_node->left;
        }
    }
  return;
}

template<typename T>
void Heap<T>::printBST(const string& prefix, bool isLeft, TreeNode<T> *node){
    if( node != nullptr )
    {
        cout << prefix;

        cout << (isLeft ? "|--" : "|__" );

        // print the value of the node
        cout << node->object << endl;
        TreeNode<T> *curr = node;
        node = node->left;
        // enter the next tree level - left and right branch
        printBST( prefix + (isLeft ? "│   " : "    "), true, node);
        node = curr->right;
        printBST( prefix + (isLeft ? "│   " : "    "), false, node);
        node = curr;
    }
}

template<typename T>
void Heap<T>::printHeap(TreeNode<T> *node) {
  printBST("", false, node);
}

  
