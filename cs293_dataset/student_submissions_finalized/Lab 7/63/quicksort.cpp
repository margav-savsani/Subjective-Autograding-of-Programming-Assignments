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




listOfObjects<TrainInfoPerStation *>* idx_ptr(int i, int n, int k, listOfObjects<TrainInfoPerStation *>* arr[]){
  int j = i%k;
  int m = i/k;
  listOfObjects<TrainInfoPerStation*> * A = arr[m];
  for (int s = 0; s < j; j++){
    A = A->next;
  }
  return A;
}

void part_k(listOfObjects<TrainInfoPerStation *>* arr[],int k ,int n, listOfObjects<TrainInfoPerStation *> *stnInfoList){
  listOfObjects<TrainInfoPerStation *> *A = stnInfoList;
  for (int i = 0; i < n; i++){
    if (i%k == 0){
      arr[i/k] = A;
    }
    A = A->next;
  }
}

int choose_pivot(int N){
  return rand()%N;
}

void exchange(int a, int b, int n, int k, listOfObjects<TrainInfoPerStation *>* arr[]){
  if (a == b){
    return;
  }
  else if (a >= n || b >= n || a < 0 || b < 0){
    cout << "index out of range" << endl;
    return;
  }
  else if (a == 0){
    
  }
}

void Quicksort(listOfObjects<TrainInfoPerStation *> *stnInfoList)
{
  // Put your code here.
}
