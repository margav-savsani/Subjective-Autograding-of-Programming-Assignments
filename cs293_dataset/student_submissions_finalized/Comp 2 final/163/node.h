#ifndef NODE_H
#define NODE_H

#ifndef STD_HEADERS
#include "std_headers.h"
#endif

using namespace std;

template <typename T>
class list
{
public:
    T object;
    list<T> *next = nullptr;
    list<T> *prev = nullptr;

    // Constructor
    list(T initValue)
    {
        object = initValue;
        next = prev = nullptr;
    }

    // returns if val is present in a list or not
    bool isPresent(T val)
    {
        if (this == nullptr)
            return false;
        if (object == val)
            return true;
        return next->isPresent(val);
    }

    // Destructor
    ~list() { ; }
};

class Node
{
public:
    int value;
    list<int> *toNode = nullptr;           // edge from this node to other node
    list<int> *fromNode = nullptr;         // edge from other node to this node
    list<int> *similar = nullptr;          // nodes which this node is similar to
    list<int> *similarSymmetric = nullptr; // nodes such that either this is similar to that, or that is similar to this

    // Constructors
    Node() { value = -1; }
    Node(int val) { value = val; }

    // to set value
    void setVal(int val) { value = val; }

    // inserting edge
    void insertEdge(int x, bool toEdge)
    {
        list<int> *insertingList = nullptr;
        if (toEdge)
        {
            if (toNode == nullptr)
            {
                toNode = new list<int>(x);
                return;
            }
            insertingList = toNode;
        }
        else
        {
            if (fromNode == nullptr)
            {
                fromNode = new list<int>(x);
                return;
            }
            insertingList = fromNode;
        }
        while (insertingList->next != nullptr)
            insertingList = insertingList->next;
        insertingList->next = new list<int>(x);
        insertingList->next->prev = insertingList;
    }

    // inserting similar node
    void insertSimilar(int x)
    {
        list<int> *s = similar;
        if (similar == nullptr)
            similar = new list<int>(x);
        else
        {
            while (s->next != nullptr)
                s = s->next;
            s->next = new list<int>(x);
            s->next->prev = s;
        }
    }

    // inserting similar symmetric node
    void insertSimilarSymmetric(int x)
    {
        list<int> *s = similarSymmetric;
        if (similarSymmetric == nullptr)
            similarSymmetric = new list<int>(x);
        else
        {
            while (s->next != nullptr)
                s = s->next;
            s->next = new list<int>(x);
            s->next->prev = s;
        }
    }
};

#endif