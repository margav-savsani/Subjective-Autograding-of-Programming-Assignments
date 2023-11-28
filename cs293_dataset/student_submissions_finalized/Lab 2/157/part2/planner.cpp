#include<iostream>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<fstream>
#include <tuple>
#include<cmath>
using namespace std;

int hashValue(string key,int N){
    const double x=33; //hash map code
    double n=key.length(); //size of key string
    const double A1=(sqrt(5)-1)/2;
    double sum=0; //hash value to be computed
    for(int i=(n-1);i>=0;i--){
        sum=(sum*x+A1*key[i]);
        sum=(sum-floor(sum));
    }
    return floor(sum*N);
  };

struct Journey {
  // define suitable fields here
  tuple <string,float,string,float> route;
  int value=-1;
  Journey(string srcstat, float strtime, string deststat, float endtime){
    get<0>(route)=srcstat;
    get<1>(route)=strtime;
    get<2>(route)=deststat;
    get<3>(route)=endtime;
  }
  Journey(){};
};

class Dictionary {
 public:
  int N; // size of array A
  Journey *A; // Array of dictionary entries


  // Find the position where given key can be inserted (after resolving hash collision if any); return value between 0 and N-1 if free location present; return -1 if no free location
  int findFreeIndex(string key){
    int keyhv=hashValue(key,this->N); //first find hashvalue of given key
    for(int i=keyhv;i<N;i++){
        if(A[i].value==-1) return i; //start iterating from the given hashvalue till null (-1) is encountered
    }
    return -1;
  };

  // Default constructor
  Dictionary(){
    this->N=64;
    A= new Journey[N];
  };


  // Put the given entry in the appropriate location (using hashing) in the dictionary; return true if success, false if failure (array is full)
  bool put(Journey B){
    if(findFreeIndex(get<0>(B.route))==-1) return false; //if no free index return false
    else {
        int free_index=findFreeIndex(get<0>(B.route));
        A[free_index]=B;                    //else put key at free index and return true
        return true;
        }
  };
};


int main(){
int N1=64; //dictionary size
Dictionary planner; //Create a journey planner
string s1,s2,command; //strings for command and two stations
float t1,t2; //Departure and arrival times
int journey_size=0; //number of existing journeys
cout<<"Welcome to Rail Planner."<<endl<<"Enter your command: "<<endl;
while(true){
    cout<<">>>";
    cin>>command;
    if(command=="ADD"){ // Adding a new journey
        cin>>s1>>t1>>s2>>t2;
        //store stations in dictionary using hashvalue of the departure station
        int freeind=planner.findFreeIndex(s1);            //compute hashvalue and find free index
        planner.A[freeind].route=make_tuple(s1,t1,s2,t2); //add journey
        planner.A[freeind].value=0;                      //set journey value to 0 from -1
        journey_size++;                                  //increment journey counter
        cout<<"Journey added successfully"<<endl;
        }
    else if(command=="EXIT") break; //Exiting the planner
    else if(command=="QUERY_STATION"){
        cin>>s1>>t1;
        int num_journey=0; //counter if journey exists or not
        int exist=0;        //counter if station exists or not

        int keyhv=hashValue(s1,N1); //compute hashvalue for station search

        for(int j=keyhv;j<N1;j++){
            if(planner.A[j].value==-1) break; //if null encountered then break
            else if (get<1>(planner.A[j].route)>=t1&&get<0>(planner.A[j].route)==s1){
                cout<<get<1>(planner.A[j].route)<<" "<<get<2>(planner.A[j].route)<<endl;
                num_journey++;
            }
            if(get<0>(planner.A[j].route)==s1) exist++;
        }
        if(exist==0) cout<<"Error! Station doesn't exist."<<endl;
        else if(num_journey==0) cout<<"No journey exists."<<endl;
    }

    else if(command=="QUERY_JOURNEY"){
        cin>>s1>>t1>>s2;
        float mintime=10000;    //soonest time initialized
        float midtime;          //departure time from intermediate stop
        string interstat;       //intermediate station name
        string f_inter;         //final string of intermediate station
        int keyhv=hashValue(s1,N1);       //compute hashvalue for station search
        for(int j=keyhv;j<N1;j++){        //first check for one stop routes
            if(planner.A[j].value==-1) break; //if null encountered then break

            if(get<0>(planner.A[j].route)==s1&&get<2>(planner.A[j].route)!=s2){
            interstat=get<2>(planner.A[j].route);
            int key2=hashValue(interstat,N1);     //compute hashvalue of the intermediate stop
            for(int k=key2;k<N1;k++){             //check journey starting from intermediate stop to query destination
                if(planner.A[k].value==-1) break;   //if null encountered then break
                if(get<0>(planner.A[k].route)==interstat&&get<2>(planner.A[k].route)==s2&&get<1>(planner.A[j].route)<=mintime&&get<1>(planner.A[j].route)>=t1){
                    midtime=get<1>(planner.A[k].route);
                    f_inter=interstat;
                    mintime=get<1>(planner.A[j].route);
                    }
                }
            }
        }
        float interstop=mintime;  //store min start time of journey with one stop
        for(int j=keyhv;j<N1;j++){ //search for direct routes
            if(planner.A[j].value==-1) break;
            if(get<0>(planner.A[j].route)==s1&&get<2>(planner.A[j].route)==s2&&get<1>(planner.A[j].route)>=t1&&get<1>(planner.A[j].route)<=mintime){
                mintime=get<1>(planner.A[j].route);
            }
        }
        if(mintime==10000) cout<<"No Journey exists."<<endl;
        else if(mintime!=interstop)cout<<mintime<<endl;       //mintime not same as interstop implies sooner direct route exists
        else cout<<mintime<<" "<<f_inter<<" "<<midtime<<endl; ////mintime same as interstop

}
}
}
