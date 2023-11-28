if (n != M){
            H[n] = val;
            int i = n;
            n += 1;
            while ((i != 0) && (H[parent(i)] > H[i])){
                int p=H[i];
                H[i]=H[parent(i)];
                H[parent(i)]=p;
                i = parent(i);
            }#ifndef HEAP_H
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
  ~TreeNode() {;}
};

template <typename T> class Heap {
  TreeNode<T> *root;

 public:
  Heap() {root = nullptr;}
  ~Heap() {;}

  void insert(T obj);
  void delMax();
  T getMax() {return root->object; // insert your own code here if needed
  }
  TreeNode<T> *find(int l,TreeNode<T> *node,TreeNode<T> *prev)
  void printHeap(TreeNode<T> *node);
  void Heapify(TreeNode<T> *node)
  //  void displayAboveThresh(int thresh);
};

#endif

