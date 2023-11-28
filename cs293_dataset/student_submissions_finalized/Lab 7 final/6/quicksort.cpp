#ifndef QUICKSORT_CPP
#define QUICKSORT_CPP

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

template <typename T>
void my_swap(T &var1, T &var2)
{
  T temp;
  temp = var1;
  var1 = var2;
  var2 = temp;
}

void swap_train_station(TrainInfoPerStation *&var1, TrainInfoPerStation *&var2)
{
  my_swap<int>(var1->journeyCode, var2->journeyCode);
  my_swap<unsigned short>(var1->stopSeq, var2->stopSeq);
  for (int i = 0; i < 7; i++)
    my_swap<bool>(var1->daysOfWeek[i], var2->daysOfWeek[i]);
  my_swap<int>(var1->arrTime, var2->arrTime);
  my_swap<int>(var1->depTime, var2->depTime);
}

listOfObjects<TrainInfoPerStation *> *find_train_stat(int serial_no, listOfObjects<TrainInfoPerStation *> *extra_space[], int k)
{
  int index = serial_no / k;
  listOfObjects<TrainInfoPerStation *> *array_elem = extra_space[index];
  for (int i = 0; i < (serial_no - index * k); i++)
    array_elem = array_elem->next;
  return array_elem;
}

int which_earlier(bool days[], int time_dep, int time_arr)
{
  const int mult = 10000;
  int net_time = 80000;
  for (int i = 0; i < 7; i++)
  {
    if (days[i])
    {
      net_time = i * mult;
      break;
    }
    else
      continue;
  }
  if(time_dep == -1)
    time_dep = 3000;
  if(time_arr == -1)
    time_arr = 0;
  time_arr = time_arr / 100;
  net_time = net_time + time_dep + time_arr;
  return net_time;
}

int get_rand_pivot(int start, int end)
{
  srand(time(NULL));
  int random = start + rand() % (end - start + 1);
  return random;
}
int perform_rand_pivot(listOfObjects<TrainInfoPerStation *> **&extra_space, int start, int end, int k, int random)
{
  if (start >= end)
    return -1;
  listOfObjects<TrainInfoPerStation *> *pivot = find_train_stat(random, extra_space, k);
  listOfObjects<TrainInfoPerStation *> *start_pointer = find_train_stat(start, extra_space, k);
  listOfObjects<TrainInfoPerStation *> *end_data = find_train_stat(end, extra_space, k);
  listOfObjects<TrainInfoPerStation *> *end_pointer = end_data;
  int ret_value = start;
  swap_train_station(pivot->object, end_data->object);
  while (start_pointer != end_pointer)
  {
    if (which_earlier(end_data->object->daysOfWeek, end_data->object->depTime, end_data->object->arrTime) <= which_earlier(start_pointer->object->daysOfWeek, start_pointer->object->depTime, start_pointer->object->arrTime))
    {
      while (start_pointer != end_pointer)
      {
        if (which_earlier(end_data->object->daysOfWeek, end_data->object->depTime, end_data->object->arrTime) > which_earlier(end_pointer->object->daysOfWeek, end_pointer->object->depTime, end_pointer->object->arrTime))
        {
          swap_train_station(start_pointer->object, end_pointer->object);
          start_pointer = start_pointer->next;
          ret_value++;
          break;
        }
        else
          end_pointer = end_pointer->prev;
      }
    }
    else
    {
      start_pointer = start_pointer->next;
      ret_value++;
    }
  }
  swap_train_station(start_pointer->object, end_data->object);
  return ret_value;
}

void Quickie(listOfObjects<TrainInfoPerStation *> **&extra_space, listOfObjects<TrainInfoPerStation *> *stnInfoList, int start, int end, int K)
{
    if (start >= end)  
      return;
    int piv = get_rand_pivot(start, end);
    int sorted_value = perform_rand_pivot(extra_space, start, end, K, piv);
    Quickie(extra_space, stnInfoList, start, sorted_value - 1, K);
    Quickie(extra_space, stnInfoList, sorted_value + 1, end, K);
    return;
}


void Planner::QuicksortSimple(listOfObjects<TrainInfoPerStation *> *stnInfoList, int start, int end)
{
  int K = 4;          
  int array_length;

  int no = end - start + 1;
  if (no % K == 0)
    array_length = no / K;
  else 
    array_length = no / K + 1;

  listOfObjects<TrainInfoPerStation *> **extra_space;
  extra_space = new listOfObjects<TrainInfoPerStation *> *[array_length];
  listOfObjects<TrainInfoPerStation *> *to_be_added = stnInfoList;
  for (int i = 0; i < array_length; i++)
  {
    extra_space[i] = to_be_added;
    int j = 0;
    listOfObjects<TrainInfoPerStation *> *current = to_be_added;
    while (j < K && current != nullptr)
    {
      current = current->next;
      j++;
    }
    to_be_added = current;
  }
  
  Quickie(extra_space, stnInfoList, start, end, K);
}

void Planner::Quicksort(listOfObjects<TrainInfoPerStation *> *stnInfoList)
{
  listOfObjects<TrainInfoPerStation *> *dummy = stnInfoList;
  int num = 0;
  if(dummy == nullptr)
    num = 0;
  while(dummy!=nullptr)
  {
    dummy = dummy->next;
    num++;
  }
  QuicksortSimple(stnInfoList, 0, num - 1);
}

#endif
