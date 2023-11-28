#include<iostream>
#include<cmath>
#include<string.h>
#include<tuple>
#include"planner.h"
#include"dictionary.cpp"
#include"linearQueue.cpp"
using namespace std;

Journey Planner::add_journey(char Key[],int Value,char Key1[],int Value1){
    Journey j;
    strcpy(j.startst.key,Key);
    j.startti=Value;
    strcpy(j.endst.key,Key1);
    j.endti=Value1;
    return j;
}

void Planner::station_query(char Key[],int Value){
    for(int i=0;i<jo.N;i++){
        if(strcmp(jo.A[i].key,Key)==0 && jo.A[i].value>=Value){
        char *x;strcpy(x,jo.A[i].key1);
        cout<<"starting time"<<jo.A[i].value<<"  ";
        cout<<"Destination"<<x<<endl;}
    }
}

void Planner::journey_query(char Key[],int Value,char Key1[]){
    Entry* x=jo.get(Key,Value,Key1);
    DynamicQueue<Entry> go;
    int i=0;
    int min1;
    min1=jo.get(Key,Value,Key1)->value;
    for(;i<jo.N;i++){
    if(strcmp(Key,jo.A[i].key)==0 && jo.get(jo.A[i].key1,jo.A[i].value1,Key1)!=NULL){
            go.QInsert(jo.A[i]);
        }}
    if(go.isEmpty()){cout<<"No such route exists";}
    else{Entry min=go.A[0];
        for(int j=1;j<=i;j++){
            if(go.A[j].value<min.value){min=go.A[j];}
        }
        Entry* y=jo.get(min.key1,Value,Key1);
        if(min1>min.value){cout<<"Starting Time:"<<min.value<<"   Intermediate Station:"<<min.key1<<"  next train starting time:"<<y->value<<endl;}
        else{cout<<min1;}}
    }
int main(){
    Planner pl;
    for(int i=0;i>=0;i++){
        char input[32];
        cout<<">>>";
        cin>>input;

        if(strcmp(input,"QUIT") == 0){//QUIT
      break;
    }
    if(strcmp(input,"ADD") == 0){//ADD string int string int

      char inputKey[32],inputKey1[32];
      cin >> inputKey;
      int value,value1;
      cin >> value;
      cin>>inputKey1;
      cin>>value1;
      Entry data;
      strcpy(data.key,inputKey);strcpy(data.key1,inputKey1);
      data.value  = value;data.value1=value1;
      int hashValueData = pl.jo.hashValue(value);
      int freeIndexData = pl.jo.findFreeIndex(value);
      cout << "Hash Value: " << hashValueData << endl;
      cout << "Free Location: "<< freeIndexData << endl;
      if(freeIndexData >= 0){
        pl.jo.put(data);
        cout << "Successfully Added " << endl;
      }
      else{
        cout << "NO Available space " << endl;
      }
    }
    if(strcmp(input,"QUERY_STATION")==0){//QUERY_STATION string int
        char inputKey[32];int value;
        cin>>inputKey;
        cin>>value;
        pl.station_query(inputKey,value);
    }
    if(strcmp(input,"QUERY_JOURNEY")==0){//QUERY_JOURNEY string int string
        char inputKey[32],inputKey1[32];
        int value;
        cin>>inputKey>>value>>inputKey1;
        pl.journey_query(inputKey,value,inputKey1);
    }
    }
}
