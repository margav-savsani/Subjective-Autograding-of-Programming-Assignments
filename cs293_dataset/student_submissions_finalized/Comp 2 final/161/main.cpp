#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

using namespace std;

#ifndef GRAPH_BST_CPP
#include "Graph.cpp"
#endif

int main(int argc, char **argv)
{
    
    string line;
    fstream file;
    string filename, graphFileName;
    int word, t;

    cin >> t;
    similarNodes *SN = NULL;
    similarNodes *allSimilarNodes;
    
    int numNodes = t;

    Graph myGraph(numNodes, graphFileName);

    bool odd = true;
    while (cin >> word){
      if(word==-1) break;
      // cout<<word<<endl;
      int index = word;
      int i,j;

      if(odd)
      {
        i = index - 1;
        myGraph.nodes[index - 1].outEdge = true;
        odd = false;
      }
      else{
        //setting the incoming list of second word
        myGraph.nodes[index - 1].inEdge = true;
        if(myGraph.nodes[index - 1].inComing == NULL){
          myGraph.nodes[index - 1].inComing = new adjacencyList(i);
        }
        else{
          adjacencyList * ptr = myGraph.nodes[index - 1].inComing;
          while(ptr->next != NULL){
            ptr = ptr->next;
          }
          ptr->next = new adjacencyList(i);
        }
        //setting the outgoing list of first node
        if(myGraph.nodes[i].outGoing == NULL){
          myGraph.nodes[i].outGoing = new adjacencyList(index - 1);
        }
        else{
          adjacencyList * ptr = myGraph.nodes[i].outGoing;
          while(ptr->next != NULL){
            ptr = ptr->next;
          }
          ptr->next = new adjacencyList(index - 1);
        }
        
        // cout<<"inedge "<<index<<endl;
        odd = true;
      } 
    }
    //graph stored
    Graph newgraph = myGraph;
    //now all the collapse changes will be done on newgraph;

    myGraph.checkThird();

   cin>>word;
   while(cin>>word){
    if(word==-1) break;
    int first = word;
    cin >> word;
    //initial similarity condition being implemented here
    //first is similar to second
    myGraph.nodes[first - 1].similarity[word - 1] = 1;
    if(SN==NULL){
      SN = new similarNodes();
      SN->first = first - 1;
      SN->second = word - 1;
      SN->next = NULL;
    }
    else{
      similarNodes *s = SN;
      while(s->next != NULL){
        s = s->next;
      }
      s->next = new similarNodes();
      s->next->first = first - 1;
      s->next->second = word - 1;
      s = s->next;
      s->next = NULL;
    }

   }

  // cout<< " line 103"<<endl;

   similarNodes *s = SN;
   while(s!=NULL){
     myGraph.dfs(s->first, s->second);
     s = s->next;
   }
   //for the second and third conditions 
   //now all similarity relations are updated

    myGraph.foo();
    myGraph.setEdges();
    

  string filen = "outgraph.txt";
  ofstream ofile;
  ofile.open(filen);
  ofile << "Source: ";
  // cout << numNodes << endl;
  for(int i=0; i<numNodes; i++){
    // cout<<"--"<<endl;
    if(myGraph.nodes[i].inEdge==false){
      // ofile<<"--";
      ofile << i+1 << " ";
    }
  }
  ofile<<"\n";
  // cout<<endl;

  myGraph.print(ofile);

    return 0;
}
