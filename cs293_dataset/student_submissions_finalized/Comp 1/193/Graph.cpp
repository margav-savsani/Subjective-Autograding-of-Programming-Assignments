#ifndef GRAPH_BST_CPP
#define GRAPH_BST_CPP

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef GRAPH_BST_H
#include "Graph.h"
#endif

#define CONST_GROWTH 6
#define INIT_SIZE 6

template <typename T>
class MyVector
{
public:
    T *A;              // the array used for implementing the dynamic dequeue
    unsigned int N;    // the current size of array A
    unsigned int head; // index where next element of queue will be deleted from
    unsigned int tail; // index where next element will be inserted
    unsigned int nextSize() { return N + CONST_GROWTH; }
    MyVector() // default constructor
    {
        A = new T[INIT_SIZE];
        if (A != nullptr)
            N = INIT_SIZE;
        else
            N = 0;
        head = tail = 0;
    }
    ~MyVector(){}; // default destructor

    bool isEmpty()
    {
        return (tail == head); // When the head variable is the same as tail variable the queue becomes empty.
    }                          // is the queue empty?
    bool isFull()
    {
        return (size() == N);
    } // is the queue full?
    void grow()
    {
        unsigned int b = nextSize();
        T *B = new T[b]; // Alloting a new memory to a pointer.

        for (unsigned int i = head; i < tail; i++)
        { // copying the elements of the initial array to newly created array.
            // In the new array the elements are kept in a linear fashion.
            B[i - head] = A[i % N];
        }
        tail = N; // tail becomes N
        head = 0; // head again becomes 0
        N = b;    // grow the queue to its next size.
        A = B;    // reallocating A to Newly created memory.
        B = NULL; // making B point to NULL.
    }             // grow the queue to its next size
    unsigned int size()
    { // Gives the total number of elements present in the queue.
        return (tail - head);
    } // return the current number of elements in the queue
    void QInsert(T x)
    {
        if (isFull())
        {
            grow(); // just grow if full (in case of circular array.)
        }
        A[tail % N] = x;
        tail += 1;
    }
    bool deletefirst()
    {
        if (size() == 0)
            return false;
        head += 1; // head incremented.
        return true;
    }
    bool deletelast()
    {
        if (size() == 0)
            return false;
        tail = tail - 1; // Tail Decremented.
        return true;
    }
    bool find_elem(T tofind) // Find whether an element is present in the Queue.
    {
        for (unsigned int i = head; i < tail; i++)
        {
            if (tofind == A[i % N])
            {
                return true;
            }
        }
        return false;
    }
    T get_last()
    {
        return A[(tail - 1) % N];
    }
    T get_first()
    {
        return A[head % N];
    }
    int last_occurence(T j)
    {
        // This function provides the position of last occurence of the element j in the Queue
        for (unsigned int i = (tail - 1); i >= head; i--)
        {
            if (A[i % N] == j)
            {
                return i;
            }
        }
        return -1;
    }
};

// A stack to store the element in the current path in DFS.
MyVector<int> path;

// A new DFS function that takes in argument as sourceNode index
// and the BST into which the Nodes have to be inserted
void Graph::DFS(int sourceNode, BST &t)
{
    path.QInsert(sourceNode);          // Adding the sourceNode to the current path
    visits[sourceNode]++;              // Incrementing the visit of the source Node
    t.insert(nodes[sourceNode].value); // Inserting source Node to BST
    linkedlist<int> *curr = adjacenylist;
    linkedlist<int> iterator = curr[sourceNode];
    if (iterator.object == -1)
    {
        // If it is a single Node without any Edge
        path.deletelast(); // Popping the stack.
        return;
    }

    // If the iterator object is not the parent of current Node and if it is present in the path,
    // Then all the elements from the last instance of the iterator object in the path to the end of Queue would be in a cycle.
    if ((iterator.object) != nodes[sourceNode].parents[0] && (iterator.object) != nodes[sourceNode].parents[1] && path.find_elem(iterator.object))
    {
        int last_ind = path.last_occurence(iterator.object);
        for (unsigned int k = last_ind; k < path.tail; k++)
        {
            isinacycle[path.A[k % path.N]] = 1;
        }
    }

    // If the iterator itself has less than 2 visits and the iterator object is not one of the parent of the Current Node
    if (visits[iterator.object] < 2 && (iterator.object) != nodes[sourceNode].parents[0] && (iterator.object) != nodes[sourceNode].parents[1])
    {
        nodes[iterator.object].insert_parent(sourceNode);
        DFS(iterator.object, t);
    }

    // Look for the next elements
    while (iterator.next != NULL)
    {
        iterator = *(iterator.next);
        if ((iterator.object) != nodes[sourceNode].parents[0] && (iterator.object) != nodes[sourceNode].parents[1] && path.find_elem(iterator.object))
        {
            int last_ind = path.last_occurence(iterator.object);
            for (unsigned int k = last_ind; k < path.tail; k++)
            {
                isinacycle[path.A[k % path.N]] = 1;
            }
        }
        if (visits[iterator.object] < 2 && (iterator.object) != nodes[sourceNode].parents[0] && (iterator.object) != nodes[sourceNode].parents[1])
        {
            nodes[iterator.object].insert_parent(sourceNode);
            DFS(iterator.object, t);
        }
    }
    path.deletelast();
    return;
}

// To store the BSTs that have been made
MyVector<BST> queues_of_BST;

void Graph::modifiedDFS()
{
    for (int i = 0; i < numNodes; i++)
    {
        if (visits[i] == 0)
        {
            // Run DFS again on a Node if the Node is not visited even once
            // This accounts for a new connected component in the graph
            BST t;
            connectedcomp++;
            DFS(i, t);
            queues_of_BST.QInsert(t);
        }
    }
    return;
}

void Graph::printResults()
{
    int count = 0;
    cout << "Total connected Components are: " << connectedcomp << endl;
    cout << "Number of Nodes visited once are: ";
    for (int i = 0; i < numNodes; i++)
    {
        if (visits[i] == 1)
        {
            count++;
        }
    }
    cout << count << endl;
    count = 0;
    cout << "Number of Nodes visited twice are: ";
    for (int i = 0; i < numNodes; i++)
    {
        if (visits[i] == 2)
        {
            count++;
        }
    }
    cout << count << endl;
    count = 0;
    cout << "Number of Nodes present in any cycle are: ";
    for (int i = 0; i < numNodes; i++)
    {
        if (isinacycle[i])
        {
            count++;
        }
    }
    cout << count << endl<<endl;
    count = 0;
    cout << "The BST for the connected components are as follows: " << endl;
    cout<<"---------------------------------------"<<endl;
    while (!queues_of_BST.isEmpty())
    { // Untill the Queue of BST is not Empty
        count++;
        cout<< "The BST of component No. " <<count<<" is "<<endl;
        BST head = queues_of_BST.get_first();
        queues_of_BST.deletefirst();
        head.printBST(" ", false);
        cout<<endl;
        cout<<"---------------------------------------"<<endl;
    }
    return;
}

#endif
