#ifndef PRINT_JOURNEY_CPP
#define PRINT_JOURNEY_CPP

#ifndef PLANNER_H
#include "planner.h"
#endif

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

using namespace std;

void Planner::printDirectJourneys(string srcStnName, string destStnName)
{

  // insert your code here
  listOfObjects<StationConnectionInfo *> *stations = adjacency[stnNameToIndex.get(srcStnName)->value].toStations;
  listOfObjects<TrainInfoPerStation *> *ans = nullptr;
  listOfObjects<StationConnectionInfo *> *current1 = nullptr;
  // listOfObjects<TrainInfoPerStation *> *current2=nullptr;
  listOfObjects<TrainInfoPerStation *> *journeys = nullptr;
  listOfObjects<TrainInfoPerStation *> *temp = nullptr;
  while (stations != NULL)
  {
    // cout<<stnNameToIndex.getKeyAtIndex(stations->object->adjacentStnIndex)<<endl;
    journeys = stations->object->trains;
    while (journeys != NULL)
    {
      // cout<<"jc:"<<journeys->object->journeyCode<<endl;
      bool dest_found = false;
      string curr_stn = srcStnName;
      while (true)
      { // cout<<"curr: "<<curr_stn<<endl;
        // cout<<"jc:"<<journeys->object->journeyCode<<endl;
        // cout<<"yo\n";
        bool jc_found = false;
        current1 = adjacency[stnNameToIndex.get(curr_stn)->value].toStations;
        // cout<<"jc:"<<journeys->object->journeyCode<<endl;
        while (current1 != NULL)
        {
          // cout<<"jc:"<<journeys->object->journeyCode<<endl;
          // cout<<"current1: "<<stnNameToIndex.getKeyAtIndex(current1->object->adjacentStnIndex)<<endl;
          listOfObjects<TrainInfoPerStation *> *current2 = current1->object->trains;
          // cout<<"jc:"<<journeys->object->journeyCode<<endl;
          while (current2 != NULL)
          {
            // cout<<"jc:"<<journeys->object->journeyCode<<endl;
            // cout<<"current2: "<<current2->object->journeyCode<<endl;
            if (journeys->object->journeyCode == current2->object->journeyCode)
            {
              // cout<<"check\n";
              jc_found = true;
              curr_stn = stnNameToIndex.getKeyAtIndex(current1->object->adjacentStnIndex);
              // cout<<"tin_jc:"<<journeys->object->journeyCode<<endl;
              if (curr_stn == destStnName)
              {
                // cout<<"boop!!\n"<<endl;
                dest_found = true;
                int jCode = current2->object->journeyCode;
                int stSeq = current2->object->stopSeq;
                int arrTime = current2->object->arrTime;
                int depTime = current2->object->depTime;

                TrainInfoPerStation *newent = new TrainInfoPerStation(jCode, stSeq, arrTime, depTime);
                for (int i = 0; i < 7; i++)
                {
                  if (journeys->object->daysOfWeek[i])
                  {
                    newent->setDayOfWeek(i);
                  }
                }
                listOfObjects<TrainInfoPerStation *> *temp = new listOfObjects<TrainInfoPerStation *>(newent);
                if (ans == nullptr)
                {
                  ans = temp;
                }
                else
                {
                  temp->next = ans;
                  ans = temp;
                }
                // TrainInfoPerStation newjrny = *(journeys->object);

                // temp = new listOfObjects<TrainInfoPerStation *>(&newjrny);

                // temp->next = ans;

                // ans = temp;
              }
              // cout<<"ha_jc:"<<journeys->object->journeyCode<<endl;
              break;
            }
            current2 = current2->next;
            // cout<<"bhua_jc:"<<journeys->object->journeyCode<<endl;
          }
          if (jc_found)
          {
            break;
          }
          current1 = current1->next;
          // cout<<"yo_jc:"<<journeys->object->journeyCode<<endl;
        }
        if (!jc_found || dest_found)
        {
          // cout<<"WTH!!"<<endl;
          break;
        }
        // cout<<"ku_jc:"<<journeys->object->journeyCode<<endl;
      }
      // cout<<"kka\n";

      journeys = journeys->next;
    }

    stations = stations->next;
  }


  if (ans != NULL)
  {
    printStationInfo(ans);
  }
  else
  {
    cout << "No direct journeys available" << endl;
  }

  return;
}

#endif
