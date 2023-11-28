#include"planner.h"
#include"dictionary.cpp"
#include<iostream>
using namespace std;


class Planner{
    Dictionary dictionary;

public:
    void query_handler(){
    for(int i=0;i>=0;i++){
        char input[32];
        cout<<">>> ";
        cin>>input;
        if(strcmp(input,"EXIT")==0){
            break;
        }


        if(strcmp(input,"ADD")==0){
            char station_one[32];
            cin>>station_one;
            float start_time;
            cin>>start_time;
            char station_two[32];
            cin>>station_two;
            float finish_time;
            cin>>finish_time;

            Entry node;
            strcpy(node.key,station_one);
            node.start_time=start_time;
            strcpy(node.station_two,station_two);
            node.finish_time=finish_time;

            int ins=insert(node);
            // if(ins==true){
            //     cout<<"Entry stored successfully"<<endl;
            // }

            // else{
            //     cout<<"No available space"<<endl;
            // }
        }


        else if(strcmp(input,"QUERY_STATION")==0){
            char station_one[32];
            cin>>station_one;
            float start_time;
            cin>>start_time;

            int count=0; 
            Entry * all;
            find_all(station_one,start_time,count,all);
            for(int i=0;i<count;i++){
                cout<<all[i].start_time<<" "<<all[i].station_two<<endl;
            }
            if(count==0){
                cout<<"No such journey exists"<<endl;
            }

        }


        else if(strcmp(input,"QUERY_JOURNEY")==0){
            char station_one[32];
            cin>>station_one;
            float start_time;
            cin>>start_time;
            char station_two[32];
            cin>>station_two;

            char inter[32];
            float st=-1;
            
            float soonest_start =soonest(station_one,start_time,inter,st, station_two);

            if(soonest_start==2401){
                cout<<"No such journey exists"<<endl;
            }

            else if(st==-1){
                cout<<soonest_start<<endl;
            }

            else{
                cout<<soonest_start<<" "<<inter<<" "<<st<<endl;
            }
            
        }
    }
}


    bool insert(Entry node){
        return dictionary.put(node);    
    }

    Entry * find_all(char key[], int start,int &count,Entry *&all){
        return dictionary.get(key,start,count,all);
    } 

    float soonest(char key[],float start ,char (&inter)[32], float &st, char station_two[] ){
        return dictionary.soonest(key,start,inter,st,station_two);
    } 

};
