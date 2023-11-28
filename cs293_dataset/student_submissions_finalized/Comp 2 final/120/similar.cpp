using namespace std;
#include <fstream>
class Graph
{
    int n;        // number of nodes
    int *adj;     // adjacency matrix
    int *source;  // source array
    int *similar; // similar matrix
    int *in;      // number of in edges
    int *dum;     // dummy array
    int *updated; // updated array
    fstream fout; // fstream for output

public:
    Graph(int n)
    {
        fout.open("outgraph.txt", ios::out); // opening output file
        this->n = n;
        adj = new int[n * n];
        source = new int[n];
        updated = new int[n];
        dum = new int[n];
        in = new int[n];
        similar = new int[n * n]; // creating new objects
        for (int i = 0; i < (n * n); i++)
        { // initialising them with zeros
            adj[i] = 0;
            similar[i] = 0;
        }
        for (int i = 0; i < n; i++)
        { // initialising them with zeros
            source[i] = 0;
            in[i] = 0;
            dum[i] = 0;
            updated[i] = 0;
        }
    }
    void addedge(int a, int b)
    {
        adj[((a - 1) * n) + (b - 1)] = 1; // updating adjacency matrix
        source[b - 1] = 1;
        in[b - 1] = in[b - 1] + 1; // increasing number of incoming edges
        dum[b - 1] = a;            // updating dummy variable
        return;
    }
    void updatesimilar()
    {
        for (int i = 0; i < n; i++)
        {
            if (in[i] == 1)
            {
                similar[(i * n) + dum[i] - 1] = 1; // updating similar matrix
            }
        }
        for (int i = 0; i < n; i++)
        {
            for (int j = i + 1; j < n; j++)
            {
                if (check(i + 1, j + 1) && check(j + 1, i + 1)) // using check for checking similarity
                {
                    similar[(i * n) + j] = 1;
                    similar[(j * n) + i] = 1;
                }
            }
        }
        return;
    }
    bool check(int n1, int n2)
    {
        int edges1[n]; // matrix for storing all nodes adjacent to n1 in the graph
        int edges2[n]; // matrix for storing all nodes adjacent to n2 in the graph
        for (int i = 0; i < n; i++)
        {
            edges1[i] = 0;
            edges2[i] = 0;
        }
        int x = 0;
        int y = 0;
        for (int i = 0; i < n; i++)
        {
            if (adj[i * n + n1 - 1] == 1)
            {
                edges1[x] = i + 1; // pushing nodes into the array
                x++;
            }
            if (adj[i * n + n2 - 1] == 1)
            {
                edges2[y] = i + 1; // pushing nodes into array
                y++;
            }
        }
        if (x == 0 || y == 0)
        {
            return false;
        }
        int count = 0; // initialising count of nodes to zeros
        for (int i = 0; i < x; i++)
        {
            int m1 = edges1[i];
            int g = 0;
            for (int j = 0; j < y; j++)
            {
                int m2 = edges2[j];
                if (similar[((m1 - 1) * n) + m2 - 1] == 1) // check for similarity
                {
                    g = 1;
                    break;
                }
            }
            if (g == 1)
            {
                count++; // increasing number of count
            }
            else
            {
                return false;
            }
        }
        if (count == x)
        {
            return true;
        }
        return false;
    }
    void addsimilar(int a, int b)
    {
        similar[((a - 1) * n) + (b - 1)] = 1; // updating similar values
        return;
    }
    void printsource()
    {
        fout << "Source nodes: "; // printing source nodes
        for (int i = 0; i < n; i++)
        {
            if (source[i] == 0)
            {
                fout << i + 1 << " ";
            }
        }
        fout << endl;
        fout << endl;
        fout << "Similar node pairs: "; // printing similar node pairs
        for (int i = 0; i < (n * n); i++)
        {
            if (similar[i] == 1)
            {
                updated[(i / n)] = 2;
                updated[(i % n)] = 2;
                fout << "(" << i / n + 1 << "," << (i % n) + 1 << ")"
                     << " ";
            }
        }
        fout << endl;
        fout << endl;
        return;
    }
    void updatesimilar(int a)
    {
        int n1 = (a / n) + 1;
        int n2 = (a % n) + 1;
        similar[a] = 0;
        int x = n1 + n2;
        if (n2 > n1)
        {
            n1 = n2; // maximum of the two nodes
        }
        n2 = x - n1;
        if (n1 == n2)
        {
            return;
        }
        for (int i = 0; i < n; i++)
        {
            if (adj[((n2 - 1) * n) + i] == 1)
            {
                adj[((n1 - 1) * n) + i] = 1; // collapsing graph with respect to minimum node number(column wise)
                adj[((n2 - 1) * n) + i] = 0;
            }
            if (adj[(i * n) + n2 - 1] == 1)
            {
                adj[(i * n) + n2 - 1] = 0; // collapsing graph with respect to minimum node number (row wise)
                adj[(i * n) + n1 - 1] = 1;
            }
            if (similar[((n2 - 1) * n) + i] == 1)
            {
                similar[((n1 - 1) * n) + i] = 1; // collapsing similar matrix with respect to minimum node number (column wise)
                similar[((n2 - 1) * n) + i] = 0;
            }
            if (similar[(i * n) + n2 - 1] == 1)
            {
                similar[(i * n) + n2 - 1] = 0; // collapsing similar matrix with respect to minimum node number (row wise)
                similar[(i * n) + n1 - 1] = 1;
            }
        }
        updated[n2 - 1] = 1;
        return;
    }
    int find()
    {
        for (int i = 0; i < n * n; i++)
        {
            if (similar[i] == 1)
            {
                return i; // finding first similarity relation
            }
        }
        return -1;
    }
    void collapse()
    {
        if (find() == -1)
        { // base case
            printcollapsed();
            return;
        }
        updatesimilar(find()); // recursive case
        collapse();
        return;
    }
    void printcollapsed()
    {
        int c = 0; // printing collapsed graph
        fout << "Collapsed graph: " << endl;
        for (int i = 0; i < n; i++)
        {
            if (updated[i] == 0 || updated[i] == 2)
            {
                c++;
            }
        }
        fout << c << ": "; // moving to output file
        for (int i = 0; i < n; i++)
        {
            if (updated[i] == 0 || updated[i] == 2)
            {
                fout << i + 1 << " ";
            }
        }
        fout << endl;
        for (int i = 0; i < n * n; i++)
        {
            if (adj[i] == 1)
            {
                if ((i / n) != (i % n))
                {
                    fout << (i / n) + 1 << " " << (i % n) + 1 << endl;
                }
            }
        }
        return;
    }
};