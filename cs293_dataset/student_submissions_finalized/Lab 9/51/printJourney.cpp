#ifndef PLANNER_H
#include "planner.h"
#endif

#ifnded STD_HEADERS_H
#include "std_headers.h"
#endif

using namespace std;

void Planner::printDirectJourneys(string srcStnName, string destStnName)
{

  Entry<int>Start = strNametoIndex(srcStnName);
  vector<int> jrnycodes = strNametoIndex(srcStnName).adjacentnodes();
  start.getjrny();
  
// getting the length and finding the trains connected to them 
//  
  // getting all adjacent nodes;
  // 
  // insert your code here
  
  cout << "This function is to be implemented by you." << endl;
  
  return;
}
