#include "dictionary.h"
#include <cmath>

Dictionary::Dictionary(){
    N=DICT_SIZE;
    A = new Entry[N];
    // Initialise all keys to NULL
    for (int i=0; i<N; i++) {
        A[i].station[0]=0;
    }
}

int Dictionary::hashValue(char key[]){
    int i=0; float poly=0; int floor;
    int x=37; float A = (sqrt(5)-1)/2;
    while(key[i]!=0){
        poly=x*poly+key[i];
        poly *= A;
        floor = (int)poly;
        poly = poly-floor;
        i++;
    }
    // Now we have the fractional part of value of the polynomial times A
    // Now we need to multiply this by m
    // cout<<"frac is "<<poly<<endl; //debug
    int ans = N*poly;
    return ans;
}

int Dictionary::findFreeIndex(char key[]){
    // 0 represents empty
    int hash = hashValue(key);
    if (A[hash].station[0]==0){
        return hash;
    }
    int slot = (hash+1)%N;
    while(slot!=hash){
        if (A[slot].station[0]==0){
            return slot;
        }
        slot=(slot+1)%N;
    }   
    return -1;
}

void Dictionary::get(char key[], int time){
    int slot = hashValue(key);
    bool found = 0;
    int orgslot=slot;
    //cout<<"---------------------------------\n";
    while(A[slot].station[0]!=0){
        if (strcmp(A[slot].station, key)==0 && A[slot].jour.start>=time){
            found=1;
            cout<<A[slot].jour.start<<" "<<A[slot].jour.dest<<endl;
        }
        slot=(slot+1)%N;
        if (slot==orgslot) break;
    }
    if (!found) cout<<"ERROR: No trains from this station."<<endl;
}

bool Dictionary::put(Entry e){
    int slot = findFreeIndex(e.station);
    if (slot==-1) return false;
    strcpy(A[slot].station, e.station);
    /*
    char *str = A[slot].station;
    for (int i=0; true; i++) {
        str[i]=e.station[i];
        if (str[i]==0) break;
    }*/
    A[slot].jour = e.jour;
    return true;
}

void Dictionary::plan(Query* q){
    int slot = hashValue(q->src);
    //cout<<"Hash value: "<<slot<<endl;
    int orgslot = slot;
    int earliest = 2359;
    char intermediate[32]={0};
    int second=2359;
    while(A[slot].station[0]!=0){
        if (strcmp(A[slot].station, q->src)==0){
            //cout<<"From station "<<q->src<<endl;
            // The starting station in dictionary matches query source

            if (strcmp(A[slot].jour.dest, q->dest)==0 && A[slot].jour.start >= q->start){
                //cout<<"destination match to "<<q->dest<<endl;
                if (earliest>A[slot].jour.start){
                    earliest = A[slot].jour.start;
                }
            }
            else if(A[slot].jour.start>=q->start && A[slot].jour.start<earliest) {
                //cout<<"trying via "<<A[slot].jour.dest<<" from "<<A[slot].jour.start<<endl;
                int _2slot = hashValue(A[slot].jour.dest);
                int _2org = _2slot;
                while(A[_2slot].station[0]!=0){
                    if(strcmp(A[_2slot].station, A[slot].jour.dest)==0) {
                        if (strcmp(A[_2slot].jour.dest, q->dest)==0 && A[_2slot].jour.start>=A[slot].jour.end){
                            strcpy(intermediate, A[slot].jour.dest);
                            second = A[_2slot].jour.start;
                            earliest = A[slot].jour.start;
                        }
                    }
                    _2slot=(_2slot+1)%N;
                    if (_2slot==_2org) break;
                }
            }
        }
        // cout<<"This is station "<<A[slot].station<<endl;
        slot=(slot+1)%N;
        if (slot==orgslot) break;
    }
    if (earliest==2359) {cout<<"ERROR: No routes are possible"<<endl; return;}
    cout<<earliest;
    if (intermediate[0]!=0){
        cout<<" via "<<intermediate<<" at "<<second;
    }
    cout<<endl;
}
