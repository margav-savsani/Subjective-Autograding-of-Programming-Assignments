#ifndef PRINT_JOURNEY_CPP
#define PRINT_JOURNEY_CPP

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

using namespace std;
 bool isNotVisited(int x, listOfObjects<int>* path){
    cout<<16<<endl;
    listOfObjects<int>* a=path;
    while(a!=nullptr){
      if(a->object==x)return false;
      a=a->next;
    }
    return true;
}
void Planner::printPlanJourneys(string srcStnName, string destStnName, int maxStopOvers, int maxTransitTime)
{
   int src_index=stnNameToIndex.hashValue(srcStnName);
    int dest_index=stnNameToIndex.hashValue(destStnName);
    StationAdjacencyList src_adj_list=adjacency[src_index];
    StationAdjacencyList dest_adj_list=adjacency[dest_index];
    listOfObjects<TrainInfoPerStation*> *src_trains=src_adj_list.toStations->object->trains;
    // path vector to store the current path
    listOfObjects<int>* path=new listOfObjects<int>(src_index);
    listOfObjects<TrainInfoPerStation*>* train=src_trains;
    listOfObjects<listOfObjects<int>*>* pathlist=new listOfObjects<listOfObjects<int>*>(path);
    listOfObjects<listOfObjects<TrainInfoPerStation*>*>* final=new listOfObjects<listOfObjects<TrainInfoPerStation*>*>(train);
    listOfObjects<listOfObjects<TrainInfoPerStation*>*>* trains_list=new listOfObjects<listOfObjects<TrainInfoPerStation*>*>(train); 
    int count=0;
    int i=0;
    while(pathlist!=nullptr){
      i++;
        cout<<1<<endl;
        train = trains_list->object;
        path = pathlist->object;
        listOfObjects<int>* a=path;
        while(a->next!=nullptr){
          a=a->next;
        }
        int last = a->object;
        // if last vertex is the desired destination
        // then print the path
        if(last == dest_index){
            count=count+1;
            if(count==1){
              final->object=train;
              cout<<2<<endl;
            }
            else{
              listOfObjects<listOfObjects<TrainInfoPerStation*>*>* b=final;
              while(final->next!=nullptr){
                final=final->next;
              }
              final->next=new listOfObjects<listOfObjects<TrainInfoPerStation*>*>(train);
              final=b;
              cout<<3<<endl;
            }
        }
        listOfObjects<StationConnectionInfo*>* connection_info=adjacency[last].toStations;
        cout<<4<<endl;
        // traverse to all the nodes connected to
        // current vertex and push new path to queue
        while(connection_info!=nullptr){
            cout<<5<<endl;
            if(isNotVisited(connection_info->object->adjacentStnIndex, path)){
                  cout<<90<<endl;
                  listOfObjects<TrainInfoPerStation*>* currnodetrains=connection_info->object->trains;
                  listOfObjects<TrainInfoPerStation*>* currcopy=currnodetrains;
                  listOfObjects<TrainInfoPerStation*>* traincopy=train;
                  listOfObjects<TrainInfoPerStation*>* newtrain=new listOfObjects<TrainInfoPerStation*>(train->object);
                  listOfObjects<TrainInfoPerStation*>* y=newtrain;
                  int count1=0;
                  cout<<30<<endl;
                  while(traincopy!=nullptr){
                    cout<<6<<endl;
                    currcopy=currnodetrains;
                    while(currcopy!=nullptr){
                      cout<<7<<endl;
                      if(traincopy->object->journeyCode==currcopy->object->journeyCode){
                        cout<<8<<endl;
                        count1=count1+1;
                        if(count1==1){
                          newtrain->object=traincopy->object;
                          cout<<9<<endl;
                        }
                        else{
                          cout<<30<<endl;
                          cout<<70<<endl;
                          cout<<21<<endl;
                          while(newtrain->next!=nullptr){
                            newtrain=newtrain->next;
                            cout<<20<<endl;
                          }
                          newtrain->next=new listOfObjects<TrainInfoPerStation*>(traincopy->object);
                          newtrain=y;
                        }
                        break;
                      }
                      currcopy=currcopy->next;
                    }
                    traincopy=traincopy->next;
                  }
                  if(count1!=0){
                    cout<<11<<endl;
                    listOfObjects<int>* newpath=new listOfObjects<int>(path->object);
                    listOfObjects<int>* c=newpath;
                    listOfObjects<int>* a=path;
                    while(a->next!=nullptr){
                      a=a->next;
                      newpath->next=new listOfObjects<int>(a->object);
                      newpath=newpath->next;
                    }
                    newpath->next=new listOfObjects<int>(connection_info->object->adjacentStnIndex);
                    listOfObjects<listOfObjects<int>*>* b=pathlist;
                    while(pathlist->next!=nullptr){
                      pathlist=pathlist->next;
                    }
                    pathlist->next=new listOfObjects<listOfObjects<int>*>(c);
                    pathlist=b;
                    listOfObjects<listOfObjects<TrainInfoPerStation*>*>* p=trains_list;
                    while(trains_list->next!=nullptr){
                      trains_list=trains_list->next;
                    }
                    trains_list->next=new listOfObjects<listOfObjects<TrainInfoPerStation*>*>(newtrain);
                    trains_list=p;
                  }
                  cout<<12<<endl;
            }
            connection_info=connection_info->next;
        }
        cout<<13<<endl;
         trains_list=trains_list->next;
         pathlist=pathlist->next;
         cout<<14<<endl;
     }
      if(count==0){cout<<"No direct journeys available"<<endl;
      cout<<i<<endl;
      cout<<16<<endl;}
      else{
        cout<<15<<endl;
        while(final!=nullptr){
          printStationInfo(final->object);
          final=final->next;
        }
      }
  // insert your code here
  
  cout << "This function is to be implemented by you." << endl;

  // Whenever you need to print a journey, construct a
  // listOfObjects<TrainInfoPerStation *> appropriately, and then
  // use printStationInfo that we had used in Lab 7.
  // printStationInfo is a private member function of
  // the Planner class. It is declared in planner.h and implemented in
  // planner.cpp

  
  return;
}

#endif
