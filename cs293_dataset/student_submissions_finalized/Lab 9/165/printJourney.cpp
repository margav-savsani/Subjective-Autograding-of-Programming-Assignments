#ifndef PLANNER_H
#include "planner.h"
#endif

#ifnded STD_HEADERS_H
#include "std_headers.h"
#endif

using namespace std;

void Planner::printDirectJourneys(string srcStnName, string destStnName)
{

  // insert your code here

  vector<bool> visited;
  visited.resize(V,false);

  // Create a stack for BFS
  vector<int> queue;

  // Mark the current node as visited and enqueue it
  visited[s] = true;
  queue.push_back(s);

  // while(!queue.empty())
  // {
  //     s = queue.front();
  //     queue.pop_front();
  //     for (auto adjecent: adj[s])
  //     {
  //         if (!visited[adjecent])
  //         {
  //             visited[adjecent] = true;
  //             queue.push_back(adjecent);
  //         }
  //     }
  //   }
  //cout << "This function is to be implemented by you." << endl;
  
  return;
}
