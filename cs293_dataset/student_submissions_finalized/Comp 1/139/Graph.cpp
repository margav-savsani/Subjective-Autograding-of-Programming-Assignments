#ifndef GRAPH_BST_CPP
#define GRAPH_BST_CPP

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef GRAPH_BST_H
#include "Graph.h"
#endif

bool BST::insert(int value)
{
    TreeNode *y = nullptr;
    TreeNode *x = this->root;
    // traversing through the tree (x as the place about to be inserted, y as parent of the x).
    while (x != nullptr)
    {
        y = x;
        if (value <= x->value)
        {
            x = x->left;
        }
        else
        {
            x = x->right;
        }
    }
    // constructing new element:
    TreeNode *about_to_insert;
    about_to_insert = new TreeNode(value);
    about_to_insert->parent = y;
    // first element to be added(root even not defined, we have to insert root).
    if (y == nullptr)
    {
        this->root = about_to_insert;
    }
    // else,adding new element depending upon parent node
    else if (about_to_insert->value <= y->value)
    {
        y->left = about_to_insert;
    }
    else if (about_to_insert->value > y->value)
    {
        y->right = about_to_insert;
    }
    return true;
}

void BST::printBST(const string &prefix, bool isLeft = false)
{
    if (root != nullptr)
    {
        cout << prefix;

        cout << (isLeft ? "|--" : "|__");

        // print the value of the node
        cout << root->value << endl;
        TreeNode *curr = root;
        root = root->left;
        // enter the next tree level - left and right branch
        printBST(prefix + (isLeft ? "│   " : "    "), true);
        root = curr->right;
        printBST(prefix + (isLeft ? "│   " : "    "), false);
        root = curr;
    }
}

void Graph::Cycles(Node *node, Node *parent, int &count)
{
    // if node done complete 2 visits
    if (node->color == 2)
        return;

    // node's first visit only
    // backtrack parents to find complete cycle.
    if (node->color == 1)
    {
        // v is a list to store all the vertices present in cycle.
        list<Node *> v;
        // increasing the count of cycles.
        count++;
        v.push_back(parent);
        // creeping all the way to ancestor and inserting all nodes to vector.
        Node *creep = parent;
        while (creep != node)
        {
            creep = creep->parent;
            v.push_back(creep);
        }
        cycles.push_back(v);
        return;
    }
    // updating parent
    node->parent = parent;

    // first visit
    node->color = 1;

    // simple dfs on graph
    for (auto const &i : node->a)
    {
        // if it has not been visited previously
        if (i->value == node->parent->value)
            continue;

        // recusrsion
        Cycles(i, node, count);
    }

    // second visit
    node->color = 2;
}

void insert(vector<Node *> &a, Node *node)
{
    bool b = true;
    // checking in vector if it exists or not.
    for (auto const &i : a)
    {
        if (node->value == i->value)
        {
            b = false;
            break;
        }
    }
    if (b)
        a.push_back(node);
}

int Graph::computeCycles(int &count)
{
    vector<Node *> nodes_present_in_cycles;
    // inserting all nodes present in cycles list into a seperate vector distinctly
    for (int i = 0; i < count; i++)
    {
        for (int j = 0; j < cycles.size(); j++)
        {
            for (auto const &node : cycles[j])
                insert(nodes_present_in_cycles, node);
        }
    }
    // returning the size of the vector.
    return nodes_present_in_cycles.size();
}

// TODO:
void visit(Node *node, BST *tree)
{
    tree->insert(node->value);
}

void DFS(Node *node, Node *parent, BST *tree)
{
    // increasing the no.of visits.
    node->visits++;
    // visiting function, which odes the main aim of DFS. In our case, inserting the value of the node in BST.
    visit(node, tree);
    // iterating through all adjacent nodes of the current node.
    for (auto const &i : node->adj)
    {
        // implementing our modified function.
        if (i->visits < 2)
        {
            // popping out the node if present from the mauplating copy of list of adjacent nodes of the curr node i.
            i->adj.remove(node);
            // recursion
            DFS(i, node, tree);
        }
    }
}

void Graph::modifiedDFS()
{
    // iterating through all nodes in the array and calling the DFS recursive function.
    for (int i = 0; i < numNodes; i++)
    {
        // if the adjacent list and its original copy are the same, then only calling the recursive function.
        if (nodes[i].adj == nodes[i].a)
        {
            if (nodes[i].visits < 2)
            {
                // appending tree to list pf trees and calling DFS function followed by increasing the no.of connected components
                BST *tree = new BST();
                DFS(&nodes[i], nullptr, tree);
                trees.push_back(tree);
                conn++;
            }
        }
    }
}

void Graph::printResults()
{
    cout << "No. of connected components: " << conn << endl;
    // computing the number of nodes visited once,twice:
    int numOnce = 0, numTwice = 0;
    for (int i = 0; i < numNodes; i++)
    {
        if (nodes[i].visits == 1)
            numOnce++;
        else if (nodes[i].visits == 2)
            numTwice++;
    }
    cout << "No. of nodes visited once: " << numOnce << endl;
    cout << "No. of nodes visited twice: " << numTwice << endl;

    // computing total no.of nodes in cycles:
    int c = 0;
    Cycles(&nodes[1], &nodes[0], c);
    cout << "No. of nodes that are present in a cycle: " << computeCycles(c) << endl;

    // printing all the BSTs:
    for (auto const &i : trees)
        i->printBST("");
}

#endif