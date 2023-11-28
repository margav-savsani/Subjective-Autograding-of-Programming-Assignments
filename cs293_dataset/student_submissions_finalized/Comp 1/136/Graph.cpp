#ifndef GRAPH_BST_CPP
#define GRAPH_BST_CPP

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef GRAPH_BST_H
#include "Graph.h"
#endif

// Add code as appropriate for your implementation

int Graph::check(){
  for(int i=0;i<numNodes;i++){
    if(visited[i]==0){
      return i;
    }
  }
  return -1;
}

void Graph::modifiedDFS() {
  for (int i = 0; i < numNodes; i++) {
    visited[i] = 0;
  }
  //tree->push_back(t);
  int count1=0;
  int* count=&count1;
  BST* b=new BST();
  s=new stack<int>;
  DFS(0,b);
  tree->push_back(b);
  number_of_connected_components++;
  while(true){
    int index=check();
    //cout<<"next index "<<index+1<<endl;
    if(index==-1){
      break;
    }
    BST* t=new BST();
    int count1=0;
    int* count=&count1;
    s=new stack<int>;
    DFS(index,t);
    //cout<<"done"<<endl;
    tree->push_back(t);
    number_of_connected_components++;
    //cout<<"okay..."<<endl;
  }
  return;
}

int Graph::number_of_components_visited_once(){
  int count=0;
  for(int i=0;i<numNodes;i++){
    if(visited[i]==1){
      count++;
    }
  }
  return count;
}

int count_number_of_unique_elements(list<int>l){
  int sz=l.size();
  int arr[sz];
  for(int i=0;i<sz;i++){
    arr[i]=l.front();
    l.pop_front();
  }
  int c=1;
  for(int i=1;i<sz;i++){
    int j=0;
    for (j=0;j<i;j++){
      if(arr[i]==arr[j]){
        break;
      }
    }
    if(i==j){
      c++;
    }
  }
  return c;
}

int Graph::number_of_components_visited_twice(){
  int count=0;
  for(int i=0;i<numNodes;i++){
    if(visited[i]==2){
      count++;
    }
  }
  return count;
}

void Graph::store_cyclic_elements(stack<int> *s,int i){
  stack<int> a=*s;
  //cout<<"pushing "<<a.top()+1<<endl;
  //cyclic.push_back(a.top());
  if(a.size()!=0){
  a.pop();
  }
  while(a.top()!=i){
    if(a.size()!=0){
      cyclic.push_back(a.top());
      //cout<<"pushing "<<a.top()+1<<endl;
      a.pop();
    }
  }
  if(a.size()!=0){
    //cout<<"pushing "<<a.top()+1<<endl;
    cyclic.push_back(a.top());
  }
}

bool Graph::check_edge_match(int n1,int n2){
  list<edge*>::iterator it;
  for(it = edges->begin(); it != edges->end(); ++it){
    if((*it)->check(n1,n2)){
      return true;
    }
  }
  return false;
}

void Graph::DFS(int i,BST *b){
  if(visited[i]==2){
    return;
  }
  //cout<<i+1<<endl;
  visited[i]++;
  s->push(i);
  Node curr_node=nodes[i];
  b->insert(curr_node.value);
  //addtoBST(b,curr_node.value);
  list<int> *neighbours=curr_node.neighbours;
  //scout<<curr_node.value<<endl;
  list<int>::iterator it;
  if(neighbours==nullptr){
    return;
  }
  for(it = neighbours->begin(); it != neighbours->end(); ++it){
    if(check_edge_match(i,*it)){
      if(visited[*it]>0){
        store_cyclic_elements(s,*it);
      }
      DFS(*it,b);
    }
  }
  s->pop();
}

void Graph::printBSTs(){
  list<BST*>::iterator it;
  int count=1;
  for(it = tree->begin(); it != tree->end(); ++it){
    cout<<"Tree "<<count<<":"<<endl;
    (*it)->printBinaryTree((*it)->root,"",false);
    cout<<"-----------------------------------------------"<<endl;
    count++;
  }
}

void Graph::printResults() {
  cout<<"No. of connected components: "<<number_of_connected_components<<endl;
  cout<<"No. of nodes visited once: "<<number_of_components_visited_once()<<endl;
  cout<<"No. of nodes visited twice: "<<number_of_components_visited_twice()<<endl;
  cout<<"No. of nodes that are present in a cycle: "<<count_number_of_unique_elements(cyclic)<<endl;
  cout<<"The BST trees:"<<endl;
  cout<<endl;
  printBSTs();
  return;
}

#endif
