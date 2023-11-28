#include "choose.h"
#include <cstdlib>
#include <iostream>
#include <cassert>


Journey* choose_one(Journey* x, int start, int finish)
{
  if ((start >= 0) && (start <= finish))
    {
      return &x[start];
    }
  else
    {
      return nullptr;
    }
    
}

Journey* choose_two(Journey* x, int start, int finish)
{
  if ((start >= 0) && (start <= finish))
    {
      return &x[finish];
    }
  else
    {
      return nullptr;
    }

}

Journey* choose_three(Journey *x, int start, int finish)
{
  static unsigned int counter = 0;
  
  if ((start >= 0) && (start <= finish))
    {
      int index;

      counter++;
      
      if ((start % 2) && !(finish % 3)) {
	index = start + (counter % (finish - start + 1));
      }
      else if (!(start % 2) && (finish % 3)) {
	index = finish - (counter % (finish - start + 1));
      }
      else if ((start % 2) && (finish % 3)) {
	index = start + ((++counter) % (finish - start + 1));
      }
      else {
	index = finish - ((--counter) % (finish - start + 1));
      }

      return &x[index];
    }
  else
    {
      return nullptr;
    }
}

Journey* choose_four(Journey *x, int start, int finish){
  int y = ((finish-start)*(rand()%1000))/1000+start;
  // std::cout << y << " " << finish-start << std::endl;
  assert(y >= start && y <= finish);
  return &x[y];
}
