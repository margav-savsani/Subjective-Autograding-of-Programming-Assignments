#ifndef STD_HEADERS
#include "std_headers.h"
#endif

#ifndef PLANNER_H
#include "planner.h"
#endif

#ifndef DICTIONARY_H
#include "dictionary.h"
#endif

#ifndef CODES_H
#include "codes.h"
#endif

#include <cstdlib>
#include <time.h>

// Simply copied previous functions of quicksort, would modify them
// now based on current need of question
int Partition(int start, int finish)
{
  // Need to choose my random pivot here
  // Need to know the range from which it is to be generated
  TrainInfoPerStation *pivot_pointer;

  int a = 1 + (rand() % 10);

  // int x = array[finish].getJourneyCode();
  int i = start - 1;
  // int j = finish + 1;

  for (int j = start; j <= finish - 1; j++)
  {

    // If current element is smaller than the pivot
    if (array[j] < array[finish])
    {
      i++; // increment index of smaller element
      // swap(&arr[i], &arr[j]);
      int jc, price;
      jc = array[i].getJourneyCode();
      price = array[i].getPrice();

      array[i].updateJC(array[j].getJourneyCode());
      array[i].updatePrice(array[j].getPrice());

      array[j].updateJC(jc);
      array[j].updatePrice(price);
    }
  }
  // swap(&arr[i + 1], &arr[finish]);
  int jc, price;
  jc = array[i + 1].getJourneyCode();
  price = array[i + 1].getPrice();

  array[i + 1].updateJC(array[finish].getJourneyCode());
  array[i + 1].updatePrice(array[finish].getPrice());

  array[finish].updateJC(jc);
  array[finish].updatePrice(price);
  return (i + 1);
}

bool Quicksort(int start, int finish)
{
  // Call appropriate pivot function based on choice
  // Split into 2 parts based on pivot choice
  // Recursively keep sorting

  // Making a variable to keep track whether any wrong index was provided in the \
    or not, if given then return false;
  bool error = true;
  if (start < finish)
  {
    int q = Partition(start, finish);
    if (q == -2)
      return false;

    error = Quicksort(start, q - 1);
    if (!error)
      return error;

    error = Quicksort(q + 1, finish);
    if (!error)
      return error;
  }
  return error;
}

void Quicksort(listOfObjects<TrainInfoPerStation *> *stnInfoList)
{
  // Put your code here.
  srand(time(0));
  // srand(time(0));
  // 1+ (rand() % 10); A code to remind me how to generate random number between a certain range
}
