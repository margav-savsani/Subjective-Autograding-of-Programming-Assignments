#include <iostream>
#include <fstream>
#include <string>


using namespace std;
ofstream output("outgraph.txt");

class Node{
public:
    bool edge;
    bool similar ;
    
    Node(){
      edge = false;
      similar = false;  
    }
};

class list{
public:
  list* next;
  int index;
  list(int n){
    index = n;
    next = nullptr;
  }
  list(){
    index = -1;
    next = nullptr;
  }
};

class graphnode{
  public:
    int index = 0;
    bool visit = false;
};

class Graph{
private:
    int numNodes;
    Node** matrix;
    list** incoming;
    list** outgoing;
    bool *f;
public:
    Graph(int n){
      numNodes = n;
      matrix = new Node*[n];
      incoming = new list*[n];
      outgoing = new list*[n];        
      f = new bool[n];
      for(int i = 0;i < n;i++){
        incoming[i] = new list();
        outgoing[i] = new list();
        matrix[i] = new Node[n];
      }
      int x = 0,y = 0;
      cin >> x>>y;
      while(x != -1 && y!= -1){
        matrix[x-1][y-1].edge = true;
        list* in1 = incoming[y-1];
        while(in1->next != nullptr){
          in1 = in1->next;
        }
        list *s = new list(x-1);
        in1->next = s;

        list* out1 = outgoing[x-1];
        while(out1->next != nullptr){
          out1 = out1->next;
        }
        list *p = new list(y-1);
        out1->next = p;
        cin >> x >> y;
      }
      cin >> x>>y;
      while(x != -1 && y != -1){
        matrix[x-1][y-1].similar = true;
        cin >> x>>y;
      }
    }

    void getsources(){
      output <<"Source Nodes:";
      for(int i = 0;i< numNodes;i++){
        list* in = incoming[i];
        if(in->next == nullptr){
          output<<i+1<<" ";
        }
      }
      output <<endl;
      output <<endl;
    }
    
    bool checksm(int i,int j){
        list *inn1 = incoming[i];
        list *innorg2 = incoming[j];
        inn1 = inn1->next;
        innorg2 = innorg2->next;
        if(inn1 == nullptr || innorg2 == nullptr){
            return false;
        }
        while(inn1 != nullptr){
          int p = inn1->index;
          list *inn2 = innorg2;
          while(inn2 != nullptr){
            int q = inn2->index;
            if(matrix[p][q].similar == true){
              break;
            }
            inn2 = inn2->next;
          }
          if(inn2 == nullptr){
            return false;
          }
          inn1 = inn1->next;
        }
        return true;
    }

    void recursion(int i,int j){
      list* out1 = outgoing[i];
      list* outorg2 = outgoing[j];
      out1 = out1->next;
      outorg2 = outorg2->next;
      if(out1 == nullptr || outorg2 == nullptr){
        return;
      }
      while(out1 != nullptr){
        int p = out1->index;
        list* out2 = outorg2;
        while(out2 != nullptr){
          int q = out2->index;
          if(checksm(p,q) == true && checksm(q,p) == true){
            matrix[p][q].similar = true;
            matrix[q][p].similar = true;
            recursion(p,q);
          }
          out2 = out2->next;
        }
        out1 = out1->next;
      }
    }

    void getsimilars(){
      output<<"Similar Node pairs: ";
      for(int i = 0;i<numNodes;i++){
        list *in = incoming[i];
        if(in->next != nullptr && in->next->next == nullptr){
          matrix[i][in->next->index].similar = true;
        }
      }
    
      for(int i = 0;i< numNodes;i++){
        for(int j = 0;j<numNodes;j++){
          if(matrix[i][j].similar){
              recursion(i,j);
          }
        }
      }

      for(int i = 0;i< numNodes;i++){
        for(int j = 0;j<numNodes;j++){
          if(matrix[i][j].similar){
              output<<"("<<i+1<<", "<<j+1<<")";
          }
        }
      }
      output<<endl;
      output<<endl;
    }

    

    void collapsedgraph(){
      bool* visit;
      visit = new bool[numNodes];
      for(int i = 0;i<numNodes;i++){
        visit[i] = true;
      }
      for(int i1 = 0;i1 < numNodes;i1++){
        for(int j1 = 0;j1 < numNodes;j1++){
          if(matrix[i1][j1].similar){
            if(i1 < j1 || i1 > j1){
              int i,j;
              if(i1 >j1){
                i= j1;
                j = i1;
              }
              else{
                i = i1;
                j = j1;
              }
              visit[i] = false;
              for(int k = 0;k< numNodes;k++){
                if(matrix[i][k].edge && k != j){
                  matrix[j][k].edge = true;
                  matrix[i][k].edge = false;
                }
                if(matrix[k][i].edge && k != j){
                  matrix[k][j].edge = true;
                  matrix[k][i].edge = false;
                }
                if(matrix[i][k].similar && k != j){
                  matrix[j][k].similar = true;
                  matrix[i][k].similar = false;
                }
                if(matrix[k][i].similar && k != j){
                  matrix[k][j].similar = true;
                  matrix[k][i].similar = false;
                }
                matrix[i][j].edge = false;
                matrix[j][i].edge = false;
              }
            matrix[i1][j1].similar = false;
          } 
        }
      }
    }
    int l = 0;
    for(int i = 0; i<numNodes;i++){
      if(visit[i]){
        l++;
      }
    }
    output<<"Collapsed graph:"<<endl;
    output<<endl;
    output<<l<<":";
    for(int i = 0; i<numNodes;i++){
      if(visit[i]){
        output<<" "<<i+1;
      }
    }
    output<<endl;
    for(int i = 0;i<numNodes;i++){
      for(int j = 0;j<numNodes;j++){
        if(matrix[i][j].edge){
          output<<i+1<<" "<<j+1<<endl;
        }
      }
    }
  }
};

int main(int argc,char **argv){
    int numnodes;
    cin >> numnodes;
    Graph g(numnodes);
    g.getsources();
    g.getsimilars();
    g.collapsedgraph();
}

