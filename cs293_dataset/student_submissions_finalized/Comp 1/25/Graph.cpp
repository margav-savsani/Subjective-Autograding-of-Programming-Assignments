#ifndef GRAPH_BST_CPP
#define GRAPH_BST_CPP

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef GRAPH_BST_H
#include "Graph.h"
#endif

void Graph::modifiedDFS()
{
    for (int i = 0; i < numNodes; i++)
    {
        if (nodes[i].visited==0)
        {
            DFS_visit(i);
            connectedComponents++; // A new connected component discovered
            treeCount++; // A new tree created for a new connected component
        }
    }
    return;
}

void Graph::DFS_visit(int x)
{
    nodes[x].color=Grey;
    nodes[x].visited++;

    // Insert into the tree
    trees[treeCount].insert(x + 1);

    for (int i=0; i<nodes[x].neighbours; i++) {
        int neighbour = nodes[x].adjacent[i];
        if (nodes[neighbour].visited==0){
            // If the node is unvisited, then we visit it
            nodes[neighbour].parent1 = x;
            DFS_visit(neighbour);
        }
        else if (nodes[x].parent1!=neighbour && nodes[x].parent2!=neighbour && nodes[neighbour].color!=Black){
            // the node encountered is visited, but it should not be the parent of the current node
            // It should not be black, because then it has no chance of being in a cycle
            if (nodes[neighbour].visited == 1){
                nodes[neighbour].parent2 = x;
                nodes[neighbour].cycle = 1;
                DFS_visit(neighbour);
            }
            else {
                // backtrack and make identify nodes in the cycle
                int current = x;
                while (current!=neighbour){
                    nodes[current].cycle = true;
                    // parent
                    current = (nodes[current].parent2==-1 ? nodes[current].parent1 : nodes[current].parent2);
                }
            }
        }
    }
    nodes[x].color = Black;
}

void Graph::printResults()
{
    int once = 0, twice = 0;
    int cycle = 0;
    for (int i=0; i<numNodes; i++) {
        if (nodes[i].visited==1){
            once++;
        }
        else if (nodes[i].visited==2){
            twice++;
        }
        if (nodes[i].cycle){
            cycle++;
        }
    }
    cout<<"No of connected components = "<<connectedComponents<<endl;
    cout<<"No. of nodes visited once: "<< once<<endl;
    cout<<"No. of nodes visited twice: "<< twice<<endl;
    cout<<"No. of nodes that are present in a cycle: "<<cycle<<endl;
    cout<<"BSTs\n====================="<<endl;
    for (int i=0; i<treeCount; i++) {
        trees[i].printBST("");
        cout<<"=====================\n";
    }
    return;
}

#endif
