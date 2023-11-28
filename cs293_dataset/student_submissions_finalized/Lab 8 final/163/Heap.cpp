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
    numOfNodes++; // number of nodes increase
    if (root == nullptr)
    {
        root = new TreeNode<T>(obj); // if heap is empty, inserted directly at root
        // printHeap(root);
        return;
    }
    int insertPosition = numOfNodes; // the new no. of nodes is the position where we want to insert
    string binaryPosition = "";      // each digit of binary form of insertPosition gives the path to the position where we have to insert
    // initial 1 being for root, then each 0 is left, 1 is right
    while (insertPosition > 0)
    {
        binaryPosition = to_string(insertPosition % 2) + binaryPosition; // converts the insertPosition to binary and stores in form of string
        insertPosition = insertPosition / 2;
    }
    TreeNode<T> *temp = root;
    for (int i = 1; i < binaryPosition.size() - 1; i++)
    { // traverses to the parent of where we want to insert new node
        if (binaryPosition[i] == '0')
            temp = temp->left;
        else
            temp = temp->right;
    }
    if (binaryPosition[binaryPosition.size() - 1] == '0') // new node is inserted at left or right, as possible
    {
        temp->left = new TreeNode<T>(obj);
        temp->left->parent = temp;
        temp = temp->left;
    }
    else
    {
        temp->right = new TreeNode<T>(obj);
        temp->right->parent = temp;
        temp = temp->right;
    }
    while (temp->parent != nullptr) // we traverse from new node to root to rectify heap
    {
        if (temp->parent->object < temp->object)
        { // if parent is less than node, we swap them, as it is max-heap
            T t = temp->object;
            temp->object = temp->parent->object;
            temp->parent->object = t;
            temp = temp->parent;
        }
        else
        {
            break;
        }
    }
    // printHeap(root);

    return;
}

template <typename T>
void Heap<T>::delMax()
{
    // insert your code here
    if (numOfNodes == 1 || numOfNodes == 0)
    { // if only root is there, it is removed.
        // if heap is empty, it remains as it is.
        root = nullptr;
        return;
    }
    int deletePosition = numOfNodes; // the numOfNodes is the position of last inserted node, which is to be placed at root.
    string binaryPosition = "";      // each digit of binary form of insertPosition gives the path to the position where we have to delete
    // initial 1 being for root, then each 0 is left, 1 is right
    while (deletePosition > 0)
    {
        binaryPosition = to_string(deletePosition % 2) + binaryPosition; // converts the insertPosition to binary and stores in form of string
        deletePosition = deletePosition / 2;
    }
    TreeNode<T> *temp = root;
    for (int i = 1; i < binaryPosition.size() - 1; i++)
    { // traverses to the parent of where we want to delete node
        if (binaryPosition[i] == '0')
            temp = temp->left;
        else
            temp = temp->right;
    }
    if (binaryPosition[binaryPosition.size() - 1] == '0') // object at node at left or right of parentNode is placed at root and then the node is deleted as required.
    {
        root->object = temp->left->object;
        temp->left->~TreeNode();
        temp->left = nullptr;
    }
    else
    {
        root->object = temp->right->object;
        temp->right->~TreeNode();
        temp->right = nullptr;
    }
    Heapify(root); // Makes the tree a heap again
    // printHeap(root);
    numOfNodes--; // numOfNodes is decreased.
    return;
}

template <typename T>
void Heap<T>::Heapify(TreeNode<T> *node)
{
    TreeNode<T> *t;
    if (node->left == nullptr && node->right == nullptr)
        return; // it is a heap
    else if (node->left == nullptr)
    { // left is nullptr, so only need to check right
        if (node->right->object < node->object)
            return; // it is a heap.
        else
            t = node->right; // we would need to make change at node->right, so stored in t
    }
    else if (node->right == nullptr)
    { // right is nullptr, so only need to check left
        if (node->left->object < node->object)
            return; // it is a heap
        else
            t = node->left; // we would need to make change at node->left, so stored in t
    }
    else
    { // need to check both right and left
        if (node->left->object < node->object && node->right->object < node->object)
            return; // it is a heap
        else if (node->right->object < node->object)
            t = node->left; // we would need to make change at node->left, so stored in t
        else if (node->left->object < node->object)
            t = node->right; // we would need to make change at node->right, so stored in t
        else if (node->left->object < node->right->object)
            t = node->right; // we would need to make change at node->right, so stored in t
        else
            t = node->left; // we would need to make change at node->left, so stored in t
    }
    // node and t (left or right of node) are swaped
    T t_obj = t->object;
    t->object = node->object;
    node->object = t_obj;
    Heapify(t); // t (left or right or node) needs to be heapified now.
}

template <typename T>
void Heap<T>::printHeap(TreeNode<T> *node)
{
    // insert your code here
    // This code is Adapted form tree.cpp of lab5

    // Adapted from Adrian Schneider's code on StackOverflow
    static string prefix = ""; // static, so only initiallise once, not in every recursive call
    static bool isLeft = false;

    if (node != nullptr)
    {
        cout << prefix;
        cout << (isLeft ? "|--" : "|__");
        // print the value of the node
        cout << node->object << endl;
        // enter the next tree level - left and right branch
        string temp = prefix;
        prefix = prefix + (isLeft ? "│   " : "    ");
        isLeft = true;
        printHeap(node->left);
        isLeft = false;
        printHeap(node->right);
        prefix = temp; // prefix is restored to maintain proper tree structure
    }

    return;
}
