#ifndef HEAP_H
#define HEAP_H

#ifndef STD_HEADERS
#include "std_headers.h"
#endif

#include<cmath>
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

  void printInfo()
  {
    cout << object;
  }
};

template <typename T> class Heap {
 public:
  TreeNode<T> *root;     
  //root was initially given as private variable
  TreeNode<T>* last;
  int currLvl;
  int n; 
  Heap() {
    root = nullptr;
    n = 0; //number of elements in heap
    currLvl = -1;
  }
  ~Heap() {;}
  void swap_obj(T &obj1, T &obj2);
  void heapify(TreeNode<T>* currNode);
  void insert(T obj);
  void delMax();
  T getMax() {
    
      return root->object; // insert your own code here if needed
    // else{
    //   // TreeNode<T> *node = new TreeNode<T>()
    // }
  }
  void printHeap(TreeNode<T> *node);
  //  void displayAboveThresh(int thresh);

  
};
template<typename T>
void printBinaryTree(TreeNode<T> *start, const string& prefix, bool isLeft)
{
  if( start != nullptr )   {
    cout << prefix;
    
    cout << (isLeft ? "|--" : "|__" );
    
    // print the value of the nodestart->printinfo();
    start->printInfo();
    cout << endl;
    TreeNode<T> *curr = start;
    start = start->left;
    // enter the next tree level - left and right branch
    printBinaryTree(start, prefix + (isLeft ? "│   " : "    "), true);
    start = curr->right;
    printBinaryTree(start, prefix + (isLeft ? "│   " : "    "), false);
    start = curr;
  }
  
  else {
    // cout << "NULL tree" << endl;
  }
}
#endif

