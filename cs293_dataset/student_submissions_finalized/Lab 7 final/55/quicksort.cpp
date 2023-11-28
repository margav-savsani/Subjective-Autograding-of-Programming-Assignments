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
// recursive calls), you must implement random choice for pivot (i.e.
// each element in the list being sorted should be equally likely to
// be chosen as pivot), and each call to finding a random pivot
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

void Planner::Quicksort(listOfObjects<TrainInfoPerStation *> *stnInfoList)
{ 
  srand(time(0));
  // A few static variable declarations
  static int K = 4; // Parameter to be experimented with
  static int recursionLevel = -1; // This can be used to find out at which
                                  // level of the recursion you are in
  static int start=0;
  static int end=999999999;
  static listOfObjects<TrainInfoPerStation*> **sub;


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
    int n=0;
    listOfObjects<TrainInfoPerStation*>*temp=stnInfoList;
    while(temp!=nullptr){
      n+=1;
      temp=temp->next;
    }
    start=0;end=n-1;
    sub=new listOfObjects<TrainInfoPerStation*>*[n/K];
    temp=stnInfoList;
    int i=0;
    while(temp!=nullptr){
      if(i%K==0){
        sub[i/K]=temp;
      }
      temp=temp->next;
      i++;
    }
  }

  if(end<=start) {
    recursionLevel--;
    return;
  }
  // //EDIT
  //   cout<<"Start: "<<start<<" End: "<<end<<endl;
  // //END EDIT

  // Put your code for the core of QuicksortSimple here
  int randPivotIndex=rand()%(end-start+1)+start;
  
  // //EDIT
  //   cout<<"Initialised randPivotIndex: "<<randPivotIndex<<endl;
  // //END EDIT

  //Partitioning
  listOfObjects<TrainInfoPerStation*> *pivot=sub[randPivotIndex/K],*head=sub[start/K],*tail=sub[end/K];
  for(int i=0;i<randPivotIndex-(K*(randPivotIndex/K));i++){
    pivot=pivot->next;
  }
  for(int i=0;i<start-(K*(start/K));i++){
    head=head->next;
  }
  for(int i=0;i<end-(K*(end/K));i++){
    tail=tail->next;
  }
  listOfObjects<TrainInfoPerStation*> *lpivot,*rpivot;
  if(pivot==head){lpivot=pivot;} else{lpivot=pivot->prev;}
  if(pivot==tail){rpivot=pivot;} else{rpivot=pivot->next;}

  int pivotDay;
  for(int i=0;i<7;i++){
    if(pivot->object->daysOfWeek[i]){pivotDay=i;break;}
  }
  int pivotDep=pivot->object->depTime;
  
  
  while(true){
    bool flagcheck=true;
    // cout<<"Stuck in while(true)\n";
    while(lpivot!=head){
      bool flag=false;
      for(int i=0;i<7;i++){
        if(lpivot->object->daysOfWeek[i]){
          if(i<pivotDay){
            lpivot=lpivot->prev;
            break;
          }
          else if (i==pivotDay){
            if(lpivot->object->depTime<=pivotDep){
              lpivot=lpivot->prev;
              break;
            }
            else{
            flag=true;
            break;
          }
          }
          else{
            flag=true;
            break;
          }
        }
      }
      if(flag) break;
    }

    while(rpivot!=tail){
      bool flag=false;
      for(int i=0;i<7;i++){
        if(rpivot->object->daysOfWeek[i]){
          if(i>pivotDay){
            rpivot=rpivot->next;
            break;
          }
          else if (i==pivotDay){
            if(rpivot->object->depTime>=pivotDep){
              rpivot=rpivot->next;
              break;
            }
            else{
            flag=true;
            break;
          }
          }
          else{
            flag=true;
            break;
          }
        }
      }
      if(flag) break;
    }

    int lpivotDay,rpivotDay,lpivotDep,rpivotDep;
    for(int i=0;i<7;i++){
      if(lpivot->object->daysOfWeek[i]){lpivotDay=i;break;}
    }
    for(int i=0;i<7;i++){
      if(rpivot->object->daysOfWeek[i]){rpivotDay=i;break;}
    }
    lpivotDep=lpivot->object->depTime;
    rpivotDep=rpivot->object->depTime;

    if(lpivotDay<=pivotDay && rpivotDay>=pivotDay){
      if(lpivotDay<pivotDay){
        if(rpivotDay>pivotDay){
          break;
        }
        else if(rpivotDep>=pivotDep){
          break;
        }
      }
      else if(lpivotDep<=pivotDep){
        if(rpivotDay>pivotDay){
          break;
        }
        else if(rpivotDep>=pivotDep){
          break;
        }
      }
    }

    if(lpivotDay>=pivotDay && rpivotDay<=pivotDay){
      if(lpivotDay>pivotDay){
        if(rpivotDay<pivotDay){
          swap(lpivot->object->arrTime,rpivot->object->arrTime);
          swap(lpivot->object->daysOfWeek,rpivot->object->daysOfWeek);
          swap(lpivot->object->depTime,rpivot->object->depTime);
          swap(lpivot->object->journeyCode,rpivot->object->journeyCode);
          swap(lpivot->object->stopSeq,rpivot->object->stopSeq);
          flagcheck=false;
        }
        else if(rpivotDep<pivotDep){
          swap(lpivot->object->arrTime,rpivot->object->arrTime);
          swap(lpivot->object->daysOfWeek,rpivot->object->daysOfWeek);
          swap(lpivot->object->depTime,rpivot->object->depTime);
          swap(lpivot->object->journeyCode,rpivot->object->journeyCode);
          swap(lpivot->object->stopSeq,rpivot->object->stopSeq);
          flagcheck=false;
        }
      }
      else if(lpivotDep>pivotDep){
        if(rpivotDay<pivotDay){
          swap(lpivot->object->arrTime,rpivot->object->arrTime);
          swap(lpivot->object->daysOfWeek,rpivot->object->daysOfWeek);
          swap(lpivot->object->depTime,rpivot->object->depTime);
          swap(lpivot->object->journeyCode,rpivot->object->journeyCode);
          swap(lpivot->object->stopSeq,rpivot->object->stopSeq);
          flagcheck=false;
        }
        else if(rpivotDep<pivotDep){
          swap(lpivot->object->arrTime,rpivot->object->arrTime);
          swap(lpivot->object->daysOfWeek,rpivot->object->daysOfWeek);
          swap(lpivot->object->depTime,rpivot->object->depTime);
          swap(lpivot->object->journeyCode,rpivot->object->journeyCode);
          swap(lpivot->object->stopSeq,rpivot->object->stopSeq);
          flagcheck=false;
        }
      }
    }

    if(flagcheck){
    if(lpivotDay>=pivotDay && rpivotDay>=pivotDay){

      if(lpivotDay>pivotDay){
        if(rpivotDay>pivotDay){
          swap(lpivot->object->arrTime,pivot->prev->object->arrTime);
          swap(lpivot->object->daysOfWeek,pivot->prev->object->daysOfWeek);
          swap(lpivot->object->depTime,pivot->prev->object->depTime);
          swap(lpivot->object->journeyCode,pivot->prev->object->journeyCode);
          swap(lpivot->object->stopSeq,pivot->prev->object->stopSeq);

          swap(pivot->object->arrTime,pivot->prev->object->arrTime);
          swap(pivot->object->daysOfWeek,pivot->prev->object->daysOfWeek);
          swap(pivot->object->depTime,pivot->prev->object->depTime);
          swap(pivot->object->journeyCode,pivot->prev->object->journeyCode);
          swap(pivot->object->stopSeq,pivot->prev->object->stopSeq);

          pivot=pivot->prev;
          randPivotIndex--;
          flagcheck=false;
        }
        else if(rpivotDep>=pivotDep){
          swap(lpivot->object->arrTime,pivot->prev->object->arrTime);
          swap(lpivot->object->daysOfWeek,pivot->prev->object->daysOfWeek);
          swap(lpivot->object->depTime,pivot->prev->object->depTime);
          swap(lpivot->object->journeyCode,pivot->prev->object->journeyCode);
          swap(lpivot->object->stopSeq,pivot->prev->object->stopSeq);

          swap(pivot->object->arrTime,pivot->prev->object->arrTime);
          swap(pivot->object->daysOfWeek,pivot->prev->object->daysOfWeek);
          swap(pivot->object->depTime,pivot->prev->object->depTime);
          swap(pivot->object->journeyCode,pivot->prev->object->journeyCode);
          swap(pivot->object->stopSeq,pivot->prev->object->stopSeq);

          pivot=pivot->prev;
          randPivotIndex--;
          flagcheck=false;
        }
      }
      else if(lpivotDep>=pivotDep){
        if(rpivotDay>pivotDay){
          swap(lpivot->object->arrTime,pivot->prev->object->arrTime);
          swap(lpivot->object->daysOfWeek,pivot->prev->object->daysOfWeek);
          swap(lpivot->object->depTime,pivot->prev->object->depTime);
          swap(lpivot->object->journeyCode,pivot->prev->object->journeyCode);
          swap(lpivot->object->stopSeq,pivot->prev->object->stopSeq);

          swap(pivot->object->arrTime,pivot->prev->object->arrTime);
          swap(pivot->object->daysOfWeek,pivot->prev->object->daysOfWeek);
          swap(pivot->object->depTime,pivot->prev->object->depTime);
          swap(pivot->object->journeyCode,pivot->prev->object->journeyCode);
          swap(pivot->object->stopSeq,pivot->prev->object->stopSeq);

          pivot=pivot->prev;
          randPivotIndex--;
          flagcheck=false;
        }
        else if(rpivotDep>=pivotDep){
          swap(lpivot->object->arrTime,pivot->prev->object->arrTime);
          swap(lpivot->object->daysOfWeek,pivot->prev->object->daysOfWeek);
          swap(lpivot->object->depTime,pivot->prev->object->depTime);
          swap(lpivot->object->journeyCode,pivot->prev->object->journeyCode);
          swap(lpivot->object->stopSeq,pivot->prev->object->stopSeq);

          swap(pivot->object->arrTime,pivot->prev->object->arrTime);
          swap(pivot->object->daysOfWeek,pivot->prev->object->daysOfWeek);
          swap(pivot->object->depTime,pivot->prev->object->depTime);
          swap(pivot->object->journeyCode,pivot->prev->object->journeyCode);
          swap(pivot->object->stopSeq,pivot->prev->object->stopSeq);

          pivot=pivot->prev;
          randPivotIndex--;
          flagcheck=false;
        }
      }
    }
    }
    if(flagcheck){
    if(lpivotDay<=pivotDay && rpivotDay<=pivotDay){
      if(lpivotDay<pivotDay){
        if(rpivotDay<pivotDay){
          swap(rpivot->object->arrTime,pivot->next->object->arrTime);
          swap(rpivot->object->daysOfWeek,pivot->next->object->daysOfWeek);
          swap(rpivot->object->depTime,pivot->next->object->depTime);
          swap(rpivot->object->journeyCode,pivot->next->object->journeyCode);
          swap(rpivot->object->stopSeq,pivot->next->object->stopSeq);

          swap(pivot->object->arrTime,pivot->next->object->arrTime);
          swap(pivot->object->daysOfWeek,pivot->next->object->daysOfWeek);
          swap(pivot->object->depTime,pivot->next->object->depTime);
          swap(pivot->object->journeyCode,pivot->next->object->journeyCode);
          swap(pivot->object->stopSeq,pivot->next->object->stopSeq);

          pivot=pivot->next;
          randPivotIndex++;
        }
        else if(rpivotDep<=pivotDep){
          swap(rpivot->object->arrTime,pivot->next->object->arrTime);
          swap(rpivot->object->daysOfWeek,pivot->next->object->daysOfWeek);
          swap(rpivot->object->depTime,pivot->next->object->depTime);
          swap(rpivot->object->journeyCode,pivot->next->object->journeyCode);
          swap(rpivot->object->stopSeq,pivot->next->object->stopSeq);

          swap(pivot->object->arrTime,pivot->next->object->arrTime);
          swap(pivot->object->daysOfWeek,pivot->next->object->daysOfWeek);
          swap(pivot->object->depTime,pivot->next->object->depTime);
          swap(pivot->object->journeyCode,pivot->next->object->journeyCode);
          swap(pivot->object->stopSeq,pivot->next->object->stopSeq);

          pivot=pivot->next;
          randPivotIndex++;
        }
      }
      else if(lpivotDep<=pivotDep){
        if(rpivotDay<pivotDay){
          swap(rpivot->object->arrTime,pivot->next->object->arrTime);
          swap(rpivot->object->daysOfWeek,pivot->next->object->daysOfWeek);
          swap(rpivot->object->depTime,pivot->next->object->depTime);
          swap(rpivot->object->journeyCode,pivot->next->object->journeyCode);
          swap(rpivot->object->stopSeq,pivot->next->object->stopSeq);

          swap(pivot->object->arrTime,pivot->next->object->arrTime);
          swap(pivot->object->daysOfWeek,pivot->next->object->daysOfWeek);
          swap(pivot->object->depTime,pivot->next->object->depTime);
          swap(pivot->object->journeyCode,pivot->next->object->journeyCode);
          swap(pivot->object->stopSeq,pivot->next->object->stopSeq);

          pivot=pivot->next;
          randPivotIndex++;
        }
        else if(rpivotDep<=pivotDep){
          swap(rpivot->object->arrTime,pivot->next->object->arrTime);
          swap(rpivot->object->daysOfWeek,pivot->next->object->daysOfWeek);
          swap(rpivot->object->depTime,pivot->next->object->depTime);
          swap(rpivot->object->journeyCode,pivot->next->object->journeyCode);
          swap(rpivot->object->stopSeq,pivot->next->object->stopSeq);

          swap(pivot->object->arrTime,pivot->next->object->arrTime);
          swap(pivot->object->daysOfWeek,pivot->next->object->daysOfWeek);
          swap(pivot->object->depTime,pivot->next->object->depTime);
          swap(pivot->object->journeyCode,pivot->next->object->journeyCode);
          swap(pivot->object->stopSeq,pivot->next->object->stopSeq);

          pivot=pivot->next;
          randPivotIndex++;
        }
      }
    }
    }
    // //EDIT
    // cout<<"pivotDay: "<<pivotDay<<" lpivotDay: "<<lpivotDay<<" rpivotDay: "<<rpivotDay<<endl;
    // //END EDIT
  }
  
  // Put your code for the core of Quicksort here
  int temp=end;
  end=randPivotIndex-1;
  Quicksort(stnInfoList);
  start=randPivotIndex+1;
  end=temp;
  Quicksort(stnInfoList);
  // Decrement recursion level before leaving the function
  recursionLevel--;
  return;
}

void Planner::QuicksortSimple(listOfObjects<TrainInfoPerStation *> *stnInfoList, int start, int end)
{
  srand(time(0));
  //base case
  if(end<=start) return;

  // //EDIT
  //   cout<<"Start: "<<start<<" End: "<<end<<endl;
  // //END EDIT

  // A few static variable declarations
  static int K = 4; // Parameter to be experimented with
  static int recursionLevel = -1; // This can be used to find out at which
                                  // level of the recursion you are in
  static listOfObjects<TrainInfoPerStation*> **sub;

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
    
    sub=new listOfObjects<TrainInfoPerStation*>*[(end-start+1)/K];
    listOfObjects<TrainInfoPerStation *> *temp=stnInfoList;
    int i=0;
    while(temp!=nullptr){
      if(i%K==0){
        sub[i/K]=temp;
      }
      temp=temp->next;
      i++;
    }
  }
  
  // Put your code for the core of QuicksortSimple here
  int randPivotIndex=rand()%(end-start+1)+start;
  
  // //EDIT
  //   cout<<"Initialised randPivotIndex: "<<randPivotIndex<<endl;
  // //END EDIT

  //Partitioning
  listOfObjects<TrainInfoPerStation*> *pivot=sub[randPivotIndex/K],*head=sub[start/K],*tail=sub[end/K];
  for(int i=0;i<randPivotIndex-(K*(randPivotIndex/K));i++){
    pivot=pivot->next;
  }
  for(int i=0;i<start-(K*(start/K));i++){
    head=head->next;
  }
  for(int i=0;i<end-(K*(end/K));i++){
    tail=tail->next;
  }
  listOfObjects<TrainInfoPerStation*> *lpivot,*rpivot;
  if(pivot==head){lpivot=pivot;} else{lpivot=pivot->prev;}
  if(pivot==tail){rpivot=pivot;} else{rpivot=pivot->next;}

  int pivotDay;
  for(int i=0;i<7;i++){
    if(pivot->object->daysOfWeek[i]){pivotDay=i;break;}
  }
  int pivotDep=pivot->object->depTime;
  
  
  while(true){
    bool flagcheck=true;
    // cout<<"Stuck in while(true)\n";
    while(lpivot!=head){
      bool flag=false;
      for(int i=0;i<7;i++){
        if(lpivot->object->daysOfWeek[i]){
          if(i<pivotDay){
            lpivot=lpivot->prev;
            break;
          }
          else if (i==pivotDay){
            if(lpivot->object->depTime<=pivotDep){
              lpivot=lpivot->prev;
              break;
            }
            else{
            flag=true;
            break;
          }
          }
          else{
            flag=true;
            break;
          }
        }
      }
      if(flag) break;
    }

    while(rpivot!=tail){
      bool flag=false;
      for(int i=0;i<7;i++){
        if(rpivot->object->daysOfWeek[i]){
          if(i>pivotDay){
            rpivot=rpivot->next;
            break;
          }
          else if (i==pivotDay){
            if(rpivot->object->depTime>=pivotDep){
              rpivot=rpivot->next;
              break;
            }
            else{
            flag=true;
            break;
          }
          }
          else{
            flag=true;
            break;
          }
        }
      }
      if(flag) break;
    }

    int lpivotDay,rpivotDay,lpivotDep,rpivotDep;
    for(int i=0;i<7;i++){
      if(lpivot->object->daysOfWeek[i]){lpivotDay=i;break;}
    }
    for(int i=0;i<7;i++){
      if(rpivot->object->daysOfWeek[i]){rpivotDay=i;break;}
    }
    lpivotDep=lpivot->object->depTime;
    rpivotDep=rpivot->object->depTime;

    if(lpivotDay<=pivotDay && rpivotDay>=pivotDay){
      if(lpivotDay<pivotDay){
        if(rpivotDay>pivotDay){
          break;
        }
        else if(rpivotDep>=pivotDep){
          break;
        }
      }
      else if(lpivotDep<=pivotDep){
        if(rpivotDay>pivotDay){
          break;
        }
        else if(rpivotDep>=pivotDep){
          break;
        }
      }
    }

    if(lpivotDay>=pivotDay && rpivotDay<=pivotDay){
      if(lpivotDay>pivotDay){
        if(rpivotDay<pivotDay){
          swap(lpivot->object->arrTime,rpivot->object->arrTime);
          swap(lpivot->object->daysOfWeek,rpivot->object->daysOfWeek);
          swap(lpivot->object->depTime,rpivot->object->depTime);
          swap(lpivot->object->journeyCode,rpivot->object->journeyCode);
          swap(lpivot->object->stopSeq,rpivot->object->stopSeq);
          flagcheck=false;
        }
        else if(rpivotDep<pivotDep){
          swap(lpivot->object->arrTime,rpivot->object->arrTime);
          swap(lpivot->object->daysOfWeek,rpivot->object->daysOfWeek);
          swap(lpivot->object->depTime,rpivot->object->depTime);
          swap(lpivot->object->journeyCode,rpivot->object->journeyCode);
          swap(lpivot->object->stopSeq,rpivot->object->stopSeq);
          flagcheck=false;
        }
      }
      else if(lpivotDep>pivotDep){
        if(rpivotDay<pivotDay){
          swap(lpivot->object->arrTime,rpivot->object->arrTime);
          swap(lpivot->object->daysOfWeek,rpivot->object->daysOfWeek);
          swap(lpivot->object->depTime,rpivot->object->depTime);
          swap(lpivot->object->journeyCode,rpivot->object->journeyCode);
          swap(lpivot->object->stopSeq,rpivot->object->stopSeq);
          flagcheck=false;
        }
        else if(rpivotDep<pivotDep){
          swap(lpivot->object->arrTime,rpivot->object->arrTime);
          swap(lpivot->object->daysOfWeek,rpivot->object->daysOfWeek);
          swap(lpivot->object->depTime,rpivot->object->depTime);
          swap(lpivot->object->journeyCode,rpivot->object->journeyCode);
          swap(lpivot->object->stopSeq,rpivot->object->stopSeq);
          flagcheck=false;
        }
      }
    }

    if(flagcheck){
    if(lpivotDay>=pivotDay && rpivotDay>=pivotDay){

      if(lpivotDay>pivotDay){
        if(rpivotDay>pivotDay){
          swap(lpivot->object->arrTime,pivot->prev->object->arrTime);
          swap(lpivot->object->daysOfWeek,pivot->prev->object->daysOfWeek);
          swap(lpivot->object->depTime,pivot->prev->object->depTime);
          swap(lpivot->object->journeyCode,pivot->prev->object->journeyCode);
          swap(lpivot->object->stopSeq,pivot->prev->object->stopSeq);

          swap(pivot->object->arrTime,pivot->prev->object->arrTime);
          swap(pivot->object->daysOfWeek,pivot->prev->object->daysOfWeek);
          swap(pivot->object->depTime,pivot->prev->object->depTime);
          swap(pivot->object->journeyCode,pivot->prev->object->journeyCode);
          swap(pivot->object->stopSeq,pivot->prev->object->stopSeq);

          pivot=pivot->prev;
          randPivotIndex--;
          flagcheck=false;
        }
        else if(rpivotDep>=pivotDep){
          swap(lpivot->object->arrTime,pivot->prev->object->arrTime);
          swap(lpivot->object->daysOfWeek,pivot->prev->object->daysOfWeek);
          swap(lpivot->object->depTime,pivot->prev->object->depTime);
          swap(lpivot->object->journeyCode,pivot->prev->object->journeyCode);
          swap(lpivot->object->stopSeq,pivot->prev->object->stopSeq);

          swap(pivot->object->arrTime,pivot->prev->object->arrTime);
          swap(pivot->object->daysOfWeek,pivot->prev->object->daysOfWeek);
          swap(pivot->object->depTime,pivot->prev->object->depTime);
          swap(pivot->object->journeyCode,pivot->prev->object->journeyCode);
          swap(pivot->object->stopSeq,pivot->prev->object->stopSeq);

          pivot=pivot->prev;
          randPivotIndex--;
          flagcheck=false;
        }
      }
      else if(lpivotDep>=pivotDep){
        if(rpivotDay>pivotDay){
          swap(lpivot->object->arrTime,pivot->prev->object->arrTime);
          swap(lpivot->object->daysOfWeek,pivot->prev->object->daysOfWeek);
          swap(lpivot->object->depTime,pivot->prev->object->depTime);
          swap(lpivot->object->journeyCode,pivot->prev->object->journeyCode);
          swap(lpivot->object->stopSeq,pivot->prev->object->stopSeq);

          swap(pivot->object->arrTime,pivot->prev->object->arrTime);
          swap(pivot->object->daysOfWeek,pivot->prev->object->daysOfWeek);
          swap(pivot->object->depTime,pivot->prev->object->depTime);
          swap(pivot->object->journeyCode,pivot->prev->object->journeyCode);
          swap(pivot->object->stopSeq,pivot->prev->object->stopSeq);

          pivot=pivot->prev;
          randPivotIndex--;
          flagcheck=false;
        }
        else if(rpivotDep>=pivotDep){
          swap(lpivot->object->arrTime,pivot->prev->object->arrTime);
          swap(lpivot->object->daysOfWeek,pivot->prev->object->daysOfWeek);
          swap(lpivot->object->depTime,pivot->prev->object->depTime);
          swap(lpivot->object->journeyCode,pivot->prev->object->journeyCode);
          swap(lpivot->object->stopSeq,pivot->prev->object->stopSeq);

          swap(pivot->object->arrTime,pivot->prev->object->arrTime);
          swap(pivot->object->daysOfWeek,pivot->prev->object->daysOfWeek);
          swap(pivot->object->depTime,pivot->prev->object->depTime);
          swap(pivot->object->journeyCode,pivot->prev->object->journeyCode);
          swap(pivot->object->stopSeq,pivot->prev->object->stopSeq);

          pivot=pivot->prev;
          randPivotIndex--;
          flagcheck=false;
        }
      }
    }
    }
    if(flagcheck){
    if(lpivotDay<=pivotDay && rpivotDay<=pivotDay){
      if(lpivotDay<pivotDay){
        if(rpivotDay<pivotDay){
          swap(rpivot->object->arrTime,pivot->next->object->arrTime);
          swap(rpivot->object->daysOfWeek,pivot->next->object->daysOfWeek);
          swap(rpivot->object->depTime,pivot->next->object->depTime);
          swap(rpivot->object->journeyCode,pivot->next->object->journeyCode);
          swap(rpivot->object->stopSeq,pivot->next->object->stopSeq);

          swap(pivot->object->arrTime,pivot->next->object->arrTime);
          swap(pivot->object->daysOfWeek,pivot->next->object->daysOfWeek);
          swap(pivot->object->depTime,pivot->next->object->depTime);
          swap(pivot->object->journeyCode,pivot->next->object->journeyCode);
          swap(pivot->object->stopSeq,pivot->next->object->stopSeq);

          pivot=pivot->next;
          randPivotIndex++;
        }
        else if(rpivotDep<=pivotDep){
          swap(rpivot->object->arrTime,pivot->next->object->arrTime);
          swap(rpivot->object->daysOfWeek,pivot->next->object->daysOfWeek);
          swap(rpivot->object->depTime,pivot->next->object->depTime);
          swap(rpivot->object->journeyCode,pivot->next->object->journeyCode);
          swap(rpivot->object->stopSeq,pivot->next->object->stopSeq);

          swap(pivot->object->arrTime,pivot->next->object->arrTime);
          swap(pivot->object->daysOfWeek,pivot->next->object->daysOfWeek);
          swap(pivot->object->depTime,pivot->next->object->depTime);
          swap(pivot->object->journeyCode,pivot->next->object->journeyCode);
          swap(pivot->object->stopSeq,pivot->next->object->stopSeq);

          pivot=pivot->next;
          randPivotIndex++;
        }
      }
      else if(lpivotDep<=pivotDep){
        if(rpivotDay<pivotDay){
          swap(rpivot->object->arrTime,pivot->next->object->arrTime);
          swap(rpivot->object->daysOfWeek,pivot->next->object->daysOfWeek);
          swap(rpivot->object->depTime,pivot->next->object->depTime);
          swap(rpivot->object->journeyCode,pivot->next->object->journeyCode);
          swap(rpivot->object->stopSeq,pivot->next->object->stopSeq);

          swap(pivot->object->arrTime,pivot->next->object->arrTime);
          swap(pivot->object->daysOfWeek,pivot->next->object->daysOfWeek);
          swap(pivot->object->depTime,pivot->next->object->depTime);
          swap(pivot->object->journeyCode,pivot->next->object->journeyCode);
          swap(pivot->object->stopSeq,pivot->next->object->stopSeq);

          pivot=pivot->next;
          randPivotIndex++;
        }
        else if(rpivotDep<=pivotDep){
          swap(rpivot->object->arrTime,pivot->next->object->arrTime);
          swap(rpivot->object->daysOfWeek,pivot->next->object->daysOfWeek);
          swap(rpivot->object->depTime,pivot->next->object->depTime);
          swap(rpivot->object->journeyCode,pivot->next->object->journeyCode);
          swap(rpivot->object->stopSeq,pivot->next->object->stopSeq);

          swap(pivot->object->arrTime,pivot->next->object->arrTime);
          swap(pivot->object->daysOfWeek,pivot->next->object->daysOfWeek);
          swap(pivot->object->depTime,pivot->next->object->depTime);
          swap(pivot->object->journeyCode,pivot->next->object->journeyCode);
          swap(pivot->object->stopSeq,pivot->next->object->stopSeq);

          pivot=pivot->next;
          randPivotIndex++;
        }
      }
    }
    }
    // //EDIT
    // cout<<"pivotDay: "<<pivotDay<<" lpivotDay: "<<lpivotDay<<" rpivotDay: "<<rpivotDay<<endl;
    // //END EDIT
  }

  // //EDIT
  // cout<<"Value of randPivotIndex before recursing: "<<randPivotIndex<<endl;
  // //END EDIT

  // //EDIT
  // string days[7] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};
  // TrainInfoPerStation *currInfo;
  // // if(stnInfoList==nullptr) cout<<"stnInfoList is null\n";
  // listOfObjects<TrainInfoPerStation *> *temp=stnInfoList;
  // while (stnInfoList != nullptr) {
  //   currInfo = stnInfoList->object;
  //   if (currInfo != nullptr) {
  //     cout << GREEN << "Day(s): " << RESET;
  //     for (int i=0; i<7; i++) {
	// if (currInfo->daysOfWeek[i]) cout << days[i] << " ";
  //     }
  //     cout << endl;
  //     cout << BLUE << "JourneyCode: " << currInfo->journeyCode << RESET << "\t";
  //     cout << RED << "Arr: " << RESET;
  //     if (currInfo->arrTime == -1) {
	// cout << "Starts";
  //     }
  //     else {
	// cout << currInfo->arrTime;
  //     }
  //     cout << RED << " Dep: " << RESET;
  //     if (currInfo->depTime == -1) {
	// cout << "Ends";
  //     }
  //     else {
	// cout << currInfo->depTime;
  //     }
  //     cout << endl;
  //   }
  //   stnInfoList = stnInfoList->next;
  // }
  // cout << endl;
  // stnInfoList=temp;
  // //END EDIT

  QuicksortSimple(stnInfoList,start,randPivotIndex-1);
  QuicksortSimple(stnInfoList,randPivotIndex+1,end);
  // Decrement recursion level before leaving the function
  recursionLevel--;
  return;
}

#endif
