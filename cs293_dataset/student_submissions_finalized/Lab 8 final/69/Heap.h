#ifndef HEAP_H
#define HEAP_H

#ifndef STD_HEADERS
#include "std_headers.h"
#endif

using namespace std;

template <typename T>
class TreeNode
{
public:
    T object;
    TreeNode<T> *left;
    TreeNode<T> *right;
    TreeNode<T> *parent;

    int lchilds;
    int rchilds;
    int height;
    int childs = lchilds + rchilds;

    TreeNode(T initObj)
    {
        object = initObj;
        left = right = parent = nullptr;
        lchilds = rchilds = height = childs = 0;
    }
    ~TreeNode() { ; }
};

template <typename T>
class Heap
{
    TreeNode<T> *root;


public:
    Heap() { root = nullptr;}
    ~Heap() { ; }

    void insert(T obj);
    void delMax();
    T getMax()
    {
        return root->object; // insert your own code here if needed
    }
    void printHeap(TreeNode<T> *node);
    //  void displayAboveThresh(int thresh);

    void swap(TreeNode<T> *n1, TreeNode<T> *n2);
    TreeNode<T>* ins_last(TreeNode<T> *n);
    TreeNode<T>* del_last(TreeNode<T> *n);
};

#endif
