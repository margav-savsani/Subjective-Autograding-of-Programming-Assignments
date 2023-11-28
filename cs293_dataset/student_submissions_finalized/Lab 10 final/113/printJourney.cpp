#ifndef PRINT_JOURNEY_CPP
#define PRINT_JOURNEY_CPP

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#include "dictionary.h"
#include "planner.h"
#include "codes.h"

using namespace std;

// new struct to mimic edges of the graph
struct data{
  int jcode;
  TrainInfoPerStation *startinfo;
  TrainInfoPerStation *endinfo;
  int startstncode;
  int endstncode;
  data(int j, int e, int s, TrainInfoPerStation *st, TrainInfoPerStation *et){
    jcode = j;
    endstncode = e;
    startstncode = s;
    startinfo = st;
    endinfo = et;
  } 
  // == operator for checking whether the two edges are same or not
  bool operator==(data d){
    if (d.startstncode == startstncode && d.endstncode == endstncode && d.jcode == jcode){
      return true;
    }
    return false;
  }
};

// function to give name of day corresponding to the index 
string days(int i){
  if (i==0){
    return "Sun";
  }
  if (i==1){
    return "Mon";
  }
  if (i==2){
    return "Tue";
  }
  if (i==3){
    return "Wed";
  }
  if (i==4){
    return "Thu";
  }
  if (i==5){
    return "Fri";
  }
  if (i==6){
    return "Sat";
  }
  return "";
}
  
void Planner::printPlanJourneys(string srcStnName, string destStnName, int maxStopOvers, int maxTransitTime)
{
  // static variables to store recursion depth and the stack/list of objects to be printed if destination station is found
  static int recursion=-1;
  static listOfObjects<data *> *visited=nullptr;

  //to count number of journeys found
  static int counter=0;

  recursion++;
  
  // finding codes of stating and ending station
  int start=stnNameToIndex.get(srcStnName)->value;
  int stop=stnNameToIndex.get(destStnName)->value;

  // base/terminating case of recursion when both start and end are same;
  if (srcStnName == destStnName){
    // finding the head of the list of objects to be printed
    listOfObjects<data *> *temp = visited;
    listOfObjects<data *> *head = nullptr;
    int count=0; // just counting the number of objects to be printed
    while (temp !=nullptr){
      count++;
      head = temp;
      temp = temp->prev;
    }

    //if no list to be printed and we are at top recursive call and counter is zero then nothing the be printed hence we print "no trains available"
    if (head == nullptr){
      recursion--;
      if (counter == 0){
        std::cout << "No trains available" << endl;
      }
      return;
    }

    // looping through all the seven days to print relevent journeys
    for (int i=0; i<7; i++){

      // first checking whether the head has a journey starting on thegiven day or not
      temp = head;
      if (temp->object->startinfo->daysOfWeek[i]){

        int day=0; //counter for number of day in the journey we are 
        bool b=true; // flag to check whether the whole journey till end starting from given day exists of not

        // changing the day counter whenever the transition time between either 2 stations of journey or between the transit time for
        // changing train at a particular staion lies is negative
        int t = temp->object->endinfo->arrTime - temp->object->startinfo->depTime;
        if (t<0){
          day++;
        }

        // looping through the whole list to check the same as last comment
        while (temp->next!=nullptr){
          temp = temp->next;

          // different cases as whether transition is occuring or not as in the case where transition is not occuring then no need to check for transit time
          if (temp->object->jcode != temp->prev->object->jcode){
            int k = temp->object->startinfo->depTime - temp->prev->object->endinfo->arrTime;
            if (k<0){
              day++;
            }
            // If the train not found of the expected day then breaking the loop as nothing to print for this day and so flagging b as false
            if(!temp->object->startinfo->daysOfWeek[(i+day)%7]){
              b = false;
              break;
            }
            k = temp->object->endinfo->arrTime - temp->object->startinfo->depTime;
            if (k<0){
              day++;
            }
          }
          else{
            int k = temp->object->startinfo->depTime - temp->prev->object->endinfo->arrTime;
            if (k<0){
              day++;
            }
            k = temp->object->endinfo->arrTime - temp->object->startinfo->depTime;
            if (k<0){
              day++;
            }
          }
        }
        // if b is still true then we have found the journey with particular day and hence we print it
        if (b == true){
          counter++;
          std::cout << "\n\n====================================================================================================" << endl;
          std::cout << "\nJourney:-\n" << endl;

          // the loops are same as the previous ones used for just checking but this time we will print along with it
          temp = head;
          int day=0;

          //creating new instances to print a journey with single day used in following loop a well
          TrainInfoPerStation *p=new TrainInfoPerStation(temp->object->startinfo->journeyCode,temp->object->startinfo->stopSeq,
                                                        temp->object->startinfo->arrTime, temp->object->startinfo->depTime);
          listOfObjects<TrainInfoPerStation *> *q=new listOfObjects<TrainInfoPerStation *>(p);
          p->daysOfWeek[(i+day)%7]=true;
          std::cout << "At " << stnNameToIndex.getKeyAtIndex(temp->object->startstncode) << endl;
          printStationInfo(q);
          int t = temp->object->endinfo->arrTime - temp->object->startinfo->depTime;
          if (t<0){
            day++;
          }
          //std::cout << "This point was reached too" << endl;
          while (temp->next!=nullptr){
            temp = temp->next;
            if (temp->object->jcode != temp->prev->object->jcode){
              std::cout << "Reaching " << stnNameToIndex.getKeyAtIndex(temp->prev->object->endstncode)
                   << " at time " << temp->prev->object->endinfo->arrTime << " on " << days((i+day)%7) << endl;
              std::cout << "Then changing to following train" << endl;
              int t=temp->object->startinfo->depTime - temp->prev->object->endinfo->arrTime;
              if (t<0){
                t += 2400;
              }
              std::cout << GREEN << "Transit Time :- " << t  << "\n" << endl;
              std::cout << RESET;
              int k = temp->object->startinfo->depTime - temp->prev->object->endinfo->arrTime;
              if (k<0){
                day++;
              }
              TrainInfoPerStation *p=new TrainInfoPerStation(temp->object->startinfo->journeyCode,temp->object->startinfo->stopSeq,
                                                            temp->object->startinfo->arrTime, temp->object->startinfo->depTime);
              listOfObjects<TrainInfoPerStation *> *q=new listOfObjects<TrainInfoPerStation *>(p);
              p->daysOfWeek[(i+day)%7]=true;
              std::cout << "At " << stnNameToIndex.getKeyAtIndex(temp->object->startstncode) << endl;
              printStationInfo(q);
              k = temp->object->endinfo->arrTime - temp->object->startinfo->depTime;
              if (k<0){
                day++;
              }
            }
            else{
              int k = temp->object->startinfo->depTime - temp->prev->object->endinfo->arrTime;
              if (k<0){
                day++;
              }
              TrainInfoPerStation *p=new TrainInfoPerStation(temp->object->startinfo->journeyCode,temp->object->startinfo->stopSeq,
                                                            temp->object->startinfo->arrTime, temp->object->startinfo->depTime);
              listOfObjects<TrainInfoPerStation *> *q=new listOfObjects<TrainInfoPerStation *>(p);
              p->daysOfWeek[(i+day)%7]=true;
              std::cout << "At " << stnNameToIndex.getKeyAtIndex(temp->object->startstncode) << endl;
              printStationInfo(q);
              k = temp->object->endinfo->arrTime - temp->object->startinfo->depTime;
              if (k<0){
                day++;
              }
            }
          }
          std::cout << "Reaching " << stnNameToIndex.getKeyAtIndex(temp->object->endstncode)
                   << " at " << temp->object->endinfo->arrTime << " on " << days((i+day)%7) << endl;
        }
      }
    }

    recursion--;
    return;
  }

  //looping through all the adjacent next stations from source
  listOfObjects<StationConnectionInfo *> *node=adjacency[start].toStations;
  while (node != nullptr){
    
    // looping through all the different trains between two stations
    listOfObjects<TrainInfoPerStation *> *info=node->object->trains;
    while (info != nullptr){
      int maxstop=maxStopOvers; // initializing the number of maximum stops

      // finding the info about the station next from the stationInfo data 
      listOfObjects<TrainInfoPerStation *> *flag = stationInfo[node->object->adjacentStnIndex];
      TrainInfoPerStation *endinginfo = nullptr;
      while (flag != nullptr){
        if (flag->object->journeyCode == info->object->journeyCode){
          endinginfo = flag->object;
          break;
        }
        flag = flag->next;
      }

      // creating a new instance of edge to be stored if not visited already in the current search
      data *d = new data(info->object->journeyCode, node->object->adjacentStnIndex, start, info->object, endinginfo);

      // if previous station exists then checking whether the conditions are satisfied on changing the train of not 
      if (visited != nullptr){
        // if train changed
        if (d->jcode != visited->object->jcode){
          // decresing the max stop counter
          maxstop--;

          //checking for time whether it is compatible with maximum allowed time or not
          int k=d->startinfo->depTime-visited->object->endinfo->arrTime;
          if (k<0){
            if (!(k+2400 <= maxTransitTime && k+2400 > 0)){
              info = info->next;
              continue;
            }
          }
          else{
            if (!(k<=maxTransitTime && k>0)){
              info = info->next;
              continue;
            }
          }
        }
        
      }
      // if max stop counter goes negative then not possible and we continue the search
      if (maxstop < 0){
        info = info->next;
        continue;
      }
      
      // loop to check whether the endge is already visited or not, if visited already then breaking the loop 
      listOfObjects<data *> *temp = visited;
      while (temp !=nullptr){
        if (*(temp->object) == *d){
          break;
        }
        temp = temp->prev;
      }

      // if the edge was not found then continuing the process 
      if (temp == nullptr){
        // two cases as visited list might be empty
        // then creating a new node for this list and adding it to the list then doing the recursive call and then removing the 
        // last added element
        if (visited != nullptr){
          visited->next = new listOfObjects<data *>(d);
          visited->next->prev = visited;
          visited = visited->next;
          printPlanJourneys(stnNameToIndex.getKeyAtIndex(d->endstncode), destStnName, maxstop, maxTransitTime);
          visited = visited->prev;
          delete visited->next;
          visited->next = nullptr;
        }
        else{
          visited = new listOfObjects<data *>(d);
          printPlanJourneys(stnNameToIndex.getKeyAtIndex(d->endstncode), destStnName, maxstop, maxTransitTime);
          delete visited;
          visited = nullptr;
        }
      }
      info = info->next;
    }
    node = node->next;
  }

  // when returning from the function then decreasing the level of recursion
  recursion--; 
  // if at top recursive call and still no journeys found then printing relevent msg 
  if (recursion==-1){
    if (counter == 0){
      std::cout << "No trains available" << endl;
    }
    counter = 0;
    delete[] visited;
  }
  return;
}

#endif
