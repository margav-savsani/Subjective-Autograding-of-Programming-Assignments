#include<iostream>
#include <fstream>
#include <utility>
#include <set>
using namespace std;
ofstream MyFile("outgraph.txt");
class dgraph{
    int n;
    int **A;
    int *degree;
    int *odegree;
    bool *source;
    bool **similar;
    int *fin;
    public:
    dgraph(int n){
        this->n=n;
        A=new int*[n];
        for(int i=0;i<n;i++){
            A[i] = new int[n];
        }
        for(int i=0;i<n;i++){
            for(int j=0;j<n;j++){
                A[i][j]=0;
            }
        }
        fin =new int[n];
        for(int i=0;i<n;i++){
            fin[i]=i;
        }
        similar = new bool*[n];
        for(int i=0;i<n;i++){
            similar[i] = new bool[n];
        }
        for(int i=0;i<n;i++){
            for(int j=0;j<n;j++){
                similar[i][j] = false;
            }
        }
        degree=new int[n];
        for(int i=0;i<n;i++){
            degree[i]=0;
        }
        odegree=new int[n];
        for(int i=0;i<n;i++){
            odegree[i]=0;
        }
        source=new bool[n];
        for(int i=0;i<n;i++){
            source[i]=false;
        }
    }
    void addedge(int i,int j){
        A[i][j]=1;
        degree[i]++;
        odegree[j]++;
    }
    void printsource(){
        MyFile<<"Source nodes: ";
        for(int i=0;i<n;i++){
            if(odegree[i] == 0){
                source[i]=true;
                MyFile<<i+1<<" ";
            }
        }
        MyFile<<endl;
        MyFile<<endl;
    }
    void addusersimilar(int i,int j){
        if(source[i] && source[j]){
            similar[i][j]=1;
        }
    }
    void computemysimilar1(){
        for(int n1=0;n1<n;n1++){
            for(int n2=0;n2<n;n2++){
                if(n1!=n2){
                    if(!source[n1] && !source[n2]){
                        bool issimilar=true;
                        for(int i=0;i<n;i++){
                            if(A[i][n1] == 1){
                                int count=0;
                                for(int j=0;j<n;j++){
                                    if(A[j][n2] == 1 ){
                                        if(similar[i][j]){
                                            count++;
                                            break;
                                        }
                                    }
                                }
                                if(count==0){
                                    issimilar=false;
                                }
                            }
                        }
                        for(int i=0;i<n;i++){
                            if(A[i][n2] == 1){
                                int count=0;
                                for(int j=0;j<n;j++){
                                    if(A[j][n1] == 1 ){
                                        if(similar[i][j]){
                                            count++;
                                            break;
                                        }
                                    }
                                }
                                if(count==0){
                                    issimilar=false;
                                }
                            }
                        }
                        if(!similar[n1][n2]){
                            similar[n1][n2]=issimilar;
                            if(similar[n1][n2]){
                                similar[n2][n1]=true;
                            }
                        }
                    }
                }
            }
        }
    }
    void computemysimilar2(){
        for(int i=0;i<n;i++){
            for(int j=0;j<n;j++){
                if(i!=j){
                    if(odegree[i]==1 && A[j][i]==1){
                        similar[i][j]=true;
                    }
                }
            }
        }
    }
    void printsimilar(){
        MyFile<<"Similar node pairs: ";
        for(int i=0;i<n;i++){
            for(int j=0;j<n;j++){
                if(similar[i][j]){
                    MyFile<<"("<<i+1<<","<<j+1<<") ";
                }
            }
        }
        MyFile<<endl;
        MyFile<<endl;
    }
    void printcollapse(){
        MyFile<<"Collapsed graph:"<<endl; 
        MyFile<<endl;
       for(int i=0;i<n;i++){
            for(int j=0;j<n;j++){
                if(similar[i][j]){
                   int temp1=i;
                   while(temp1!=fin[temp1]){
                    temp1=fin[temp1];
                   }
                   int temp2=j;
                   while(temp2!=fin[temp2]){
                    temp2=fin[temp2];
                   }
                   int temp3=max(temp1,temp2);
                   fin[i]=temp3;
                   fin[j]=temp3;
                   while(fin[temp1]!=temp3){
                    int temp4=fin[temp1];
                    fin[temp1]=temp3;
                    temp1=temp4;
                   }
                   while(fin[temp2]!=temp3){
                    int temp4=fin[temp2];
                    fin[temp2]=temp3;
                    temp2=temp4;
                   }
                }
            }
       }
       for(int i=0;i<n;i++){
        fin[n-1-i]=fin[fin[n-1-i]];
       }
        set<int> a;
       for(int i=0;i<n;i++){
        a.insert(fin[i]+1);
       }
       MyFile << a.size()<<": ";
        for(auto& str: a)
        {
            MyFile << str << ' ';
        }
        MyFile<<endl;
        set<pair<int,int>>b;
        for(int i=0;i<n;i++){
            for(int j=0;j<n;j++){
                if(A[i][j] == 1){
                    pair<int,int>c;
                    c.first=fin[i]+1;
                    c.second=fin[j]+1;
                    if(fin[i]!=fin[j]){
                        b.insert(c);
                    }
                    // b.insert(fin[i]+1,fin[j]+1);
                }
            }
        }
        for(auto& str: b)
        {
            MyFile << str.first << " "<< str.second<<endl;
        } 
    }
};
