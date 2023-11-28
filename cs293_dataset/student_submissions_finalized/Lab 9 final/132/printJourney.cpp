#ifndef PLANNER_H
#include "planner.h"
#endif

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

using namespace std;
struct printJourney
{
  queue<int>q;                       // here i created the new class with memeber function queue 
};

void Planner::printDirectJourneys(string srcStnName, string destStnName)
{
    {
    queue<int> q;
                                                  // here i inserted the src station to queue
    q.push(srcStnName);
    v[u] = true;                                // then i checked it is inserted or not                          
 
    while (!q.empty()) {
 
        int f = q.front();                     //then i started to traviersing 
        q.pop();                                    // and delteing the node i visted 
 
        cout << f << " ";
 
        // Enqueue all adjacent of f and mark them visited
        for (auto i = g[f].begin(); i != g[f].end(); i++) {
            if (!v[*i]) {
                q.push(*i);
                v[*i] = true;
            }
        }
    }
}
    
   
  cout << "This function is to be implemented by you." << endl;
  
  return;
}
