#include<iostream>
#include<cmath>
#include<vector>
using namespace std;
struct node{
    int value;
    vector<int> outgoingnodes;
    vector<int> incomingnodes;
    vector<int> adjacentnodes;
void addoutgoing(int b){
    outgoingnodes.push_back(b);
    }
void addincoming(int b){
    incomingnodes.push_back(b);
    }
};