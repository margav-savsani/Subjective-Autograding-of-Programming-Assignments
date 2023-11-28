#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef HEAP_H
#include "Heap.h"
#endif

template<typename T>
TreeNode<T> * Heap<T>::rightOf(TreeNode<T> * currNode)
{
    //---------------------------don't allow-----------------------------
    if (currNode == nullptr) return nullptr;
    if (currNode->parent == nullptr) return nullptr;
    //-------------------------------------------------------------------
    if (currNode = currNode->parent->left) return currNode->parent->right;
    TreeNode<T> * next_p = rightOf(currNode->parent);
    if (next_p == nullptr) return nullptr;
    else return next_p->left;
}

template<typename T>
void Heap<T>::insert(T obj)
{
    // insert your code here
    TreeNode<T> * start = root;
    if (root == nullptr)
    {
        root = new TreeNode(obj);
        return;
    }
    bool inserted = 0;
    TreeNode<T> * x = new TreeNode(obj);
    while (!inserted)
    {
        // start is the second last level
        if (start->left == nullptr) 
        {
            x->parent = start;
            start->left = x;
            inserted = 1;
        }
        else if (start->right == nullptr) 
        {
            x->parent = start;
            start->right = x;
            inserted = 1;
        }
        TreeNode * next = rightOf(start);
        start = next;
        if (start == nullptr)
        {
            start = root;
            while (start->left != nullptr) start = start->left;
            x->parent = start;
            start->left = x;
            inserted = 1;
        }
        else
        {
            x->parent = start;
            start->left = x;
            inserted = 1;
        }
    }
    if (T < start->object) return;
    while (start != nullptr && start->object < x->object)
    {
        int s_rate = (start->object).rating;
        int s_id = (start->object).revId;
        string s_rev = (start->object).rev;
        (start->object).rating = (x->object).rating;
        (start->object).revId = (x->object).revId;
        (start->object).rev = (x->object).rev;
        (x->object).rating = s_rate;
        (x->object).revId = s_id;
        (x->object).rev = s_rev;

        start = start->parent;
        x = start;
    }
    return;
}

template<typename T>
void Heap<T>::delMax()
{

    // insert your code here

    return;
}

template<typename T>
void Heap<T>::printHeap(TreeNode<T> *node)
{

    // insert your code here

    return;
}
d
