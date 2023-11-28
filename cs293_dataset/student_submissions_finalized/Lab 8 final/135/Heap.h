#ifndef HEAP_H
#define HEAP_H

#ifndef STD_HEADERS
#include "std_headers.h"
#endif

using namespace std;

template <typename T> class TreeNode {
 public:
  T object;
  TreeNode<T> *left;
  TreeNode<T> *right;
  TreeNode<T> *parent;

  TreeNode(T initObj) {
    object = initObj;
    left = right = parent = nullptr;
  }
  ~TreeNode() {
    if(left != nullptr) ~left();
    if(right != nullptr) ~right();
  }
};

template <typename T> class Heap {
  TreeNode<T> *root;
  int numberOfNodes;

  int binary(int n){
    int b=0;
    while(n>0){
      int r = n%2;
      b = b*10 + r;
      n = n/2;
    }
    return b;
  }

  void heapify(TreeNode<T>* node){
    if(node == nullptr) return;
    if(node->left == nullptr) return;
    if(node->right == nullptr){
      if(node->object < node->left->object){
        T temp = node->object;
        node->object = node->left->object;
        node->left->object = temp;
      }
      return;
    }

    if(!(node->left->object < node->right->object)){
      if(node->object < node->left->object){
        T temp = node->object;
        node->object = node->left->object;
        node->left->object = temp;
        heapify(node->left);
      }
      return;
    }
    if(!(node->right->object < node->left->object)){
      if(node->object < node->right->object){
        T temp = node->object;
        node->object = node->right->object;
        node->right->object = temp;
        heapify(node->right);
      }
      return;
    }
  }

  void printTree(const string& prefix, bool isLeft=false);

 public:
  Heap() {
    root = nullptr;
    numberOfNodes = 0;
  }
  ~Heap() {;}

  void insert(T obj);
  void delMax();
  T getMax() {
    if(root == nullptr) return *(new T);
    return root->object; // insert your own code here if needed
  }
  void printHeap(TreeNode<T> *node);
  //  void displayAboveThresh(int thresh);
};

#endif

