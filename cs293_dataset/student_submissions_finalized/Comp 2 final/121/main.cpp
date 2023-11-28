// #include<iostream>
#include"DAG.cpp"

int main(){
    int numberOfNodes;
    cin>>numberOfNodes;
    DAG dag(numberOfNodes);
    dag.printSources();
    dag.printSimilar();
    dag.Collapse();
}
