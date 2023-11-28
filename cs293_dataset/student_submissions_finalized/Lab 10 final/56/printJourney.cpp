#ifndef PRINT_JOURNEY_CPP
#define PRINT_JOURNEY_CPP

#ifndef PLANNER_H
#include "planner.h"
#endif

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#include <cassert>

using namespace std;

template <typename T>
class Util_Queue
{ // A queue class, used as a utility data structure
public:
  listOfObjects<T> *queue; // stores the start of the queue
  int length;              // length of the queue
  listOfObjects<T> *end;   // end pointer of the queue
  Util_Queue()
  { // default constructor
    queue = nullptr;
    length = 0;
    end = nullptr;
  }
  Util_Queue(T entry)
  {
    queue = new listOfObjects<T>(entry);
    length = 1;
    end = queue;
  }
  Util_Queue(listOfObjects<T> *entries)
  { // construct a queue with a list of entries
    length = 0;
    queue = nullptr;
    end = nullptr;
    if (entries != nullptr)
    {
      listOfObjects<T> *trav = entries;
      while (trav != nullptr)
      {
        this->push(trav->object);
        trav = trav->next;
      }
    }
  }
  void push(T entry)
  { // the standard push operation on queues
    if (queue != nullptr)
    {
      listOfObjects<T> *elt = new listOfObjects<T>(entry);
      end->next = elt;
      elt->prev = end;
      end = elt;
      length++;
    }
    else
    {
      queue = new listOfObjects<T>(entry);
      length = 1;
      end = queue;
    }
  }
  listOfObjects<T> *pop()
  { // the standard pop operation on queues
    if (length != 0)
    {
      if (length == 1)
      {
        auto top = queue;
        queue = nullptr;
        length = 0;
        end = nullptr;
        top->prev = nullptr;
        top->next = nullptr;
        return top;
      }
      else
      {
        auto top = queue;
        listOfObjects<T> *temp = queue->next;
        queue = temp;
        queue->prev = nullptr;
        length--;
        top->prev = nullptr;
        top->next = nullptr;
        return top;
      }
    }
    else
    {
      cout << "aborting" << endl; // something wrong with the program, abort for the meanwhile
      abort();
    }
  }
  bool isEmpty()
  { // function to check if the queue is empty
    return (length == 0);
  }
};

struct InfoNode   //tree node which stores relevant dynamic info such as layover time, layover number etc
{
  InfoNode *parent;   //parent node
  TrainInfoPerStation *info; // use this only to query arrtime, deptime and jrnycode
  int src, dest;   //IDs of source and destination station corresponding to info
  int weekday;    //the day of the week this node is related to
  int layovers_until;  //the layovers until this current node; gets updated according to the corresponding variable in parent node
  int layover_time;  //layover time corresponding to this node

  InfoNode(TrainInfoPerStation *info, int src, int dest, int weekday)
  {   
    this->src = src;
    this->dest = dest;
    this->info = info;
    layover_time = 0;
    parent = nullptr;
    layovers_until = 0;
    this->weekday = weekday;
  }
  bool addToParent(InfoNode *par, listOfObjects<TrainInfoPerStation *> *stnInfo, int maxStopOvers, int maxTransitTime)
  { //checks if the current node is a valid child of the parent, otherwis delete this object

    int jrny_par = par->info->journeyCode;   //parent's journey code
    if (par->layovers_until == maxStopOvers && info->journeyCode != jrny_par)   //layovers already maxed out
    {
      return false;
    }
    int arr_time_par = -1;
    int par_travel_day;   //assuming that a train doesn't run for more than 24 hrs, this variable stores the day of arrival of the parent's journey code train at the current station
    auto trav = stnInfo;   //traverse through the current node's station info to get the arrival time of parent's journey
    while (trav != nullptr)
    {
      if (trav->object->journeyCode == jrny_par)
      {
        arr_time_par = trav->object->arrTime;   //parent's journey code found

        if (par->info->depTime < arr_time_par)
        { //if day is the same, then this is the day on which train arrives at the current node
          par_travel_day = par->weekday;
        }
        else
        {//if the date is different, then the train has to arrive at this station on the next day
          par_travel_day = par->weekday + 1; // a train runs for atmost 24 hrs
        }
        break;
      }
      trav = trav->next;
    }
    if (arr_time_par == -1)   //journey code not found(technical failures), cannot be a valid child node
    {
      return false;
    }
    bool poss = false;  //variable that stores if this is a possible child
    if (info->journeyCode == jrny_par && par_travel_day == weekday)   //same day, same code => same train, hence possible child
    {
      poss = true;
    }
    else
    {// calculate the difference between parent and current journey times and compare with maxTransitTime
      int temp = (weekday >= par_travel_day ? weekday - par_travel_day : 7 + weekday - par_travel_day);  
      int non_day_delay;
      if (info->depTime >= arr_time_par)
      {
        int hr1 = info->depTime / 100;
        int hr2 = arr_time_par / 100;
        int min1 = info->depTime % 100;
        int min2 = arr_time_par % 100;
        int resmin = 0;
        if (min1 >= min2)
          resmin = min1 - min2;
        else
        {
          resmin = 60 + min1 - min2;
          hr1--;
        }
        int reshr = hr1 - hr2;
        non_day_delay = reshr * 100 + resmin;
      }
      else
      {
        int hr2 = info->depTime / 100;
        int hr1 = arr_time_par / 100;
        int min2 = info->depTime % 100;
        int min1 = arr_time_par % 100;
        int resmin = 0;
        if (min1 >= min2)
          resmin = min1 - min2;
        else
        {
          resmin = 60 + min1 - min2;
          hr1--;
        }
        int reshr = hr1 - hr2;
        non_day_delay = reshr * 100 + resmin;
      }
      int hrsdelay = temp * 2400 + non_day_delay; 

      if (hrsdelay > 0 && hrsdelay <= maxTransitTime * 100)
      { // assuming max transit time is given in hours(int)

         
        if(par->layovers_until >= maxStopOvers){  //parent already has max layovers, hence cannot be a child
          assert(par->layovers_until == maxStopOvers);
          return false;
        }
        layovers_until = par->layovers_until + 1;    //journey code is not same/same journey code but different day => layovers increases
        layover_time = hrsdelay;  //transit time
        poss = true;
      }
      else
      {
        weekday = -1;
      }
    }

    if (poss)
    {
      parent = par;   //valid parent
    }
    else
    {
      return false;
    }
    assert(weekday != -1);
    return true;
  }
};

void Planner::printPlanJourneys(string srcStnName, string destStnName, int maxStopOvers, int maxTransitTime)
{

  // insert your code here
  int srcIndex = (stnNameToIndex.get(srcStnName))->value;
  Util_Queue<InfoNode *> *queue = new Util_Queue<InfoNode *>; // create the q

  // Whenever you need to print a journey, construct a
  // listOfObjects<TrainInfoPerStation *> appropriately, and then
  // use printStationInfo that we had used in Lab 7.
  // printStationInfo is a private member function of
  // the Planner class. It is declared in planner.h and implemented in
  // planner.cpp

  auto outtrav = adjacency[srcIndex].toStations;   //traverse the adjacent stations of source to add the nodes
  while (outtrav != nullptr)
  {
    auto traintrav = outtrav->object->trains;
    while (traintrav != nullptr)
    {

      for (int i = 0; i < 7; i++)
      {
        if (traintrav->object->daysOfWeek[i])
        {   //make a node for each weekday and push to the queue
          InfoNode *tempnode = new InfoNode(traintrav->object, srcIndex, outtrav->object->adjacentStnIndex, i);
          
          queue->push(tempnode);
        }
      }
      traintrav = traintrav->next;
    }
    outtrav = outtrav->next;
  }
  string days[] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
  while (!(queue->isEmpty()))
  {
    auto curr_entry = queue->pop();
    if (curr_entry->object->dest == (stnNameToIndex.get(destStnName))->value)   //destination reached, print the entire journey and DO NOT explore further from this node(desintation can be explored from some other path though)
    {
      cout << "=================================" << endl
           << endl;
      cout << "Journey available ";
      cout << endl;
      auto parent_trav = curr_entry->object;
      cout << "--------NEAR DESTINATION----------" << endl;
      while (parent_trav != nullptr)
      {
        
        cout << "Train number " << parent_trav->info->journeyCode << " from " << stnNameToIndex.getKeyAtIndex(parent_trav->src) << " to " << stnNameToIndex.getKeyAtIndex(parent_trav->dest) << " arrives at ";
        if (parent_trav->info->arrTime != -1)
        {
          cout << parent_trav->info->arrTime;
        }
        else
        {
          cout << "(starts)";
        }
        cout << " departs at ";
        if (parent_trav->info->depTime != -1)
        {
          cout << parent_trav->info->depTime;
        }
        else
        {
          cout << "(ends)";
        }
        cout << " on " << days[parent_trav->weekday] << endl;

        if(parent_trav->layover_time != 0){
          cout << "Layover time: " << parent_trav->layover_time/100 << " hours " << parent_trav->layover_time%100 << " minutes" << endl;
        }

        parent_trav = parent_trav->parent;
      }
      cout << "---------NEAR SOURCE---------" << endl
           << endl;
    }
    else
    {
      auto info_node = curr_entry->object;
      auto outstn_verts = adjacency[info_node->dest].toStations;   //traverse adjancent vertices
      while (outstn_verts != nullptr)
      {
        auto traintrav = outstn_verts->object->trains;   //traverse trains in each edge
        while (traintrav != nullptr)
        {
          for (int j = 0; j < 7; j++)
          {
            if (traintrav->object->daysOfWeek[j])
            {   //create a node for each day
              InfoNode *tempnode = new InfoNode(traintrav->object, info_node->dest, outstn_verts->object->adjacentStnIndex, j);
              //check if the node can be inserted onto the tree
              if (tempnode->addToParent(info_node, stationInfo[info_node->dest], maxStopOvers, maxTransitTime))
              {
                queue->push(tempnode);
              }
              else
              {  //cannot be inserted, delete it to free memory
                delete tempnode;
              }
            }
          }
          traintrav = traintrav->next;
        }
        outstn_verts = outstn_verts->next;
      }
    }
  }
}

#endif