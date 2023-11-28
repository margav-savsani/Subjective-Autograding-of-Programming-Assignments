#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

struct list
{
	int value;
	list *next;
	list()
	{
		value = -1;
		next = nullptr;
	}
	list(int value)
	{
		this->value = value;
		next = nullptr;
	}
};

void del(list **x, int v)
{
	list *r = *x;
	list *prev = nullptr;
	if (r != nullptr && r->value == v)
	{
		*x = r->next;
		delete r;
		return;
	}
	else
	{
		while (r != nullptr && r->value != v)
		{
			prev = r;
			r = r->next;
		}
		if (r == nullptr)
			return;
		prev->next = r->next;
		delete r;
		return;
	}
}

class Node
{
public:
	int value;
	list *toAdj;
	list *fromAdj;
	Node()
	{
		toAdj = new list(-1);
		fromAdj = new list(-1);
	}
};

class directedGraph
{
public:
	int numNodes;
	Node *nodes;
	int **simNodes;
	bool *source;
	int *visited;
	int *connected;
	int compNum;   // to find the number of components while making the graph for similar nodes
	int **adjMatrix;
	ofstream outFile;
	directedGraph(string file)
	{
		outFile.open (file);
		int a, b;
		cin >> a;
		numNodes = a;
		nodes = new Node[numNodes];
		source = new bool[numNodes];
		simNodes = new int *[numNodes];
		adjMatrix = new int *[numNodes];
		for (int i = 0; i < numNodes; i++)
		{
			simNodes[i] = new int[numNodes];
		}
		for (int i=0; i<numNodes; i++)
			adjMatrix[i] = new int[numNodes];

		for (int i=0; i<numNodes; i++)
			for (int j=0; j<numNodes; j++)
				adjMatrix[i][j]=0;
		
		visited= new int[numNodes] ();
		connected = new int[numNodes] ();
		compNum=1;
		
		for (int i = 0; i < numNodes; i++)
			for (int j = 0; j < numNodes; j++)
				simNodes[i][j] = 0;
		cin >> a >> b;
		while (a != -1 && b != -1)
		{
			adjMatrix[a-1][b-1]=1;
			list *currNode1 = nodes[a - 1].toAdj;
			list *currNext1 = currNode1->next;

			while (currNext1 != nullptr)
			{
				currNext1 = currNext1->next;
				currNode1 = currNode1->next;
			}
			currNode1->next = new list(b);

			list *currNode2 = nodes[b - 1].fromAdj;
			list *currNext2 = currNode2->next;
			while (currNext2 != nullptr)
			{
				currNext2 = currNext2->next;
				currNode2 = currNode2->next;
			}
			currNode2->next = new list(a);
			cin >> a >> b;
		}
		for (int i = 0; i < numNodes; i++)
		{
			if (nodes[i].fromAdj->next == nullptr)
				source[i] = true;
		}

		cin >> a >> b;
		while (a != -1 && b != -1)
		{
			simNodes[a - 1][b - 1] = 1;
			cin >> a >> b;
		}
	}

	void sourceNode() {
		outFile << "Source nodes: ";
		for (int i=0; i<numNodes; i++) {
			if (nodes[i].fromAdj->next == nullptr)
				outFile << i+1 << " ";
		}
		outFile << endl;
	}

	void calculateSim()
	{
		// case 3
		for (int i = 0; i < numNodes; i++)
		{
			list *currNode1 = nodes[i].fromAdj->next;
			if (currNode1 != nullptr && currNode1->next == nullptr)
				simNodes[i][currNode1->value - 1] = 1;
		}

		// case 2
		for (int i = 0; i < numNodes; i++)
		{
			for (int j = 0; j < numNodes; j++)
			{
				if (i != j)
				{
					list *currNode1 = nodes[i].fromAdj->next;
					bool bijec = false;   // it's not really bijection :(
					while (currNode1 != nullptr)
					{
						int iF = currNode1->value - 1;
						list *currNode2 = nodes[j].fromAdj->next;
						while (currNode2 != nullptr)
						{
							int jF = currNode2->value - 1;
							if (simNodes[iF][jF] == 1)
							{
								bijec = true;
								break;
							}
							currNode2 = currNode2->next;
						}
						if (currNode2 == nullptr)
						{
							bijec = false;
							break;
						}
						currNode1 = currNode1->next;
					}
					/*if (bijec)
						simNodes[i][j]=1;				*/
					if (bijec)
					{
						list *currNode1 = nodes[j].fromAdj->next;
						while (currNode1 != nullptr)
						{
							int jF = currNode1->value - 1;
							list *currNode2 = nodes[i].fromAdj->next;
							while (currNode2 != nullptr)
							{
								int iF = currNode2->value - 1;
								if (simNodes[jF][iF] == 1)
								{
									bijec = true;
									break;
								}
								currNode2 = currNode2->next;
							}
							if (currNode2 == nullptr)
							{
								bijec = false;
								break;
							}
							currNode1 = currNode1->next;
						}
					}

					if (bijec) {
						simNodes[i][j]=1;
						simNodes[j][i]=1;
					}
				}
			}
		}
	}

	void printSim()
	{
		outFile << "Similar node pairs: ";
		for (int i = 0; i < numNodes; i++)
			for (int j = 0; j < numNodes; j++)
				if (simNodes[i][j] == 1)
					outFile << "(" << i + 1 << ", " << j + 1 << ")" << " ";
		outFile << endl;
	}

	void DFS() {
		static int nodeIdx = 0;
		static int depth=1;
		
		visited[nodeIdx]++;
		connected[nodeIdx]=compNum;
		int currIdx = nodeIdx;
		for (int i=0; i<numNodes; i++) {
			nodeIdx = i;
			if (visited[nodeIdx]==0 && (simNodes[currIdx][nodeIdx]==1 || simNodes[nodeIdx][currIdx]==1)) {
				depth++;
				DFS();
				depth--;
			}
		}

		if (depth==1) {
		
			for (int i=0; i<numNodes; i++) {
				if (visited[i]==0) {
					compNum++;
					nodeIdx=i;
					depth++;   // note that depth here has been incremented to reduce time complexity
					DFS();
					depth--;
				}
			}
		}
		return;
	}

	void collapsedGraph() {
		outFile << "Collapsed graph:"<<"\n\n";
		int *maxIdn = new int[compNum] ();
		int cl[numNodes];
		int x;
		for (int i=1; i<=compNum; i++) {
			for (int nodeI=numNodes-1; nodeI>=0; nodeI--) {
				if (connected[nodeI] == i) {
					maxIdn[i]=nodeI;
					break;
				}
			}
		}
		
		outFile << compNum << ": ";
		for (int i=0; i<compNum; i++)
			outFile << maxIdn[i+1]+1 << " ";
		outFile << endl;

		for (int i=0; i<numNodes; i++)
			cl[i]=maxIdn[connected[i]];

		int **collapsedGraph = new int*[compNum] ();
		for (int i = 0; i < numNodes; i++)
			collapsedGraph[i] = new int[compNum] ();    // Initialize everything to zeros*/
		for (int i=0; i<compNum; i++)
			for(int j=0; j<compNum; j++)
				collapsedGraph[i][j]=0;
		
		for (int i=0; i<numNodes; i++)
			for (int j=0; j<numNodes; j++) {
				if (adjMatrix[i][j]==1) collapsedGraph[connected[i]-1][connected[j]-1]=1;
			}

		for (int i=0; i<compNum; i++)
			for(int j=0; j<compNum; j++)
				if (collapsedGraph[i][j] == 1 && i!=j)
					outFile << maxIdn[i+1]+1 << " " << maxIdn[j+1]+1 << endl;

	}

};