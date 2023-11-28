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


#include <bits/stdc++.h>
using namespace std;

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
// recursive calls), <<< you must implement random choice for pivot (i.e.
// each element in the list being sorted should be equally likely to
// be chosen as pivot) >>>, and each call to finding a random pivot
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
// 
// 
// 
// ----------------------MOST IMPORTANT-----------------------------
// The whole point of this assignment is to have you do this without
// converting the whole list to an array.
//
// Remember it is indeed possible to solve this problem using the
// function Quicksort with only stnInfoList as its argument.  However,
// if you are finding it difficult to implement Quicksort, you can
// implement QuicksortSimple instead.  Those who implement both
// Quicksort and QuicksortSimple potentially stand to gain some bonus
// points.



int ActualValue( listOfObjects<TrainInfoPerStation*> *currNode){
    int t;
    t = currNode->object->arrTime;

    for(int i=0; i<7; i++){
        if(currNode->object->daysOfWeek[i]){
            t = t + i * 10000;
            break;
        }
    }

    return t;
}





void printList( listOfObjects<TrainInfoPerStation *> *stnInfoList ){

    auto currNode = stnInfoList;
    int i = 0;

    cout << "LIST:- " << endl;

    while(currNode != nullptr){

        cout << i << "\t";

        // End
        currNode = currNode->next;
        i++;
    }

    cout << endl;

    currNode = stnInfoList;
    i = 0;

    while(currNode != nullptr){

        int t;
        t = currNode->object->arrTime;

        for(int i=0; i<7; i++){
            if(currNode->object->daysOfWeek[i]){
                t = t + i * 10000;
                break;
            }
        }

        cout << t << "\t";

        // End
        currNode = currNode->next;
        i++;
    }

    cout << endl;
}





bool lessthan( listOfObjects<TrainInfoPerStation *> *node1, listOfObjects<TrainInfoPerStation *> *node2 ){
    bool isless = false;

    for(int i=0; i<7; i++){
        if( node1->object->daysOfWeek[i] && node2->object->daysOfWeek[i] ){
            // Now check the arrTime as day of the week is same.
            if( node1->object->arrTime < node2->object->arrTime ){
                isless = true;
                break;
            }
            else{
                isless = false;
                break;
            }
        }
        else if( node1->object->daysOfWeek[i] ){
            isless = true;
            break;
        }
        else{
            isless = false;
            break;
        }

    }


    return isless;
}








void Planner::Quicksort(listOfObjects<TrainInfoPerStation *> *stnInfoList)
{
    // Find length of stnInfoList
    int len = 0;
    auto currNode = stnInfoList;
    while(currNode != nullptr){
        len++;
        currNode = currNode->next;
    }
    QuicksortSimple(stnInfoList, 0, len-1);
}













void Planner::QuicksortSimple(listOfObjects<TrainInfoPerStation *> *stnInfoList, int start, int end)
{

    static int K = 4; // Parameter to be experimented with
    static int recursionLevel = -1; // This can be used to find out at which
    recursionLevel++;
    static listOfObjects<TrainInfoPerStation *> **arr;
   

    // ::::::::::::::::::::::::::::::::::  MAKING SPECIAL NODES ARRAY ::::::::::::::::::::::::::::::::::::::::::
    if (recursionLevel == 0) {
        // Making the array containing pointers to floor(n/k) TrainInfoPerStation objects from the list.
        float n = end - start + 1;
        int lenOfArray = floor(n / K) + 1;
        // arr = new TrainInfoPerStation* [lenOfArray];
        // listOfObjects<TrainInfoPerStation *> **arr;
        arr = new listOfObjects<TrainInfoPerStation *> *[lenOfArray];
        //Inserting values in  the array 'arr'
        int arrIndex = 0; // index at array
        int i = 0;

        auto currNode = stnInfoList;
        while(currNode != nullptr){
            if( i % K == 0 ){
                // Insert this currNode in our array
                arr[ arrIndex ] = currNode;
                // arr.push_back(currNode);
                arrIndex++;
            }
            // End
            currNode = currNode->next;
            i++;
        }
    }
    // IMPORTANT NOTE: The sequence of listOfObejects pointers remains same throughout.





    // :::::::::::::::::::::::::::::::::  USUAL QUICKSORT FUNCTION, same as before :::::::::::::::::::::::::::::::
    if (start >= end) return;
    if (start < end){
        int q = Partition(stnInfoList, start, end, K, arr);
        QuicksortSimple(stnInfoList ,start, q);
        QuicksortSimple(stnInfoList, q+1, end);
    }
    // Decrement recursion level before leaving the function
    recursionLevel--;
    return;
}














// int Planner::Partition(int start, int finish, listOfObjects** arr){
int Planner::Partition(listOfObjects<TrainInfoPerStation *> *stnInfoList, int start, int finish, int K, listOfObjects<TrainInfoPerStation *> **arr){

    assert(start < finish);


    // ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;CHOOSING THE PIVOT ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    // First select a random index between 'start' and 'finish'
    int ri = start + rand() % (finish - start + 1);
    // Now access it in O(k) time
    // which means that I have to find its pointer in less than K steps.
    int spi = ri - ri % K;
    int t = ri % K;
    // Note that ri == spi + t
    auto spiPointer = arr[spi / K];
    // note that t <=  K
    for( int i=0; i<t; i++ ){
        spiPointer = spiPointer->next;
    }
    // Now spiPointer is the pointer to the pivot node.
    auto pivot = spiPointer;
    int pivotValue = ActualValue(pivot);




    // :::::::::::::::::::::::::::::::::USUAL PARTITION FUNCTION similar to before::::::::::::::::::::::::::::::::
    int i = start - 1;
    int temp = 1;
    // Need to start startNode at index start
    auto currNode = stnInfoList;
    while(temp < start + 1) {
        temp++;
        currNode = currNode->next;
    }
    auto startNode = currNode;

    int j = finish + 1;
    temp = 1;
    // Need to find node at index finish.
    currNode = stnInfoList;
    while(temp < finish + 1) {
        temp++;
        currNode = currNode->next;
    }
    auto finishNode = currNode;

    while(true){
        do{
            if(j <= finish) finishNode = finishNode->prev;
            j--;
        }
        // while( lessthan(pivot, finishNode) && j > start );
        while( pivotValue < ActualValue(finishNode) && j > start);
        do{
            if(i >= start && i < finish) startNode = startNode->next;
            i++;
        }
        // while( lessthan(startNode, pivot) );
        while( ActualValue(startNode) < pivotValue );

        if(i <= j){
            // swapping ith and jth elements.
            // which is basically just copying, as I can't change the structure of the nodes.
            auto temp = startNode->object;
            startNode->object = finishNode->object;
            finishNode->object = temp;
        }
        else{
            return j;
        }
        if(j == start){
            return j;
        }  
    }
}

#endif
