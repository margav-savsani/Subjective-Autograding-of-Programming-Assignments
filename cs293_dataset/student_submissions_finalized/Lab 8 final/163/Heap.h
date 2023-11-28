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

    TreeNode(T initObj)
    {
        object = initObj;
        left = right = parent = nullptr;
    }
    ~TreeNode()
    { // deallocated memory given to left and right subtrees before deleting given node
        // if (left != nullptr)
        //     left->~TreeNode();
        // if (right != nullptr)
        //     right->~TreeNode();
    }
};

template <typename T>
class Heap
{
    TreeNode<T> *root;
    int numOfNodes;

public:
    Heap()
    {
        root = nullptr;
        numOfNodes = 0;
    }
    ~Heap()
    { // deallocates the memory given to the tree
        if (root != nullptr)
            root->~TreeNode();
    }

    void insert(T obj);
    void delMax();
    void Heapify(TreeNode<T> *node);
    T getMax()
    {
        return root->object; // insert your own code here if needed
    }
    void printHeap(TreeNode<T> *node);
    //  void displayAboveThresh(int thresh);
};

#endif
