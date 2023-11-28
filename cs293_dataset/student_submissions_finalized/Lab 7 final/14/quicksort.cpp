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

//utility function less than or equal to for partition function
bool lessthan_or_equalto(TrainInfoPerStation  time1, TrainInfoPerStation time2)
{
  // comparing day first
  for(int i=0;i<7;i++)
  {
    if(time1.daysOfWeek[i]==1 && time2.daysOfWeek[i]==0) return true; 
    if(time1.daysOfWeek[i]==0 && time2.daysOfWeek[i]==1) return false;
  }
  //if days are same

  //comparing depTime
  return time1.depTime < time2.depTime;
  //compares depTime if days are equal
}
//defined a utility function for comparison in partition function

//utility function to swap objects
void swap_objects(listOfObjects<TrainInfoPerStation *> * time1, listOfObjects<TrainInfoPerStation *> * time2)
{
  //this function doesn't swap nodes of doubly lined list
  //it just swaps the objects in it
  TrainInfoPerStation* t;
  t = time1->object;
  time1->object = time2->object;
  time2->object = t;
}
//defined a utility function which swaps the objects(only) of nodes

//utility function for getting pointer from index in list
listOfObjects<TrainInfoPerStation*>* getptr(int size,listOfObjects<TrainInfoPerStation*>**arr,int K)
{
  listOfObjects<TrainInfoPerStation*> *pointer = arr[size/K];
  for(int i=0;i<size%K;i++)
  {
    pointer=pointer->next;
  }
  return pointer;
}
//defined a utility function which gets pointer from array

//partition function
int partition(listOfObjects<TrainInfoPerStation*> *stnInfoList, int start, int end, listOfObjects<TrainInfoPerStation*>**arr, int K)
{
  //getting random pivot
  srand((unsigned)time(NULL)); 
  int n = (rand() % (end - start)) + start;
  listOfObjects<TrainInfoPerStation*>* pvt =  getptr(n,arr,K);
  TrainInfoPerStation piv_class = *(pvt->object);
  //got random pivot

  //to implement random quicksort first swap the random pivot with first
  listOfObjects<TrainInfoPerStation*>* st = getptr(start,arr,K);
  swap_objects(getptr(n,arr,K),st);
  //now we can proceed normally as we do by taking first element as pivot 
  
  listOfObjects<TrainInfoPerStation*>* temp_s = st;
  TrainInfoPerStation *temp_s_class=temp_s->object;
 
  // counting no of objects less than pivot
  int c=0;
  for(int i=1;i<end-start+1;i++)
  {
    if( lessthan_or_equalto(*(temp_s->next->object) , *(temp_s_class)))  c++;
    temp_s = temp_s->next;
  }

  int p_idx=start+c;

  // exchanging pivot and element at pivoth index
  listOfObjects<TrainInfoPerStation*>*piv;
  piv=getptr(p_idx,arr,K);
  swap_objects(st,piv);

  int i=start, j=end;
  while (i < p_idx && j > p_idx) 
  {  
    // index of element greater than pivot
    while (lessthan_or_equalto(*(getptr(i,arr,K)->object), piv_class)) i++; 
 
    // index of element lesser than pivot
    while (lessthan_or_equalto(piv_class, *(getptr(j,arr,K)->object))) j--; 

    if (i < p_idx && j > p_idx) 
    {
      //swap elements
      swap_objects(getptr(i,arr,K), getptr(j,arr,K));
      i++;
      j--;
    }
  }
  return p_idx;
}

void Planner::QuicksortSimple(listOfObjects<TrainInfoPerStation *> *stnInfoList, int start, int end)
{  
  // A few static variable declarations 
  static int K=4;          // Parameter to be experimented with
  static int recursionLevel=-1; // This can be used to find out at which level of the recursion you are in
  static int len;
  static listOfObjects<TrainInfoPerStation*>**arr;
  // declared static variables

  recursionLevel++;

  if(recursionLevel ==0 )
  {  
    // finding length of stinfolist
    listOfObjects<TrainInfoPerStation*> * temp1 = stnInfoList;
    while(temp1)
    {
      len++; 
      temp1 = temp1->next;
    }
    //found length of doubly inked list

    //creating dummy_arr so that we can use variable length of array
    listOfObjects<TrainInfoPerStation*>** dummy_arr = new listOfObjects<TrainInfoPerStation*>*[((len-1)/K)+1];
    //head of linked list
    listOfObjects<TrainInfoPerStation*>* temp2 = stnInfoList;

    //storing pointers int array
    int i=0, j=0;
    while(temp2!=NULL)
    {
      if(i%4==0)
      { 
        dummy_arr[j] = temp2;  
        j++;
      }
      i=(i+1)%4;
      temp2=temp2->next;
    }
    arr = dummy_arr;
    //stored every Kth pointer in array

  }

  //recursive quicksort
  if(start < end)
  {  
    int p_idx = partition(stnInfoList,start,end,arr,K); 
    QuicksortSimple(stnInfoList,start,p_idx-1); 
    QuicksortSimple(stnInfoList,p_idx+1,end); 
  }
  //recursion

  recursionLevel--;
  return;
}

#endif
