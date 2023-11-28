
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string>
#include <sstream>
#include <cstring>
#include <cctype>
#include<vector>
#include "cmath"

using namespace std;

class Node {
 public:
  int value;
};
class Graph {
public:
  int numNodes;
  int numsrcnodes=0;
  Node *nodes;
  vector<vector<int>> adjbydest;
  bool **similar;
  vector<int> a1;
  vector<int> a2;
  bool areSimilar(int a, int b){
    //Case(i)
    if(similar[a-1][b-1]){
        return true;
    }
   //Case(iii)
    if(adjbydest[a-1].size()==1){
        if(adjbydest[a-1][0]==b-1){
        return true;
        }
    }
    else return false;
  }
  bool areSimilar_case2(int a,int b){
    //Case(ii)
   int vectsize1 = adjbydest[a-1].size();
   int vectsize2 = adjbydest[b-1].size();
   if((vectsize1==0 || vectsize2==0)){
    return false;
   }
   for(int i=0;i<vectsize1;i++){
    bool istrue = false;
    for(int j=0;j<vectsize2;j++){
        bool found;
        found = {areSimilar_case2((adjbydest[a-1][i]+1),(adjbydest[b-1][j]+1))||similar[adjbydest[a-1][i]][adjbydest[b-1][j]]};
        if(found){
            istrue=true;
            break;
        }
    }
    if(!istrue){
            return false;
        }
   }
    for(int i=0;i<vectsize2;i++){
    bool istrue = false;
    for(int j=0;j<vectsize1;j++){
        bool found;
        found = {areSimilar_case2((adjbydest[b-1][i]+1),(adjbydest[a-1][j]+1))||similar[adjbydest[b-1][i]][adjbydest[a-1][j]]};
        if(found){
            istrue=true;
            break;
        }
    }
    if(!istrue){
            return false;
        }
   }
   return true;
  }
   Graph() {
    cin>>numNodes;
    nodes = new Node[numNodes];
    for (int i = 0; i < numNodes; i++) {
      nodes[i].value = i+1;
    }
    similar = new bool*[numNodes];

    for (int i = 0; i < numNodes; i++) {
        similar[i] = new bool[numNodes];
    }
    adjbydest.resize(numNodes);
    while(true){
        int a,b;
        cin>>a>>b;
        if(a != -1 && b != -1){
            addEdge(a,b);
        }
        else{
            break;
        }
    }
    while(true){
        int a,b;
        cin>>a>>b;
        if(a != -1 && b != -1){
            similar[a-1][b-1]=true;
        }
        else{
            break;
        }
    }
    }
    void addEdge(int src,int dest){
        adjbydest[dest-1].push_back(src-1);
    }
    void findsrcnodes(){
        vector<int> v;
        for(int i=0;i<numNodes;i++){
            if(adjbydest[i].size()==0){
                cout<<i+1<<" ";
            }
        }
    }
    void calcsimilar(){
        for(int i=1;i<=numNodes;i++){
            for(int j=1;j<=numNodes;j++){
                similar[i-1][j-1]=areSimilar(i,j);
            }
        }
         for(int i=1;i<=numNodes;i++){
            for(int j=1;j<=numNodes;j++){
                if(!similar[i-1][j-1])
                    similar[i-1][j-1]=areSimilar_case2(i,j);
            }
        }
        for(int i=1;i<=numNodes;i++){
            for(int j=1;j<=numNodes;j++){
                if(similar[i-1][j-1]==true){
                    cout<<"("<<i<<","<<j<<")"<<" ";
                    a1.push_back(i);
                    a2.push_back(j);
                }
            }
        }
    }
    void Printcollapsedgraf(){
      int size = a1.size();
        int pointer=0;
        while(pointer<size){
            if(a1[pointer] == a2[pointer]){
                pointer++;
                continue;
            }
            for(int i=0;i<size;i++){
                if(a2[pointer]==a1[i]){
                    int maximum = max(a1[pointer],a2[pointer]);
                    maximum = max(maximum,a2[i]);
                    int m1=a1[pointer];
                    int m2=a2[i];
                    int m3=a2[pointer];
                    for(int j=0;j<size;j++){
                        if(a1[j]==m1||a1[j]==m2||a1[j]==m3)
                            a1[j]=maximum;
                        if(a2[j]==m1||a2[j]==m2||a2[j]==m3)
                            a2[j]=maximum;
                    }
                break;
                }
            }
    pointer++;
    
    }
    
    pointer=0;
    vector<int>collapsed_grf;
while(pointer<size){
    bool isnew=true;
    if(collapsed_grf.size()==0){
        collapsed_grf.push_back(a1[pointer]);
        pointer++;
        continue;
    }
    for (int i=0;i<collapsed_grf.size();i++){
        if(a1[pointer]==collapsed_grf[i]){
            isnew = false;
            }
        }
        if(isnew){
            collapsed_grf.push_back(a1[pointer]);
        }
        pointer++;
    }
    cout<<collapsed_grf.size()<<":";
for(int j=0;j<collapsed_grf.size();j++){
    cout<<collapsed_grf[j]<<" ";
}
}
  };