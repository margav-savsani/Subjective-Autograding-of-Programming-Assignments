#ifndef PRINT_JOURNEY_CPP
#define PRINT_JOURNEY_CPP

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

using namespace std;

void printStationInfomod(listOfObjects<TrainInfoPerStation *> *stnInfoList, listOfObjects<string> *station_names)
{
  listOfObjects<TrainInfoPerStation *> *currList, *expandedList;
  TrainInfoPerStation *currInfo;
  string days[7] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};

  currList = stnInfoList;
  expandedList = nullptr;
  int listLength = 0;
  while (currList != nullptr) {
    currInfo = currList->object;
    if (currInfo != nullptr) {
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

  currList = stnInfoList;
  listOfObjects<string> *currNames = station_names;
  while (currList != nullptr) {
    currInfo = currList->object;
    if (currInfo != nullptr) {
      cout << GREEN << "Day(s): " << RESET;
      for (int i=0; i<7; i++) {
	if (currInfo->daysOfWeek[i]) cout << days[i] << " ";
      }
      cout << endl;
      cout << BLUE << "JourneyCode: " << currInfo->journeyCode << RESET << "\t";
      cout << RED << "Arr: " << RESET;
      if (currInfo->arrTime == -1) {
	cout << "Starts";
      }
      else {
	cout << currInfo->arrTime;
      }
      cout << RED << " Dep: " << RESET;
      if (currInfo->depTime == -1) {
	cout << "Ends";
      }
      else {
	cout << currInfo->depTime;
      }
      cout << RED << "  Station Name: " << RESET << currNames->object;
      cout << endl;
    }
    currList = currList->next;
    currNames = currNames->next;
  }
  cout << endl;
}
  
void Planner::printPlanJourneys(string srcStnName, string destStnName, int maxStopOvers, int maxTransitTime)
{

  // insert your code here
  

  // Whenever you need to print a journey, construct a
  // listOfObjects<TrainInfoPerStation *> appropriately, and then
  // use printStationInfo that we had used in Lab 7.
  // printStationInfo is a private member function of
  // the Planner class. It is declared in planner.h and implemented in
  // planner.cpp
  static int reccLevel = -1;
  int index1 = stnNameToIndex.get(srcStnName)->value;   //finding the index of source station   
  int index2 = stnNameToIndex.get(destStnName)->value;    //finding the index of the destination station
  listOfObjects<TrainInfoPerStation *> *stn = stationInfo[index1];    //finding all the train schedules from source station
  static listOfObjects<TrainInfoPerStation *> *parent1 = nullptr;    //list to store the direct connecting trains
  static listOfObjects<string> *station_names = nullptr;    //stores the names of stations in the journey
  static TrainInfoPerStation* train = nullptr;    //train through which we get to a station
  static int j_num = 1;   //number of journeys found
  reccLevel++;
  if(reccLevel == 0)
  {
    listOfObjects<StationConnectionInfo *> *adj = adjacency[index1].toStations;
    station_names = new listOfObjects<string>(srcStnName);
    while(adj != nullptr)
    {
      listOfObjects<TrainInfoPerStation *> *curr_trains = stationInfo[stnNameToIndex.get(srcStnName)->value];   //trains of current station
      listOfObjects<TrainInfoPerStation *> *trains = adj->object->trains;   //trains of adjacent station
      while(trains != nullptr)    //iterating through trains
      {
        while(curr_trains->object->journeyCode != trains->object->journeyCode)    
        {
          curr_trains = curr_trains->next;
        }
        parent1 = new listOfObjects<TrainInfoPerStation *>(curr_trains->object);
        train = trains->object;
        station_names = new listOfObjects<string>(srcStnName);    
        printPlanJourneys(stnNameToIndex.getKeyAtIndex(adj->object->adjacentStnIndex),destStnName,maxStopOvers,maxTransitTime); 
        trains = trains->next;
        parent1 = nullptr;
        station_names = nullptr;
      }
      adj = adj->next;
    }
  }
  else
  {
    if(srcStnName == destStnName)   
    {
      if(parent1 == nullptr)
      {
        parent1 = new listOfObjects<TrainInfoPerStation *>(train);    
      }
      else
      {
        listOfObjects<TrainInfoPerStation *> *p = parent1;
        while(p->next != nullptr)
        {
          p = p->next;
        }
        p->next = new listOfObjects<TrainInfoPerStation *>(train);
        p->next->prev = p;
      }
      station_names->next = new listOfObjects<string>(srcStnName);
      station_names->next->prev = station_names;
      listOfObjects<TrainInfoPerStation *> *p_temp = parent1;
      while(p_temp->next != nullptr)
      {
        p_temp = p_temp->next;
      }
      bool possible = false;
      for(int i = 0; i<7; i++)
      {
        possible = possible || p_temp->object->daysOfWeek[i];
      }
      if(possible)    //checking if the journey is possible
      {
        cout<<"Journey Number: "<<j_num<<endl;
        printStationInfomod(parent1,station_names);
        j_num++;
      }
      parent1->next = nullptr;
      station_names->next = nullptr;
    }
    else
    {
      listOfObjects<StationConnectionInfo *> *adj = adjacency[index1].toStations;
      while(adj != nullptr)
      {
        int maxStopOvers_temp = maxStopOvers;
        listOfObjects<TrainInfoPerStation *> *trains = adj->object->trains;
        while(trains != nullptr)
        {
          if(trains->object->journeyCode == train->journeyCode)   //direct journey
          {
            if(parent1 == nullptr)
            {
              parent1 = new listOfObjects<TrainInfoPerStation *>(train);
            }
            else
            {
              listOfObjects<TrainInfoPerStation *> *p = parent1;
              while(p->next != nullptr)
              {
                p = p->next;
              }
              p->next = new listOfObjects<TrainInfoPerStation *>(train);
              p->next->prev = p;
            }
            if(station_names == nullptr)
            {
              station_names = new listOfObjects<string>(srcStnName);
            }
            else
            {
              listOfObjects<string> *sn = station_names;
              while(sn->next != nullptr)
              {
                sn = sn->next;
              }
              sn->next  = new listOfObjects<string>(srcStnName);
              sn->next->prev = sn;
            }
            if(adj->object->adjacentStnIndex == index2)   //if adjacent station is the destination
            {
              listOfObjects<TrainInfoPerStation *> *p = parent1;
              while(p->next != nullptr)
              {
                p = p->next;
              }
              p->next = new listOfObjects<TrainInfoPerStation *>(trains->object);   //adding train to path
              p->next->prev = p;
              if(station_names == nullptr)
              {
                station_names = new listOfObjects<string>(stnNameToIndex.getKeyAtIndex(adj->object->adjacentStnIndex));   //adding station name to station names list
              }
              else
              {
                listOfObjects<string> *sn = station_names;
                while(sn->next != nullptr)
                {
                  sn = sn->next;
                }
                sn->next  = new listOfObjects<string>(stnNameToIndex.getKeyAtIndex(adj->object->adjacentStnIndex));
                sn->next->prev = sn;
              }
              listOfObjects<TrainInfoPerStation *> *p_temp = parent1;
              while(p_temp->next != nullptr)
              {
                p_temp = p_temp->next;
              }
              bool possible = false;
              for(int i = 0; i<7; i++)
              {
                possible = possible || p_temp->object->daysOfWeek[i];
              }
              if(possible)    //checking is the given journey is possible
              {
                cout<<"Journey Number: "<<j_num<<endl;
                printStationInfomod(parent1,station_names);
                j_num++;
              }
              p = parent1;
              while(p->next->next != nullptr)
              {
                p = p->next;
              }
              p->next = nullptr;
              if(station_names->next == nullptr)
              {
                station_names = nullptr;
              }
              else
              {
                listOfObjects<string> *sn = station_names;
                while(sn->next->next != nullptr)
                {
                  sn = sn->next;
                }
                sn->next = nullptr;
              }
            }
            else
            {
              TrainInfoPerStation *train_temp = train;
              train = trains->object;
              printPlanJourneys(stnNameToIndex.getKeyAtIndex(adj->object->adjacentStnIndex),destStnName,maxStopOvers,maxTransitTime);   //calling the function reccursively for adjacent station
              train = train_temp;
            }
            if(parent1->next == nullptr)
            {
              parent1 = nullptr;
            }
            else
            {
              listOfObjects<TrainInfoPerStation *> *p = parent1;
              while(p->next->next != nullptr)
              {
                p = p->next;
              }
              p->next = nullptr;
            }
            if(station_names->next == nullptr)
            {
              station_names = nullptr;
            }
            else
            {
              listOfObjects<string> *sn = station_names;
              while(sn->next->next != nullptr)
              {
                sn = sn->next;
              }
              sn->next = nullptr;
            }
          }
          else    //not a direct journey
          {
            maxStopOvers_temp--;    //reducing the numbers of max stop overs
            if(maxStopOvers_temp >= 0)    //checking the max stop overs condition
            {
              listOfObjects<TrainInfoPerStation *> *curr_trains = stationInfo[stnNameToIndex.get(srcStnName)->value];
              while(trains->object->journeyCode != curr_trains->object->journeyCode)
              {
                curr_trains = curr_trains->next;
              }
              if(curr_trains->object->depTime - train->arrTime > 0 && curr_trains->object->depTime - train->arrTime <= maxTransitTime)    //checking transit time condition
              {
                TrainInfoPerStation train1 = *train;
                for(int i = 0; i<7; i++)
                {
                  if(!(train->daysOfWeek[i] && curr_trains->object->daysOfWeek[i]))
                  {
                    train->resetDayOfWeek(i);
                  }
                }
                if(parent1 == nullptr)
                {
                  parent1 = new listOfObjects<TrainInfoPerStation *>(train);    //adding the train to path
                }
                else
                {
                  listOfObjects<TrainInfoPerStation *> *p = parent1;
                  while(p->next != nullptr)
                  {
                    p = p->next;
                  }
                  p->next = new listOfObjects<TrainInfoPerStation *>(train);
                  p->next->prev = nullptr;
                }
                listOfObjects<string> *sn = station_names;
                while(sn->next != nullptr)
                {
                  sn = sn->next;
                }
                sn->next  = new listOfObjects<string>(srcStnName);
                sn->next->prev = sn;
                TrainInfoPerStation curr_train1 = *curr_trains->object;
                for(int i = 0; i<7; i++)
                {
                  if(!(train->daysOfWeek[i] && curr_trains->object->daysOfWeek[i]))
                  {
                    curr_trains->object->resetDayOfWeek(i);
                  }
                }
                if(parent1 == nullptr)
                {
                  parent1 = new listOfObjects<TrainInfoPerStation *>(curr_trains->object);    //adding the changed train to path
                }
                else
                {
                  listOfObjects<TrainInfoPerStation *> *p = parent1;
                  while(p->next != nullptr)
                  {
                    p = p->next;
                  }
                  p->next = new listOfObjects<TrainInfoPerStation *>(curr_trains->object);
                  p->next->prev = nullptr;
                }
                sn = station_names;
                while(sn->next != nullptr)
                {
                  sn = sn->next;
                }
                sn->next  = new listOfObjects<string>(srcStnName);
                sn->next->prev = sn;
                if(adj->object->adjacentStnIndex == index2)   //if adjacent station is destination
                {
                  TrainInfoPerStation* t = trains->object;
                  TrainInfoPerStation t_temp = *t;
                  int e = 0;
                  if(t->arrTime < curr_trains->object->depTime)
                  {
                    e = 1;
                  }
                  for(int i = 0; i<7; i++)
                  {
                    if(!(t->daysOfWeek[(i+e)%7] && train->daysOfWeek[i]))
                    {
                      t->resetDayOfWeek((i+e)%7);
                    }
                  }
                  if(parent1 == nullptr)
                  {
                    parent1 = new listOfObjects<TrainInfoPerStation *>(t);    //adding the train taken to get to adjacent station in the list
                  }
                  else
                  {
                    listOfObjects<TrainInfoPerStation *> *p = parent1;
                    while(p->next != nullptr)
                    {
                      p = p->next;
                    }
                    p->next = new listOfObjects<TrainInfoPerStation *>(t);
                    p->next->prev = p; 
                  }
                  listOfObjects<string> *sn = station_names;
                  while(sn->next != nullptr)
                  {
                    sn = sn->next;
                  }
                  sn->next  = new listOfObjects<string>(stnNameToIndex.getKeyAtIndex(adj->object->adjacentStnIndex));   //adding the name of destination in the station names lists
                  sn->next->prev = sn;
                  listOfObjects<TrainInfoPerStation *> *p_temp = parent1;
                  while(p_temp->next != nullptr)
                  {
                    p_temp = p_temp->next;
                  }
                  bool possible = false;
                  for(int i = 0; i<7; i++)
                  {
                    possible = possible || p_temp->object->daysOfWeek[i];
                  }
                  if(possible)
                  {
                    cout<<"Journey Number: "<<j_num<<endl;
                    printStationInfomod(parent1,station_names);
                    j_num++;
                  }
                  for(int i = 0; i<7; i++)
                  {
                    train->daysOfWeek[i] = train1.daysOfWeek[i];
                    t->daysOfWeek[i] = t_temp.daysOfWeek[i];
                    curr_trains->object->daysOfWeek[i] = curr_train1.daysOfWeek[i];
                  }
                  if(parent1->next == nullptr)
                  {
                    parent1 = nullptr;
                  }
                  else
                  {
                    listOfObjects<TrainInfoPerStation *> *p = parent1;
                    while(p->next->next != nullptr)
                    {
                      p = p->next;
                    }
                    p->next = nullptr;
                  }
                  sn = station_names;
                  while(sn->next->next != nullptr)
                  {
                    sn = sn->next;
                  }
                  sn->next = nullptr;
                }
                else    //if adjacent station is not destination
                { 
                  TrainInfoPerStation *train2 = train;
                  TrainInfoPerStation trains1 = *trains->object;
                  int e = 0;
                  if(trains->object->arrTime < curr_trains->object->depTime)
                  {
                    e = 1;
                  }
                  for(int i=0;i<7;i++)
                  {
                    if(!(train->daysOfWeek[i] && trains->object->daysOfWeek[(i+e)%7]))
                    {
                      trains->object->resetDayOfWeek((i+e)%7);
                    }
                  }
                  train = trains->object;
                  printPlanJourneys(stnNameToIndex.getKeyAtIndex(adj->object->adjacentStnIndex),destStnName,maxStopOvers_temp,maxTransitTime);
                  for(int i = 0; i<7; i++)
                  {
                    trains->object->daysOfWeek[i] = trains1.daysOfWeek[i];
                    train2->daysOfWeek[i] = train1.daysOfWeek[i];
                    curr_trains->object->daysOfWeek[i] = curr_train1.daysOfWeek[i];
                  }
                  train = train2;
                }
                for(int i = 0; i<2; i++)
                {
                  if(parent1->next == nullptr)
                  {
                    parent1 = nullptr;
                  }
                  else
                  {
                    listOfObjects<TrainInfoPerStation *> *p = parent1;
                    while(p->next->next != nullptr)
                    {
                      p = p->next;
                    }
                    p->next = nullptr;
                  }
                  sn = station_names;
                  while(sn->next->next != nullptr)
                  {
                    sn = sn->next;
                  }
                  sn->next = nullptr;     
                }
              }
            }
          }
          trains = trains->next; 
        }
        adj = adj->next;
      }
    }
  }
  reccLevel--;
  if(reccLevel == -1)
  {
    if(j_num == 1)    //if no journeys found
    {
      cout<<"No direct journeys available"<<endl;
    }
    train = nullptr;
    parent1 = nullptr;
    j_num = 1;
  }
  return;
}

#endif
