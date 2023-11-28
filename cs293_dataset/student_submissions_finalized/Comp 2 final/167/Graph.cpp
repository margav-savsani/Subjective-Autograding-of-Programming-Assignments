#ifndef GRAPH_BST_CPP
#define GRAPH_BST_CPP

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef GRAPH_BST_H
#include "Graph.h"
#endif
void Graph::intersection(int i,int j){
  bool f;
  listOfObjects<int> * a=nodes[i].group;
  listOfObjects<int> * b=nodes[j].group;
  listOfObjects<int> * c=nodes[i].group;
  while(b!=NULL){
    f=false;
    a=nodes[i].group;
    while(a!=NULL){
      if(a->object==b->object){ f=true; break;}
      a=a->next;
    }
    if(f==false) {
      listOfObjects<int> *d=c;
      if(d==NULL){ c=new listOfObjects<int> (b->object);}
      else{
        while(d->next!=NULL){
          d=d->next;
        }
        d->next=new listOfObjects<int> (b->object);
      }
    }
    b=b->next;
  }
  nodes[j].group=NULL;
}
bool Graph::similarnodes(int a,int b){
  listOfObjects<int> *sic=si;
  listOfObjects<int> *soc=so;
  while(sic!=NULL){
    if(sic->object==b && soc->object==a){return true;}
    sic=sic->next;
    soc=soc->next;
  }
  if(nodes[a-1].parent==NULL || nodes[b-1].parent==NULL){return false;}
    bool b1,b2;
    listOfObjects<int> *p1=nodes[a-1].parent;
    listOfObjects<int> *p2=nodes[b-1].parent;
    while(p1!=NULL){
      b1=false;
      p2=nodes[b-1].parent;
      while(p2!=NULL){
        bool b=similarnodes(p1->object,p2->object);
        if(b==true){ b1=true;break; }
        p2=p2->next;
      }
      if(b1==false) return false;
      p1=p1->next;
    }
  while(p2!=NULL){
      b2=false;
      p1=nodes[a-1].parent;
      while(p1!=NULL){
        bool b=similarnodes(p2->object,p1->object);
        if(b==true){ b2=true; break;}
        p1=p1->next;
      }
      if(b2==false) return false;
      p2=p2->next;
    }
    return true;
}
bool Graph::check(int x,int y){
  listOfObjects<int> *n=nodes[y].group;
  while(n!=NULL){
    if(n->object==x) return true;
    n=n->next;
  }
  return false;
}
void Graph::newedge(int w,int m){
  listOfObjects<int> *n=nodes[w].group;
  listOfObjects<int> *d=dest;
  listOfObjects<int> *s=src;
  while(d!=NULL){
      if(check(d->object,w)) d->object=m;
      d=d->next;
    }
  while(s!=NULL){
      if(check(s->object,w)) s->object=m;
      s=s->next;
    }
  bool q;
  listOfObjects<int> *d1=dest;
  listOfObjects<int> *s1=src;
  listOfObjects<int> *l1=f1;
  listOfObjects<int> *l2=f2;
  listOfObjects<int> *c1=f1;
  listOfObjects<int> *c2=f2;
  while(d1!=NULL){
    q=false;
    while(c1!=nullptr){
      if(c1->object==d1->object && s1->object==c2->object) q=true;
      c2=c2->next;
      c1=c1->next;
    }
    if(q){
        if(l1==NULL){ 
          f1 = new listOfObjects<int> (d1->object);
        }
        else{
        while(l1->next!=NULL){
          l1=l1->next;
        }
        l1->next=new listOfObjects<int> (d1->object);
        }
        if(l2==NULL){ 
          f2 = new listOfObjects<int> (s1->object);
        }
        else{
        while(l2->next!=NULL){
          l2=l2->next;
        }
        l1->next=new listOfObjects<int> (s1->object);
    }
    }
    d1=d1->next;
    s1=s1->next;
  }
  
}
void Graph::printResults() {
  graphfinal<<"Source nodes: ";
  for(int i=0;i<numNodes;i++){
    if(nodes[i].source){
      graphfinal<<i+1<<" ";
    }
  }
  graphfinal<<endl<<endl<<"Similar node pairs: ";
  int n1,n2;
  while (cin>>n1>>n2 ){ 
      if(n1<0 && n2<0) break;
      graphfinal<<"("<<n1<<","<<n2<<") ";
      listOfObjects<int> *sic=si;
      listOfObjects<int> *soc=so;
      if(sic==NULL){ 
        si= new listOfObjects<int> (n2);
      }
      else{
        while(sic->next!=NULL){
          sic=sic->next;
        }
        sic->next=new listOfObjects<int> (n2);
      }
      if(soc==NULL){ 
        so= new listOfObjects<int> (n1);
      }
      else{
        while(soc->next!=NULL){
          soc=soc->next;
        }
        soc->next=new listOfObjects<int> (n1);
      }
  }
  for (int i = 0; i < numNodes; i++) {
       if(nodes[i].parents==1){
            graphfinal<<"("<<i+1<<","<<nodes[i].parent->object<<") ";
            listOfObjects<int> *sic=si;
            listOfObjects<int> *soc=so;
            if(sic==NULL){ 
              si= new listOfObjects<int> (nodes[i].parent->object);
            }
            else{
              while(sic->next!=NULL){
                sic=sic->next;
              }
              sic->next=new listOfObjects<int> (nodes[i].parent->object);
            }
            if(soc==NULL){ 
              so= new listOfObjects<int> (i+1);
            }
            else{
              while(soc->next!=NULL){
                soc=soc->next;
              }
              soc->next=new listOfObjects<int> (i+1);
            }
       }
  }
  bool h;
  for(int k=1;k<numNodes+1;k++){
    for(int j=1;j<numNodes+1;j++){
        h=false;
        listOfObjects<int> *sic=si;
        listOfObjects<int> *soc=so;
        while(sic!=NULL){
          if(soc->object==k && sic->object==j){h=true;}
          sic=sic->next;
          soc=soc->next;
        }
        if(h==false){
        if(similarnodes(k,j)){
          graphfinal<<"("<<k<<","<<j<<") ";
          listOfObjects<int> *h1=so;
          listOfObjects<int> *h2=si;
          if(h1==NULL || h2==NULL){ 
            si= new listOfObjects<int> (j);
            so= new listOfObjects<int> (k);
          }
          else{
            while(h1->next!=NULL || h2->next!=NULL){
              h1=h1->next;
              h2=h2->next;
            }
            h1->next=new listOfObjects<int> (k);
            h2->next=new listOfObjects<int> (j);
          }
        }
      }
    }
  }
  // collapse graph----------------------->
  bool u,w;
  listOfObjects<int> *q=so;
  listOfObjects<int> *r=si;
  for(int g=0;g<numNodes;g++){
    nodes[g].group=new listOfObjects<int> (nodes[g].value);
  }
  while(q!=NULL){
    u=false;
    w=false;
    listOfObjects<int> * z=nodes[q->object-1].group;
    listOfObjects<int> * v=nodes[r->object-1].group;
    if(z->object==r->object) u=true;
    if(v->object==q->object) w=true;
    while(z->next!=NULL){
      if(z->next->object==r->object) u=true;
      z=z->next;
    }
    while(v->next!=NULL){
      if(v->next->object==q->object) w=true;
      v=v->next;
    }
    if(u==false) z->next=new listOfObjects<int> (r->object);
    if(w==false) v->next=new listOfObjects<int> (q->object);
    q=q->next;
    r=r->next;
  }
  
  bool p=false;
  for(int g=0;g<numNodes;g++){
    for(int d=0;d<numNodes;d++){
      if(d==g) continue;
      listOfObjects<int> * y=nodes[g].group;
      listOfObjects<int> * i=nodes[d].group;
      while(y!=NULL){
        while(i!=NULL){
          if(y->object==i->object){ 
            intersection(g,d);
            }
          i=i->next;
        }
        y=y->next;
      }
    }
  }
  int eqclass=0;
  int m=-1;
  for(int g=0;g<numNodes;g++){
    listOfObjects<int> * y=nodes[g].group;
    if(y!=NULL) eqclass++;
  }
  graphfinal<<endl<<endl<<"Collapsed graph: "<<endl<<endl<<eqclass<<": ";
  bool t;
  for(int g=0;g<numNodes;g++){
    t=false;
    listOfObjects<int> * y=nodes[g].group;
    while(y!=NULL){
      t=true;
      if(m<y->object){ m=y->object; }
      y=y->next;
    }
    if(t==true){
      graphfinal<<m<<" ";
      newedge(g,m);
    }
  }
  graphfinal<<endl;
  listOfObjects<int> *k1=dest;
  listOfObjects<int> *k2=src;
  listOfObjects<int> *k3=dest;
  listOfObjects<int> *k4=src;
  int y=0;
  bool bb;
  int p1[100];
  int p2[100];
  for(int i=0;i<100;i++){
     p1[i]=0;
     p2[i]=0;
  }
  while(k1!=NULL){
    if(k1->object!=k2->object){
    bb=false;
    for(int i=0;i<100;i++){
      if(p1[i]==k1->object && p2[i]==k2->object) bb=true;
    }
    if(bb==false){
      p1[y]=k1->object;
      p2[y]=k2->object;
    }
    }
    k1=k1->next;
    k2=k2->next;
    y++;
  }
  for(int i=0;i<100;i++){
      if(p1[i]!=0 && p2[i]!=0) {
        graphfinal<<p2[i]<<" "<<p1[i]<<endl;
      }
    }
  
  return;
}

#endif
