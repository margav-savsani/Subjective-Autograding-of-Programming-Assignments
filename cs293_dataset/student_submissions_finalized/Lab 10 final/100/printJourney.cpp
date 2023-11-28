#ifndef PRINT_JOURNEY_CPP
#define PRINT_JOURNEY_CPP

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#include "planner.h"

#define RESET "\033[0m"
#define GREEN "\033[32m"
#define RED "\033[31m"
#define BLUE "\033[34m"

using namespace std;
class ALLInfo // a class to store all info and find journeys reccursively
{

  StationAdjacencyList *adjacency;                    
  listOfObjects<TrainInfoPerStation *> **stationInfo; 
  Dictionary<int> stnNameToIndex;                     
  int maxStopOvers;                                   
  int maxTransitTime;                                
  int src_index;                                      
  int routeNo;                                          

public:
  ALLInfo(StationAdjacencyList adjacency[512], listOfObjects<TrainInfoPerStation *> *(stationInfo)[512], Dictionary<int> stnNameToIndex, int maxStopOvers, int maxTransitTime)
  { 
    this->adjacency = adjacency;
    this->stationInfo = stationInfo;
    this->stnNameToIndex = stnNameToIndex;
    this->maxStopOvers = maxStopOvers;
    this->maxTransitTime = maxTransitTime;
    routeNo = 0;
  }

  //printer function to print journeys in some specific format
  void printer(listOfObjects<int> *jcs, listOfObjects<int> *stnIndices) 
  {
    cout<<"\n##########################################################\n";
    // while (currtrains != nullptr)
      // {
      //   if (currtrains->object->journeyCode == jcs->object)
      //   {
      //     printinfostn(currtrains->object); 
          
      //     break;
      //   }
      //   currtrains = currtrains->next;
      // }
    while (jcs->prev != nullptr)
    {
      jcs = jcs->prev; 
    }
    while (stnIndices->prev != nullptr)
    {
      stnIndices = stnIndices->prev; 
    }
    listOfObjects<TrainInfoPerStation *> *currtrains, *prevtrains;
    while (stnIndices->next != nullptr)
    {
      currtrains = stationInfo[stnIndices->object];
      if (jcs->prev != nullptr && jcs->prev->object != jcs->object)
      { 
        while (currtrains != nullptr)
        {
          if (currtrains->object->journeyCode == jcs->object)
          {
            break;
          }
          currtrains = currtrains->next;
        }
        
        cout <<RED <<"\nCHANGE TRAIN TO JOURNEY CODE: "<<jcs->object<<RESET<<"\n"<<endl;
      }
      // while (currtrains != nullptr)
      // {
      //   if (currtrains->object->journeyCode == jcs->object)
      //   {
      //     printinfostn(currtrains->object); 
          
      //     break;
      //   }
      //   currtrains = currtrains->next;
      // }
      // from and to stations
      cout << stnNameToIndex.getKeyAtIndex(stnIndices->object) << endl;
      cout<<"\n";
      listOfObjects<StationConnectionInfo *> *tostation = adjacency[stnIndices->next->object].fromStations;
      while (currtrains != nullptr)
      {
        if (currtrains->object->journeyCode == jcs->object)
        {
          printinfostn(currtrains->object); 
          
          break;
        }
        currtrains = currtrains->next;
      }
      // while (currtrains != nullptr)
      // {
      //   if (currtrains->object->journeyCode == jcs->object)
      //   {
      //     printinfostn(currtrains->object); 
          
      //     break;
      //   }
      //   currtrains = currtrains->next;
      // }
      while (tostation != nullptr)
      {
        currtrains = tostation->object->trains;
        while (currtrains != nullptr)
        {
          if (currtrains->object->journeyCode == jcs->object)
          {
            printinfostn(currtrains->object); // this is the arrival and departure time at the next station
            prevtrains = currtrains;       
            jcs = jcs->next;               // moving to the next journey code
            break;
          }
          currtrains = currtrains->next;
        }
        // while (currtrains != nullptr)
      // {
      //   if (currtrains->object->journeyCode == jcs->object)
      //   {
      //     printinfostn(currtrains->object); 
          
      //     break;
      //   }
      //   currtrains = currtrains->next;
      // }
        if (currtrains != nullptr)
        {
          break;
        }
        tostation = tostation->next;
      }
      stnIndices = stnIndices->next;
    }
  }

int calctranstime(listOfObjects<TrainInfoPerStation *> *incomingtrain, listOfObjects<TrainInfoPerStation *> *outgoingtrain)
  {
    // calculates the transit time between trains
    bool nextdayincoming = false, nextdayoutgoing = false;
    if (incomingtrain->object->arrTime > incomingtrain->object->depTime)
      nextdayincoming = true; 
    if (outgoingtrain->object->arrTime > outgoingtrain->object->depTime)
      nextdayoutgoing = true;
    int arr = incomingtrain->object->arrTime;
    int dep = outgoingtrain->object->depTime;
    int Time = -1;
    for (int i = 0; i < 7; i++)
    { 
      if (incomingtrain->object->daysOfWeek[i] == outgoingtrain->object->daysOfWeek[i] && outgoingtrain->object->daysOfWeek[i])
      { 
        if ((!nextdayincoming && !nextdayoutgoing) || (nextdayincoming && !nextdayoutgoing))
        { 
          if (dep - arr < 0 || (dep - arr) > maxTransitTime*100)
            continue;
          else
            return ((dep - arr));
        }
        // while (currtrains != nullptr)
      // {
      //   if (currtrains->object->journeyCode == jcs->object)
      //   {
      //     printinfostn(currtrains->object); 
          
      //     break;
      //   }
      //   currtrains = currtrains->next;
      // }
        else if ((nextdayincoming && nextdayoutgoing) || (!nextdayincoming && nextdayoutgoing))
        { 
          if ((dep - arr) + 2400 > maxTransitTime*100)
            continue;
          else
            return (dep / 100 - arr / 100) * 100 + ((dep % 100 == 0 && arr % 100 != 0) ? 60 - (arr % 100) - 100 : (dep % 100) - (arr % 100)) + 2400;
        }
        // while (currtrains != nullptr)
      // {
      //   if (currtrains->object->journeyCode == jcs->object)
      //   {
      //     printinfostn(currtrains->object); 
          
      //     break;
      //   }
      //   currtrains = currtrains->next;
      // }
      }
      else if (incomingtrain->object->daysOfWeek[i] < outgoingtrain->object->daysOfWeek[i])
      { 
        if (nextdayoutgoing && incomingtrain->object->daysOfWeek[i + 1] && arr < dep)
        {
          if ((dep - arr) / 100 > maxTransitTime)
            continue;
          else
            return (dep / 100 - arr / 100) * 100 + ((dep % 100 == 0 && arr % 100 != 0) ? 60 - (arr % 100) - 100 : (dep % 100) - (arr % 100));
        }
        // while (currtrains != nullptr)
      // {
      //   if (currtrains->object->journeyCode == jcs->object)
      //   {
      //     printinfostn(currtrains->object); 
          
      //     break;
      //   }
      //   currtrains = currtrains->next;
      // }
      }
      else if ((incomingtrain->object->daysOfWeek[i] > outgoingtrain->object->daysOfWeek[i]))
      { 
        int j;
        for (j = i + 1; j < 7; j++)
          if (outgoingtrain->object->daysOfWeek[j])
            break;
        if (j < 7)
        {
          if (((dep - arr) / 100) + 24 * (j - i) > maxTransitTime)
            continue;
          // while (currtrains != nullptr)
      // {
      //   if (currtrains->object->journeyCode == jcs->object)
      //   {
      //     printinfostn(currtrains->object); 
          
      //     break;
      //   }
      //   currtrains = currtrains->next;
      // }
          else
          {
            int last1 = (dep / 100 - arr / 100) * 100 + ((dep % 100 == 0 && arr % 100 != 0) ? 60 - (arr % 100) - 100 : (dep % 100) - (arr % 100)) + 2400 * (j - i);
            if (Time == -1 || last1 < Time)
              Time = last1; 
          }
        }
      }
    }
    
      return Time;
  }

  bool findJourney(int index, int dest_index, int StopOvers, listOfObjects<int> *jcs, listOfObjects<int> *stnIndices)
  {
    //if next station is is destination station
    if (index == dest_index)                       
    {
      printer(jcs, stnIndices);
      return true;
    }
    // while (currtrains != nullptr)
      // {
      //   if (currtrains->object->journeyCode == jcs->object)
      //   {
      //     printinfostn(currtrains->object); 
          
      //     break;
      //   }
      //   currtrains = currtrains->next;
      // }
    bool res = false; 
    listOfObjects<StationConnectionInfo *> *tostation = adjacency[index].toStations;
    if (tostation == nullptr)
      return false;                                            
    listOfObjects<TrainInfoPerStation *> *alltrains = nullptr; 

    // traversing on each station and trains
    while (tostation != nullptr)
    {
      int adj_index = tostation->object->adjacentStnIndex; 
      alltrains = tostation->object->trains;
      //operating on each train leaving station              
      while (alltrains != nullptr)
      {
        listOfObjects<int> *list1 = new listOfObjects<int>(alltrains->object->journeyCode); // making the new linked list
        list1->prev = jcs;                                                                  // add it to the linked list of the journey code
        int stp = StopOvers;
        if (jcs != nullptr) 
        {
          if (jcs->object != list1->object) 
          {
            stp++; 
            listOfObjects<StationConnectionInfo *> *fromstation = adjacency[index].fromStations;
            listOfObjects<TrainInfoPerStation *> *incomingtrain = nullptr;
            while (fromstation != nullptr)
            { 
              incomingtrain = fromstation->object->trains;
              while (incomingtrain != nullptr && incomingtrain->object->journeyCode != jcs->object)
                incomingtrain = incomingtrain->next;
              if (incomingtrain != nullptr)
                break;
              fromstation = fromstation->next;
            }
            // while (currtrains != nullptr)
      // {
      //   if (currtrains->object->journeyCode == jcs->object)
      //   {
      //     printinfostn(currtrains->object); 
          
      //     break;
      //   }
      //   currtrains = currtrains->next;
      // }
            if (stp > maxStopOvers || calctranstime(incomingtrain, alltrains) == -1)
            {                              
              alltrains = alltrains->next; 
              continue;                    
            }
          }
          jcs->next = list1; 
        }
        // while (currtrains != nullptr)
      // {
      //   if (currtrains->object->journeyCode == jcs->object)
      //   {
      //     printinfostn(currtrains->object); 
          
      //     break;
      //   }
      //   currtrains = currtrains->next;
      // }
        listOfObjects<int> *nextstn = new listOfObjects<int>(adj_index); 
        nextstn->prev = stnIndices;
        if (stnIndices != nullptr)
          stnIndices->next = nextstn;
        res = (findJourney(adj_index, dest_index, stp, list1, nextstn) || res); 
        alltrains = alltrains->next;
      }
      tostation = tostation->next; 
    }
    return res; 
  }

  void printinfostn(TrainInfoPerStation *Info)
  {
    // a part of function as printStationInfo in the planner.h using it print here
    string days[7] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
    if (Info != nullptr)
    {
      for (int i = 0; i < 7; i++)
      {
        if (Info->daysOfWeek[i]){
          cout << GREEN << "Day: " << RESET;
          cout << days[i] << endl;
          cout << BLUE << "JourneyCode: " << Info->journeyCode << RESET << "\t";
          cout << RED << "Arr: " << RESET;
          if (Info->arrTime == -1)cout << "Starts";
          else
            cout << Info->arrTime;
          cout << RED << " Dep: " << RESET;
          if (Info->depTime == -1)
            cout << "Ends"<<endl;
          else
            cout << Info->depTime<<endl;
        }
      }
    }
      
      
  }
};

void Planner::printPlanJourneys(string srcStnName, string destStnName, int maxStopOvers, int maxTransitTime)
{

  // source station index
  if (srcStnName == destStnName)
    return;
  int source_index = stnNameToIndex.get(srcStnName)->value;
  int dest_index = stnNameToIndex.get(destStnName)->value;

  ALLInfo object(adjacency, stationInfo, stnNameToIndex, maxStopOvers, maxTransitTime); // make an object here copying takes linear time only for dictionary
  listOfObjects<int> *curr = new listOfObjects<int>(source_index);
  if (!object.findJourney(source_index, dest_index, 0, nullptr, curr))
  {                                                                                                                   // calling the function
   // incase no way found
    cout << "SORRY, NO Journey POSSIBLE!" << endl;
  }
  return;
}
#endif
