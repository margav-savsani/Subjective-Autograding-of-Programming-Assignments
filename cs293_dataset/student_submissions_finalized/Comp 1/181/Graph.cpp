#ifndef GRAPH_BST_CPP
#define GRAPH_BST_CPP

#ifndef STD_HEADERS_H
#include "std_headers.h"
using namespace std;
#endif
#include <algorithm>
#include <vector>
#ifndef GRAPH_BST_H
#include "Graph.h"
#endif
Node g;
Node v;
// Add code as appropriate for your implementation
void Graph::modifiedDFS()
{

    for (int i = 0; i < numNodes; i++)
    {
        if (nodes[i].isvisited == 0)
        {
            vector<int> k;
            nodes[i].isvisited++;
            tree[i].insert(nodes[i].value);
            g=nodes[i];
            k.push_back(nodes[i].value);
            modifiedDFS(nodes[i], i, k);
            k.pop_back();
        }
    }
    return;
}
void Graph::modifiedDFS(Node a, int r, vector<int> k)
{
    vector<int> j;
    for (int i = 0; i < nodes[a.value - 1].adjacencynumbers; i++)
    {
        if (nodes[nodes[a.value - 1].adjacent[i].value - 1].isvisited == 0)
        {
            nodes[nodes[a.value - 1].adjacent[i].value - 1].isvisited++;
            tree[r].insert(nodes[a.value - 1].adjacent[i].value);
            v=nodes[nodes[a.value - 1].adjacent[i].value - 1];
            k.push_back(nodes[a.value - 1].adjacent[i].value);
            modifiedDFS(nodes[a.value - 1], nodes[nodes[a.value - 1].adjacent[i].value - 1], r, k);
            k.pop_back();
        }
        else
        {
            j.push_back(i);
        }
    }
    for (int i = 0; i < j.size(); i++)
    {
        if (nodes[nodes[a.value - 1].adjacent[j[i]].value - 1].isvisited == 1)
        {
            nodes[nodes[a.value - 1].adjacent[j[i]].value - 1].isvisited++;
            tree[r].insert(nodes[nodes[a.value - 1].value - 1].adjacent[j[i]].value);
            v=nodes[nodes[a.value - 1].adjacent[i].value - 1];
            k.push_back(nodes[a.value - 1].adjacent[i].value);
            modifiedDFS(nodes[a.value - 1], nodes[nodes[a.value - 1].adjacent[j[i]].value - 1], r, k);
            k.pop_back();
        }
    }
}
void Graph::modifiedDFS(Node b, Node a, int r, vector<int> k)
{
    vector<int> j;
    for (int i = 0; i < nodes[a.value - 1].adjacencynumbers; i++)
    {
        if (nodes[b.value - 1].value == nodes[a.value - 1].adjacent[i].value)
        {
        }
        else
        {
            if (nodes[nodes[a.value - 1].adjacent[i].value - 1].isvisited == 0)
            {
                nodes[nodes[a.value - 1].adjacent[i].value - 1].isvisited++;
                tree[r].insert(nodes[nodes[a.value - 1].value - 1].adjacent[i].value);
                int l = find(k.begin(), k.end(), nodes[a.value - 1].adjacent[i].value) - k.begin();
                for (int h = l; h < k.size(); h++)
                {
                    nodes[k[h] - 1].isincycle = true;
                    nodes[nodes[a.value - 1].adjacent[i].value - 1].isincycle = true;
                }
                if(nodes[nodes[a.value-1].adjacent[i].value-1].value==g.value&&a.value==v.value){continue;}
                k.push_back(nodes[a.value - 1].adjacent[i].value);
                modifiedDFS(nodes[a.value - 1], nodes[nodes[a.value - 1].adjacent[i].value - 1], r, k);
                k.pop_back();
            }
            else
            {
                j.push_back(i);
            }
        }
    }
    for (int i = 0; i < j.size(); i++)
    {
        if (nodes[a.value - 1].adjacent[j[i]].value == nodes[b.value - 1].value)
        {
        }
        else
        {
            if (nodes[nodes[a.value - 1].adjacent[j[i]].value - 1].isvisited == 1)
            {
                nodes[nodes[a.value - 1].adjacent[j[i]].value - 1].isvisited++;
                tree[r].insert(nodes[a.value - 1].adjacent[j[i]].value);
                int l = find(k.begin(), k.end(), nodes[a.value - 1].adjacent[i].value) - k.begin();
                for (int h = l; h < k.size(); h++)
                {
                    nodes[k[h] - 1].isincycle = true;
                    nodes[nodes[a.value - 1].adjacent[i].value - 1].isincycle = true;
                }
                if(nodes[nodes[a.value-1].adjacent[i].value-1].value==g.value&&a.value==v.value){continue;}
                k.push_back(nodes[a.value - 1].adjacent[j[i]].value);
                modifiedDFS(nodes[a.value - 1], nodes[nodes[a.value - 1].adjacent[j[i]].value - 1], r, k);
                k.pop_back();
            }
        }
    }
}
void Graph::printResults()
{
    int k = 0;
    for (int i = 0; i < numNodes; i++)
    {
        if (tree[i].root != nullptr)
        {
            k++;
        }
    }
    cout << "No. of connected components:" << k << endl;
    k = 0;
    for (int i = 0; i < numNodes; i++)
    {
        if (nodes[i].isvisited == 1)
        {
            k++;
        }
    }
    cout << "No. of nodes visited once:" << k << endl;
    k = 0;
    for (int i = 0; i < numNodes; i++)
    {
        if (nodes[i].isvisited == 2)
        {
            k++;
        }
    }
    cout << "No. of nodes visited twice:" << k << endl;
    k = 0;
    for (int i = 0; i < numNodes; i++)
    {
        if (nodes[i].isincycle&&nodes[i].adjacencynumbers>1)
            k++;
    }
    cout << "No. of nodes that are present in a cycle:" << k << endl;
    for (int i = 0; i < numNodes; i++)
    {
        tree[i].printBST("");
    }
    return;
}

bool BST::insert(int price)
{
    TreeNode *t = new TreeNode(price);
    if (root == NULL)
    {
        root = t;
        return true; // adds at root if its null
    }
    TreeNode *temp = new TreeNode();
    temp = root;
    while (temp != NULL)
    {
        if (temp->price >= price) // if less than root goes to left
        {
            if (temp->left == NULL)
            {
                TreeNode *t = new TreeNode(price, NULL, NULL, temp); // new node if its null before
                temp->left = t;
                return true;
            }
            else
                temp = temp->left;
        }
        else if (temp->price < price) // if greater than root goes to right subtree
        {
            if (temp->price == price)
            {
                return false; // returns false if it already exists
            }
            if (temp->right == NULL)
            {
                TreeNode *t = new TreeNode(price, NULL, NULL, temp);
                temp->right = t; // creating new node if the position is null
                return true;
            }
            else
            {
                temp = temp->right;
            }
        }
    }
    return false;
}

#endif
