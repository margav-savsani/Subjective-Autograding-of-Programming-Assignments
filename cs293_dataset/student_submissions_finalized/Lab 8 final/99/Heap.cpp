#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef HEAP_H
#include "Heap.h"
#endif


template<typename T>
TreeNode<T> * Heap<T>::next(TreeNode<T> * currNode)
{
    if (currNode == nullptr) return nullptr;
    if (currNode->parent == nullptr) return currNode->left;
    if (currNode == currNode->parent->left) return currNode->parent->right;
    TreeNode<T> * next_p = next(currNode->parent);
    return next_p->left;
    
}
template<typename T>
TreeNode<T> * Heap<T>::prev(TreeNode<T> * currNode)
{
    if (currNode == nullptr) return nullptr;
    if (currNode->parent == nullptr) return nullptr;
    if (currNode == currNode->parent->right) return currNode->parent->left;
    TreeNode<T> * prev_p = prev(currNode->parent);
    if (prev_p == nullptr) return currNode->parent;
    else return prev_p->right;
}

template<typename T>
void Heap<T>::insert(T obj)
{
  // insert your code here
    TreeNode<T> * start = root;
    if (root == nullptr)
    {
        root = new TreeNode<T>(obj);
        last = root;
        return;
    }
    bool inserted = 0;
    TreeNode<T> * x = new TreeNode<T>(obj);
    while (!inserted)
    {
        // start is the second last level
        if (start->left == nullptr) 
        {
            x->parent = start;
            start->left = x;
            last = x;
            inserted = 1;
            break;
        }
        else if (start->right == nullptr) 
        {
            x->parent = start;
            start->right = x;
            last = x;
            inserted = 1;
            break;
        }
        start = next(start);
    }
    if (x->object < start->object) return;
    while (start != nullptr && start->object < x->object)
    {
        T tmp;
        tmp = start->object;
        start->object = x->object;
        x->object = tmp;
        x = start;
        start = start->parent;
    }
    // printHeap(root);
    return;
}

template<typename T>
void Heap<T>::delMax()
{
    if (root == nullptr) return;

    root->object = last->object;

    TreeNode<T> * prnt = last->parent;
    TreeNode<T> * newLast = prev(last);
    if (prnt == nullptr) { root = nullptr; return; }
    if (last == prnt->left) prnt->left = nullptr;
    else prnt->right = nullptr;
    last = newLast;

    TreeNode<T> * start = root;
    bool heapified = 0;
    while (!heapified)
    {
        TreeNode<T> * x = nullptr;
        if (start->left == nullptr) { heapified = 1; break; }
        else if (start->right == nullptr) {x = start->left;}
        else
        {
            if (start->left->object < start->right->object) x = start->right;
            else x = start->left;
        }
        if (start->object < x->object)
        {
            T tmp;
            tmp = start->object;
            start->object = x->object;
            x->object = tmp;
            start = x;
        }
        else heapified = 1;
    }
    return;
}

template<typename T>
void Heap<T>::printHeap(TreeNode<T> *node)
{
    // insert your code here
    static int i = 0;
    static bool isLeft = false;
    static string prefix = "";
    if (node != nullptr)
    {
        if (i) 
        {
            cout << prefix;
            cout << (isLeft ? "|--" : "|__" );
        }
        // print the value of the node
        cout << node->object << endl;
        string x = prefix;
        if (i) prefix = prefix + (isLeft ? "│   " : "    ");
        i++;
        isLeft = true;
        printHeap(node->left);
        isLeft = false;
        printHeap(node->right);
        prefix = x;
        i--;
    }
    return;
}

template<typename T>
void Heap<T>::recursiveDelete(TreeNode<T> * node)
{
    if (node == nullptr) return;
    recursiveDelete(node->left);
    recursiveDelete(node->right);
    node->left = nullptr;
    node->right = nullptr;
    if (node != root) delete node;
}