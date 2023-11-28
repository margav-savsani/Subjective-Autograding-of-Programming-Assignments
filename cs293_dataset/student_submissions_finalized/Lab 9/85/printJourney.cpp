#ifndef PRINT_JOURNEY_CPP
#define PRINT_JOURNEY_CPP

#ifndef PLANNER_H
#include "planner.h"
#endif

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

using namespace std;
void PLanner::BFS(int s)
{
    
    vector<bool> visited;
    visited.resize(V,false);
 
    
    list<int> queue;
 
   
    visited[s] = true;
    queue.push_back(s);
 
    while(!queue.empty())
    {
        
        s = queue.front();
        cout << s << " ";
        queue.pop_front();
 
      
        for (auto adjecent: adj[s])
        {
            if (!visited[adjecent])
            {
                visited[adjecent] = true;
                queue.push_back(adjecent); }
        }
    }
}
 
void Planner::printDirectJourneys(string srcStnName, string destStnName)
{

 
  
  return;
}

#endif
