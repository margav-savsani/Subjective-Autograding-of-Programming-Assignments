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

int Day(listOfObjects<TrainInfoPerStation *> *check){ //checks the day of the train 
  for(int i = 0;i<7;i++){
    if(check->object->daysOfWeek[i]==true){
      return i;
    }
  }
}

void Planner::Quicksort(listOfObjects<TrainInfoPerStation *> *stnInfoList)
{
  return;
}

void Planner::QuicksortSimple(listOfObjects<TrainInfoPerStation *> *stnInfoList, int start, int end) 
{
  
  if(start >= end){ //base case if start >= end it returns
    return;
  }
  static int K = 4;
  static int recursionLevel = -1; //counts the number of recursions
  static int n=1; //the length of the list

  int start_copy = start;//used to know the partition
  int end_copy = end;//used to know the partition

  listOfObjects<TrainInfoPerStation *> *tail;//tail of the list

  recursionLevel++;//increasing the recursion level

  if (recursionLevel == 0) { //counts the length of the list at the start
    listOfObjects<TrainInfoPerStation *> *head = stnInfoList;
    while(head->next!=nullptr){
      head = head->next;
      n++;
    } 
  }

  listOfObjects<TrainInfoPerStation *> *head10 = stnInfoList; //used to find the tail of the list
    while(head10->next!=nullptr){
      head10 = head10->next;
    } 
    tail = head10;

  static listOfObjects<TrainInfoPerStation *> **pivot =new listOfObjects<TrainInfoPerStation *> *[n/K + 1];//array created so as to store the elements at equal intervals of K elements

  listOfObjects<TrainInfoPerStation *> *head1 = stnInfoList; //used to assign values to the pivot array
  for(int i = 0;i <= n/K ; i++){
    pivot[i] = head1;
    if(i!=n/K){
    for(int j = 0 ;j<K;j++){
      head1 = head1->next;
    }
    }
  }
  
  srand(time(NULL));
  int ran = (rand()%(end-start+1))+start;//used to generate random integer between start to end so as to generate a random pivot
  
  listOfObjects<TrainInfoPerStation *> *head2 = pivot[ran/K]; //head2 stores the pivot
  for(int i = 0;i<ran%K;i++){
    head2 = head2->next;
  }

  listOfObjects<TrainInfoPerStation *> *head3 = stnInfoList; //head3 stores the element at the start
  for(int i = 0;i<start;i++){
    head3 = head3->next;
  }

  listOfObjects<TrainInfoPerStation *> *startcopy = new listOfObjects<TrainInfoPerStation *> (head3->object);//copy of the head3 object
  

  listOfObjects<TrainInfoPerStation *> *tail1 = tail;//stores the element at the end
  for(int i = 0;i<n-end-1;i++){
    tail1 = tail1->prev; 
  }

  listOfObjects<TrainInfoPerStation *> *endcopy = new listOfObjects<TrainInfoPerStation *> (tail1->object);//copy of the tail1 object
  

  listOfObjects<TrainInfoPerStation *> *swap;//used to swap head3 and tail1

  listOfObjects<TrainInfoPerStation *> *copy = new listOfObjects<TrainInfoPerStation *>(head2->object);//copy of the pivot element

  while(head3!=tail1 && head3->prev!=tail1){

    while(Day(head3)<=Day(copy)&& head3!=tail1){//updating head3
      if(Day(head3)!=Day(copy)){ //if days are different 
        head3 = head3->next;
        start_copy++; 
      }
      while(Day(head3)==Day(copy)&& head3->object->depTime<copy->object->depTime && head3!=tail1){ //if days are same and time is different
        head3 = head3->next;
        start_copy++;
      }
      if(Day(head3)==Day(copy) && head3->object->depTime>=copy->object->depTime){ //if head3 is same as the pivot
        break;
      }
    }

    while(Day(tail1)>=Day(copy)&& head3!=tail1){
      if(Day(tail1)!=Day(copy)){ //if days are different 
        tail1 = tail1->prev;
        end_copy--;
      }
      while(Day(tail1)==Day(copy)&& tail1->object->depTime>copy->object->depTime && head3!=tail1){ //if days are same and time is different
        tail1 = tail1->prev;
        end_copy--;  
      }
      if(Day(tail1)==Day(copy) && tail1->object->depTime<=copy->object->depTime){ //if tail1 is the same as the pivot
        break;
      }
    }
    
  listOfObjects<TrainInfoPerStation *> *swap = new listOfObjects<TrainInfoPerStation *>(head3->object);// created to store the object in head3
  //swapping
  head3->object = tail1->object;
  tail1->object = swap->object;
  //updating head3 and tail1
  if(head3!=tail1 &&head3->prev!=tail1){
    head3 = head3->next;
    tail1 = tail1->prev;
    start_copy++;
    end_copy--;
  }
}
if(head3->object == tail1->object && ((Day(head3)<Day(copy)) || (Day(head3)==Day(copy)&& head3->object->depTime<copy->object->depTime))){ //if head3 and tail1 are same but not as pivot and are less than pivot
  QuicksortSimple(stnInfoList,start,start_copy);
  QuicksortSimple(stnInfoList,start_copy+1,end);
}
else if(head3->object == tail1->object && ((Day(head3)>Day(copy)) || (Day(head3)==Day(copy)&& head3->object->depTime>copy->object->depTime))){ //if head3 and tail1 are same but not as pivot and are greater than pivot
  
  QuicksortSimple(stnInfoList,start,start_copy-1);
  QuicksortSimple(stnInfoList,start_copy,end);
}
else if((Day(head3)<Day(tail1)) || (Day(head3)==Day(tail1)&& head3->object->depTime<tail1->object->depTime)){ //if head3 object is less than tail1 object

  QuicksortSimple(stnInfoList,start,start_copy);
  QuicksortSimple(stnInfoList,start_copy+1,end);
}  
else if((Day(head3)>Day(tail1)) || (Day(head3)==Day(tail1)&& head3->object->depTime>tail1->object->depTime)){ //if head3 object is greater than tail1 object
  
  QuicksortSimple(stnInfoList,start,end_copy);
  QuicksortSimple(stnInfoList,start_copy,end); 
}
else if(head3->object == tail1->object && (Day(head3)==Day(copy)&& head3->object->depTime==copy->object->depTime)) { //if head3 tail1 and pivot are same
  if(head3->object == startcopy->object){ //if it is the first element
    QuicksortSimple(stnInfoList,start,end_copy);
    QuicksortSimple(stnInfoList,end_copy+1,end); 
  }
  else if(head3->object == endcopy->object){ //if it is the last element
    QuicksortSimple(stnInfoList,start,end_copy-1);
    QuicksortSimple(stnInfoList,end_copy,end); 
  }
  else{ //if it is not in the start and the end
    QuicksortSimple(stnInfoList,start,end_copy);
    QuicksortSimple(stnInfoList,start_copy+1,end);   
  }
}



recursionLevel--; //updating recursion level
n = 1; //updating n
return;
  
}

#endif
