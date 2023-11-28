#ifndef GRAPH_BST_CPP
#define GRAPH_BST_CPP

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef GRAPH_BST_H
#include "Graph.h"
#endif

void Graph::printGraph(){
  //opening the file stream
  out.open("outgraph.txt", iostream::app);
  out << numNodes << ":";

  // sorting the list after adding all the elements to it
  DLL<int> Nodes;
  for (int i=0; i<numNodes; i++){
    Nodes.insert(nodes[i].value);
  }

  Nodes.insertionSort();

  // printing the sorted list
  DLLNode<int> *d3 = Nodes.head;
  while (d3!=nullptr){
    out << " " << d3->value;
    d3 = d3->next;
  }

  // sorting the list after adding all the elements to it
  DLL<Pair> Edges;
  for (int i=0; i<numNodes; i++){
    DLLNode<int> *d = nodes[i].outgoing.head;
    while (d!= nullptr){
      Edges.insert(Pair(nodes[i].value,d->value));
      d = d->next;
    }
  }

  Edges.insertionSort();
  
  // printing all the edges
  DLLNode<Pair> *d2 = Edges.head;
  while (d2!=nullptr){
      out << "\n" <<d2->value.n1 << " " << d2->value.n2;
    d2 = d2->next;
  }
  out.close();
}

void Graph::printSources(){
  //opening the file stream
  out.open("outgraph.txt");

  //printing  all the source nodes based on the data of incoming size we already have
  out << "Source Nodes:";
  for (int i=0; i<numNodes; i++){
    if (nodes[i].incomingSize == 0){
      sourceNode[i] = true;
      out << " " << i+1;
    }
  }
  out << "\n" << endl;

  out.close();
}



bool Graph::isSimilar(int m, int n){
  // 1 => similar hence return true
  if (similar[(m-1)*numNodes+(n-1)] == 1){
    return true;
  }
  // 2 => not similar hence return false
  if (similar[(m-1)*numNodes+(n-1)] == 2){
    return false;
  }
  // if source nodes then already have been settled before and hence can not be similar any more hence value 2 stored and false returned
  if (sourceNode[m-1] || sourceNode[n-1]){
    similar[(m-1)*numNodes+(n-1)]=2;
    return false;
  }

  // otherwise we need the settle these edges hence we look at their parents and find their matches
  int count = nodes[m-1].incoming.size();
  // assuming found, changed to false if any one of parent pair is not found
  bool found = true;
  {
    DLLNode<int> *d1 = nodes[m-1].incoming.head;
    while (d1 != nullptr){
      int counter=nodes[n-1].incomingSize;
      DLLNode<int> *d2 = nodes[n-1].incoming.head;
      while (d2 != nullptr){
        // checking if parents are similar or not, if yes then we found one of the parent match, or else we continue our search
        if (isSimilar(d1->value, d2->value)){
          count--;
          break;
        }
        counter--;
        d2 = d2->next;
      }
      // no pair found for this d1 then found is false 
      if (counter == 0){
        found = false;
      }
      d1 = d1->next;
    }
  }

  // only if found in previous case then continue
  if (found){
    //similar to previous loop but with values reversed
    found = true;
    int count2 = nodes[n-1].incoming.size();
    {
      DLLNode<int> *d1 = nodes[n-1].incoming.head;
      while (d1 != nullptr){
        int counter=nodes[m-1].incomingSize;
        DLLNode<int> *d2 = nodes[m-1].incoming.head;
        while (d2 != nullptr){
          if (isSimilar(d1->value,d2->value)){
            count2--;
            break;
          }
          counter--;
          d2 = d2->next;
        }
        if (counter == 0){
          found = false;
        }
        d1 = d1->next;
      }
    }
    
    // if found is still true then we found a similar pair and we update all our entries and return true
    if (found && count == 0 && count2 == 0){
      nodes[m-1].similar.insert(n);
      similarList.insert(Pair(m,n));
      nodes[n-1].similar.insert(m);
      similarList.insert(Pair(n,m));
      similar[(m-1)*numNodes+(n-1)] = 1;
      similar[(n-1)*numNodes+(m-1)] = 1;
      return true;
    }

    //otherwise the pair cannot be similar and return false along with changing the value to 2
    else{
      similar[(m-1)*numNodes+(n-1)] = 2;
      similar[(n-1)*numNodes+(m-1)] = 2;
      return false;
    }
  }
  similar[(m-1)*numNodes+(n-1)] = 2;
  similar[(n-1)*numNodes+(m-1)] = 2;
  return false;
}

// prints similar using the isSimilar function 
void Graph::printSimilar(){
  out.open("outgraph.txt",iostream::app);

  // taking inputs for first condition and updating the similarity data
  int n1,n2;
  while (true){
    cin >> n1;
    cin >> n2;
    if (n1 == -1 || n2 == -1){
      break;
    }
    if (sourceNode[n1-1] && sourceNode[n2-1]){
      similarList.insert(Pair(n1,n2));
      nodes[n1-1].similar.insert(n2);
      similar[(n1-1)*numNodes+(n2-1)]=1;
    }
  }

  // checking for the 3rd condition in problem statement along with updating the similarity data
  for (int i=0; i<numNodes; i++){
    if (nodes[i].incomingSize == 1){
      similar[(i)*numNodes+(nodes[i].incoming.head->value-1)]=1;
      nodes[i].similar.insert(nodes[i].incoming.head->value);
      similarList.insert(Pair(i+1,nodes[i].incoming.head->value));
    }
  }

  // for each pair of vertices we check whether they are similar or not only if they are not yet settled i.e. value stored is 0
  for (int i=0; i<numNodes; i++){
    for (int j=0; j<numNodes; j++){
      if (similar[(i)*numNodes+(j)] == 0){
        isSimilar(i+1, j+1);
      }
    }
  }

  // sorting and printing this similarity pairs
  similarList.insertionSort();
  DLLNode<Pair> *d = similarList.head;
  out << "Similar Node Pairs:";
  while(d != nullptr){
    out << " (" << d->value.n1 << ", " << d->value.n2 << ")";
    d = d->next;
  }
  out << "\n" << endl;
  out.close();
}

// the following is the naive implementation of finding similar pairs

/*
void Graph::printSimilar(){
  out.open("outgraph.txt", iostream::app);
  int n1,n2;
  while (true){
    cin >> n1;
    cin >> n2;
    if (n1 == -1 || n2 == -1){
      break;
    }
    if (sourceNode[n1-1] && sourceNode[n2-1]){
      similarList.insert(Pair(n1,n2));
      nodes[n1-1].similar.insert(n2);
    }
  }

  for (int i=0; i<numNodes; i++){
    if (nodes[i].incomingSize == 1){
      nodes[i].similar.insert(nodes[i].incoming.head->value);
      similarList.insert(Pair(i+1,nodes[i].incoming.head->value));
    }
  }

  while (true){
    bool counter=false;
    for (int i=0; i<numNodes; i++){
      for (int j=0; j<numNodes; j++){
        if (nodes[i].similar.isin(j+1) || sourceNode[i] || sourceNode[j]){
          continue;
        }
        int count = nodes[i].incoming.size();
        {
          DLLNode<int> *d1 = nodes[i].incoming.head;
          while (d1 != nullptr){
            DLLNode<int> *d2 = nodes[j].incoming.head;
            while (d2 != nullptr){
              if (nodes[d1->value-1].similar.isin(d2->value)){
                count--;
                break;
              }
              d2 = d2->next;
            }
            d1 = d1->next;
          }
        }

        int count2 = nodes[j].incoming.size();
        {
          DLLNode<int> *d1 = nodes[j].incoming.head;
          while (d1 != nullptr){
            DLLNode<int> *d2 = nodes[i].incoming.head;
            while (d2 != nullptr){
              if (nodes[d1->value-1].similar.isin(d2->value)){
                count2--;
                break;
              }
              d2 = d2->next;
            }
            d1 = d1->next;
          }
        }

        if (count == 0 && count2 == 0){
          nodes[i].similar.insert(j+1);
          similarList.insert(Pair(i+1,j+1));
          nodes[j].similar.insert(i+1);
          similarList.insert(Pair(j+1,i+1));
          counter = true;
        }
      }
    }
    if (!counter){
      break;
    }
  }

  similarList.insertionSort();
  DLLNode<Pair> *d = similarList.head;
  out << "Similar Node Pairs:";
  while(d != nullptr){
    out << " (" << d->value.n1 << ", " << d->value.n2 << ")";
    d = d->next;
  }
  out << "\n" << endl;
  out.close();
}
*/

void Graph::printCollapsed(){
  out.open("outgraph.txt", iostream::app);

  // creating an undirected graph for symmetric closer
  GraphUndirected similarityGraph(numNodes);

  // adding the similarity data to this new graph
  DLLNode<Pair> *d = similarList.head;
  while(d != nullptr){
    similarityGraph.addEdgeToGraph(d->value.n1,d->value.n2);
    d = d->next;
  }

  // equivalance class of transitive and symmetric closure will be the connected components of this undirected graph
  similarityGraph.findComponents();

  // updating the connected components data from this new undirected graph to our original graph 
  updateConn(similarityGraph.connectedCompNumber, similarityGraph.compNum);

  // creating a new directed graph which is the collapsed graph that we need 
  Graph collapsedGraph(numConnComp); // its size is same as the number of connected components

  // updating the values stored in the nodes to the largest node value in the connected component
  bool updated[numConnComp];
  for (int i=0; i<numConnComp; i++){
    updated[i] = false;
  }
  for (int i=numNodes-1 ; i>=0; i--){
    if (updated[connectedCompNumber[i]-1]){
      continue;
    }
    collapsedGraph.updateNode(connectedCompNumber[i], i+1);
    updated[connectedCompNumber[i]-1]=true;
  }

  // adding edges to the new collapsed graph based on the original edges
  for (int i=0; i<numNodes; i++){
    for (int j=0; j<numNodes; j++){
      if (connectedCompNumber[j]!=connectedCompNumber[i]){
        if (nodes[i].outgoing.isin(j+1)){
          collapsedGraph.addEdgeToGraph(connectedCompNumber[i],connectedCompNumber[j]);
        }
      }
    }
  }
  
  // printing the collapsed graph
  out << "Collapsed Graph:\n" << endl;
  collapsedGraph.printGraph();
  out.close();
}

// defining DFS for the undirected graph trivial
void GraphUndirected::DoDFS(int x){
  visited[x-1]++;
  connectedCompNumber[x-1] = compNum;

  DLLNode<int> *temp = nodes[x-1].adjacent.head;

  while (temp!=nullptr){
    if (visited[temp->value-1] == 0){
      DoDFS(temp->value);
    }
    temp = temp->next;
  }
  return;
}

void GraphUndirected::findComponents(){
  compNum=0;
  for (int i=0; i<numNodes; i++){
    // if node not visited yet then do a dfs on it along with counting the number of connected components
    if (visited[i]==0){
      compNum ++;
      DoDFS(i+1);
    }
  }
  return;
}


#endif
