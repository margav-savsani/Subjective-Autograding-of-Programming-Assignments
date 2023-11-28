#ifndef GRAPH_BST_CPP
#define GRAPH_BST_CPP

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef GRAPH_BST_H
#include "Graph.h"
#endif

// Add code as appropriate for your implementation

void recursiveDFS(Node *x, Node *parent, int *visited, bool *backtraced, list<Node *> *stack, int linkToCycle, int numNodes, BST *tree, int &numNodesVisitOnce, int &numNodesVisitTwice)
{
    // cout << "Entering Node: " << x->value << "------------------------" << endl;
    visited[x->value - 1]++;
    list<Node *> *w = x->adjacency;
    while (w != nullptr)
    {
        // cout << "Before if, linkToCycle: " << linkToCycle << endl;
        if (visited[w->object->value - 1] < 2 && w->object->value != parent->value && backtraced[w->object->value - 1] == false && linkToCycle != w->object->value)
        {
            if (visited[w->object->value - 1] == 0)
                numNodesVisitOnce++;
            else
            {
                numNodesVisitOnce--;
                numNodesVisitTwice++;
            }
            list<Node *> *s = stack;
            int l = -1;
            // cout << "stack: ";
            while (s->next != nullptr)
            {
                // cout << s->next->object->value << "  ";
                if (s->next->object->value == w->object->value)
                    l = s->object->value;
                s = s->next;
            }
            // if (l == w->object->value) {w = w->next; continue;}
            s->next = new list<Node *>(new Node(w->object->value));
            s->next->prev = s;
            tree->insert(w->object->value);
            // cout << endl << "Inserted " << w->object->value << ", linkToCycle: " << l << endl;
            recursiveDFS(w->object, x, visited, backtraced, stack, l, numNodes, tree, numNodesVisitOnce, numNodesVisitTwice);
            w->object->removeAdjacency(x->value);
            x->removeAdjacency(w->object->value);
            s->next = nullptr;
        }
        w = w->next;
    }
    // x->removeAdjacency(parent->value);
    // parent->removeAdjacency(x->value);
    // cout << "Exiting Node: " << x->value << "------------------------" << endl;
}

void Graph::modifiedDFS()
{
    int visited[numNodes] = {0};
    bool backtraced[numNodes] = {false};
    list<Node *> *stack = new list<Node *>(new Node(-1));
    list<BST *> *tree = nullptr;
    for (int i = 0; i < numNodes; i++)
    {
        if (visited[i] == 0)
        {
            numConnectedComponents++;
            numNodesVisitOnce++;
            stack->next = new list<Node *>(new Node(i + 1));
            stack->next->prev = stack;
            if (trees == nullptr)
            {
                trees = new list<BST *>(new BST(i + 1));
                tree = trees;
            }
            else
            {
                tree->next = new list<BST *>(new BST(i + 1));
                tree = tree->next;
            }
            recursiveDFS(&nodes[i], new Node(-1), visited, backtraced, stack, -1, numNodes, tree->object, numNodesVisitOnce, numNodesVisitTwice);
            stack->next = nullptr;
        }
    }
}

void Graph::printResults()
{
    cout << "No. of connected components: " << numConnectedComponents << endl;
    cout << "No. of nodes visited once: " << numNodesVisitOnce << endl;
    cout << "No. of nodes visited twice: " << numNodesVisitTwice << endl;
    cout << "No. of nodes that are present in a cycle: " << numNodesVisitTwice << endl;
    int i = 0;
    list<BST *> *tree = trees;
    while (tree != nullptr)
    {
        cout << endl;
        cout << "Tree No.: " << ++i << endl;
        tree->object->printBST();
        tree = tree->next;
    }
}

#endif
