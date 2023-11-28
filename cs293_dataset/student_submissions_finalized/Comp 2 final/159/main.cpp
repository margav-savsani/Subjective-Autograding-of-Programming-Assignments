#include <iostream>
#include <fstream>
#include <string>
using namespace std;
class adjlist{
   public: 
     int value;
     adjlist* next;
     adjlist(){
        value=0;
        next=nullptr;
     }
     adjlist(int value){
      this->value=value;
      next=nullptr;
     }
};
int max(adjlist* x){
    adjlist* r=x;
    int max=x->value;
    while(r!=nullptr){
        if(max<=r->value){
            max=r->value;
        }
        r=r->next;
    }
    return max;
}
adjlist *return_tail(adjlist* x){
  adjlist *r=x;
  while(r->next!=nullptr){
      r=r->next;
  }
  return r;
}
int length(adjlist* x){
  adjlist* r=x;
  int s=0;
  while(r!=nullptr){
     r=r->next;
     s++;
  }
  return s;
}
void print(adjlist* s,ofstream& f2){
    if(s==nullptr){return;}
    int l=length(s);
    int *arr=new int[l];
    for(int i=0;i<l;i++){
        arr[i]=s->value;
        s=s->next;
    }
    for(int i=0;i<l;i=i+2){
        if(i==0){
        f2<<arr[i]<<" "<<arr[i+1]<<endl;}
        else{
        bool x=false;
        for(int j=0;j<i;j++){
            if(arr[j]==arr[i]&&arr[j+1]==arr[i+1]){
                x=true;
            }
        }
        if(!x){f2<<arr[i]<<" "<<arr[i+1]<<endl;}
        }
    }
  

}

bool present(adjlist* r,int x){
  adjlist* r1=r;
  while(r1!=nullptr){
    if(r1->value==x){
      return true;
    }
    r1=r1->next;
  }
  return false;
}
bool intersect(adjlist* r1,adjlist* r2){
    adjlist* r3=r1;
    adjlist* r4=r2;
    while(r3!=nullptr){
        while(r4!=nullptr){
            if(r3->value==r4->value){
                
                return true;}
            r4=r4->next;

        }
        r3=r3->next;
        r4=r2;
    }
    return false;
}
void add(adjlist* r1,adjlist* r2){
      adjlist* r4=r2;
      adjlist* r5=r1;
      while(r4!=nullptr){
        adjlist* r3=return_tail(r5);
        if(!present(r1,r4->value)){
            r3->next=new adjlist(r4->value);
            
        }
        r4=r4->next;
      }
}
class Node{
    public:
       int value;
       adjlist* outgoing;
       adjlist* incoming;
       adjlist* similar;
       Node(){
          value=0;
        outgoing=nullptr;
        incoming=nullptr;
        similar=nullptr;
       }
       Node(int x){
        value=x;
        outgoing=nullptr;
        incoming=nullptr;
        similar=nullptr;
       }
};
class Graph{
    public:
        int numnodes;
        Node* nodes;
        bool* ingroup;
        adjlist* sourcenodes;
        adjlist* nonsourcenodes;
        
        Graph(int x){
            numnodes=x;
            nodes = new Node[numnodes];
            ingroup=new bool[numnodes];
            for(int i=0;i<numnodes;i++){
                nodes[i].value=i+1;
                ingroup[i]=false;
            }
            sourcenodes=nullptr;
            nonsourcenodes=nullptr;
        }
        bool checksimilar(int x1,int x2){
            adjlist* s1=nodes[x1-1].similar;
            adjlist* s2=nodes[x2-1].similar;
            adjlist* r1=nodes[x1-1].incoming;
            adjlist* p=nodes[x2-1].incoming;
            adjlist* r2=p;
            if(r1==nullptr || r2==nullptr){
                if(present(nodes[x1-1].similar,x2)){
                    return true;
                }
                else{
                    return false;
                }
            }
            else{
                while(r1!=nullptr && r2!=nullptr){
                    if(checksimilar(r1->value,r2->value)){
                        r1=r1->next;
                        r2=p;
                    }
                    else{
                        r2=r2->next;
                    }
                }
            }
            if(r1!=nullptr){return false;}
            else{return true;}
        }
        void printsource(ofstream& f2){
            string s="Source nodes: ";
            adjlist* r=sourcenodes;
            while(r!=nullptr){
                s=s+to_string(r->value)+" ";
                r=r->next;
            }
           f2<<s<<endl<<endl;
        
        }
        void printsimilar(ofstream& f2){
            string s="Similar node pairs: ";
            string s1;
            string s2;
            for(int i=0;i<numnodes;i++){
                s1="("+to_string(i+1)+",";
                adjlist* r=nodes[i].similar;
                while(r!=nullptr){
                    s2=s1+to_string(r->value)+") ";
                    r=r->next;
                    s=s+s2;
                }
            }
            f2<<s<<endl<<endl;
        }
        
        int returnidx(){
            for(int i=0;i<numnodes;i++){
                if(ingroup[i]==false){
                    return i;
                }
            }
            return -1;
        }
};

int main(){
    ofstream f1("outgraph.txt");
    int numnodes,a,b;
    cin>>numnodes;
    Graph g(numnodes);
    while(true){
        cin>>a>>b;
        if(a==-1 || b==-1){
            break;
        }
        if(g.nodes[a-1].outgoing==nullptr && g.nodes[b-1].incoming==nullptr){
              g.nodes[a-1].outgoing=new adjlist(b);
              g.nodes[b-1].incoming=new adjlist(a);
        }
        else if(g.nodes[a-1].outgoing!=nullptr && g.nodes[b-1].incoming==nullptr){
                  adjlist* r=return_tail(g.nodes[a-1].outgoing);
                  r->next=new adjlist(b);
                  g.nodes[b-1].incoming=new adjlist(a);
        }
        else if(g.nodes[b-1].incoming!=nullptr && g.nodes[a-1].outgoing==nullptr){
                  adjlist* r=return_tail(g.nodes[b-1].incoming);
                  r->next=new adjlist(a);
                  g.nodes[a-1].outgoing=new adjlist(b);
        }
        else if(g.nodes[b-1].incoming!=nullptr && g.nodes[a-1].outgoing!=nullptr){
                  adjlist* r=return_tail(g.nodes[b-1].incoming);
                  r->next=new adjlist(a);
                  adjlist* r1=return_tail(g.nodes[a-1].outgoing);
                  r1->next=new adjlist(b);
        }
        else;
    }
    
    while(true){
        cin>>a>>b;
        if(a==-1 || b==-1){
            break;
        }
        if(g.nodes[a-1].similar==nullptr){
            g.nodes[a-1].similar=new adjlist(b);
        }
        else{
            adjlist* r =return_tail(g.nodes[a-1].similar);
            r->next=new adjlist(b);
        }
    }
    for(int i=0;i<g.numnodes;i++){
        if(length(g.nodes[i].incoming)==0){
            if(g.sourcenodes == nullptr){
                g.sourcenodes = new adjlist(i+1);
            }
            else{
                adjlist* r3=return_tail(g.sourcenodes);
                r3->next=new adjlist(i+1);
            }
        }
        else{
            if(g.nonsourcenodes==nullptr){
                g.nonsourcenodes=new adjlist(i+1);
            }
            else{
                adjlist* r4=return_tail(g.nonsourcenodes);
                r4->next=new adjlist(i+1);
            }
        }
    }
    for(int i=0;i<g.numnodes;i++){
        if(length(g.nodes[i].incoming)==1){
            if(g.nodes[i].similar==nullptr){
                g.nodes[i].similar=new adjlist(g.nodes[i].incoming->value);
                
            }
            else{
                adjlist* r2=return_tail(g.nodes[i].similar);
                r2->next=new adjlist(g.nodes[i].incoming->value);
                
            }
        }
    }
    int size=length(g.nonsourcenodes);
    int* arr=new int[size];
    adjlist* r=g.nonsourcenodes;
    for(int i=0;i<size;i++){
        arr[i]=r->value;
        r=r->next;
    }
    for(int i=0;i<size;i++){
        for(int j=i;j<size;j++){
            if(g.checksimilar(arr[i],arr[j])&&g.checksimilar(arr[j],arr[i])){
               
                if(g.nodes[arr[i]-1].similar==nullptr && g.nodes[arr[j]-1].similar==nullptr){
                    g.nodes[arr[i]-1].similar=new adjlist(arr[j]);
                    g.nodes[arr[j]-1].similar=new adjlist(arr[i]);
                }
                else if(g.nodes[arr[i]-1].similar!=nullptr && g.nodes[arr[j]-1].similar==nullptr){
                    adjlist* r=return_tail(g.nodes[arr[i]-1].similar);
                    r->next=new adjlist(arr[j]);
                    g.nodes[arr[j]-1].similar=new adjlist(arr[i]);
                }
                else if(g.nodes[arr[j]-1].similar!=nullptr && g.nodes[arr[i]-1].similar==nullptr){
                    adjlist* r=return_tail(g.nodes[arr[j]-1].similar);
                    r->next=new adjlist(arr[i]);
                    g.nodes[arr[i]-1].similar=new adjlist(arr[j]);
                }
                else if(g.nodes[arr[j]-1].similar!=nullptr && g.nodes[arr[i]-1].similar!=nullptr){
                    adjlist* r=return_tail(g.nodes[arr[j]-1].similar);
                    r->next=new adjlist(arr[i]);
                    adjlist* r1=return_tail(g.nodes[arr[i]-1].similar);
                    r1->next=new adjlist(arr[j]);
                }
                else;
            }
        }
    }
    g.printsource(f1);
    g.printsimilar(f1);
    

    adjlist* group[numnodes];
    for(int i=0;i<numnodes;i++){
        group[i]=new adjlist(g.nodes[i].value);
        group[i]->next=g.nodes[i].similar;
    }
    adjlist* final[numnodes];
    int j=0;
    

    for(int i=0;i<numnodes;i++){
        if(g.ingroup[i]==false){
           
        for(int j=i+1;j<numnodes;j++){
            
            if(intersect(group[i],group[j])&& g.ingroup[j]==false){
                
                add(group[i],group[j]);
                g.ingroup[j]=true;
                j=i;
            }
        }
        final[j]=group[i];
        g.ingroup[i]=true;
        j++;
        }
    }
    f1<<"Collapsed Graph: "<<endl<<endl;
    f1<<j<<": ";
    for(int i=0;i<j;i++){
        f1<<max(final[i])<<" ";
    }
    f1<<endl;
    adjlist* out=nullptr;
    string s="";
    for(int i=0;i<numnodes;i++){
        adjlist* r=g.nodes[i].outgoing;
        int grpidx;
        while(r!=nullptr){
            int elemidx;
            for(int k=0;k<j;k++){
               if(present(final[k],g.nodes[i].value)){
                      grpidx=k;
               }
               if(present(final[k],r->value)){
                elemidx=k;
               }
            }
            if(!present(final[grpidx],r->value)){
                
                if(out==nullptr){
                      out=new adjlist(max(final[grpidx]));
                      out->next=new adjlist(max(final[elemidx]));
                }
                else{
                    adjlist* r=return_tail(out);
                    r->next=new adjlist(max(final[grpidx]));
                    r->next->next=new adjlist(max(final[elemidx]));
                }
            }
            r=r->next;
            
        }
    }
    print(out,f1);
    f1.close();
   
    return 0;
}