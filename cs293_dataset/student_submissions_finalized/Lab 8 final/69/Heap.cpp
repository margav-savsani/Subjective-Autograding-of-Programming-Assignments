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
    TreeNode<T> *n = new TreeNode<T>(obj);
    if (root == nullptr)
    {
        root = n;
    }
    else
    {
        TreeNode<T> *p = ins_last();
        TreeNode<T> *q = p;

        // inserting in sub-tree
        if (p->left == nullptr)
        {
            p->left = n;
        }
        else
        {
            p->right = n;
        }

        // updating the number of nodes for a particular subtree
        while (q->parent != nullptr)
        {
            q->nodes++;
            q = q->parent;
        }

        // updating the heights
        if (n->parent != nullptr)
        {
            TreeNode<T> *r = n->parent;
            while (r != nullptr)
            {
                if (r->left == nullptr)
                {
                    r->height = max(0, r->right->height) + 1;
                }
                else if (r->right == nullptr)
                {
                    r->height = max(r->left->height, 0) + 1;
                }
                else
                {
                    r->height = max(r->left->height, r->right->height) + 1;
                }
                r = r->parent;
            }
        }
    }
}


template <typename T>
void Heap<T>::delMax()
{

    // insert your code here

    // obtaining the right most element fo the heap
    TreeNode<T> *rg = del_last(root);

    // replacing it with the top
    swap(rg, root);

    // deleting the right most node
    rg->parent->nodes--;
    rg = nullptr;

    // rearranging heap with respect to ratings of the object
    TreeNode<T> *r = root;
    while (r->object->rating < r->left->object->rating && r.rating < r->right->object->rating)
    {
        // if left child has more review then it will be swapped
        if (r->left->object->rating > r->right->object->rating)
        {
            swap(r, r->left);
            r = r->left;
        }
        // otherwise right child will be swapped
        else
        {
            swap(r, r->right);
            r = r->right;
        }
    }
}


template <typename T>
void Heap<T>::printHeap(TreeNode<T> *node)
{

    // insert your code here

    return;
}


template <typename T>
void Heap<T>::swap(TreeNode<T> *n1, TreeNode<T> *n2)
{
    // creating new object and copying the elements into it.
    T n = new T();
    n = n1->object;
    n1->object = n2->object;
    n2->object = n;
}


template <typename T>
TreeNode<T> *Heap<T>::del_last()
{
    // returns pointer to the last element inserted
    TreeNode<T> *n = root;
    while (n->left != nullptr && n->right != nullptr)
    {
        if (n->childs + 2 <= 3 * (2 ^ n->height))
        {
            n = n->left;
        }
        if (n->childs + 2 > 3 * (2 ^ n->height))
        {
            n = n->right;
        }
    }
    if (n->left == nullptr)
    {
        return n;
    }
    if (n->right == nullptr)
    {
        return n->left;
    }
}


template <typename T>
TreeNode<T> *Heap<T>::ins_last()
{
    TreeNode<T> *n = root;
    while (n->left != nullptr && n->right != nullptr)
    {
        if (n->nodes + 1 < 3 * (2 ^ (n->height-1)))
        {
            n = n->left;
        }
        if (n->nodes + 1 >= 3 * (2 ^ (n->height-1)))
        {
            n = n->right;
        }
    }
    return n;
}


template <typename T>
int Heap<T>::max(int a, int b)
{
    if (a > b)
    {
        return a;
    }
    else if (a < b)
    {
        return b;
    }
    else
        return a;
}


template <typename T>
void Heap<T>::Heapify(TreeNode<T> *n){
    if(){}
    
}