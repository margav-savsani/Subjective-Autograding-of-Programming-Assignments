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

    TreeNode(T initObj)
        : object(initObj), left(nullptr), right(nullptr), parent(nullptr)
    {
    }
    ~TreeNode()
    {
    }
};

template<typename T> class Heap {
    TreeNode<T>* root;
    
    void heapify_bottom_up(TreeNode<T>* node);
    void heapify_top_down(TreeNode<T>* node);

    // Returns pointer to successor of n
    // If it does not exist it returns pointer to the node which would have been parent to the successor
    static TreeNode<T>* successor_with_parent(TreeNode<T>* n);

    // Returns pointer to successor of n
    // If it does not exist it returns nullptr
    static TreeNode<T>* successor(TreeNode<T>* n);

    // Swaps objects of n1 and n2
    static void swap(TreeNode<T>* n1, TreeNode<T>* n2);

    void printHeap(TreeNode<T>* node, std::string const& prefix, bool isLeft);
  public:
    Heap()
        : root(nullptr)
    {
    }
    ~Heap()
    {
        if (root != nullptr) {
            TreeNode<T>* temp = root;
            root = temp->left;
            this->~Heap();
            root = temp->right;
            this->~Heap();
            delete temp;
        }
    }

    void insert(T obj);
    void delMax();
    T getMax()
    {
        return root->object;
    }

    void printHeap(TreeNode<T>* node)
    {
        printHeap(node, "", false);
    }
    //  void displayAboveThresh(int thresh);
};
#endif
