#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string>
#include <sstream>
#include <cstring>
#include <cctype>
#include <vector>
using namespace std;

class Graph {
    public:
    int numNodes;
    int numEdges;
    int numNodesAfterCollapsing;
    bool* existsAfterCollapsing;
    vector<int>* EdgeList;
    vector<int>* ReverseEdgeList;
    vector<int>* SimilarityList;
    // bool* HasASource;
    bool **SimilarityMatrix;
    bool **EdgeMatrix;
    int* NoOfSources;
    Graph(int nNodes){
        this->numNodes = nNodes;
        this->numNodesAfterCollapsing = nNodes;
        existsAfterCollapsing = new bool[nNodes];
        for(int i=0;i<nNodes;i++){
            existsAfterCollapsing[i] = true;
        }
        EdgeList = new vector<int>[nNodes];
        ReverseEdgeList = new vector<int>[nNodes];
        SimilarityList = new vector<int>[nNodes];
        // HasASource = new bool[nNodes];
        NoOfSources = new int[nNodes];
        for(int i=0;i<nNodes;i++){
            // HasASource[i] = false;
            NoOfSources[i] = 0;
        }
        SimilarityMatrix = new bool*[numNodes];
        for(int i = 0; i < numNodes; i++){
            SimilarityMatrix[i] = new bool[numNodes];
            for(int j = 0; j < numNodes; j++){
                SimilarityMatrix[i][j]=false;
            }
        }
        EdgeMatrix = new bool*[numNodes];
        for(int i = 0; i < numNodes; i++){
            EdgeMatrix[i] = new bool[numNodes];
            for(int j = 0; j < numNodes; j++){
                EdgeMatrix[i][j]=false;
            }
        }
    }
    void addEdge(int x,int y){
        EdgeList[x-1].push_back(y-1);
        ReverseEdgeList[y-1].push_back(x-1);
        // HasASource[y-1] = true;
        NoOfSources[y-1]++;
        EdgeMatrix[x-1][y-1] = true;
    }
    void addSimilar(int x,int y){
        SimilarityList[x-1].push_back(y-1);
        SimilarityMatrix[x-1][y-1]=true;
    }
    void printSourceNodes(){
        cout << "Source nodes: " ;
        for(int i=0;i<numNodes;i++){
            // if(!HasASource[i]){
            //     cout << i+1 << " ";
            // }
            if(NoOfSources[i]==0){
                cout << i+1 << " ";
            }
        }
        cout << endl << endl;
    }
    void checkSimilar3(){
        for(int i=0;i<numNodes;i++){
            if(NoOfSources[i] == 1){
                addSimilar(i+1,ReverseEdgeList[i].front()+1);
            }
        }
    }
    bool checkSimilar2(int i,int j){
        if(SimilarityMatrix[i-1][j-1]){return true;}
        else if(NoOfSources[i-1]>0 && NoOfSources[j-1]>0){
            for(auto a : ReverseEdgeList[i-1]){
                bool m1m2Similar = false;
                for(auto b : ReverseEdgeList[j-1]){
                        if(checkSimilar2(a+1,b+1)){
                            m1m2Similar = true;
                        };
                    }
                if(!m1m2Similar){ return false;}
                }
            for(auto a : ReverseEdgeList[j-1]){
                bool m1m2Similar = false;
                for(auto b : ReverseEdgeList[i-1]){
                        if(checkSimilar2(a+1,b+1)){
                            m1m2Similar = true;
                        };
                    }
                if(!m1m2Similar){ return false;}
                }
            addSimilar(i,j);
            addSimilar(j,i);
            return true;
            }
        return false;
    }
    void printSimilar(){
        checkSimilar3();
        cout << "Similar node pairs: ";
        for(int i=0;i<numNodes;i++){
            for(int j=0;j<numNodes;j++){
                if(checkSimilar2(i+1,j+1)){
                    cout << "(" << i+1 << ", " << j+1 << ") ";
                }
            }
        }
        cout << endl << endl;
    }
    void constructEquivalance(){
        for(int i=0;i<numNodes;i++){
            for(int j=0;j<numNodes;j++){
                if(SimilarityMatrix[i][j]){
                    SimilarityMatrix[j][i] = true;
                }
            }
        }
        for(int i=0;i<numNodes;i++){
            SimilarityMatrix[i][i] = true;
        }
        bool x = true;
        while(x){
            bool **temp;
            temp = new bool*[numNodes];
            for(int i = 0; i < numNodes; i++){
                temp[i] = new bool[numNodes];
                for(int j = 0; j < numNodes; j++){
                    temp[i][j]=SimilarityMatrix[i][j];
                }
            }
            bool **curr;
            curr = new bool*[numNodes];
            for(int i = 0; i < numNodes; i++){
                curr[i] = new bool[numNodes];
                for(int j = 0; j < numNodes; j++){
                    curr[i][j]=false;
                }
            }
            for(int i=0;i<numNodes;i++){
                for(int j=0;j<numNodes;j++){
                    for(int k=0;k<numNodes;k++){
                        curr[i][j] = curr[i][j] || SimilarityMatrix[i][k] && SimilarityMatrix[k][j];
                    }
                }
            }
            for(int i = 0; i < numNodes; i++){
                for(int j = 0; j < numNodes; j++){
                    SimilarityMatrix[i][j] = SimilarityMatrix[i][j] || curr[i][j];
                }
            }
            int n=0;
            for(int i = 0; i < numNodes; i++){
                for(int j = 0; j < numNodes; j++){
                    if(temp[i][j]==SimilarityMatrix[i][j]){
                        n++;
                    };
                }
            }
            if(n == numNodes*numNodes){
                x = false;
                break;
            }
        }
    }
    void collapse(){
        for(int i=0;i<numNodes;i++){
            for(int j=0;j<numNodes;j++){
                if(i!=j && SimilarityMatrix[i][j] && existsAfterCollapsing[j]){
                    for(int k=0;k<numNodes;k++){
                        if(k!=j && existsAfterCollapsing[k]){
                            EdgeMatrix[j][k] = EdgeMatrix[j][k] || EdgeMatrix[i][k];
                            EdgeMatrix[k][j] = EdgeMatrix[k][j] || EdgeMatrix[k][i];    
                        }
                    }
                    existsAfterCollapsing[i] = false;
                    numNodesAfterCollapsing--;
                    break;
                }
            }
        }
    }
    void printCollapsedGraph(){
        constructEquivalance();
        collapse();
        cout << "Collapsed graph:" << endl;
        cout << numNodesAfterCollapsing <<": " ;
        for(int i=0;i<numNodes;i++){
            if(existsAfterCollapsing[i]){
                cout << i+1 << " ";
            }
        }
        cout << endl;
        for(int i=0;i<numNodes;i++){
            for(int j=0;j<numNodes;j++){
                if(existsAfterCollapsing[i] && existsAfterCollapsing[j] && EdgeMatrix[i][j]){
                    cout << i+1 << " " << j+1 << endl;
                }
            }
        }

    }
};

int main(){
    int N;
    cin >> N;
    Graph G(N);
    int a,b;
    cin>>a>>b;
    while(a!=-1 || b!=-1){
        G.addEdge(a,b);
        G.numEdges++;
        cin >> a >> b;
    }
    cin>>a>>b;
    while(a!=-1 || b!=-1){
        if(G.NoOfSources[a-1] == 0 && G.NoOfSources[b-1] == 0){
            G.addSimilar(a,b);
            }
        cin >> a >> b;
    }
    // for printing source nodes
    G.printSourceNodes();
    // for printing similar nodes 
    G.printSimilar();
    // for printing collapsed graph
    G.printCollapsedGraph();
}