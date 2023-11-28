#include "graph.h"
using namespace std;

void Graph::printResults() {
  cout<<"Source Nodes:  ";
  for (int i=0;i<numNodes;i++){
    if(nodes[i].from==nullptr){
      cout<<i+1<<" ";
    }
    if(i=numNodes-1) cout<<endl;
  }
  similarity13();
  //similarity2();
  cout<<"Similar node pairs: ";
  for(int i=0;i<numNodes;i++){
    for(int j=0;j<numNodes;j++){
      cout<<"("<<i<<", "<<j<<") ";
    }
  }
  cout<<endl;
  return;
}
void Graph::addedge(int a , int b){
  listOfObjects<Node*> *temp1=nodes[a-1].to;
  listOfObjects<Node*> *temp2=nodes[b-1].from;
  if(temp1==nullptr)
  temp1->object=&nodes[b-1];
  else {while (temp1->next!=nullptr)
  {
    temp1=temp1->next;
  }
  temp1->next->object=&nodes[b-1];}
  if(temp2==nullptr)
  temp2->object=&nodes[a-1];
  else 
  {while (temp2->next!=nullptr)
  {
    temp2=temp2->next;
  }
  temp2->next->object=&nodes[a-1];  }
}
void Graph::addsimilarpair(int a , int b){
  similaritymatrix[a-1][b-1]=true;
  checked[a-1][b-1]=true;
}
// void Graph::similarity2(){
//   for(int i=0;i<numNodes;i++){
//     for(int j=0;j<numNodes;j++){
//       if(similaritymatrix[i][j]) continue;
//       if(nodes[i].from==nullptr&&nodes[j].from==nullptr) continue;
//       if(check(i,j,nodes[i].from,nodes[j].from))similaritymatrix[i][j]==true;
//     }
//   }
// }
// bool Graph::check(int i , int j , listOfObjects<Node*> *a,listOfObjects<Node*> *b){
//   listOfObjects<Node*> *c=a,*e=a,*d=b,*f=b;
//   checked[i][j]=true;
//   bool s,t=false;
//   while(c->next!=nullptr){
//     while(d->next!=nullptr){
//       if(checked[c->object->value-1][d->object->value-1])
//         s=similaritymatrix[c->object->value-1][d->object->value-1];
//       else {if(check(c->object->value,d->object->value,c->object->from,d->object->from))s=true;}
//       d=d->next;
//     }
//     c=c->next;
//   }
//   while(f->next!=nullptr){
//     while(e->next!=nullptr){
//       if(checked[f->object->value-1][e->object->value-1])
//         s=similaritymatrix[f->object->value-1][e->object->value-1];
//       else {if(check(f->object->value,e->object->value,f->object->from,e->object->from))t=true;}
//       e=e->next;
//     }
//     f=f->next;
//   }
//   return (s&t);
// }
void Graph::similarity13(){
  for(int i=0;i<numNodes;i++){
    for(int j=0;j<numNodes;j++){
      if(nodes[i].from->object==&nodes[j]&&nodes[i].from->next==nullptr) 
        similaritymatrix[i][j]=true;
    }
  }
}