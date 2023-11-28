#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

using namespace std;

#ifndef GRAPH_BST_CPP
#include "Graph.cpp"
#endif

int main(int argc, char **argv){
    Graph *myGraph;
    if (argc != 2) {
        cerr << "incorrect number of arguments"<<endl;
    }

    string graphFileName = argv[1];
    string myText;
    int numNodes;
    ifstream MyReadFile(graphFileName);
    int i=0;
    bool sources=false;
    while (getline (MyReadFile, myText)) {
        if(i==0){
            numNodes=stoi(myText);
            myGraph = new Graph(numNodes);
            if (myGraph == nullptr) {
                cerr << "Memory allocation failure." << endl;
                exit(-1);
            }
        }
        else{
            istringstream ss(myText);
            string del;
            int j=0;
            int n1,n2;
            while(getline(ss, del, ' ')) {
                if(j==0)n1=stoi(del);
                else{
                    n2=stoi(del);
                }
                j++;
            }
            if(n1!=-1 && n2!=-1 && !sources){myGraph->makeEdge(n1,n2);}
            if(n1==-1 && n2==-1)sources=true;
            if(sources && n1!=-1 && n2!=-1){
                myGraph->similar_type1(n1,n2);
            }
        }
        i++;
    }

    MyReadFile.close(); 
    myGraph->callDFS();
    myGraph->similar_type3();
    myGraph->similar_type2();
    myGraph->PrintSourceNodes("outgraph.txt");
    myGraph->PrintSimilarNodes("outgraph.txt");
    myGraph->printCollapsedNodes("outgraph.txt");
    // listOfObjects<int>* a =nullptr;
    // if(myGraph->isTransitive(1,14,a))cout<<"hi";
    return 0;
}
