#include <iostream>
#include <cmath>
#include<string.h>
#include "dictionary.h"
using namespace std;

void merge(struct Entry U[], int Lu, struct Entry V[], int Lv, struct Entry S[]){
    int uf=0, vf=0;
    for(int sb=0; sb < Lu+Lv; sb++){
        if(uf<Lu && vf<Lv){
            if(U[uf].start_time < V[vf].start_time){
                S[sb] = U[uf]; uf++;
            }
            else{
                S[sb] = V[vf]; vf++;
            }
        }
        else if(uf < Lu){
            S[sb] = U[uf]; uf++;
        }
        else{
            S[sb] = V[vf]; vf++;
        }
    }
} 

void mergesort(struct Entry S[], int n){ 
    if(n==1) return;
    struct Entry U[n/2];
    struct Entry V[n-n/2]; // local arrays
    for(int i=0; i<n/2; i++){
        U[i]=S[i];
    } // copy of first half
    for(int i=0; i<n-n/2; i++){
        V[i]=S[i+n/2];
    } // copy of second half
    mergesort(U,n/2);
    mergesort(V,n-n/2);
    merge(U, n/2, V, n-n/2, S); // merge into original array S.
} 

int Dictionary::hashValue(char key[]){
    double p = (sqrt(5)-1)/2;
    int size=0;
    int i=0;
    while(key[i]!='\0'){
        size++;
        i++;
    }
    double hash=(p*key[size-1]-int(p*key[size-1]));
    int x=33;
    for(int i=size-1; i>0; i--){
        hash = (hash*x + (p*key[i-1]))-int(hash*x + (p*key[i-1]));
    }
    hash = N*hash;
    return int(hash);
}
int Dictionary::findFreeIndex(char key[]){
    int id = hashValue(key);
    if((A[id].isPresent==0) || (A[id].isPresent==2)){
        return id;
    }else{
        id=(id+1)%N;
        while(id!=hashValue(key)){
            if((A[id].isPresent==0) || (A[id].isPresent==2)){
                return id;
            }
            id=(id+1)%N;
        }
        return -1;
    }
}
Dictionary::Dictionary(){
    A = new Entry[DICT_SIZE];
    if (A != nullptr) N = DICT_SIZE;
    else N = 0;
    for(int i=0; i<N; i++){
        A[i].isPresent=0;
    }
}
bool Dictionary::put(struct Entry e){
    int i = findFreeIndex(e.station1);
    if(i!=-1){
        strcpy(A[i].station1,e.station1);
        A[i].start_time=e.start_time;
        A[i].finish_time=e.finish_time;
        strcpy(A[i].station2, e.station2);
        A[i].isPresent=1;
        return true;
    }else{
        return false;
    }
}
struct Entry * Dictionary::get(char station1[]){
    int id = hashValue(station1);
    if(A[id].isPresent==0){
        return NULL;
    }else{
        if( (strcmp(station1, (A[id].station1))==0) && A[id].isPresent==1 ){
            return &A[id];
        }
        else{
            id=(id+1)%N;
            while(id!=hashValue(station1)){
                if(A[id].isPresent==1 && (strcmp(station1, (A[id].station1))==0)){
                    return &A[id];
                }
                else if(A[id].isPresent==0){
                    return NULL;
                }else{
                    id=(id+1)%N;
                }
            }
        }
    }
}
// bool Dictionary::remove(char key[]){
//     // Entry * element = get(key);
//     int hash=-1;
//     int id = hashValue(key);
//     if(A[id].isPresent==0){
//         hash=-1;
//     }else{
//         if( (strcmp(key, (A[id].key))==0) && A[id].isPresent==1 ){
//             hash=id;
//         }
//         else{
//             id=(id+1)%N;
//             while(id!=hashValue(key)){
//                 if(A[id].isPresent==1 && (strcmp(key, (A[id].key))==0)){
//                     hash=id;
//                     break;
//                 }
//                 else if(A[id].isPresent==0){
//                     hash=-1;
//                     break;
//                 }else{
//                     id=(id+1)%N;
//                 }
//             }
//         }
//     }
//     if(hash != -1){
//         A[hash].isPresent=2;
//         return true;
//     }else{
//         return false;
//     }
// } 
void Dictionary::querystation(char station1[], float start_time){
    bool found = false;
    for(int i=0; i<N; i++){
        if( (strcmp(A[i].station1, station1)==0) && A[i].isPresent==1 && A[i].start_time>=start_time){
            cout<<A[i].start_time<<" "<<A[i].station2<<endl;
            found=true;
        }
    }
    if(found==false){
        cout<<"ERROR"<<endl;
    }
}

bool Dictionary::queryjourney(char station1[], float start_time, char station2[]){
    struct Entry *B;
    B = new Entry[DICT_SIZE];
    int count = 0;
    bool B_empty=true;
    for(int i=0; i<N; i++){
        if((strcmp(A[i].station1, station1)==0) && A[i].start_time>=start_time){
            B[count]= A[i];
            count++;
            B_empty=false;
        }
    }
    if(B_empty==true){
        cout<<"ERROR"<<endl;
        return false;
    }
    mergesort(B, count);
    bool found = false;
    for(int i=0; i<count && found==false; i++){
        if(strcmp(B[i].station2, station2)==0){
            found = true;
            cout<<B[i].start_time<<endl;
            return true;
        }
        else{
            for(int j=0; j<N; j++){
                if(strcmp(A[j].station1, B[i].station2)==0 && strcmp(A[j].station2, station2)==0){
                    found=true;
                    cout<<B[i].start_time<<" "<<B[i].station2<<" "<<A[j].start_time<<endl;
                    return true;
                }
            }
        }
    }
    if(found==false){
        cout<<"ERROR"<<endl;
        return false;
    }
}
