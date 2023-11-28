#include <iostream>
#include <fstream>
using namespace std;

/// @brief usual list of objects... no need of explanation here
/// @tparam T data type of the object to be stored in the linked list
template <typename T>
class listOfObjects
{
public:
    T object;
    listOfObjects<T> *next;
    listOfObjects<T> *prev;
    listOfObjects<T> *tail;

    listOfObjects(T initValue)
    {
        object = initValue;
        next = prev = nullptr;
    }
    ~listOfObjects() { ; }
};

/// @brief Node in the graph, stores each and every information corresponding to the node
class Node
{
public:
    int value = 0;
    int eqClass;                 // variable for storing in which equivalence class is the node present
    listOfObjects<Node *> *to;   // to adjacency list
    listOfObjects<Node *> *from; // from adjacency list
    int toCounter = 0;
    int fromCounter = 0;
    bool *similar = nullptr; // similar matrix i.e., matrix  for storing the nodes which are similar
    bool visited = false;    // for recursive function
    Node()
    {
        to = nullptr;
        from = nullptr;
    }
    Node(int n)
    {
        to = nullptr;
        from = nullptr;
        value = n;
    }
    /// @brief function to find the collapsed graph
    /// @param k total no. of nodes in the graph
    /// @param nodes array of nodes of the graph
    /// @param eq equivalence class number
    /// @param index index of the current node in the array
    void collapsed(int k, Node nodes[], int eq, int index)
    {
        visited = true;             // mark the node visited
        eqClass = eq;               // assign the eq class
        for (int i = 0; i < k; i++) // loop and find if it is similar and visit those nodes to assign the same equivalence class
        {
            if (similar[i] && !nodes[i].visited)
            {
                nodes[i].collapsed(k, nodes, eq, i);
            }
            else if (nodes[i].similar[index] && !nodes[i].visited)
            {
                nodes[i].collapsed(k, nodes, eq, i);
            }
        }
    }
};

int main(int argc, char *argv[])
{
    ofstream oo("outGraph.txt");
    int k;
    cin >> k;
    Node nodes[k];
    // initialising the node array
    for (int i = 0; i < k; i++)
    {
        nodes[i].value = i + 1;
        nodes[i].similar = new bool[k];
        for (int j = 0; j < k; j++)
        {
            nodes[i].similar[j] = false;
        }
    }
    // taking the input and filling the adjacency list of the nodes.
    while (true)
    {
        int l, m;
        cin >> l >> m;
        l = l - 1;
        m = m - 1;
        if (l == -2 || m == -2)
        {
            break;
        }
        else if (nodes[l].toCounter == 0 and nodes[m].fromCounter == 0)
        {
            nodes[l].to = new listOfObjects<Node *>(&nodes[m]);
            nodes[l].to->tail = nodes[l].to;
            nodes[m].from = new listOfObjects<Node *>(&nodes[l]);
            nodes[m].from->tail = nodes[m].from;
            nodes[l].toCounter++;
            nodes[m].fromCounter++;
        }
        else if (nodes[l].toCounter == 0)
        {
            nodes[l].to = new listOfObjects<Node *>(&nodes[m]);
            nodes[l].to->tail = nodes[l].to;
            nodes[m].from->tail->next = new listOfObjects<Node *>(&nodes[l]);
            nodes[m].from->tail = nodes[m].from->tail->next;
            nodes[l].toCounter++;
            nodes[m].fromCounter++;
        }
        // when one of the nodes , adjacency list is empty
        else if (nodes[m].fromCounter == 0)
        {
            nodes[m].from = new listOfObjects<Node *>(&nodes[l]);
            nodes[m].from->tail = nodes[m].from;
            nodes[l].to->tail->next = new listOfObjects<Node *>(&nodes[m]);
            nodes[l].to->tail = nodes[l].to->tail->next;
            nodes[l].toCounter++;
            nodes[m].fromCounter++;
        }
        // when both are not wmpty, check whether the node already exists, then insert in it
        else
        {
            nodes[l].to->tail->next = new listOfObjects<Node *>(&nodes[m]);
            nodes[l].to->tail = nodes[l].to->tail->next;
            nodes[m].from->tail->next = new listOfObjects<Node *>(&nodes[l]);
            nodes[m].from->tail = nodes[m].from->tail->next;
            nodes[l].toCounter++;
            nodes[m].fromCounter++;
        }
    }
    // taking the user defined inputs for the similar nodes and assigning the nodes as similar
    while (true)
    {
        int m, n;
        cin >> m >> n;
        m--, n--;
        if (m == -2 || n == -2)
            break;
        else
        {
            nodes[m].similar[n] = true;
        }
    }
    for (int i = 0; i < k; i++)
    {
        // condition 3 of the problem statement. when single parent, child-parent similar
        if (nodes[i].from != nullptr)
        {
            if (nodes[i].from->next == nullptr)
            {
                nodes[i].similar[nodes[i].from->object->value - 1] = true;
            }
        }
        // whole case for the handling in the case when a reflexive simialarity is defined by the user for some node
        if (nodes[i].similar[i] == true)
        {
            // oo << " " << nodes[i].value << endl;
            listOfObjects<Node *> *curr = nodes[i].to;
            bool arr[k];
            int count = 0;
            for (int s = 0; s < k; s++)
            {
                arr[s] = 0;
            }
            while (curr != nullptr)
            {
                // oo << curr->object->from->object->value << endl;
                if (curr->object->from->next == nullptr)
                {
                    nodes[curr->object->value - 1].similar[curr->object->value - 1] = true;
                }
                arr[curr->object->value - 1] = true;
                count++;
                curr = curr->next;
            }
            if (count > 1)
            {
                for (int s = 0; s < k; s++)
                {
                    for (int t = 0; t < k; t++)
                    {
                        if (arr[s] && arr[t] && s != t)
                        {
                            nodes[s].similar[t] = true;
                            nodes[t].similar[s] = true;
                        }
                    }
                }
            }
        }
    }

    // this bool is whether to continue the while loop. there may be cases when after performing one loop, new nodes becomes similar which might affect other nodes and they can also be similar. so the while loop is made
    bool cont = true;
    while (cont)
    {
        // below 2 for loops check for the 2nd condition os the problem statement. when there is a corresponding parent for the other loop for every parent of the first lop and they are similar symmetrically, then the child nodes are also made symmetrically similar
        for (int i = 0; i < k; i++)
        {
            for (int j = 0; j < k; j++)
            {
                listOfObjects<Node *> *curr1 = nodes[i].from;
                listOfObjects<Node *> *curr2 = nodes[j].from;
                bool y = false;
                while (curr1 != nullptr)
                {
                    bool x = false;
                    while (curr2 != nullptr)
                    {
                        if (curr1->object->similar[curr2->object->value - 1])
                        {
                            x = true;
                            break;
                        }
                        curr2 = curr2->next;
                    }
                    if (!x)
                    {
                        y = false;
                        break;
                    }
                    else
                    {
                        y = true;
                    }
                    curr1 = curr1->next;
                }
                curr1 = nodes[i].from;
                curr2 = nodes[j].from;
                if (y)
                {
                    y = false;
                    while (curr2 != nullptr)
                    {
                        bool x = false;
                        while (curr1 != nullptr)
                        {
                            if (curr2->object->similar[curr1->object->value - 1])
                            {
                                x = true;
                                break;
                            }
                            curr1 = curr1->next;
                        }
                        if (!x)
                        {
                            y = false;
                        }
                        else
                        {
                            y = true;
                        }
                        curr2 = curr2->next;
                    }
                }
                if (y)
                {
                    if (!nodes[i].similar[nodes[j].value - 1])
                    {
                        nodes[i].similar[nodes[j].value - 1] = true;
                        cont = true;
                    }
                    else
                    {
                        cont = false;
                    }
                }
                else{
                    cont = false;
                }
            }
        }
    }
    // int for storing the equivalence class no.
    int eq = 0;
    // calling the collapsed function which is not visited even once.
    for (int i = 0; i < k; i++)
    {
        if (!nodes[i].visited)
        {
            nodes[i].collapsed(k, nodes, eq, i);
            eq++;
        }
    }
    Node newnodes[eq];
    bool edgematrix[eq][eq]; // edgematrix for the newly formed graph
    for (int i = 0; i < eq; i++)
    {
        for (int j = 0; j < eq; j++)
        {
            edgematrix[i][j] = false;
        }
    }
    // following lopp add edges between the nodes of the new collapsed graph according to the nodes present in the original graph
    for (int i = k - 1; i >= 0; i--)
    {
        if (newnodes[nodes[i].eqClass].value == 0)
        {
            newnodes[nodes[i].eqClass].value = nodes[i].value;
            listOfObjects<Node *> *curr1 = nodes[i].to, *curr2 = nodes[i].from;
            while (curr1 != nullptr)
            {
                if (curr1->object->eqClass != nodes[i].eqClass)
                {
                    edgematrix[nodes[i].eqClass][curr1->object->eqClass] = true;
                }
                curr1 = curr1->next;
            }
        }
        else if (newnodes[nodes[i].eqClass].value != 0)
        {
            listOfObjects<Node *> *curr1 = nodes[i].to, *curr2 = nodes[i].from;
            while (curr1 != nullptr)
            {
                if (curr1->object->eqClass != nodes[i].eqClass)
                {
                    edgematrix[nodes[i].eqClass][curr1->object->eqClass] = true;
                }
                curr1 = curr1->next;
            }
        }
    }

    // from here, all loops are used to just print the desired outputs
    oo << "Source nodes: ";
    for (int i = 0; i < k; i++)
    {
        if (nodes[i].from == nullptr)
        {
            oo << nodes[i].value << " ";
        }
    }
    oo << endl;
    oo << "Similar Node pairs: ";
    for (int i = 0; i < k; i++)
    {
        for (int j = 0; j < k; j++)
        {
            if (nodes[i].similar[j])
            {
                oo << "(" << nodes[i].value << "," << nodes[j].value << ") ";
            }
        }
    }
    oo << endl;
    oo << "Collapsed Graph:" << endl;
    oo << eq << ":";
    for (int i = 0; i < eq; i++)
    {
        oo << newnodes[i].value << " ";
    }
    oo << endl;
    for (int i = 0; i < eq; i++)
    {
        for (int j = 0; j < eq; j++)
        {
            if (edgematrix[i][j])
            {
                oo << newnodes[i].value << " " << newnodes[j].value << endl;
            }
        }
    }
    oo.close();
}