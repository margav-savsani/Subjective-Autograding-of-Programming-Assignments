#include <iostream>
#include <vector>
using namespace std;

class Graph
{ // class to store info about Graph .
public:
    int num_nodes; // equals number of nodes in the graph .
    int num_edges; // equals number of edges in the graph .
    vector<vector<int>> adjacency;
    bool **matrix; // boolean matrix of size n+1 x n+1 .
    Graph(int n1, int n2)
    { // constructor
        num_nodes = n1;
        num_edges = n2;
        matrix = new bool *[n1 + 1];
        for (int i = 0; i <= n1; i++)
        {
          matrix[i] = new bool[n1 + 1];
        }
    }
    ~Graph() { ; } // desturctor
    bool similar(vector<int> a, vector<int> b, int c, int d)
    { // function which checks whether two nodes were similar or not .
        int i = 0;
        int j = 0;
        for (i = 0; i < a.size(); i++)
        {
            if (c == a[i])
                break;
        }
        for (j = 0; j < b.size(); j++)
        {
            if (d == b[j])
                break;
        }
        if (i == j && i < a.size())
        {
            return true; // returns true if similar
        }
        else
        {
            return false; // returns false if not similar
        }
    }
};
bool check(vector<int> task1, int j)
{ // this function whether the node j is present in the vector or not .
    if (task1.size() == 0)
        return true;
    for (int i = 0; i < task1.size(); i++)
    {
        if (j == task1[i])
        {
            return false; // returns true if not present .
        }
    }
    return true; // returns false if present .
}

int main()
{
    int numnodes;     // num of nodes .
    int numedges = 0; // num of edges initially equals to zero .
    cin >> numnodes;
    vector<int> source; // vector to store sources .
    vector<int> dest;   // vector to store destinations .
    while (true)
    {
        int n1;
        int n2;
        cin >> n1 >> n2; // input of edges .
        if ((n1 <= 0 || n1 > numnodes || n2 <= 0 || n2 > numnodes) && (n1 != -1) && (n2 != -1))
        {
            cout << "Invalid Input" << endl;
        }
        if (n1 == -1 && n2 == -1)
        {
            break;
        }
        source.push_back(n1); // updating source vector
        dest.push_back(n2);   // updating destination vector
        numedges++;           // updating number of edges .
    }
    Graph mygraph(numnodes, numedges); // defining a class named as mygraph .
                                       //  mygraph.adjacency[0].push_back(0);
    // for (int i = 0; i < source.size(); i++)
    // {
    //     mygraph.adjacency[source[i]].push_back(dest[i]); // updating the adjacency vector .
    // }
    for (int i = 0; i < numnodes + 1; i++)
    {
        for (int j = 0; j < numnodes + 1; j++)
        {
           // mygraph.matrix[i][j] = false; // initializing the boolean matrix .
        }
    }

    vector<int> task1; // this vector stores all the source nodes .
    for (int i = 0; i < source.size(); i++)
    {
        int v = source[i];
        int y = 0;
        for (int j = 0; j < dest.size(); j++)
        {
            if (v == dest[j])
            {
                y++;
            }
        }
        if (y == 0)
        {
            bool fn = check(task1, v);
            if (fn)
            {
                task1.push_back(v); // updating the source node vector .
            }
        }
    }
    for (int i = 1; i <= numnodes; i++)
    {
        int x = 0;
        int y = 0;
        for (int j = 0; j < source.size(); j++)
        {
            if (i == source[j])
            {
                x++;
            }
        }
        for (int j = 0; j < dest.size(); j++)
        {
            if (i == dest[j])
            {
                y++;
            }
        }
        if (x == 0 && y == 0)
        {
            bool fn = check(task1, i); // checking whether the node is already present in the vector or not .
            if (fn)
            {
                task1.push_back(i); // if not present then the vector gets updated .
            }
        }
    }
    vector<int> similar_source; // vector to store similar source nodes .
    vector<int> similar_dest;   // vector to store similar destination nodes .
    int n = 0 ;
    while (true)
    {
        int n1;
        int n2;
        cin >> n1 >> n2;
        if ((n1 <= 0 || n1 > numnodes || n2 <= 0 || n2 > numnodes) && (n1 != -1) && (n2 != -1))
        {
            cout << "Invalid Input" << endl;
        }
        if (n1 == -1 && n2 == -1)
        {
            break;
        }
      //  mygraph.matrix[n1][n2] = true;
        similar_source.push_back(n1); // updating the vector .
        similar_dest.push_back(n2);   // updating the vector .
    }
    int *array;
    array = new int[numedges];
    for (int i = 0; i < numedges; i++)
    {
        array[i] = 0;
        for (int j = 0; j < numedges; j++)
        {
            if (i == j)
            {
                continue;
            }
            else
            {
                if (dest[i] == dest[j])
                {
                    array[i]++;
                }
            }
        }
    }
    int x = 0;
    for (x = 0; x < numedges; x++)
    {
        if (array[x] == 0)
        {
           // mygraph.matrix[dest[x]][source[x]] = true;
            similar_source.push_back(dest[x]); // updating the vector similar_source .
            similar_dest.push_back(source[x]); // updating the vector similar_dest .
        }
    }

    //////////////////////////////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////    OUTPUT   /////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////////////////////////////

    cout << endl;
    cout << "Expected Output :-" << endl; // Start of the output
    cout << endl;
    cout << "Source nodes : ";
    for (int k = 0; k < task1.size(); k++)
    {
        cout << task1[k] << " ";
    }
    cout << endl;
    cout << endl;
    cout << "Similar node pairs : ";
    for (int j = 0; j < similar_dest.size(); j++)
    {
        cout << "(" << similar_source[j] << "," << similar_dest[j] << ")";
    }
    cout << endl;
    cout << endl;
    cout<<"Collapsed Graph : "<<endl;

    for (int i = 0; i < source.size(); i++)
    {
        mygraph.adjacency[source[i]].push_back(dest[i]); // updating the adjacency vector .
    }
    
}