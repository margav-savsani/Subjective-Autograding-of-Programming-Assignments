#include "std_headers.h"
#include "Graph.cpp"
using namespace std;
int main()
{
    //to take input from a file
    string filename;
    cin>>filename;
    ifstream myfile(filename);
    string myline;
    int numNodes = 0;
    while (getline(myfile, myline))
    {
        numNodes = stoi(myline);
        break;
    }

    //make a graph
    Graph* myGraph;
    myGraph = new Graph(numNodes, filename);
    if (myGraph == nullptr) {
        cerr << "Memory allocation failure." << endl;
        exit(-1);
    }

    //finding source nodes
    for(int i=0; i<numNodes; i++){
        if(myGraph->nodes[i].parentAdjacency==nullptr){
            if(myGraph->sourceNodes==nullptr){
                myGraph->sourceNodes = new listOfObjects<Node*>(&myGraph->nodes[i]);
            }else{
                listOfObjects<Node*>* a = myGraph->sourceNodes;
                while(a->next!=nullptr){
                    a=a->next;
                }
                a->next = new listOfObjects<Node*>(&myGraph->nodes[i]);
            }
        }
    }
    myfile.close();

    myGraph->similar();

    myGraph->printResults();
}