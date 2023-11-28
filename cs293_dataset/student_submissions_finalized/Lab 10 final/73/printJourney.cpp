#ifndef PRINT_JOURNEY_CPP
#define PRINT_JOURNEY_CPP

#ifndef PLANNER_H
#include "planner.h"
#endif

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

using namespace std;

bool checkTransit(TrainInfoPerStation *jrny1,TrainInfoPerStation *jrny2,int maxTransitTime,StationAdjacencyList *list,int src,int *path)
{
  //for checking the transit times
  listOfObjects<StationConnectionInfo *> *s1,*s2;
  s1=list[path[src]].fromStations;
  s2=list[path[src]].toStations;
  while (s1->object->adjacentStnIndex != path[src-1])
    s1=s1->next;
  while (s2->object->adjacentStnIndex != path[src+1])
    s2=s2->next;
  listOfObjects<TrainInfoPerStation *> *j1,*j2;
  j1=s1->object->trains;//to get the arr time with same jrny code as jrny1
  j2=s2->object->trains;//to get the arr time with same jrny code as jrny2
  while(j1->object->journeyCode != jrny1->journeyCode)
  {
    j1=j1->next;
    if (j1==nullptr)
      return false;
  }
  while(j2->object->journeyCode != jrny2->journeyCode)
  {
    j2=j2->next;
    if (j2==nullptr)
      return false;
  }
  int d1=0,d2=0;
  for (int i=0;i<7;i++)
  {//getting the days
    if (jrny1->daysOfWeek[i])
      d1=i;
    if (jrny2->daysOfWeek[i])
      d2=i;
  }
  int t=j1->object->arrTime+maxTransitTime*100;
  int t2=j2->object->depTime;
  if (t%100>60)
    t=t+100-60;
  if (t > 2400 && d1==6)
  {
    t=t%2400;
    d1=0;
  }
  //first condition is for max transit time and 2nd is for checking the train arrives before the dep of the 2nd train
  if (t+d1*2400 > t2+(d2)*2400 && j1->object->arrTime+d1*2400 < t2+d2*2400)
  {
    return true;
  }
  return false;
}

bool printTrains(int *path,int &path_index,StationAdjacencyList *list,int maxStopOvers,int maxTransitTime,int stopnum,int num,TrainInfoPerStation *jrny,int val)
{
  //got more than the max stops
  if (stopnum > maxStopOvers)
    return false;
  if (num==0)
  {
    //for the starting station
    listOfObjects<StationConnectionInfo *> *nextstn=list[path[num]].toStations;
    while (nextstn->object->adjacentStnIndex != path[num+1] )
      nextstn=nextstn->next;
    listOfObjects<TrainInfoPerStation *> *traininfo=nextstn->object->trains;
    listOfObjects<TrainInfoPerStation *> *currList, *expandedList;
    TrainInfoPerStation *currInfo;
    currList = nextstn->object->trains;
    expandedList = nullptr;
    int listLength = 0;
    //expanding the list by days
    while (currList != nullptr) {
      currInfo = currList->object;
      if (currInfo != nullptr) {
        // Make as many copies of currInfo as the total count of days in the week
        // when this train runs from/to this station
        int jCode = currInfo->journeyCode;
        int stSeq = currInfo->stopSeq;
        int arrTime = currInfo->arrTime;
        int depTime = currInfo->depTime;
      
        for (int i=0; i < 7; i++) {
      if (currInfo->daysOfWeek[i]) {
      TrainInfoPerStation *newExpandedElement = new TrainInfoPerStation(jCode, stSeq, arrTime, depTime);
      if (newExpandedElement == nullptr) {
        cerr << "Memory allocation failure." << endl;
        continue;
      }
      newExpandedElement->setDayOfWeek(i);

      listOfObjects<TrainInfoPerStation *> *newExpandedListElement = new listOfObjects<TrainInfoPerStation *> (newExpandedElement);
      if (newExpandedListElement == nullptr) {
        cerr << "Memory allocation failure." << endl;
        continue;
      }

      if (expandedList == nullptr) {
        expandedList = newExpandedListElement;
      }
      else {
        newExpandedListElement->next = expandedList;
        expandedList->prev = newExpandedListElement;
        expandedList = newExpandedListElement;
      }
      listLength++;
    }
        }
      }
      currList = currList->next;
    }
    traininfo=expandedList;
    //checking the list
    while(traininfo != nullptr)
    {
      printTrains(path,path_index,list,maxStopOvers,maxTransitTime,0,1,traininfo->object,1);
      traininfo=traininfo->next;
    }
  }
  else if (num<path_index-1)
  {
    //intermdiate jrny
    listOfObjects<StationConnectionInfo *> *nextstn=list[path[num]].toStations;
    while (nextstn->object->adjacentStnIndex != path[num+1] )
      nextstn=nextstn->next;
    listOfObjects<TrainInfoPerStation *> *traininfo=nextstn->object->trains;
    listOfObjects<TrainInfoPerStation *> *currList, *expandedList;
    TrainInfoPerStation *currInfo;
    string days[7] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};

    // Expanding information in stnInfoList to get a list of train info
    // in which each element of the list refers to a single day of the
    // week.  This is the list that has to be finally sorted using
    // quicksort.

    currList = nextstn->object->trains;
    expandedList = nullptr;
    int listLength = 0;
    //expanding the list
    while (currList != nullptr) {
      currInfo = currList->object;
      if (currInfo != nullptr) {
        // Make as many copies of currInfo as the total count of days in the week
        // when this train runs from/to this station
        int jCode = currInfo->journeyCode;
        int stSeq = currInfo->stopSeq;
        int arrTime = currInfo->arrTime;
        int depTime = currInfo->depTime;
      
        for (int i=0; i < 7; i++) {
      if (currInfo->daysOfWeek[i]) {
      TrainInfoPerStation *newExpandedElement = new TrainInfoPerStation(jCode, stSeq, arrTime, depTime);
      if (newExpandedElement == nullptr) {
        cerr << "Memory allocation failure." << endl;
        continue;
      }
      newExpandedElement->setDayOfWeek(i);

      listOfObjects<TrainInfoPerStation *> *newExpandedListElement = new listOfObjects<TrainInfoPerStation *> (newExpandedElement);
      if (newExpandedListElement == nullptr) {
        cerr << "Memory allocation failure." << endl;
        continue;
      }

      if (expandedList == nullptr) {
        expandedList = newExpandedListElement;
      }
      else {
        newExpandedListElement->next = expandedList;
        expandedList->prev = newExpandedListElement;
        expandedList = newExpandedListElement;
      }
      listLength++;
    }
        }
      }
      currList = currList->next;
    }
    traininfo=expandedList;
    while(traininfo != nullptr)
    {
      //we wont check maxtransit time for direct jrnys
      if (checkTransit(jrny,traininfo->object,traininfo->object->depTime-traininfo->object->arrTime,list,num,path))
      if (traininfo->object->journeyCode == jrny->journeyCode)
      {
        if (printTrains(path,path_index,list,maxStopOvers,maxTransitTime,stopnum,num+1,traininfo->object,val+1))
        {
          string days[7] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};
          int d=0;
          for (int i=0;i<7;i++)
          {
            if (jrny->daysOfWeek[i])
            {
              d=i;
              break;
            }
          }
          cout<<"Day:"<<days[d]<<endl;
          cout<<"JourneyCode: "<<jrny->journeyCode<<" Arr Time: ";
          if (jrny->arrTime == -1)
            cout<<"Starts "<<" Dep: ";
          else
            cout<<jrny->arrTime<<" Dep: ";
          if (jrny->depTime == -1 )
            cout<<"Ends"<<endl;
          else
            cout<<jrny->depTime <<endl<<endl;
        }
      }
      else  
      {
        //check the trasit time if true use the recursion
        if (checkTransit(jrny,traininfo->object,maxTransitTime,list,num,path))
          if (printTrains(path,path_index,list,maxStopOvers,maxTransitTime,stopnum+1,num+1,traininfo->object,val+1))
          {
            string days[7] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};
            int d=0;
            for (int i=0;i<7;i++)
            {
              if (jrny->daysOfWeek[i])
              {
                d=i;
                break;
              }
            }
            cout<<"Day:"<<days[d]<<endl;
            cout<<"JourneyCode: "<<jrny->journeyCode<<" Arr Time: ";
            if (jrny->arrTime == -1)
              cout<<"Starts "<<" Dep: ";
            else
              cout<<jrny->arrTime<<" Dep: ";
            if (jrny->depTime == -1 )
              cout<<"Ends"<<endl;
            else
              cout<<jrny->depTime <<endl;
            cout<<"Please change to Train with Journey code: "<<traininfo->object->journeyCode<<endl<<endl;
          }
      }
      traininfo=traininfo->next;
    }
  }
  //at the end print the train that is coming to the station
  else
  {
    if (path_index == val+1)
    {
      string days[7] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};
      int d=0;
      for (int i=0;i<7;i++)
      {
        if (jrny->daysOfWeek[i])
        {
          d=i;
          break;
        }
      }
      cout<<"Day:"<<days[d]<<endl;
      cout<<"JourneyCode: "<<jrny->journeyCode<<" Arr Time: ";
      if (jrny->arrTime == -1)
        cout<<"Starts "<<" Dep: ";
      else
        cout<<jrny->arrTime<<" Dep: ";
      if (jrny->depTime == -1 )
        cout<<"Ends"<<endl;
      else
        cout<<jrny->depTime <<endl;
      cout<<"The Next stop With this train is Your Destination"<<endl<<endl;
      return true;
    }
    else 
      return false;
  }
  if(stopnum+1> maxStopOvers )
    return false;
  return true;
}
void Trains(int src,int dest,bool *visited,int *path,int &path_index,StationAdjacencyList *list,int maxStopOvers,int maxTransitTime)
{
  //getting the path using DFS
  visited[src]=true;
  path[path_index] = src;
  path_index++;
 
  // If current vertex is same as destination, then print
  // current path[]
  if (src == dest) {
      //after getting the path print the possible trains
      printTrains(path,path_index,list,maxStopOvers,maxTransitTime,0,0,list[path[0]].toStations->object->trains->object,0);
  }
  else // If current vertex is not destination
  {
      // Recur for all the vertices adjacent to current
      // vertex
      listOfObjects<StationConnectionInfo *> *tostn=list[src].toStations;
      while(tostn!=nullptr)
      {
        if (!visited[tostn->object->adjacentStnIndex])
        {
          Trains(tostn->object->adjacentStnIndex,dest,visited,path,path_index,list,maxStopOvers,maxTransitTime);
        }
        tostn=tostn->next;
      }
  } 
  // Remove current vertex from path[] and mark it as
  // unvisited
  path_index--;
  visited[src] = false;
}

void Planner::printPlanJourneys(string srcStnName, string destStnName,int maxStopOvers, int maxTransitTime)
{
  Entry<int> *srcname,*destname;
  int src,dest;
  srcname=stnNameToIndex.get(srcStnName);
  destname=stnNameToIndex.get(destStnName);
  src=srcname->value;
  dest=destname->value;
  listOfObjects<StationConnectionInfo *> *Stn = adjacency[src].toStations;
  if (Stn==nullptr)
  {
    cout<<"No Trains"<<endl;
    return;
  }
  bool *visited=new bool[512];
  int *path=new int[512];
  int path_index=0;
  for (int i = 0; i < 512; i++)
        visited[i] = false;
  //first get the path between 2 stations
  //next get the possible trains
  Trains(src,dest,visited,path,path_index,adjacency,maxStopOvers,maxTransitTime);
}
//by saran 210050036
#endif