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

#define k 4

void Quicksort(listOfObjects<TrainInfoPerStation *> *stnInfoList)
{
  int n=0;
  listOfObjects<TrainInfoPerStation *> *temp = stnInfoList;
  while(temp!=nullptr){
    n++;
    temp =temp->next;
  }
  listOfObjects<TrainInfoPerStation *> *array[(n-1)/k +1];
  n = 0;
  temp = stnInfoList;
  while(temp!=nullptr){
    if(n%k == 0){
      array[n/k] = temp;
    }
    n++;
    temp =temp->next;
  }
  // cout<<n<<endl;
  // for(auto x : array){
  //   cout<<x->object->temp_for_testing<<" ";
  // }
  // cout<<endl;
}

// int main(){
//   TrainInfoPerStation *a;
//   a = new TrainInfoPerStation(1,1,1,1);
//   a->temp_for_testing=1;
 
//   listOfObjects<TrainInfoPerStation *> *mylist;
//   mylist = new listOfObjects<TrainInfoPerStation *>(a);
//   listOfObjects<TrainInfoPerStation *> *temp = mylist;
  
//   for(int u=1 ; u<10 ; u++){
//     a = new TrainInfoPerStation(1,1,1,1);
//     a->temp_for_testing = 2*u+1;
//     temp->next = new listOfObjects<TrainInfoPerStation *>(a);
//     temp->next->prev = temp;
//     temp = temp->next;  
//   }


//   Quicksort(mylist);
//   return 0;
// }
