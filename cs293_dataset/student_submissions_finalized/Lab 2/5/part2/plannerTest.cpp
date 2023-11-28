#include "planner.cpp"
using namespace std;


// This is a rail planner program.
// Queries are of following type->
// 1). ADD <station A> <departure> <station B> <arrival>
//		This add a journey into our database

// 2). QUERY_STATION <station A> <time>
//		This gives all trains available from station A after time "time" in format <departure> <station B> 

// 3). QUERY_JOURNEY <station A> <time> <station B> 
//		This gives soonest possible journey with atmost 1 stop from station A to station B after time "time" in format <time> if no stop during journey or <departure time from source station A> <intermediate station> <departure time from intermediate station>

int main(){

	Planner railPlanner;
	
	railPlanner.run();
}	
