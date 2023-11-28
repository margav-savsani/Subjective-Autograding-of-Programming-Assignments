#include<iostream>
#include<cmath>
#include"math.h"
#include"dictionary.h"
#include"planner.h"
#include<string.h>
#include <bits/stdc++.h>

using namespace std ;

int Planner::hashValue(char key[]){  
    long unsigned int s=0 ;
    int i=0 ;
    while(int(key[i])!=0){
        s = (s+(int(key[i])))*37 ;
        i++;
    }
    const double f = 0.618033988 ;
    unsigned int val ;
    val = floor(M*((f*s)-floor(f*s))) ;
    return val ;
}


int Planner::findFreeIndex(char key[]){
    int m = 0;
    int k = hashValue(key) ;  
    while(B[k].starting_time!=0){
        m++;
        k = (k+1)%M ;
        if(m==M)return -1 ;
    }
    return k ;
}

bool Planner::add_journey(Journey k){
    if(findFreeIndex(k.starting.Name)!=-1){
        int m;
        m = findFreeIndex(k.starting.Name);
        B[m].starting_time = k.starting_time ;
        B[m].stopping_time = k.stopping_time ;
        B[m].stopping.Name = k.stopping.Name; 
        B[m].starting.Name = k.starting.Name ;
        return true;
    }
    else {
        return false;
    } 
}


int compare(char* arr1,char* arr2){
    int i=0;
    int j=0;
    while(int(arr1[i])!=0){
        i++;
    }
    while(int(arr2[j])!=0){
        j++;
    }
    if(i!=j){
        return 1;
    }
    else{
        int m=0;
        for(m=0;m<i;m++){
            if(arr1[m]!=arr2[m]){
                return 1;
            }       
        }
        if(m==i)return 0 ;
        
    }
}

bool Planner::check_Station(float time,char key[]){
    int k = hashValue(key) ;
    int j = 0 ;
    int no_train = 0 ;
    while(B[k].starting_time!=0){
        if(compare((B[k].starting.Name),key)==0){
            if(B[k].starting_time >= time){
                no_train++ ;
                cout << "Starting Time : "<<B[k].starting_time<<endl;
                cout<< "Stopping Time : "<<B[k].stopping_time<<endl;
            }

        }
        j++;
        k = (k+1)%M ;
        if(j==M)return 0 ;
    }
    if(no_train>0){ 
        return 1 ;
    }
    else{ 
        return 0 ;
    }
}

int min(int length,float list[]){
    int  m = length-1;
    for(int i = length-2;i>=0;i--){
        if(list[m]>=list[i]){
            m = i ;
        }
    }
    return m ;
}

bool Planner::check_Journey(char key_1[],char key_2[],float time){
    int k = hashValue(key_1);
    float time_array[125];
    struct Journey train[125] ;
    int l=0 ;
    int train_present=0 ;
    while(B[k].starting_time != 0){
        if(compare((B[k].starting.Name),key_1)==0){
            if(B[k].starting_time >= time){
                if(compare((B[k].stopping.Name),key_2)==0){
                    time_array[train_present] = B[k].stopping_time - B[k].starting_time ;
                    train[train_present] = B[k] ;
                    train_present++ ;
                }
                else{
                    int k2 = hashValue(B[k].stopping.Name) ;
                    while(B[k2].starting.Name!=0){
                        if(compare((B[k].stopping.Name),(B[k2].starting.Name))==0){
                            if(B[k2].starting_time >= B[k].stopping_time){
                                if(compare((B[k2].stopping.Name),key_2)==0){
                                    time_array[train_present]=(B[k2].stopping_time-B[k].starting_time);  
                                    train[train_present] = B[k2];
                                    train_present++;                                  
                                }
                            }

                        }
                        k2 = (k2+1)%M ;
                    }
                }
            }

        }
        l++ ;
        k =(k+1)%M;
        if(l==M){
            return 0;
        }        
    }
    int  p = min(train_present,time_array);
    if(compare(key_1,(train[p].starting.Name))==0){
        cout<<"From Station : "<<key_1<<" at time "<<train[p].starting_time<<" hrs to Station : "<<key_2<<" with time duration "<<time_array[p]<<" hrs"<<endl;
    }
    else{
        cout<<"From Station : "<<key_1<<" to Station : "<<train[p].starting.Name<<" and then to Station :"<<key_2<<" with time duration "<<time_array[p]<<" hrs"<<endl;
    }
    if(train_present==0)return false;
    else return true;
}





