template <typename T>
class listOfObjects
{
public:
    T object;
    listOfObjects<T> *next;
    listOfObjects<T> *prev;

    // Constructor
    listOfObjects(T initValue)
    {
        object = initValue;
        next = prev = nullptr;
    }

    // Destructor
    ~listOfObjects() { ; }
};

class Node
{

public:
    int value; // store value of the node
    listOfObjects<int> *incoming; // store incoming edges to the node
    listOfObjects<int> *outgoing; // store outgoing edges from the node

    int numIncoming; // number of incoming edges
    int numOutgoing; // number of outgoing edges

    Node()
    {
        value = 0;
        incoming = nullptr;
        outgoing = nullptr;
        numIncoming = 0;
        numOutgoing = 0;
    }
};

class Graph
{
public:
    int numNodes; // number of nodes present in the graph
    bool *source; // to mark if the node is a source
    Node *nodes; // array of nodes in the graph
    bool *edges; // 2D array to mark edges between nodes
    bool *relations; // 2D array to mark relations between nodes
    bool *afterClosure; // 2D array of realtions formed after taking closure

    Graph(int numberOfNodes);

    void principle(); // function which does the majority of calculation and takes closure
    void afterClosureThings(); // this function works after taking closure
};