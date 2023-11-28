#ifndef PRINT_JOURNEY_CPP
#define PRINT_JOURNEY_CPP
#ifndef PLANNER_H
#include "planner.h"
#endif
#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

using namespace std;
void printStationInfo2(listOfObjects<TrainInfoPerStation *> *stnInfoList) //Prints the stations info
{
  listOfObjects<TrainInfoPerStation *> *currList, *expandedList;
  TrainInfoPerStation *currInfo;
  string days[7] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};

  // Expanding information in stnInfoList to get a list of train info
  // in which each element of the list refers to a single day of the
  // week.  This is the list that has to be finally sorted using
  // quicksort.

  currList = stnInfoList;
  expandedList = nullptr;
  int listLength = 0;
  while (currList != nullptr)
  {
    currInfo = currList->object;
    if (currInfo != nullptr)
    {
      // Make as many copies of currInfo as the total count of days in the week
      // when this train runs from/to this station
      int jCode = currInfo->journeyCode;
      int stSeq = currInfo->stopSeq;
      int arrTime = currInfo->arrTime;
      int depTime = currInfo->depTime;

      for (int i = 0; i < 7; i++)
      {
        if (currInfo->daysOfWeek[i])
        {
          TrainInfoPerStation *newExpandedElement = new TrainInfoPerStation(jCode, stSeq, arrTime, depTime);
          if (newExpandedElement == nullptr)
          {

            cerr << "Memory allocation failure." << endl;
            continue;
          }
          newExpandedElement->setDayOfWeek(i);

          listOfObjects<TrainInfoPerStation *> *newExpandedListElement = new listOfObjects<TrainInfoPerStation *>(newExpandedElement);
          if (newExpandedListElement == nullptr)
          {

            cerr << "Memory allocation failure." << endl;
            continue;
          }

          if (expandedList == nullptr)
          {
            expandedList = newExpandedListElement;
          }
          else
          {
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

  // QuicksortSimple(expandedList, 0, listLength-1);

  currList = expandedList;
  while (currList != nullptr)
  {
    currInfo = currList->object;
    if (currInfo != nullptr)
    {
      cout << GREEN << "Day(s): " << RESET;
      for (int i = 0; i < 7; i++)
      {
        if (currInfo->daysOfWeek[i])
          cout << days[i] << " ";
      }
      cout << endl;
      cout << BLUE << "JourneyCode: " << currInfo->journeyCode << RESET << "\t";
      cout << RED << "Arr: " << RESET;
      if (currInfo->arrTime == -1)
      {
        cout << "Starts";
      }
      else
      {
        cout << currInfo->arrTime;
      }
      cout << RED << " Dep: " << RESET;
      if (currInfo->depTime == -1)
      {
        cout << "Ends";
      }
      else
      {
        cout << currInfo->depTime;
      }
      cout << endl;
    }
    currList = currList->next;
  }
  cout << endl;
}

int check_time(TrainInfoPerStation *from, TrainInfoPerStation *to, bool *&days1) //Finds the difference between arrival and departure time of two trains
{
  days1 = new bool[7];
  bool days[7];
  for (int i = 0; i < 7; i++)
  {
    if (from->daysOfWeek[i] && to->daysOfWeek[i])
      days[i] = days1[i] = 1;
    else
      days[i] = days1[i] = 0;
  }

  for (int i = 0; i < 7; i++)
  {
    if (days[i] && (to->depTime - from->arrTime >= 0))
    {
      return to->depTime - from->arrTime;
    }
  }
  return -1;
}
class stop  //Contains Station Index an trains the go through that station
{
public:
  int StnIndex;
  listOfObjects<TrainInfoPerStation *> *trains;
  stop()
  {
    StnIndex = -1;
    trains = nullptr;
  }
  stop(int x, listOfObjects<TrainInfoPerStation *> *y)
  {
    this->StnIndex = x;
    this->trains = y;
  }
};

class listOfObjects1
{
public:
  stop object;
  listOfObjects1 *next;
  listOfObjects1 *prev;

  // Constructor
  listOfObjects1(stop initValue)
  {
    object = initValue;
    next = prev = nullptr;
  }
  listOfObjects1()
  {
    object = *(new stop());
    next = prev = nullptr;
  }

  // Destructor
  ~listOfObjects1() { ; }
};

class listOfObjects2
{
public:
  listOfObjects1 object;
  listOfObjects2 *next;
  listOfObjects2 *prev;

  // Constructor
  listOfObjects2(listOfObjects1 initValue)
  {
    object = initValue;
    next = prev = nullptr;
  }
  listOfObjects2()
  {
    object = *(new listOfObjects1());
    next = prev = nullptr;
  }
  // Destructor
  ~listOfObjects2() { ; }
};


//In a recursive manner conducts a dfs and returns a list of lists of stops(each list starts from a different station on the tostations list of the source station)
void DFS(listOfObjects2 *&final, listOfObjects2 *&efinal, int srci, int desti, listOfObjects<stop> *route, listOfObjects<stop> *eroute, StationAdjacencyList adjacency[])
{

  listOfObjects<StationConnectionInfo *> *curr = adjacency[eroute->object.StnIndex].toStations;
  // eroute->next=new listOfObjects<stop>((eroute->object));
  // eroute->next->prev=eroute;
  while (curr != NULL)
  {
    cout << "fuq\n";
    int index_of_this_station = curr->object->adjacentStnIndex;

    if (index_of_this_station == desti)
    {
      cout << "found\n";

      eroute->next = new listOfObjects<stop>(*(new stop(index_of_this_station, curr->object->trains)));
      eroute->next->prev = eroute;
      cout << "HELLO\n"
           << eroute->next->object.StnIndex;

      if (final == nullptr)
      {
        cout << 69 << endl;
        listOfObjects<stop> *curr_rou = route->next;
        listOfObjects1 *temp = new listOfObjects1(route->object);
        listOfObjects1 *tem = temp;
        while (curr_rou != nullptr)
        {
          temp->next = new listOfObjects1(curr_rou->object);
          curr_rou = curr_rou->next;
          temp = temp->next;
        }

        final = new listOfObjects2(*tem);
        efinal = new listOfObjects2(*tem);
      }
      else
      {
        listOfObjects<stop> *curr_rou = route->next;
        listOfObjects1 *temp = new listOfObjects1(route->object);
        listOfObjects1 *tem = temp;
        while (curr_rou != nullptr)
        {
          temp->next = new listOfObjects1(curr_rou->object);
          curr_rou = curr_rou->next;
          temp = temp->next;
        }

        efinal->next = new listOfObjects2(*tem);
        cout << 69 << endl;
        efinal->next->prev = efinal;
        efinal = efinal->next;
      }
      eroute->next = nullptr;
    }

    else
    {

      eroute->next = new listOfObjects<stop>(*(new stop(index_of_this_station, curr->object->trains)));
      eroute->next->prev = eroute;
      eroute = eroute->next;

      DFS(final, efinal, srci, desti, route, eroute, adjacency);
      eroute->next = nullptr;
    }

    curr = curr->next;
  }
  return;
}

//Recursively prints the required output.
bool print(listOfObjects2 *final, listOfObjects1 *pos, listOfObjects1 *top, int maxStopOvers, int maxTransitTime, int desti)
{
  static int nstops = 0, route_no = 0;
  static listOfObjects2 *curr_start_st = final;
  static listOfObjects1 *curr_stop = &(final->object);
  if (pos == nullptr)
  {
    listOfObjects<TrainInfoPerStation *> *currTrain = curr_stop->object.trains;
    while (currTrain != nullptr)
    {
      stop temp(curr_stop->object.StnIndex, currTrain);

      pos = new listOfObjects1(temp);
      listOfObjects1 *temp2 = pos;
      listOfObjects1 *top = pos;
      listOfObjects1 *temp1 = curr_stop;
      curr_stop = curr_stop->next;
      print(final, pos, top, maxStopOvers, maxTransitTime, desti);
      pos = temp2;
      top = pos;
      curr_stop = temp1;
      currTrain = currTrain->next;
    }
  }
  else
  {
    if (top->object.StnIndex = desti)
    {
      listOfObjects1 *curr = pos;
      int jrnycode = curr->object.trains->object->journeyCode;
      listOfObjects<TrainInfoPerStation *> *x = pos->object.trains;
      printStationInfo2(x);
      while (curr->next != nullptr)
      {
        if (curr->next->object.trains->object->journeyCode = jrnycode)
        {
          listOfObjects<TrainInfoPerStation *> *x = curr->object.trains;
          printStationInfo2(x);
        }
        else
        {
          bool *y = nullptr;
          cout << "transit time:" << check_time(curr->object.trains->object, curr->next->object.trains->object, y) << endl;
          cout << "Train Changeover at station" << stnNameToIndex.getKeyAtIndex(curr->next->object.StnIndex) << endl;
          listOfObjects<TrainInfoPerStation *> *x = curr->object.trains;
          printStationInfo2(x);
        }

        curr = curr->next;
      }
    }
    else
    {
      TrainInfoPerStation *t1 = top->object.trains->object;
      int code = t1->journeyCode;
      listOfObjects<TrainInfoPerStation *> *currTrain = curr_stop->object.trains;

      while (currTrain != nullptr)
      {
        if (code == currTrain->object->journeyCode)
        {
          listOfObjects1 *temp2 = pos, *temp3 = top;
          stop x(curr_stop->object.StnIndex, currTrain);
          top->next = new listOfObjects1(x);
          listOfObjects1 *temp1 = curr_stop;
          curr_stop = curr_stop->next;
          print(final, pos, top, maxStopOvers, maxTransitTime, desti);
          curr_stop = temp1;
          pos = temp2;
          top = temp3;
        }
        else if (nstops < maxStopOvers)
        {
          bool *days = nullptr;
          int time = check_time(t1, (currTrain->object), days);
          if (time < 0)
            continue;
          time = time / 100;
          if (time > maxTransitTime)
          {
            continue;
          }
          else
          {
            listOfObjects1 *temp2 = pos, *temp3 = top;

            stop x(curr_stop->object.StnIndex, currTrain);
            top->next = new listOfObjects1(x);
            listOfObjects1 *temp1 = curr_stop;
            curr_stop = curr_stop->next;
            nstops++;
            print(final, pos, top, maxStopOvers, maxTransitTime, desti);
            nstops--;
            curr_stop = temp1;
            pos = temp2;
            top = temp3;
          }
        }
        currTrain = currTrain->next;
      }
    }
  }
}

void Planner::printPlanJourneys(string srcStnName, string destStnName, int maxStopOvers, int maxTransitTime)
{

  cout << "This function is to be implemented by you." << endl;
  int srci = stnNameToIndex.hashValue(srcStnName), desti = stnNameToIndex.hashValue(destStnName);
  while (true)
  {
    if (srcStnName == stnNameToIndex.getKeyAtIndex(srci))
      break;
    srci = (srci + 1) % DICT_SIZE;
  }

  while (true)
  {
    if (destStnName == stnNameToIndex.getKeyAtIndex(desti))
      break;
    desti = (desti + 1) % DICT_SIZE;
  }

  if (desti == srci)
  {
    cout << "No direct journeys available!\n";
    return;
  }

  listOfObjects<TrainInfoPerStation *> *ans = nullptr; // list which contains the correct stations
  listOfObjects<TrainInfoPerStation *> *end = nullptr; // points to the end of the "ans" list so that it becomes easy to add new element
  listOfObjects2 *final = nullptr, *efinal = nullptr;

  listOfObjects<stop> *routes[10];
  int nroutes = 0;
  // int ind[DICT_SIZE], i = 0;    // Stores indexes of prospective intermediate stations,i is no of stations found.

  listOfObjects<StationConnectionInfo *> *curr = adjacency[srci].toStations;
  cout << "x\n";
  while (curr != NULL) // parsing through tostations of source station to find direct journeys and initialize "ind" and "jrnycodes"
  {

    int index_of_this_station = curr->object->adjacentStnIndex;
    if (index_of_this_station == desti)
    {
      listOfObjects<TrainInfoPerStation *> *curr_train = curr->object->trains;
      while (curr_train != nullptr)
      {

        if (ans == nullptr)
        {
          ans = new listOfObjects<TrainInfoPerStation *>(curr_train->object);
          end = ans;
          curr_train = curr_train->next;
          continue;
        }

        end->next = new listOfObjects<TrainInfoPerStation *>(curr_train->object);
        end = end->next;

        curr_train = curr_train->next;
      }
      curr = curr->next;
      continue;
    }

    else
    {
      listOfObjects<TrainInfoPerStation *> *curr_train = curr->object->trains;
      // ind[i] = index_of_this_station;
      stop temp(index_of_this_station, curr->object->trains);
      routes[nroutes] = new listOfObjects<stop>(temp);
      nroutes++;
      // i++;
    }

    curr = curr->next;
  }
  cout << nroutes << "y\n";
  for (int k = 0; k < nroutes; k++)
  {
    DFS(final, efinal, srci, desti, routes[k], routes[k], adjacency);
  }
  cout << "z\n";
  // Using recursion finds indirect journeys and update "ans" list which we pass by reference
  //  Get the list of journeys as a listOfObjects<TrainInfoPerStation *>
  //  for the source station and then we can print it out by invoking
  //  printStationInfo that we had used in Lab 7.
  //  printStationInfo is a private member function of the Planner class
  //  It is declared in planner.h and implemented in planner.cpp
  if (final == nullptr)
  {
    cout << "yep!\n";
    return;
  }
  if (ans == nullptr)
  {
    if (final == nullptr)
    {
      cout << "No journeys available!\n";
      return;
    }
  }
  else
  {
    cout << "Direct Journeys:";
    printStationInfo(ans);
  }
  listOfObjects2 *temp = final;
  int st = 1;

  print(final,nullptr,nullptr,maxStopOvers,maxTransitTime,desti);

  return;
}

#endif