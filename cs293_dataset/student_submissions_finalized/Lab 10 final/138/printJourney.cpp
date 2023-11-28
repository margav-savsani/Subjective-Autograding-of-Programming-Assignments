#ifndef PRINT_JOURNEY_CPP
#define PRINT_JOURNEY_CPP


#ifndef PLANNER_H
#include "planner.h"
#endif

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

using namespace std;

class trial {
public:
  int journeyCode; // same as train number
  int stnto; // stn index of the station train is going to
  int dayOfWeek; // Day of the week when the train travels
  int arrTime;  // Arrival time at station; -1 if train starts from here
  int depTime;  // Departure time from station; -1 if train ends here
  trial* next; // pointer to next trial
  int count;
  int gap;
  int go_to_index;
  int source_day;
  bool source_days[7];

public:

  //parametrized construuctor

  // changes the constructor
  //changes: days, next
  trial(int jCode,int stnto,int aTm,int dTm,int dayOfWeek,int go_to_index,int source_day,bool source_days[7],trial* next = NULL,int count = 0,int gap=-10)
  {
    // initialising
    journeyCode=jCode;
    this->stnto=stnto;
    arrTime=aTm;
    depTime=dTm;
    this->dayOfWeek=dayOfWeek;
    this->next=next;
    this->count=count;
    this->gap=gap;
    this->go_to_index=go_to_index;
    for(int i=0;i<7;i++){
      this->source_days[i]=source_days[i];
    }
    this->source_day=source_day;
  }

  //constructor
  trial();

  //destructor
  ~trial() {;}

};

// planner class has adjacency array each entry of which correspponds to a station
// each entry is a ptr of type Station Adjacency List and corresponds to a particular station
// each Station Adjacency list has a to and from linked list
// each entry of which is StationConnectionInfo which contains a stn index which tells the station number and train info per station which contains the journey code

void Planner::printPlanJourneys(string srcStnName, string destStnName, int maxStopOvers, int maxTransitTime)
{

  // insert your code here

  // Whenever you need to print a journey, construct a
  // listOfObjects<TrainInfoPerStation *> appropriately, and then
  // use printStationInfo that we had used in Lab 7.
  // printStationInfo is a private member function of
  // the Planner class. It is declared in planner.h and implemented in
  // planner.cpp

  //initializing all variables to NULL

  // this is the queue via which bfs is carried out
  listOfObjects<trial*> * queue=NULL;
  //tail_ptr
  listOfObjects<trial*> * tail_queue=NULL;


  // final queue to be printed out

  //CHANGED to trial * only
  listOfObjects <trial*> * final=NULL;
  // head of the final_queue for the purpose of insertion
  listOfObjects <trial*> * tail_final=NULL;

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
      // listOfObjects<TrainInfoPerStation*>* actual=stationInfo[source_index];

      // if the destination station is the next station, no need to insert in queue, directly insert in list to be printed
      if(des_index==dest_index){
        for (int i=0;i<7;i++){
            if(iter_in->object->daysOfWeek[i]==true){
              // one_way_to_reach->daysOfWeek[i]=true;
              //CHANGE NOW STORED BOOL ARRAYS TOO
              // NO NEED TO CHECK FOR CORRECT DAY OF ARRIVAL AS NOT IN QUEUE
              trial* one_way_to_reach=new trial(iter_in->object->journeyCode,des_index,iter_in->object->arrTime,iter_in->object->depTime,i,source_index,i,iter_in->object->daysOfWeek);

              // inserting element in the list to be returned
              listOfObjects <trial*>* one_way=new listOfObjects <trial*>(one_way_to_reach);

              //NO NEW ELEMENT IS CREATED, INSERT IN FINAL DIRECTLY
              //inserting the first element
              if(counter==0){
                final=one_way;
                tail_final=one_way;
                counter++;
              }

              //NO NEW ELEMENT IS CREATED INSERT IN FINAL DIRECTLY
              //inserting other elements
              else{
                tail_final->next= one_way;
                one_way->prev=tail_final;
                tail_final=tail_final->next;
              }
            }
          }
      }

      //not reached destination
      //to be inserted in queue
      else{
        for (int i=0;i<7;i++){
          if(iter_in->object->daysOfWeek[i]==true){
            // trial* to_insert=new trial(iter_in->object->journeyCode,des_index,actual->object->arrTime,actual->object->depTime,i,source_index,i,actual->object->daysOfWeek);
            trial* to_insert=new trial(iter_in->object->journeyCode,des_index,iter_in->object->arrTime,iter_in->object->depTime,i,source_index,i,iter_in->object->daysOfWeek);

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
        }
      }
      //traversal
      iter_in=iter_in->next;
    }
    //traversal
    iter=iter->next;
  }


 // looping through all elements of the queue
  while(queue!=NULL){

    // found_next is false at the start of search for every element of the queue
    // found_next=false;

    // have to look through the trains leaving from this index
    int go_to_index=queue->object->stnto;

    listOfObjects<StationConnectionInfo *>* iter=adjacency[go_to_index].toStations;
    int jrny_to_search=queue->object->journeyCode;

      // now have to loop through all trains going from that station to find the station with the same or different journey code
      //CHANGES MADE INSIDE
      // looping through the tostation list of that station
      while(iter!=NULL){

        int next_index=iter->object->adjacentStnIndex;

        listOfObjects<TrainInfoPerStation *> * iter_in=iter->object->trains;

        // looping through all trains with different journey codes going from that intermediate station to the next station
        while(iter_in!=NULL){


          // if journey code of next connecting train and train of queue matches
          // do not have to check for waiting time
          // do not have to increment count

          // NEW ELEMENT IS NOT CREATED WHEN REACHED DESTINATION
          //ELEMENT SIMPLE INSERTED IN FINAL
          //REMOVED FROM QUEUE
          if(iter_in->object->journeyCode == jrny_to_search){

            //if have reached destination
            //insert in final
            //remove from queue
            // AS NO LONGER IN QUEUE HENCE NO UPDATION IN DAYOFWEEK IS REQUIRED
            if(next_index==dest_index){

              //final ka first element just starts pointing to this element and it gets removed from queue
              //create a new element
              //and insert it in final

              listOfObjects<trial*>* to_put=new listOfObjects<trial*>(queue->object);

              if(counter==0){

                final=to_put;
                tail_final=to_put;

                counter++;
              }

              //inserting other elements
              //NEW ELEMENT NOT CREATED INSERTED
              else{
                tail_final->next=to_put;
                to_put->prev=tail_final;
                tail_final=tail_final->next;
              }
            }

            //else if have not reached destination
            //HAVE TO CREATE SEPERATE ELEMENT WITH JUST CHANGE IN JOURNEY CODE
            //ALSO CHANGE IN dayOfWeek

            else{
              // the element to be inserted at the end
              // inserting element in the list at the end
              listOfObjects <trial*>* at_the_end=new listOfObjects <trial*>(queue->object);
              at_the_end->object->stnto=next_index;
              //changing the reached station
              // enqueing the element at the end


              int j=0;
              for(;j<7;j++){
                bool match=true;
                for(int k=0;k<7;k++){
                  if(queue->object->source_days[j] != iter_in->object->daysOfWeek[(k+j)%7]){
                    match=false;
                    break;
                  }
                }
                if(match==true){
                  break;
                }
              }

              at_the_end->object->dayOfWeek = (at_the_end->object->source_day + j)%7;


              tail_queue->next= at_the_end;
              at_the_end->prev=tail_queue;
              tail_queue=tail_queue->next;
            }

          }

          //if journey code doesnt match
          // then have to check difference between departure of previous and arrival of this node
          // have to check for count
          // if conditions match then have to increment count
          // have to add an additional node
          else{

            //obtaining departure time and departure day for previous node
            listOfObjects<TrainInfoPerStation*>* actual=stationInfo[go_to_index];
            while(actual!=NULL){
              //found the node
              if(actual->object->journeyCode==queue->object->journeyCode){
                break;
              }
              else{
                actual=actual->next;
              }
            }

            int next_arr_time=actual->object->arrTime;
            // int dep_time = actual->object->depTime;

            int arr_day = queue->object->dayOfWeek;

            int count = queue->object->count;

            int dep_time = iter_in->object->depTime;

            //if have reached destination
            //insert in final
            //remove from queue
            if(next_index==dest_index){
              for (int i=0;i<7;i++){

                // iterating for all days of the week for iter_in
                //HAVE TO CHANGE THIS
                // THIS ASSUMES DAY NOT CHANGED
                /////////////////////////
                if( iter_in->object->daysOfWeek[i]==1 ){

                  // if the day matches
                  if(i==arr_day){

                    //CALCULATING THE TIME GAP
                    // int gap=dep_time-next_arr_time;
                    int gap;
                    //////////////////TIME MINUS

                    int main1=dep_time;
                    int to_sub1=next_arr_time;

                    if(main1%100>=to_sub1%100){
                      gap=main1-to_sub1;
                    }
                    else{
                      gap=main1-100+60-to_sub1;
                    }

                    //if it is a probable path checking for conditions
                    //if it satisfies all conditions
                    //to be added in the queue at the end
                    //but queue  element still remains till not checked for all the elements
                    // AS DIRECT FINAL ME INSERTION NO NEED TO CHANGE DAYOFWEEK
                    if(gap>=0 && gap<=maxTransitTime && count<maxStopOvers){

                      // the element to be inserted at the end
                      trial* to_be_inserted=new trial(iter_in->object->journeyCode,next_index,iter_in->object->arrTime,iter_in->object->depTime,i,go_to_index,i,iter_in->object->daysOfWeek,queue->object,count+1,gap);

                      // inserting element in the list at the end
                      listOfObjects <trial*>* at_the_end=new listOfObjects <trial*>(to_be_inserted);

                      //inserting an element at the final list

                      // inserting the first element
                      if(counter==0){
                        final=at_the_end;
                        tail_final=at_the_end;
                        counter++;
                      }

                      //inserting other elements in the final list
                      else{
                        tail_final->next= at_the_end;
                        at_the_end->prev=tail_final;
                        tail_final=tail_final->next;
                      }
                    }
                  }

                  // if the day doesnt match
                  else {

                    //checking for conditions on count and time
                    //if they satisfy
                    //insert at end of queue
                    int day_gap= (i-arr_day+7)%7 -1;
                    // int time_gap=(day_gap)*2400+2400-(next_arr_time-dep_time);
                    //////////////////TIME MINUS

                    int gap;
                    //////////////////TIME MINUS

                    int main2=next_arr_time;
                    int to_sub2=dep_time;

                    if(main2%100>=to_sub2%100){
                      gap=main2-to_sub2;
                    }
                    else{
                      gap=main2-100+60-to_sub2;
                    }

                    int more_gap;
                    //////////////////TIME MINUS

                    int main3=2400;
                    int to_sub3=gap;

                    if(main3%100>=to_sub3%100){
                      more_gap=main3-to_sub3;
                    }
                    else{
                      more_gap=main3-100+60-to_sub3;
                    }

                    int time_gap=(day_gap)*2400+more_gap;



                    if(time_gap<maxTransitTime && count<maxStopOvers){

                      // the element to be inserted at the end
                        // trial* to_be_inserted=new trial(iter_in->object->journeyCode,next_index,next_arr_time,dep_time,i,go_to_index,i,iter_in->object->daysOfWeek,queue->object,count+1,time_gap);
                        trial* to_be_inserted=new trial(iter_in->object->journeyCode,next_index,iter_in->object->arrTime,iter_in->object->depTime,i,go_to_index,i,iter_in->object->daysOfWeek,queue->object,count+1,time_gap);


                        // inserting element in the list at the end
                        listOfObjects <trial*>* at_the_end=new listOfObjects <trial*>(to_be_inserted);

                        // tail_queue->next = at_the_end;
                        // at_the_end->prev=tail_queue;
                        // tail_queue=tail_queue->next;
                        // inserting the first element
                      if(counter==0){
                        final=at_the_end;
                        tail_final=at_the_end;
                        counter++;
                      }

                      //inserting other elements in the final list
                      else{
                        tail_final->next= at_the_end;
                        at_the_end->prev=tail_final;
                        tail_final=tail_final->next;
                      }
                    }
                  }
                }
              }
            }

            //else if have not reached destination
            //SIMPLY INSERT IN QUEUE IF CONDITIONS MATCH
            else{

              for (int i=0;i<7;i++){

                // iterating for all days of the week for iter_in
                if( iter_in->object->daysOfWeek[i]==1 ){

                  // if the day matches
                  if(i==arr_day){
                    int gap;
                    //////////////////TIME MINUS

                    int main4=dep_time;
                    int to_sub4=next_arr_time;

                    if(main4%100>=to_sub4%100){
                      gap=main4-to_sub4;
                    }
                    else{
                      gap=main4-100+60-to_sub4;
                    }

                    //if it is a probable path checking for conditions
                    //if it satisfies all conditions
                    //to be added in the queue at the end
                    //but queue  element still remains till not checked for all the elements
                    if(gap>=0 && gap<maxTransitTime && count<maxStopOvers){

                        // the element to be inserted at the end of the queue
                        // gap time
                        trial* to_be_inserted=new trial(iter_in->object->journeyCode,next_index,iter_in->object->arrTime,iter_in->object->depTime,i,go_to_index,i,iter_in->object->daysOfWeek,queue->object,count+1,gap);

                        // inserting element in the list at the end
                        listOfObjects <trial*>* at_the_end=new listOfObjects <trial*>(to_be_inserted);
                        //inserting an element at the end
                        tail_queue->next = at_the_end;
                        at_the_end->prev=tail_queue;
                        tail_queue=tail_queue->next;
                    }
                  }

                  // if the day doesnt match
                  else {

                    //checking for conditions on count and time
                    //if they satisfy
                    //insert at end of queue
                    int day_gap= (i-arr_day+7)%7 -1;
                    // int time_gap=(day_gap)*2400+2400-next_arr_time+dep_time;

                    /////////TIME MINUS

                    int gap;
                    //////////////////TIME MINUS

                    int main5=next_arr_time;
                    int to_sub5=dep_time;

                    if(main5%100>=to_sub5%100){
                      gap=main5-to_sub5;
                    }
                    else{
                      gap=main5-100+60-to_sub5;
                    }

                    int more_gap;
                    //////////////////TIME MINUS

                    int main=2400;
                    int to_sub=gap;

                    if(main%100>=to_sub%100){
                      more_gap=main-to_sub;
                    }
                    else{
                      more_gap=main-100+60-to_sub;
                    }

                    int time_gap=(day_gap)*2400+more_gap;


                    if(time_gap<maxTransitTime && count<maxStopOvers){

                        // the element to be inserted at the end
                        trial* to_be_inserted=new trial(iter_in->object->journeyCode,next_index,iter_in->object->arrTime,iter_in->object->depTime,i,go_to_index,i,iter_in->object->daysOfWeek,queue->object,count+1,time_gap);

                        // inserting element in the list at the end
                        listOfObjects <trial*>* at_the_end=new listOfObjects <trial*>(to_be_inserted);
                        //inserting an element at the end
                        tail_queue->next = at_the_end;
                        at_the_end->prev=tail_queue;
                        tail_queue=tail_queue->next;

                    }
                  }
                }
              }
            }
          }

          //traversal
          iter_in=iter_in->next;
        }

        //traversal
        iter=iter->next;
      }

    //traversal
    queue=queue->next;

    //cutting of link from first element
    if(queue!=NULL){
      queue->prev=NULL;
    }

    //cutting of link from last element
    tail_queue->next=NULL;
  }

  if(final==NULL){
    cout<<"No journeys available"<<endl;
  }

  //print the journeys
  else{
        string days[7] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
        listOfObjects<trial *> *iter=final;
        trial *iter_in;
        cout << "ALL POSSIBLE JOURNEYS" << endl<<"*********************"<<endl;
        cout<<"All journeys are printed in bottom-up order"<<endl<<"Follow the directions of the upward pointing arrow"<<endl;
        int i;
        i=1;

        while (iter != nullptr)
        {
            iter_in = iter->object;

            cout << endl<<GREEN << "JOURNEY " << i << RESET << endl;
            while (iter_in != nullptr)
            {
                cout << RED << "Day: " << RESET;
                cout << days[iter_in->source_day] << " "<<"\t\t"<< "FROM : " << stnNameToIndex.getKeyAtIndex(iter_in->go_to_index)<<endl;
                // cout << "\t\t"<< "FROM : " << stnNameToIndex.getKeyAtIndex(iter_in->go_to_index);
                // cout << endl;
                cout << BLUE << "JourneyCode: " << iter_in->journeyCode << RESET << "\t";
                cout << GREEN << "Arrival: " << RESET;
                if (iter_in->arrTime != -1){
                    cout << iter_in->arrTime;
                }
                else{
                    cout << "Starts";
                }
                cout << GREEN << " Departure: " << RESET;
                if (iter_in->depTime != -1){
                    cout << iter_in->depTime<< endl;
                }
                else{
                    cout << "Ends"<< endl;
                }
                string key = stnNameToIndex.getKeyAtIndex(iter_in->go_to_index);
                if (iter_in->next != nullptr)
                {
                    string t="";
                    t=t+"Train needs to be changed at ";
                    string w="";
                    w = w+"\t Transit time is ";
                    cout << RED << t << key << endl<<RESET;
                    cout<<GREEN<<w << iter_in->gap <<endl<< RESET;
                    cout << "\t \t \t"<< "^" << endl<< "\t \t \t"<< "|" << endl;
                }
                iter_in = iter_in->next;
            }

            i=i+1;
            iter = iter->next;
        }

  }
  return;
}
#endif
