#ifndef PRINT_JOURNEY_CPP
#define PRINT_JOURNEY_CPP

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif
#include "planner.h"
using namespace std;

#define RESET "\033[0m"
#define GREEN "\033[32m"
#define RED "\033[31m"
#define BLUE "\033[34m"
#define COLOR "\033[33m"

// The below struct is used to store the info of train from src to dest with days, source name(as index) and dest name(as inedx).
struct TrainInfo
{
  TrainInfoPerStation *src, *dest;
  int src_ind, dest_ind;
  string src_arr_day, dest_arr_day;
  TrainInfo(TrainInfoPerStation *s, TrainInfoPerStation *d, int si, int di, string sad, string dad)
  {
    src = s;
    dest = d;
    src_ind = si;
    dest_ind = di;
    src_arr_day = sad;
    dest_arr_day = dad;
  }
};

// The below function prints same as the printStationInfo but uses list of TrainInfo instead of TrainInfoPerStation
void PrintAllJrny(listOfObjects<TrainInfo *> *list, Dictionary<int> stnName)
{
  // printing src and stop 1.
  cout << BLUE << "JourneyCode: " << RESET << list->object->src->journeyCode << endl;
  cout << COLOR << "Source               : " << RESET << stnName.getKeyAtIndex(list->object->src_ind) << "\t";
  cout << GREEN << "Day : " << RESET << list->object->src_arr_day << "\t";
  cout << RED << "Arr: " << RESET;
  if (list->object->src->arrTime == -1)
  {
    cout << "Starts";
  }
  else
  {
    cout << list->object->src->arrTime;
  }
  cout << RED << " Dep: " << RESET;
  if (list->object->src->depTime == -1)
  {
    cout << "Ends";
  }
  else
  {
    cout << list->object->src->depTime;
  }
  cout << endl;
  bool direct = false;
  if (list->prev == nullptr)
  {
    cout << COLOR << "Destination Station  : " << RESET << stnName.getKeyAtIndex(list->object->dest_ind) << "\t";
    direct = true;
  }
  else
  {
    while(true){
      if(list->prev != nullptr){
        if(list->prev->object->src->journeyCode == list->object->dest->journeyCode && 
           list->prev->object->src_ind == list->object->dest_ind &&
           list->prev->object->src_arr_day == list->object->dest_arr_day){list = list->prev;}
        else break;
      }
      else break;
    }
    if(list->prev == nullptr){
      cout << COLOR << "Destination Station  : " << RESET << stnName.getKeyAtIndex(list->object->dest_ind) << "\t";
    }
    else{
      cout << COLOR << "Intermediate Station : " << RESET << stnName.getKeyAtIndex(list->object->dest_ind) << "\t";
    }
  }
  cout << GREEN << "Day : " << RESET << list->object->dest_arr_day << "\t";
  cout << RED << "Arr: " << RESET;
  if (list->object->dest->arrTime == -1)
  {
    cout << "Starts";
  }
  else
  {
    cout << list->object->dest->arrTime;
  }
  cout << RED << " Dep: " << RESET;
  if (list->object->dest->depTime == -1)
  {
    cout << "Ends";
  }
  else
  {
    cout << list->object->dest->depTime;
  }
  cout << endl;
  if (direct){return;}
  if(list->prev != nullptr)
    list = list->prev;
  else return;
  cout << "---------------------------------------------------------------------------\n";
  
  while (list->prev != nullptr)
  {
    bool last = false;
    while(true){
      if(list->prev != nullptr){
        if(list->prev->object->src->journeyCode == list->object->dest->journeyCode && 
           list->prev->object->src_ind == list->object->dest_ind &&
           list->prev->object->src_arr_day == list->object->dest_arr_day){list = list->prev;}
        else break;
      }
      else{last = true; break;}
    }
    if(last)break;
    cout << BLUE << "JourneyCode: " << RESET << list->object->src->journeyCode << endl;
    cout << COLOR << "Intermediate Station : " << RESET << stnName.getKeyAtIndex(list->object->src_ind) << "\t";
    cout << GREEN << "Day : " << RESET << list->object->src_arr_day << "\t";
    cout << RED << "Arr: " << RESET;
    if (list->object->src->arrTime == -1)
    {
      cout << "Starts";
    }
    else
    {
      cout << list->object->src->arrTime;
    }
    cout << RED << " Dep: " << RESET;
    if (list->object->src->depTime == -1)
    {
      cout << "Ends";
    }
    else
    {
      cout << list->object->src->depTime;
    }
    cout << endl;
    cout << COLOR << "Intermediate Station : " << RESET << stnName.getKeyAtIndex(list->object->dest_ind) << "\t";
    cout << GREEN << "Day : " << RESET << list->object->dest_arr_day << "\t";
    cout << RED << "Arr: " << RESET;
    if (list->object->dest->arrTime == -1)
    {
      cout << "Starts";
    }
    else
    {
      cout << list->object->dest->arrTime;
    }
    cout << RED << " Dep: " << RESET;
    if (list->object->dest->depTime == -1)
    {
      cout << "Ends";
    }
    else
    {
      cout << list->object->dest->depTime;
    }
    cout << endl;
    cout << "---------------------------------------------------------------------------\n";
    if(list->prev != nullptr)
      list = list->prev;
  }
  cout << BLUE << "JourneyCode: " << RESET << list->object->src->journeyCode << endl;
  cout << COLOR << "Intermediate Station : " << RESET << stnName.getKeyAtIndex(list->object->src_ind) << "\t";
  cout << GREEN << "Day : " << RESET << list->object->src_arr_day << "\t";
  cout << RED << "Arr: " << RESET;
  if (list->object->src->arrTime == -1)
  {
    cout << "Starts";
  }
  else
  {
    cout << list->object->src->arrTime;
  }
  cout << RED << " Dep: " << RESET;
  if (list->object->src->depTime == -1)
  {
    cout << "Ends";
  }
  else
  {
    cout << list->object->src->depTime;
  }
  cout << endl;
  cout << COLOR << "Destination Station  : " << RESET << stnName.getKeyAtIndex(list->object->dest_ind) << "\t";
  cout << GREEN << "Day : " << RESET << list->object->dest_arr_day << "\t";
  cout << RED << "Arr: " << RESET;
  if (list->object->dest->arrTime == -1)
  {
    cout << "Starts";
  }
  else
  {
    cout << list->object->dest->arrTime;
  }
  cout << RED << " Dep: " << RESET;
  if (list->object->dest->depTime == -1)
  {
    cout << "Ends";
  }
  else
  {
    cout << list->object->dest->depTime;
  }
  cout << endl;
}

// the below function checks if the next train will be valid according to max transit time
// this is achieved by calculating the day and time limit by adding transit time to arrival day and checking if departure time is less than transit time.
bool valid(TrainInfoPerStation *a, TrainInfoPerStation *b, int transit)
{
  if (b->depTime < 0)
    return false;
  // when journeycode is equal it can happen that the same train is taken on same day or going with same journeycode but on different day
  // but when transit is less than 2400 then 2400 should be considered since the train can stop at station for 24 hrs.
  if (a->journeyCode == b->journeyCode && transit < 2400)
    transit = 2400;
  if (transit >= 2400 * 7)
    return true;
  int day_a = 0;
  int day_b = 0;
  int time_a = a->arrTime;
  int time_b = b->depTime;
  for (int i = 0; i < 7; i++)
  {
    if (a->daysOfWeek[i])
      day_a = i;
    if (b->daysOfWeek[i])
      day_b = i;
  }
  if (day_b < day_a)
    day_b += 7;
  else if (day_b == day_a)
  {
    if (time_a > time_b)
    {
      day_b += 7;
    }
  }
  int dept_day = day_a + transit / 2400;
  transit = transit % 2400;
  int hrs = a->arrTime / 100 + transit / 100;
  int min = a->arrTime % 100 + transit % 100;
  if (min >= 60)
  {
    hrs++;
    min -= 60;
  }
  int dept_time = hrs * 100 + min;
  if (dept_time >= 2400)
  {
    dept_time -= 2400;
    dept_day++;
  }
  if (dept_day > day_b)
    return true;
  if (dept_day == day_b)
  {
    if (dept_time >= time_b)
      return true;
  }
  return false;
}
// expand creates a new list in which each TrainInfoPerStation contains only one day
listOfObjects<TrainInfoPerStation *> *expand(listOfObjects<TrainInfoPerStation *> *list, TrainInfoPerStation *filter, int transit)
{
  listOfObjects<TrainInfoPerStation *> *expanded = nullptr;
  while (list != nullptr && list->object->depTime > 0)
  {
    for (int i = 0; i < 7; i++)
    {
      if (list->object->daysOfWeek[i])
      {
        TrainInfoPerStation *temp = new TrainInfoPerStation(list->object->journeyCode, list->object->stopSeq, list->object->arrTime, list->object->depTime);
        temp->setDayOfWeek(i);
        if (filter != nullptr)
        {
          if (valid(filter, temp, transit))
          {
            if (expanded == nullptr)
            {
              expanded = new listOfObjects<TrainInfoPerStation *>(temp);
            }
            else
            {
              listOfObjects<TrainInfoPerStation *> *iter = expanded;
              while (iter->next != nullptr)
              {
                iter = iter->next;
              }
              iter->next = new listOfObjects<TrainInfoPerStation *>(temp);
            }
          }
        }
        else
        {
          if (expanded == nullptr)
          {
            expanded = new listOfObjects<TrainInfoPerStation *>(temp);
          }
          else
          {
            listOfObjects<TrainInfoPerStation *> *iter = expanded;
            while (iter->next != nullptr)
            {
              iter = iter->next;
            }
            iter->next = new listOfObjects<TrainInfoPerStation *>(temp);
          }
        }
      }
    }
    list = list->next;
  }
  return expanded;
}
// Is present gives the pointer to the same Jrny from list if the Jrny is present in the list with changed day.
TrainInfoPerStation *isPresent(TrainInfoPerStation *Jrny, listOfObjects<TrainInfoPerStation *> *list)
{
  while (list != nullptr)
  {
    if (list->object->journeyCode == Jrny->journeyCode)
    {
      TrainInfoPerStation *return_train = new TrainInfoPerStation(list->object->journeyCode, list->object->stopSeq, list->object->arrTime, list->object->depTime);
      for (int i = 0; i < 7; i++)
      {
        if (Jrny->daysOfWeek[i])
        {
          if (return_train->arrTime <= Jrny->depTime)
          {
            return_train->setDayOfWeek((i + 1) % 7);
            return return_train;
          }
          else
          {
            return_train->setDayOfWeek(i);
            return return_train;
          }
        }
      }
    }
    list = list->next;
  }
  return nullptr;
}

void Planner::printPlanJourneys(string srcStnName, string destStnName, int maxStopOvers, int maxTransitTime)
{
  // insert your code here

  // cout << "This function is to be implemented by you." << endl;
  static string days[7] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};

  // Get the expanded list. Now if recursionlvl is 0 then just iterate over list and apply while loop
  // If recursionllvl is not 0 then given a train info filter only those journeys which are possible according to constraint.
  static int src_hash = stnNameToIndex.get(srcStnName)->value;
  static int dest_hash = stnNameToIndex.get(destStnName)->value;
  if (src_hash == -1)
  {
    src_hash = stnNameToIndex.get(srcStnName)->value;
    dest_hash = stnNameToIndex.get(destStnName)->value;
  }
  static int prev_hash = -1;
  int temp = src_hash;
  int temp_prev = prev_hash;
  static int recurslvl = -1;

  recurslvl++;
  // it stores the final ans and is used to print.
  static listOfObjects<TrainInfo *> *fin_head = nullptr;
  static listOfObjects<TrainInfo *> *fin_tail = nullptr;
  // when maxStopOvers limit is exceeded then return
  if (maxStopOvers == -1)
  {
    recurslvl--;
    return;
  }
  // filter is used to filter out all next valid journeys in adjacent station.
  // it also sees if the journey leads to the next station if not then return.
  TrainInfoPerStation *filter = nullptr;
  if (recurslvl != 0)
  {
    listOfObjects<StationConnectionInfo *> *from = adjacency[src_hash].fromStations;
    while (from != nullptr)
    {
      if (from->object->adjacentStnIndex == prev_hash)
      {
        filter = isPresent(fin_head->object->src, from->object->trains);
      }
      from = from->next;
    }
    if (filter == nullptr)
    {
      // cout << "notrain\n";
      recurslvl--;
      return;
    }
    fin_head->object->dest = filter;
    fin_head->object->dest_ind = src_hash;
    int i = 0;
    while(!fin_head->object->dest->daysOfWeek[i]){i++;}
    fin_head->object->dest_arr_day = days[i];
  }
  // when we reach the dest node then just print the answer.
  if (src_hash == dest_hash)
  {
    PrintAllJrny(fin_tail, stnNameToIndex);
    cout << "===========================================================================\n";
    recurslvl--;
    return;
  }
  // creating expanded list which contains trains info with only one day and valid journeys according to maxTransit time.
  listOfObjects<TrainInfoPerStation *> *expanded = nullptr;
  if (fin_head == nullptr)
  {
    expanded = expand(stationInfo[src_hash], nullptr, maxTransitTime);
  }
  else
  {
    expanded = expand(stationInfo[src_hash], filter, maxTransitTime);
  }
  // Iterating over all the trains and appending values in the answer
  while (expanded != nullptr)
  {
    // creating the new TrainInfo and appending to expanded list.
    if (fin_tail == nullptr)
    {
      int i = 0;
      while(!expanded->object->daysOfWeek[i]){i++;}
      fin_head = new listOfObjects<TrainInfo *>(new TrainInfo(expanded->object, nullptr, src_hash, -1, days[i], days[0]));
      fin_tail = fin_head;
    }
    else
    {
      int i = 0;
      while(!expanded->object->daysOfWeek[i]){i++;}      
      fin_head->prev = new listOfObjects<TrainInfo *>(new TrainInfo(expanded->object, nullptr, src_hash, -1, days[i], days[0]));
      fin_head->prev->next = fin_head;
      fin_head = fin_head->prev;
    }
    // takin the TrainInfo and doing dfs on each adjacent train station.
    listOfObjects<StationConnectionInfo *> *adj = adjacency[src_hash].toStations;
    while (adj != nullptr)
    {
      prev_hash = src_hash;
      src_hash = adj->object->adjacentStnIndex;
      if (recurslvl == 0)
      {
        printPlanJourneys(srcStnName, destStnName, maxStopOvers, maxTransitTime);
      }
      else
      {
        if (fin_head->next->object->src->journeyCode == fin_head->object->src->journeyCode)
        {
          printPlanJourneys(srcStnName, destStnName, maxStopOvers, maxTransitTime);
        }
        else
        {
          printPlanJourneys(srcStnName, destStnName, maxStopOvers - 1, maxTransitTime);
        }
      }
      src_hash = temp;
      prev_hash = temp_prev;
      adj = adj->next;
    }
    // deleting recently added journey to maintain the list since it is static
    if (recurslvl == 0)
    {
      fin_tail = fin_head = nullptr;
    }
    else
    {
      fin_head = fin_head->next;
      delete fin_head->prev;
      fin_head->prev = nullptr;
    }
    expanded = expanded->next;
  }
  // cout << "+++" << recurslvl << " ";
  recurslvl--;
  // cout << recurslvl << "+++" << endl;
  // at the end of programme re-assining values to src_hash and prev_hash since it is static. 
  if (recurslvl == -1)
  {
    src_hash = -1;
    prev_hash = -1;
  }
}

#endif
