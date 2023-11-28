#ifndef PRINT_JOURNEY_CPP
#define PRINT_JOURNEY_CPP


#ifndef PLANNER_H
#include "planner.h"
#endif

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#include "queue"
using namespace std;

//this class has is a single journey holds all the trains of that journey route 
class Tracker { 
    public : 
      listOfObjects<int>* stn_index ; 
      int stopovers ; 
      listOfObjects<TrainInfoPerStation*>* trains = nullptr ; 
      int arrTime , day ;
      int transitTime = 0  ;
      Tracker() { stopovers = 0 ; } ;
      Tracker(listOfObjects<int>* stn_index , int stopovers ,listOfObjects<TrainInfoPerStation*>* trains , int day , int arrTime , int transitTime ) { 
          this->stn_index = stn_index ; 
          this->trains = trains ; 
          this->stopovers = stopovers ;
          this->arrTime = arrTime ; 
          this->day = day ;
          this->transitTime = transitTime ;
      } 
}; 

//check wheter the code newtrain is satisfying the condition
int isValid( Tracker* curr , TrainInfoPerStation* newTrain , int maxTransitTime ) { 
        //check wheter the code newtrain is satisfying the condition
         if ( curr->arrTime == -1 ) return 0 ; 
         int day ; 
         for ( int i = 0 ; i < 7 ; i++ ) if (newTrain->daysOfWeek[i]) day = i ; 
         if ( newTrain->arrTime > newTrain->depTime ) day += 1 ; 
         int diff = (day - curr->day)*2400 + (newTrain->depTime - curr->arrTime) ;
         if ( diff%100 > 59)  diff =   (diff/100)*100 + 100   + (diff%100)%60 ; //time conversion
         if ( diff >= 0 && diff <= maxTransitTime )  return diff ;
         return 0 ;
}

int findDay(TrainInfoPerStation* train) {  //find the day of the given traininfo station ( assumed only one day )
    for ( int i = 0 ; i < 7 ; i ++ ) 
      if ( train->daysOfWeek[i] ) return i ;
}

Tracker* add( Tracker* tracker , TrainInfoPerStation* newTrain  , int stn_index , int maxTransitTime, int day , int arrTime , int transitTime ) {  
          //This funcctions add the newTrain to tracker joureny path 
          if (tracker->trains != nullptr) { //add the first train to tracker 
            TrainInfoPerStation* lastTrain = tracker->trains->object ;             
            if ( lastTrain->journeyCode == newTrain->journeyCode &&  findDay(newTrain) == findDay(lastTrain) ) {
                   return new Tracker(tracker->stn_index,tracker->stopovers,tracker->trains,day,arrTime ,tracker->transitTime ) ; 
            }
          } 
           listOfObjects<TrainInfoPerStation*>* newTrackerTrains = new listOfObjects<TrainInfoPerStation*>(newTrain) ; 
           listOfObjects<int>* newStnIndex = new listOfObjects<int>(stn_index);
           newTrackerTrains->next = tracker->trains ;
           newStnIndex->next = tracker->stn_index ;
           //create a newTracker with updated data 
           Tracker* newTracker = new Tracker(newStnIndex,tracker->stopovers+1,newTrackerTrains,day,arrTime, max(tracker->transitTime,transitTime) ) ; 
           return newTracker ;          
}

void Planner::printPlanJourneys(string srcStnName, string destStnName, int maxStopOvers, int maxTransitTime){

   listOfObjects<Tracker *>*  journeys =  nullptr ; //MATCH Journeys 
   int source_index = stnNameToIndex.get(srcStnName)->value ;  
   int dest_index = stnNameToIndex.get(destStnName)->value ;

   queue<Tracker*> Queue ;  // the first int is for station index and second int is for journey code 
   Queue.push(new Tracker(new listOfObjects<int>(source_index),0,nullptr,-1,-1,0));

   while( !Queue.empty() ) { //if queue has some remaining stations to visit 
        Tracker* curr = Queue.front(); //get the breadth first station , journey to visit 
        Queue.pop();
        int stn_index = curr->stn_index->object ; //station index 
        listOfObjects<StationConnectionInfo *>  *tostations = (adjacency[stn_index]).toStations ; 
        while ( tostations != nullptr ) {
          //loop for stations from the given station
          listOfObjects<TrainInfoPerStation *>* train = tostations->object->trains ; 
          //get the from station info 
          listOfObjects<StationConnectionInfo *>* fromStations =  (adjacency[tostations->object->adjacentStnIndex]).fromStations ;
          while ( fromStations->object->adjacentStnIndex !=  stn_index ) fromStations = fromStations->next ;

          while ( train != nullptr ) {
               //loop for all trains leaving the station 
               //find the corresending train data in the arrival station 
               listOfObjects<TrainInfoPerStation *>* fromTrain = fromStations->object->trains ; 
               while ( fromTrain->object->journeyCode !=  train->object->journeyCode) fromTrain = fromTrain->next ;

               int dayCount = 0 ; 
               if ( train->object->depTime > fromTrain->object->arrTime ) dayCount = 1 ; 
               for (int i=0; i < 7; i++) {
	               if (train->object->daysOfWeek[i]) {
                    //loop for each day of the train 
                    TrainInfoPerStation *oldTrain = train->object ;  
               	    TrainInfoPerStation *newTrain = new TrainInfoPerStation(oldTrain->journeyCode,oldTrain->stopSeq,
                                                                            oldTrain->arrTime,oldTrain->depTime); 
                    newTrain->setDayOfWeek(i);
                    //condition for the journey
                    if ( curr->trains == nullptr || ( curr->stopovers < maxStopOvers  && isValid(curr,newTrain,maxTransitTime)) ) {
                        int transitTime = isValid(curr,newTrain,maxTransitTime) ;
                        //new Tracker is created with added train 
                        Tracker* tracker = add(curr,newTrain,tostations->object->adjacentStnIndex,maxTransitTime,
                                                    i+dayCount ,fromTrain->object->arrTime , transitTime);

                        if ( tracker != nullptr) { 
                         //if destination is reached 
                         if ( tostations->object->adjacentStnIndex == dest_index ) {
                          //add to the journeys
                          if ( journeys == nullptr ) {
                              journeys = new listOfObjects<Tracker *>(tracker) ;
                          }
                          else  {  
                              listOfObjects<Tracker *>*  last_journey = journeys ; 
                              while ( last_journey->next != nullptr) last_journey = last_journey->next ;
                              last_journey->next = new listOfObjects<Tracker *>(tracker) ;
                           }        
                      }
                      else {  //if in intermediate path
                         Queue.push( tracker );   
                       }
                      }
                    }
                  }
               } 
               train = train->next ;
            }
            tostations = tostations->next ; 
        }
    }
   
   //Printing function 
   listOfObjects<Tracker *>* tracker = journeys ; 
   cout<<endl ;
   while ( tracker != nullptr )  { 
      cout<<RED<<"Journey ::"<<RESET<<"\t" ;
      cout<<BLUE<<"Maximum Transit time: "<<RESET<<tracker->object->transitTime<<endl<<endl ;
      string days[7] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};

      listOfObjects<TrainInfoPerStation *>* x = tracker->object->trains; 
      listOfObjects<int>* y = tracker->object->stn_index; 

      listOfObjects<TrainInfoPerStation *>* trains = new listOfObjects<TrainInfoPerStation *>(x->object);
      listOfObjects<int>* stn = new listOfObjects<int>(y->object); 

      //reverse the list
      x = x->next ;
      while ( x != nullptr ) {
           listOfObjects<TrainInfoPerStation *>* temp = trains ;
           trains = new listOfObjects<TrainInfoPerStation *>(x->object);
           trains->next = temp ; 
           x = x->next ; 
      }

      y = y->next ;
      while ( y != nullptr ) {
           listOfObjects<int>* temp = stn ;
           stn = new listOfObjects<int>(y->object);
           stn->next = temp ; 
           y = y->next ; 
      }
        
      while ( trains != nullptr )  { 
         cout<<GREEN<<"Station :: "<<RESET<<stnNameToIndex.getKeyAtIndex(stn->object)<<endl ;
         cout << GREEN << "Day: " << RESET ; 
         cout<<days[findDay(trains->object)]<<"\t" ; 
         cout << BLUE << "JourneyCode: " << trains->object->journeyCode << RESET << "\t";
         
         cout << RED << " Arr: " << RESET; 
         if ( trains->object->arrTime != -1 ) cout<<trains->object->arrTime; 
         else cout<<"Starts" ; 

         cout << RED << " Dep: " << RESET; 
         if ( trains->object->depTime != -1 ) cout<<trains->object->depTime; 
         else cout<<"Ends" ; 
         cout<<endl<<endl ; 
         //printStationInfo( new listOfObjects<TrainInfoPerStation*>(trains->object));
         trains = trains->next ; 
         stn = stn->next ; 
      } 
      tracker = tracker->next ; 
   }
   cout << "This function is to be implemented by you." << endl;
   return;
}

#endif

