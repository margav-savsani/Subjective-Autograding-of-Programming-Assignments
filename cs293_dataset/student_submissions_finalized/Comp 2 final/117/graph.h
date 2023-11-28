
#ifndef STD_HEADERS
#include "stdheaders.h"
#endif

using namespace std;

class myArr
{ // Growable array
private:
    int *array, length, elements;

public:
    myArr()
    {
        length = 4;
        array = new int[4];
        elements = 0;
    }
    void add(int elem)
    {
        if (length != elements)
        {
            array[elements] = elem;
            elements++;
        }
        else
        {
            int *arr1 = array;
            length = length * 2;
            array = new int[length];
            for (int i = 0; i < length / 2; i++)
            {
                array[i] = arr1[i];
            }
            array[elements] = elem;
            elements++;
        }
    }
    int getElem(int index)
    {
        if (index < 0 or index >= elements)
        {
            return -1;
        }
        else
        {
            return array[index];
        }
    }

    int numElem()
    {
        return elements;
    }

    void print(int num)
    {
        for (int i = 0; i < elements; i++)
        {
            cout << num << " " << array[i] + 1 << endl;
        }
    }
    int exists(int num)
    {
        for (int i = 0; i < elements; i++)
        {
            if (array[i] == num)
                return i;
        }
        return -1;
    }
};

class Node
{
private:
    int value;
    myArr *outarr, *inarr;
    bool isSource, isSink;

public:
    Node()
    {
        outarr = new myArr();
        inarr = new myArr();
        isSource = true;
        isSink = true;
    }
    Node(int val)
    {
        outarr = new myArr();
        inarr = new myArr();
        value = val;
        isSource = true;
        isSink = true;
    }
    void setval(int val)
    {
        value = val;
    }
    int getval()
    {
        return value;
    }
    void addout(int indexOfNode)
    {
        outarr->add(indexOfNode);
        isSink = false;
    }
    void addin(int indexOfNode)
    {
        inarr->add(indexOfNode);
        isSource = false;
    }
    myArr *outAdjacencyList()
    {
        return outarr;
    }
    myArr *inAdjacencyList()
    {
        return inarr;
    }
    bool source()
    {
        return isSource;
    }
    bool sink()
    {
        return isSink;
    }
};

class Graph
{
private:
    Node *nodes;
    int numNodes;
    string outputfilename;
    bool **similar, **closure;
    int *depTimes, time, *topsort;
    bool *visited;
    // Compressed class data variables
    int numOfclass, *classRepresentative, **classNodes, *elementsInClass;

    void init()
    {
        time = 0;
        for (int i = 0; i < numNodes; i++)
        {
            visited[i] = 0;
            depTimes[i] = 0;
        }
        for (int i = 0; i < numNodes; i++)
        {
            if (!visited[i])
            {
                DFS(i);
            }
        }
    }
    void DFS(int elem)
    {
        time++;
        visited[elem] = 1;
        int num = nodes[elem].outAdjacencyList()->numElem();
        for (int i = 0; i < num; i++)
        {
            int elem1 = nodes[elem].outAdjacencyList()->getElem(i);
            if (!visited[elem1])
            {
                DFS(elem1);
            }
        }
        depTimes[elem] = time;
    }
    void topologicalsort()
    {
        init();
        for (int i = 0; i < numNodes; i++)
        {
            int ithmax = 0;
            for (int j = 0; j < numNodes; j++)
            {
                if (depTimes[ithmax] < depTimes[j])
                    ithmax = j;
            }
            depTimes[ithmax] = -1;
            topsort[i] = ithmax;
        }
        return;
    }
    // check similar banana baaki hai, banaenge, only second case banana hai
    bool checksimilar(int n1, int n2)
    {
        myArr *inlist1 = nodes[n1].inAdjacencyList(), *inlist2 = nodes[n2].inAdjacencyList();
        for (int i = 0; i < inlist1->numElem(); i++)
        {
            int inelem = inlist1->getElem(i);
            bool found = false;
            for (int j = 0; j < inlist2->numElem(); j++)
            {
                if (similar[inelem][inlist2->getElem(j)])
                {
                    found = true;
                    break;
                }
            }
            if (!found)
            {
                if (n1 == 6 && n2 == 14)
                    cout << "HI\n";
                return false;
            }
        }
        for (int i = 0; i < inlist2->numElem(); i++)
        {
            int inelem = inlist2->getElem(i);
            bool found = false;
            for (int j = 0; j < inlist1->numElem(); j++)
            {
                if (similar[inelem][inlist1->getElem(j)])
                {
                    found = true;
                    break;
                }
            }
            if (!found)
                return false;
        }
        return true;
    }

    void calculateCompressedData()
    {
        bool elementAdded[numNodes];
        numOfclass = 0;
        classRepresentative = new int[numNodes];
        elementsInClass = new int[numNodes];
        classNodes = new int *[numNodes];
        for (int i = 0; i < numNodes; i++)
        {
            classNodes[i] = new int[numNodes];
            elementsInClass[i] = 0;
            classRepresentative[i] = -1;
            elementAdded[i] = 0;
        }
        for (int i = 0; i < numNodes; i++)
        {
            int elements = 0, maxelement = 0;
            for (int j = 0; j < numNodes; j++)
            {
                if (closure[i][j] && !elementAdded[j])
                {
                    classNodes[numOfclass][elements] = j;
                    elements++;
                    maxelement = max(maxelement, j);
                    elementAdded[j] = 1;
                    if (elements > 0)
                    {
                    }
                }
            }
            if (elements > 0)
            {
                classRepresentative[numOfclass] = maxelement;
                elementsInClass[numOfclass] = elements;
                numOfclass++;
            }
        }
    }

    int equivalenceClassNum(int n1)
    {
        for (int i = 0; i < numOfclass; i++)
        {
            for (int j = 0; j < elementsInClass[i]; j++)
            {
                if (classNodes[i][j] == n1)
                    return i;
            }
        }
        return -1;
    }

public:
    Graph(int numNodes, string output)
    {

        outputfilename = output;
        this->numNodes = numNodes;
        nodes = new Node[numNodes];
        depTimes = new int[numNodes];
        visited = new bool[numNodes];
        similar = new bool *[numNodes];
        closure = new bool *[numNodes];
        topsort = new int[numNodes];
        for (int i = 0; i < numNodes; i++)
        {

            similar[i] = new bool[numNodes];
            closure[i] = new bool[numNodes];
            for (int j = 0; j < numNodes; j++)
            {
                similar[i][j] = 0;
                closure[i][j] = 0;
            }
        }
        for (int i = 0; i < numNodes * 2; i++)
            for (int i = 0; i < numNodes; i++)
            {
                nodes[i].setval(i + 1);
            }
        while (true)
        {
            int from, to;
            cin >> from >> to;
            if (from == -1)
                break;
            nodes[from - 1].addout(to - 1);
            nodes[to - 1].addin(from - 1);
        }
        while (true)
        {
            int n1, n2;
            cin >> n1 >> n2;
            if (n1 == -1)
                break;
            similar[n1 - 1][n2 - 1] = 1;
        }
    }
    void printSimilar() // Includes printing source nodes
    {
        ofstream output(outputfilename);
        output << "Source nodes: ";
        for (int i = 0; i < numNodes; i++)
        {
            if (nodes[i].source())
                output << nodes[i].getval() << " ";
        }
        output << endl
               << endl;
        output << "Similar node pairs: ";
        for (int i = 0; i < numNodes; i++)
        {
            for (int j = 0; j < numNodes; j++)
            {
                if (similar[i][j])
                {
                    output << "(" << nodes[i].getval() << ", " << nodes[j].getval() << ") ";
                }
            }
        }
        output << endl
               << endl;

        calculateCompressedData();
        output << "Collapsed Graph:\n\n";
        output << numOfclass << ": ";
        for (int i = 0; i < numOfclass; i++)
        {
            output << nodes[classRepresentative[i]].getval() << " ";
        }
        output << endl;

        bool print[numOfclass][numOfclass];
        for (int i = 0; i < numOfclass; i++)
        {
            for (int j = 0; j < numOfclass; j++)
            {
                print[i][j] = 0;
            }
        }
        for (int i = 0; i < numNodes; i++)
        {
            myArr *outedge = nodes[i].outAdjacencyList();
            for (int j = 0; j < outedge->numElem(); j++)
            {
                int n1 = i, n2 = outedge->getElem(j);
                int equiv1 = equivalenceClassNum(n1), equiv2 = equivalenceClassNum(n2);
                if (equiv1 != equiv2 && !print[equiv1][equiv2])
                {
                    output << nodes[classRepresentative[equiv1]].getval() << " " << nodes[classRepresentative[equiv2]].getval() << endl;
                    print[equiv1][equiv2] = 1;
                }
            }
        }
        output.close();
    }
    void calcSimPairs()
    {

        topologicalsort();
        for (int i = 0; i < numNodes; i++)
        {
            int elem = topsort[i];
            myArr *inelems = nodes[elem].inAdjacencyList();
            if (inelems->numElem() == 1)
            {
                similar[elem][inelems->getElem(0)] = 1;
            }
            for (int j = 0; j < i; j++)
            {
                if (checksimilar(elem, topsort[j]) && !nodes[elem].source())
                {
                    similar[elem][topsort[j]] = 1;
                    similar[topsort[j]][elem] = 1;
                }
            }
        }
    }

    void closurefunc()
    {
        for (int i = 0; i < numNodes; i++)
        {
            for (int j = 0; j < i; j++)
            {
                if (similar[i][j] or similar[j][i])
                {
                    closure[i][j] = 1;
                    closure[j][i] = 1;
                }
            }
            closure[i][i] = 1;
        }

        bool ***R;
        R = new bool **[numNodes + 1];
        for (int i = 0; i <= numNodes + 1; i++)
        {
            R[i] = new bool *[numNodes];
            for (int j = 0; j < numNodes; j++)
            {
                R[i][j] = new bool[numNodes];
                for (int k = 0; k < numNodes; k++)
                {
                    if (i == 0)
                    {
                        R[i][j][k] = closure[j][k];
                    }
                    else
                    {
                        R[i][j][k] = 0;
                    }
                }
            }
        }

        for (int k = 1; k < numNodes + 1; k++)
        {
            for (int i = 0; i < numNodes; i++)
            {
                for (int j = 0; j < numNodes; j++)
                {
                    R[k][i][j] = (R[k - 1][i][j] || (R[k - 1][i][k - 1] && R[k - 1][k - 1][j]));
                }
            }
        }

        for (int i = 0; i < numNodes; i++)
        {
            for (int j = 0; j < numNodes; j++)
            {
                closure[i][j] = R[numNodes][i][j];
            }
        }
    }
};