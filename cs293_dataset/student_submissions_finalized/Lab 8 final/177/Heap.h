#ifndef HEAP_H
#define HEAP_H

#ifndef STD_HEADERS
#include "std_headers.h"
#endif

using namespace std;

template <typename T> class TreeNode {
 public:
  T object;
  TreeNode<T>* left;
  TreeNode<T>* right;
  TreeNode<T>* parent;

  TreeNode(T initObj) {
    object = initObj;
    left = right = parent = nullptr;
  }

  bool operator < (TreeNode<T> object_2){
    return object < object_2.object;
  }

  void rec_delete(){
    if (left != nullptr) left -> rec_delete();
    if (right != nullptr) right -> rec_delete();
    delete(this);
  }

  ~TreeNode(){;}
};

template <typename T> class Heap{
  TreeNode<T>* root;
  int size = 0;

 public:
  Heap() {root = nullptr;}
  Heap(TreeNode<T>* node) {root = node; node -> parent = nullptr; size = 1;}
  ~Heap() {if (root != nullptr) root -> rec_delete();}

  T getMax() {return root -> object;}
  void insert(T obj);
  void delMax();
  void printHeap(TreeNode<T>* node);
  void heapify(TreeNode<T>* node);

  TreeNode<T>* get_root() {return root;}
  int get_size() {return size;}
};

#endif

