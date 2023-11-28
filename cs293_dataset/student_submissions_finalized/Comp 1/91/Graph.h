#ifndef GRAPH_BST_H
#define GRAPH_BST_H

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

struct TreeNode {
    int value; // value
    TreeNode* left; // pointer to left child of this node (nullptr, if none)
    TreeNode* right; // pointer to right child of this node (nullptr, if none)
    TreeNode* parent; // pointer to parent node (nullptr in case of root)

    // constructors
    TreeNode();
    TreeNode(int value);
    TreeNode(int value, TreeNode* leftChild, TreeNode* rightChild, TreeNode* parent);
};

#ifndef NODE_DLL_TPL_HPP
#define NODE_DLL_TPL_HPP
template<typename T> struct Node_dll {
    T value;
    Node_dll* next;
    Node_dll* prev;
    Node_dll(T value, Node_dll* next, Node_dll* prev)
        : value(value), next(next), prev(prev)
    {
    }
};
#endif // NODE_DLL_TPL_HPP

class BST {
    TreeNode* root;

public:
    // constructors
    BST();
    BST(TreeNode* root);

    // destructor
    ~BST();

    // returns false, if given JourneyCode is already present in the BST
    // inserts the element and returns true otherwise
    void insert(int value);

    // prints the BST using ASCII characters using the
    // format:
    //   root
    //       |-- left subtree
    //       |__ right subtree
    // where the left and right subtrees are printed recursively in
    // the same format.
    void printBST(std::string const& prefix = "", bool isLeft = false);
};

#ifndef LINKEDLIST_TPL_HPP
#define LINKEDLIST_TPL_HPP
template<typename T> class LinkedList {
    Node_dll<T>* head;
    Node_dll<T>* tail;
    int n;

public:
    struct Iterator {
    private:
        Node_dll<T>* ptr;

    public:
        // Iterator tags here...
        using iterator_category = std::forward_iterator_tag;
        using difference_type = std::ptrdiff_t;

        // Iterator constructors here...
        Iterator(Node_dll<T>* ptr)
            : ptr(ptr)
        {
        }

        T& operator*() const
        {
            if (ptr != nullptr)
                return ptr->value;
            std::cerr << "Null pointer iterator dereferenced\n";
            exit(-1);
        }

        // Prefix increment
        Iterator& operator++()
        {
            if (ptr != nullptr)
                ptr = ptr->next;
            return *this;
        }

        // Postfix increment
        Iterator operator++(int)
        {
            Iterator tmp = *this;
            if (ptr != nullptr)
                ptr = ptr->next;
            return tmp;
        }

        bool operator==(Iterator const& b) const
        {
            return ptr == b.ptr;
        }
        bool operator!=(Iterator const& b) const
        {
            return ptr != b.ptr;
        }
    };

    Iterator begin()
    {
        return Iterator(head);
    }
    Iterator end()
    {
        return Iterator(nullptr);
    }

    LinkedList()
        : head(nullptr), tail(nullptr), n(0)
    {
    }
    ~LinkedList()
    {
        while (head != nullptr) {
            Node_dll<T>* temp = head;
            head = head->next;
            delete temp;
        }
    }

    void push_back(T value)
    {
        if (tail == nullptr) {
            tail = head = new Node_dll<T>(value, nullptr, nullptr);
        } else {
            tail->next = new Node_dll<T>(value, nullptr, tail);
            tail = tail->next;
        }
        n++;
    }
    /*
    void push_front(T value)
    {
        if (head == nullptr)
            head = tail = new Node_dll<T>(value, nullptr, nullptr);
        else {
            head->prev = new Node_dll<T>(value, head, nullptr);
            head = head->prev;
        }
        n++;
    }
     */
    void insert(T value)
    {
        if (head == nullptr)
            head = tail = new Node_dll<T>(value, nullptr, nullptr);
        else {
            Node_dll<T>* temp = head;
            while (temp != tail) {
                if (temp->value < value && temp->next->value >= value) {
                    Node_dll<T>* new_node = new Node_dll<T>(value, temp->next, temp);
                    temp->next->prev = new_node;
                    temp->next = new_node;
                    break;
                }
                temp = temp->next;
            }
            if (temp == tail) {
                tail->next = new Node_dll<T>(value, nullptr, tail);
                tail = tail->next;
            }
        }
        n++;
    }
    void clear()
    {
        while (head != nullptr) {
            Node_dll<T>* temp = head;
            head = head->next;
            delete temp;
        }
        n = 0;
    }
    bool is_empty() const
    {
        return (n == 0);
    }
    bool contains(T value) const
    {
        Node_dll<T>* temp = head;
        while (temp != nullptr) {
            if (temp->value == value)
                return true;
            temp = temp->next;
        }
        return false;
    }
};
#endif

class Node {
public:
    int value;
    LinkedList<int> adjacency; // contains node names, not node indices
};

class Graph {
    int numNodes;
    int numEdges;
    std::fstream graphFile;

    Node* nodes;

    void DFS_connected(int prev_name, int src_name, int& time, BST* tree_ptr, std::string prefix = "");

    int* visits;
    int* old_parent_name;
    int* DFST_parent_name;
    int* arrival;
    bool* in_cycle;
    int components;
    LinkedList<BST*> tree_ptrs;

public:
    Graph(int nNodes, int nEdges, std::string gFileName);
    ~Graph();

    // Add appropriate method declarations as necessary for your implementation
    void modifiedDFS();
    void printResults();
};

#endif
