#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fstream>
#include "planner.cpp"
void queryhandler(Planner &p)
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
    else if (strcmp(input, "ADD") == 0)
    {
      char k1[32], k2[32];
      float f1, f2;
      cin >> k1 >> f1 >> k2 >> f2;
      Entry b;
      strcpy(b.key1, k1);
      b.value1 = f1;
      strcpy(b.key2, k2);
      b.value2 = f2;
      if (p.addjourney(b))
        cout << "Successfully Added" << endl;
      else
        cout << "Not added successfully" << endl;
    }
    else if (strcmp(input, "QUERY_STATION") == 0)
    {
      char k1[32];
      float f1;
      cin >> k1 >> f1;
      Query b;
      b.t2 = f1;
      strcpy(b.A, k1);
      p.querystation(b);
    }
    else if (strcmp(input, "QUERY_JOURNEY") == 0)
    {
      char k1[32], k2[32];
      float t2;
      cin >> k1 >> t2 >> k2;
      Query b;
      b.t2 = t2;
      strcpy(b.A, k1);
      strcpy(b.B, k2);
      p.queryjourney(b);
    }
  }
}

void interactive()
{
  
  Planner p;
  queryhandler(p);
}
int main()
{
  

  
  
    interactive();
  
  
  return 0;
}
