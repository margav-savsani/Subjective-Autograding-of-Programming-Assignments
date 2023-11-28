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
    if (root == nullptr)
    {
        root = new TreeNode<T>(obj);
        numOfNodes++;
        return;
    }
    int insertPosition = numOfNodes + 1;
    string binary;
    while (insertPosition > 0)
    {
        binary = to_string(insertPosition % 2) + binary;
        insertPosition = insertPosition / 2;
    }
    TreeNode<T> *temp = root;
    for (int i = 1; i < binary.size() - 1; i++)
    {
        if (binary[i] == '0')
            temp = temp->left;
        else
            temp = temp->right;
    }
    if (binary[binary.size() - 1] == '0')
    {
        temp->left = new TreeNode<T>(obj);
        temp = temp->left;
    }
    else
    {
        temp->right = new TreeNode<T>(obj);
        temp = temp->right;
    }
    while (temp->parent != nullptr)
    {
        if (temp->object > temp->parent->object)
        {
            T t = temp->object;
            temp->object = temp->parent->object;
            temp->parent->object = t;
            temp = temp->parent;
        }
        else
        {
            break;
        }
    }

    numOfNodes++;
    return;
}

template <typename T>
void Heap<T>::delMax()
{
    // insert your code here
    int deletePosition = numOfNodes;
    string binary;
    while (deletePosition > 0)
    {
        binary = to_string(deletePosition % 2) + binary;
        deletePosition = deletePosition / 2;
    }
    TreeNode<T> *temp = root;
    for (int i = 1; i < binary.size() - 1; i++)
    {
        if (binary[i] == '0')
            temp = temp->left;
        else
            temp = temp->right;
    }
    if (binary[binary.size() - 1] == '0')
    {
        root->object = temp->left->object;
        temp->left = nullptr;
    }
    else
    {
        root->object = temp->right->object;
        temp->right = nullptr;
    }
    Heapify(root);

    numOfNodes--;
    return;
}

template <typename T>
void Heap<T>::Heapify(TreeNode<T> *node)
{
    TreeNode<T> *t;
    if (node->object > node->left->object && node->object > node->right->object)
        return;
    else if (node->object < node->left->object && node->object > node->right->object)
        t = node->left;
    else if (node->object > node->left->object && node->object < node->right->object)
        t = node->right;
    else if (node->left->object > node->right->object)
        t = node->left;
    else
        t = node->right;
    T t_obj = t->object;
    t->object = node->object;
    node->object = t_obj;
    Heapify(t);
}

template <typename T>
void Heap<T>::printHeap(TreeNode<T> *node)
{

    // insert your code here

    return;
}
