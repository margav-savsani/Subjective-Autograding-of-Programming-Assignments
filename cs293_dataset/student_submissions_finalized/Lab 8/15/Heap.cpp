#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef HEAP_H
#include "Heap.h"
#endif

template <typename T>
void Heap<T>::insert(T obj)
{
    number_of_elements++;
    if (number_of_elements == 1)
    {
        root = new TreeNode<T>(obj);
        return;
    }

    int n_bits = 0, dummy = number_of_elements;

    while (dummy != 0)
    {
        n_bits++;
        dummy /= 2;
    }
    dummy = number_of_elements;
    bool directions[n_bits - 1];
    for (int i = n_bits - 2; i >= 0; i--)
    {
        directions[i] = dummy % 2;
        dummy = dummy / 2;
    }
    int i;
    TreeNode<T> *curr = root;
    for (i = 0; i < n_bits - 2; i++)
    {
        if (directions[i])
        {
            curr = curr->right;
        }
        else
        {
            curr = curr->left;
        }
    }
    if (directions[i])
    {
        curr->right = new TreeNode<T>(obj);
        cout << "R" << endl;
        curr->right->parent = curr;
        curr = curr->right;
    }
    else
    {
        curr->left = new TreeNode<T>(obj);
        cout << "L" << endl;
        curr->left->parent = curr;
        curr = curr->left;
    }
    // insert your code here

    while (curr->object < curr->parent->object && curr->parent != nullptr)
    {
        swap(curr->object, curr->parent->object);
        curr = curr->parent;
    }
    return;
}

template <typename T>
void Heap<T>::delMax()
{
    int n_bits = 0, dummy = number_of_elements;

    while (dummy != 0)
    {
        n_bits++ ;
        dummy /= 2;
    }
    dummy = number_of_elements;
    bool directions[n_bits - 1];
    for (int i = n_bits - 2; i >= 0; i--)
    {
        directions[i] = dummy % 2;
        dummy = dummy / 2;
    }
    int i;
    TreeNode<T> *curr = root;
    for (i = 0; i < n_bits - 1; i++)
    {
        if (directions[i])
        {
            curr = curr->right;
        }
        else
        {
            curr = curr->left;
        }
    }
    swap(root->object, curr->object);
    delete (curr);
    number_of_elements--;
    Heapify(root);
    // insert your code here

    return;
}

template <typename T>
void Heap<T>::printHeap(TreeNode<T> *node)
{
    if (node == nullptr)
        return;
    cout << node->object << endl;
    cout << " L " << endl;
    printHeap(node->left);
    cout << " R " << endl;
    printHeap(node->right);
    // insert your code here
    return;
}

template <typename T>
void Heap<T>::Heapify(TreeNode<T> *node)
{
    TreeNode<T> *exchange = nullptr;

    if (node->left != nullptr && node->object < node->left->object  )
    {
        exchange = node->left;
    }
    if (node->right != nullptr &&  exchange->object < node->right->object)
    {
        exchange = node->right;
    }
    if (exchange != nullptr)
    {
        swap(exchange->object, node->object);
        Heapify(exchange);
    }
}
