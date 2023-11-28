#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef HEAP_H
#include "Heap.h"
#endif

template<typename T>
void down_heap(TreeNode<T> *Node)
//Downwards heapify
{
    if (Node->parent == nullptr) return;
    //base case
    else 
    {
        if (Node->object < Node->parent->object) return;
        //Not a base case
        else
        {
            T temp = Node->object;
            Node->object = Node->parent->object;
            Node->parent->object = temp;
            down_heap(Node->parent);
            //Recursive call
        }
    }
}

template <typename T>
TreeNode<T> * Left_Most_Parent(TreeNode<T>* Node)
//Left most parent
{
    while(Node->parent != nullptr)
    //Until node is null
    {
        if (Node->parent->right == Node) Node = Node->parent;
        else break;
    }
    return Node;
}

template <typename T>
TreeNode<T> * Right_Most_Parent(TreeNode<T>* Node)
//Right most parent
{
    while(Node->parent != nullptr)
    //Until parent of node is null
    {
        if (Node->parent->left == Node) Node = Node->parent;
        else break;
    }
    return Node;
}

template <typename T>
TreeNode<T> * Right_Most_Child(TreeNode<T>* Node)
//Right most child
{
    while(Node->right != nullptr) Node = Node->right;
    //Right most node
    return Node;
}

template <typename T>
TreeNode<T> * Left_Most_Child(TreeNode<T>* Node)
//Left Most child
{
    while(Node->right != nullptr) Node = Node->left;
    //Left Most node
    return Node;
}

template <typename T>
void Heap<T>::insert(T obj)
//Insert node of object
{
    TreeNode<T> *node = new TreeNode<T> (obj);
    //constructing node of object

    if (root == nullptr)
    //1st node
    {
        root = node;
        Last_Node = node;
    }
    else
    //Multiple cases
    {
        Last_Node = Left_Most_Parent(Last_Node);
        if (Last_Node->parent == nullptr) 
        {
            Last_Node = Left_Most_Child(Last_Node);
            Last_Node->left = node;
            node->parent = Last_Node;
            Last_Node = Last_Node->left;
        }
        else
        {
            Last_Node = Last_Node->parent;
            if (Last_Node->right == nullptr)
            {
                Last_Node->right = node;
                node->parent = Last_Node;
                Last_Node = Last_Node->right;
            }
            else
            {
                Last_Node = Left_Most_Child(Last_Node->right);
                Last_Node->left = node;
                node->parent = Last_Node;
                Last_Node = Last_Node->left;
            }
        }
    }

    down_heap(Last_Node);
    //Heapifying step
}

template<typename T>
void heapify(TreeNode<T> *Node)
//Heapifying node
{
    if (Node == nullptr) return;
    //Base case
    if (Node->left == nullptr) return;
    //Another base case
    else
    //Multiple cases and subcases
    {
        if(Node->object < Node->left->object)
        {
            if (Node->right == nullptr)
            {
                T Temp = Node->object;
                Node->object = Node->left->object;
                Node->left->object = Temp;
                heapify(Node->left);
            }
            else if (Node->left->object < Node->right->object)
            {
                T Temp = Node->object;
                Node->object = Node->right->object;
                Node->right->object = Temp;
                heapify(Node->right);
            }
            else
            {
                T Temp = Node->object;
                Node->object = Node->left->object;
                Node->left->object = Temp;
                heapify(Node->left);
            }
        }
        else 
        {
            if (Node->right == nullptr) return;
            else if (Node->object < Node->right->object)
            {
                T Temp = Node->object;
                Node->object = Node->right->object;
                Node->right->object = Temp;
                heapify(Node->right);
            }
        }
    }
}


template <typename T>
void Heap<T>::delMax()
//Deletes maximum element
{
    root->object = Last_Node->object;
    //changine last node to root

    if (Last_Node->parent == nullptr)
    //Base case
    {
        root = nullptr;
        Last_Node = nullptr;
    }
    else 
    //Multiple cases and sub cases
    {
        TreeNode<T> *NN = Last_Node;
        Last_Node = Right_Most_Parent(Last_Node);
        if (Last_Node->parent == nullptr)
        {
            Last_Node = Right_Most_Child(Last_Node);
        }
        else
        {
            Last_Node = Last_Node->parent->left;
            Last_Node = Right_Most_Child(Last_Node);
        }
        if(NN->parent->left == NN)
        {
            NN->parent->left = nullptr;
        }
        else NN->parent->right = nullptr;
    }

    heapify(root);
    //call of heapify
}

template <typename T>
void Heap<T>::printHeap(TreeNode<T> *node)
{
    static string pre = "";
    static bool left = false;
    static int recursion_level = 0;

    recursion_level++;
    if (recursion_level == 1)
    {
        pre = "";
        left = false;
    }

    if (node != nullptr)
    {
        string s = pre;
        if (left) cout << pre <<"|--" << node->object << "\n";
        else cout << pre << "|__" << node->object << "\n";

        if (left) pre = pre + "|  ";
        else pre = pre + "   ";
        left = true;
        printHeap(node->left);
        left = false;
        printHeap(node->right);
        pre = s;
    }
    recursion_level--;

    return;
}
