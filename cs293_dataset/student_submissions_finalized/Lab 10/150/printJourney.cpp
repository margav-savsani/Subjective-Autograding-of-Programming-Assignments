#ifndef PRINT_JOURNEY_CPP
#define PRINT_JOURNEY_CPP

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

using namespace std;

struct myclass
{
  int stn;
  TrainInfoPerStation jrny;
};

struct mystore{
  int jrny_code=0;
  int start=0;
  int end=0;
  mystore(){
  jrny_code=0;
  start=0;
  end=0;
  }
  mystore(int a,int b ,int c){
    jrny_code=a;
    start=b;
    end=c;
  }
};

class journey{

public:
mystore myjrny[DICT_SIZE];
int n_stop;
journey(){
  n_stop=0;
}
bool allowed_stat(int stat){
    for (int i=0;i<n_stop;i++){
      if (myjrny[i].start== stat){
        return false;
      }
    }
    return true;
}

void put_jrny(int a , int b, int c){
    myjrny[n_stop].jrny_code=a;
    myjrny[n_stop].start=b;
    myjrny[n_stop].end=c;
    n_stop++;
}

void reset(int n_stop){
    this->n_stop=n_stop;
}
};

  
void Planner::printPlanJourneys(string srcStnName, string destStnName, int maxStopOvers, int maxTransitTime)
{
   
   static bool visited[DICT_SIZE]={false};
  int start_index = stnNameToIndex.get(srcStnName)->value;
  int end_index = stnNameToIndex.get(destStnName)->value;
  // insert your code here
  listOfObjects<StationConnectionInfo *> *myqueue = adjacency[start_index].toStations;
  //cout << "This function is to be implemented by you." << endl;

  // Whenever you need to print a journey, construct a
  // listOfObjects<TrainInfoPerStation *> appropriately, and then
  // use printStationInfo that we had used in Lab 7.
  // printStationInfo is a private member function of
  // the Planner class. It is declared in planner.h and implemented in
  // planner.cpp

  
  //return;
      journey a; int level=0; int end =0;
      while(true){
      while (myqueue != null
     
    }
     if (myqueue2 == nullptr)
      {
        myqueue2 = new listOfObjects<myclass *>(a);
        myqueue2_last = myqueue2;
      }
      else
      {
        myqueue2_last->next = new listOfObjects<myclass *>(a);
        myqueue2_last = myqueue2_last->next;
      }
      trains = trains->next;
    }
    myqueue = myqueue->next;
  }
  // queue of the valid trains i.e, that will go from start to end index
  listOfObjects<TrainInfoPerStation *> *myqueue3 = nullptr;
  listOfObjects<TrainInfoPerStation *> *myqueue3_last = nullptr;




  


#endif
