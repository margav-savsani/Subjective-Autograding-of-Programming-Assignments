#ifndef GRAPH
#define GRAPH
#include <iostream>
#include "node.h"
using namespace std;

void assignGroup(node **nodelist, node * root, int num, int group){
    root->group=group;
    root->visited=1;
    listNode<node *> *curr = root->closure;
    while(curr!=nullptr){
        if(curr->object->visited==0)
            assignGroup(nodelist, curr->object, num, group);
        curr=curr->next;
    }
}

void collapse(node ** nodelist, int num){
    for(int i =0; i<num; i++){
        for(int j=0; j<num; j++){
            if(nodelist[i]->findSim(nodelist[j]->name)){
                nodelist[i]->insertClosure(nodelist[j]);
                nodelist[j]->insertClosure(nodelist[i]);
            }
        }
    }
    
    
    int group=0;
    for(int i=0; i<num; i++){
        if(nodelist[i]->visited == 0){
            assignGroup(nodelist, nodelist[i], num, group);
            group++;
        }
    }
    node *collapsedList[group];
    for(int k=0; k<group; k++){
        collapsedList[k]=new node();
        collapsedList[k]->name = k;
    }
    for(int i=0; i<num; i++){
        listNode<node *> *curr= nodelist[i]->outNeighbours;
        while(curr!=nullptr){
            if(curr->object->group!=nodelist[i]->group){
                collapsedList[nodelist[i]->group]->insertOutNeigh(collapsedList[curr->object->group]);
            }
            curr=curr->next;
        }
    }

    for(int k=0; k<group; k++){
        int max=-1;
        for(int i=0; i<num; i++){
            
            if(nodelist[i]->group == k && (i+1)>max){
                max=(i+1);

            }
            collapsedList[k]->name = max;
        }
    }
    cout<<"Collapsed graph:"<<endl;
    cout<<endl;
    cout<<group<<":";
    for(int i=0; i<group; i++){
        cout<<" "<<collapsedList[i]->name;
    }
    cout<<endl;
    for(int i=0; i<group; i++){
        listNode<node *> *curr = collapsedList[i]->outNeighbours;
        while(curr!=nullptr){
            cout<<collapsedList[i]->name<<" "<<curr->object->name;
            curr=curr->next;
            cout<<endl;
        }
    }

}
#endif