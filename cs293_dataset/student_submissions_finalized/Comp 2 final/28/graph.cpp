#include <iostream>
using namespace std;
#include <fstream>

class ll // class for linked list
{
public:
    int value;
    ll *next;
    ll *prev;
    ll()
    {
        value = -1;
        next = prev = nullptr;
    }
    ll(int val)
    {
        value = val;
        next = prev = nullptr;
    }
    int getsize()  //getting size of the linked list
    {
        int s = 1;
        ll *curr = next;
        while (curr != nullptr)
        {
            s++;
            curr = curr->next;
        }
        return s;
    }
};

class Node // class for node
{
public:
    int value;
    ll *outadjacent;
    ll *inadjacent;
    int component = -1;
    Node()  //constructors
    {
        value = -1;
        inadjacent = outadjacent = nullptr;
    }
    Node(int val)
    {
        value = val;
        inadjacent = outadjacent = nullptr;
    }
};

class Graph
{
public:
    int numNodes;
    int numEdges;
    Node *nodes;
    bool **similarity;   //similar checking matric
    bool **is_upadated;  //used for memoization
    int *components; // number of components
    bool *visited;   // if visited during DFS finally
    int c = 0;
    ofstream o;
    Graph(int nNodes)
    {
        o.open("outgraph.txt");
        numNodes = nNodes;
        nodes = new Node[nNodes];
        similarity = new bool *[nNodes];
        is_upadated = new bool *[nNodes];  //updating
        components = new int[nNodes];
        visited = new bool[nNodes];

        for (int i = 0; i < nNodes; i++)
        {
            nodes[i].value = i + 1;
            similarity[i] = new bool[nNodes];
            is_upadated[i] = new bool[nNodes];
            components[i] = -1;
            visited[i] = false;
        }
        for (int i = 0; i < nNodes; i++)
        {
            for (int j = 0; j < nNodes; j++)
            {
                similarity[i][j] = false;
                is_upadated[i][j] = false;
            }
        }
        while (true)
        {
            int x, y;

            cin >> x >> y;
            if (x == -1 || y == -1)
                break;
            ll *curr = nodes[x - 1].outadjacent;
            if (curr == nullptr)
                nodes[x - 1].outadjacent = new ll(y);
            else
            {
                while (curr->next != nullptr)
                {
                    curr = curr->next;
                }
                curr->next = new ll(y);
            }
            ll *curr1 = nodes[y - 1].inadjacent;
            if (curr1 == nullptr)
                nodes[y - 1].inadjacent = new ll(x);
            else
            {
                while (curr1->next != nullptr)
                {
                    curr1 = curr1->next;
                }
                curr1->next = new ll(x);
            }
        }
    }
    bool updatematrix(int i, int j)  //a recursive function to update the matrix of similarity
    {
        if (is_upadated[i][j])
            return similarity[i][j];

        ll *curr1 = nodes[i].inadjacent;

        if (nodes[i].inadjacent == nullptr && nodes[j].inadjacent == nullptr)
        {
            is_upadated[i][j] = true;
            similarity[i][j] = false;
            return false;
        }
        bool b1 = true;
        while (curr1 != nullptr)
        {
            bool found = false;
            ll *curr2 = nodes[j].inadjacent;
            while (curr2 != nullptr)
            {
                if (updatematrix(curr1->value - 1, curr2->value - 1))
                {
                    found = true;
                    break;
                }
                curr2 = curr2->next;
            }
            if (!found)
            {
                b1 = false;
                break;
            }
            curr1 = curr1->next;
        }
        if (!b1)
        {
            is_upadated[i][j] = true;
            similarity[i][j] = b1; // can write directly
            return false;
        }
        curr1 = nodes[j].inadjacent;

        while (curr1 != nullptr)
        {
            bool found = false;
            ll *curr2 = nodes[i].inadjacent;
            while (curr2 != nullptr)
            {
                if (updatematrix(curr1->value - 1, curr2->value - 1))
                {
                    found = true;
                    break;
                }
                curr2 = curr2->next;
            }
            if (!found)
            {
                b1 = false;
                break;
            }
            curr1 = curr1->next;
        }
        is_upadated[i][j] = true;
        similarity[i][j] = b1;
        return b1;
    }
    void getsimilarity()  //this function updates the similariuty
    {
        while (true)
        {
            int x, y;
            cin >> x >> y;
            if (x == -1 || y == -1)
                break;
            similarity[x - 1][y - 1] = true;
            is_upadated[x - 1][y - 1] = true;
        }
        for (int i = 0; i < numNodes; i++)
        {
            if (nodes[i].inadjacent != nullptr)
            {
                if (nodes[i].inadjacent->getsize() == 1)
                {
                    similarity[i][nodes[i].inadjacent->value - 1] = true;
                    is_upadated[i][nodes[i].inadjacent->value - 1] = true;
                }
            }
        }
        for (int i = 0; i < numNodes; i++)
        {
            for (int j = 0; j < numNodes; j++)
            {
                if (!is_upadated[i][j])
                {
                    updatematrix(i, j);
                }
            }
        }
    }
    void DFS(int i, int c)  //a modified DFS to update the components of the graph 
    {
        components[i] = c;
        visited[i] = true;
        for (int j = 0; j < numNodes; j++)
        {
            if (similarity[i][j] || similarity[j][i])
            {
                if (!visited[j])
                    DFS(j, c);
            }
        }
    }
    void getcollapsed() // getting collapsed graph
    {
        c = 0;
        for (int i = numNodes - 1; i >= 0; i--)
        {
            if (!visited[i])
            {
                c++;
                DFS(i, c);
            }
        }
    }
    void getedges() // for printing the edges
    {
        bool a[c][c];
        for (int i = 0; i < c; i++)
        {
            for (int j = 0; j < c; j++)
            {
                a[i][j] = false;
            }
        }
        for (int i = 0; i < c; i++)
        {
            for (int j = 0; j < numNodes; j++) // iterating over all
            {
                if (components[j] == i + 1)
                {
                    ll *curr = nodes[j].inadjacent;
                    while (curr != nullptr)
                    {
                        if ((components[curr->value - 1] != components[j]))
                        {
                            if (!a[components[curr->value - 1] - 1][components[j] - 1])
                            {
                                o << getmax(components[curr->value - 1]) << " " << getmax(components[j]);
                                o << endl;
                            }
                            a[components[curr->value - 1] - 1][components[j] - 1] = true;
                        }

                        curr = curr->next;
                    }
                }
            }
        }
    }
    int getmax(int c) // for retruning maximum value of the component
    {
        for (int j = numNodes - 1; j >= 0; j--)
        {
            if (components[j] == c)
            {
                return (j + 1);
            }
        }
        return 0;
    }
    void printsource() // main printing function for printing all the values
    {
        o << "Source nodes: ";
        for (int i = 0; i < numNodes; i++)
        {
            if (nodes[i].inadjacent == nullptr)
                o << i + 1 << " ";
        }
        o << endl;
        o << "Similar node pairs: ";
        for (int i = 0; i < numNodes; i++)
        {
            for (int j = 0; j < numNodes; j++)
            {
                if (similarity[i][j])
                    o << '(' << i + 1 << ',' << j + 1 << ')' << ' ';
            }
        }
        o << endl;
        getcollapsed();
        int c1 = c;
        o << "Collapsed graph:" << endl;
        o << c << ": ";
        while (c1 > 0)
        {
            // for (int j = numNodes - 1; j >= 0; j--)
            // {
            //     if (components[j] == c1)
            //     {
            //         o << j + 1 << " ";
            //         c1--;
            //     }
            // }
            o << getmax(c1) << ' ';
            c1--;
        }
        o << endl;
        getedges();
    }
};
