#include<iostream>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<fstream>
#include"planner.h"

using namespace std;

Planner::Planner(){
int size = 0;


}

void add(char station_one[], float start_time, char station_two[], float finish_time ){
    
    // int hashv = hashValue(station_one);
    Dictionary D;
    
    int index = D.findFreeIndex(station_one);
    D.A[index].key = station_one;
    D.A[index].start[p] = start_time;
    D.A[index].destination[p] = *station_two;
    D.A[index].finish[p] = finish_time;
    p++;
    size++;

}

void query_station(char station_one[], float start_time){

    Dictionary D;
    int use1 = D.hashValue(station_one);
    int x1 = 0;
    for(int i=use1; x1<N; i=(i+1)%N){
        x1++;
        if(strcmp(station_one, D.A[i].key)==0){
            for(int j=0; j<size; j++){
                if(D.A[i].start[j]>= start_time){
                    cout << D.A[i].start[j] << " " << D.A[i].destination[j] << endl;
                    return;
                }
            }
        
        }
    }
    if(x1==N) {
            cout << "No such Station exist !" << endl;
        }
    }


void query_journey(char station_one[], float start_time, char station_two[]){
    Dictionary D;
    int find1 =0;
    int use2 = D.hashValue(station_one);
    int x2 = 0;
    for(int i=use2; x2<N; i=(i+1)%N){
        x2++;
        if(strcmp(station_one, D.A[i].key)==0){
                int soon2;
                int soonest = D.A[i].start[0];
                for(int j=0; j<size; j++){
                    if(soonest>D.A[i].start[j]){
                        soonest = D.A[i].start[j];
                        find1=j;
                        
                    }
                   // if(soonest == D.A[i])
                }
                if(strcmp(station_two, &D.A[i].destination[find1])==0){
                    cout << D.A[i].start[find1] << endl;
                    // break;
                    return;
                }
                 if(true){
                    int use3 = D.hashValue(&D.A[i].destination[find1]);
                    int x3 = 0;
                    for(int k=use3; x3<N; k=(k+1)%N){
                         x3++;
                        if(strcmp(&D.A[i].destination[find1], D.A[k].key)==0){
                            for( int j=0; j<size; j++){
                                if(strcmp(station_two, &D.A[k].destination[j])==0 && D.A[k].start[j]>D.A[i].finish[find1]){
                                        cout << D.A[i].start[find1] << " " << D.A[i].destination[find1] << " " << D.A[k].start[j] << endl;
                                        return;
                                }
                            }
                            
                            }

                            
    }

    
    }
    else{

        

    }
    }
    break;
    if(x2==N){
        cout << "This journey is not possible" << endl;
    }
}
}


int main(){

char *st1 = "Berlin";
char *st2 = "Munich";
float t1 = 1300;
float t2 = 1700;
 add(st1,t1,st2,t2) ;
 //query_station(st1, t1);



}