#ifndef HEAP_H
#define HEAP_H

#ifndef STD_HEADERS
#include "std_headers.h"
#endif

template<typename T> class TreeNode {
  public:
    T object;
    TreeNode<T>* left;
    TreeNode<T>* right;
    TreeNode<T>* parent;

    TreeNode(T initObj);
    ~TreeNode();
};

template<typename T> std::ostream& operator<<(std::ostream& o, TreeNode<T> const& p);

template<typename T> class Heap {
    void cleanup(TreeNode<T>* subroot);
    static TreeNode<T>* successor_with_parent(TreeNode<T>* n);
    static TreeNode<T>* successor(TreeNode<T>* n);
  public:
    TreeNode<T>* root;
    
    void heapify();
    Heap();
    ~Heap();

    void insert(T obj);
    T delMax();
    T getMax();
    
    void printHeap(std::string const& prefix = "", bool isLeft = false);
    //  void displayAboveThresh(int thresh);
};
#endif
