#ifndef GRAPH_BST_CPP
#define GRAPH_BST_CPP

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef GRAPH_BST_H
#include "Graph.h"
#endif

// Runs a modified dfs on one connected component of the graph
void Graph::modifiedDFS_on_cc(int cur, int prev, bool** edges_used) {
    bool cycle = false;  // Is the current node in a cycle
    nodes[cur].visited++;  // Visit the node
    bsts[cc].insert(cur+1, -1);  // Insert the node into BST

    // Visit the nodes not visited twice along edges that haven't been traversed 
    // in the opposite direction by dfs i.e. from next->cur
    for (int i=0; i<nodes[cur].num_edges; i++) {
        
        int next = nodes[cur].edges[i];
        cycle |= (nodes[next].visited == 2 && !edges_used[next][cur]);
        if (nodes[next].visited == 2 || edges_used[next][cur]) continue;
        edges_used[cur][next] = true;
        modifiedDFS_on_cc(next, cur, edges_used);
        cycle |= nodes[next].cycle;
    }

    if (cycle) nodes[cur].cycle = true;
}

void Graph::modifiedDFS() {
    // Keep track the edges used by dfs and in which direction
    bool* edges_used[numNodes];
    for (int i=0; i<numNodes; i++) edges_used[i] = new bool[numNodes];

    // Keep doing dfs until there's no node unvisited
    for (int i=0; i<numNodes; i++) {
        if (!nodes[i].visited) {
            modifiedDFS_on_cc(i, -1, edges_used);
            cc++;
        }
        if (nodes[i].visited == 1) once++;
        else twice++;
    }
}

void Graph::printResults() {
    // Printing number of connected components
    cout << "No. of connected components: " << cc << '\n';

    // Printing the nodes visited once
    cout << "No. of nodes visited once: " << once << " (";
    int k {once};
    for (int i=0; i<numNodes; i++) {
        if (nodes[i].visited == 1) {
            cout << i+1, k--;
            if (k) cout << ",";
        }
    }
    cout << ")\n";

    // Printing the nodes visited twice
    cout << "No. of nodes visited twice: " << twice << " (";
    k = twice;
    for (int i=0; i<numNodes; i++) {
        if (nodes[i].visited == 2) {
            cout << i+1, k--;
            if (k) cout << ",";
        }
    }
    cout << ")\n";

    // Counting total number of nodes in cycles
    int cycle_nodes {0};
    for (int i=0; i<numNodes; i++) {
        if (nodes[i].visited == 1) continue;
        cycle_nodes += nodes[i].cycle;
    }
    // Printing number of nodes in cycles
    cout << "No. of nodes that are present in a cycle: " << cycle_nodes << " (";
    k = cycle_nodes;
    for (int i=0; i<numNodes; i++) {
        if (nodes[i].visited == 1) continue;
        if (nodes[i].cycle) {
            cout << i+1, k--;
            if (k) cout << ",";
        }
    }
    cout << ")\n";

    // Printing BSTs
    for (int i=0; i<cc; i++) {
        bsts[i].printBST("");
        cout << endl;
    }
}


// Same as in lab 4
bool BST::insert(int JourneyCode, int price) {
    // Create the new node
    TreeNode* new_node = new TreeNode { JourneyCode, price };
    new_node->parent = nullptr;

    // Inserting at the root
    if (!root) {
        root = new_node;
        return true;
    }

    // Insert at the right place
    TreeNode* cur { root };
    while (true) {
        if (JourneyCode > cur->JourneyCode) {
            if (cur->right) cur = cur->right;
            else {
                cur->right = new_node;
                new_node->parent = cur;
                return true;
            }
        } else {
            if (cur->left) cur = cur->left;
            else {
                cur->left = new_node;
                new_node->parent = cur;
                return true;
            }
        }
    }
}

// Same as in lab 4
void BST::printBST(const string& prefix, bool isLeft)
{
    if( root != nullptr )
    {
        cout << prefix;

        cout << (isLeft ? "|--" : "|__" );

        // print the value of the node
        cout << root->JourneyCode << endl;
        TreeNode *curr = root;
        root = root->left;
        // enter the next tree level - left and right branch
        printBST( prefix + (isLeft ? "│   " : "    "), true);
        root = curr->right;
        printBST( prefix + (isLeft ? "│   " : "    "), false);
        root = curr;
    }
}

#endif