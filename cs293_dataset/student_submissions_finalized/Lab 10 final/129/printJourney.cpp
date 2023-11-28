#ifndef PRINT_JOURNEY_CPP
#define PRINT_JOURNEY_CPP

#ifndef PLANNER_H
#include "planner.h"
#endif

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

using namespace std;

class Queue_BFS
{ // Queue used in BFS stores index of station and journey code
public:
  int index;
  // listOfObjects<int>   *jcode;
  int jcode;
  int stopovers;
  Queue_BFS *next;
  Queue_BFS *parent;
  int parenttochildjcode;
  listOfObjects<TrainInfoPerStation*> *myinfo;
  Queue_BFS()
  {
    index = -1;
    jcode = -1;
    next = nullptr;
    parent = nullptr;
    stopovers = 0;
    parenttochildjcode = 0;
    myinfo = nullptr;
  }
  Queue_BFS(int index, int jcode, int numof)
  {
    this->index = index;
    this->jcode = jcode;
    next = nullptr;
    parent = nullptr;
    myinfo = nullptr;

    stopovers = numof;
    parenttochildjcode = 0;
  }
};
class Predecessor{

};
int transit_time_checker(listOfObjects<TrainInfoPerStation *> *train1, listOfObjects<TrainInfoPerStation *> *train2)
{
  int dept2 = train2->object->depTime;
  int arr1 = train1->object->arrTime;
  int mintransittime = 999999;
  bool a = false;
  // if(dept2 == -1){
  //   return - 1;
  // }
  if (train2->object->arrTime > dept2)
  {
    a = true;
  }
  for (int i = 0; i < 7; i++)
  {
    for (int j = i; j < 7; j++)
    {
      int mini = 0;
      if (!a)
      {

        if (train1->object->daysOfWeek[i] == train2->object->daysOfWeek[j] && train1->object->daysOfWeek[i] == 1)
        {
          // if(j<i){
          //     if(dept2 %100 > arr1%100)
          //       mini = (7+j-i)*24 + dept2/100 - arr1 /100 ;
          //     else
          //       mini = (7 + j - i) *24 + dept2/100 - arr1 /100 -1;

          // }
          if (j == i)
          {
            if (arr1 / 100 > dept2 / 100)
            {
              if (dept2 % 100 > arr1 % 100)
                mini = (7 + j - i) * 24 + dept2 / 100 - arr1 / 100;
              else
                mini = (7 + j - i) * 24 + dept2 / 100 - arr1 / 100 - 1;
            }
            else
            {
              if (dept2 % 100 > arr1 % 100)
                mini = +dept2 / 100 - arr1 / 100;
              else
                mini = dept2 / 100 - arr1 / 100 - 1;
            }
          }
          else
          {
            if (dept2 % 100 > arr1 % 100)
              mini = (j - i) * 24 + dept2 / 100 - arr1 / 100;
            else
              mini = (j - i) * 24 + dept2 / 100 - arr1 / 100 - 1;
          }

          mintransittime = min(mini, mintransittime);
        }
      }
      else
      {
        if (j >= 1)
        {
          if (train1->object->daysOfWeek[i] == train2->object->daysOfWeek[j - 1] && train1->object->daysOfWeek[i] == 1)
          {
            if (j < i)
            {
              if (dept2 % 100 > arr1 % 100)
                mini = (7 + j - i) * 24 + dept2 / 100 - arr1 / 100;
              else
                mini = (7 + j - i) * 24 + dept2 / 100 - arr1 / 100 - 1;
            }
            else if (j == i)
            {
              if (arr1 / 100 > dept2 / 100)
              {
                if (dept2 % 100 > arr1 % 100)
                  mini = (7 + j - i) * 24 + dept2 / 100 - arr1 / 100;
                else
                  mini = (7 + j - i) * 24 + dept2 / 100 - arr1 / 100 - 1;
              }
              else
              {
                if (dept2 % 100 > arr1 % 100)
                  mini = +dept2 / 100 - arr1 / 100;
                else
                  mini = dept2 / 100 - arr1 / 100 - 1;
              }
            }
            else
            {
              if (dept2 % 100 > arr1 % 100)
                mini = (j - i) * 24 + dept2 / 100 - arr1 / 100;
              else
                mini = (j - i) * 24 + dept2 / 100 - arr1 / 100 - 1;
            }

            mintransittime = min(mini, mintransittime);
          }
        }
        else
        {
          if (train1->object->daysOfWeek[i] == train2->object->daysOfWeek[6] && train1->object->daysOfWeek[i] == 1)
          {
            if (j < i)
            {
              if (dept2 % 100 > arr1 % 100)
                mini = (7 + j - i) * 24 + dept2 / 100 - arr1 / 100;
              else
                mini = (7 + j - i) * 24 + dept2 / 100 - arr1 / 100 - 1;
            }
            else if (j == i)
            {
              if (arr1 / 100 > dept2 / 100)
              {
                if (dept2 % 100 > arr1 % 100)
                  mini = (7 + j - i) * 24 + dept2 / 100 - arr1 / 100;
                else
                  mini = (7 + j - i) * 24 + dept2 / 100 - arr1 / 100 - 1;
              }
              else
              {
                if (dept2 % 100 > arr1 % 100)
                  mini = +dept2 / 100 - arr1 / 100;
                else
                  mini = dept2 / 100 - arr1 / 100 - 1;
              }
            }
            else
            {
              if (dept2 % 100 > arr1 % 100)
                mini = (j - i) * 24 + dept2 / 100 - arr1 / 100;
              else
                mini = (j - i) * 24 + dept2 / 100 - arr1 / 100 - 1;
            }

            mintransittime = min(mini, mintransittime);
          }
        }
      }
    }
  }
  return mintransittime;
}
// class storePredecessor{

//   // public:
//   // listOfObjects

// };

void Planner::printPlanJourneys(string srcStnName, string destStnName, int maxStopOvers, int maxTransitTime)
{

  // insert your code here
  // inserting my code
  listOfObjects<TrainInfoPerStation *> *ansstart = nullptr; // head of the final list to be output
  listOfObjects<TrainInfoPerStation *> *ansend = nullptr;   // tail of the final list to be output
  // listOfObjects<TrainInfoPerStation *> *ansinter = nullptr;
  // listOfObjects<TrainInfoPerStation *> *ansintertail = nullptr;

  
  
  // Queue_BFS *maintain = nullptr;
  int s_index = stnNameToIndex.hashValue(srcStnName);
  while (true)
  {
    if (srcStnName == stnNameToIndex.getKeyAtIndex(s_index))
    { // index of the source station

      break;
    }
    s_index = (s_index + 1) % (DICT_SIZE);
  }

  int dest_index = stnNameToIndex.hashValue(destStnName);
  while (true)
  {
    if (destStnName == stnNameToIndex.getKeyAtIndex(dest_index))
    { // index of the destination station

      break;
    }
    dest_index = (dest_index + 1) % (DICT_SIZE);
  }
  Queue_BFS *head = nullptr; // head of the queue
  Queue_BFS *tail = nullptr;
  Queue_BFS *nonhead = nullptr;
  Queue_BFS *nontail  = nullptr;

  bool fact = false;
  // tail of the queue
  listOfObjects<StationConnectionInfo *> *x = adjacency[s_index].toStations; // neighbours of the starting station
  while (x != nullptr)
  {
    
    int a = x->object->adjacentStnIndex; // index of the node adjacent to source
    listOfObjects<TrainInfoPerStation *> *y = x->object->trains;
    while (y != nullptr)
    {

    // listOfObjects<TrainInfoPerStation *> *finalli = new listOfObjects<TrainInfoPerStation*>(y->object);

      if (head == nullptr)
      {

        Queue_BFS *xhead = new Queue_BFS(a, y->object->journeyCode, maxStopOvers); // adding each train to the queue
        xhead->myinfo = new listOfObjects<TrainInfoPerStation*>(y->object);
        head = xhead;
        Queue_BFS *xxhead = new Queue_BFS(a, y->object->journeyCode, maxStopOvers);
        nonhead = xxhead;
        // maintain = xhead;
        tail = xhead;
        nontail = xxhead;

        if (a == dest_index)
        { // checking if adjacent node is the final node
          printStationInfo(xhead->myinfo);
          fact = true;
        }

        // tail = head;
        y = y->next;
      }
      else
      { // just adding to the queue
        // tail = tail->next;
        Queue_BFS *xhead = new Queue_BFS(a, y->object->journeyCode, maxStopOvers);
        Queue_BFS *xxhead = new Queue_BFS(a, y->object->journeyCode, maxStopOvers);
        Queue_BFS *t = head;
        xhead->myinfo = new listOfObjects<TrainInfoPerStation*>(y->object);

        // Queue_BFS* c = maintain;

        // while(t->next != nullptr){
        //   t = t->next;
        // }
        // while(c->next != nullptr){

        // }
        // t->next = xhead;

        tail->next = xhead;
        tail = tail->next;
        nontail->next = xxhead;
        nontail = nontail->next;

        if (a == dest_index)
        {
          fact = true;
          // printStationInfo(xhead->myinfo);
        }
        y = y->next;
      }
    }
    x = x->next;
  }

  while (head != nullptr)
  {                                        // empty queue in BFS
    x = adjacency[head->index].toStations; // index of neighbours of head
    while (x != nullptr)
    {
      // bool found = false; // denotes if a train with a particular journeycode is found in a neighbour of head

      int a = x->object->adjacentStnIndex;                         // index of a neighbouring station
      listOfObjects<TrainInfoPerStation *> *y = x->object->trains; // trains on that particular edge in graph
      while (y != nullptr)
      {
         Queue_BFS *xhead = new Queue_BFS(a, y->object->journeyCode, head->stopovers);
          Queue_BFS *xxhead = new Queue_BFS(a, y->object->journeyCode, head->stopovers);
          nontail->next = xxhead;
          xxhead->parent = head;
          xhead->myinfo = head->myinfo;
          listOfObjects<TrainInfoPerStation*> *garbage = xhead->myinfo;
          while(garbage -> next != nullptr){
            garbage = garbage->next;
          }
          garbage->next = new listOfObjects<TrainInfoPerStation*>(y->object);
          nontail = nontail->next;

          Queue_BFS *t = head;
          // while(t->next!= nullptr){
          //   t = t->next;
          // }
          // t->next = xhead;
          tail->next = xhead;
          tail = tail->next;

        if (y->object->journeyCode == head->jcode)
        { // train code matching
          // tail = tail->next;
          if (a == dest_index)
          {
            // if (ansstart == nullptr)
            // {
            //   listOfObjects<TrainInfoPerStation *> *garb = new listOfObjects<TrainInfoPerStation *>(y->object);
            //   ansstart = garb;
            //   ansend = garb;
            // }
            // else
            // {
            //   listOfObjects<TrainInfoPerStation *> *garb = new listOfObjects<TrainInfoPerStation *>(y->object);
            //   ansend->next = garb;
            //   ansend = ansend->next;
            // }
            // printStationInfo(xhead->myinfo);
            fact = true;
          }
         
          

          // found = true;
          // break;
        }
        else
        {
          if (head->stopovers >= 1)
          {
            listOfObjects<TrainInfoPerStation *> *t = adjacency[head->index].fromStations->object->trains;
            while (t->next!= nullptr)
            {
              if (head->jcode == t->object->journeyCode)
              {
                break;
              }
              t = t->next;
            }

            // cout << transit_time_checker(t, y) << endl;
            // cout << t->object->journeyCode << endl;

            if (transit_time_checker(t, y) != 999999 && transit_time_checker(t, y) < maxTransitTime)
            {

               Queue_BFS *xhead = new Queue_BFS(a, y->object->journeyCode, head->stopovers - 1);
              xhead->myinfo = head->myinfo;
              listOfObjects<TrainInfoPerStation*> *garbage = xhead->myinfo;
              while(garbage -> next != nullptr){
                garbage = garbage->next;
               }
              garbage->next = new listOfObjects<TrainInfoPerStation*>(y->object);

              Queue_BFS *xxhead = new Queue_BFS(a, y->object->journeyCode, head->stopovers - 1);
              nontail->next = xxhead;
              xxhead->parent = head;
              nontail = nontail->next;

              // Queue_BFS *t = head;
              // while(t->next!= nullptr){
              //   t = t->next;
              // }
              // t->next = xhead;
              tail->next = xhead;
              tail = tail->next;


              if (a == dest_index)
              {
                // if (ansstart == nullptr)
                // {
                //   listOfObjects<TrainInfoPerStation *> *garb = new listOfObjects<TrainInfoPerStation *>(y->object);
                //   ansstart = garb;
                //   ansend = garb;
                // }
                // else
                // {
                //   listOfObjects<TrainInfoPerStation *> *garb = new listOfObjects<TrainInfoPerStation *>(y->object);
                //   ansend->next = garb;
                //   ansend = ansend->next;
                // // }
                // printStationInfo(xhead->myinfo);
                fact = true;
              }
             
            }
          }
        }

        y = y->next;
      }
      // if (found == true)
      // { // found a journey-code , it cannot be there in any other neighbour
      //   break;
      // }
      x = x->next;
    }
    head = head->next;
  }
  if (fact == false)
  { // no journeys available
    cout << "No direct journeys available" << endl;
  }
  // else
  // {
  //   // while(ansstart != nullptr){

    // }

  //   while (ansstart != nullptr)
  //   { // just printing
  //     int jcode = ansstart->object->journeyCode;
  //     listOfObjects<TrainInfoPerStation *> *s = stationInfo[s_index];
  //     cout << s << endl;
  //     while (s != nullptr)
  //     {
  //       if (s->object->journeyCode == jcode)
  //       {
  //         listOfObjects<TrainInfoPerStation *> *k = new listOfObjects<TrainInfoPerStation *>(s->object);
  //         k->next = nullptr;
  //         k->prev = nullptr;
  //         // printStationInfo(k);
  //         // cout << k->object->journeyCode<<endl;
  //       }
  //       s = s->next;
  //     }
  //     ansstart = ansstart->next;
  //   }
  //   // printStationInfo(ansstart);
  // }

  // col[s_index] = 2;

  // if(){}

  // else{
  //   cout<<"No direct journeys available"<<endl;
  // }

  return;
}
#endif