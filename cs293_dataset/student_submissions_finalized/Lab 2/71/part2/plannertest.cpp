#include<iostream>
#include "planner.h"
using namespace std;


int main(){
    Planner P;
    cout<<"WELCOME TO TRAIN PLANNER.START GIVING COMMAND"<<endl;
    char *ins = new char[32];
    cin>>ins;
    while(string(ins)!="EXIT"){
        if(string(ins)=="ADD"){
            char *st1= new char[32],*st2= new char[32];
            int start,end;
            cin>>st1>>start>>st2>>end;
            P.add(st1,start,st2,end);
        }
        if(string(ins)=="QUERY_STATION"){
            char *st1= new char[32];
            int start;
            cin>>st1>>start;
            if(P.get_station(st1)!=NULL){
                Query *z=P.get_station(st1)->z;
                for(int i=0; z[i].null==false; i++){
                    if(z[i].start_time >= start){
                        cout<<z[i].start_time<<" "<<z[i].j->dest_name<<endl;
                    }
                }
            }
            else{
                cout<<"NO STATION WITH GIVEN NAME EXIST"<<endl;
            }
        }
        if(string(ins)=="QUERY_JOURNEY"){
            char *st1= new char[32],*st2= new char[32],*intermediate=new char[32];
            int min_start,next_start;
            int ans=2400;
            cin>>st1>>min_start>>st2;
            if(P.get_station(st1)==NULL){
                cout<<"NO STATION WITH GIVEN NAME EXIST"<<endl;
            }
            else{
                Station initial=*P.get_station(st1);
                if(initial.q_st(st2)!=-1){
                    int t_a=initial.q_st(st2);
                    if(t_a>=min_start) ans=t_a;
                }
                Query *t_z=initial.z;
                for(int i=0; t_z[i].null==false; i++){
                    if((t_z[i].start_time >= min_start)&&(t_z[i].start_time < ans)){
                        int finish_time=t_z[i].j->finish_time;
                        char* t_i_n=t_z[i].j->dest_name;
                        if(P.get_station(t_i_n)!=NULL){
                            Station t_i=*P.get_station(t_i_n);
                            if(t_i.q_st(st2)!=-1){
                                int t_s2=t_i.q_st(st2);
                                if(t_s2>=finish_time){
                                    ans=t_z[i].start_time;
                                    intermediate=t_i_n;
                                    next_start=t_s2;
                                }
                            }
                        }                       
                    }
                }
                if(intermediate[0]=='\0'){
                    if(ans==2400) cout<<"NO SUCH POSSIBLE JOURNEY EXISTS"<<endl;
                    else cout<<ans<<endl;
                }
                else{
                    cout<<ans<<" "<<intermediate<<" "<<next_start<<endl;
                }
            }
        }
        cin>>ins;
    }
    return 0;
}