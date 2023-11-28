#include<iostream>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<fstream>
#include"planner.h"
using namespace std;

int main(){

    Planner p;
    
    while(1){
        char what[32];
        // cout<<"Ready to take another query-"<<endl;
        cin >> what;
        if(strcmp(what, "EXIT")==0){
            // cout<<"me";
            // break;
            return 0;
        }
        string output = p.queryHandler(what);
        cout<<output<<endl;
        
    }
}