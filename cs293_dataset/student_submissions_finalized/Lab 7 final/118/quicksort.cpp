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

// If you are using the updated planner.cpp, then you simply need to
// sort the list of TrainInfoPerStation objects in stnInfoList.  The
// function that calls Quicksort in planner.cpp (i.e. printStationInfo)
// will then automatically pretty-print the sorted list.
//
// USING THE UPDATED planner.cpp FILE IS STRONGLY RECOMMENDED
//
// Notice that there is a variable K in Quicksort that is to be used as
// described in the problem statement in problems_statement.pdf
// Specifically, if the first call to Quicksort has an argument list of
// n TrainInfoPerStation objects, you can't use additional storage space
// for more than n/K TrainInfoPerStation objects overall (across all
// recursive calls), you must implement randomom choice for pivot (i.e.
// each element in the list being sorted should be equally likely to
// be chosen as pivot), and each call to finding a randomom pivot
// within the list being sorted must take time within O(K), regardless
// of how long the list to be sorted is.
//
// In the function signature of Quicksort, stnInfoList is a list of
// TrainInfoPerStation objects that is to be sorted. In the updated
// planner.cpp file, this list (unsorted) is already prepared for you,
// and you need to simply ensure that the list is sorted (see note
// below about sorting order) when Quicksort returns.
//
// A note about the sorting order:
//
// The final list should be sorted with respect to day of week (first)
// and departure time within the day (next).  Thus Sun 900 < Sun 1100
// < Mon 800 < Thu 700 < Fri 1200
//
//
// Based on how we saw some of you were trying to approach the problem
// in the lab of Sep 23, we are providing another function QuicksortSimple
// with a slightly extended signature. In addition to the list stnInfoList,
// which is passed as the first argument to QuicksortSimple, there are two
// integer parameters "start" and "end", just like in the usual Quicksort
// of an array (as in Prof. Naveen Garg's lectures, for example).
// How do we interpret these "start" and "end" variables in this case,
// when we are trying to sort a list?
// Well, here is one way of thinking about this: If we start
// counting elements of the list starting from stnInfoList and
// chasing "next" pointers until nullptr is reached, the corresponding
// elements can be thought of as elements of a (virtual) array indexed
// from 0 onwards.
// Then, the call to Quicksort must sort the part of the list
// consisting of elements at indices start, start+1, ... until end
// of the above virtual array.
// The whole point of this assignment is to have you do this without
// converting the whole list to an array.
//
// Remember it is indeed possible to solve this problem using the
// function Quicksort with only stnInfoList as its argument.  However,
// if you are finding it difficult to implement Quicksort, you can
// implement QuicksortSimple instead.  Those who implement both
// Quicksort and QuicksortSimple potentially stand to gain some bonus
// points.

//Function to find a random pivot + partition the list
listOfObjects<TrainInfoPerStation *>* Planner::partition(listOfObjects<TrainInfoPerStation *> *start,listOfObjects<TrainInfoPerStation *> *end,listOfObjects<TrainInfoPerStation *>**arr,int K){

//*************************************************************************************************************

  //To generate random index and find the pivot
  int random=start->object->depTime+(rand()%(end->object->depTime-start->object->depTime+1));
//cout<<"Random - "<<random<<endl;
//cout<<"Start and End - "<<start->object->depTime<<" "<<end->object->depTime<<endl;

  listOfObjects<TrainInfoPerStation *> *pivot;//To store the pivot
  pivot=arr[random/K];
  random=random%K;
//cout<<"Random Pivot Being Generated, pivot = "<<pivot->object->depTime<<", end = "<<end->object->depTime<<endl;

  while(random>0){
//cout<<"Random Pivot Generating at - "<<pivot->object->depTime<<endl;
    pivot=pivot->next;
    random--;
  }
//cout<<"Random Pivot Generated at - "<<pivot->object->depTime<<endl;

//*************************************************************************************************************

  //Partition "function"
  listOfObjects<TrainInfoPerStation *> *temp;
  temp=end;
  while(start!=temp){
    if(temp->object->arrTime<=pivot->object->arrTime){
      random++;
    }
    temp=temp->prev;
  }
  if(temp->object->arrTime>pivot->object->arrTime)
    random--; 
  random+=start->object->depTime;
//cout<<"Pivot to be placed at - "<<random<<endl;

  //To find the correct location of the pivot
  temp=arr[random/K];
  random=random%K;
  while(random>0){
    temp=temp->next;
    random--;
  }
//-------------------------------------------------------
  //To swap the pivot and the elemt in its position
  TrainInfoPerStation *tempObj=temp->object;
  temp->object=pivot->object;
  pivot->object=tempObj;
  random=temp->object->depTime;
  temp->object->depTime=pivot->object->depTime;
  pivot->object->depTime=random;

  pivot=temp;
//cout<<"Partitioned, pivot = "<<pivot->object->depTime<<endl;

//*************************************************************************************************************

  //To make the two lists for Quicksort
  while(start->object->depTime<end->object->depTime){
    while(end->object->arrTime>pivot->object->arrTime)
      end=end->prev;
    while(start->object->arrTime<=pivot->object->arrTime && start->object->depTime<end->object->depTime)
      start=start->next;
    if(start->object->depTime<end->object->depTime){
      //To swap the elements
      tempObj=start->object;
      start->object=end->object;
      end->object=tempObj;
      random=start->object->depTime;
      start->object->depTime=end->object->depTime;
      end->object->depTime=random;
      start=start->next;
      end=end->prev;
    }
  }
//cout<<"2 Lists Made"<<endl;

//*************************************************************************************************************
  //To return the pivot
  return pivot;
}

void Planner::Quicksort(listOfObjects<TrainInfoPerStation *> *stnInfoList)
{
  // A few static variable declarations
  static int K = 4; // Parameter to be experimented with
  static int recursionLevel = -1; // This can be used to find out at which
                                  // level of the recursion you are in
  static listOfObjects<TrainInfoPerStation *> **arr;
  static listOfObjects<TrainInfoPerStation *> *end;

  // Increment recursion level on entering the function
  recursionLevel++;
  
  // If you need to set up additional storage (upto n/K TrainInfoPerStation
  // elements), it's ok to do it *once* using static variables/array.
  // Using the static recursionLevel, you can ensure that the storage
  // allocation is done only the first time Quicksort is called, and not
  // in every recursive call.
  //
  // Note that if you allocate space for upto n/K TrainInfoPerStation in
  // each recursive call, you will end up using much more than n/K space
  // overall.  So you MUST NOT allocate space in each recursive call.
  //
  // A variable/array defined using static is not created afresh in
  // each recursive call.  Instead, a single copy of it is maintained
  // across all recursions.
  
  if (recursionLevel == 0) {
    // Find length of the list stnInfoList, if needed.
    // Allocate additional space for upto n/K TrainInfoPerStation objects
    // if needed.
    // Do other things that you may want to do only at the beginning
    // as a pre-processing step.

    if(stnInfoList==nullptr || stnInfoList->next==nullptr){
      return;
    }

    srand(time(0));
    
    end=stnInfoList;

    for(int i=0;end->next!=nullptr;i++){
      for(int j=0;j<7;j++){
        if(end->object->daysOfWeek[j]){
          end->object->arrTime+=(j*2500+1);
          end->object->arrTime*=2500;
          if(end->object->depTime==-1)
            end->object->arrTime+=2401;
          else
            end->object->arrTime+=end->object->depTime;
          break;
        }
      }
      end->object->depTime=i;
//cout<<end->object->depTime<<endl;

      end=end->next;
    }
    for(int j=0;j<7;j++){
      if(end->object->daysOfWeek[j]){
        end->object->arrTime+=(j*2500+1);
        end->object->arrTime*=2500;
        if(end->object->depTime==-1)
          end->object->arrTime+=2401;
        else
          end->object->arrTime+=end->object->depTime;
        break;
      }
    }
    end->object->depTime=end->prev->object->depTime+1;
    int len=end->object->depTime/K + 1; //size of array to be created
    arr = new listOfObjects<TrainInfoPerStation *>*[len];
    if(arr==nullptr){
      cout<<"Memory allocation failure."<<endl;
      return;
    }
    arr[0]=stnInfoList->next;
    for(int i=1;i<=end->object->depTime;i++){
      if(i%K==0)
        arr[i/K]=arr[0];
      arr[0]=arr[0]->next;
    }
    arr[0]=stnInfoList;
  }

  // Put your code for the core of Quicksort here
  if(stnInfoList==nullptr){
    recursionLevel--;
    return;
  }
//cout<<"COND-0"<<endl;
  if(stnInfoList->object->depTime<end->object->depTime){
//cout<<"COND-1"<<endl;
    Quicksort(partition(stnInfoList,end,arr,K)->next);
//cout<<"COND-1.1"<<endl;
    Quicksort(stnInfoList);
//cout<<"COND-1.2"<<endl;
  }
  else if(stnInfoList==end){
//cout<<"COND-2"<<endl;
    end=end->prev;
    if(end==nullptr || end->prev==nullptr){
      recursionLevel--;
      return;
    }
    end=end->prev;
  }
  else{
//cout<<"COND-3"<<endl;
    if(end==nullptr || end->prev==nullptr){
      recursionLevel--;
      return;
    }
    end=end->prev;
  }

  if(recursionLevel==0){
    stnInfoList=arr[0];
    while(stnInfoList->next!=nullptr){
      stnInfoList->object->depTime=stnInfoList->object->arrTime%2500;
      if(stnInfoList->object->depTime==2401)
        stnInfoList->object->depTime=-1;
      stnInfoList->object->arrTime=(stnInfoList->object->arrTime/2500)%2500-1;
      stnInfoList=stnInfoList->next;
    }
    stnInfoList->object->depTime=stnInfoList->object->arrTime%2500;
    if(stnInfoList->object->depTime==2401)
      stnInfoList->object->depTime=-1;
    stnInfoList->object->arrTime=(stnInfoList->object->arrTime/2500)%2500-1;
    delete[] arr;
  }

  // Decrement recursion level before leaving the function
  recursionLevel--;
  return;
}

void Planner::QuicksortSimple(listOfObjects<TrainInfoPerStation *> *stnInfoList, int start, int end)
{
  // A few static variable declarations
  static int K = 4; // Parameter to be experimented with
  static int recursionLevel = -1; // This can be used to find out at which
                                  // level of the recursion you are in

  static listOfObjects<TrainInfoPerStation *> **arr;
  static int random;
  static listOfObjects<TrainInfoPerStation *> *pivot;
  static listOfObjects<TrainInfoPerStation *> *temp;
  static TrainInfoPerStation *tempObj;
  static listOfObjects<TrainInfoPerStation *> *piv;

  // Increment recursion level on entering the function
  recursionLevel++;
  // If you need to set up additional storage (upto n/K TrainInfoPerStation
  // elements), it's ok to do it *once* using static variables/array.
  // Using the static recursionLevel, you can ensure that the storage
  // allocation is done only the first time Quicksort is called, and not
  // in every recursive call.
  //
  // Note that if you allocate space for upto n/K TrainInfoPerStation in
  // each recursive call, you will end up using much more than n/K space
  // overall.  So you MUST NOT allocate space in each recursive call.
  //
  // A variable/array defined using static is not created afresh in
  // each recursive call.  Instead, a single copy of it is maintained
  // across all recursions.
  
  if (recursionLevel == 0) {
    // Allocate additional space for upto n/K TrainInfoPerStation objects
    // if needed.
    // Do other things that you may want to do only at the beginning
    // as a pre-processing step.
    srand(time(0));
    int len=(end - start)/K + 1; //size of array to be created
    arr = new listOfObjects<TrainInfoPerStation *>*[len];
    if(arr==nullptr){
      cout<<"Memory allocation failure."<<endl;
      return;
    }
    listOfObjects<TrainInfoPerStation *> *temp;
    temp=stnInfoList;

    //To create an array to access the list elements faster
    for(int i=0;i<=(end-start);i++){
      for(int j=0;j<7;j++){
        if(temp->object->daysOfWeek[j]){
          temp->object->arrTime+=j*2500+1;
          temp->object->arrTime*=2500;
          if(temp->object->depTime==-1)
            temp->object->arrTime+=2401;
          else
            temp->object->arrTime+=temp->object->depTime;
          break;
        }
      }
      if(i%K==0)
        arr[i/K]=temp;
      temp=temp->next;
    }
  }
  
  // Put your code for the core of QuicksortSimple here

  if(start<end){
    //To find random pivot index
    random=start+( rand() %(end-start+1));
//---------------------------------------------------------------------------
//      cout<<start<<" "<<end<<" "<<random<<endl;
//---------------------------------------------------------------------------

//*****************************************************************************************
    
    //random pivot generation from the index
    pivot=arr[random/K];
    random=random%K;
    while(random>0){
      pivot=pivot->next;
      random--;
    }

//****************************************************************************************
    
    //Partition "function"
    temp=arr[start/K];
    for(int i=start%K;i>0;i--){
      temp=temp->next;
    }
    random=start-1;
    for(int i=start;i<=end;i++){
      if(temp->object->arrTime<=pivot->object->arrTime)
        random++;
      temp=temp->next;
    }
    temp=arr[random/K];
//---------------------------------------------------------------------------
//      cout<<random<<" "<<pivot->object->arrTime/10000+1<<endl;
//---------------------------------------------------------------------------
    start+=random*end;
    random=random%K;
    while(random>0){
      temp=temp->next;
      random--;
    }
    tempObj=temp->object;
    temp->object=pivot->object;
    pivot->object=tempObj;

//*******************************************************************************************
    
    //Making the two lists for quicksort
    pivot=stnInfoList;
    piv=arr[end/K];
    for(int i=0;i<end%K;i++)
      piv=piv->next;
    random=start/end;
//--------------------------------------------------------------------------------------------------------------
//      cout<<"First and Last pivots-"<<pivot->object->arrTime/10000+1<<" "<<piv->object->arrTime/10000+1<<endl;
//      cout<<"Pivot Location-"<<random<<endl;
//--------------------------------------------------------------------------------------------------------------
    for(int i=start%end,j=end;i<random&&random<j;){
//cout<<"Inside-1"<<endl;
      while(i<random && pivot->object->arrTime<=temp->object->arrTime){
        i++;//cout<<pivot->object->arrTime/10000+1<<endl;
        pivot=pivot->next;
      }
//cout<<"Inside-2"<<endl;
      while(piv->object->arrTime>temp->object->arrTime){
        j--;//cout<<piv->object->arrTime/10000+1<<endl;
        piv=piv->prev;
      }
//------------------------------------------------------------------------------------------------------------
//        cout<<"Stopped at pivots-"<<pivot->object->arrTime/10000+1<<" "<<piv->object->arrTime/10000+1<<endl;
//        cout<<"i and j = "<<i<<" "<<j<<endl;
//------------------------------------------------------------------------------------------------------------
      if(i<j){
//--------------------------------------------------------------------------------------------------------
//          cout<<"EXCHANGE  - "<<pivot->object->arrTime/10000+1<<" "<<piv->object->arrTime/10000+1<<endl;
//--------------------------------------------------------------------------------------------------------
        tempObj=pivot->object;
        pivot->object=piv->object;
        piv->object=tempObj;
//--------------------------------------------------------------------------------------------------------------
//          cout<<"AFTER EXCHANGE  - "<<pivot->object->arrTime/10000+1<<" "<<piv->object->arrTime/10000+1<<endl;
//--------------------------------------------------------------------------------------------------------------
        piv=piv->prev;
        pivot=pivot->next;
        i++;
        j--;
      }
    }

//*********************************************************************************************************

    QuicksortSimple(stnInfoList,start%end,start/end-1);
    QuicksortSimple(stnInfoList,start/end+1,end);
  }
  if(recursionLevel==0){
    delete[] arr;
    start=start%end;
    for(int i=0;i<=(end-start);i++){
      stnInfoList->object->arrTime=(stnInfoList->object->arrTime/2500)%2500-1;
      stnInfoList=stnInfoList->next;
    }
  }
  recursionLevel--;
  return;
}

/*
listOfObjects<TrainInfoPerStation *> operator<= (listOfObjects<TrainInfoPerStation *> obj){
  int a=object->arrTime,b=obj.object->arrTime;
  for(int i=0;i<7,i++){
    if(object->daysOfWeek[i])
      a+=i*2000;
    if(obj.object->daysOfWeek[i])
      b+=i*2000;
  }
  return(a<=b);
}
*/

#endif
