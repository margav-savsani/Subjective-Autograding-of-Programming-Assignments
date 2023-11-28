#ifndef GRAPH_BST_CPP
#define GRAPH_BST_CPP

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef GRAPH_BST_H
#include "Graph.h"
#endif

// Add code as appropriate for your implementation

bool** Graph::similarity(bool ** similar){
  // entering the similar nodes
  int n1,n2;
  while(true){
    cin>>n1>>n2;
    if(n1==-1){
      break;
    }
    n1=n1-1;
    n2--;
    similar[n1][n2]=1;
  }

  for(int i=0;i<numNodes;i++){
    auto temp = nodes[i].prevList;
    if(temp){
      if(!temp->next){
        // cout<<"hi"<<endl;
        similar[i][temp->object]=1;
        // cout<<temp->object<<endl;
      }
    }
  }


  //point 2
  for(int i=0;i<numNodes;i++){
    if(nodes[i].isSource){
      continue;
    }
    for(int j=0;j<numNodes;j++){
      if(nodes[j].isSource){
        continue;
      }
      bool flag = true;
      auto temp1 = nodes[i].prevList;
      while(temp1){
        auto temp2 = nodes[j].prevList;
        //if there is a node in temp2 such that temp1.object and temp2.object are similar, continue looking, else break
        bool flag2 = false;
        while(temp2){
          if(similar[temp1->object][temp2->object]){
            flag2 = true;
            break;
          }
          temp2=temp2->next;
        }
        if(!flag2){
          flag=false;
          break;
        }
        temp1=temp1->next;
      }
      if(!flag){
        continue;
      }

      flag = true;
      temp1 = nodes[j].prevList;
      while(temp1){
        auto temp2 = nodes[i].prevList;
        //if there is a node in temp2 such that temp1.object and temp2.object are similar, continue looking, else break
        bool flag2 = false;
        while(temp2){
          if(similar[temp1->object][temp2->object]){
            flag2 = true;
            break;
          }
          temp2=temp2->next;
        }
        if(!flag2){
          flag=false;
          break;
        }
        temp1=temp1->next;
      }

      if(flag){
        //since the point is a symmetric definition, we add both relations to the matrix
        similar[i][j]=1;
        similar[j][i]=1;
      }

    }
  }

  return similar;
}

void Graph::collapse(bool** similar,int n){
  //runs a DFS on the nodes till we reach all nodes in the same component of the graph with adjacency matrix given by similar
  nodes[n].classed=true;
  auto temp = classes->next->object;
  if(temp){
    while (temp->next)
    {
      temp=temp->next;
    }
    temp->next=new listOfObjects<int>(n);    
  }
  else{
    classes->next->object = new listOfObjects<int>(n);
  }
  for(int i=0;i<numNodes;i++){
    if(similar[n][i] && !nodes[i].classed){
      collapse(similar,i);
    }
  }
}

void Graph::printEdges(listOfObjects<listOfObjects<int>*>* eqclasses,listOfObjects<int>* maxes,int count){
  auto t = eqclasses;
  auto s = maxes;
  //fixing the value of max for each node
  while(t){
    auto t1 = t->object;
    while(t1){
      nodes[t1->object].max=s->object;
      t1=t1->next;
    }
    t=t->next;
    s=s->next;
  }
  //converting to a max array 
  int* maxarray = new int[count];
  s = maxes;
  int index=0;
  while(s){
    maxarray[index]=s->object;
    s=s->next;
    index++;
  }

  //creating an adjacency matrix for our collapsed graph
  bool** edges = new bool*[count];
  for(int i=0;i<count;i++){
    edges[i] = new bool[count];
  }

  for(int x=0;x<count;x++){
    for(int y=0;y<count;y++){
      edges[x][y]=0;
    }
  }
  int counter=0;
  auto classes = eqclasses;
  while(classes){
    auto temp = classes->object;
    while(temp){
      // cout<<temp->object+1<<" ";
      auto adj = nodes[temp->object].adjacencyList;
      while(adj){
        // add edge from [counter] to [maxes of adj.object] if not exists
        int node = adj->object;
        auto temp1 = maxes;
        int counter2=0;
        while(temp1){
          if(temp1->object==nodes[node].max){
            break;
          }
          counter2++;
          temp1=temp1->next;
        }
        edges[counter][counter2]=1;
        adj=adj->next;
      }
      //end
      temp=temp->next;
    }
    // cout<<endl;

    classes=classes->next;
    counter++;
  }

  // for(int i=0;i<numNodes;i++){
  //   cout<<nodes[i].max<<endl;
  // }
  
  //printing out our edges
  for(int x=0;x<count;x++){
    for(int y=0;y<count;y++){
      if(edges[x][y] && x!=y){
        cout<<maxarray[x]+1<<" "<<maxarray[y]+1<<endl;
      }
    }
  }

}

#endif
