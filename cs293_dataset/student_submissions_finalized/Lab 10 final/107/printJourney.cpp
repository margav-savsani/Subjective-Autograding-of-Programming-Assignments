#ifndef PRINT_JOURNEY_CPP
#define PRINT_JOURNEY_CPP

#ifndef PLANNER_H
#include "planner.h"
#endif

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

using namespace std;


// The class for entries in Queue
class maxStopOverAndStationConnectionInfo
{
public:
  StationConnectionInfo* SCIobject; // Current train
  listOfObjects<StationConnectionInfo*>* stops; // List of trains where we first started journey in it
  int stopOverUntilNow; // Stops until now
  listOfObjects<int>* transitTime;  // Transit time at each stop in stops

  maxStopOverAndStationConnectionInfo(StationConnectionInfo* obj, listOfObjects<StationConnectionInfo*>* stn, listOfObjects<int>* transit, int stop = 0) {
    SCIobject = obj;
    stopOverUntilNow = stop;
    stops=stn;
    transitTime=transit;
  }

  ~maxStopOverAndStationConnectionInfo() {
    delete SCIobject;
  }
};


typedef listOfObjects<TrainInfoPerStation*> TIPS;
typedef listOfObjects<StationConnectionInfo*> SCI;
typedef listOfObjects<maxStopOverAndStationConnectionInfo*> SAS;
typedef listOfObjects<int> LI;
typedef maxStopOverAndStationConnectionInfo MS;


// My print function
// It is esentially same as printStationInfo but only prints one TrainInfoPerStation
void myPrintStationInfo(TIPS *toPrint)
{
  string days[7] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};
  TrainInfoPerStation* currInfo = toPrint->object;
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
      cout << endl;
    }
}


void Planner::printPlanJourneys(string srcStnName, string destStnName, int maxStopOvers, int maxTransitTime)
{
  // insert your code here

  // Days of week
  string days[7] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};

  // Get entry of source station in Dictionary
  Entry<int>* srcIndex= stnNameToIndex.get(srcStnName);
  // Get entry of destination station in Dictionary
  Entry<int>* destIndex= stnNameToIndex.get(destStnName);

  // Either of the station not in dictionary
  if(srcIndex==nullptr || destIndex==nullptr)
  {
    cout<<RED<<"No journey available"<<RESET<<endl;
    return;
  }

  // Get adjacency List for source station
  SCI *toStns= adjacency[srcIndex->value].toStations;
  // If no trains from source sation
  if(toStns==nullptr)
  {
    cout<<RED<<"No journey available"<<RESET<<endl;
    return;
  }

  // To store list of direct trains from source to destination
  SAS *dirTrainsStart=nullptr;  // Pointer to start
  SAS *dirTrainsEnd=nullptr;  // Pointer to end

  // Queue for BFS
  SAS *queueStart=nullptr;  // Queue Start
  SAS *queueEnd=nullptr;  // Queue End

  // Adding all trains passing through or starting at source station to queue
  // Iterator for adjacent stations
  SCI *adjToSrc= toStns;
  while(adjToSrc!=nullptr)
  {
    // Expand the list
    // As train 101 and 102 for example might run on different days
    // 101: Mon, Tue, Thur
    // 102: Mon, Thur
    // So after 101, we can take 102 only when day is either Mon or Thurs but not Tues

    // Expanding the list's implementation is taken from printStationInfo
    TIPS *currList, *expandedList;
    TrainInfoPerStation *currInfo;
    // Iterator for all the trains to adjToSrc
    TIPS *trainFromSrc=adjToSrc->object->trains;
    currList = trainFromSrc;
    expandedList = nullptr;
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
            newExpandedElement->setDayOfWeek(i);
            listOfObjects<TrainInfoPerStation *> *newExpandedListElement = new listOfObjects<TrainInfoPerStation *> (newExpandedElement);
            if (expandedList == nullptr) {
              expandedList = newExpandedListElement;
            }
            else {
              newExpandedListElement->next = expandedList;
              expandedList->prev = newExpandedListElement;
              expandedList = newExpandedListElement;
            }
          }
        }
      }
      currList = currList->next;
    }

    // We have our expanded list
    trainFromSrc=expandedList;
    // Add all trains
    while(trainFromSrc!=nullptr)
    {
      // Add this train with next stop's index in dictionary
      StationConnectionInfo *nextStn=new StationConnectionInfo(adjToSrc->object->adjacentStnIndex);
      nextStn->trains=new TIPS(trainFromSrc->object);
      // This will be first train to take
      StationConnectionInfo* forMS= new StationConnectionInfo(srcIndex->value);
      forMS->trains=new TIPS(trainFromSrc->object);
      // Queue entry with transit time as 0 and stopOverUntilNow as default=0
      MS *newEntry= new MS(nextStn, new SCI(forMS), new LI(0));
      SAS *listnewEntry= new SAS(newEntry);
      if(queueStart==nullptr) // Queue is empty so add at the start
      {
        queueStart=listnewEntry;
        queueEnd=queueStart;
      }
      else  // Queue is not empty so add next to the end
      {
        queueEnd->next=listnewEntry;
        listnewEntry->prev=queueEnd;
        queueEnd=listnewEntry;
      }
      trainFromSrc=trainFromSrc->next;
    }
    adjToSrc=adjToSrc->next;
  }

  //////////////////////////////////////// Do BFS ////////////////////////////////////////
  // Three cases are possible for head of the queue:
  // Case 1: It's train ends at destination without max stop-overs not exceeded , so put it into list of dirTrains and remove it
  // Case 2: Max stop-overs not exceeded, change the adjacentStnIndex to next station and update train's specifications and add it if it departs for some other station
  // Case 3: Else remove it
  while(queueStart!=nullptr)
  {
    /////////////////////// Case 1 ///////////////////////
    if(queueStart->object->SCIobject->adjacentStnIndex==destIndex->value && queueStart->object->stopOverUntilNow <= maxStopOvers)
    {
      // Add this train to list of dirTrains
      SAS *newEntry= new SAS(queueStart->object);
      if(dirTrainsStart==nullptr) // List is empty so add at the dirTrainsStart
      {
        dirTrainsStart=newEntry;
        dirTrainsEnd=dirTrainsStart;
      }
      else  // List is not empty so add to next of dirTrainsEnd
      {
        dirTrainsEnd->next=newEntry;
        newEntry->prev=dirTrainsEnd;
        dirTrainsEnd=newEntry;
      }
    }
    /////////////////////// Case 2 ///////////////////////
    else if(queueStart->object->stopOverUntilNow <= maxStopOvers)
    {
      // Find our queueStart's train in list for arrival day and arrival time
      // So that we can get transit time and whether other journey chosen is feasible
      StationConnectionInfo *nextStnTrain= new StationConnectionInfo(queueStart->object->SCIobject->adjacentStnIndex);
      SCI *toStnsTrain= adjacency[nextStnTrain->adjacentStnIndex].toStations;
      int arrTimeOriginal;  // arrTime of queueStart's train
      int arrDayOriginal; // arrTDay of queueStart's train
      bool found=false; // if train found
      // Find train
      while(toStnsTrain!=nullptr)
      {
        // all trains
        TIPS *trainFromStn=toStnsTrain->object->trains;
        while(trainFromStn!=nullptr)
        {
          if(trainFromStn->object->journeyCode == queueStart->object->SCIobject->trains->object->journeyCode)
          {
            // Found it !!!
            found=true;
            if(queueStart->object->SCIobject->trains->object->depTime!=-1)  
            {
              // It still continues so add at end of queue
              nextStnTrain->adjacentStnIndex=toStnsTrain->object->adjacentStnIndex;
              TrainInfoPerStation* currInfo = trainFromStn->object;
              int jCode = currInfo->journeyCode;
              int stSeq = currInfo->stopSeq;
              int arrTime = currInfo->arrTime;
              int depTime = currInfo->depTime;
              TrainInfoPerStation* duplicate=new TrainInfoPerStation(jCode, stSeq, arrTime, depTime);
              for (int i=0; i < 7; i++) 
              {
                if (currInfo->daysOfWeek[i]) 
                {
                  duplicate->daysOfWeek[i]=true;
                }
              }
              nextStnTrain->trains= new TIPS(duplicate);
            }
            // dayDept is departure day for train coming to this station at previous station
            // dayArr is arrival day for train coming to this station at this station
            int dayDept, dayArr;  
            for (int i=0; i<7; i++)
            {
              if(queueStart->object->SCIobject->trains->object->daysOfWeek[i])
              {
                if(queueStart->object->SCIobject->trains->object->arrTime > queueStart->object->SCIobject->trains->object->depTime)
                  dayDept=(i+1)%7;
                else
                  dayDept=i;
                break;
              }
            }
            // initTrainDept is departure time for train coming to this station at previous station
            // followTrainArr is arrival time for train coming to this station at this station
            int initTrainDept=queueStart->object->SCIobject->trains->object->depTime;
            int followTrainArr=trainFromStn->object->arrTime;

            // Assumption that a train will take a stop atleast once in 24 hours
            if(followTrainArr > initTrainDept)
            {
              // same day
              dayArr = dayDept;
            }
            else
            {
              // next day
              dayArr=(dayDept+1)%7;
            }
            for(int i=0; i<7; i++)
            {
              // only dayArr will be true
              if(i==dayArr)
                nextStnTrain->trains->object->daysOfWeek[i]=true;
              else
                nextStnTrain->trains->object->daysOfWeek[i]=false;
            }  
             
            arrTimeOriginal=followTrainArr;
            arrDayOriginal=dayArr;
          }
          trainFromStn=trainFromStn->next;
        }
        if(found)
          break;
        toStnsTrain=toStnsTrain->next;        
      }
      // Add to the end of queue if train doesn't end here
      if(queueStart->object->SCIobject->trains->object->depTime!=-1 && nextStnTrain->trains!=nullptr)
      {
        // copy Queue Start's stops and transitTime into newEntry
        // add this newEntry to end of queue
        SCI *toadd= queueStart->object->stops;
        SCI *newSCI= new SCI(toadd->object);
        toadd=toadd->next;
        SCI *endSCI= newSCI;
        while(toadd!=nullptr)
        {
          SCI *append= new SCI(toadd->object);
          append->prev= endSCI;
          endSCI->next=append;
          endSCI=append;
          toadd=toadd->next;
        }
        LI *stops=queueStart->object->transitTime;
        LI *newLI= new LI(stops->object);
        stops=stops->next;
        LI *endLI= newLI;
        while(stops!=nullptr)
        {
          LI *append= new LI(stops->object);
          append->prev= endLI;
          endLI->next=append;
          endLI=append;
          stops=stops->next;
        }

        MS *newEntry= new MS(nextStnTrain, newSCI, newLI, queueStart->object->stopOverUntilNow);      
        SAS *newlistEntry= new SAS(newEntry);
        queueEnd->next=newlistEntry;
        newlistEntry->prev=queueEnd;
        queueEnd=newlistEntry;
      }


      // Add updated Train/ new Train to end of the queue if feasible
      StationConnectionInfo *nextStn= new StationConnectionInfo(queueStart->object->SCIobject->adjacentStnIndex);
      SCI *toStns= adjacency[nextStn->adjacentStnIndex].toStations;
      while(toStns!=nullptr)
      {
        // Expanding the list's implementation is taken from printStationInfo
        TIPS *currList, *expandedList;
        TrainInfoPerStation *currInfo;
        TIPS *trainFromStn=toStns->object->trains;
        currList = trainFromStn;
        expandedList = nullptr;
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
                newExpandedElement->setDayOfWeek(i);
                listOfObjects<TrainInfoPerStation *> *newExpandedListElement = new listOfObjects<TrainInfoPerStation *> (newExpandedElement);
                if (expandedList == nullptr) {
                  expandedList = newExpandedListElement;
                }
                else {
                  newExpandedListElement->next = expandedList;
                  expandedList->prev = newExpandedListElement;
                  expandedList = newExpandedListElement;
                }
              }
            }
          }
          currList = currList->next;
        }
        // We have our expanded list
        trainFromStn = expandedList;
        while(trainFromStn!=nullptr)
        {
          if(trainFromStn->object->depTime==-1)
          {
            // No need to add as it ends here
            trainFromStn=trainFromStn->next;
            continue;
          }
          StationConnectionInfo *nextStn= new StationConnectionInfo(toStns->object->adjacentStnIndex);
          bool addIt=false; // If we are to add this train in queue
          int transitTime;  // This train's transit time
          nextStn->trains=new TIPS(trainFromStn->object);
          if(trainFromStn->object->journeyCode == queueStart->object->SCIobject->trains->object->journeyCode)
          {
            // Just check for day's offset from arrDayOriginal
            int maxDaysAhead=maxTransitTime/24;
            for(int i=1; i<=maxDaysAhead; i++)
            {
              if(trainFromStn->object->daysOfWeek[(arrDayOriginal+i)%7])
              {
                addIt=true;
                transitTime= i*2400;
                // Transit time calculation
                int deptminutes= trainFromStn->object->depTime%100;
                int arrminutes= trainFromStn->object->arrTime%100;
                // decreaseTotal is used as 1900 - 1820 = 80 but 19:00 - 18:20 = 00:40 which is what we want
                // we need to subtract 40 if arrminutes > deptminutes
                int decreaseTotal=0;
                if(arrminutes>deptminutes)
                {
                  decreaseTotal=40;
                }
                transitTime+= trainFromStn->object->depTime - trainFromStn->object->arrTime - decreaseTotal;
                if(transitTime <= 0 || (transitTime-1)/100 >= maxTransitTime) // transtTime out of bound
                  addIt=false;
                if(addIt)
                {
                  // copy Queue Start's stops and transitTime into newEntry
                  // append to its stops a new stop given by current station
                  // append to its transitTime the transitTime calculated above
                  // add this newEntry to end of queue
                  SCI *toadd= queueStart->object->stops;
                  SCI *newSCI= new SCI(toadd->object);
                  toadd=toadd->next;
                  SCI *endSCI= newSCI;
                  while(toadd!=nullptr)
                  {
                    SCI *append= new SCI(toadd->object);
                    append->prev= endSCI;
                    endSCI->next=append;
                    endSCI=append;
                    toadd=toadd->next;
                  }
                  StationConnectionInfo *forMS= new StationConnectionInfo(queueStart->object->SCIobject->adjacentStnIndex);
                  forMS->trains= new TIPS(nextStn->trains->object);
                  SCI *SCIend= new SCI(forMS);
                  endSCI->next= SCIend;
                  SCIend->prev=endSCI;
                  endSCI=SCIend;
                  LI *stops=queueStart->object->transitTime;
                  LI *newLI= new LI(stops->object);
                  stops=stops->next;
                  LI *endLI= newLI;
                  while(stops!=nullptr)
                  {
                    LI *append= new LI(stops->object);
                    append->prev= endLI;
                    endLI->next=append;
                    endLI=append;
                    stops=stops->next;
                  }
                  LI *LIend= new LI(transitTime);
                  endLI->next= LIend;
                  LIend->prev=endLI;
                  endLI=LIend;
                  MS *newEntry= new MS(nextStn, newSCI, newLI, queueStart->object->stopOverUntilNow + 1);
                  SAS *newlistEntry= new SAS(newEntry);
                  queueEnd->next=newlistEntry;
                  newlistEntry->prev=queueEnd;
                  queueEnd=newlistEntry;
                }
              }
            }
          }
          else
          {
            // departure day at current station
            int dayDept;
            for (int i=0; i<7; i++)
            {
              if(trainFromStn->object->daysOfWeek[i])
              {
                dayDept=i;
                break;
              }
            }
            if(trainFromStn->object->arrTime > trainFromStn->object->depTime)
            {
              dayDept=(dayDept+1)%7;
            }
            int deptminutes= trainFromStn->object->depTime%100;
            int arrminutes= arrTimeOriginal%100;
            // decreaseTotal is used as 1900 - 1820 = 80 but 19:00 - 18:20 = 00:40 which is what we want
            // we need to subtract 40 if arrminutes > deptminutes
            int decreaseTotal=0;
            if(arrminutes>deptminutes)
            {
              decreaseTotal=40;
            }
            int dayOffset= dayDept-arrDayOriginal;  // offset in departure and arrival
            if (dayOffset<0)
              dayOffset+=7;
            bool toContinue = true; // while we are in bounds for transit time
            while(toContinue)
            {
              int timeForDeptFromArr= dayOffset*2400 + trainFromStn->object->depTime - arrTimeOriginal - decreaseTotal;
              transitTime= timeForDeptFromArr;
              if(timeForDeptFromArr > 0 && (timeForDeptFromArr-1)/100 < maxTransitTime) // check if within bounds
                addIt=true;
              else
                addIt=false;
              if(addIt)
              {
                // copy Queue Start's stops and transitTime into newEntry
                // append to its stops a new stop given by current station
                // append to its transitTime the transitTime calculated above
                // add this newEntry to end of queue
                SCI *toadd= queueStart->object->stops;
                SCI *newSCI= new SCI(toadd->object);
                toadd=toadd->next;
                SCI *endSCI= newSCI;
                while(toadd!=nullptr)
                {
                  SCI *append= new SCI(toadd->object);
                  append->prev= endSCI;
                  endSCI->next=append;
                  endSCI=append;
                  toadd=toadd->next;
                }
                StationConnectionInfo *forMS= new StationConnectionInfo(queueStart->object->SCIobject->adjacentStnIndex);
                forMS->trains= new TIPS(nextStn->trains->object);
                SCI *SCIend= new SCI(forMS);
                endSCI->next= SCIend;
                SCIend->prev=endSCI;
                endSCI=SCIend;
                LI *stops=queueStart->object->transitTime;
                LI *newLI= new LI(stops->object);
                stops=stops->next;
                LI *endLI= newLI;
                while(stops!=nullptr)
                {
                  LI *append= new LI(stops->object);
                  append->prev= endLI;
                  endLI->next=append;
                  endLI=append;
                  stops=stops->next;
                }
                LI *LIend= new LI(transitTime);
                endLI->next= LIend;
                LIend->prev=endLI;
                endLI=LIend;
                MS *newEntry= new MS(nextStn, newSCI, newLI, queueStart->object->stopOverUntilNow + 1);
                SAS *newlistEntry= new SAS(newEntry);
                queueEnd->next=newlistEntry;
                newlistEntry->prev=queueEnd;
                queueEnd=newlistEntry;

                dayOffset+=7;
              }
              else
                toContinue=false; // We are out of bounds
            }
          }
          trainFromStn=trainFromStn->next;
        }
        toStns=toStns->next;        
      }
    }
    // Delete head of the queue
    if(queueStart->next!=nullptr)
    {
      // So after deleting element, queue still has atleast one element
      queueStart=queueStart->next;
      delete queueStart->prev;
      queueStart->prev=nullptr;
    }
    else
    {
      // This is last element in the queue
      delete queueStart;
      queueStart=nullptr;
    }
  }

  // Couldn't find a journey
  if(dirTrainsStart==nullptr)
  {
    cout<<RED<<"No journey available"<<RESET<<endl;
    return;
  }

  // Trains from Source
  SAS* dirTrainsIterator= dirTrainsStart; // Iterator for dirTrains
  cout<<endl;
  int i=1;
  while (dirTrainsIterator!=nullptr)
  {
    cout<<GREEN<<"Option "<<i<<RESET<<endl;
      i++;
    // All stops for a particular journey
    SCI* aJourney= dirTrainsIterator->object->stops;
    // Corresponding transitTime for this journey
    LI* transit= dirTrainsIterator->object->transitTime;
    // Start of journey
    bool first=true;
    while(aJourney != nullptr)
    {
      if(!first)
      {
        if(transit->object %100 >=10) 
          cout<<"Change train at "<<GREEN<<stnNameToIndex.getKeyAtIndex(aJourney->object->adjacentStnIndex)<<RESET<<" with a transit time of "<<RED<<transit->object /100 <<":"<<transit->object %100 <<" hours"<<RESET<<endl;
        else  // to print 1009 as 10:09 and not 10:9
          cout<<"Change train at "<<GREEN<<stnNameToIndex.getKeyAtIndex(aJourney->object->adjacentStnIndex)<<RESET<<" with a transit time of "<<RED<<transit->object /100 <<":0"<<transit->object %100 <<" hours"<<RESET<<endl;
      }
      if(aJourney->next!=nullptr) // This train ends at a station other than destination and we have to take another train from here
        cout<<"Train is from "<<RED<<stnNameToIndex.getKeyAtIndex(aJourney->object->adjacentStnIndex)<<RESET<<" to "<<GREEN<<stnNameToIndex.getKeyAtIndex(aJourney->next->object->adjacentStnIndex)<<RESET<<endl;
      else  // This train ends at destination
        cout<<"Train is from "<<RED<<stnNameToIndex.getKeyAtIndex(aJourney->object->adjacentStnIndex)<<RESET<<" to "<<GREEN<<stnNameToIndex.getKeyAtIndex(destIndex->value)<<RESET<<endl;
      TIPS* toPrint= new TIPS(aJourney->object->trains->object);
      // call myPrintStationInfo
      myPrintStationInfo(toPrint);
      delete toPrint;
      // Journey has already begun!!!
      first=false;
      aJourney=aJourney->next;
      transit=transit->next;
    }
    cout<<endl;
    dirTrainsIterator=dirTrainsIterator->next;
  }
  return;
}

#endif