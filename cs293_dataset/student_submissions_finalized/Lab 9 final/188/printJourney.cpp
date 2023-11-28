#ifndef PLANNER_H
#include "planner.h"
#endif

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

using namespace std;

template <typename T>
listOfObjects<T> *getLast(listOfObjects<T> *queue)
{
  listOfObjects<T> *last = queue;
  if (last == nullptr)
    return nullptr;
  while (last->next != nullptr)
  {
    last = last->next;
    // //cout<< "last " << last->object<<endl;
  }
  return last;
}
// listOfObjects<TrainInfoPerStation *> *getLast2(listOfObjects<TrainInfoPerStation *> *queue)
// {
//   listOfObjects<TrainInfoPerStation *> *last = queue;
//   if (last == nullptr)
//     return nullptr;
//   while (last->next != nullptr)
//   {
//     last = last->next;
//   }
//   return last;
// }
bool find_obj(listOfObjects<TrainInfoPerStation *> *queue, listOfObjects<TrainInfoPerStation *> *obj)
{
  listOfObjects<TrainInfoPerStation *> *last = queue;
  while (last != nullptr)
  {
    // //cout << last->object->journeyCode << " " << obj->object->journeyCode << endl;
    if (last->object->journeyCode == obj->object->journeyCode)
    {
      return true;
    }
    last = last->next;
  }
  return false;
}
bool find_it(listOfObjects<int> *queue, listOfObjects<int> *obj)
{
  listOfObjects<int> *last = queue;
  while (last != nullptr)
  {
    // //cout << last->object->journeyCode << " " << obj->object->journeyCode << endl;
    if (last->object == obj->object)
    {
      return true;
    }
    last = last->next;
  }
  return false;
}
void Planner::printDirectJourneys(string srcStnName, string destStnName)
{
  // insert your code here
  listOfObjects<TrainInfoPerStation *> *directJourneys = nullptr;
  Entry<int> *srcstn = stnNameToIndex.get(srcStnName);
  int srcstnIndex = srcstn->value;
  //cout<<srcstnIndex<<endl;

  Entry<int> *deststn = stnNameToIndex.get(destStnName);
  int deststnIndex = deststn->value;
  // trains_btw_stations is a pointer running through linked list of trains(trainInfoperStation)
  // listOfObjects<TrainInfoPerStation *> *trains_btw_stations = adjacency[srcstnIndex].toStations->object->trains;

  // linked list queue, which is initialized to list of trains in first adjacent station
  listOfObjects<int> *queue_trains = new listOfObjects(srcstnIndex);
  // adj_stns is a pointer running through linked list of toStations(stationconnectionInfo)

  listOfObjects<int> *jrnyqueue = nullptr;

  while (queue_trains != nullptr)
  {
    int index = queue_trains->object;
    listOfObjects<StationConnectionInfo *> *adj_stns = adjacency[index].toStations;
    //cout << "hi1" << endl;
    while (adj_stns != nullptr)
    {
      // //cout << "hi2" << endl;
      listOfObjects<TrainInfoPerStation *> *trains_btw_stations = adj_stns->object->trains;
      int adjindex = adj_stns->object->adjacentStnIndex;
      while (trains_btw_stations != nullptr)
      {
        // //cout << "hi3" << endl;
        listOfObjects<TrainInfoPerStation *> *next_trains = adjacency[adjindex].toStations->object->trains;
        if (adjindex == deststnIndex)
        {
          listOfObjects<int> *code = new listOfObjects(trains_btw_stations->object->journeyCode);
          if (jrnyqueue == nullptr)
          {
            // //cout << "ifelse" << endl;
            jrnyqueue = code;
          }
          else
          {
            if (!find_it(jrnyqueue, code))
            {
              listOfObjects<int> *tp = getLast<int>(jrnyqueue);
              //cout << tp->object << " " << code->object << endl;
              tp->next = code;
            }
          }
        }
        else if (find_obj(next_trains, trains_btw_stations))
        {
          // //cout << "endnextelse" << endl;
          listOfObjects<int> *last_queue = getLast<int>(queue_trains);
          last_queue->next = new listOfObjects(adj_stns->object->adjacentStnIndex);
          // //cout << "nextelse" << endl;
        }
        trains_btw_stations = trains_btw_stations->next;
      }
      adj_stns = adj_stns->next;
    }
    // //cout << queue_trains->object << endl;
    queue_trains = queue_trains->next;
  }

  listOfObjects<StationConnectionInfo *> *train_src_info = adjacency[srcstnIndex].toStations;
  //cout<<srcstnIndex<<endl;
  while (train_src_info != nullptr)
  {
    // //cout << "hi2" << endl;
    listOfObjects<TrainInfoPerStation *> *trains_src = train_src_info->object->trains;
    while (trains_src != nullptr)
    {
      if (jrnyqueue->object == trains_src->object->journeyCode)
      {
        listOfObjects<TrainInfoPerStation *> *code = new listOfObjects(trains_src->object);
        if (directJourneys == nullptr)
        {
          directJourneys = code;
        }
        else
        {
          listOfObjects<TrainInfoPerStation *> *ptr = getLast(directJourneys);
          ptr->next = code;
        }
        // printStationInfo(directJourneys);
        jrnyqueue = jrnyqueue->next;
      }
      trains_src = trains_src->next;
    }
    if (jrnyqueue == nullptr)
      break;
    train_src_info = train_src_info->next;
  }

  if (directJourneys == nullptr)
    cout << "No Direct Journeys" << endl;
  else
    printStationInfo(directJourneys);

  // Get the list of journeys as a listOfObjects<TrainInfoPerStation *>
  // for the source station and then we can print it out by invoking
  // printStationInfo that we had used in Lab 7.
  // printStationInfo is a private member function of the Planner class
  // It is declared in planner.h and implemented in planner.cpp
  return;
}
