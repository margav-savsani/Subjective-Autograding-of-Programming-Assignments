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
  
  cout << "This function is to be implemented by you." << endl;
  
  // start
  myPlanner->displayWelcomeMessage();

  do {
    bool continueMenu = myPlanner->displayMenuAndAct();

    if (!continueMenu) {
      delete myPlanner;
      return 0;
    }
    else {
      continue;
    }
  } while (true);
  //end
  return;
}
