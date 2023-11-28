#ifndef GRAPH_CPP
#include "Graph.cpp"
#endif

int main(){

    //Redefine stdout to outgraph.txt
    ofstream out("outgraph.txt");    
    streambuf *coutbuf = cout.rdbuf(); //save old buffer
    cout.rdbuf(out.rdbuf());

    //Take input from user
    int numNodes, n;
    cin >> n;
    numNodes = n;
    Graph G(numNodes);
    for ( int i = 0 ; i < numNodes; i++ ){
        G.nodes[i].id=(i+1);
    }
    for ( int i = 1 ; n != -1 ; i++ ){
        int sNode;
        int dNode;
        Node *s;
        Node *d;
        cin >> n;
        if (n==-1){
            break;
        }
        sNode = n;
        cin >> n;
        dNode = n;
        G.nodes[sNode-1].adjList->insert(&G.nodes[dNode-1]);
        G.nodes[dNode-1].parentList->insert(&G.nodes[sNode-1]);
        G.isSource[dNode-1]=false;
        G.isSink[sNode-1]=false;
    }
    cin >> n;

    //Print the source nodes
    cout << "Source Nodes: " ;
    for ( int i = 0 ; i < G.nNodes ; i++ ){
        if ( G.isSource[i]==true ){
            cout << (i+1) << " ";
        }
    }
    cout << endl;
    cout << endl;
    for ( int i = 0 ; true ; i++ ){
        cin >> n;
        int s1 = n;
        cin >> n;
        int s2 = n;
        if ( n == -1 ){
            break;
        }
        G.customSimilarity(s1-1, s2-1);
    }
    G.singleSimilarity();

    //Call update similiarity till no more changes are made in the graph
    bool changeMade = true;
    while(changeMade){
        changeMade=false;
        for ( int i = 0 ; i < numNodes ; i++ ){
            for ( int j = 0 ; j <  numNodes ; j++ ){
                if (i!=j){
                    if (G.updateSimilarity(i,j)){
                        changeMade = true;
                    }
                }
            }
        }
    }

    //Print the similar nodes
    cout << "Similar node pairs:";
    for ( int i = 0 ;  i < G.nNodes ; i++ ){
        if ( G.nodes[i].similarList->start!=nullptr ){
            ListOfNodes *iter = G.nodes[i].similarList->start;
            while (iter!=nullptr ){
                cout << "(" << i+1 << "," << iter->value->id << ")";
                iter = iter->next;
            }
        }
    }

    //Compute and print the collapsed Graph
    cout << endl;
    cout << endl;
    cout << "Collapsed graph:" << endl;
    G.similarDFS();
}