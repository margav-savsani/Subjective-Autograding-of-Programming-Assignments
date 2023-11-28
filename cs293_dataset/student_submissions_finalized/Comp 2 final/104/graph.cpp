#include <iostream>
#include <fstream>
#include "graph.h"
using namespace std;

// helper function to insert at the head of listOfObjects
template <typename T>
void insertAtHead(listOfObjects<T> *&ptr, T x)
{
    if (ptr == nullptr)
    {
        ptr = new listOfObjects<T>(x);
    }
    else
    {
        listOfObjects<T> *temp = ptr;
        ptr = new listOfObjects<T>(x);
        ptr->next = temp;
        temp->prev = ptr;
    }
}

// helper function to insert at the tail of listOfObjects
template <typename T>
void insertAtTail(listOfObjects<T> *&ptr, T x)
{
    if (ptr == nullptr)
    {
        ptr = new listOfObjects<T>(x);
    }
    else
    {
        listOfObjects<T> *temp = ptr;

        while (temp->next != nullptr)
        {
            temp = temp->next;
        }

        temp->next = new listOfObjects<T>(x);
        temp->next->prev = temp;
    }
}

Graph::Graph(int numberOfNodes)
{
    numNodes = numberOfNodes; // setting number of nodes

    nodes = new Node[numNodes]; 
    source = new bool[numNodes];
    edges = new bool[numNodes * numNodes]; // 2D arrays
    relations = new bool[numNodes * numNodes]; // 2D arrays

    // initializing edges and relations to false
    for (int i = 0; i < numberOfNodes; ++i)
    {
        for (int j = 0; j < numNodes; ++j)
        {
            edges[i * numNodes + j] = false;
            relations[i * numNodes + j] = false;
        }
    }

    // initializing values of nodes and sources as true
    for (int i = 0; i < numNodes; ++i)
    {
        nodes[i].value = i + 1;
        source[i] = true;
    }

    int from, to;

    cin >> from >> to;

    // getting input of edges
    while (from != -1 && to != -1)
    {   
        // setting incoming and outgoing edges of nodes
        insertAtHead(nodes[from - 1].outgoing, to); // outgoing edge for "from"
        insertAtHead(nodes[to - 1].incoming, from); // incoming edge for "to"
        source[to - 1] = false; // as incoming edge is there, make source as false for that node

        edges[(from - 1) * numNodes + (to - 1)] = true; // setting edge "from" ==> "to"

        nodes[from - 1].numOutgoing = nodes[from - 1].numOutgoing + 1; // incrementing number of outgoing edges
        nodes[to - 1].numIncoming = nodes[to - 1].numIncoming + 1; // incrementing number of incoming edges

        cin >> from >> to;
    }

    cin >> from >> to;

    // getting input of source relations
    while (from != -1 && to != -1)
    {
        relations[(from - 1) * numNodes + (to - 1)] = true;

        cin >> from >> to;
    }
}

// this is where we will find all the relations between node
// also we will find a closure of relations and make them an equivalence relation
void Graph::principle()
{   
    // this is condition 3 of relations specified in problem statement
    // If n1 has a single incoming edge from n2, and there are no other incoming
    // edges of n1, then n1 and n2 are said to be similar
    for (int i = 0; i < numNodes; ++i)
    {
        if (nodes[i].numIncoming == 1)
        {
            relations[i * numNodes + (nodes[i].incoming->object) - 1] = true;
        }
    }

    
    // Summary of algorithm to check relations of type-1 in problem statement

    // 1. Initially mark all source nodes as visited.
    // 2. Find the nodes such that, all the parents of these nodes should
    //    be in the visited nodes. Call these nodes a layer.
    // 3. All the relations of type-2 can only be present between nodes of layer
    //    or a node of layer and another node which is visited.
    // 4. Pick 2 nodes from the layer at a time and check if they are related.
    // 5. For every node in layer, iterate over all the visited nodes and check
    //    if they are related.
    // 6. Mark the  nodes in the layer as visited.
    // 7. Repeat this process until all the nodes are visited.

    bool *visited = new bool[numNodes];

    // setting visited to true if it is a source node, else false
    for (int i = 0; i < numNodes; ++i)
    {
        if (source[i])
        {
            visited[i] = true;
        }
        else
        {
            visited[i] = false;
        }
    }

    // looping until every node is visited
    while (true)
    {

        listOfObjects<int> *currLayer = nullptr;

        for (int i = 0; i < numNodes; ++i)
        {   
            // if node is already visited then, no need to check if it's present in layer. It won't be
            if (visited[i])
            {
                continue;
            }

            listOfObjects<int> *parents = nodes[i].incoming;

            bool isInLayer = true;

            // checking if all the parents of the node lie in the layer or not
            while (parents != nullptr)
            {
                if (!visited[parents->object - 1])
                {
                    isInLayer = false;
                    break;
                }

                parents = parents->next;
            }

            if (isInLayer == false)
            {
                continue;
            }

            // if conditions satisfied then inserrt it into layer
            insertAtHead(currLayer, i + 1);
        }

        listOfObjects<int> *temp1 = currLayer;

        // choosing 2 layer nodes at a time and checking if they are related
        while (temp1 != nullptr)
        {
            listOfObjects<int> *temp2 = currLayer;

            while (temp2 != nullptr)
            {   
                // to avoid redundant checks
                if(temp2->object > temp1->object){
                    temp2 = temp2->next;
                    continue;
                }

                bool isTrueForThisPair = true;

                listOfObjects<int> *incomingOf1 = nodes[temp1->object - 1].incoming;

                // checking if for all parents of temp1
                // if there is a related parent of temp2
                while (incomingOf1 != nullptr)
                {
                    bool isTrueForThisParent = false;
                    listOfObjects<int> *incomingOf2 = nodes[temp2->object - 1].incoming;

                    while (incomingOf2 != nullptr)
                    {
                        if (relations[(incomingOf1->object - 1) * numNodes + (incomingOf2->object - 1)])
                        {
                            isTrueForThisParent = true;
                            break;
                        }

                        incomingOf2 = incomingOf2->next;
                    }

                    if (isTrueForThisParent == false)
                    {
                        isTrueForThisPair = false;
                        break;
                    }

                    incomingOf1 = incomingOf1->next;
                }

                listOfObjects<int> *incomingOf2 = nodes[temp2->object - 1].incoming;

                // checking if for all parents of temp2
                // if there is a related parent of temp1
                while (incomingOf2 != nullptr)
                {
                    bool isTrueForThisParent = false;
                    listOfObjects<int> *incomingOf1 = nodes[temp1->object - 1].incoming;

                    while (incomingOf1 != nullptr)
                    {
                        if (relations[(incomingOf2->object - 1) * numNodes + (incomingOf1->object - 1)])
                        {
                            isTrueForThisParent = true;
                            break;
                        }

                        incomingOf1 = incomingOf1->next;
                    }

                    if (isTrueForThisParent == false)
                    {
                        isTrueForThisPair = false;
                        break;
                    }

                    incomingOf2 = incomingOf2->next;
                }

                // if above conditions are satisfied, then make relation as true
                // this is a symmetric realtion, so making true for both
                if (isTrueForThisPair)
                {
                    relations[(temp1->object - 1) * numNodes + (temp2->object - 1)] = true;
                    relations[(temp2->object - 1) * numNodes + (temp1->object - 1)] = true;
                }

                temp2 = temp2->next;
            }

            temp1 = temp1->next;
        }

        // checking if node in layer is related to a priorly visited node

        temp1 = currLayer;

        while (temp1 != nullptr)
        {   
            // looping over all priorly visiteed node
            // logic is exactly same as done above
            // just that here we are looping over a different set
            for(int x=0; x<numNodes; ++x)
            {   

                if(visited[x] == false){
                    continue;
                }

                bool isTrueForThisPair = true;

                listOfObjects<int> *incomingOf1 = nodes[temp1->object - 1].incoming;

                while (incomingOf1 != nullptr)
                {
                    bool isTrueForThisParent = false;
                    listOfObjects<int> *incomingOf2 = nodes[x].incoming;

                    while (incomingOf2 != nullptr)
                    {
                        if (relations[(incomingOf1->object - 1) * numNodes + (incomingOf2->object - 1)])
                        {
                            isTrueForThisParent = true;
                            break;
                        }

                        incomingOf2 = incomingOf2->next;
                    }

                    if (isTrueForThisParent == false)
                    {
                        isTrueForThisPair = false;
                        break;
                    }

                    incomingOf1 = incomingOf1->next;
                }

                listOfObjects<int> *incomingOf2 = nodes[x].incoming;

                while (incomingOf2 != nullptr)
                {
                    bool isTrueForThisParent = false;
                    listOfObjects<int> *incomingOf1 = nodes[temp1->object - 1].incoming;

                    while (incomingOf1 != nullptr)
                    {
                        if (relations[(incomingOf2->object - 1) * numNodes + (incomingOf1->object - 1)])
                        {
                            isTrueForThisParent = true;
                            break;
                        }

                        incomingOf1 = incomingOf1->next;
                    }

                    if (isTrueForThisParent == false)
                    {
                        isTrueForThisPair = false;
                        break;
                    }

                    incomingOf2 = incomingOf2->next;
                }
                
                // if conditions are satisfied, then make relation as true
                // symmetric relation
                if (isTrueForThisPair)
                {
                    relations[(temp1->object - 1) * numNodes + (x)] = true;
                    relations[(x) * numNodes + (temp1->object - 1)] = true;
                }
            }

            temp1 = temp1->next;
        }

        listOfObjects<int> *chk = currLayer;

        // making current layer as visited
        while(chk != nullptr){
            visited[chk->object-1] = true;
            chk = chk->next;
        }

        // exit logic
        // if all nodes are visited then exit the while loop
        bool isDone = true;
        for (int i = 0; i < numNodes; ++i)
        {
            if (visited[i] == false)
            {
                isDone = false;
                break;
            }
        }

        if (isDone)
        {
            break;
        }
    }

    // here we will take closure of relations
    // firstly all the reflexive and symmetric relations will be marked
    // then transitive closure will be taken using Warshall's algorithm

    bool *pOld = new bool[numNodes * numNodes];

    // copying of realtions
    for (int i = 0; i < numNodes; ++i)
    {
        for (int j = 0; j < numNodes; ++j)
        {
            pOld[i * numNodes + j] = relations[i * numNodes + j];
        }
    }

    // marking reflexive and symmetric closure
    for (int i = 0; i < numNodes; ++i)
    {   
        pOld[i*numNodes + i] = true;
        for (int j = 0; j < numNodes; ++j)
        {
            if (pOld[i * numNodes + j])
            {
                pOld[j * numNodes + i] = true;
            }
        }
    }

    // Warshall's algorithm
    // all the transitive closures of relations are marked here
    for (int k = 0; k < numNodes; ++k)
    {
        bool *pNew = new bool[numNodes * numNodes];
        for (int i = 0; i < numNodes; ++i)
        {
            for (int j = 0; j < numNodes; ++j)
            {
                pNew[i * numNodes + j] = pOld[i * numNodes + j] || (pOld[i * numNodes + k] && pOld[k * numNodes + j]);
            }
        }

        pOld = pNew;
    }

    // we have got the closure
    afterClosure = pOld;
}

// here we will collapse the nodes
// mark the lexicographically largest node in relation as representative for all
void Graph::afterClosureThings()
{   
    ofstream file("outGraph.txt");

    file << endl << "Source Nodes: ";

    for (int i = 0; i < numNodes; ++i)
    {
        if (source[i])
        {
            file << i + 1 << " ";
        }
    }

    bool *isCollapsed = new bool[numNodes]; // array to store if the node is collapsed or not
    bool *superNodes = new bool[numNodes]; // to store which are the super nodes
    int *parentNode = new int[numNodes]; // to store representative nodes of eachj node

    bool *newEdges = new bool[numNodes * numNodes]; // will contain edges between representative node

    // initializing all newEdges as false
    for (int i = 0; i < numNodes; ++i)
    {
        for (int j = 0; j < numNodes; ++j)
        {
            newEdges[i * numNodes + j] = false;
        }
    }

    // intializing other stuff
    for (int i = 0; i < numNodes; ++i)
    {
        isCollapsed[i] = false;
        superNodes[i] = false;
        parentNode[i] = -1;
    }

    // iterating over all nodes
    // if they are collapsed then do nothing
    // if they are not collapsed, then collapse whole of equivalence class containing that node

    for (int i = 0; i < numNodes; ++i)
    {
        if (isCollapsed[i])
        {
            continue;
        }

        int sup;

        // finding the representative node for this class
        for (int j = numNodes - 1; j >= 0; --j)
        {
            if (afterClosure[i * numNodes + j])
            {
                sup = j;
                break;
            }
        }

        // setting representative node as true
        superNodes[sup] = true;

        // setting this node as representative for all the nodes present in this equivalence class
        for (int j = 0; j < numNodes; ++j)
        {
            if (afterClosure[i * numNodes + j])
            {
                parentNode[i] = sup;
                isCollapsed[i] = true;
            }
        }
    }

    // iterating over all the nodes
    // and setting inter equivalence class edges

    for(int i=0; i<numNodes; ++i){
        listOfObjects<int> *temp = nodes[i].outgoing;

        while(temp != nullptr){

            // checking if this edge is between the same equivalence class
            if(parentNode[i] != parentNode[temp->object-1]){
                newEdges[parentNode[i]*numNodes + parentNode[temp->object-1]] = true;
            }

            temp = temp->next;
        }
    }

    // after this is just printing

    file << endl << endl
         << "Similar node pairs: ";

    for (int i = 0; i < numNodes; ++i)
    {
        for (int j = 0; j < numNodes; ++j)
        {
            if (relations[i * numNodes + j])
            {   
                file << "(" << i + 1 << "," << j + 1 << ") ";
            }
        }
    }

    file << endl << endl
         << "Collapsed graph : " << endl;

    int count = 0;

    for (int i = 0; i < numNodes; ++i)
    {
        if (superNodes[i])
        {
            count++;
        }
    }

    file << count << ": " ;

    for (int i = 0; i < numNodes; ++i)
    {
        if (superNodes[i])
        {
            file << i+1 << " ";
        }
    }
    file << endl;

    for (int i = 0; i < numNodes; ++i)
    {
        if (superNodes[i])
        {
            for(int j=0; j<numNodes; ++j){
                if(newEdges[i*numNodes+j]){
                    file << i+1 << " " << j+1 << endl;
                }
            }
        }
    }
}
