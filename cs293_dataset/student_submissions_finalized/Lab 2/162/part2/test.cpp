#include <iostream>
#include <stdexcept>
#include <cstdlib>
#include <cstring>

#include "planner.cpp"

using namespace std;


int main() {

    Planner planner;

    while(true)
    {
      Query q;
      char command[32];
      // cout<<">>";
      cin>>command;
      if(strcmp(command,"ADD")==0)
      {    
          char station1[32];
          float startTime;
          char station2[32];
          float endTime;
          cin>>station1;
          cin>>startTime;
          cin>>station2;
          cin>>endTime;
          strcpy(q.journey.station1.stationName,station1);
          strcpy(q.journey.station2.stationName,station2);
          q.journey.startTime = startTime;
          q.journey.endTime = endTime;

          planner.ADD(q);
          
      }

       if(strcmp(command,"QUERY_STATION")==0)
      {
          char station1[32];
          float time;
          cin>>station1;
          cin>>time;    
          strcpy(q.journey.station1.stationName,station1);
          q.journey.startTime = time;
          vector<Journey> journeys = planner.QUERY_STATION(q);
          if(journeys.size() ==0)
          {
            cout<<"ERROR"<<endl;
            continue;
          }
          for(int i = journeys.size()-1; i >=0 ; i--)
          {
            cout<<journeys[i].startTime<<" "<<journeys[i].station2.stationName<<endl;
          } 
      }

       if(strcmp(command,"QUERY_JOURNEY")==0)
      {
        char station1[32];
          float startTime;
          char station2[32];
          cin>>station1;
          cin>>startTime;
          cin>>station2;
          strcpy(q.journey.station1.stationName,station1);
          strcpy(q.journey.station2.stationName,station2);
          q.journey.startTime = startTime;

          ThreeTuple result = planner.QUERY_JOURNEY(q);
          if(result.n1 > 2400)
          {
            cout<<"ERROR"<<endl;
          }
          else if(result.n2 > 2400 || result.string == "NULL")
          {
            cout<<result.n1<<endl;
          }
          else
          {
            cout<<result.n1<<" "<<result.string<<" "<<result.n2<<endl;
          }
      }

       if(strcmp(command,"EXIT")==0)
      { 
        return 0;
      }

      
    }
}

