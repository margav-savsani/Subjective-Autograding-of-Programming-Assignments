#ifndef JOURNEY_H
#define JOURNEY_H

//This defines a journey of train between two stations
struct Journey {
  	
  	char from[32] , destination[32];
  	float departure , arrival;
  	bool tombStone;
  	bool empty;
  
  	
  	Journey(){
  		empty = true;
  	}		
};

#endif
