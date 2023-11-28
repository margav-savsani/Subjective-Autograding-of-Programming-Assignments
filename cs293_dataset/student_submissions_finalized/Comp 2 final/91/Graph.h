#ifndef GRAPH_BST_H
#define GRAPH_BST_H

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

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

#ifndef LINKEDLIST_TPL_HPP
#define LINKEDLIST_TPL_HPP
template<typename T> class LinkedList {
    Node_dll<T>* head;
    Node_dll<T>* tail;
    size_t n;

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
            std::cerr << "Null pointer iterator dereferenced (as LinkedList::Iterator dereference)\n";
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

    Iterator begin() const
    {
        return Iterator(head);
    }
    Iterator end() const
    {
        return Iterator(nullptr);
    }

    LinkedList()
        : head(nullptr), tail(nullptr), n(0)
    {
    }
    LinkedList(LinkedList<T> const& l)
        : head(nullptr), tail(nullptr), n(0)
    {
        for (T c : l)
            this->push_back(c);
    }
    LinkedList& operator=(LinkedList<T> const& l)
    {
        this->clear();
        for (T c : l)
            this->push_back(c);
    }
    ~LinkedList()
    {
        while (head != nullptr) {
            Node_dll<T>* temp = head;
            head = head->next;
            delete temp;
        }
    }

    void insert(T value)
    {
        if (head == nullptr)
            head = tail = new Node_dll<T>(value, nullptr, nullptr);
        else {
            Node_dll<T>* temp = head;
            if (value <= head->value) {
                head->prev = new Node_dll<T>(value, head, nullptr);
                head = head->prev;
            }
            else {
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
        head = tail = nullptr;
        n = 0;
    }
    size_t size() const
    {
        return n;
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
#endif // LINKEDLIST_TPL_HPP

#ifndef PAIR_TPL_HPP
#define PAIR_TPL_HPP
template<typename T> class Pair {
public:
    T v1;
    T v2;
    Pair(T v1, T v2)
        : v1(v1), v2(v2)
    {
    }
    bool operator==(Pair const& p) const
    {
        return (v1 == p.v1) && (v2 == p.v2);
    }
    bool operator!=(Pair const& p) const
    {
        return (v1 != p.v1) || (v2 != p.v2);
    }
    bool operator>(Pair const& p) const
    {
        if (v1 != p.v1)
            return v1 > p.v1;
        return v2 > p.v2;
    }
    bool operator<(Pair const& p) const
    {
        if (v1 != p.v1)
            return v1 < p.v1;
        return v2 < p.v2;
    }
    bool operator>=(Pair const& p) const
    {
        return (*this > p) || (*this == p);
    }
    bool operator<=(Pair const& p) const
    {
        return (*this < p) || (*this == p);
    }
};
#endif // PAIR_TPL_HPP

class Node {
public:
    int value;
    LinkedList<int> outbound_adjacency; // contains node names, not node indices, and
                                        // this->outbound_adjacency.contains(n) <=> edge value--->n exists
    LinkedList<int> inbound_adjacency; // contains node names, not node indices, and
                                        // this->inbound_adjacency.contains(n)  <=> edge n--->value exists
    LinkedList<int> similar; // contains node names, not node indices, and
                             // this->similar.contains(n) <=> value~n in similarity
};

class Graph {
    int numNodes;
    Node* nodes;
    
    LinkedList<int> sources;
    LinkedList<int> non_sources;
    LinkedList<Pair<int>> similar_pairs_list;

    void update_similarity(LinkedList<int> l);

public:
    Graph();
    ~Graph();

    LinkedList<int> source() const;
    LinkedList<Pair<int>> similar_pairs() const;

    void collapse_similarity(std::ofstream& f) const;
};

#endif
