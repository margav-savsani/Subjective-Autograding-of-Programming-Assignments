#ifndef MAIN
#define MAIN
#include <iostream>
using namespace std;

#include "node.h"
#include "graph.h"
int num;

bool areSimilar(node * a, node *b, node ** nodelist){
    listNode<node *> *curra = a->inNeighbours;
    listNode<node *> *currb = b->inNeighbours;
    bool c1 = true;
    bool c2 = true;
    if(curra ==nullptr){
        c1=false;
    }
    if(currb ==nullptr){
        c2=false;
    }
    while(curra!=nullptr){
        bool check=false;
        currb = b->inNeighbours;
        while(currb!=nullptr){
            if(curra->object->findSim(currb->object->name)){
                check=true;
                break;
            }
            currb=currb->next;
        }
        if(check==false){
            c1=false;
            break;
        }
        curra=curra->next;
    }
    curra = a->inNeighbours;
    currb = b->inNeighbours;
    while(currb!=nullptr){
        bool check=false;
        curra = a->inNeighbours;
        while(curra!=nullptr){
            if(currb->object->findSim(curra->object->name)){
                check=true;
                break;
            }
            curra=curra->next;
        }
        if(check==false){
            c2=false;
            break;
        }
        currb=currb->next;
    }
    if(c1 && c2){
        return true;
    }
    else{
        return false;
    }
}

void solve(node ** nodelist){
    for(int i =0; i<num; i++){//Checking relations in case 3
        if(nodelist[i]->inNeighbours!=nullptr && nodelist[i]->inNeighbours->next == nullptr)
            nodelist[i]->insertSimilar(nodelist[i]->inNeighbours->object);
    }
    
    for(int i =0; i<num; i++){//checking via case 2
        for(int j=0; j<num; j++){ 
            if(nodelist[i]->findSim(nodelist[j]->name)==false){
                if(areSimilar(nodelist[i], nodelist[j], nodelist)){
                    nodelist[i]->insertSimilar(nodelist[j]);
                    nodelist[j]->insertSimilar(nodelist[i]);
                    i=0;
                    j=0;
                    break;
                }
            }
        }
    }
}

int main(){
    cin>>num;
    node *nodelist[num];
    for(int i =0; i<num; i++){
        nodelist[i]=new node();
        nodelist[i]->name = i+1;
    }
    while(true){
        int a, b;
        cin>>a>>b;
        if(a==-1 || b==-1){
            break;
        }
        nodelist[a-1]->insertOutNeigh(nodelist[b-1]);
        nodelist[b-1]->insertInNeigh(nodelist[a-1]);
    }
       
    while(true){
        int a , b;
        cin>>a>>b;
        if(a==-1||b==-1){
            break;
        }
        if(nodelist[a-1]->inNeighbours==nullptr && nodelist[b-1]->inNeighbours==nullptr){
            nodelist[a-1]->insertSimilar(nodelist[b-1]);
        }
    }

    
    cout<<"Source Nodes:";
    for(int i=0; i<num; i++){
        if(nodelist[i]->inNeighbours == nullptr){
            cout<<" "<<(i+1);
        }
    }
    cout<<endl;
    cout<<endl;

    cout<<"Similar node pairs:";
    solve(nodelist);
    for(int i=0; i<num; i++){
        listNode<node *> *temp = nodelist[i]->similar;
        while(temp!=nullptr){
            cout<<" ("<<(i+1)<<", "<<temp->object->name<<")";
            temp=temp->next;
        }
    }
    cout<<endl;
    cout<<endl;
    collapse(nodelist, num);
}
#endif