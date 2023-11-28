#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef HEAP_H
#include "Heap.h"
#endif

template<typename T>
void Heap<T>::insert(T obj) {
    // insert your code here
    size++;

    if (!root) root = new_node;
    else {
        std::bitset<32> path { size };
        TreeNode<T> *cur = root;
        for (int i=path.count()-2; i>=0; i--) {
            if (obj > cur->object) swap(obj, cur->object);
            if (!i) (path[i] ? cur->right : cur->left) = new Treenode<T> {obj};
            else cur = (path[i] ? cur->right : cur->left);
        }
    }

    return;
}

template<typename T>
void Heap<T>::delMax() {

    // insert your code here
    TreeNode<T> *cur = root;
    if (root->left) {
        std::bitset<32> path { size };
        for (int i=path.count()-2; i>=0; i--) {
            if (!i) {
                if (cur->right) {
                    swap(cur->right->object, cur->object);
                    delete cur->right;
                    cur->right = nullptr;
                    if (cur->object < cur->left->object) swap(cur->object, cur->left->object);
                } else {
                    swap(cur->left->object, cur->object);
                    delete cur->left;
                    cur->left = nullptr;
                }
            } else {
                if (cur->left->object > cur->right->object) {
                    swap(cur->object, cur->left->object);
                    cur = cur->left;
                } else {
                    swap(cur->object, cur->right->object);
                    cur = cur->right;
                }
            }
        }

        delete cur;
    } else {
        delete root;
        root = nullptr;
    }

    size--;
    return;
}

template<typename T>
void Heap<T>::printHeap(TreeNode<T> *node) {

    // insert your code here

    return;
}