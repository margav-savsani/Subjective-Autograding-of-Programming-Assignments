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
  
  cout << "This function is to be implemented by you." << endl;
  int i=0;
  while (true){
    if(adjacency[i]==nullptr) break;
    i++;
  }
  int V=i;
  list<int> queue;
  bool *visited = new bool[V];
  for(int i = 0; i < V; i++){
        visited[i] = false;
    while(!queue.empty())
    {

        s = queue.front();
        cout << s << " ";
        queue.pop_front();
  
   
        for (i = adj[s].begin(); i != adj[s].end(); ++i)
        {
            if (!visited[*i])
            {
                visited[*i] = true;
                queue.push_back(*i);
            }
        }
    }
  }
  // Get the list of journeys as a listOfObjects<TrainInfoPerStation *>
  // for the source station and then we can print it out by invoking
  // printStationInfo that we had used in Lab 7.
  // printStationInfo is a private member function of the Planner class
  // It is declared in planner.h and implemented in planner.cpp
  
  return;
}

#endif
