// Linked list used for storing data
class listOfObjects
{
public:
    int value;
    listOfObjects *next;
    listOfObjects *prev;

    // Constructor
    listOfObjects(int initValue)
    {
        value = initValue;
        next = prev = nullptr;
    }
    listOfObjects() { next = prev = nullptr; }

    ~listOfObjects() { ; }
};
// Used as an object of the graph
class Node
{
public:
    int value;
    listOfObjects *tolist;
    listOfObjects *fromlist;
    int *similar;
    int *equisimilar;

    Node(int val)
    {
        value = val;
        tolist = nullptr;
        fromlist = nullptr;
        similar = nullptr;
        equisimilar = nullptr;
    }
    Node()
    {
        value = -1;
        tolist = nullptr;
        fromlist = nullptr;
        similar = nullptr;
        equisimilar = nullptr;
    }
};
// the acyclic grpah used in the quesiton
class ADG
{
public:
    Node *listofnodes;
    int total;
    int *issource;
    int finalcount;
    int *nodesremain;

    ADG(int number)
    {
        listofnodes = new Node[number]();

        for (int i = 0; i < number; i++)
        {
            listofnodes[i].fromlist = new listOfObjects(-1);
            listofnodes[i].tolist = new listOfObjects(-1);
            listofnodes[i].similar = new int[number];
            listofnodes[i].equisimilar = new int[number];
            for (int j = 0; j < number; j++)
            {
                listofnodes[i].similar[j] = 0;
                listofnodes[i].equisimilar[j] = 0;
            }
            listofnodes[i].value = i;
        }
        total = number;
        issource = new int[total];
        finalcount = 0;
        nodesremain = new int[total];
        for (int i = 0; i < total; i++)
        {
            nodesremain[i] = 0;
        }
    }
    // Creates edges in the graph by adding relation between respective edges

    void createedge(int node1, int node2)
    {
        Node n1 = listofnodes[node1 - 1];
        listOfObjects *list1 = n1.tolist;
        listOfObjects *element = new listOfObjects(node2 - 1);
        if (list1->value != -1)
        {
            while (list1->next != nullptr)
            {
                list1 = list1->next;
            }
            list1->next = element;
            list1->next->prev = element;
        }
        else
        {

            list1->value = node2 - 1;
        }
        // cout << "Node2: " << node2 << endl;
        Node n2 = listofnodes[node2 - 1];
        listOfObjects *list2 = n2.fromlist;
        listOfObjects *element2 = new listOfObjects(node1 - 1);

        if (list2->value != -1)
        {

            while (list2->next != nullptr)
            {
                list2 = list2->next;
            }
            list2->next = element2;
            list2->next->prev = element2;
        }
        else
        {
            list2->value = node1 - 1;
        }
    }

    // Adding the similarity of the nodes which are mentioned in the question
    void addsimilar(int node1, int node2)
    {

        Node n1 = listofnodes[node1 - 1];

        // listOfObjects *element = new listOfObjects(node2 - 1);

        if (issource[node1 - 1] == false && issource[node2 - 1] == false)
        {
            n1.similar[node2 - 1] = 1;
            n1.equisimilar[node2 - 1] = 1;
            listofnodes[node2 - 1].equisimilar[node1 - 1] = 1;
        }
    }

    // This is used as a helper function for adding the similarity relation to the pairs found using the properties of similarities
    void similar(int node1, int node2)
    {

        Node n1 = listofnodes[node1 - 1];
        n1.similar[node2 - 1] = 1;
        n1.equisimilar[node2 - 1] = 1;
        listofnodes[node2 - 1].equisimilar[node1 - 1] = 1;
    }
    // Used to check for similarities between 2 nodes by using their adjacent nodes
    bool recursivesimilar(int i, int j)
    {
        // cout << i << ">>==>>" << j << endl;
        listOfObjects *list1 = listofnodes[i].fromlist;
        bool found = 0;
        while (list1 != nullptr && list1->value != -1)
        {
            listOfObjects *list2 = listofnodes[j].fromlist;
            Node value1 = listofnodes[list1->value];
            // cout << "VALUE: " << list1->value << endl;
            bool isSimilar = false;
            // cout << list2->value << endl;
            while (list2 != nullptr && list2->value != -1)
            {
                // cout << "VALUE 2: " << list2->value << endl;
                if (value1.similar[list2->value] == 1)
                {

                    isSimilar = true;
                    // cout << isSimilar << endl;
                }
                list2 = list2->next;
            }
            if (isSimilar == false)
            {
                found = 1;
                break;
            }
            list1 = list1->next;
        }
        // cout << i << ">>==>>" << j << endl;
        listOfObjects *list3 = listofnodes[j].fromlist;
        bool found2 = 0;
        while (list3 != nullptr && list3->value != -1)
        {
            listOfObjects *list4 = listofnodes[i].fromlist;
            Node value1 = listofnodes[list3->value];
            // cout << "VALUE: " << list3->value << endl;
            bool isSimilar = false;
            while (list4 != nullptr && list4->value != -1)
            {
                // cout << "VALUE 2: " << list4->value << endl;
                if (value1.similar[list4->value] == 1)
                {

                    isSimilar = true;
                    // cout << isSimilar << endl;
                }
                list4 = list4->next;
            }
            if (isSimilar == false)
            {
                found2 = 1;
                break;
            }
            list3 = list3->next;
        }
        if (found == 0 && found2 == 0)
        {

            return true;
        }
        return false;
    }
    // Uses the relation described in the question to check for similarity between the nodes
    void checksimilar()
    {
        for (int i = 0; i < total; i++)
        {
            if (listofnodes[i].fromlist->value != -1 && listofnodes[i].fromlist->next == nullptr)
            {
                if (i != listofnodes[i].fromlist->value)
                {
                    // cout << "Adding Similar " << i + 1 << "-=-=-=-" << listofnodes[i].fromlist->value + 1 << endl;
                    similar(i + 1, listofnodes[i].fromlist->value + 1);
                }
            }
        }

        int samelevel[total];
        int l = 0;
        int old = 0;
        // First finding the nodes which dont have any incoming nodes
        for (int j = 0; j < total; j++)
        {
            Node n1 = listofnodes[j];
            listOfObjects *l1 = n1.fromlist;
            if (l1->value == -1)
            {
                // cout << "Level 1 No adding : " << j << endl;
                samelevel[l] = j;
                l = l + 1;
            }
        }
        int num = l;
        old = 0;
        // Now adding the nodes to queue by going 1 step up the heirchy by using the to list
        while (old != total)
        {
            for (int i = old; i < l; i++)
            {
                listOfObjects *l2 = listofnodes[i].tolist;
                while (l2 != nullptr && l2->value != -1)
                {
                    // cout << "Adding i=" << l2->value << endl;
                    int ispresent = 0;
                    for (int k = 0; k < l; k++)
                    {

                        if (samelevel[k] == l2->value)
                        {
                            ispresent = 1;
                        }
                    }
                    if (ispresent == 0)
                    {
                        samelevel[l] = l2->value;
                        l = l + 1;
                    }

                    l2 = l2->next;
                }
            }
            // Checking for similarity using similar funciton
            // cout << "Vslue of l" << l << endl;
            for (int w = old; w < l; w++)
            {
                for (int y = 0; y < l; y++)
                {
                    if (w >= num)
                    {
                        // cout << "PAssing " << samelevel[w] << " " << samelevel[y] << endl;
                        if (recursivesimilar(samelevel[w], samelevel[y]) == true)
                        {
                            // cout << "I found something" << endl;
                            // cout << samelevel[w] << " " << samelevel[y] << endl;
                            similar(samelevel[w] + 1, samelevel[y] + 1);
                            similar(samelevel[y] + 1, samelevel[w] + 1);
                        }
                    }
                }
            }
            old = l;
        }
    }
    // Upadtes the values of graph by finding the max value in that equivalence relation partition
    int updatevalue(int i, int prev, int val)
    {
        // cout << "Starting Function for i=" << i << endl;
        for (int j = prev - 1; j > -1; j--)
        {
            // cout << i << ">>" << j << " ";
            // cout << listofnodes[i].equisimilar[j] << endl;
            if (listofnodes[i].equisimilar[j] == 1)
            {
                // cout << "J=" << j << endl;
                // cout << "J VALUE=" << listofnodes[j].value << endl;
                // cout << "I VALUE=" << listofnodes[i].value << endl;
                if (listofnodes[i].value <= listofnodes[j].value)
                {
                    listofnodes[j].value = max(listofnodes[i].value, listofnodes[j].value);
                }
                else
                {
                    listofnodes[j].value = max(listofnodes[i].value, listofnodes[j].value);
                    listofnodes[j].value = max(listofnodes[j].value, updatevalue(j, prev, listofnodes[i].value));
                }
            }
        }

        return max(listofnodes[i].value, val);
    }
    // Colapsing the graphing by suppling nodes who happent been encountered till now
    void collapse()
    {

        for (int i = total - 1; i > -1; i--)
        {
            if (listofnodes[i].value == i)
            {
                finalcount++;
                nodesremain[i] = 1;
                // cout << "Entering for i=" << i << endl;
                updatevalue(i, i, -1);
            }
        }
    }
    // Printing all the data required 
    void printsimilar()
    {
        ofstream data;

        data.open("outgraph.txt");

        data << "Source nodes: ";
        for (int i = 0; i < total; i++)
        {
            if (issource[i] == false)
            {
                data << i + 1 << " ";
            }
        }
        data << endl;

        data << endl;
        data << "Similar node pairs: ";

        for (int i = 0; i < total; i++)
        {

            for (int j = 0; j < total; j++)
            {
                if (listofnodes[i].similar[j] == 1)
                {
                    data << "(" << i + 1 << ", " << j + 1 << ") ";
                }
            }

          
        }
        data << endl;
        data << endl;
        // We check for nodes whose value has been increased and print only those nodes
        data << "Collapsed graph:" << endl;
        data << endl;
        data << finalcount << ": ";
        for (int i = 0; i < total; i++)
        {
            if (nodesremain[i] == 1)
            {
                data << i + 1 << " ";
            }
        }
        data << endl;
        for (int i = total - 1; i > -1; i--)
        {

            // data<<"Entry"<<endl;

            Node n1 = listofnodes[i];
            int val1 = n1.value;
            int alledge[total];
            // data << "===" << val1 << "====" << endl;
            if (val1 == i)
            {
                for (int l = 0; l < total; l++)
                {
                    alledge[l] = 0;
                }
                // data << "===" << i << "====" << endl;
                for (int j = 0; j < total; j++)
                {
                    Node n2 = listofnodes[j];
                    listOfObjects *list = n2.tolist;
                    if (n2.value == val1)
                    {
                        while (list != nullptr)
                        {
                            if (n1.value != listofnodes[list->value].value && list->value != -1)
                            {
                                alledge[listofnodes[list->value].value] = 1;
                            }
                            list = list->next;
                        }
                    }
                }
                for (int k = 0; k < total; k++)
                {
                    if (alledge[k] == 1)
                    {
                        data << val1 + 1 << " " << k + 1 << endl;
                    }
                }
            }
        }
    }
};
