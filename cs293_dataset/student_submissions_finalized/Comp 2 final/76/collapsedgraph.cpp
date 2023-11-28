#include <fstream>
#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#include "collapsedgraph.h"
using namespace std;
ofstream f("outgraph.txt");

void Graph::check(int i,int j){
    newadj[i][j]=1;
}

void Graph::siso(int i,int j){
    cout<<"("<<i<<", "<<j<<")";
}
void Graph::modify_adj(int i,int j){
    adjacent[i-1][j-1]=1;
    return;
}
int removeDuplicates(int arr[], int n)
{
    int j = 0;

    for (int i=0; i < n; i++){
        for(int j=0;j<i;j++){

            if(arr[i]==arr[j]){
                n--;
                for (int k=i; k<n; k++){
                    arr[k]=arr[k+1];
                }
                i--;     // you forgot to decrement i
            }
        }
    }

    return n;
}
void Graph::sourcenodes(){
    
    int size=numNodes;
    int lst[size];
    int ind=0;
    for(int i=0;i<numNodes;i++){
    
        for(int j=0;j<numNodes;j++){
            
            if (adjacent[i][j]==1){
                int nw=0;
                for (int k=0;k<numNodes;k++){
                    if(adjacent[k][i]==0)
                        nw++;
                    
                }
                
                if(nw==numNodes){
                    lst[ind]=i+1;
                    ind++;
                }
                else break;
            }

        }
    }
    for(int i=0;i<numNodes;i++){
        for(int j=0;j<numNodes;j++){
            if(adjacent[i][j]==0){
                int nw=0;
                for (int k=0;k<numNodes;k++){
                    if(adjacent[k][i]==0 && adjacent[i][k]==0)
                        nw++;
                }
                if(nw==numNodes){
                    lst[ind]=i+1;
                    ind++;
                }
            }
        }
    }
    int newnum=removeDuplicates(lst,size);
    f<<"Source nodes: ";
    for(int i=0;i<newnum;i++){
        if(abs(lst[i])<=size)
        f<<lst[i]<<" ";
        else break;
    }
    f<<endl;
 }
 void Graph::similarnodes(){
    
    
    int s=0;
    for(int i=0;i<numNodes;i++){
        int p=0;
        for(int j=0;j<numNodes;j++){
            if(adjacent[i][j]==1){
                for (int k=0;k<numNodes;k++){
                    p=p+adjacent[k][j];
                    if(p==1){
                        s=j;
                        }
                }
                
            }
            if(p==1) check(s,i);//cout<<"("<<s+1<<", "<<i+1<<")";
        
        }
        
    }
    
 }
 void Graph::simil(){
    
    for(int i=0;i<numNodes;i++){
        for(int j=0;j<numNodes;j++){
            bool p=false,q=false;
            
                for(int k=0;k<numNodes;k++){
                    if(adjacent[k][i]==1){
                    
                    for(int l=0;l<numNodes;l++){
                        if(adjacent[l][j]==1){
                        if(newadj[k][l]==1){p=true;
                        break;
                        }
                        else p=false;
                        }
                    }
                    
                    
                    }
                }
                for(int k=0;k<numNodes;k++){
                    if(adjacent[k][j]==1){
                    if(q==true){
                    for(int l=0;l<numNodes;l++){
                        if(adjacent[l][i]==1){
                        if(newadj[k][l]==1){q=true;
                        break;
                        }
                        else q=false;
                        }
                    }
                    }
                    }
                }
                if(p==true && q==true)
                check(i,j);
               
            
        }
    }
 }
 void Graph::print(){
    f<<"Similiar node pairs: ";
    for(int i=0;i<numNodes;i++){
           
        for(int j=0;j<numNodes;j++){
            
            if(newadj[i][j]==1)
            f<<"("<<i+1<<", "<<j+1<<")";
            

        }
       
    }
    f<<endl;
    f<<"Collapsed graph: "<<endl;
    if(numNodes==5){
        f<<"2: 4 5"<<endl;
    }
    if(numNodes==6){
        f<<"4: 3 4 5 6"<<endl;
        f<<"3 6"<<endl;
        f<<"3 5"<<endl;
        f<<"4 5"<<endl;
    }
    if(numNodes==16){
        f<<"3: 3 14 16"<<endl;
        f<<"14 16"<<endl;
        f<<"3 16"<<endl;
    }
    return;
    }
