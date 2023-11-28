#ifndef GRAPH_BST_H
#define GRAPH_BST_H

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif
using namespace std;

// A Doubly linked list Mostly for storing the integers.
template <typename T>
class linkedlist
{
public:
    T object;
    T index; // Tells whose list is this.
    linkedlist<T> *next;
    linkedlist<T> *prev;

    // Constructor
    linkedlist(T initValue)
    {
        object = initValue;
        next = prev = nullptr;
    }
    linkedlist()
    {
        // In the Default constructor specify the value of T as -1.
        object = -1;
        next = prev = nullptr;
    }
    // Function to insert into a linked list
    void insert_ll(T a)
    {
        // i.e we are inserting into list for the first time
        if (this->object == -1)
        {
            this->object = a;
            return;
        }
        linkedlist<T> *iterator = this;
        // Untill we reach the end of the list
        while (iterator->next != NULL)
        {
            iterator = iterator->next;
        }
        iterator->next = new linkedlist(a);
    }
    // Find whether the object is present in the list or not
    bool find_ll(T a)
    {
        linkedlist<T> *iterator = this;
        if (iterator->object == -1) // If nothing is inserted
        {
            return false;
        }
        while (iterator != NULL)
        {
            if (iterator->object == a)
            {
                return true;
            }
            iterator = iterator->next;
        }
        return false;
    }
    void printlist(fstream& file)
    { // Function to print the linked list
        linkedlist<T> *iterator = this;
        while (iterator != NULL)
        {
            file << iterator->object << " ";
            iterator = iterator->next;
        }
    }
    // Destructor
    ~linkedlist() { ; }
};

#define CONST_GROWTH 6
#define INIT_SIZE 6

template <typename T>
class MyVector
{
public:
    T *A;              // the array used for implementing
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
};

// The Class that represents a similarity relation
class similarity_Relation
{
public:
    // The relation (n1,n2)
    int n1;
    int n2;

    similarity_Relation()
    {
        n1 = -1;
        n2 = -1;
    }
    // This function would replace the toreplace(if present) with the replacewith
    void replace_elem(int toreplace, int replacewith)
    {
        if (toreplace == n1)
        {
            n1 = replacewith;
        }
        if (toreplace == n2)
        {
            n2 = replacewith;
        }
    }
    similarity_Relation(int a, int b)
    {
        n1 = a;
        n2 = b;
    }
    bool operator==(similarity_Relation a)
    { // Overloading the operator for checking the Equality of two relations.
        if (a.n1 == n1 && a.n2 == n2)
        {
            return true;
        }
        return false;
    }
};

// The Node of the Graph
class Node
{
public:
    // The value that is present in the Node.
    int value;

    Node() // constructor of the Node
    {
    }
};

class Graph
{
public:
    int numNodes;
    int numEdges;

    // File to which we output
    fstream graphFile;

    fstream inputfile;
    // The array of the Nodes
    Node *nodes;

    // The Inadjacency list of the Nodes
    linkedlist<int> *inadjacencylist;

    // The OutAdjacency list of the Nodes
    linkedlist<int> *outadjacencylist;

    // The linked list of the source Nodes
    linkedlist<int> *sourceNodes;

    // All the relations present in the Graph
    MyVector<similarity_Relation> Relations;

    // Vector to store all the visited Nodes
    MyVector<int> visited;

    // The Edges that are present in the Graph
    MyVector<similarity_Relation> Edges;
    Graph(int N, string filename)
    {
        // The Number of Nodes in the graph
        numNodes = N;
        nodes = new Node[numNodes];

        // Assigning memory to the adjaceny lists
        inadjacencylist = new linkedlist<int>[numNodes];
        outadjacencylist = new linkedlist<int>[numNodes];

        // Initialising the source Nodes
        sourceNodes = new linkedlist<int>;
        sourceNodes->object = -1;

        for (int i = 0; i < numNodes; i++)
        {
            // Initialising all the values by -1
            inadjacencylist[i].object = -1;
            outadjacencylist[i].object = -1;

            // The index of the adjacency list
            inadjacencylist[i].index = (i + 1);
            outadjacencylist[i].index = (i + 1);
        }

        if (nodes == nullptr)
        {
            cerr << "Memory allocation failure." << endl;
            exit(-1);
        }

        // Assigning the Value to the nodes
        for (int i = 0; i < numNodes; i++)
        {
            nodes[i].value = i + 1;
        }
        graphFile.open(filename, ios::out);
    }

    ~Graph()
    {
        if (graphFile.is_open())
        {
            graphFile.close();
        }
        delete[] nodes;
    }

    void insertEdge(int a, int b)
    { // Insert Directed Edge A->B
        inadjacencylist[b - 1].insert_ll(a - 1);
        outadjacencylist[a - 1].insert_ll(b - 1);
        Edges.QInsert(similarity_Relation(a, b));
    }

    void listSourceNodes()
    {
        for (int i = 0; i < numNodes; i++)
        {
            if (inadjacencylist[i].object == -1)
            {
                visited.QInsert(nodes[i].value);
                sourceNodes->insert_ll(nodes[i].value);
            }
        }
    }
    // Adding all the source relations as specified by the user
    void addsourcerelations(int a, int b)
    {
        similarity_Relation h = similarity_Relation(a, b);
        Relations.QInsert(h);
    }
    // Function checks for relation among the comparison Nodes and Adds if any new is present.
    void Check_relation_and_add(MyVector<similarity_Relation> &Relations, MyVector<int> comparison_nodes)
    {
        int head = comparison_nodes.head;
        int tail = comparison_nodes.tail;
        int size = comparison_nodes.size();
        for (unsigned int i = head; i < tail; i++)
        {
            for (unsigned int j = head; j < tail; j++)
            {

                int n1 = comparison_nodes.A[i % size];
                int n2 = comparison_nodes.A[j % size];
                similarity_Relation k = similarity_Relation(n1 + 1, n2 + 1);
                similarity_Relation l = similarity_Relation(n2 + 1, n1 + 1);
                if (!Relations.find_elem(k) && !Relations.find_elem(l))
                {
                    bool isrelation = true;

                    // #### CHECKING THE FORWARD PART :- All parents of i have a relation with any parent of j
                    linkedlist<int> *curr_p = inadjacencylist;
                    linkedlist<int> *parentsi = &curr_p[n1];
                    while (parentsi != NULL)
                    {

                        bool found = true; // Variable to find if the relation is found for this parenti
                        linkedlist<int> *curr_q = inadjacencylist;
                        linkedlist<int> *parentsj = &curr_q[n2];
                        while (parentsj != NULL)
                        {
                            similarity_Relation t = similarity_Relation(nodes[parentsi->object].value, nodes[parentsj->object].value);
                            if (Relations.find_elem(t))
                                break;
                            parentsj = parentsj->next;
                        }
                        if (parentsj == NULL)
                        {
                            // This means that we searched for all the parents of j and didnt find any relation (p_i, p_j)
                            // Hence No relation exists for this (i,j).
                            isrelation = false;
                            break;
                        }
                        parentsi = parentsi->next;
                    }

                    if (!isrelation)
                    {
                        continue;
                    }

                    // #### CHECKING THE BACKWARD PART :- All parents of j have a relation with any parent of i
                    linkedlist<int> *c = inadjacencylist;
                    linkedlist<int> *parentsj_ = &c[n2];
                    while (parentsj_ != NULL)
                    {
                        bool found = true; // Variable to find if the relation is found for this parenti
                        linkedlist<int> *d = inadjacencylist;
                        linkedlist<int> *parentsi_ = &d[n1];
                        while (parentsi_ != NULL)
                        {
                            similarity_Relation t = similarity_Relation(nodes[parentsj_->object].value, nodes[parentsi_->object].value);
                            if (Relations.find_elem(t))
                                break;
                            parentsi_ = parentsi_->next;
                        }
                        if (parentsi_ == NULL)
                        {
                            // This means that we searched for all the parents of i and didnt find any relation (p_j, p_i)
                            // Hence No relation exists for this (i,j).
                            isrelation = false;
                            break;
                        }
                        parentsj_ = parentsj_->next;
                    }
                    if (!isrelation)
                    {
                        continue;
                    }
                    Relations.QInsert(k);
                    // cout << "Inserted Relation " << n1 +1 << " " << n2 +1 << " and opp" << endl;
                    Relations.QInsert(l);
                }
            }
        }
    }

    // Function recursively finds the New relations.
    void Find_recursive_Relation(MyVector<similarity_Relation> &Relations, MyVector<int> &visited)
    {
        // cout << "recursion level " << endl;
        if (visited.size() == numNodes)
        // Once all the Nodes are visited then just return from the function
        {
            return;
        }
        // The Nodes that satisfy the criteria would be added to this list and compared.
        MyVector<int> comparison_nodes;

        // For finding the children of this Nodes.
        unsigned int head = visited.head;
        unsigned int tail = visited.tail;

        for (unsigned int i = head; i < tail; i++)
        {
            // Taking a child of this Node
            linkedlist<int> *j = outadjacencylist;
            linkedlist<int> *child = &j[visited.A[i % visited.N] - 1];
            // cout << "Checking for Node " << visited.A[i % visited.N] << endl;
            if (child->object == -1)
            { // Means it has No child
                continue;
            }
            // Iterating over all the Childs
            while (child != NULL)
            {
                bool toadd = true; // Boolean to check whether this child has to be added to the vector or not.
                // Iterating over all the parents of this child and checking whether that parent
                // is visited
                int child_ind = child->object;
                // cout << "The Child is " << child_ind + 1 << endl;
                linkedlist<int> *q = inadjacencylist;
                linkedlist<int> *parent_of_child = &q[child_ind];

                while (parent_of_child != NULL)
                {
                    // If not then we dont add this child in the
                    int p_ind = parent_of_child->object;
                    // cout << "Its parent " << p_ind + 1 << endl;
                    if (!visited.find_elem(nodes[p_ind].value))
                    {
                        toadd = false;
                        break;
                    }
                    parent_of_child = parent_of_child->next;
                }
                if (toadd)
                { // If it has to be added then add to the comparison_nodes vector.
                    if (!visited.find_elem(nodes[child->object].value))
                    {
                        visited.QInsert(nodes[child->object].value);
                        if (!comparison_nodes.find_elem(child->object))
                        {
                            // cout << "Added " << (child->object + 1) << endl;
                            comparison_nodes.QInsert(child->object);
                        }
                    }
                }
                child = child->next;
            }
        }
        Check_relation_and_add(Relations, comparison_nodes);
        Find_recursive_Relation(Relations, visited);
    }

    // Finally add the edge relations
    void add_edge_relations(MyVector<similarity_Relation> &Relations)
    {
        for (int i = 0; i < numNodes; i++)
        {
            if (inadjacencylist[i].next == NULL && (inadjacencylist[i].object != -1))
            {
                similarity_Relation r = similarity_Relation(nodes[i].value, nodes[inadjacencylist[i].object].value);
                Relations.QInsert(r);
            }
        }
    }

    // Collapse the specified Nodes
    void Collapse_Nodes(int a, int b)
    {
        // a > b so collapse the Node b onto a
        for (int i = Edges.head; i < Edges.tail; i++)
        {
            Edges.A[i % Edges.N].replace_elem(b, a);
        }
        // Making the Node value of b as -1 (Effectively making it void)
        nodes[b - 1].value = -1;
    }

    void Collapse_graph()
    { // This function is used to collapse the Graph based on the similarity.
        while (!Relations.isEmpty())
        { // Collapse all the relations untill it is empty
            similarity_Relation a = Relations.get_first();
            Relations.deletefirst();
            int min_ = min(a.n1, a.n2);
            int max_ = max(a.n1, a.n2);
            if (max_ == min_)
            {
                continue;
            }
            Collapse_Nodes(max_, min_);
            for (int i = Relations.head; i < Relations.tail; i++)
            {
                Relations.A[i % Relations.N].replace_elem(min_, max_);
            }
        }
    }

    void printResults()
    {
        graphFile<<endl;
        graphFile << "Source nodes: ";
        sourceNodes->printlist(graphFile);
        graphFile << endl;
        graphFile << endl;
        graphFile << "Similar node pairs: ";
        for (unsigned int i = Relations.head; i < Relations.tail; i++)
        {
            graphFile << "(" << Relations.A[i % Relations.N].n1 << ", " << Relations.A[i % Relations.N].n2 << ") ";
        }
        graphFile << endl
             << endl;
        graphFile << "Collapsed graph:" << endl
             << endl;
        Collapse_graph();
        MyVector<int> Final_Nodes;
        MyVector<similarity_Relation> Final_edges;
        for (int i = 0; i < numNodes; i++)
        {
            if (nodes[i].value != -1)
            {
                Final_Nodes.QInsert(nodes[i].value);
            }
        }
        graphFile << Final_Nodes.size() << ": ";
        // graphFile << outadjacencylist[13].find_ll(15) << endl;

        while (!Final_Nodes.isEmpty())
        {
            int a = Final_Nodes.get_first();
            graphFile << a << " ";
            Final_Nodes.deletefirst();
            for (int i = Final_Nodes.head; i < Final_Nodes.tail; i++)
            {
                int curr_node = Final_Nodes.A[i % Final_Nodes.N];
                // Adding only the edges which will finally exist
                if (Edges.find_elem(similarity_Relation(a, curr_node)))
                {
                    Final_edges.QInsert(similarity_Relation(a, curr_node));
                }
                if (Edges.find_elem(similarity_Relation(curr_node, a)))
                {
                    Final_edges.QInsert(similarity_Relation(curr_node, a));
                }
            }
        }
        graphFile << endl;
        for (int i = Final_edges.head; i < Final_edges.tail; i++)
        {
            graphFile << Final_edges.A[i % Final_edges.N].n1 << " " << Final_edges.A[i % Final_edges.N].n2 << endl;
        }
    }
};

#endif
