#ifndef HEAP_H
#define HEAP_H

#ifndef STD_HEADERS
#include "std_headers.h"
#endif

using namespace std;

template <typename T> class TreeNode {
 public:
  T object;
  int height ;
  TreeNode<T> *left;
  TreeNode<T> *right;
  TreeNode<T> *parent;

  TreeNode(T initObj) {
    object = initObj;
    height = 0 ;
    left = right = parent = nullptr;
  }
  ~TreeNode() {;}
};

template <typename T> class Heap {
  TreeNode<T> *root;
  int num_levels ;
  int free_index ;
  TreeNode<T> *last_node ;
 public:
  Heap() {root = nullptr;last_node=nullptr;}
  ~Heap() {;}
  void swap(TreeNode<T>* a , TreeNode<T>* b);
  TreeNode<T>* findlast_insert();
  int getheight(TreeNode<T> *currnode);
  void insert(T obj);
  void Heapify_down(TreeNode<T> *currNode);
  void Heapify_up(TreeNode<T> *currNode);
  void delMax();
  T getMax() {
    return root->object; // insert your own code here if needed
  }
  //void printHeap(TreeNode<T> *node);
  void print_heap(const string& prefix, bool isLeft=false){
    if( root != nullptr ){
      cout << prefix;
      cout << (isLeft ? "|--" : "|__" );
      //root->printInfo();
      cout <<root->object;
      cout<<endl;
      TreeNode<T> *curr = root;
      root = root->left;
      // enter the next tree num_levels - left and right branch
      print_heap( prefix + (isLeft ? "│   " : "    "), true);
      root = curr->right;
      print_heap( prefix + (isLeft ? "│   " : "    "), false);
      root = curr;
  }
  else {
    cout << "NULL tree" << endl;
  }
  return;
  }
  void printHeap(TreeNode<T> *node);
  //  void displayAboveThresh(int thresh);
};

#endif

