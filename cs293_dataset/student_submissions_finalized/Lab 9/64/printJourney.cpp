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


  //Basic code for BFS
  // vector<bool> visited;
  //   visited.resize(V,false);
 
  //   // Create a queue for BFS
  //   list<int> queue;
 
  //   // Mark the current node as visited and enqueue it
  //   visited[s] = true;
  //   queue.push_back(s);
 
  //   while(!queue.empty())
  //   {
  //       // Dequeue a vertex from queue and print it
  //       s = queue.front();
  //       cout << s << " ";
  //       queue.pop_front();
 
  //       // Get all adjacent vertices of the dequeued
  //       // vertex s. If a adjacent has not been visited,
  //       // then mark it visited and enqueue it
  //       for (auto adjecent: adj[s])
  //       {
  //           if (!visited[adjecent])
  //           {
  //               visited[adjecent] = true;
  //               queue.push_back(adjecent);
  //           }
  //       }
  //   }

    listOfObjects<TrainInfoPerStation*> *direct;
    listOfObjects<TrainInfoPerStation*> *all;
    while(direct!=nullptr){
      int JC;//stores journey codes to maintain direct journey 
      printStationInfo(direct);
      if(all->object->journeyCode==JC){
        printDirectJourneys(all->object->stopSeq, destStnName);
      }

      all = all->next;
    }
     

  // Get the list of journeys as a listOfObjects<TrainInfoPerStation *>
  // for the source station and then we can print it out by invoking
  // printStationInfo that we had used in Lab 7.
  // printStationInfo is a private member function of the Planner class
  // It is declared in planner.h and implemented in planner.cpp
  
  return;
}

#endif
