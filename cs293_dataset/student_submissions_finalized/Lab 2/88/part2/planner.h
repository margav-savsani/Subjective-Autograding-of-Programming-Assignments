#ifndef PLANNER_H
#define PLANNER_H
#include "dictionary.cpp"
using namespace std;

struct Query{
  // define suitable fields here
  const char *action;
  char station1[30], station2[30];
  float start, finish;
  int num_results;
  Journey *result; // stores results of query as an array

public:
  Query(){
    result = new Journey[5];
    num_results = 0;
  }
  ~Query(){
    delete[] result;
  }
};

class Planner {
  // define suitable fields here
  Dictionary d;
  bool HandleAdd(Query &q){
    Journey J;
    // storing the station data in the Journey object
    strcpy(J.station1, q.station1);
    strcpy(J.station2, q.station2);
    J. start = q.start; J.finish = q.finish;

    Entry e;
    // storing J inside entry and trying to store it inside dictionary
    e.value = J; e.key = e.value.station1;
    int freeIndexData = d.findFreeIndex(q.station1);
    if(freeIndexData >= 0){
      d.put(e);
      return 1;
    }
    else{
      return 0; // returns 0 if dictionary is full
    }   
  }
  void HandleStationQuery(Query &q, Journey *result){
    d.getall(q.station1, result, q.num_results, q.start); // gets all trains originating from station1 and stores it in result
  }
  void HandleJourneyQuery(Query &q, Journey *result){
    float fastest = 9999;
    d.FastestOneStop(q.station1, q.station2, q.start, result, q.num_results, fastest); // gets the fastest train journey involving at most
                                                                                       // one stop and stores it in result
  }
  void DisplayResults(Query &q, Journey *result){
    // process each type of query separately
    if(strcmp(q.action, "QUERY_STATION") == 0){
      if(q.num_results == 0){
        cout << "ERROR: No search results found." << endl; // error message
      }
      else{
        for(int i=0; i<q.num_results; i++){
          (result+i)->dump(q.action); // print relevant details of all trains 
        }
      }
    }
    else if(strcmp(q.action, "QUERY_JOURNEY") == 0){
      if(q.num_results == 0){
        cout << "ERROR: No possible train journey between given two stations." << endl; // error message
      }
      else if(q.num_results == 1){
        result->dump("QUERY_JOURNEY_NO_STOP"); // print relevant details of journey
      }
      else if(q.num_results == 2){
        result->dump("QUERY_JOURNEY_STOP_0"); // print relevant details of journey
        (result+1)->dump("QUERY_JOURNEY_STOP_1");
      }
    }
  }
public:
  bool HandleQuery(char *a){
    Query q;
    q.action = a;
    // process each type of query
    if(strcmp(a, "EXIT") == 0) return 0;
    if (strcmp(a,"ADD") == 0){
      cin>>q.station1>>q.start>>q.station2>>q.finish;
      bool b = HandleAdd(q); // function to add station to dictionary
      if (!b){
        cout << "ERROR: Dictionary is full" << endl;
      }
    }
    else if(strcmp(a, "QUERY_STATION") == 0){
      cin>>q.station1>>q.start;
      HandleStationQuery(q, q.result); // function to handle station query
      DisplayResults(q, q.result); // function to desplay result according to query
    }
    else if(strcmp(a, "QUERY_JOURNEY") == 0){
      cin>>q.station1>>q.start>>q.station2;
      HandleJourneyQuery(q, q.result); // function to handle journey query
      DisplayResults(q, q.result);
    }
    return 1;
  }
};

#endif