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

    if (!root) root = new TreeNode<T> {obj};
    else {
        // Path to the place of the insertion from root given by 
        // the bits in "size" in reverse order
        std::bitset<32> path { size };
        int i {31};
        while (path[i] == 0) i--;
        TreeNode<T> *cur = root;
        
        // Insert at the right place
        for (i--; i>=0; i--) {
            if (!(obj < cur->object)) swap(obj, cur->object);
            if (!i) (path[i] ? cur->right : cur->left) = new TreeNode<T> {obj};
            else cur = (path[i] ? cur->right : cur->left);
        }
    }
    
    return;
}


// Heapify the binary tree to convert it back into a heap after deletion
template<typename T>
void Heap<T>::heapify(TreeNode<T> *node) {
    if (node->right) {
        if (node->left->object < node->object && node->right->object < node->object) return;
        else if (node->left->object < node->right->object && node->object < node->right->object) {
            swap(node->object, node->right->object);
            heapify(node->right);
        } else if (node->right->object < node->left->object || node->object < node->left->object) {
            swap(node->object, node->left->object);
            heapify(node->left);
        }
    } else if (node->left && node->object < node->left->object) swap(node->object, node->left->object);
}


template<typename T>
void Heap<T>::delMax() {

    // insert your code here
    TreeNode<T> *cur = root;
    if (size > 1) {
        // Path to the place of the insertion from root given by 
        // the bits in "size" in reverse order
        std::bitset<32> path { size };  
        int i {31};
        while (path[i] == 0) i--;
        TreeNode<T> *cur = root;
        
        // Get the last element to the root and delete its node
        for (i--; i>=0; i--) {
            if (!i) {
                TreeNode<T> *node = (cur->right ? cur->right : cur->left);
                swap(root->object, node->object);
                (node == cur->right ? cur->right : cur->left) = nullptr;
                delete node;
            }
            else cur = (path[i] ? cur->right : cur->left);
        }

        heapify(root);

    } else {
        delete root;
        root = nullptr;
    }

    size--;
    return;
}


template<typename T>
void Heap<T>::printHeap(const string& prefix, bool isLeft)
{
    if( root != nullptr )
    {
        cout << prefix;

        cout << (isLeft ? "|--" : "|__" );

        // print the value of the node
        cout << root->object << endl;
        TreeNode<T> *curr = root;
        root = root->left;
        // enter the next tree level - left and right branch
        printHeap( prefix + (isLeft ? "│   " : "    "), true);
        root = curr->right;
        printHeap( prefix + (isLeft ? "│   " : "    "), false);
        root = curr;
    }
}