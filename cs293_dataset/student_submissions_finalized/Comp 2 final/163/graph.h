#ifndef GRAPH_H
#define GRAPH_H

#ifndef NODE_H
#include "node.h"
#endif

class Graph
{
public:
    int numNodes = 0;
    Node *nodes = nullptr;
    list<int> *source = nullptr;
    ofstream file;

    Graph(string filename)
    {
        file.open(filename); // Opening output file stream
        cin >> numNodes;
        nodes = new Node[numNodes]; // Array of correct size initialized
        for (int i = 0; i < numNodes; i++)
            nodes[i].setVal(i + 1); // values of nodes initialised
        int node1, node2;
        while (cin >> node1 >> node2) // Reading and inserting edges
        {
            if (node1 == -1 && node2 == -1)
                break;
            nodes[node1 - 1].insertEdge(node2, true);
            nodes[node2 - 1].insertEdge(node1, false);
        }
    }

    void getSourceNodes()
    {
        file << "Source nodes:";
        for (int i = 0; i < numNodes; i++)
        {
            if (nodes[i].fromNode == nullptr) // condition for source node
            {
                file << " " << i + 1;
                if (source == nullptr)
                    source = new list<int>(i + 1);
                else
                {
                    list<int> *s = source;
                    while (s->next != nullptr)
                        s = s->next;
                    s->next = new list<int>(i + 1);
                    s->next->prev = s;
                }
            }
        }
        file << endl;
        file << endl;
    }

    void similarity()
    {
        // When both nodes are source and mentioned.
        int node1, node2;
        while (cin >> node1 >> node2)
        {
            if (node1 == -1 && node2 == -1)
                break;
            if (source->isPresent(node1) && source->isPresent(node2))
            {
                if (!nodes[node1 - 1].similar->isPresent(node2))
                    nodes[node1 - 1].insertSimilar(node2);
                if (!nodes[node1 - 1].similarSymmetric->isPresent(node2))
                    nodes[node1 - 1].insertSimilarSymmetric(node2);
                if (!nodes[node2 - 1].similarSymmetric->isPresent(node1))
                    nodes[node2 - 1].insertSimilarSymmetric(node1);
            }
        }

        // Similar due to only one edge to this nodes
        for (int i = 0; i < numNodes; i++)
        {
            if (nodes[i].fromNode != nullptr && nodes[i].fromNode->next == nullptr)
            {
                nodes[i].insertSimilar(nodes[i].fromNode->object);
                if (!nodes[i].similarSymmetric->isPresent(nodes[i].fromNode->object))
                    nodes[i].insertSimilarSymmetric(nodes[i].fromNode->object);
                if (!nodes[nodes[i].fromNode->object - 1].similarSymmetric->isPresent(i + 1))
                    nodes[nodes[i].fromNode->object - 1].insertSimilarSymmetric(i + 1);
            }
        }

        // Similar due to similar parent
        bool Similarchanged = true;
        while (Similarchanged) // if similarity is not changed in one iteration, then it will not change afterwards either, so process complete
        {
            Similarchanged = false; // By default, assume it will not change
            for (int i = 0; i < numNodes - 1; i++)
            {
                if (source->isPresent(i + 1)) // Only non-source needed
                    continue;
                for (int j = i + 1; j < numNodes; j++)
                {
                    if (nodes[i].similarSymmetric->isPresent(j + 1) || source->isPresent(j + 1)) // Only non-source needed
                        continue;
                    bool foundDissimilarParent1 = false;
                    list<int> *p1 = nodes[i].fromNode; // parent nodes of i
                    while (p1 != nullptr)
                    {
                        bool found = false;
                        list<int> *p2 = nodes[j].fromNode; // parent nodes of j
                        while (p2 != nullptr)
                        {
                            if (nodes[p1->object - 1].similar->isPresent(p2->object))
                            {
                                found = true;
                                break;
                            }
                            p2 = p2->next;
                        }
                        if (!found)
                        {
                            foundDissimilarParent1 = true;
                            break;
                        }
                        p1 = p1->next;
                    }
                    bool foundDissimilarParent2 = false;
                    list<int> *p2 = nodes[j].fromNode; // parent nodes of j
                    while (p2 != nullptr)
                    {
                        bool found = false;
                        list<int> *p1 = nodes[i].fromNode; // parent nodes of i
                        while (p1 != nullptr)
                        {
                            if (nodes[p2->object - 1].similar->isPresent(p1->object))
                            {
                                found = true;
                                break;
                            }
                            p1 = p1->next;
                        }
                        if (!found)
                        {
                            foundDissimilarParent2 = true;
                            break;
                        }
                        p2 = p2->next;
                    }
                    if (!foundDissimilarParent1 && !foundDissimilarParent2) // if both have only similar parents, they are similar
                    {
                        Similarchanged = true; // inserting in similar means similar is changed
                        nodes[i].insertSimilar(j + 1);
                        nodes[j].insertSimilar(i + 1);
                        nodes[i].insertSimilarSymmetric(j + 1);
                        nodes[j].insertSimilarSymmetric(i + 1);
                    }
                }
            }
        }


        // All Similar pairs found. Printing them
        file << "Similar node pairs:";
        for (int i = 0; i < numNodes; i++)
        {
            list<int> *s = nodes[i].similar;
            if (s != nullptr)
            {
                while (s != nullptr)
                {
                    file << " (" << i + 1 << ", " << s->object << ")";
                    s = s->next;
                }
            }
        }
        file << endl;
        file << endl;
    }

    void recursiveCollapse(int index, list<int> *&collapseTail, list<int> *&checked, list<int> *&checkedTail, list<int> *&collapseClassesTail)
    {
        // updating collapse classes and checked lists
        checkedTail->next = new list<int>(index + 1);
        checkedTail = checkedTail->next;
        collapseClassesTail->next = new list<int>(index + 1);
        collapseClassesTail = collapseClassesTail->next;
        list<int> *s = nodes[index].similarSymmetric;
        while (s != nullptr)
        {
            if (!checked->isPresent(s->object)) // if similar node is not checked
            {
                if (collapseTail->object < s->object) // value of collapsed node updated
                    collapseTail->object = s->object;
                recursiveCollapse(s->object - 1, collapseTail, checked, checkedTail, collapseClassesTail); // recursive call made
            }
            s = s->next;
        }
    }

    void collapseGraph()
    {
        list<int> *collapse = new list<int>(-1); // list of nodes in collapsed graph
        list<int> *collapseTail = collapse; // tail of collapse list
        int numCollapse = 0;
        list<int> *checked = new list<int>(-1); // list of nodes that have been checked once (not to be checked again)
        list<int> *checkedTail = checked; // tail of checked list

        list<list<int> *> *collapseClasses = new list<list<int> *>(new list<int>(-1)); // each object is a list of nodes in original graph that collapse to 1 node (same order as in collapse list)
        list<list<int> *> *collapseClassesTail = collapseClasses; // tail of collapseClass list

        for (int i = 0; i < numNodes; i++)
        {
            if (checked->isPresent(i + 1)) // if node is checked, do not check again
                continue;
            // Fresh node means new similar class, so appropriate insertions
            collapseTail->next = new list<int>(i + 1);
            collapseTail = collapseTail->next;
            collapseClassesTail->next = new list<list<int> *>(new list<int>(0));
            collapseClassesTail = collapseClassesTail->next;
            numCollapse++;
            list<int> *colList = collapseClassesTail->object;
            recursiveCollapse(i, collapseTail, checked, checkedTail, colList); // recursive call made to update new collapsed nodes value and also checked and collapseClass lists
        }

        // Info printed
        file << "Collapsed graph:" << endl;
        file << endl;
        file << numCollapse << ":";
        list<int> *temp = collapse->next;
        while (temp != nullptr)
        {
            file << " " << temp->object;
            temp = temp->next;
        }
        file << endl;

        // Indentifying and printing collapsed edges
        list<int> *colNode = collapse->next;
        list<list<int> *> *colClass = collapseClasses->next;
        while (colNode->next != nullptr)
        {
            list<int> *nextColNode = colNode->next;
            list<list<int> *> *nextColClass = colClass->next;
            while (nextColNode != nullptr)
            {
                bool found1 = false;
                bool found2 = false;
                list<int> *i1 = colClass->object->next;
                while (i1 != nullptr)
                {
                    list<int> *i2 = nextColClass->object->next;
                    while (i2 != nullptr)
                    {
                        if (!found1)
                        {
                            // file << "Checking Nodes " << colNode->object << ":" << i1->object << " against " << nextColNode->object << ":" << i2->object << endl;
                            if (nodes[i2->object - 1].fromNode->isPresent(i1->object))
                            {
                                found1 = true;
                                file << colNode->object << " " << nextColNode->object << endl;
                            }
                        }
                        if (!found2)
                        {
                            // file << "Checking Nodes " << nextColNode->object << ":" << i2->object << " against " << colNode->object << ":" << i1->object << endl;
                            if (nodes[i1->object - 1].fromNode->isPresent(i2->object))
                            {
                                found2 = true;
                                file << nextColNode->object << " " << colNode->object << endl;
                            }
                        }
                        i2 = i2->next;
                    }
                    i1 = i1->next;
                }

                nextColNode = nextColNode->next;
                nextColClass = nextColClass->next;
            }
            colNode = colNode->next;
            colClass = colClass->next;
        }
    }
};

#endif