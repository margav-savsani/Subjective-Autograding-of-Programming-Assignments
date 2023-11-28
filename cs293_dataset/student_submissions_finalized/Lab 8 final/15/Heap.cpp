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
        dummy = dummy / 2;
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
        curr->right->parent = curr;
        curr = curr->right;
    }
    else
    {
        curr->left = new TreeNode<T>(obj);
        curr->left->parent = curr;
        curr = curr->left;
    }

    while (curr->parent != nullptr && curr->parent->object < curr->object)
    {
        swap(curr->object, curr->parent->object);
        curr = curr->parent;
    }
    return;
}

template <typename T>
void Heap<T>::delMax()
{
    if (number_of_elements == 1)
    {
        number_of_elements--;
        root = nullptr;
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

    if (curr->parent->left == curr)
    {
        curr->parent->left = nullptr;
    }
    if (curr->parent->right == curr)
    {
        curr->parent->right = nullptr;
    }
    delete (curr);
    number_of_elements--;
    Heapify(root);
    return;
}

template <typename T>
void Heap<T>::printHeap(TreeNode<T> *node)
{
    static bool isLeft = false;
    static string prefix = "";

    if (node != nullptr)
    {
        cout << prefix;
        cout << (isLeft ? "|--" : "|__");
        cout << node->object << endl;
        string prev=prefix;
        bool prev_l=isLeft;
        prefix+="|   ";
        isLeft=true;
        printHeap(node->left);
        isLeft=false;
        prefix=prev+"    ";
        printHeap(node->right);
        prefix=prev;
        isLeft=prev_l;
    }
}

template <typename T>
void Heap<T>::Heapify(TreeNode<T> *node)
{

    if (node == nullptr)
    {
        return;
    }
    TreeNode<T> *exchange = node;

    if (node->left != nullptr && node->object < node->left->object)
    {
        exchange = node->left;
    }
    if (node->right != nullptr && exchange->object < node->right->object)
    {
        exchange = node->right;
    }
    if (exchange != node)
    {
        swap(exchange->object, node->object);
        Heapify(exchange);
    }
    return;
}

// template <typename T>
// void Heap<T>::print_tree_structure(TreeNode<T> *r, const string &prefix, bool isLeft)
// {
//     if (r != nullptr)
//     {
//         cout << prefix;
//         cout << (isLeft ? "|--" : "|__");
//         cout<<r->object<<endl;
//         print_tree_structure(r->left, prefix + (isLeft ? "│   " : "    "), true);
//         print_tree_structure(r->right, prefix + (isLeft ? "│   " : "    "), false);
//     }
// }