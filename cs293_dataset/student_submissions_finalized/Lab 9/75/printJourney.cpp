#ifndef PLANNER_H
#include "planner.h"
#endif

#ifnded STD_HEADERS_H
#include "std_headers.h"
#endif

#include<vector>
using namespace std;

void Planner::printDirectJourneys(string srcStnName, string destStnName)
{

  // insert your code here
  vector<int> shortest;
  vector<int> marked;
  vector<int> neighbours;
  int n = 10;

  for (int i = 0; i<n;i++ ){
    if (marked[i] != 0){
      int v = shortest.pop_back();

      while (true){
        int adj = neighbours.pop_back();
        if (marked[adj] != 0){
          shortest.push_back();
        }
      }
    }
  }
  
  cout << "This function is to be implemented by you." << endl;
  
  return;
}
