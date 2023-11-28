#ifndef GRAPH_BST_CPP
#define GRAPH_BST_CPP

#include <cstddef>
#include <iostream>
#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef GRAPH_BST_H
#include "Graph.h"
#endif

// Add code as appropriate for your implementation
void Graph::modifiedDFS() {

    bool isFinished = false;
    B = new Linklist<BST*>();
    int initial = 0;
    while (!isFinished) {
        B->object = new BST();
        currectedComponent++;
        Linklist<int>* path = new Linklist<int>;
        path->object = initial;
        visitDFS(initial, B->object, path);
        isFinished = true;

        for (int i = 0; i < numNodes; i++) {
            if (nodes[i].visit == 0) {
                isFinished = false;
                initial = i;
            }
        }
        if (!isFinished) {
            B->prev = new Linklist<BST*>();
            B->prev->next = B;
            B = B->prev;
        }
    }
}

void Graph::printResults() {
    for (int i = 0; i < numNodes; i++) {
        if (nodes[i].visit == 1) visitedOne++;
        if (nodes[i].visit == 2) visitedTwice++;
        if (nodes[i].isInCycle) inloop++;
    }
    // counting BST
    cout << "Number of connected components is : " << currectedComponent << endl;
    cout << "No. of nodes visited once : " << visitedOne << endl;
    cout << "No. of nodes visited twice : " << visitedTwice << endl;
    cout << "No. of nodes that are present in a cycle: " << inloop << endl;
    while (B != nullptr) {
        B->object->printBST("");
        B = B->next;
        cout << "-------------------------" << endl;
    }
}

void Graph::visitDFS(int N, BST* B, Linklist<int>* path, int parent) {
    if (nodes[N].visit >= 2) return;
    nodes[N].visit++;
    path->next = new Linklist<int>;
    path->next->prev = path;
    path = path->next;

    B->insert(nodes[N].value);
    Linklist<int>* curr = nodes[N].adjacency;
    curr = nodes[N].adjacency;
    bool isInCycle = false;
    while (curr != nullptr) {
        if (nodes[curr->object].visit == 1 and nodes[N].visit == 1) {
            Linklist<int>* currNode = path->prev;
            while (currNode->object != curr->object) {
                nodes[currNode->object].isInCycle = true;
                currNode = currNode->prev;
            }
        }
        if (curr->object != parent) {
            path->object = N;
            nodes[N].out = curr->object;
            if (nodes[curr->object].out >= 0 and nodes[curr->object].out != N) {
                nodes[curr->object].isInCycle = true;
            }
            visitDFS(curr->object, B, path, N);
        }

        curr = curr->next;
    }
}
#endif
