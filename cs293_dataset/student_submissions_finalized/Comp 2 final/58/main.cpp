#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

using namespace std;

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

class Pair{
 public:
  int x1; int x2;

  Pair(int m1,int m2){
    x1=m1;x2=m2;
  }
};

class Node{
 public:
  int value;
  listOfObjects<int> *toNodes;
  listOfObjects<int> *fromNodes;

  Node(){
    toNodes = fromNodes =nullptr;
  }

  void add_to(int m){
    if(toNodes==nullptr){
      toNodes = new listOfObjects<int>(m);
    }

    else{
      listOfObjects<int> *p = toNodes;

      while(p->next!=nullptr){
        p = p->next;
      }

      listOfObjects<int> *q = new listOfObjects<int>(m);
      p->next = q; q->prev = p;
    }
  }

  void add_from(int m){
    if(fromNodes==nullptr){
      fromNodes = new listOfObjects<int>(m);
    }

    else{
      listOfObjects<int> *p = fromNodes;

      while(p->next!=nullptr){
        p = p->next;
      }

      listOfObjects<int> *q = new listOfObjects<int>(m);
      p->next = q; q->prev = p;
    }
  }

};

class DAG{
 public:
  Node *nodes;
  int numNodes;

  DAG(int n){
    numNodes = n;
    nodes = new Node[n];

    for(int i=0;i<n;i++){
      nodes[i].value = i+1;
    }
  }

  void add_edge(int m,int n){
    nodes[m-1].add_to(n);
    nodes[n-1].add_from(m);
  }

  listOfObjects<int> * sourceNodes(){
    listOfObjects<int> *p = nullptr,*currObj;

    for(int i=0;i<numNodes;i++){
      if(nodes[i].fromNodes==nullptr){
        if(p==nullptr){
          p = new listOfObjects<int>(nodes[i].value);
          currObj = p;
        }
        else{
          listOfObjects<int> *q=new listOfObjects<int>(nodes[i].value);

          currObj->next = q; q->prev = currObj;

          currObj = q;
        }
      }
    }

    return p;
  }

  listOfObjects<Pair*> *nodePairs(listOfObjects<Pair*> *inputPairs){
    listOfObjects<Pair*> *p = nullptr,*currObj;
    listOfObjects<int> *sources = sourceNodes();

    // Checking first condition for similar nodes and adding them
    listOfObjects<Pair*> *d1 = inputPairs;
    while(d1!=nullptr){
      int s1=d1->object->x1, s2=d1->object->x2;
      bool b1=false,b2=false;

      listOfObjects<int> *d2 = sources;
      while(d2!=nullptr){
        if(d2->object==s1 && !b1){
          b1 = true;
        }
        if(d2->object==s2 && !b2){
          b2 = true;
        }

        d2 = d2->next;
      }

      if(b1 && b2){
        if(p==nullptr){
          p = new listOfObjects<Pair*>(new Pair(s1,s2));
          currObj = p;
        }
        else{
          listOfObjects<Pair*> *q = new listOfObjects<Pair*>(new Pair(s1,s2));
          currObj->next = q; q->prev = currObj;
          currObj = q;
        }
      }

      d1 = d1->next;
    }

    // Checking third condition and adding if new pairs are found
    for(int i=0;i<numNodes;i++){
      if(nodes[i].fromNodes!=nullptr && nodes[i].fromNodes->next==nullptr){
        int s1=nodes[i].value,s2=nodes[i].fromNodes->object;

        listOfObjects<Pair*> *k = p;bool b = true;
        while(k!=nullptr){
          if(k->object->x1==s1 && k->object->x2==s2){
            b = false;break;
          }

          k = k->next;
        }

        if(b){
          if(p==nullptr){
            p = new listOfObjects<Pair*>(new Pair(s1,s2));
          }
          else{
            k = p;
            while(k->next!=nullptr){
              k = k->next;
            }

            listOfObjects<Pair*> *q = new listOfObjects<Pair*>(new Pair(s1,s2));
            k->next = q; q->prev = k;
          }
        }
      }
    }

    // Checking second condition and adding if new pairs are found
    for(int i=0;i<numNodes;i++){
      for(int j=0;j<numNodes;j++){
        int s1=nodes[i].value,s2=nodes[j].value;
        bool B=true;
        listOfObjects<Pair*> *k = p;
        while(k!=nullptr){
          if(k->object->x1==s1 && k->object->x2==s2){
            B = false;
            break;
          }

          k = k->next;
        }

        listOfObjects<int> *w = sources;
        while(w!=nullptr){
          if(s1==w->object || s2==w->object){
            B = false;
            break;
          }

          w = w->next;
        }
        
        if(B){
          listOfObjects<int> *l1 = nodes[i].fromNodes;
          listOfObjects<int> *l2 = nodes[j].fromNodes;

          bool B1 = true;

          while(l1!=nullptr){
            bool b1 = false;
            l2 = nodes[j].fromNodes;
            while(l2!=nullptr){

              k = p;
              while(k!=nullptr){
                if(k->object->x1==l1->object && k->object->x2==l2->object){
                  b1 = true;
                  break;
                }

                k = k->next;
              }
              
              if(b1){break;}
              l2 = l2->next;
            }

            if(!b1){
              B1 = false;
              break;
            }

            l1 = l1->next;
          }

          if(!B1){continue;}

          bool B2 = true;

          l1 = nodes[i].fromNodes;l2 = nodes[j].fromNodes;

          while(l2!=nullptr){
            bool b1 = false;
            l1 = nodes[i].fromNodes;
            while(l1!=nullptr){
              k = p;
              while(k!=nullptr){
                if(k->object->x1==l2->object && k->object->x2==l1->object){
                  b1 = true;
                  break;
                }

                k = k->next;
              }
              
              if(b1){break;}
              l1 = l1->next;
            }
            if(!b1){
              B2 = false;
              break;
            }

            l2 = l2->next;
          }
          
          if(!B2){continue;}

          
          if(B1 && B2){
            if(p==nullptr){
              p = new listOfObjects<Pair*>(new Pair(s1,s2));
            }
            else{
              k = p;
              while(k->next!=nullptr){
                k = k->next;
              }

              listOfObjects<Pair*> *q = new listOfObjects<Pair*>(new Pair(s1,s2));
              k->next = q; q->prev = k;
              k = q;
              q = new listOfObjects<Pair*>(new Pair(s2,s1));
              k->next = q; q->prev = k;
            }
          }
        }
      }
    }

    return p;
  }
};

int main(int argc, char **argv)
{
  int numNodes;
  cin >> numNodes;
  DAG graph(numNodes);

  listOfObjects<Pair*> *edges = nullptr;

  int a,b;
  while(true){
    cin >> a >> b;
    if(a==-1){
      break;
    }
    else{
      graph.add_edge(a,b);

      if(edges==nullptr){
        edges = new listOfObjects<Pair*>(new Pair(a,b));
      }
      else{
        listOfObjects<Pair*> *t = edges;
        while(t->next!=nullptr){
          t = t->next;
        }

        listOfObjects<Pair*> *t1 = new listOfObjects<Pair*>(new Pair(a,b));
        t->next = t1;t1->prev = t;
      }
    }
  }

  listOfObjects<int> *p = graph.sourceNodes();

  cout <<"Source Nodes:";
  if(p!=nullptr){
    while(p!=nullptr){
      cout << " " << p->object;
      p = p->next;
    }
  }

  cout << endl;

  listOfObjects<Pair*> *inputPairs = nullptr,*currObj;
  while(true){
    cin >> a >> b;
    if(a==-1){
      break;
    }
    else{
      if(inputPairs==nullptr){
        inputPairs = new listOfObjects<Pair*>(new Pair(a,b));
        currObj = inputPairs;
      }
      else{
        listOfObjects<Pair*> *q = new listOfObjects<Pair*>(new Pair(a,b));

        currObj->next = q;
        q->prev = currObj;

        currObj = q;
      }
    }
  }

  cout << endl;

  cout << "Similar node pairs:";
  bool l[numNodes][numNodes];
  for(int i=0;i<numNodes;i++){
    for(int j=0;j<numNodes;j++){
      l[i][j]=0;
    }
  }

  listOfObjects<Pair*> *req = graph.nodePairs(inputPairs);
  while(req!=nullptr){
    l[req->object->x1 -1][req->object->x2 -1] = 1;
    cout << " " << '(' << req->object->x1 << ',' << " " << req->object->x2 << ')';
    req = req->next;
  }

  cout << endl;
  cout << endl << "Collapsed graph:" << endl << endl;

  for(int i=0;i<numNodes;i++){
    for(int j=0;j<numNodes;j++){
      if(i==j){
        l[i][j]=1;
      }

      if(l[i][j]==1){
        l[j][i]=1;
      }
    }
  }

  while(true){

    bool m[numNodes][numNodes];
    for(int i=0;i<numNodes;i++){
      for(int j=0;j<numNodes;j++){
        m[i][j]=0;

        for(int k=0;k<numNodes;k++){
          m[i][j]+= l[i][k]*l[k][j];
        }

        m[i][j]+=l[i][j];
      }
    }

    bool b=true;
    for(int i=0;i<numNodes;i++){
      for(int j=0;j<numNodes;j++){
        if(m[i][j]!=l[i][j]){
          b = false;
          break;
        }
      }

      if(!b){
        break;
      }
    }

    if(b==true){
      break;
    }

    else{
      for(int i=0;i<numNodes;i++){
        for(int j=0;j<numNodes;j++){
          l[i][j]=m[i][j];
        }
      }
    }

  }

  int n[numNodes];
  for(int i=0;i<numNodes;i++){
    n[i] = 0;
  }

  int count =0,c1=0;
  while(c1<numNodes){
    if(n[c1]==0){
      count++;

      for(int i=0;i<numNodes;i++){
        if(l[c1][i]==1){
          n[i] = count;
        }
      }
    }

    c1++;
  }

  listOfObjects<int> *list = nullptr;
  for(int i=1;i<=count;i++){
    int index = 0;
    for(int j=0;j<numNodes;j++){
      if(n[j]==i && j>index){
        index = j;
      }
    }

    if(list==nullptr){
      list = new listOfObjects<int>(index+1);
    }
    else{
      listOfObjects<int> *z = list;
      while(z->next!=nullptr){
        z = z->next;
      }

      listOfObjects<int> *z1 = new listOfObjects<int>(index+1);
      z->next = z1; z1->prev = z;
    }
  }

  int Z[count];int c9 = 0;

  cout << count << ':';
  listOfObjects<int> *har = list;
  while(har!=nullptr){
    Z[c9] =  har->object; c9++;
    cout << " " << har->object;
    har = har->next;
  }
  cout << endl;

  listOfObjects<Pair*> *newedges = nullptr;
  listOfObjects<Pair*> *t2 = edges;

  while(t2!=nullptr){
    int a = t2->object->x1,b=t2->object->x2;

    int a1 = Z[n[a-1]-1], b1 = Z[n[b-1]-1];

    if(newedges==nullptr){
      newedges = new listOfObjects<Pair*>(new Pair(a1,b1));
    }

    else{
      listOfObjects<Pair*> *dink = newedges;
      bool bit =false;

      while(dink!=nullptr){
        if(a1==dink->object->x1 && b1==dink->object->x2){
          bit = true;
          break;
        }
        dink = dink->next;
      }

      if(!bit){
        dink = newedges;
        while(dink->next!=nullptr){
          dink = dink->next;
        }

        listOfObjects<Pair*> *dunk = new listOfObjects<Pair*>(new Pair(a1,b1));
        dink->next = dunk;dunk->prev = dink;
      }
    }
    t2 = t2->next;
  }

  while(newedges!=nullptr){
    int s1=newedges->object->x1,s2=newedges->object->x2;
    if(s1!=s2){
      cout << newedges->object->x1 << " " << newedges->object->x2 << endl;
    }
    
    newedges = newedges->next;
  }
}
