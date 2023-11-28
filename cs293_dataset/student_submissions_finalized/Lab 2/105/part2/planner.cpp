#include<iostream>
#include<string.h>
#include"planner.h"
using namespace std;

void Query_handler(Query &query1,Query &query2){
    Journey j;
    for(int i=0;i>=0;i++){
        char input[20];
        cin>>input;

        if(strcmp(input,"EXIT")==0) break;

        if(strcmp(input,"ADD")==0){
            char stn1[30], stn2[30];
            int t1,t2;
            cin>>stn1>>t1>>stn2>>t2;
            Station data1,data2;
            Journey data={data1,data2};
            strcpy(data1.key,stn1);strcpy(data2.key,stn2);
            data1.value=t1;data2.value=t2;
            query1.put(data1);query2.put(data2);
        }    
    }
}

int main(){

}
