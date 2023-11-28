#include<iostream>
#include <fstream>
#include <utility>
#include <set>
using namespace std;
#include"graph.cpp"
int main(int argc,char*argv[]){
    int n;
    cin>>n;
    dgraph g=dgraph(n);
    int x,y;
    cin>>x>>y;
    while(x!=-1 && y!=-1){
        g.addedge(x-1,y-1);
        cin>>x>>y;
    }
    g.printsource();
    cin>>x>>y;
    while(x!=-1 && y!=-1){
        g.addusersimilar(x-1,y-1);
        cin>>x>>y;
    }
    g.computemysimilar2();
    g.computemysimilar1();
    g.printsimilar();
    g.printcollapse();
    MyFile.close();
}