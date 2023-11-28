#ifndef GRAPH_BST_H
#define GRAPH_BST_H

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif
template <typename T> class listOfObjects {
 public:
  T object;
  listOfObjects<T> *next;
  listOfObjects<T> *prev;
  
  // Constructor
  listOfObjects(T initValue) {object = initValue; next = prev = nullptr;}
  
  // Destructor
  ~listOfObjects() {;}
};

class Node {
 public:
  int value;
  int equi;
  int equi_value;
  int re_value;
  listOfObjects<int> *parents=NULL;
  listOfObjects<int> *child=NULL;
  listOfObjects<int> *s_nodes=NULL;
  //listOfObjects<int> *equi=NULL;
  void addchild(int v) {
    listOfObjects<int> *x=child;
    if(x==NULL){child=new listOfObjects <int> (v);}
    else{
      while(x->next!=NULL){
        x=x->next;
      }
      x->next=new listOfObjects <int> (v);
    }
  }
  void addparent(int v) {
    listOfObjects<int> *x=parents;
    if(x==NULL){parents=new listOfObjects <int> (v);}
    else{
      while(x->next!=NULL){
        x=x->next;
      }
      x->next=new listOfObjects <int> (v);
    }
  }
  void addsim(int v){
     listOfObjects<int> *x=s_nodes;
     bool f=true;
     if(x==NULL){s_nodes=new listOfObjects <int> (v);}
     else{
          if(x->object==v){f=false;}
          else{
               while(x->next!=NULL){
               if(x->next->object==v){f=false;break;}
               x=x->next;
               }
          }
          if(f){x->next=new listOfObjects <int> (v);}
     }
  }

};

class Graph {
     public:
     ofstream graph1;
     string word;
     Node *nodes;
     int numNodes=0;
     listOfObjects<int> *e1=NULL;
     listOfObjects<int> *e2=NULL;
     listOfObjects<int> *sim1=NULL;
     listOfObjects<int> *sim2=NULL;
     //listOfObjects<int> *equi=NULL;

     void similar_nodes(int i,int j){
          listOfObjects<int> *y1=sim1;
          listOfObjects<int> *y2=sim2;
          if(y1==NULL){sim1=new listOfObjects <int> (i);sim2=new listOfObjects <int> (j);}
          else{
               while(y1->next!=NULL){
               y1=y1->next;
               y2=y2->next;
               }
               y1->next=new listOfObjects <int> (i);
               y2->next=new listOfObjects <int> (j);
          }
     }
     
     Graph(){
          
          graph1.open("outgraph.txt");
          cin>>numNodes;
          nodes = new Node[numNodes];
          for (int i = 0; i < numNodes; i++) {
               nodes[i].value = i+1;
               nodes[i].re_value=i+1;
               nodes[i].equi=0;
               nodes[i].equi_value=i+1;
          }
          int x,y;
          while(true){
               cin>>x>>y;
               if(x==-1){break;}
               nodes[y-1].addparent(x);nodes[x-1].addchild(y);
               addedge(x,y);
          }
     }
     void addedge(int l1,int l2){
          listOfObjects<int> *u=e1;
          listOfObjects<int> *v=e2;
          if(u==NULL){e1=new listOfObjects <int> (l1);
                      e2=new listOfObjects <int> (l2);}
          else{
               while(u->next!=NULL){
               u=u->next;
               v=v->next;
               }
               u->next=new listOfObjects <int> (l1);
               v->next=new listOfObjects <int> (l2);
          }
     }
     void print(){
          graph1<<"Source nodes: ";
          for (int i=0;i<numNodes;i++){
          if(nodes[i].parents==nullptr){graph1<<i+1<<" ";}
          }
          graph1<<endl;
     }
     bool recursion(int l,int m){
          listOfObjects<int> *y1=sim1;
          listOfObjects<int> *y2=sim2;
          bool found=false;
          while(y1!=nullptr){
                   if((y1->object==l)&&(y2->object==m)){found=true;break;}
                   y2=y2->next;
                   y1=y1->next;
          }
          if(found){return true;}
          if((nodes[l-1].parents==nullptr) || (nodes[m-1].parents==nullptr)){return false;}
          listOfObjects<int> *p1=nodes[l-1].parents;
          listOfObjects<int> *p2=nodes[m-1].parents;
          found=false;
          while(p1!=nullptr){
               int d=0;
               p2=nodes[m-1].parents;
               while(p2!=nullptr){
                    if(recursion(p1->object,p2->object)){d++;break;}
                    p2=p2->next;
               }
               if(d==0){return false;}
               p1=p1->next;
          }
          p2=nodes[m-1].parents;
          while(p2!=nullptr){
               int d=0;
               p1=nodes[l-1].parents;
               while(p1!=nullptr){
                    if(recursion(p2->object,p1->object)){d++;break;}
                    p1=p1->next;
               }
               if(d==0){return false;}
               p2=p2->next;
          }
          y1=sim1;
          y2=sim2;
          if(y1==NULL){sim1=new listOfObjects <int> (l);sim2=new listOfObjects <int> (m);}
          else{
               while(y1->next!=NULL){
               y1=y1->next;
               y2=y2->next;
               }
               y1->next=new listOfObjects <int> (l);
               y1->next->next=new listOfObjects <int> (m);
               y2->next=new listOfObjects <int> (m);
               y2->next->next=new listOfObjects <int> (l);
          } 
          return true;  
     }
     void similar(){
          graph1<<endl<<"Similar node pairs: ";
          int a[2];
          int p=0;
          int x,y;
          while(true){
               cin>>x>>y;
               if(x==-1){break;}
               similar_nodes(x,y);}
          for (int i=0;i<numNodes;i++){
               listOfObjects<int> *z=nodes[i].parents;
               int k=0;
               if(z!=nullptr){
                   if(z->next==nullptr){similar_nodes(i+1,z->object);}
               }  
          }
          
          for(int l=0;l<numNodes;l++){
               for(int m=l;m<numNodes;m++){
                    recursion(l+1,m+1);
               }
          }
          listOfObjects<int> *y1=sim1;
          listOfObjects<int> *y2=sim2;
          while(y1!=nullptr){graph1<<"("<<(y1->object)<<", "<<(y2->object)<<")"<<" ";y1=y1->next;y2=y2->next;}
          graph1<<endl;
     }  
     void collapse(){
          listOfObjects<int> *y1=sim1;
          listOfObjects<int> *y2=sim2;
          while(y1!=nullptr){ 
                              nodes[y1->object-1].addsim(y1->object);
                              nodes[y2->object-1].addsim(y2->object);
                              nodes[y1->object-1].addsim(y2->object);
                              nodes[y2->object-1].addsim(y1->object);
                              y1=y1->next; y2=y2->next;
          }
          
          int q=0;
          for(int i=0;i<numNodes;i++){
               bool g=false;
               int max=nodes[i].re_value;
               listOfObjects<int> *p1=nodes[i].s_nodes;
               if(nodes[i].equi!=0){g=true;}
               while(p1!=NULL){
                    if(nodes[p1->object-1].re_value>max){max=nodes[p1->object-1].re_value;}
                    if(nodes[i].equi==0){
                         if(nodes[p1->object-1].equi!=0){nodes[i].equi=nodes[p1->object-1].equi;g=true;}
                    }
                    p1=p1->next;
               }
               if(g==false){
                    q++;
                    nodes[i].equi=q;
               }
               p1=nodes[i].s_nodes;
               while(p1!=NULL){
                    nodes[p1->object-1].equi=nodes[i].equi;
                    if(nodes[p1->object-1].re_value<i+1){nodes[p1->object-1].re_value=i+1;}
                    p1=p1->next;
               }

               for(int j=0;j<numNodes;j++){
                    if(nodes[j].equi==nodes[i].equi){nodes[j].re_value=max;}
               }

          }
          graph1<<endl<<"Collapsed graph: "<<endl;
          graph1<<q<<": ";                    //printing how many different groups are formed
          int new_arr[q];
          int h=1;
          int i=0;
          while(i<numNodes && h<=q){
               if(h==nodes[i].equi){new_arr[h-1]=nodes[i].re_value;i=0;h++;}
               else{i++;}
          }
          for(int i=0;i<q;i++){
               graph1<<new_arr[i]<<" ";       //printing values
          }
          graph1<<endl;
          listOfObjects<int> *w1=e1;
          listOfObjects<int> *w2=e2;
          listOfObjects<int> *e11=NULL;
          listOfObjects<int> *e22=NULL;
          while(w1!=NULL){
                          int f1=nodes[w1->object-1].re_value;
                          int f2=nodes[w2->object-1].re_value;
                          if(f1!=f2){
                              bool f=true;
                              listOfObjects<int> *u1=e11;
                              listOfObjects<int> *v1=e22;
                              if(u1==NULL){
                                   e11=new listOfObjects <int> (f1);
                                   e22=new listOfObjects <int> (f2);
                              }
                              else{
                                   if((u1->object==f1) && (v1->object==f2)){f=false;}
                                   else{
                                        while(u1->next!=NULL){
                                        if((u1->next->object==f1) && (v1->next->object==f2)){f=false;break;}
                                        u1=u1->next;
                                        v1=v1->next;
                                        }
                                   }
                                   if(f){
                                        u1->next=new listOfObjects <int> (f1);
                                        v1->next=new listOfObjects <int> (f2);
                                   }
                              }
                         }
                         w1=w1->next;
                         w2=w2->next;
          }
          listOfObjects<int> *w11=e11;
          listOfObjects<int> *w22=e22;
          while(w11!=NULL){
                    graph1<<w11->object<<" "<<w22->object<<endl;    //printing edges after collapsing nodes
                    w11=w11->next;
                    w22=w22->next;
          }
     }

};
#endif