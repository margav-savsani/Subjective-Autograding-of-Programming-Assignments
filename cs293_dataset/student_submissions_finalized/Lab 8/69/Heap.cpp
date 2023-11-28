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
    if(){}
    else{}

}

template <typename T>
void Heap<T>::delMax()
{

    // insert your code here

}

template <typename T>
void Heap<T>::printHeap(TreeNode<T> *node)
{

    // insert your code here

}

template <typename T>
void Heap<T>::heapify(TreeNode<T> *i){
    TreeNode<T> *p = i->parent;
    if(p->parent != nullptr){
    TreeNode<T> *gp = p->parent;}
    if(p != nullptr){
        if(i->rating > p->rating){
            // swap(i,p)
            if(gp != nullptr){
                if(gp->left == p && p->left == i){
                    if(i->left != nullptr){
                        p->left = i->left;
                    }
                    if(i->right != nullptr){
                        p->right = i->right;
                    }
                    gp->left = i;
                    i->left = p;
                }
                if(gp->left == p && p->right == i){
                    if(i->left != nullptr){
                        p->left = i->left;
                    }
                    if(i->right != nullptr){
                        p->right = i->right;
                    }
                    gp->left = i;
                    i->right = p;
                }
                if(gp->right == p && p->left == i){
                    if(i->left != nullptr){
                        p->left = i->left;
                    }
                    if(i->right != nullptr){
                        p->right = i->right;
                    }
                    gp->right = i;
                    i->left = p;
                }
                if(gp->right == p && p->right == i){
                    if(i->left != nullptr){
                        p->left = i->left;
                    }
                    if(i->right != nullptr){
                        p->right = i->right;
                    }
                    gp->right = i;
                    i->right = p;
                }
            }
            else{
                if(p->left == i){
                    TreeNode<T> *n = p;
                    if(i->left != nullptr){
                        p = i;
                        p->left = n;
                    }
                    if(i->right != nullptr){
                        p = i;
                        p->right = n;
                    }
                }
                if(p->right == i){

                }
            }

            heapify(p);
        }
    }
}