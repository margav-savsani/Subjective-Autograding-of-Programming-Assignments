#ifndef PRINT_JOURNEY_CPP
#define PRINT_JOURNEY_CPP

#ifndef PLANNER_H
#include "planner.h"
#endif

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

using namespace std;

// planner class has adjacency array each entry of which correspponds to a station
// each entry is a ptr of type Station Adjacency List and corresponds to a particular station
// each Station Adjacency list has a to and from linked list
// each entry of which is StationConnectionInfo which contains a stn index which tells the station number and train info per station which contains the journey code

class trial {
public:
  int journeyCode; // same as train number

  int stnto; // stn index of the station train is going to

  bool daysOfWeek[7]; // Days of week when this train travels
                      // to/from this station
  int arrTime;  // Arrival time at station; -1 if train starts from here
  int depTime;  // Departure time from station; -1 if train ends here
  unsigned short stopSeq; // stoppage of source station

public:

  //parametrized construuctor
  trial(int jCode,int stnto,int aTm,int dTm,bool daysOfWeek[7],unsigned short stopSeq)
  {
    // initialising
    journeyCode=jCode;
    this->stnto=stnto;
    arrTime=aTm;
    depTime=dTm;
    for (int i=0;i < 7;i++) {
      if(daysOfWeek[i]==true){
        this->daysOfWeek[i]=true;
      }
      else{
        this->daysOfWeek[i]=false;
      }
    }
    this->stopSeq=stopSeq;
  }

  //constructor
  trial();

  //destructor
  ~trial() {;}

};



void Planner::printDirectJourneys(string srcStnName,string destStnName)
{
  // insert your code here
  // cout << "This function is to be implemented by you." << endl;

  //initializing all variables to NULL

  // this is the queue via which bfs is carried out
  listOfObjects<trial*> * queue=NULL;
  //tail_ptr
  listOfObjects<trial*> * tail_queue=NULL;


  // final queue to be printed out
  listOfObjects <TrainInfoPerStation*> * final=NULL;
  // head of the final_queue for teh purpose of insertion
  listOfObjects <TrainInfoPerStation*> * tail_final=NULL;

  // getting index for source and destination
  int source_index=(stnNameToIndex.get(srcStnName))->value;
  int dest_index=(stnNameToIndex.get(destStnName))->value;

  // populating the queue for the first time
  listOfObjects<StationConnectionInfo *>* iter=adjacency[source_index].toStations;
  int count=0;
  int counter=0;

  while(iter!=NULL){

    // adjacent station index
    int des_index=iter->object->adjacentStnIndex;

    // to loop through all trains going from that station to des_index station
    listOfObjects<TrainInfoPerStation *> * iter_in=iter->object->trains;

    while(iter_in!=NULL){
      listOfObjects<TrainInfoPerStation*>* actual=stationInfo[source_index];
      while(actual!=NULL){
        if(actual->object->journeyCode==iter_in->object->journeyCode){
          break;
        }
        else{
          actual=actual->next;
        }
      }

      // if the destination station is the next station, no need to insert in queue, directly insert in list to be printed
      if(des_index==dest_index){
        TrainInfoPerStation* one_way_to_reach=new TrainInfoPerStation (iter_in->object->journeyCode,actual->object->stopSeq,actual->object->arrTime,actual->object->depTime);
          for (int i=0;i<7;i++){
            if(actual->object->daysOfWeek[i]==true){
              one_way_to_reach->daysOfWeek[i]=true;
            }
          }
        // inserting element in the list to be returned
        listOfObjects <TrainInfoPerStation*>* one_way=new listOfObjects <TrainInfoPerStation*>(one_way_to_reach);

        // inserting the first element
        if(counter==0){
          final=one_way;
          tail_final=one_way;
          counter++;
        }

        //inserting other elements
        else{
          tail_final->next= one_way;
          one_way->prev=tail_final;
          tail_final=tail_final->next;
        }
      }

      else{
        trial *to_insert= new trial(iter_in->object->journeyCode,des_index,actual->object->arrTime,actual->object->depTime,actual->object->daysOfWeek,actual->object->stopSeq);
        listOfObjects<trial*> * to_ins=new listOfObjects<trial*>(to_insert);

        //first insertion
        if(count==0){
          tail_queue=to_ins;
          queue=tail_queue;
          count++;
        }

        //later insertions
        else{
          tail_queue->next=to_ins;
          to_ins->prev=tail_queue;
          tail_queue=tail_queue->next;
        }
      }
      //traversal
      iter_in=iter_in->next;

    }

    //traversal
    iter=iter->next;
  }

  // as the queue has been populated
  // looping till this becomes empty


  // found_next is true if next train with the same journey code is found
  bool found_next=false;

  // looping through all elements of the queue
  while(queue!=NULL){

    // found_next is false at the start of search for every element of the queue
    found_next=false;

    // have to look through the trains leaving from this index
    int go_to_index=queue->object->stnto;
    listOfObjects<StationConnectionInfo *>* iter=adjacency[go_to_index].toStations;
    int jrny_to_search=queue->object->journeyCode;

      // now have to loop through all trains going from that station to find the station with the same journey code
      // looping through the tostation list of that station
      while(iter!=NULL){
        int next_index=iter->object->adjacentStnIndex;
        listOfObjects<TrainInfoPerStation *> * iter_in=iter->object->trains;

        // looping through all trains with different journey codes going from that intermediate station to the next station
        while(iter_in!=NULL){

          // if journey code of next connecting train and train of queue matches
          if(iter_in->object->journeyCode == jrny_to_search){

            // found a path that reaches the destination that is the next index the train is going to is the destination index
            if(next_index==dest_index){
              TrainInfoPerStation* one_way_to_reach=new TrainInfoPerStation (queue->object->journeyCode,queue->object->stopSeq,queue->object->arrTime,queue->object->depTime);
              for (int i=0;i<7;i++){
                if(queue->object->daysOfWeek[i]==true){
                  one_way_to_reach->daysOfWeek[i]=true;
                }
              }
              // inserting element in the list to be returned
              listOfObjects <TrainInfoPerStation*>* one_way=new listOfObjects <TrainInfoPerStation*>(one_way_to_reach);

              // inserting the first element
              if(counter==0){
                final=one_way;
                tail_final=one_way;
                counter++;
              }

              //inserting other elements
              else{
                tail_final->next= one_way;
                one_way->prev=tail_final;
                tail_final=tail_final->next;
              }
              found_next=true;
              break;
            }

            // jcode matches but still not reached destination station
            else{
              //changing the reached station
              queue->object->stnto=next_index;

              // enqueing the element at the end
              tail_queue->next= queue;
              queue->prev=tail_queue;
              tail_queue=tail_queue->next;
              // tail_queue->next=NULL;
              found_next=true;
              break;
            }
          }
          // traversal
          iter_in=iter_in->next;
        }

        // traversal
        if(found_next==true){
          break;
        }

        iter=iter->next;
      }

    // removing element from starting of the queue
    // dequeing

    queue=queue ->next;
    if(queue!=NULL){
      queue->prev=NULL;
    }
    tail_queue->next=NULL;
  }

  // Get the list of journeys as a listOfObjects<TrainInfoPerStation *>
  // for the source station and then we can print it out by invoking
  // printStationInfo that we had used in Lab 7.
  // printStationInfo is a private member function of the Planner class
  // It is declared in planner.h and implemented in planner.cpp
  if(final==NULL){
    cout<<"No direct journeys available"<<endl;
  }
  else{
    printStationInfo(final);
  }
  return;
}

#endif