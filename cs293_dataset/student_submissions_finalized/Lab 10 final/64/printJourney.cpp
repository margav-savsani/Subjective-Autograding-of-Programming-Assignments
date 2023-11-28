#ifndef PRINT_JOURNEY_CPP
#define PRINT_JOURNEY_CPP

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

using namespace std;

void printStationInfomod(listOfObjects<TrainInfoPerStation *> *stnInfoList, listOfObjects<string> *namesStn)
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
  listOfObjects<string> *currNames = namesStn;
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
  //index of source station
  int srcIndex = stnNameToIndex.get(srcStnName)->value;   

  //index of the destination station   
  int destIndex = stnNameToIndex.get(destStnName)->value;    

  //trains from source station
  listOfObjects<TrainInfoPerStation *> *stn = stationInfo[srcIndex]; 

  //list to store the direct connecting trains   
  static listOfObjects<TrainInfoPerStation *> *path = nullptr;

  //stores the names of stations in the journey    
  static listOfObjects<string> *namesStn = nullptr;  

  //train through which we get to a station  
  static TrainInfoPerStation* train = nullptr; 

  //number of journeys found   
  static int jourNum = 1;   
  reccLevel++;
  if(reccLevel == 0)
  {
    listOfObjects<StationConnectionInfo *> *adj = adjacency[srcIndex].toStations;
    namesStn = new listOfObjects<string>(srcStnName);
    while(adj != nullptr)
    {
      listOfObjects<TrainInfoPerStation *> *curr_trains = stationInfo[stnNameToIndex.get(srcStnName)->value];
      listOfObjects<TrainInfoPerStation *> *trains = adj->object->trains;
      while(trains != nullptr)
      {
        while(curr_trains->object->journeyCode != trains->object->journeyCode)    
        {
          curr_trains = curr_trains->next;
        }
        path = new listOfObjects<TrainInfoPerStation *>(curr_trains->object);
        train = trains->object;
        namesStn = new listOfObjects<string>(srcStnName);    
        printPlanJourneys(stnNameToIndex.getKeyAtIndex(adj->object->adjacentStnIndex),destStnName,maxStopOvers,maxTransitTime); 
        trains = trains->next;
        path = nullptr;
        namesStn = nullptr;
      }
      adj = adj->next;
    }
  }
  else
  {
    if(srcStnName == destStnName)   
    {
      if(path == nullptr)
      {
        path = new listOfObjects<TrainInfoPerStation *>(train);    
      }
      else
      {
        listOfObjects<TrainInfoPerStation *> *p = path;
        while(p->next != nullptr)
        {
          p = p->next;
        }
        p->next = new listOfObjects<TrainInfoPerStation *>(train);
        p->next->prev = p;
      }
      namesStn->next = new listOfObjects<string>(srcStnName);
      namesStn->next->prev = namesStn;
      listOfObjects<TrainInfoPerStation *> *tempPath = path;
      while(tempPath->next != nullptr)
      {
        tempPath = tempPath->next;
      }
      bool mybool = false;
      for(int i = 0; i<7; i++)
      {
        mybool = mybool || tempPath->object->daysOfWeek[i];
      }
      if(mybool)
      {
        cout<<"Journey Number: "<<jourNum<<endl;
        printStationInfomod(path,namesStn);
        jourNum++;
      }
      path->next = nullptr;
      namesStn->next = nullptr;
    }
    else
    {
      listOfObjects<StationConnectionInfo *> *adj = adjacency[srcIndex].toStations;
      while(adj != nullptr)
      {
        int maxStopOvers_temp = maxStopOvers;
        listOfObjects<TrainInfoPerStation *> *trains = adj->object->trains;
        while(trains != nullptr)
        {
          if(trains->object->journeyCode == train->journeyCode)
          {
            if(path == nullptr)
            {
              path = new listOfObjects<TrainInfoPerStation *>(train);
            }
            else
            {
              listOfObjects<TrainInfoPerStation *> *p = path;
              while(p->next != nullptr)
              {
                p = p->next;
              }
              p->next = new listOfObjects<TrainInfoPerStation *>(train);
              p->next->prev = p;
            }
            if(namesStn == nullptr)
            {
              namesStn = new listOfObjects<string>(srcStnName);
            }
            else
            {
              listOfObjects<string> *sn = namesStn;
              while(sn->next != nullptr)
              {
                sn = sn->next;
              }
              sn->next  = new listOfObjects<string>(srcStnName);
              sn->next->prev = sn;
            }
            if(adj->object->adjacentStnIndex == destIndex)
            {
              listOfObjects<TrainInfoPerStation *> *p = path;
              while(p->next != nullptr)
              {
                p = p->next;
              }
              p->next = new listOfObjects<TrainInfoPerStation *>(trains->object); 
              p->next->prev = p;
              if(namesStn == nullptr)
              {
                namesStn = new listOfObjects<string>(stnNameToIndex.getKeyAtIndex(adj->object->adjacentStnIndex)); 
              }
              else
              {
                listOfObjects<string> *sn = namesStn;
                while(sn->next != nullptr)
                {
                  sn = sn->next;
                }
                sn->next  = new listOfObjects<string>(stnNameToIndex.getKeyAtIndex(adj->object->adjacentStnIndex));
                sn->next->prev = sn;
              }
              listOfObjects<TrainInfoPerStation *> *tempPath = path;
              while(tempPath->next != nullptr)
              {
                tempPath = tempPath->next;
              }
              bool mybool = false;
              for(int i = 0; i<7; i++)
              {
                mybool = mybool || tempPath->object->daysOfWeek[i];
              }
              if(mybool)
              {
                cout<<"Journey Number: "<<jourNum<<endl;
                printStationInfomod(path,namesStn);
                jourNum++;
              }
              p = path;
              while(p->next->next != nullptr)
              {
                p = p->next;
              }
              p->next = nullptr;
              if(namesStn->next == nullptr)
              {
                namesStn = nullptr;
              }
              else
              {
                listOfObjects<string> *sn = namesStn;
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
              printPlanJourneys(stnNameToIndex.getKeyAtIndex(adj->object->adjacentStnIndex),destStnName,maxStopOvers,maxTransitTime);
              train = train_temp;
            }
            if(path->next == nullptr)
            {
              path = nullptr;
            }
            else
            {
              listOfObjects<TrainInfoPerStation *> *p = path;
              while(p->next->next != nullptr)
              {
                p = p->next;
              }
              p->next = nullptr;
            }
            if(namesStn->next == nullptr)
            {
              namesStn = nullptr;
            }
            else
            {
              listOfObjects<string> *sn = namesStn;
              while(sn->next->next != nullptr)
              {
                sn = sn->next;
              }
              sn->next = nullptr;
            }
          }
          else 
          {
            maxStopOvers_temp--; 
            if(maxStopOvers_temp >= 0) 
            {
              listOfObjects<TrainInfoPerStation *> *curr_trains = stationInfo[stnNameToIndex.get(srcStnName)->value];
              while(trains->object->journeyCode != curr_trains->object->journeyCode)
              {
                curr_trains = curr_trains->next;
              }
              if(curr_trains->object->depTime - train->arrTime > 0 && curr_trains->object->depTime - train->arrTime <= maxTransitTime) 
              {
                TrainInfoPerStation train1 = *train;
                for(int i = 0; i<7; i++)
                {
                  if(!(train->daysOfWeek[i] && curr_trains->object->daysOfWeek[i]))
                  {
                    train->resetDayOfWeek(i);
                  }
                }
                if(path == nullptr)
                {
                  path = new listOfObjects<TrainInfoPerStation *>(train); 
                }
                else
                {
                  listOfObjects<TrainInfoPerStation *> *p = path;
                  while(p->next != nullptr)
                  {
                    p = p->next;
                  }
                  p->next = new listOfObjects<TrainInfoPerStation *>(train);
                  p->next->prev = nullptr;
                }
                listOfObjects<string> *sn = namesStn;
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
                if(path == nullptr)
                {
                  path = new listOfObjects<TrainInfoPerStation *>(curr_trains->object);
                }
                else
                {
                  listOfObjects<TrainInfoPerStation *> *p = path;
                  while(p->next != nullptr)
                  {
                    p = p->next;
                  }
                  p->next = new listOfObjects<TrainInfoPerStation *>(curr_trains->object);
                  p->next->prev = nullptr;
                }
                sn = namesStn;
                while(sn->next != nullptr)
                {
                  sn = sn->next;
                }
                sn->next  = new listOfObjects<string>(srcStnName);
                sn->next->prev = sn;
                if(adj->object->adjacentStnIndex == destIndex) 
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
                  if(path == nullptr)
                  {
                    path = new listOfObjects<TrainInfoPerStation *>(t);
                  }
                  else
                  {
                    listOfObjects<TrainInfoPerStation *> *p = path;
                    while(p->next != nullptr)
                    {
                      p = p->next;
                    }
                    p->next = new listOfObjects<TrainInfoPerStation *>(t);
                    p->next->prev = p; 
                  }
                  listOfObjects<string> *sn = namesStn;
                  while(sn->next != nullptr)
                  {
                    sn = sn->next;
                  }
                  sn->next  = new listOfObjects<string>(stnNameToIndex.getKeyAtIndex(adj->object->adjacentStnIndex)); 
                  sn->next->prev = sn;
                  listOfObjects<TrainInfoPerStation *> *tempPath = path;
                  while(tempPath->next != nullptr)
                  {
                    tempPath = tempPath->next;
                  }
                  bool mybool = false;
                  for(int i = 0; i<7; i++)
                  {
                    mybool = mybool || tempPath->object->daysOfWeek[i];
                  }
                  if(mybool)
                  {
                    cout<<"Journey Number: "<<jourNum<<endl;
                    printStationInfomod(path,namesStn);
                    jourNum++;
                  }
                  for(int i = 0; i<7; i++)
                  {
                    train->daysOfWeek[i] = train1.daysOfWeek[i];
                    t->daysOfWeek[i] = t_temp.daysOfWeek[i];
                    curr_trains->object->daysOfWeek[i] = curr_train1.daysOfWeek[i];
                  }
                  if(path->next == nullptr)
                  {
                    path = nullptr;
                  }
                  else
                  {
                    listOfObjects<TrainInfoPerStation *> *p = path;
                    while(p->next->next != nullptr)
                    {
                      p = p->next;
                    }
                    p->next = nullptr;
                  }
                  sn = namesStn;
                  while(sn->next->next != nullptr)
                  {
                    sn = sn->next;
                  }
                  sn->next = nullptr;
                }
                else 
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
                  if(path->next == nullptr)
                  {
                    path = nullptr;
                  }
                  else
                  {
                    listOfObjects<TrainInfoPerStation *> *p = path;
                    while(p->next->next != nullptr)
                    {
                      p = p->next;
                    }
                    p->next = nullptr;
                  }
                  sn = namesStn;
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
    if(jourNum == 1)
    {
      cout<<"No direct journeys available"<<endl;
    }
    train = nullptr;
    path = nullptr;
    jourNum = 1;
  }
  return;
}

#endif
