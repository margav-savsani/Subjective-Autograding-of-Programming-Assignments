#ifndef GRAPH_BST_CPP
#define GRAPH_BST_CPP

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef GRAPH_BST_H
#include "Graph.h"
#endif


void Graph::DFS(Node *n, BST *bst){ //dfs where node can be visited twice
  //update bools of visited once and twice
  if(!n->visited_once) n->visited_once=true;
  else n->visited_twice=true;
  arr[this->n] = n->value;
  this->n++;
  bst->insert(n->value);

  //Recur for all adj nodes
  for(int i=0; i<numNodes; i++){
    List<Node> *adj = n->adj;
    while(adj!=nullptr){
      if(adj->value.value == nodes[i].value) break; //check whether adj or not
      adj=adj->next;
    }
    if(adj==nullptr) continue; //not adj
    List<Node> *p = n->parents;
    //first check whether the adj node is in parents list or not
    while(p!=nullptr){
      if(p->value.value==nodes[i].value) break;
      p=p->next;
    }
    if(p!=nullptr) {
      continue; //nodes[i] present in parents list
    }
    if(!nodes[i].visited_twice){
      //add n to parents list of nodes[i]
      List<Node> *p2 = nodes[i].parents;
      if(p2==nullptr){
        nodes[i].parents = new List<Node>(*n);
      }
      else{
        while(p2->next!=nullptr){
          p2=p2->next;
        }
        p2->next=new List<Node>(*n);
      }
      DFS(&nodes[i], bst); //recurrence
    }
  }
}

// Add code as appropriate for your implementation
void Graph::modifiedDFS() {
  for(int i=0; i<numNodes; i++){
    if(!nodes[i].visited_once) { //whichever node is not even visited once, apply dfs considering that as the node
      if(bst->value.root==nullptr){
        BST *first = new BST();
        bst = new List<BST>(*first);
        DFS(&nodes[i],&bst->value);
        }
      else{
        List<BST> *rec = bst;
        while(rec->next!=nullptr){
          rec=rec->next;
        }
        BST *a = new BST();
        rec->next = new List<BST>(*a);
        DFS(&nodes[i],&rec->next->value);
      }
      numConnComp++; //everytime dfs occurs means one more connected component
    }
  }
  //counting number of nodes visited once and twice 
  for(int i=0; i<numNodes; i++){
    if(nodes[i].visited_twice) num_twos++;
  }
  num_ones = numNodes-num_twos;
}

int Graph::in_cycle(){
  int degree[numNodes];
  for(int i=0; i<numNodes; i++){
    degree[i] = nodes[i].degree;
  }
  queue<int> q;
  while(true){
    for(int i=0; i<numNodes; i++){
      if(degree[i]==1 && !nodes[i].visited) {
        q.push(i);
        nodes[i].visited = 1;
      }
    }
    if(q.empty()) break;
    while(!q.empty()){
      int t = q.front();
      q.pop();
      // nodes[t].visited = 1;

      for(int i=0; i<numNodes; i++){
        //check whether adj or not
        List<Node> *adj = nodes[t].adj;
        while(adj!=nullptr){
          if(adj->value.value == nodes[i].value) break; //check whether adj or not
          adj=adj->next;
        }
        if(adj==nullptr) continue; //not adj
        degree[i]--;
      }
    }
  }
  int c = 0;
  for(int i=0; i<numNodes; i++){
    if(degree[i]>1) c++;
  }
  return c;
}

void Graph::printResults() {

  cout<<"No. of connected components: "<<numConnComp<<endl;
  cout<<"No. of nodes visited once: "<<num_ones<<endl;
  cout<<"No. of nodes visited twice: "<<num_twos<<endl;
  num_in_cycle = in_cycle();
  cout<<"No. of nodes that are present in a cycle: "<<num_in_cycle<<endl;
  //print all BSTs
  cout<<endl;
  int i=1;
  cout<<"Total number of BSTs: "<<numConnComp<<endl;
  while(bst!=nullptr){
    cout<<"BST Number "<<i<<endl;
    bst->value.printBST("");
    bst = bst->next;
    i++;
  }

  return;
}

#endif
