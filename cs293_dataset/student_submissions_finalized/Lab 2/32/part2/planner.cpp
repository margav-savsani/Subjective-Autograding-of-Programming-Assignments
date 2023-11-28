#ifndef PLANNER_H
#define PLANNER_H
#include <math.h>

#include<iostream>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<fstream>
#include <vector>
#include "planner.cpp"

using namespace std;

struct Station
{
  // define suitable fields here
  char station_one[300];
  float start_time = -999;
  char station_two[300];

  float finish_time = -999;
};

class Planner
{
  // define suitable fields here

  private:
     int N = 300;
     vector <Station> A[300]; // Create an array of vectors of type Station

  public:



  int hashValue(char station_one[])
  {
    // Calculate Hash value like in dictionary.cpp
  	const int p=31, modn=67;
  	int hashValue = 0;
  	long int pow=1;

  	for(int i=0; station_one[i] != '\0'; i++)
    {
  		hashValue = (hashValue + (station_one[i] +1 -'A')*pow);
  		pow = (pow*p)%modn;
    }

  	float fracin = 0.618034* hashValue;
  	float frac = fracin - floor(fracin);
  	hashValue = floor(N*frac);
  	return hashValue;
   }





   Planner() //Constructor
   {
  	 N= 300;
     new vector<Station> ;
   }



   void query_station(char station_one[], float start_time)
   {
  	int location = hashValue(station_one);
  	int flag=0;

  	for(int j= 0; j < A[location].size() ; j++) //Move through the vector corresponding to the
  	{                                           // key station_one

      if(strcmp(A[location].at(j).station_one, station_one)==0 and A[location].at(j).start_time >= start_time)
      { // If we find an acceptable station, print it

         cout<<A[location].at(j).start_time<<" "<<A[location].at(j).station_two<<"\n";
         flag = 1;
      }


    }

    if(flag == 0)
    cout<<"ERROR\n"; // If no acceptable station found, error
   }


   void add(struct Station e)
   {
  	  int index = hashValue(e.station_one);
  	  A[index].push_back(e); // Add a new member to vector
   }


   // For command QUERY_JOURNEY
   void query_journey(char station_one[], float start_time, char station_two[])
   {
       int location = hashValue(station_one);
       int done = 0, val;
       float time, min_time=9999;
       char st[300];
       int index;

       for(int j = 0; j < A[location].size() ; j++)
       {
          // Find the min starting time of train
          if((A[location].at(j).start_time < min_time) and (A[location].at(j).start_time >= start_time))
          {
             min_time = A[location].at(j).start_time;
             strcpy(st, A[location].at(j).station_two); // Store the destination's name in st
             time = A[location].at(j).finish_time; //end time
             val = j;
          }
        }


        // If going directly, print the time
        if( strcmp(st, station_two) == 0)
        {
            cout<<min_time<<"\n";
            done = 1;
        }


        // If min time is taking one intermediate stop
        if(strcmp(st, station_two) != 0)
        {
            index = hashValue(st); // hash value of intermediate stop

            for(int i = 0; i < A[index].size(); i++)
            {
                if((strcmp((A[index].at(i).station_two), station_two) == 0) and A[index].at(i).start_time >= time)
                {
                    // If an acceptable entry to station_two is found print it
                    done = 1;
                    cout<<min_time<<" "<<A[index].at(0).station_one<<" "<<A[index].at(i).start_time<<"\n";

                    break;
                }
            }

            if(done == 0) // If entry not found try looking for direct route to station_two
            {
               min_time = 9999;
               for(int j = 0; j < A[location].size() ; j++)
               {
                  if(A[location].at(j).start_time < min_time and strcmp(A[location].at(j).station_two, station_two) == 0)
                 {
                    // If a dircet route is found
                    min_time = A[location].at(j).start_time;
                    strcpy(st, A[location].at(j).station_two);
                    time = A[location].at(j).finish_time; // reaching time
                    val = j;
                    done = 1;
                 }
               }

               if(done == 1)
               cout<<min_time<<"\n"; // Print the time to reach
            }
        }


        // If no such station found, error
        if(done == 0)
        cout<<"ERROR\n";
    }

};

#endif


