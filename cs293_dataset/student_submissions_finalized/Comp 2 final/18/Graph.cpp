#ifndef GRAPH_BST_CPP
#define GRAPH_BST_CPP
#endif

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef GRAPH_BST_H
#include "Graph.h"
#endif

Graph::Graph(){ //will take into consideration first condition of similarity too
  cin>>numNodes;
  t = 0;
  // num_list=0;
  nodes = new Node[numNodes];
  visited = new int[numNodes];
  // List<int> *null_list = new List<int>(-1);
  // final = new List<List<int>>(*null_list);
  if (nodes == nullptr)
  {
    cerr << "Memory allocation failure." << endl;
    exit(-1);
  }

  for (int i = 0; i < numNodes; i++)
  {
    nodes[i].value = i + 1;
    nodes[i].toadj = nullptr;
    nodes[i].fromadj = nullptr;
    nodes[i].to_degree = 0;
    nodes[i].from_degree = 0;
    nodes[i].source = true;
    nodes[i].similar = nullptr;
    nodes[i].num_similar = 0;
    nodes[i].rep = -1;
    visited[i] = false;
  }
  while(true){ //add the req directed edges
    int a[2];
    cin>>a[0]>>a[1];
    if(a[0]==(-1)) break;
    int n1 = a[0]-1;
    int n2 = a[1]-1;
    List<Node> *adj1 = nodes[n1].toadj;
    List<Node> *adj2 = nodes[n2].fromadj;
    if(nodes[n1].toadj == nullptr){
      nodes[n1].toadj = new List<Node>(nodes[n2]);
    }
    else{
      while(adj1->next!=nullptr){
        adj1=adj1->next;
      }   
      adj1->next = new List<Node>(nodes[n2]);
    }
    if(nodes[n2].fromadj == nullptr){
      nodes[n2].fromadj = new List<Node>(nodes[n1]);
      nodes[n2].source = false;
    }
    else{
      while(adj2->next!=nullptr){
        adj2=adj2->next;
      }   
      adj2->next = new List<Node>(nodes[n1]);
    }
    nodes[n1].to_degree++;
    nodes[n2].from_degree++;
  }
  while(true){ //first condition of similarity
    int a[2];
    cin>>a[0]>>a[1];
    if(a[0]==(-1)) break;
    int n1 = a[0]-1;
    int n2 = a[1]-1;
    List<Node> *sim1 = nodes[n1].similar;
    nodes[n1].num_similar++;
    if(nodes[n1].similar == nullptr){
      nodes[n1].similar = new List<Node>(nodes[n2]);
    }
    else{
      while(sim1->next!=nullptr){
        sim1=sim1->next;
      }   
      sim1->next = new List<Node>(nodes[n2]);
    }
  }
}

bool in_List(List<Node> *l, Node n){ //checks if given node is in given list
  while(l!=nullptr){
    if(l->value.value==n.value) return true;
    l=l->next;
  }
  return false;
}

void Graph::similar(){
  //let's apply the third condition before second since second can be incfluenced by third
  for(int i=0; i<numNodes; i++){
    if(nodes[i].fromadj!=nullptr && nodes[i].fromadj->next==nullptr){
      nodes[i].num_similar++;
      List<Node> *sim1 = nodes[i].similar;
      if(nodes[i].similar == nullptr){
        nodes[i].similar = new List<Node>(nodes[i].fromadj->value);
      }
      else{
        while(sim1->next!=nullptr){
          sim1=sim1->next;
        }   
        sim1->next = new List<Node>(nodes[i].fromadj->value);
      }
    }
  }
  //third condition done
  //now we have to apply the second condition
  while(true){
    int inc = 0; //this counts the increase in number of pair of similar nodes
    for(int i=0; i<numNodes; i++){
      if(nodes[i].source) continue; //i is not source
      for(int j=i+1; j<numNodes; j++){ //we'll add i to j and j to i's sim list if condition is satisfied
        if(nodes[j].source) continue; //j is not source
        // cout<<nodes[i].value<<" "<<nodes[j].value<<endl;
        List<Node> *from1 = nodes[i].fromadj;
        while(from1!=nullptr){
          int n = from1->value.value;
          List<Node> *from2 = nodes[j].fromadj;
          List<Node> *sim = nodes[n-1].similar;
          while(from2!=nullptr){
            if(in_List(sim, from2->value)) break; //if similar, break
            from2=from2->next;
          }
          if(from2==nullptr) break; //if not broken, means not similar to any
          from1=from1->next;
        }
        if(from1!=nullptr) { //from1 == nullptr means similar condition from one side satisfied, otherwise continue the loop
          continue;
        }
        //now repeat for vice versa
        List<Node> *from3 = nodes[j].fromadj;
        while(from3!=nullptr){
          int n2 = from3->value.value;
          List<Node> *from4 = nodes[i].fromadj;
          List<Node> *sim2 = nodes[n2-1].similar;
          while(from4!=nullptr){
            if(in_List(sim2, from4->value)) break;
            from4=from4->next;
          }
          if(from4==nullptr) break;
          from3=from3->next;
        }
        if(from3!=nullptr) continue;
        //now second condition is satisfied for nodes[i] and nodes[j] so we add the req nodes to req sim list
        if(!in_List(nodes[i].similar,nodes[j])){
          inc++;
          nodes[i].num_similar++;
          List<Node> *sim1 = nodes[i].similar;
          if(nodes[i].similar == nullptr){
            nodes[i].similar = new List<Node>(nodes[j]);
          }
          else{
            while(sim1->next!=nullptr){
              sim1=sim1->next;
            }   
            sim1->next = new List<Node>(nodes[j]);
          }
        }
        if(!in_List(nodes[j].similar,nodes[i])){
          inc++;
          nodes[j].num_similar++;
          List<Node> *sim1 = nodes[j].similar;
          if(nodes[j].similar == nullptr){
            nodes[j].similar = new List<Node>(nodes[i]);
          }
          else{
            while(sim1->next!=nullptr){
              sim1=sim1->next;
            }   
            sim1->next = new List<Node>(nodes[i]);
          }
        }
      }
    }
    if(inc==0) break; //if no increase, break the while loop
  }
}

int partition(int start, int end, int *a){ //for sorting
  int p = a[end];
  int i = start-1;
  for(int j = start; j<end; j++){
    if(a[j]<p){
      i++;
      int temp = a[i];
      a[i] = a[j];
      a[j] = temp;
    }
  }
  int temp = a[i+1];
  a[i+1] = a[end];
  a[end] = temp;
  return i+1;
}

void sort(int start, int end, int *a){ //to sort the final list of pairs of similar nodes according to order given on piazza
  if(start<end){
    int p = partition(start, end, a);
    sort(start, p-1, a);
    sort(p+1, end, a);
  }
}

int maxima(List<int> *n1){
  int m = 0;
  List<int> *n = n1;
  while(n!=nullptr){
    if(n->value>m) m = n->value;
    n=n->next;
  }
  return m;
}

void Graph::symmetrize(){ //make similar edge pairs symmetrical
  for(int i=0; i<numNodes; i++){
    for(int j=0; j<numNodes; j++){
      if((in_List(nodes[i].similar, nodes[j])) &&(!in_List(nodes[j].similar, nodes[i]))){
        nodes[j].num_similar++;
        List<Node> *sim1 = nodes[j].similar;
        if(nodes[j].similar == nullptr){
          nodes[j].similar = new List<Node>(nodes[i]);
        }
        else{
          while(sim1->next!=nullptr){
            sim1=sim1->next;
          }   
          sim1->next = new List<Node>(nodes[i]);
        }
      }
      if((!in_List(nodes[i].similar, nodes[j])) &&(in_List(nodes[j].similar, nodes[i]))){
        nodes[i].num_similar++;
        List<Node> *sim1 = nodes[i].similar;
        if(nodes[i].similar == nullptr){
          nodes[i].similar = new List<Node>(nodes[j]);
        }
        else{
          while(sim1->next!=nullptr){
            sim1=sim1->next;
          }   
          sim1->next = new List<Node>(nodes[j]);
        }
      }
    }
  }
}

void Graph::dfs(int v, List<int> *l){ //similar to dfs on a graph, to get the list of connected nodes
  visited[v] = true;
  List<int> *n = l;
  if(l == nullptr){
    l = new List<int>(v);
  }
  else{
    while(n->next!=nullptr){
      n=n->next;
    }   
    n->next = new List<int>(v);
  }
  List<Node> *n2 = nodes[v].similar;
  while(n2!=nullptr){
    if(!visited[n2->value.value - 1]){
      dfs(n2->value.value - 1, l);
    }
    n2=n2->next;
  }
}

void Graph::rep_updator(){//this function is supposed to update the rep values of each node, which is the max value in the connected component of which the given node is a part
  for(int i=0; i<numNodes; i++){
    if(!visited[i]){
      List<int> *l = new List<int>(-1);
      dfs(i, l);
      int m = maxima(l);
      while(l!=nullptr){
        nodes[l->value].rep = m;
        l=l->next;
      }
    }
  }
}

void Graph::coll_source(){ //returns the array with indices of sources of the collapsed graph
  int a[numNodes];
  for(int i=0; i<numNodes; i++){
    a[i] = -1;
  }
  for(int i=0; i<numNodes; i++){
    int m = nodes[i].rep;
    int j;
    for(j=0; j<t; j++){
      if(m==a[j]) break;
    }
    if(j==t){
      a[t] = m;
      t++;
    }
  }
  sort(0,t-1,a);
  coll_sources = new int[t];
  for(int i=0; i<t; i++){
    coll_sources[i] = a[i];
  }
} 

void Graph::printResult(string FileName){ //this is the final function that is called in the main file
  similar();
  ofstream f;
  f.open(FileName);
  f<<"Source nodes:";
  for(int i=0; i<numNodes; i++){
    if(nodes[i].source) f<<" "<<nodes[i].value;
  }
  f<<endl<<endl;
  f<<"Similar node pairs:";
  for(int i=0; i<numNodes; i++){
    int sim[nodes[i].num_similar];
    List<Node> *sim1 = nodes[i].similar;
    for(int j=0; j<nodes[i].num_similar; j++){
      sim[j] = sim1->value.value;
      sim1= sim1->next;
    }
    //made the array containing values of similar nodes, now sort it
    sort(0, nodes[i].num_similar - 1, sim);
    //now print it
    for(int j=0; j<nodes[i].num_similar; j++){
      f<<" ("<<nodes[i].value<<", "<<sim[j]<<")";
    }
  }
  f<<endl<<endl;
  f<<"Collapsed graph:"<<endl<<endl;
  symmetrize();
  rep_updator();
  coll_source();
  //printing the collapsed graph
  f<<t<<":";
  for(int i=0; i<t; i++){
    f<<" "<<coll_sources[i]+1;
  }
  f<<endl;
  //now we will form the edges wrt the represented value of nodes in the collapsed graph
  bool visited[numNodes][numNodes];
  for(int i=0; i<numNodes; i++){
    for(int j=0; j<numNodes; j++){
      visited[i][j] = false;
    }
  }
  for(int i=0; i<numNodes; i++){
    List<Node> *n = nodes[i].toadj;
    while(n!=nullptr){
      visited[nodes[i].rep][nodes[n->value.value-1].rep] = true;
      n=n->next;
    }
  }
  for(int i=0; i<numNodes; i++){
    visited[i][i] = false; //no self edges to be taken into account
  }
  for(int i=0; i<numNodes; i++){
    for(int j=0; j<numNodes; j++){
      if(visited[i][j]){
        f<<i+1<<" "<<j+1<<endl;
      }
    }
  }
}