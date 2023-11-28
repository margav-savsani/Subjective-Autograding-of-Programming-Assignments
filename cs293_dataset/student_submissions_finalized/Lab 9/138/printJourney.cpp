#ifndef PLANNER_H
#include "planner.h"
#endif

#ifnded STD_HEADERS_H
#include "std_headers.h"
#endif

using namespace std;

// planner class has adjacency array each entry of which correspponds to a station
// each entry is a ptr of type Station Adjacency List and corresponds to a particular station
// each Station Adjacency list has a to and from linked list
// each entry of which is StationConnectionInfo which contains a stn index which tells the station number and train info per station which contains the journey code
void Planner::printDirectJourneys(string srcStnName, string destStnName)
{

  // insert your code here


  cout << "This function is to be implemented by you." << endl;

    // Mark all the vertices as not visited
    vector<bool> visited;
    visited.resize(V,false);

    // Create a queue for BFS
    list<int> queue;

    // Mark the current node as visited and enqueue it
    visited[s] = true;
    queue.push_back(s);

    while(!queue.empty())
    {
        // Dequeue a vertex from queue and print it
        s = queue.front();
        cout << s << " ";
        queue.pop_front();

        // Get all adjacent vertices of the dequeued
        // vertex s. If a adjacent has not been visited,
        // then mark it visited and enqueue it
        for (auto adjecent: adj[s])
        {
            if (!visited[adjecent])
            {
                visited[adjecent] = true;
                queue.push_back(adjecent);
            }
        }
    }
  return;
}
