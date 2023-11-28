#include "planner.h"
#include <cmath>
#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

const double igr=0.618;
const double x=37;
const float epsilon=0.001;

int Planner::hashValue(char key[]){
    int i=0;
    double a=key[i];
    while(key[i]!='\0'){
        int b=key[i+1];
        a=(((a*x)*igr))-(long)(((a*x)*igr))+(b*igr)-(long)(b*igr);//x-(long)x gives fractional part
                                                                  //Here is calculate (ax%1+b%1)%1 on a loop.
        a=a-(long)a;
        i+=1;
    }
    return floor(N*a);
}

int Planner::findFreeIndex(char key[]){
    int h=hashValue(key);
    for(int i=0;i<N;i++){
        if(eq(A[h].start_time,-1)||(string)A[h].station_one=="tomb") return h;
        // cout<<"Hi:"<<i<<endl;
        h=(h+1)%N;
    }
    return -1;
}

Planner::Planner(){
    N=DICT_SIZE;
    A=new Journey[N];
}

bool Planner::addJourney(struct Journey j){
    int freeindex=findFreeIndex(j.station_one);
    if(freeindex==-1){
        return false;
    }
    else{
        A[freeindex]=j;
        return true;
    }
}

vector<Journey> Planner::returnTrains(char station_one[],float start_time){
    vector<Journey> vj;
    int h=hashValue(station_one);
    int i;
    for(i=0;i<N;i++){
        // if(eq(A[h].start_time,-1)){
        //     cout<<"ERROR:Station Not Found!\n";break;
        // }
        if((string)A[h].station_one==(string)station_one && (A[h].start_time>start_time||eq(A[h].start_time,start_time))){
            vj.push_back(A[h]);
            // cout<<"Hash Value Of Place That Is Being Added is: "<<h<<endl;
            // cout<<"Added Train with station_one as: "<<A[h].station_one<<" and start_time as: "<<A[h].start_time<<endl;
        }
        h=(h+1)%N;
    }
    // if(i==N){
    //     cout<<"ERROR:Station Not Found!\n";
    // }
    return vj;
}

void Planner::printJourney(char station_one[], float start_time, char station_two[]){
    int h=hashValue(station_one);
    vector<Journey> listofTrains;
    listofTrains=returnTrains(station_one, start_time);
    sort(listofTrains.begin(),listofTrains.end());
    // cout<<"For Loop Starts\n";
    // for(int i=0;i<listofTrains.size();i++){
        // cout<<listofTrains[i].station_one<<" "<<listofTrains[i].start_time<<" "<<listofTrains[i].station_two<<endl;
    // }
    // cout<<"For Loop Ends\n";
    for(int i=0;i<listofTrains.size();i++){
        if((string)listofTrains[i].station_two==(string)station_two){
            // cout<<"Direct Journey Wow!!"<<endl;
            cout<<listofTrains[i].start_time<<endl;
            return;
        }
        else{
            char midway[32];
            int arrAtMidway=listofTrains[i].finish_time;
            vector<Journey> trainsAfterMidway;
            trainsAfterMidway=returnTrains(listofTrains[i].station_two,arrAtMidway);
            for(int j=0;j<trainsAfterMidway.size();j++){
                if((string)trainsAfterMidway[j].station_two==(string)station_two){
                    cout<<listofTrains[i].start_time<<" "<<listofTrains[i].station_two<<" "<<trainsAfterMidway[j].start_time<<endl;
                    return;
            }
            }
        }
    }
    cout<<"ERROR: No Such Path Exists!\n";
}




// bool compareByTime(const Journey &a, const Journey &b){
//     return (a.start_time<b.start_time);
// }

bool Planner::eq(float a, float b){
    return abs(a-b)<epsilon;
}