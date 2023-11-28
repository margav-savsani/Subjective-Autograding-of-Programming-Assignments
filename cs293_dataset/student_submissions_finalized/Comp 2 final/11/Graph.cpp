#include <iostream>
#include "vector.cpp"
using namespace std;

class Node { 
    //the node class
    public : 
     int value ;  //the value 
     bool isSource ;
     vector<int> adj ; //directed edges from cuur node  
     vector<int> revadj ; //directed edges to the curr nod e
     Node()  { isSource = true ;}
     void addadjancent(int n) { adj.push_back(n);  } 
     void addreverseradjacent(int n ) { isSource = false ; revadj.push_back(n); }
};

class Matrix { 
   public : 
    //matrix  2nested array 
    int** similar ; 
    int count ; //number of similar pairs 
    int n ; 
    Matrix(int n) { //intialize 
        similar = new int*[n] ;
        this->n = n ;
        for ( int i =0 ; i < n ; i++ )  similar[i] = new int[n] ;
        count = 0 ;
    }
    void addSimilar(int n1, int n2) { //add and increase the count 
        if (isSimilar(n1,n2)) return ; 
        similar[n1][n2] = 1 ; 
        count++; 
    }
    int isSimilar(int n1,int n2) { return similar[n1][n2] ; }
}; 

class Graph { 
   public : 
    Node* nodes ; 
    Matrix* similar ; //similar matrix 
    int n ; 
    bool* visited ; //for dfs purpose 
    vector<int> collapsedEdges ; //the edges after the collapsed graph 
   
    Graph(int n) {  //initalize the graph 
        this->n = n ; 
        nodes =  new Node[n]; 
        visited = new bool[n];
        for ( int i =0 ; i < n ; i++ )  { nodes[i].value = i+1 ; similar = new Matrix(n);  }
    }
    ~Graph() { delete[] nodes ; }
    void addEdge(int n1,int n2) {//add a edge with n1 is the index and not the value 
             nodes[n1].addadjancent(n2);
             nodes[n2].addreverseradjacent(n1);
    }
    
    bool edgeExists(int n1,int n2) {  //check if edge exists 
       for ( int i = 0 ; i<nodes[n1].adj.size() ; i ++ )  { 
           if ( nodes[n1].adj[i] == n2 ) return true ; 
       }
       return false ; 
    }
    
    void similarNodes() {  //function to update the similar matrix 
        int old_similar_count = similar->count ; 
        for(int i=0;i<n;i++) { // for each possible i and j in nodes 
            for(int j=0; j<n ; j++) {
                if ( !(nodes[i].isSource && nodes[j].isSource) ) { 
                    if(edgeExists(j,i) && nodes[i].revadj.size() == 1 ) //the one incoming criteria 
                        similar->addSimilar(i,j);
                    else { 
                     int viceversa[] = {i,j} ; //dummy array to check for both the case i,j and j,i 
                     bool isSimilar = true ; //check for similarity 
                     for ( int order = 0 ; order < 2 && isSimilar; order++  ) { //two times
                       int i = viceversa[order] , j = viceversa[(order+1)%2] ; 
                       vector<int> revadj1 = nodes[i].revadj ; 
                       vector<int> revadj2 = nodes[j].revadj ; 
                       for ( int p = 0 ; p < revadj1.size() ; p++ ) { //for all the incoming nodes 
                           bool matched = false ; 
                           for ( int q = 0 ; q < revadj2.size() ; q++ ) { 
                                if ( similar->isSimilar( revadj1[p] , revadj2[q]) ) matched = true ; 
                           }
                           if (!matched) { isSimilar = false ; break ; } //no similar node found in the other node parents  
                       }
                    }  
                    if(isSimilar) similar->addSimilar(i,j); //add to similar matrix 
                 }
                }
            }
       }
       if ( old_similar_count != similar->count ) similarNodes();  //if similar matrix is updated , then recursicve do 
    }   

    void printResults(vector<int> maxCollapsed) { 
        //print the results 
        cout << "Source nodes: ";
        for (int i = 0; i < n; i++) {
           if( nodes[i].isSource ) cout << nodes[i].value << " ";
        }
        cout << endl;
        cout << "Similar node pairs: ";
        for (int i = 0; i < n ; i++) {
           for (int j = 0; j < n ; j++) {
             if ( similar->isSimilar(i,j))   cout << "(" << nodes[i].value << ", " << nodes[j].value << ") ";
           }
        }
        cout << endl;
        cout << "Collapsed graph:" << endl ;
        cout << maxCollapsed.size() << ": ";
        for (int i = 0; i < maxCollapsed.size(); i++) {
               cout << maxCollapsed[i] << " ";
        } 
        cout << endl;
        for (int i = 0; i < collapsedEdges.size()/2; i++) {
           cout << collapsedEdges[2*i] << " " << collapsedEdges[2*i+1] << endl;
        }
    }
    
    int recursiveDFS(Node* source, vector<int>* connected, int maximum) { 
      //two way dfs for a directed graph 
      //this dfs treats it like a undirected graph 
      //the connected gives the nodes that was explored from the source , they form a connected component
      //index of the node whose value is maximum in the component 
      for (int i = 0; i < source->adj.size(); i++) {
        if (! visited[source->adj[i]] ) {
           visited[source->adj[i]] = true ;   
           int value = nodes[ source->adj[i] ].value ;     
           maximum = max(maximum,value);
           connected->push_back( source->adj[i] );
           maximum = recursiveDFS( &nodes[source->adj[i]] , connected, maximum) ; 
      }
     }
      for (int i = 0; i < source->revadj.size(); i++) {
       if (! visited[source->revadj[i]] ) {
           visited[source->revadj[i]] = true ;   
           int value = nodes[ source->revadj[i] ].value ;     
           maximum = max(maximum,value);
           connected->push_back( source->revadj[i] );
           maximum = recursiveDFS( &nodes[source->revadj[i]] , connected, maximum) ; 
      }
     }
      return maximum;
    }

    void collapsedGraph(Graph* originalGraph,vector<int>* maxCollapsed ) { 
        //add edges to current graph from the similar nodes from the original graph . 
        vector<vector<int>> collapsed ; 
        for (int i = 0; i < n ; i++) {
        for (int j = 0; j < n ; j++) {
           if ( originalGraph->similar->isSimilar(i,j)) addEdge(i,j);
          }
        }
        //dfs for different connected component 
        for (int i = 0; i < n; i++) {
          if (!visited[i]) {
            visited[i] = true ;
            vector<int> connected;
            connected.push_back(i);
            int maximum = nodes[i].value;
            maximum = max(recursiveDFS(&nodes[i], &connected, 0), maximum);
            maxCollapsed->push_back(maximum);
            collapsed.push_back(connected); 
          }
        }
        //to add the edges between two max collapsed , if there is a edge between their corresponding , 
        // connected components 
        for (int i = 0; i < collapsed.size(); i++) {
         for (int j = 0; j < collapsed.size(); j++) {
            if (i != j) {
                bool temp  = true;
                for (int k = 0; k < collapsed[i].size(); k++) { 
                    for (int l = 0; l < collapsed[j].size(); l++) {
                        //if edge exist between any two nodes of the two different connected components 
                        if (originalGraph->edgeExists(collapsed[i][k],collapsed[j][l])) {
                            if (temp) {
                                //add the edgs to the original graph collapsed edges 
                                originalGraph->collapsedEdges.push_back((*maxCollapsed)[i]);
                                originalGraph->collapsedEdges.push_back((*maxCollapsed)[j]);
                                temp = false;
                                break;
                            }
                        }
                    }
                    if (!temp)  break;
                }
            }
         }
       }

    }

};
