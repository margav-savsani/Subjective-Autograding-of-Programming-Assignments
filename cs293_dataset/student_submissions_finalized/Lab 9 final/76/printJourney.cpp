#ifndef PLANNER_H
#include "planner.h"
#endif

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

using namespace std;

bool find(listOfObjects<TrainInfoPerStation *> *t, TrainInfoPerStation *p)
{
  listOfObjects<TrainInfoPerStation *> *temt = t;
  while (temt != NULL)
  {
    if (temt->object->journeyCode != p->journeyCode)
    { // if journeycodes aren"t same we will return false
      return false;
    }
    else
    {
      temt = temt->next; // we iterate if true
      return true;
    }
  }
  return false;
}
void Planner::printDirectJourneys(string srcStnName, string destStnName)
{

  int src = stnNameToIndex.get(srcStnName)->value;   // getting index of source station name
  int dest = stnNameToIndex.get(destStnName)->value; // getting index of dest station name
  listOfObjects<StationConnectionInfo *> *srctr = adjacency[src].toStations;
  listOfObjects<TrainInfoPerStation *> *p = srctr->object->trains;
  listOfObjects<TrainInfoPerStation *> *lstofdir = nullptr; /// list to append direct trains
  listOfObjects<TrainInfoPerStation *> *lstofdir_tail = nullptr;

  while (srctr != NULL)
  {

    if (dest == srctr->object->adjacentStnIndex)
    {
      if (lstofdir == nullptr)
      {

        lstofdir = srctr->object->trains; // list of trains corresponding to index
        lstofdir_tail = lstofdir;
      }
      else
      {

        listOfObjects<TrainInfoPerStation *> *train = srctr->object->trains;
        while (train != nullptr)
        {
          listOfObjects<TrainInfoPerStation *> *add = new listOfObjects<TrainInfoPerStation *>(train->object);
          add->prev = lstofdir_tail; // pointing add_prev to lstofdir_tail
          lstofdir_tail->next = add;
          lstofdir_tail = add;
        }
      }
    }
    else
    {
      while (p->next != nullptr)
      {
        int ind = srctr->object->adjacentStnIndex;//index of adjacent station
        listOfObjects<StationConnectionInfo *> *newsrctr = adjacency[ind].toStations;
        int t = newsrctr->object->adjacentStnIndex;
        listOfObjects<TrainInfoPerStation *> *newp = srctr->object->trains;
        while (newsrctr != NULL)
        {//if the destination is reached we append to the list 
          if (t == dest)
          {
            while (lstofdir == nullptr)
            {
              lstofdir = newp;
              lstofdir_tail = lstofdir;
            }
          }
          else
          {
            while (newp != nullptr)
            {
              listOfObjects<TrainInfoPerStation *> *train = newp;//appending in same process as before
              while (train != nullptr)
              {
                listOfObjects<TrainInfoPerStation *> *add = new listOfObjects<TrainInfoPerStation *>(train->object);
                add->prev = lstofdir_tail;
                lstofdir_tail->next = add;
                lstofdir_tail = add;
              }
            }
          }
        }
        if (find(p, newp->object) == false)//if the journey code isn't same it leaves the current train and goes forward
        {
          newp = newp->next;
          continue;
        }
        else
        {
          t = newsrctr->object->adjacentStnIndex; //iterating by changing index of source
        }
        newsrctr = newsrctr->next;
        p = p->next;
      }
    }
  }

  if (lstofdir->next == NULL)
  {
    cout << "No Direct Trains found" << endl;
  }

  printStationInfo(lstofdir->next);

  return;
}
