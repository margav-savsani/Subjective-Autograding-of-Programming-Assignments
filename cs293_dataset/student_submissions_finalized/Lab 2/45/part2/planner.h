#ifndef PLANNER_H
#define PLANNER_H
#include<string>
using namespace std;

struct Journey {                               // defines a struct about a journey b/w 2 stations.takes the 2 stations and start time and end time
  // define suitable fields here               // as objects of the struct.
  float start_time;
  float end_time;
  string stn1;
  string stn2;
};

struct jrny_qry{                              // This struct takes objects defined below .They are useful when using QUERY_JOURNEY cmd
  float start;                                // start times of station 1.
  string intmdt_loc;                          // intermediate station between b/w 2stations (in case of no intmdt station it takes a string "direct")
  float intmdt_start;                         // start time for journey intmdt loc to station2 (in case of no intmdt station it takes -1.)
  bool path_exist=false;                      // if there is no train b/w station1 and station2 (atmost 1stop b/w) it takes false.else true
};

class Planner {
  // define suitable fields here
  private:                                      // N-total max journeys
    int N;
    Journey *J;                                  // an array of struct Journeys
    int tot_jns;                                 // total no of journeys added to the above array
  public:
    Planner(){
      N=64;
      J= new Journey[N];
      tot_jns=0;
    }  
 
    void insert(string s1,float t1,string s2,float t2){    // add the input params to the array and increment tot_jns
      J[tot_jns].stn1=s1;
      J[tot_jns].stn2=s2;
      J[tot_jns].start_time=t1;
      J[tot_jns].end_time=t2;
      tot_jns++;
    }


    jrny_qry soonest(string s1,float t1,string s2){         //return a struct jrny_qry for the soonest arrival path b/w station s1,s2 after time t1
      jrny_qry x;                                           // define a struct jrny_qry x
      
      for(int i=0;i<tot_jns;i++){
        if(J[i].stn1==s1 and J[i].stn2==s2 and J[i].start_time>=t1)      // first checks if a direct train is available b/w s1 and s2
        {                                                                // if so takes appropiate values to the objects of struct jrny-qry x
          x.start=J[i].start_time;          
          x.intmdt_loc="direct" ;
          x.intmdt_start=-1; 
          x.path_exist=true;    
        }

        if(J[i].stn1==s1 and J[i].start_time>=t1)                // This is to check for 1stop b/w s1 and s2.
        {
          for (int j=0;j<tot_jns;j++){
            if(J[j].stn1==J[i].stn2 and J[j].stn2==s2 and J[j].start_time>=J[i].end_time)  // A-stn1,B-stn2,C-intermediate stop.checks if such C exists
            {                                                                              // btw A and B
              
              if(x.start>J[i].start_time){                                        // if it exists checks if its start time is less than x.start
                                                                                  // if it is less, overwrite x as jrny_qry for this path.
                x.start=J[i].start_time;
                x.intmdt_loc=J[j].stn1;
                x.intmdt_start=J[j].start_time;                
                x.path_exist=true;
              }
            }
          }
        }

      }
      return x;
    }

    void stn_qry(string s1,float t1){                                    // prints all journeys at station s1 after time t1.
      int stn_exist=0;                                                   // if no stn s1 exists in the Journey array, it keeps its value as 0.
      int trn_avlble=0;                                                  // if station exists but no more trains available after time t1,its value is 0
      for(int i=0;i<tot_jns;i++){                                        // intially intialised both variables to 0.
        if(s1==J[i].stn1){                                               // now check for s1 in the array,if it exists check for trains after time t1.
          stn_exist++;                                                   // if such trains exist,now output start time and destination loc for all such trains 
          if(J[i].start_time>=t1){
            trn_avlble++;
            cout<<J[i].start_time<<"  "<<J[i].stn2<<endl;
          }                     
        }
      }

      if(stn_exist==0){
        cout<< "No such station exist"<<endl;
      }
      if(trn_avlble==0 and stn_exist!=0){
        cout << "No more trains available "<<endl;
      }
      
    }

};

#endif
