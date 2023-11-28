#include<iostream>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<fstream>
#include "planner.h"

using namespace std;


void plannerOfStations(Planner &planner){

    for(int i=0;i>=0;i++){

        char input1[32];
        cout << ">>> " ;
        cin>>input1;
        if(strcmp(input1,"EXIT") == 0){ break;}

        if(strcmp(input1,"ADD") == 0){
            char stat1[32],stat2[32];
            float startt,finisht;

            cin >>stat1 >>startt >>stat2 >>finisht;

            if(planner.findindex(stat1)==-1){
                planner.addstat(stat1);

                Station *x = planner.getstat(stat1);
                x->addjourney(stat2,startt,finisht);
                
            }

            else {
                Station *x = planner.getstat(stat1);
                x->addjourney(stat2,startt,finisht);

            }

        }

        else if(strcmp(input1,"QUERY_STATION") == 0){
            char stat[32];
            float startt;

            cin >>stat >>startt;

            if(planner.findindex(stat)==-1){
                cout <<"Station not found"<<endl;
            }

            else {
                Station *x = planner.getstat(stat);
                x->list(startt);
            }

        }

        else if(strcmp(input1,"QUERY_JOURNEY") == 0){
            char stat1[32],stat2[32];
            float startt;

            cin >>stat1 >>startt >>stat2;

            if(planner.findindex(stat1) == -1){
                cout <<"Station1 not found"<<endl;
            }

            else {
                Station *x = planner.getstat(stat1);

                x->insertionSort();
        
                for(int i=0;i<x->noOfJour;i++){
                    if((startt<=x->j[x->store[i]].startt) && (strcmp(stat2,x->j[x->store[i]].dest)==0)){
                    cout << x->j[x->store[i]].startt <<endl;
                    break;
                    }

                    else if((startt<=x->j[x->store[i]].startt) && (strcmp(stat2,x->j[x->store[i]].dest) !=0)){

                        

                        Station *y=planner.getstat(x->j[x->store[i]].dest);

                        for(int a=0;a<y->noOfJour;a++){
                            if((strcmp(y->j[y->store[a]].dest,stat2)==0) && (x->j[x->store[i]].finisht<=y->j[y->store[a]].startt)){

                                cout <<x->j[x->store[i]].startt << " "<<x->j[x->store[i]].dest<< " "<<y->j[y->store[a]].startt <<endl;
                                break;
                            }
                        }
                        
                    }

                    if(i==(x->noOfJour)-1) cout <<"Journey not found"<<endl;
                }
            }
        }
    }
}

void interactive(){
    
    Planner planner;
    plannerOfStations(planner);
}

int main(){

    interactive();
}
