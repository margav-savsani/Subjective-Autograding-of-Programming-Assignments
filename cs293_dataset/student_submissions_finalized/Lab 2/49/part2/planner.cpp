#include "planner.h"

Planner :: Planner(){//constructor
    N=96;
    A=new Journey[N];
    
} 
bool Planner:: add(Station s1, float t1, Station s2, float t2){
    Journey data;
    data.start=s1;
    data.end=s2;
    data.t1=t1;
    data.t2=t2;
    int probe = t1/100;
    for(int i=0;i<N;i++){
        if((A[probe].t1==0)&&(A[probe].t2==0)){//adding into array  if space is there 
            A[probe]=data;                      
            return true;
        } 
        else probe=(probe+1)%N;       
    }
    return false;
}
void Planner:: query_station(Station s, float t){
    int probe = t/100;
    int count=0;
    for(int i = 0;i<N;i++){
        if((A[probe].t1>=t)&&(A[probe].start.name==s.name)){// checks whether any such train journey exists or not
            count++;
            cout<<A[probe].t1<<" "<<A[probe].end.name<<endl;
        }
        probe=(probe+1)%N;
    }
    if(count==0)cout<<"ERROR"<<endl;
}
void Planner :: query_journey(Station s1,float t, Station s2){
    int probe = t/100;
    Journey* J=new Journey[N];
    Journey* K=new Journey[N];
    int count1=0,count2=0,count3=0;     
    for(int i=0;i<96;i++){
        if((A[probe].t1>=t)&&(A[probe].start.name==s1.name)){
            J[count1]=A[probe];// copies train journeys which start from station1 after or at the given time 
            count1++;                
        } 
        if(s2.name==A[probe].end.name){
            K[count2]=A[probe];// copies journeys which end at station2            
            count2++;            
        }           
        probe=(probe+1)%N;            
    }
    for(int j=0;j<count1;j++){
        if(J[j].end.name==s2.name){// compares whether journey starting at s1 ends at s2 or not if it ends it returns it
            cout<<J[j].t1<<endl;
            count3++; 
            break;           
        }
        else{
            int i=0;
            while(i<count2){//checks any journey exists with one intermediate station
                if((J[j].t2<=K[i].t1)&&(J[j].end.name==K[i].start.name)){
                    cout<<J[j].t1<<" "<<K[i].start.name<<" "<<K[i].t1<<endl;
                    count3++;
                    break;
                }
                i++;
            }
            if(count3==1)break;                      
        }
    }
    if(count3==0)cout<<"ERROR"<<endl;
} 
    
