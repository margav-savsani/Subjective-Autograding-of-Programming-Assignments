#ifndef GRAPH_BST_CPP
#define GRAPH_BST_CPP

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef GRAPH_BST_H
#include "Graph.h"
#endif

// Add code as appropriate for your implementation
void Graph::modifiedDFS()
{
    int connected_component_number = 1;
    for (int i = 0; i < numNodes; i++)
    {
        // Performing DFS if the node is not visited
        if (nodes[i].visited == 0)
        {
            connected_components++;
            // Our helper function would put the data in the NodesTree
            BST NodesTree;
            DFSHelper(i, NodesTree);
            cout << endl
                 << "BST for Connected Component number " << connected_component_number << endl
                 << endl;
            connected_component_number++;
            NodesTree.printBST();
        }
        // This point is reached after DFS is performed on the connected component of a node
        if (nodes[i].visited == 1)
        {
            singly_visited++;
        }
        if (nodes[i].in_a_cycle)
        {
            Nodes_in_cycles++;
        }
    }

    return;
}

void Graph::DFSHelper(int i, BST &NodesTree)
{
    // inserting to stack
    S->insert(i);

    // S->print(); We could print the stack for visualisation

    // Inserting to tree
    NodesTree.insert(i + 1);
    nodes[i].visited++;
    listOfObjects<int> *L = adjacency[i];
    while (L != nullptr)
    {
        // We find locations at which the adjacent node is present in the stack
        //  If it is present just previour to our current node we do not visit it
        int loc_at_stack = S->find_from_first(L->object);
        int loc2 = S->find_from_last(L->object);

        // This is for finding cycles
        // If we reach a node that is already in the stack and is not a parent 
        // all the nodes in between that node and the current node are present in a cycle
        if (loc_at_stack != -1 && S->arr[loc_at_stack + 1] != i && S->arr[loc2 + 1] != i)
        {
            int *a = S->arr;
            // all nodes between these are in a cycle
            for (int i = loc_at_stack; i <= S->top; i++)
            {
                nodes[a[i]].in_a_cycle = true;
            }
        }

        // If the adjacent node is not visited twice
        if (nodes[L->object].visited != 2)
        {
            // If it is not a parent
            if (S->find_from_first(L->object) == -1 || S->arr[S->find_from_first(L->object) + 1] != i)
            {
                // Recursively calling DFS
                DFSHelper(L->object, NodesTree);
            }
        }

        L = L->next;
    }
    // Removing from the Stack
    S->remove();
}

void Graph::printResults()
{
    cout << "No. of connected components " << connected_components << endl;
    cout << "No. of Nodes visited once " << singly_visited << endl;
    cout << "No. of Nodes visited twice " << numNodes - singly_visited << endl;
    cout << "No. of Nodes in a cycle " << Nodes_in_cycles << endl;
}

#endif
