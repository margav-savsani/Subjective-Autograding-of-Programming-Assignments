#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef HEAP_H
#include "Heap.h"
#endif

template <typename T>
void Heap<T>::insert(T obj)
{
    // insert your code here
    TreeNode<T> *node = root;
    if (node == nullptr)
    {
        node = new TreeNode(obj);
    }
    else
    {
        while(obj <= node->object)
        {
            
        }
    }


    return;
}

template <typename T>
void Heap<T>::delMax()
{

    // insert your code here

    return;
}

template <typename T>
void Heap<T>::printHeap(TreeNode<T> *node)
{

    // insert your code here

    return;
}
