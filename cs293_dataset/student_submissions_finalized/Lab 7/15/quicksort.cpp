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

void Quicksort(listOfObjects<TrainInfoPerStation *> *stnInfoList)
{
    // Put your code here.
    cout << stnInfoList->object->depTime << endl;
    listOfObjects<TrainInfoPerStation *> *l1, *l2;
    int n = rand();
    int i=0;
    l1 = stnInfoList;
    while (l1->next != nullptr)
    {
        if(i==n){break;}
        l1=l1->next;
    }
    l2=l1->next;
    Quicksort(l1);
    Quicksort(l2);

}

// int partition(int A[],int start,int end){
//   int pivot=A[end];
//   int j=end,i=start;
//   while(true){
//     while(A[j]>pivot){
//       j--;
//     }
//     while(A[i]<=pivot){
//       i++;
//     }
//     if(j>i){
//       // cout<<"haha"<<endl;
//       swap(A[i],A[j]);
//     }
//     else{
//       return j;
//     }
//   }
// }

// void quicksort(int A[],int start,int end){
//   if(start>=end)return;
//   else{
//     // cout<<"hello"<<endl;
//     int mid=partition(A,start,end);
//     cout<<mid<<endl;
//     if(mid==end){
//       quicksort(A,start,mid-1);
//       return;
//     }
//     quicksort(A,start,mid);
//     quicksort(A,mid+1,end);
//   }
// }