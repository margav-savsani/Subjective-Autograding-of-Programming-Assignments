
#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef GRAPH_BST_H
// #include "Graph.h"
#endif

class cn{
  public:
  int val; //max value representing the component
  int *snode; //all nodes int hte component
  int *outedges; 
  int *inedges;
  cn(int numNodes){
    val = -1;
    snode = new int[numNodes];
    outedges = new int[numNodes];
    inedges = new int[numNodes];
    for(int i=0; i<numNodes; i++){
      snode[i] = -1;
      outedges[i] = -1;
      inedges[i] = -1;
    }
  }
};

class similarNodes{
  public:
  int first;
  int second;
  similarNodes *next;
};

class adjacencyList{
  public:
    int nodeIndex;
    adjacencyList *next;
    adjacencyList(){
      nodeIndex = -1;
      next = NULL;
    }
    adjacencyList(int i){
      nodeIndex = i;
      next = NULL;
    }

};

class Node {
  public:
    bool inEdge;
    bool outEdge; 
    adjacencyList *inComing;
    adjacencyList *outGoing;
    int *similarity;

    int componentNo;

    bool visited;


    Node(){
      inEdge = false;
      outEdge = false;
      inComing = NULL;
      outGoing = NULL;
      similarity = NULL;

      componentNo = -1;

      visited = false;
    }
};



class Graph {
  public:
  int numNodes;
  Node *nodes;
  cn **collapsedNodes;
  int NumConnectedComponent;
  int NumEdges;
  // int **similar;

  // Add appropriate fields as necessary for your implementation
  
 public:
   Graph(int nNodes, string gFileName) {
    NumEdges = 0;
    NumConnectedComponent = 0;
    collapsedNodes = new cn* [numNodes];
    numNodes = nNodes;
    nodes = new Node[numNodes];
    for(int i=0; i<nNodes; i++){
      nodes[i].similarity = new int[numNodes];
      for(int j=0; j<numNodes; j++){
        nodes[i].similarity[j] = 0;
      }
      collapsedNodes[i] = NULL;
    }
    //set the similarity to zero for every node
   }

   void checkThird(){
    // cout<<" entered checkThird"<<endl;
    //third condition of similarity
    for(int i=0; i<numNodes; i++){
      if ( nodes[i].inComing && nodes[i].inComing->next == NULL ){
        cout<< nodes[i].inComing->nodeIndex << endl;
        //only one incoming edge
        nodes[i].similarity[nodes[i].inComing->nodeIndex] = 1;
      }
    }
    // cout<<" returned from checkThird"<<endl;
   }

  bool checkSecond(int x, int y){
  
        bool similar = false;

        // if(nodes[x].similarity)

        adjacencyList *xptr = nodes[x].inComing;
        while(xptr){
          bool flag = false;
          adjacencyList *yptr = nodes[y].inComing;
          while(yptr){
            if( nodes[xptr->nodeIndex].similarity[yptr->nodeIndex] == 1 ){
              flag = true;
            }
            yptr = yptr->next;
          }
          if(flag == false){
            //if even one iptr didnt get a similar node with nodes[j].incoming
            //then i is not similar to j by this condition
            similar = false;
            break;
          }
          xptr = xptr->next;
          similar = true;
        }

        if(similar==false) return similar;

        adjacencyList *yptr2 = nodes[y].inComing;
        while(yptr2){
          bool flag = false;
          adjacencyList *xptr2 = nodes[x].inComing;
          while(xptr2){
            if( nodes[yptr2->nodeIndex].similarity[xptr2->nodeIndex] == 1 ){
              flag = true;
            }
            xptr2 = xptr2->next;
          }
          if(flag == false){
            //if even one iptr didnt get a similar node with nodes[j].incoming
            //then i is not similar to j by this condition
            similar = false;
            break;
          }
          yptr2 = yptr2->next;
          similar = true;
        }

        if(similar == false) return similar;

        //update the similarity for (x,y) and (y,x)
        nodes[x].similarity[y] = 1;
        nodes[y].similarity[x] = 1;

        return similar;

 
  }

  void dfs(int x, int y){
    // cout << "dfs"<<endl;
    checkSecond(x , y);
    // cout<< "passed check second"<<endl;
    if( nodes[x].similarity[y] == 0 ){
      //if x is not similar to y 
      return;
    }

    adjacencyList *xtemp = nodes[x].outGoing;
    while(xtemp){
      bool flag = false;
      adjacencyList *ytemp = nodes[y].outGoing;
      while(ytemp){
        // if(nodes[])
        dfs(xtemp->nodeIndex, ytemp->nodeIndex);
        ytemp = ytemp->next;
      }
      xtemp = xtemp->next;
    }

  }

  int maxfind(int x, int maxx, int pos){
    // if( nodes[x].visited == false )
    nodes[x].visited = true;
    for(int i=0; i<numNodes; i++){

      if(nodes[i].visited == false && (nodes[x].similarity[i] == 1 || nodes[i].similarity[x] == 1 )){
            for(int cc=0; cc<numNodes; cc++){

              if( collapsedNodes[pos]->snode[cc] == i )
              {
                //already there 
                break;
              }
              if( collapsedNodes[pos]->snode[cc] == -1)
              {
                //added to each node the ifo tha which component it belong to 
                collapsedNodes[pos]->snode[cc] = i;
                nodes[i].componentNo = pos;
                break;
              }

            }
            maxx = max(i, maxx);
            int t = maxfind( i, maxx, pos);
            // cout<<" maxx "<<maxx << "maxfind "<<t <<endl;
          maxx = max(maxx, t);
          collapsedNodes[pos]->val = maxx;
      }

    }
    return maxx;
  }

  void foo(){

    int maxx = -1;
    for(int i=0; i<numNodes; i++)
    {
      maxx = i;
      if(nodes[i].visited == true)
      {
        continue;
      }
        NumConnectedComponent++;
        collapsedNodes[i] = new cn(numNodes);
        collapsedNodes[i]->snode[0] = i;
        nodes[i].componentNo = i;
      
      maxx = maxfind(i, maxx, i);
      collapsedNodes[i]->val = maxx;

    }

  }

  void setEdges(){
    for(int i=0; i<numNodes; i++)
    {
      if(collapsedNodes[i] == NULL) continue;
      for(int n1=0; n1<numNodes; n1++)
      {
        if(collapsedNodes[i]->snode[n1] == -1) break;
        adjacencyList *outptr = nodes[collapsedNodes[i]->snode[n1]].outGoing;
        while(outptr != NULL){
          if( nodes[outptr->nodeIndex].componentNo != i  ){
            // cout<<"line 269"<<endl;
            for(int o=0; o<numNodes; o++){
              if( collapsedNodes[i]->outedges[o] == nodes[outptr->nodeIndex].componentNo ) break;
              if( collapsedNodes[i]->outedges[o] == -1){
                collapsedNodes[i]->outedges[o] = nodes[outptr->nodeIndex].componentNo;
                NumEdges++;
                break;
              }
            } 
          }
          outptr = outptr->next;
        }
        //outedge for each node being checked

        adjacencyList *inptr = nodes[collapsedNodes[i]->snode[n1]].inComing;
        while(inptr != NULL){
          if( nodes[inptr->nodeIndex].componentNo != i  ){
            for(int o=0; o<numNodes; o++){
              if( collapsedNodes[i]->inedges[o] == -1){
                collapsedNodes[i]->inedges[o] = nodes[inptr->nodeIndex].componentNo;
                break;
              }
            } 
          }
          inptr = inptr->next;
        }

      }

    }
  }

 void print( ofstream& ofile){

  ofile << "\nSimilar Nodes: ";
  // cout << numNodes << endl;
  for(int i=0; i<numNodes; i++){
    for(int j=0; j<numNodes; j++){
      // cout<<"--"<<endl;
      if(nodes[i].similarity[j] == 1){
        // ofile<<"--";
        ofile << "(" << i+1 << ", " << j+1 <<") ";
        // cout << "(" << i+1 << ", " << j+1 <<")" << endl;
      }
    } 
  }
 
  ofile<<"\n\nCollapsed Graph: \n"<< NumConnectedComponent<<": ";
  for(int i=0; i<numNodes; i++){
    
    if(collapsedNodes[i] != NULL){
      ofile << collapsedNodes[i]->val + 1 << " ";
      // for(int j=0; j<numNodes; j++){
      //   if(collapsedNodes[i]->snode[j] == -1) break;
      //   ofile << collapsedNodes[i]->snode[j]+1 <<" - ";
      // }
      
    }
    
  }
  ofile<<"\n";
  // cout<<endl;

  if(NumEdges == 0){
    ofile<<"\nNO EDGES\n";
    return ;
  }

  ofile<<"\nEdges:\n";
  for(int i=0; i<numNodes; i++){

    if(collapsedNodes[i] != NULL ){
      for(int p=0; p<numNodes; p++)
      {
        if( collapsedNodes[i]->outedges[p] == -1 ) break;
        ofile << collapsedNodes[i]->val + 1 << " " << collapsedNodes[collapsedNodes[i]->outedges[p]]->val + 1 << "\n";
        // cout << collapsedNodes[i]->val + 1 << " " << collapsedNodes[collapsedNodes[i]->outedges[p]]->val + 1 << "\n";
        // ofile<<"\n";
      }
      
    }
    
  }

 }

   

};



