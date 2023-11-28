#ifndef PRINT_JOURNEY_CPP
#define PRINT_JOURNEY_CPP

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef PLANNER_H
#include "planner.h"
#endif

#include <iostream>
#include <list>
#include <vector>
using namespace std;

class TrainInfoperStation
{
public:
  int jcode;            // same as train number
  unsigned short stpSq; // sequence of this station's stop in
  string name;          // itinerary of train, i.e. 1st stop in journey
                        // or 2nd stop in journey or ...
  bool daysOfWeek[7];   // Days of week when this train travels
                        // to/from this station
  int aTm;              // Arrival time at station; -1 if train starts from here
  int dTm;              // Departure time from station; -1 if train ends here

public:
  TrainInfoperStation(string name, int jcode, unsigned short stpSq, int aTm, int dTm)
  { 
    for (int i = 0; i < 7; i++)
    {
      daysOfWeek[i] = false;
    }
    jcode = jcode;
    aTm = aTm;
    dTm = dTm;
    name = name;
    stpSq = stpSq;
  }

  ~TrainInfoperStation() { ; }
  void resetDayOfWeek(int m)
  {
    if ((m < 7) && (m >= 0))
      daysOfWeek[m] = false;
  }
  void setDayOfWeek(int k)
  {
    if ((k < 7) && (k >= 0))
      daysOfWeek[k] = true;
  }
};

int Transition_time(TrainInfoperStation *newjrny, TrainInfoperStation *tojrny)
{
  if (newjrny->jcode == -9)
  {
    return -1;
  }
  int newjrny_day, tojrny_day;
  int l = 0 ;
  while(l<7)
  {
    if (tojrny->daysOfWeek[l])
    {
      tojrny_day = l;
      break;
    }
    l++ ;
  }
  l = l - 7 ;
  while(l<7)
  {
    if (newjrny->daysOfWeek[l])
    {
      newjrny_day = l;
      break;
    }
    l++ ;
  }
  int t_1 = newjrny->aTm ;
  int t_2 = tojrny->aTm ;
  int t_3 = newjrny_day - tojrny_day ;
  int answer ;
  answer = t_1 - t_2 + 2400*t_3; 
  return answer ;
}


int Journey_duration(TrainInfoperStation *initial_stn, TrainInfoperStation *final_stn)
{
  int starting = 0;
  int ending = 0;
  int k = 0 ;
  while(k<7)
  {
    if (final_stn->daysOfWeek[k])
    {
      ending = k;
      break;
    }
    k++ ;
  }
  k = k - 7 ;
  while(k<7)
  {
    if (initial_stn->daysOfWeek[k])
    {
      starting = k;
      break;
    }
  }
  
  int t1 = final_stn->aTm;
  int t2 = initial_stn->dTm;
  int t3 = ending - starting;
  return t1 - t2 + 24 * t3;
}


listOfObjects<TrainInfoPerStation *> *expanded_trains(listOfObjects<TrainInfoPerStation *> *stnInfoList)
{
  listOfObjects<TrainInfoPerStation *> *currentList, *expandedList;
  expandedList = nullptr;
  currentList = stnInfoList;

  TrainInfoPerStation *currentInfo;

  while (currentList != nullptr)
  {
    int l = 0 ;
    currentInfo = currentList->object;
    while(l<7)
    {
      if (currentInfo->daysOfWeek[l])
      { 
        int arrTime = currentInfo->arrTime ;
        int depTime = currentInfo->depTime ;
        int jCode = currentInfo->journeyCode ;
        int stSeq = currentInfo->stopSeq ;
        TrainInfoPerStation *newExpandedElement = new TrainInfoPerStation(jCode, stSeq, arrTime, depTime);
        newExpandedElement->setDayOfWeek(l);

        listOfObjects<TrainInfoPerStation *> *newExpandedListElement = new listOfObjects<TrainInfoPerStation *>(newExpandedElement);

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
      }
      l = l + 1 ;
    }
    currentList = currentList->next;
  }
  return expandedList;
}

int terminates(listOfObjects<TrainInfoperStation *> *jny)
{ int result = 0;
  listOfObjects<TrainInfoperStation *> *previous ;
  previous = jny;
  listOfObjects<TrainInfoperStation *> *curr ;
  curr = previous->next->next;
  while (curr->object->jcode != -9)
  { int a = previous->object->jcode ;
    int b = curr->object->jcode ;
    int c = a - b ;
    if (c != 0)
    {
      result++;
    }
    previous = curr;
    listOfObjects<TrainInfoperStation *> *current ;
    current = curr->next ;
    curr = curr->next->next;
  }
  return result;
}



class Graph 
{ 
    int V;    // No. of vertices  
    // Pointer to an array containing 
    // adjacency lists 
    list<int> *adj; 
  
    // A recursive function used by printAllPaths()
    void printAllPathsUtil(int v1, int v2, bool visited[], int path[], int index); 
public: 
    Graph(int V);   // Constructor 
    bool pathExist; //variable to indicate if path exist or not
    // function to add an edge to graph 
    void addEdge(int v, int w); 
    void printAllPaths(int v1, int v2);
    
}; 
  
Graph::Graph(int V) 
{ 
    this->V = V; 
    adj = new list<int>[V]; 
} 
  
void Graph::addEdge(int v, int w) 
{ 
    adj[v].push_back(w); // Add w to v’s list. 
} 

// A recursive function to print all paths from 'v1' to 'v2'. 
// visited[] keeps track of vertices in current path. 
// path[] stores actual vertices and index is current 
// index in path[] 
void Graph::printAllPathsUtil(int v1, int v2, bool visited[], int path[], int index) 
{ 
    // Mark the current node as visited and store it in path[] 
    visited[v1] = true;
    path[index]=v1;
    index++;
    // If current vertex is same as v2, then print 
	// current path[] 
    if(v1==v2){
        int i;
        if(!pathExist)
            cout<<"Following are the paths between "<<path[0]<<" and "<<path[index-1]<<endl;
        pathExist=true;
        for(i=0;i<index-1;i++)
            cout<<path[i]<<"->";
        cout<<path[i]<<endl;
    }
    else{ // If current vertex is not v2 
    // Recur for all the vertices adjacent 
    // to this vertex 
        list<int>::iterator i; 
        for (i = adj[v1].begin(); i != adj[v1].end(); ++i) 
            if (!visited[*i]) 
                printAllPathsUtil(*i, v2, visited, path, index); 
    }
    // Remove current vertex from path[] and mark it as unvisited 
    index--;
    visited[v1]=false;
} 
  
// DFS traversal of the vertices reachable from v. 
// It uses recursive prinAllPathsUtil 
void Graph::printAllPaths(int v1, int v2) 
{ 
    // Mark all the vertices as not visited 
    bool *visited = new bool[V]; 
    for (int i = 0; i < V; i++) 
        visited[i] = false;
        
    // Create an array to store paths 
    int *path = new int[V];
    
    // Initialize path[] as empty 
    int index = 0;
    
    pathExist=false;
    
    // Call the recursive helper function to print all paths 
    printAllPathsUtil(v1,v2,visited,path,index);
    
   
} 

void find(listOfObjects<StationConnectionInfo *> *h, int a, listOfObjects<TrainInfoPerStation *> *u, int check, listOfObjects<StationConnectionInfo *> *e, StationAdjacencyList *adjacency)
{
  listOfObjects<StationConnectionInfo *> *k = h;
  listOfObjects<StationConnectionInfo *> *o = e;
  listOfObjects<TrainInfoPerStation *> *d = u;
  while (k != nullptr)
  {
    if (k->object->adjacentStnIndex == a)
    {
      if (check == 0)
      {
        listOfObjects<TrainInfoPerStation *> *s = o->object->trains;
        while (s != nullptr)
        {
          d->next = new listOfObjects<TrainInfoPerStation *>(s->object);
          d = d->next;
          s = s->next;
        }
      } // Here this condition specifies whether the destination is connected directly to the start or it is connected indirectly. If check=0 the destionation is found
      // in the adjacent list of start.
      else
      {
        listOfObjects<TrainInfoPerStation *> *p = k->object->trains;
        while (p != nullptr)
        {
          if (p->object->journeyCode == check)
          {
            if (d->next == nullptr)
            {
              d->next = new listOfObjects<TrainInfoPerStation *>(p->object);
              d = d->next;
              break;
            }
            else
            {
              while (d->next != nullptr)
              {
                d = d->next;
              }
            }
          }
          else
          {
            p = p->next;
          }
        }
        // In this part we will add only one train code to the list of direct journeys.
      }
    }
    else
    {
      int g = k->object->adjacentStnIndex;
      listOfObjects<TrainInfoPerStation *> *y = o->object->trains;
      int z;
      while (y != nullptr)
      { // This loop helps to go through all the trains to given adjacent station of the given source station
        if (check == 0)
        {
          z = y->object->journeyCode;
        }
        else
        {
          z = check;
        } // Here if check is zero then z takes the journey code value of that object or else check itself acts as the journey code that should be assigned to z.
        listOfObjects<StationConnectionInfo *> *t = adjacency[g].toStations;
        while (t != nullptr)
        { // This loop helps to go through all the trains between the adjacent station to starting station and their adjacent stations.
          listOfObjects<TrainInfoPerStation *> *j = t->object->trains;
          while (j != nullptr)
          {
            if (j->object->journeyCode == z)
            {
              break;
            }
            j = j->next;
          }
          if (j != nullptr)
          {
            find(t, a, d, z, o, adjacency);
          }
          t = t->next;
        }
        // check=0;
        if (check == 0)
        {
          y = y->next;
        }
        else
          break;
      }
    }
    k = k->next;
    if (check == 0)
    {
      o = o->next;
    }
  } // I have done this function recursively to traverse through all the stations and find the all possible direct journeys from given start to end.
  return;
}

void Planner::printPlanJourneys(string srcStnName, string destStnName, int maxStopOvers, int maxTransitTime)
{ // insert your code here
  if (maxStopOvers == 0 && maxTransitTime == 0)
  {
    int start = stnNameToIndex.get(srcStnName)->value;
    int end = stnNameToIndex.get(destStnName)->value;
    listOfObjects<StationConnectionInfo *> *tolist1 = adjacency[start].toStations;
    TrainInfoPerStation *pil = new TrainInfoPerStation(0, 0, 0, 0);
    listOfObjects<TrainInfoPerStation *> *l = new listOfObjects<TrainInfoPerStation *>(pil);
    find(tolist1, end, l, 0, tolist1, adjacency);
    if (l->next != nullptr)
    {
      printStationInfo(l->next);
    }
    else
    {
      cout << "No Journeys from "<<srcStnName<<" to "<<destStnName<< endl;
    }
  }
  else {

    int start = stnNameToIndex.get(srcStnName)->value;
    int end = stnNameToIndex.get(destStnName)->value;
    listOfObjects<StationConnectionInfo *> *tolist1 = adjacency[start].toStations;
    TrainInfoPerStation *pil = new TrainInfoPerStation(0, 0, 0, 0);
    listOfObjects<TrainInfoPerStation *> *l = new listOfObjects<TrainInfoPerStation *>(pil);
    find(tolist1, end, l, 0, tolist1, adjacency);
    if (l->next != nullptr)
    {
      printStationInfo(l->next);
    }
    else
    {
      cout << "No Direct Journeys from "<<srcStnName<<" to "<<destStnName<< endl;
    }

    Graph g(numStations);
    g.addEdge(start, end);
    g.addEdge(0, 2);
    g.addEdge(0, 3);
    g.addEdge(2, 0);
    g.addEdge(2, 1);
    g.addEdge(1, 3);



  }
}

#endif
