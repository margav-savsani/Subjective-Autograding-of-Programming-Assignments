#ifndef GRAPH_BST_CPP
#define GRAPH_BST_CPP

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef GRAPH_BST_H
#include "Graph.h"
#endif

// Add code as appropriate for your implementation

void Graph::DFS(Node &node, int parent){
    cout<<node.value<<" "<<parent<<endl<<endl;
    cout<<node.no_of_visits<<endl<<endl;
    node.neighbours->print_list();
    tree->insert(node.value);
    static int time = -1;
    time++;
    if (node.arr_time == -2) node.arr_time=time;
    node.no_of_visits++;
    if ((node.no_of_visits == 1) && (parent1[node.value] == -1)){
      parent1[node.value] = parent;
      DFS_array[node.value] = parent;
    }
    else if ((node.no_of_visits == 2) && (parent1[node.value] != -1) && (parent2[node.value] == -1)){
      parent2[node.value] = parent;
    }
    listOfObjects* a = node.neighbours;
    int back_index = node.value;
    while(a != nullptr){
      if (node.value == 3) cout<<"Hi1"<<endl;
      if ((nodes[a->object].no_of_visits == 2) && (nodes[a->object].value != parent1[node.value]) && (nodes[a->object].value != parent2[node.value])){
        
        if((nodes[a->object].no_of_visits == 1) && (nodes[a->object].arr_time < node.arr_time)){
          back_index = nodes[a->object].value;
          for (int i=node.value;i!=back_index;i=parent1[i]){
            in_cycle[i] = true;
          }
        }
      }
      
      if (node.value == 3) cout<<"Hi2"<<endl;


      if ((nodes[a->object].no_of_visits < 2) && (nodes[a->object].value != parent1[node.value]) && (nodes[a->object].value != parent2[node.value])){
        if (node.value == 3) {cout<<"Hi3"<<endl;}
        if((nodes[a->object].no_of_visits == 1) && (nodes[a->object].arr_time < node.arr_time)){
        if (node.value == 3) cout<<"Hi4"<<endl;
          back_index = nodes[a->object].value;
          for (int i=node.value;i!=back_index;i=parent1[i]){
            in_cycle[i] = true;
          }
        }
        cout<<"DFS Starting"<<endl;
        DFS(nodes[a->object], node.value);
        cout<<"DFS Over"<<endl;
      }
      a = a->next;
    }

    if (parent2[node.value] != -1){
      parent2[node.value] = -1;
    }

    else if (parent1[node.value] != -1){
        parent1[node.value] = -1;
    }
    return;
  }
void Graph::modifiedDFS() {
  for (int i=0;i<numNodes;i++){
    if (nodes[i].no_of_visits == 0){
      no_conn_comp++;
      DFS(nodes[i],-1);
    }
  }
}

void Graph::printResults() {
  cout<<no_conn_comp<<endl;
  int one = 0,two = 0, num = 0;
  for(int i=0;i<numNodes;i++){
    if (nodes[i].no_of_visits == 1) one++;
    else if (nodes[i].no_of_visits == 2) two++;
    if (in_cycle[i]) num++;
  }
  cout<<one<<endl;
  cout<<two<<endl;
  cout<<num<<endl;
  tree->printBST("",false);
}

#endif
