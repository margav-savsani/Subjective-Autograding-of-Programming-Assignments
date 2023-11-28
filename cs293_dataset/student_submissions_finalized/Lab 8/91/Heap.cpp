#include "Heap.h"

template<typename T> TreeNode<T>::TreeNode(T initObj)
    : object(initObj), left(nullptr), right(nullptr), parent(nullptr)
{
}

template<typename T> TreeNode<T>::~TreeNode()
{
}

template<typename T> std::ostream& operator<<(std::ostream& o, TreeNode<T> const& p)
{
    o << p.object;
    return o;
}

template<typename T> void Heap<T>::cleanup(TreeNode<T>* subroot)
{
    if (subroot != nullptr) {
        cleanup(subroot->left);
        cleanup(subroot->right);
        delete subroot;
    }
}

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

template<typename T> void Heap<T>::heapify()
{

}

template<typename T> Heap<T>::Heap()
    : root(nullptr)
{
}

template<typename T> Heap<T>::~Heap()
{
    cleanup(root);
}

template<typename T> void Heap<T>::insert(T obj)
{
    if (root == nullptr) {
        root = new TreeNode<T>(obj);
        return;
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
    temp = successor_with_parent(ptr);
    if (temp->left == nullptr) {
        temp->left = new TreeNode<T>(obj);
        temp->left->parent = temp;
    }
    else {
        temp->right = new TreeNode<T>(obj);
        temp->right->parent = temp;
    }
    // heapify();
}

template<typename T> T Heap<T>::delMax()
{
    if (root == nullptr) {
        std::cerr << "Deleting max from empty heap!\n";
        exit(-1);
    }
    T ret = root->object;
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
    // heapify();
    return ret;
}

template<typename T> T Heap<T>::getMax()
{
    return root->object;
}

template<typename T> void Heap<T>::printHeap(std::string const& prefix, bool isLeft)
{
    // Adapted from Adrian Schneider's code on Stack Overflow
    if (root != nullptr) {
        std::cout << prefix << (isLeft ? "│--(" : "│__(" );
        
        // print the value of the node
        std::cout << *root << ")\n";
        TreeNode<T>* curr = root;
        root = root->left;
        // enter the next tree level - left and right branch
        printHeap(prefix + (isLeft ? "│   " : "    "), true);
        root = curr->right;
        printHeap(prefix + (isLeft ? "│   " : "    "), false);
        root = curr;
    }
}

    
