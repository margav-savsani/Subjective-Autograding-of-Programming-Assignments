#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

using namespace std;

// #ifndef GRAPH_BST_CPP
 #include "graph.cpp"
// #endif

int main(int argc, char **argv)
{
 

  if (argc != 2) {
    cerr << "Usage: " << argv[0] << " numNodes numEdges graphFile" << endl;
  }

  fstream inpFile;  // reading node values from file
  string inpFileName = argv[1];
  inpFile.open(inpFileName, ios::in);
  int numNodes; // total number of nodes in the graph
  inpFile>> numNodes;
  int n1; // node values for vertices of edges in the graph
  int n2;

   Node *nodes; // storing nodes of all the graph 
   nodes = new Node[numNodes+1];
   for (int i=0; i<=numNodes;i++){
      nodes[i].value= i; // initialising the nodes values in the graph to be the same as the index
   }

  
   bool *sourcenode = new  bool[numNodes+1];
   for (int i=0; i<numNodes; i++){ 
    sourcenode[i]=true; // initialising all nodes to be source nodes 
   }                    // unitll we find an incoming edge
 
   while (!inpFile.eof()){  // reading edges from file 
      inpFile>> n1>>n2;
  
      if (n1!=-1){ // if we encounter the separtor 
        if (sourcenode[n1]!= false)
          {sourcenode[n1]= true;}
        sourcenode[n2]=false; // we found an incoming edge to n2 hence not a source node 
     
        adjacent * newneighbour1 =  new adjacent(n2); // updating the to list or the 
        newneighbour1->next=nodes[n1].toadjacencylist;// outgoing list of n1 as n2 
        nodes[n1].toadjacencylist =newneighbour1;
       
        adjacent * newneighbour2 =  new adjacent(n1); // updating the from list or incoming edge 
        newneighbour2->next=nodes[n2].fromadjacencylist; //of n2  as n1 
        nodes[n2].fromadjacencylist =newneighbour2;
        }
      else break; 
   }

   while (!inpFile.eof()){ 
      inpFile>> n1>>n2;
      if (n1!=-1){  // if we encounter the separtor 
        nodes[n1].similarlist[n2] =true;  // n1 is similar to n2 so updating list of only n1 
      }
      else break;
    }
   
    // fstream outfile;  
    // string fileoutname="out.txt"; // name of the output file 
    // outfile.open(fileoutname, ios::out);
    // cout<<"source nodes: ";  // to avoid any ambiguity printed all result in the terminal 
    // for (int i=1; i<=numNodes; i++){ // otherwise to print in out file , just replace 'cout' by 'outfile'
    //   if (sourcenode[i]== true){  // if the value of the sourcenode bool array is still true 
    //     cout<< i<<" "; }    // then this node is a source node 
    // }
    // cout<<endl;
    // outfile.close();


  Graph *myGraph = new Graph( numNodes, nodes,sourcenode); // creating a new graph 
  if (myGraph == nullptr) {
   cerr << "Memory allocation failure." << endl;
    exit(-1);
  }

  myGraph->findsimilar();  // find similar nodes by condition 2 and condition 3 given in the problem statement 
  myGraph->printResults(); // collapsing the nodes of the graph based on the symmetric and transitive behavior 
                          // and printing out the collapsed graph 
  return 0;
}
