#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef HEAP_H
#include "Heap.h"
#endif

#include <sstream>

string get_binary(int num) {
    stringstream ss;
    string bin = "";
    while (num != 0) {
        ss.clear();
        ss.str("");
        ss << (num%2);
        bin = ss.str() + bin;
        num /= 2;
    }
    return bin;
}

template<typename T>
void heapify(TreeNode<T> *node) {
    if(node == nullptr)
        return;

    TreeNode *swap = node;
    if(node->object < node->left->object)
        swap = node->left;
    if(obj->object < obj->right->object)
        swap = node->right;

    if (swap != node) {
        T temp = node->object;
        node->object = swap->object;
        swap->object = temp;
        Heapify(swap);
    }
    return;
}

template<typename T>
void Heap<T>::insert(T obj) {
    num++;
    if (root == nullptr) {
        root = new TreeNode<T>(obj);
        return;
    }
    string bin = get_binary(num);
    TreeNode<T> *parent = root;
    int i = 1;
    for(; i<bin.length()-1; i++) {
        if (bin[i] == '0')
            parent = parent->left;
        else
            parent = parent->right;
    }
    if(bin[i] == '0') {
        parent->left = new TreeNode<T>(obj);
        parent->left->parent = parent;
    }
    else {
        parent->right = new TreeNode<T>(obj);
        parent->right->parent = parent;
    }
    return;
}

template<typename T>
T Heap<T>::delMax() {

  // insert your code here

  return;
}

template<typename T>
void Heap<T>::printHeap(TreeNode<T> *node) {

  // insert your code here

  return;
}

  
