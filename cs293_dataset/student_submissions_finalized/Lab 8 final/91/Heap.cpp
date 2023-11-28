#include "Heap.h"

template<typename T> TreeNode<T>* Heap<T>::successor_with_parent(TreeNode<T>* n)
{
    if (n == nullptr)
        return nullptr;
    if (n->parent == nullptr) {
        if (n->left == nullptr)
            return n;
        return n->left;
    }
    if (n->parent->left == n) {
        if (n->parent->right == nullptr)
            return n->parent;
        return n->parent->right;
    }
    TreeNode<T>* s = successor(n->parent);
    if (s->left != nullptr)
        return s->left;
    return s;
}

template<typename T> TreeNode<T>* Heap<T>::successor(TreeNode<T>* n)
{
    if (n == nullptr)
        return nullptr;
    if (n->parent == nullptr)
        return n->left;
    if (n->parent->left == n)
        return n->parent->right;
    return successor(n->parent)->left;
}

template<typename T> void Heap<T>::swap(TreeNode<T>* n1, TreeNode<T>* n2)
{
    if (n1 != nullptr && n2 != nullptr) {
        T temp = n1->object;
        n1->object = n2->object;
        n2->object = temp;
    }
}

template<typename T> void Heap<T>::printHeap(TreeNode<T>* node, std::string const& prefix, bool isLeft)
{
    // Adapted from Adrian Schneider's code on Stack Overflow
    if (node != nullptr) {
        std::cout << prefix << (isLeft ? "│--(" : "│__(" );
        // print the value of the node
        std::cout << node->object << ")\n";
        // enter the next tree level - left and right branch
        printHeap(node->left, prefix + (isLeft ? "│   " : "    "), true);
        printHeap(node->right, prefix + (isLeft ? "│   " : "    "), false);
    }
}

template<typename T> void Heap<T>::heapify_bottom_up(TreeNode<T>* node)
{
    if (node != nullptr && node->parent != nullptr && node->parent->object < node->object) {
        swap(node, node->parent);
        heapify_bottom_up(node->parent);
    }
}

template<typename T> void Heap<T>::heapify_top_down(TreeNode<T>* node)
{
    if (node != nullptr) {
        TreeNode<T>* largest = node;
        if (node->left != nullptr && !(node->left->object < largest->object))
            largest = node->left;
        if (node->right != nullptr && !(node->right->object < largest->object))
            largest = node->right;
        if (largest != node) {
            swap(node, largest);
            heapify_top_down(largest);
        }
    }
}

template<typename T> void Heap<T>::insert(T obj)
{
    if (root == nullptr) {
        root = new TreeNode<T>(obj);
    }
    else {
        TreeNode<T>* ptr = nullptr;
        TreeNode<T>* temp = root;

        while (temp != nullptr) {
            ptr = temp;
            temp = temp->left;
        }
        
        temp = successor(ptr);
        while (temp != nullptr) {
            ptr = temp;
            temp = successor(ptr);
        }
        temp = successor_with_parent(ptr);

        if (temp->left == nullptr) {
            temp->left = new TreeNode<T>(obj);
            temp->left->parent = temp;
            temp = temp->left;
        }
        else {
            temp->right = new TreeNode<T>(obj);
            temp->right->parent = temp;
            temp = temp->right;
        }

        heapify_bottom_up(temp);
    }
}

template<typename T> void Heap<T>::delMax()
{
    if (root == nullptr) {
        std::cerr << "Deleting max from empty heap!\n";
        exit(-1);
    }

    TreeNode<T>* ptr = nullptr;
    TreeNode<T>* temp = root;
    while (temp != nullptr) {
        ptr = temp;
        temp = temp->left;
    }
    temp = successor(ptr);
    while (temp != nullptr) {
        ptr = temp;
        temp = successor(temp);
    }
    root->object = ptr->object;
    
    if (ptr->parent != nullptr) {
        if (ptr == ptr->parent->left)
            ptr->parent->left = nullptr;
        else
            ptr->parent->right = nullptr;
   }
    else {
        root = nullptr;
    }

    delete ptr;
    heapify_top_down(root);
}
