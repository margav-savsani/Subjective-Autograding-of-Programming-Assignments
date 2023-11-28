#ifndef PRINT_JOURNEY_CPP
#define PRINT_JOURNEY_CPP

#ifndef PLANNER_H
#include "planner.h"
#endif

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

using namespace std;

/*
Assumptions made : 
1. Time spent at the station on the same train is not considered as transit time
2. arrival and departure time are for "current station" in the adjacency list
3. The arrival day is the soonest available choice after the departure from the source
4. The Transit Time can exceed one day, in which case, departures from other days of the week become available. 
5. Basically, the split train departure time can be "trusted" but the arrival time cannot
6. Two connecting trains can be separated by atmost a week, for example Kal 2200 and nag 2100 on the same day is allowed since this implies that the train at nagpur leaves one week after arrival at nagpur.
7. The journey plot has latest tickets above and oldest tickets below
*/

/* Inside print
To get arrival time actual -> 
day = time / 2400
time = time % 2400

To get departure time -> 
deptime = time % 10000
transit = time / 10000
*/

void print(listOfObjects<TrainInfoPerStation*>* currList)
{
  string days[7] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};
  while (currList != nullptr) {
    TrainInfoPerStation* currInfo = currList->object;
    if (currInfo != nullptr) if (currInfo->journeyCode != 0)
    {
      cout << GREEN << "Arrival Day: " << RESET;
      cout << days[currInfo->arrTime/2400] << " ";
      cout << GREEN << "Departure Day: " << RESET;
      for (int i = 0; i < 7; i++) {
        if (currInfo->daysOfWeek[i])
          cout << days[i] << " ";
      }
      cout << endl;
      cout << BLUE << "JourneyCode: " << currInfo->journeyCode << RESET << "\t";
      cout << RED << "Arr: " << RESET;
      if ((currInfo->arrTime)%2400 == -1){cout << "Starts";}
      else{cout << (currInfo->arrTime)%2400;}
      cout << RED << " Dep: " << RESET;
      if ((currInfo->depTime)%(10000) == 9999){cout << "Ends";}
      else{cout << (currInfo->depTime)%10000;}
      cout << endl;
      if (currInfo->depTime/10000 != 0)
        cout << GREEN <<"Transit : " << currInfo->depTime/10000 << RESET << endl;
    }
    currList = currList->next;
  }
  cout << endl;
  cout << BLUE << "=====================================================================" << RESET << endl;
}

struct Element
{
  listOfObjects<TrainInfoPerStation*> *path;
  int stnidx;
  int stops;
  TrainInfoPerStation* last; // Stores the last element on the current path. 
};

bool check (TrainInfoPerStation* t, Element e, int maxtransit, int maxstop, int arrtime, int& transit) {

  TrainInfoPerStation* last = e.last; 
  // maxtransit is in hours, so is multiplied by 100 when dealing with in the logic.
  // first getting the departure time of the train.
  // t->daysOfWeek[i] is a one-hot vector, so is true only once in the for loop.

  int deptime = 0;
  for (int i = 0; i < 7; i++) {
    if (t->daysOfWeek[i]) deptime = 2400*i + t->depTime;
  }
  
  // if the arrival at the station is after the departure, journey codes do not matter !
  

  if (last->journeyCode != t->journeyCode) {
    // checking for appropriate arrival time < departure time.
    // modulus updated because negative numbers cause issue
    if (((deptime - arrtime)%(2400*7)+2400*7)%(2400*7) < maxtransit*100) {
      transit = ((deptime - arrtime)%(2400*7)+2400*7)%(2400*7);
      return true;
    } 
    else {return false;}
  }
  else {
    transit = 0;
    return true;
  }
}

bool operator==(TrainInfoPerStation a, TrainInfoPerStation b) {
  if (a.arrTime == b.arrTime && a.daysOfWeek == b.daysOfWeek && a.depTime == b.depTime && a.journeyCode == b.journeyCode)
    return true;
  else 
    return false;
} 

void Planner::printPlanJourneys(string srcStnName, string destStnName, int maxStopOvers, int maxTransitTime)
{
  // Get the list of journeys as a listOfObjects<TrainInfoPerStation *>
  // for the source station and then we can print it out by invoking
  // printStationInfo that we had used in Lab 7.
  // printStationInfo is a private member function of the Planner class
  // It is declared in planner.h and implemented in planner.cpp

  int src = stnNameToIndex.get(srcStnName)->value;
  int dest = stnNameToIndex.get(destStnName)->value;
  StationAdjacencyList* l = new StationAdjacencyList(adjacency[src]);
  listOfObjects<StationConnectionInfo *> *to_stn = l->toStations;

  // Initialising Result : subsequent memory must be allocated on the heap. and then the first dummy element to be removed at the end 
  // from all the linked lists containied inside this mega result
  listOfObjects<listOfObjects<TrainInfoPerStation*>*>*Result = 
  new listOfObjects<listOfObjects<TrainInfoPerStation*>*>(new listOfObjects<TrainInfoPerStation*>(new TrainInfoPerStation(TrainInfoPerStation(0, 0, 0, 0))));

  // Now, initialising the queue : subsequent memory must be allocated on the heap. and then the first dummy element to be removed at the end 
  listOfObjects<Element*> *Q = new listOfObjects<Element*>(new Element(Element{new listOfObjects<TrainInfoPerStation*>(new TrainInfoPerStation(0, 0, 0, 0)), 0, 0, new TrainInfoPerStation(0, 0, 0, 0)}));

  // start elements : 
  listOfObjects<TrainInfoPerStation*> *start = new listOfObjects<TrainInfoPerStation*>(new TrainInfoPerStation(0, 0, 0, 0));
  listOfObjects<int*> *stations_start = new listOfObjects<int*>(new int(0));
  listOfObjects<TrainInfoPerStation*> *startcpy = start;
  listOfObjects<int*> *stnstcpy = stations_start;

  // making first as dummy object, and finally shifting head to 2nd element : Start initialised !
  while (to_stn != nullptr) {

    listOfObjects<TrainInfoPerStation*> *train = to_stn->object->trains;
    
    while (train != nullptr) {
      TrainInfoPerStation* journey = train->object; 
      start->next = new listOfObjects<TrainInfoPerStation*>(journey); start = start->next;
      stations_start->next = new listOfObjects<int*>(new int(to_stn->object->adjacentStnIndex)); stations_start = stations_start->next;
      train = train->next;
    }
    to_stn = to_stn->next;
  }
  start = startcpy->next;
  stations_start = stnstcpy->next;

  // Now, initialising the queue
  listOfObjects<Element*> *Qcpy = Q;
  listOfObjects<TrainInfoPerStation*> *startcpy1 = start;
  listOfObjects<int*>* stncpy = stations_start;
  // startcpy = current listOfObjects TrainInfoPerStation* element
  while (startcpy1 != nullptr) {
    // iterating over all days of the week
    for (int i = 0; i < 7; i++){
      TrainInfoPerStation* newobj = new TrainInfoPerStation(*startcpy1->object); // so that the two are NOT linked.
      if (startcpy1->object->daysOfWeek[i]) {
        for (int j = 0; j < 7; j++) newobj->daysOfWeek[j] = 0;
        newobj->daysOfWeek[i] = 1;
        listOfObjects<TrainInfoPerStation*>* path = new listOfObjects<TrainInfoPerStation*> (newobj);
        Element push{path, *stncpy->object, 0, newobj};
        Q->next = new listOfObjects<Element*>(new Element(push)); Q = Q->next;
      }
    }
    startcpy1 = startcpy1->next;
    stncpy = stncpy->next;
  }
  // Q is already at the end of the linked list ! -- dummy object burned successfully
  Qcpy = Qcpy->next;
  // Qcpy = head, Q = tail.
  // Queue initialised with singleton path leaders which are already split using days of week.

  // Making a copy of Result in order to obtain its head pointer
  listOfObjects<listOfObjects<TrainInfoPerStation*>*>* resultcpy = Result;

  while (Qcpy != nullptr) {
    Element currelem = *Qcpy->object; Qcpy = Qcpy->next;
    TrainInfoPerStation* last = currelem.last;

    if (currelem.stnidx == dest) {
      // Destination found.
      // Result = list of paths : so put this path in and shift the pointer ahead.
      Result->object = currelem.path; Result->next =   new listOfObjects<listOfObjects<TrainInfoPerStation*>*>(new listOfObjects<TrainInfoPerStation*>(new TrainInfoPerStation(TrainInfoPerStation(0, 0, 0, 0))));
      Result = Result->next;
    }

    else {
      StationAdjacencyList* l = new StationAdjacencyList(adjacency[currelem.stnidx]);
      listOfObjects<StationConnectionInfo *> *to_stn = l->toStations;

      while (to_stn != nullptr) {
        
        listOfObjects<TrainInfoPerStation*> *train = to_stn->object->trains;
        
        while (train != nullptr) {
          TrainInfoPerStation* journey = train->object; 
          //start->next = new listOfObjects<TrainInfoPerStation*>(journey); start = start->next;
          //stations_start->next = new listOfObjects<int*>(new int(to_stn->object->adjacentStnIndex)); stations_start = stations_start->next;
          
          // getting departure of last. 
          int dep = 0;
          for (int i = 0; i < 7; i++) {
            if (currelem.last->daysOfWeek[i]) {
              dep = 2400 * i + currelem.last->depTime;
              break;
            }
          }
          // iterating over all days. -- first instance of the arrival after the departure of the last train is assumed.
          int arr = -2;
          for (int i = dep/2400; true; i = (i+1)%7) {
            if (train->object->daysOfWeek[i]) {
              if (i == dep/2400) {
                if (dep/2400 < train->object->arrTime) {
                  arr = 2400 * i + train->object->arrTime;
                  break;
                }
              }
              else {
                arr = 2400 * i + train->object->arrTime;
                break;
              }
            } 
          }
          // now that we have the actual "arrival" day and time, judging the transit is easy
          // departure can again happen anytime, that is why the days are maintained.
          for (int i = 0; i < 7; i++) {
            // allocating new object to make sure no linking of pointers
            TrainInfoPerStation* tcpy = new TrainInfoPerStation(*train->object);
            if (tcpy->daysOfWeek[i]) {
              for (int j = 0; j < 7; j++) tcpy->daysOfWeek[j] = 0;
              tcpy->daysOfWeek[i] = 1;
              // modified arrival time, 2400 * i + time format -- will be useful in printing
              tcpy->arrTime = arr;
              
              // Element to be pushed into the queue if check is true
              // A copy having "one-hot" encoded vector created.
              int transit;
              if (check(tcpy, currelem, maxTransitTime, maxStopOvers, arr, transit)) {
                tcpy->depTime = 10000 * transit + tcpy->depTime;
                // add tcpy to the path, to.stnidx to the element, increase stops if required, display transit time (add to element)
                // Updating the path first.
                Element newelem;
                listOfObjects<TrainInfoPerStation*>* newpath = new listOfObjects<TrainInfoPerStation*>(*currelem.path);
                listOfObjects<TrainInfoPerStation*>* newhead = newpath; // header of the path
                while (newpath->next != nullptr) {
                  newpath = newpath->next;
                }
                newpath->next = new listOfObjects<TrainInfoPerStation*>(tcpy);

                if (last->journeyCode != tcpy->journeyCode) {
                  newelem = Element{newhead, to_stn->object->adjacentStnIndex, currelem.stops+1, new TrainInfoPerStation(*tcpy)};
                }
                else {
                  newelem = Element{newhead, to_stn->object->adjacentStnIndex, currelem.stops, new TrainInfoPerStation(*tcpy)};
                }
                // Element pushed into the queue
                Q->next = new listOfObjects<Element*>(new Element(newelem)); Q = Q->next;
              }
            }
          }
          train = train->next;
        }
        to_stn = to_stn->next;
      }
    }
  }
  // Burning the first element (dummy)
  Result = resultcpy->next;
  // Now, printing all journeys using the "inbuit print function" after iterating through all "paths"
  if (Result != nullptr){
    print(Result->object);
    while (Result->next != nullptr) {
      print(Result->next->object);
      Result = Result->next;
    }
  }
  else {
    cout << RED << "NO JOURNEYS FOUND" << RESET << endl;
  }
}

#endif
