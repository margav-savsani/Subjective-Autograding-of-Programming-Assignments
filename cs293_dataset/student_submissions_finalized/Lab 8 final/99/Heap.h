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
    ~TreeNode() {;}
};

template <typename T> class Heap {
    TreeNode<T> *root;
    TreeNode<T> *last;
 public:
    Heap() {root = nullptr; last = nullptr; }
    ~Heap() {recursiveDelete(root);}

    TreeNode<T> * next(TreeNode<T> * currNode);
    TreeNode<T> * prev(TreeNode<T> * currNode);
    void insert(T obj);
    void delMax();
    T getMax() 
    {
        if (root == nullptr) return T();
        return root->object; // insert your own code here if needed
    }
    void printHeap(TreeNode<T> *node);
    // void printHeap(TreeNode<T> *node);
    // void displayAboveThresh(int thresh);
    void recursiveDelete(TreeNode<T> * node);
};

#endif