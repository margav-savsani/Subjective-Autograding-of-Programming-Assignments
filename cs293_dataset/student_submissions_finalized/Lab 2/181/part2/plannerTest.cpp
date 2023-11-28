#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fstream>
#include "planner.h"
using namespace std;

/*

In interactive mode you can give commands '
  QUIT
  INS <key> <value>
  DEL <key>
  FIND <key>

*/

void Plannerhandler(Planner &planner)
{
  for (int i = 0; i >= 0; i++)
  {
    char input[32];
    cout << ">>> ";
    cin >> input;
    if (strcmp(input, "EXIT") == 0)
    {
      break;
    }

    // INS <key> <value>
    if (strcmp(input, "ADD") == 0)
    {
      char station1[32];
      char station2[32];
      Entry data;
      cin >> station1;
      float starttime;
      cin >> starttime;
      data.starttime = starttime;
      cin >> station2;
      float endtime;
      cin >> endtime;
      data.endtime = endtime;
      strcpy(data.station1, station1);
      strcpy(data.station2, station2);
      int freeIndexData = planner.findFreeIndex(station1);
      if (freeIndexData >= 0)
      {
        planner.put(data);
      }
    }
    // FIND <key>
    else if (strcmp(input, "QUERY_STATION") == 0)
    {
      char station[32];
      cin >> station; // start station
      float starttime;
      cin >> starttime;
      Entry *entry = planner.get(station); // getting array of trains at start station
      int j = 0;
      for (int i = 0; i < planner.getsize(station); i++)
      {
        if (entry[i].starttime >= starttime)
        {
          cout << entry[i].starttime;
          cout << "  " << entry[i].station2 << endl;
          j++;
        } // ALL trains from start station
      }
      if (j == 0)
      {
        cout << "ERROR" << endl;
      }
    }
    else if (strcmp(input, "QUERY_JOURNEY") == 0)
    {
      char station1[32];
      cin >> station1; // start station
      float starttime;
      cin >> starttime;
      char station2[32];
      cin >> station2;
      planner.besttrain(station1, starttime, station2);
    }
  }
}

void interactive()
{
  cout << "Welcome to Dictionary \n";
  cout << "";
  Planner planner;
  Plannerhandler(planner);
}
void automatic()
{
  Planner planner;
  freopen("sample-planner.txt", "r", stdin);
  // dictionaryHandler(dictionary);
  // TODO
  Plannerhandler(planner);
  char word[32];
  while ((cin >> word))
  {
  }
}
int main()
{
  int i;
  cout << "Enter 1 for interactive testing and 0 for automatic" << endl;
  cin >> i;
  if (i == 0)
  {
    automatic();
  }
  else
  {
    interactive();
  }
}
