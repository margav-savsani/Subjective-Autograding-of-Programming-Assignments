#include <iostream>
#include <fstream>
#include <string>

using namespace std;

ofstream out("outgraph.txt");           //The file to read into

class AdjacencyList                     //Linked List
{
 public:
    int value;                          //value stored in linked list
    AdjacencyList *Next;                //Next of linked list

    AdjacencyList(int value)            //constructor with value
    {
        this->value = value;
        Next = nullptr; 
    }

    void insert(int x)                  //Inserting into list
    {
        if (Next == nullptr) Next = new AdjacencyList(x);
        else Next->insert(x);
    }

    bool search(int x)                  //Searching for x in the list
    {
        if (Next == nullptr) return (value == x);
        else return Next->search(x);
    }

};

class GraphNode                         //The graphnode class
{
 public:
    int value;                          //Number of that node in the graph
    int no_of_after = 0;                //No of outgoing edges
    AdjacencyList *Adjacent;            //Linked list of outgoing edges
    AdjacencyList *Previous;            //Linked list of incoming edges
    int no_of_prev = 0;                 //No of incoming edges    
    bool sink = false;                  //If sink then true, else it is false

    GraphNode()                         //Default constructor fofr the graph node
    {
        value = -1;
    }

    GraphNode(int value)                //constructor with given value
    {
        this->value = value;
        Adjacent = nullptr;
    }

    void set_value(int value)           //Setting value at that node of that graph
    {
        this->value = value;
        Adjacent = nullptr;
    }

    void Add_adjacent(int n)            //Add an adjacent node to the given node
    {
        if (Adjacent == nullptr) Adjacent = new AdjacencyList(n);
        else Adjacent->insert(n);
    }

    void Add_previous(int n)            //Add a previous node to the given node
    {
        if (Previous == nullptr) Previous = new AdjacencyList(n);
        else Previous->insert(n);
    }

    void is_sink() {sink = true;}       //Updates the sink property

};

class Graph                             //Graph class(The main Aramageddon)
{
 public:
    GraphNode* Nodes;                   //Array of all the nodes
    int **AdjcencyMatrix;               //Adjacency matrix of similar nodes
    int *visited;                       //Replaced array after collapsing similar ones
    int no_of_nodes;                    //No of nodes in that graph

    Graph(int n)                        //Constructor with no of nodes
    {
        no_of_nodes = n;
        Nodes = new GraphNode[n];
        visited = new int[n];
        AdjcencyMatrix = new int*[n];
        for (int i = 0; i < n; i++)
        {
            visited[i] = -1;
            Nodes[i].set_value(i+1);
            AdjcencyMatrix[i] = new int[n];
            for (int j = 0; j < n; j++) AdjcencyMatrix[i][j] = 0;
        }
    }
    
    bool check_similar(int a, int b)    //Checks if nodes with indices a and b are similar according to property 2
    {
        AdjacencyList* prevA = Nodes[a].Previous;
        //List of prev of node a
        AdjacencyList* prevB = Nodes[b].Previous;
        //List of prev of node b

        if (prevA == nullptr || prevB == nullptr) return false;
        //Checks if any of then is source

        while(prevA != nullptr)         //Going through every ingoing edge of a
        {
            bool ans = false;
            
            AdjacencyList* temp = prevB;
            while(temp != nullptr)      //Going through every incoming edge of b
            {
                if (AdjcencyMatrix[prevA->value][temp->value] == 1) 
                //Checking if they are similar
                {
                    ans = true; 
                    break;
                }
                temp = temp->Next;
            }

            if (!ans) return ans;

            prevA = prevA->Next;
        }
        return true;
    }

    void Add_similar(int a, int b)      //Add similar node a, b
    {
        AdjcencyMatrix[a][b] = 1;
    }

    void get_similar_nodes(int a, int b)//Getting similar nodes down to a, b
    {
        out << " (" << a+1 << ", " << b+1 << ")";
        //Printing it first
        Add_similar(a, b);              //Adding similar edge             

        AdjacencyList *nextA = Nodes[a].Adjacent;
        AdjacencyList *nextB = Nodes[b].Adjacent;

        while(nextA != nullptr)         //Going through every edge from a
        {
            int new_a = nextA->value;
            AdjacencyList *Temp = nextB;

            while(Temp != nullptr)      //Going through every edge of b
            {
                if (check_similar(new_a, Temp->value))
                {
                    if (check_similar(Temp->value, new_a))
                    //chekcing if they are similar by condition 2
                    {
                        get_similar_nodes(new_a, Temp->value);
                        get_similar_nodes(Temp->value, new_a);
                        //Recursive calling
                    }
                }
                Temp = Temp->Next;
            }
            nextA = nextA->Next;
        }
    }

    
    void DFS(int m, int n)              //Does DFS on the graph and updates the visited array
    {
        visited[m] = n;
        for (int i = 0; i < no_of_nodes; i++)
        {
            if ((AdjcencyMatrix[i][m] == 1 || AdjcencyMatrix[m][i] == 1) && visited[i] == -1) DFS(i, n);
            //Recursive DFS call
        }
    }

    void collapse()                     //Collapsing and printing the final graph
    {
        int num_visited = 0;
        AdjacencyList *Temp = new AdjacencyList(no_of_nodes - 1);

        for (int i = no_of_nodes-1; i >= 0; i--)
        //Doing DFS and updating the visited array accordingly
        {
            if (visited[i] == -1)
            {
                Temp->insert(i);
                num_visited++;
                DFS(i, i);
            }
        }
        
        out << "Collapsed Graph:\n" << num_visited << ":";

        AdjacencyList *A[num_visited];  //New array of lists each for each node of final output
        for (int i = num_visited-1; i >= 0; i--)
        {
            Temp = Temp->Next;
            A[i] = new AdjacencyList(Temp->value);
        }

        for (int i = 0; i < num_visited; i++)
        //Printing the nodes of final graph
        {
            out << " " << A[i]->value+1;
        }
        out << "\n";

        for (int i = 0; i < no_of_nodes; i++)
        //Adding the adjacent edges to the final graph i.e. the edges of the final graph
        {
            int k = visited[i];
            int j;
            for (j = 0; j < num_visited; j++)
            {
                if (A[j]->value == k) break;
            }

            AdjacencyList* Temp = Nodes[i].Adjacent;
            while(Temp != nullptr)
            {
                int k = visited[Temp->value];
                if (!(A[j]->search(k)) && (A[j]->value != k)) A[j]->insert(k);
                Temp = Temp->Next;
            }
        }

        for (int i = 0; i < num_visited; i++)
        //Printing the final output
        {
            int k = A[i]->value;
            AdjacencyList* Temp = A[i]->Next;
            while(Temp != nullptr)
            {
                out << k+1 << " " << Temp->value+1 << "\n";
                Temp = Temp->Next;
            }
        }
    }

};


int main()
{
    int no_of_nodes;                    //No of nodes of the graph
    cin >> no_of_nodes;
    Graph G(no_of_nodes);               //Constructing the graph

    int a, b;
    cin >> a >> b;                      //Edges input
    while ((a != -1) && (b != -1))      //Taking inputs until -1, -1 and adding them into and updating graph
    {
        G.Nodes[a-1].Add_adjacent(b-1);
        G.Nodes[a-1].no_of_after++;
        G.Nodes[b-1].Add_previous(a-1);
        G.Nodes[b-1].no_of_prev++;
        G.Nodes[b-1].is_sink();
        cin >> a >> b;
    }

    AdjacencyList* Source = nullptr;    //List of source nodes and updating them
    for (int i = 0; i < no_of_nodes; i++)
    {
        GraphNode Node = G.Nodes[i];
        if (!(Node.sink))
        {
            if (Source == nullptr) Source = new AdjacencyList(i);
            else Source->insert(i);
        }
    }

    out << "Source Nodes:";
    while (Source != nullptr)           //Printing the source nodes
    {
        out << " " << Source->value + 1 ;
        Source = Source->Next;
    }
    out << "\n\n";
    out << "Similar Nodes :";           //Printing the similar nodes before taking inputs from file i.e. by property 3
    for (int i = 0; i < no_of_nodes; i++)
    {
        if (G.Nodes[i].no_of_prev == 1) //The edges with no of incoming as 1
        {
            G.get_similar_nodes(i, G.Nodes[i].Previous->value);
        }
    }
    
    cin >> a >> b;                      //Again taking inputs from file until -1, -1
    while ((a != -1) && (b != -1))      //Adding them into similar nodes
    {
        G.get_similar_nodes(a-1, b-1);
        cin >> a >> b;
    }
    out << "\n\n";

    G.collapse();                       // And finally collapsing the similar nodes graph
}