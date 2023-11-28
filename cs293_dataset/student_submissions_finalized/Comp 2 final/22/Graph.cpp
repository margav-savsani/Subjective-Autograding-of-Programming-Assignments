#ifndef GRAPH_BST_CPP
#define GRAPH_BST_CPP

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef GRAPH_BST_H
#include "Graph.h"
#endif

// C++ program for Merge Sort
#include <iostream>
using namespace std;

// Merges two subarrays of array[].
// First subarray is arr[begin..mid]
// Second subarray is arr[mid+1..end]
void merge(int array[], int const left, int const mid,
           int const right)
{
    auto const subArrayOne = mid - left + 1;
    auto const subArrayTwo = right - mid;

    // Create temp arrays
    auto *leftArray = new int[subArrayOne],
         *rightArray = new int[subArrayTwo];

    // Copy data to temp arrays leftArray[] and rightArray[]
    for (auto i = 0; i < subArrayOne; i++)
        leftArray[i] = array[left + i];
    for (auto j = 0; j < subArrayTwo; j++)
        rightArray[j] = array[mid + 1 + j];

    auto indexOfSubArrayOne = 0,   // Initial index of first sub-array
        indexOfSubArrayTwo = 0;    // Initial index of second sub-array
    int indexOfMergedArray = left; // Initial index of merged array

    // Merge the temp arrays back into array[left..right]
    while (indexOfSubArrayOne < subArrayOne && indexOfSubArrayTwo < subArrayTwo)
    {
        if (leftArray[indexOfSubArrayOne] <= rightArray[indexOfSubArrayTwo])
        {
            array[indexOfMergedArray] = leftArray[indexOfSubArrayOne];
            indexOfSubArrayOne++;
        }
        else
        {
            array[indexOfMergedArray] = rightArray[indexOfSubArrayTwo];
            indexOfSubArrayTwo++;
        }
        indexOfMergedArray++;
    }
    // Copy the remaining elements of
    // left[], if there are any
    while (indexOfSubArrayOne < subArrayOne)
    {
        array[indexOfMergedArray] = leftArray[indexOfSubArrayOne];
        indexOfSubArrayOne++;
        indexOfMergedArray++;
    }
    // Copy the remaining elements of
    // right[], if there are any
    while (indexOfSubArrayTwo < subArrayTwo)
    {
        array[indexOfMergedArray] = rightArray[indexOfSubArrayTwo];
        indexOfSubArrayTwo++;
        indexOfMergedArray++;
    }
    delete[] leftArray;
    delete[] rightArray;
}

// begin is for left index and end is
// right index of the sub-array
// of arr to be sorted */
void mergeSort(int array[], int const begin, int const end)
{
    if (begin >= end)
        return; // Returns recursively

    auto mid = begin + (end - begin) / 2;
    mergeSort(array, begin, mid);
    mergeSort(array, mid + 1, end);
    merge(array, begin, mid, end);
}

void Graph::connectedComps(int index, DynamicQueue<int> *set)
{
    visited[index] = true;
    Node currNode = nodes[index];
    int *similarList = currNode.similarNodes.returnArray();

    set->QInsert(index);

    for(int i=0;i<currNode.similarNodes.size();i++)
    {
        if(!visited[similarList[i]])connectedComps(similarList[i], set);
    }
    return;
}

void Graph::compressGraph()
{
    for (int i = 0; i < numNodes; i++)
    {
        if (!visited[i])
        {
            DynamicQueue<int> *set = new DynamicQueue<int>;
            connectedComps(i, set);

            int *A = set->returnArray();
            mergeSort(A, 0, set->size()-1);

            int head = A[set->size()-1];
            for(int j=0;j<set->size();j++)
            {
                nodes[A[j]].head = head;
            }
            condensedGraph.QInsert(head);
        }
    }

    for(int i=0;i<numNodes;i++)
    {
        int *a = nodes[i].adjacencyList.returnArray();
        int s = nodes[i].adjacencyList.size();

        for(int j=0;j<s;j++)
        {
            if(nodes[i].head != nodes[a[j]].head)
            {
                Pair p(nodes[i].head, nodes[a[j]].head);
                condensedGraphEdges.QInsert(p);
            }
        }
    }

}

void Graph::similarNodes()
{
    DynamicQueue<Pair> tmp = similars;
    while (!tmp.isEmpty())
    {
        Pair p;
        tmp.QDelete(&p);
        int node1 = p.a, node2 = p.b;
        int *aj1 = nodes[node1].adjacencyList.returnArray(), s1 = nodes[node1].adjacencyList.size();
        int *aj2 = nodes[node2].adjacencyList.returnArray(), s2 = nodes[node2].adjacencyList.size();

        if (tmp.isPresent(Pair(node2, node1)))
        {
            for (int i = 0; i < s1; i++)
            {
                for (int j = 0; j < s2; j++)
                {
                    Pair *q = new Pair(aj1[i], aj2[j]);
                    Pair *q2 = new Pair(aj2[j], aj1[i]);
                    tmp.QInsert(*q);
                    tmp.QInsert(*q2);
                    similars.QInsert(*q);
                    similars.QInsert(*q2);
                    nodes[aj1[i]].similarNodes.QInsert(aj2[j]);
                    nodes[aj2[j]].similarNodes.QInsert(aj1[i]);
                }
            }
        }
        if (!nodes[node1].cond3done)
        {
            for (int i = 0; i < s1; i++)
            {
                if (nodes[aj1[i]].inCount == 1)
                {
                    Pair *q = new Pair(aj1[i], node1);
                    nodes[node1].similarNodes.QInsert(aj1[i]);
                    nodes[aj1[i]].similarNodes.QInsert(node1);
                    tmp.QInsert(*q);
                    similars.QInsert(*q);
                }
            }
            nodes[node1].cond3done = true;
        }

        if (!nodes[node2].cond3done)
        {
            for (int i = 0; i < s2; i++)
            {
                if (nodes[aj2[i]].inCount == 1)
                {
                    Pair *q = new Pair(aj2[i], node2);
                    nodes[node2].similarNodes.QInsert(aj2[i]);
                    nodes[aj2[i]].similarNodes.QInsert(node2);
                    tmp.QInsert(*q);
                    similars.QInsert(*q);
                }
            }
            nodes[node2].cond3done = true;
        }
    }
}

void Graph::printResults()
{
    cout << "Source Nodes: ";
    int *s = sourceNodes.returnArray();
    for (int i = 0; i < sourceNodes.size(); i++)
    {
        cout << nodes[s[i]].value << " ";
    }
    cout << "\n";

    cout << "Similar node pairs: ";
    Pair *pairs = similars.returnArray();
    for (int i = 0; i < similars.size(); i++)
    {
        pairs[i].printPair();
        cout << " ";
    }
    cout << "\n";

    cout<<"Collapsed graph:\n";
    cout<<condensedGraph.size()<<": ";
    int *a = condensedGraph.returnArray();
    for(int i=0;i<condensedGraph.size();i++)
    {
        cout<<nodes[a[i]].value<<" ";
    }
    cout<<endl;
    Pair *ps = condensedGraphEdges.returnArray();
    int size = condensedGraphEdges.size();
    for(int i=0;i < size;i++)
    {
        Pair p = ps[i];
        cout<<nodes[p.a].value<<" "<<nodes[p.b].value<<endl;
    }
}
#endif