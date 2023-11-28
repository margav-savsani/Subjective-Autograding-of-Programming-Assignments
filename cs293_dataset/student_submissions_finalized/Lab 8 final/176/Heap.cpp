#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef HEAP_H
#include "Heap.h"
#endif

#include <sstream>


// returns the binary form of given integer
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


// heapifies the tree at given node
template<typename T>
void heapify(TreeNode<T> *node) {
    if(node == nullptr || node->left == nullptr)    // no node or no children 
        return;

    TreeNode<T> *swap = node;   // the node object to be put at the top
    if(node->object < node->left->object)   // check with the left child if it is larger
        swap = node->left;
    if(node->right != nullptr)              // check with the right child if it is larger
        if(swap->object < node->right->object)
            swap = node->right;

    if (swap != node) {     // if one of the children is larger than the node
        T temp = node->object;
        node->object = swap->object;
        swap->object = temp;
        heapify(swap);      // heaify at this node to proper the heap structure downside
    }
    return;
}


// inserts a node into the heap tree
template<typename T>
void Heap<T>::insert(T obj) {
    num++;
    if (root == nullptr) {          // heap is empty, first node to be added
        root = new TreeNode<T>(obj);
        return;
    }
    string bin = get_binary(num);   // for position of node to be inserted
    TreeNode<T> *parent = root;
    int i = 1;
    for(; i<bin.length()-1; i++) {
        if (bin[i] == '0')                  // traverse left if character is '0' in binary form
            parent = parent->left;
        else                                // traverse right if character is '1' in binary form
            parent = parent->right;
    }
    if(bin[i] == '0') {                         // empty node is at the left
        parent->left = new TreeNode<T>(obj);
        parent->left->parent = parent;
    }
    else {
        parent->right = new TreeNode<T>(obj);   // empty node is at the right
        parent->right->parent = parent;
    }

    TreeNode<T> *node = parent;
    while(node != nullptr) {    // heapify up the tree from this node onwards
        heapify(node);
        node = node->parent;
    }
    return;
}


// deletes the object at with maximum value in heap i.e. root node
template<typename T>
void Heap<T>::delMax() {
    if (root == nullptr) {      // nothing to be deleted
        return;
    }

    if(num == 1) {      // onyl one node present, so delete it
        delete root;
        root = nullptr;
        num--;
        return;
    }

    string bin = get_binary(num);   // for position of last node in heap
    TreeNode<T> *parent = root;
    int i = 1;
    for(; i<bin.length()-1; i++) {
        if (bin[i] == '0')          // traverse left if character is '0' to reach node
            parent = parent->left;
        else                        // traverse right if character is '1' to reach node
            parent = parent->right;
    }

    if(bin[i] == '0') {                         // object to be deleted is left child of parent
        root->object = parent->left->object;
        delete parent->left;
        parent->left = nullptr;
    }
    else {                                      // object to be deleted is right child of parent
        root->object = parent->right->object;
        delete parent->right;
        parent->right = nullptr;
    }
    num--;
    heapify(root);      // to correct the heap structure and place the root object at correct position
    return;
}


// prints all the nodes in the heap in a tree format
template<typename T>
void Heap<T>::printHeap(TreeNode<T> *node) {
    static string prefix;
    static bool isLeft;

    if(node == root) {
        prefix = "";
        isLeft = false;
    }

    if( node != nullptr )
    {
        cout << prefix;
        cout << (isLeft ? "|--" : "|__" );

        // print the value of the node
        cout << node->object << endl;

        string old_prefix = prefix;
        bool rightSiblingParent = (isLeft && (node->parent->right != nullptr));
        
        // printing the left sub-heap
        prefix = prefix + (rightSiblingParent ? "│   " : "    ");
        isLeft = true;
        printHeap(node->left);

        // printing the right sub-heap
        prefix = old_prefix + (rightSiblingParent ? "│   " : "    ");
        isLeft = false;
        printHeap(node->right);
    }
    return;
}


// destructor to free all nodes in the heap
template<typename T>
Heap<T>::~Heap() {
    for(int i=0; i<num; i++)
        delMax();
}