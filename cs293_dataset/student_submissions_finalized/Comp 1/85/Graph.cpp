#ifndef GRAPH_BST_CPP
#define GRAPH_BST_CPP

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef GRAPH_BST_H
#include "Graph.h"
#endif
void Graph::DFS1(Node *a,BST *tr){
   a->visit=a->visit+1;
  tr->insert(a->value);
  
  listOfObjects<Node *> *t=a->adj;
  
  while(t != nullptr){
    if (t->object->visit<1){
      DFS1(t->object,tr);
    }
     else if(t->object->visit <2){
        
        DFS1(t->object,tr);
     }

     t=t->next;
  }
  
}

void Graph::DFS(Node *a){
  a->visit=a->visit+1;
 
  
  listOfObjects<Node *> *t=a->adj;
  
  while(t != nullptr){
    if (t->object->visit<1){
      DFS(t->object);
    }
     else if(t->object->visit <2){
        
        DFS(t->object);
     }

     t=t->next;
  }
  
}
void Graph::cycle(Node *a){
    a->color=a->color+1;
 
  
  listOfObjects<Node *> *t=a->adj;
  
  while(t != nullptr){
   if(t->object->color <=1){
        
        cycle(t->object);
     }

     t=t->next;
  }
  
}
// Add code as appropriate for your implementation
void Graph::modifiedDFS() {
  DFS(&nodes[0]);
}

void Graph::printResults() {
  
  int i=0;
  int con=1;
  int n=0;
  int m=0;
  while(i<numNodes){
    
    if(nodes[i].visit==0){
      DFS(&nodes[i]);
      con++;
    }
    if(nodes[i].visit==1){
      n++;
    }
    if(nodes[i].visit==2){
       m++;
    }
    i++;
  }
  cout<<con<<endl;
  cout<<n<<endl;
  cout<<m<<endl;
  cycle(&nodes[0]);
  int e=0;
  while(e<numNodes){
    if(nodes[e].color==0){
      cycle(&nodes[e]);
    }
    e++;
  }
  int y=0;
  for(int i=0;i<numNodes;i++){
    if(nodes[i].color==2){
      y++;
    }
  }
  cout<<y<<endl;
  for(int i=0;i<numNodes;i++){
    nodes[i].visit=0;
  }

  BST *q;
  int r=0;
  int r1=0;
  q=new BST[con];
   DFS1(&nodes[0],&q[0]);
  q[0].printBST(&q[0],"",false); 
  cout<<"TREE NUMBER "<<r1+1<<endl;
  r1++;
  q[r1].root=NULL;
 while(r<numNodes){
  if(nodes[r].visit==0){
    DFS1(&nodes[r],&q[r1]);
    q[r1].printBST(&q[r1],"",false); 
    cout<<"TREE NUMBER "<<r1+1<<endl;
    r1++;
    q[r1].root=NULL;
  }
  r++;
 }
 
  
  
}

#endif
