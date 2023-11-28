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

TrainInfoPerStation * chooser ( listOfObjects<TrainInfoPerStation *> *stnInfoList, int i ) {

	
	listOfObjects<TrainInfoPerStation *> x = stnInfoList; 
	int k = 0;
	
  	while ( x != NULL ) {
  	
  		if ( x->daysOfWeek[i] == true ) {
  			
  			return x;
  		}
  	}	


}

void Quicksort(listOfObjects<TrainInfoPerStation *> *stnInfoList)
{

  for ( int i=0; i< 7; i++){
  
  	TrainInfoPerStation *k = chooser( stnInfoList, i);	
  
  }	
  
  // Put your code here.
}
