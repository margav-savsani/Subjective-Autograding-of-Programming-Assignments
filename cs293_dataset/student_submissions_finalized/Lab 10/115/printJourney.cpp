#ifndef PRINT_JOURNEY_CPP
#define PRINT_JOURNEY_CPP

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

using namespace std;
	
void Planner::printPlanJourneys(string srcStnName, string destStnName, int maxStopOvers, int maxTransitTime)
{
	if(maxStopOvers<0||maxTransitTime<0)
	{
		return;
	}
	int srcstnidx=stnNameToIndex.get(srcStnName)->value;  // I am converting given string to the index in the dictionary
	int deststnidx=stnNameToIndex.get(destStnName)->value;// I am converting given string to the index in the dictionary
	listOfObjects<TrainInfoPerStation*>* FinalJourneyCodeslist=new listOfObjects<TrainInfoPerStation*>(NULL); // This is the final list of objects that is to be printed
	listOfObjects<TrainInfoPerStation*>* Iterator=FinalJourneyCodeslist; //Some iterator which will be useful in traversing the list of objects
	int* JourneyCodes=new int[512];//I am storing all the trains starting from the source station in this array
    int JourneyCodes_size=0;//corresponding int which is size of the above array, which will be changed whenever the array got modified or deleted
	int* StationIndices=new int[512];// I am storing all the stations in any **BFS** step
    int StationIndices_size=0;// corresponding int which is size of the above array, which will be changed whenever the above array got modified
	listOfObjects<TrainInfoPerStation*>* Iterator2=stationInfo[srcstnidx];// some iterator which is used in traversing the list of objects
	while(Iterator2!=NULL)
	{//adding all the journey codes starting from the source station
		JourneyCodes[JourneyCodes_size]=Iterator2->object->journeyCode;
        JourneyCodes_size++;
		Iterator2=Iterator2->next;
	}
	StationIndices[StationIndices_size]=srcstnidx;
    StationIndices_size++;
	while(StationIndices_size>0)//this while loop is for BFS levels like if there are n BFS levels, then this loop will repeat over n times
	{
		int no_of_stations=StationIndices_size;
		int* NewJourneyCodes=new int[512];
        int NewJourneyCodes_size=0;
		for(int j=0;j<JourneyCodes_size;j++)// This loop is for all journey codes still remained in the array
		{
			bool found=false;
			for(int i=0;i<no_of_stations&&!found;i++)// This loop is for all stations in the BFS level n
			{
				listOfObjects<StationConnectionInfo*>* Station_dep_Trains=adjacency[StationIndices[i]].toStations;
				while(Station_dep_Trains!=NULL&&!found)// This loop is for all stations adjacent to the stations in BFS level n,
				{
					listOfObjects<TrainInfoPerStation*>* Trains=Station_dep_Trains->object->trains;
					while(Trains!=NULL&&!found)
					{//checking track is in proper condition or not, I am not adding to the new journey codes unless track is good
						if(Trains->object->journeyCode==JourneyCodes[j]&&Station_dep_Trains->object->adjacentStnIndex==deststnidx)
						{// if dest station is reached in level n+1
							Iterator->next=new listOfObjects<TrainInfoPerStation*>(Trains->object);
							Iterator=Iterator->next;
							found=true;
						}
						else if(Trains->object->journeyCode==JourneyCodes[j] && Station_dep_Trains->object->adjacentStnIndex!=srcstnidx)
						{// track is good
							NewJourneyCodes[NewJourneyCodes_size]=JourneyCodes[j];
                            NewJourneyCodes_size++;
							found=true;
						}
						Trains=Trains->next;
					}
					Station_dep_Trains=Station_dep_Trains->next;
				}
			}
		}
        JourneyCodes_size=0;// JourneyCodes and NewJourneyCodes are different, so this step is just like modifying the array JourneyCodes
		for(int i=0;i<NewJourneyCodes_size;i++)
		{
			JourneyCodes[JourneyCodes_size]=NewJourneyCodes[i];
            JourneyCodes_size++;
		}
    	int* NewStationIndices=new int[512];
        int NewStationIndices_size=0;
		for(int i=0;i<no_of_stations;i++)
		{
			if(StationIndices[i]!=deststnidx)// I am not adding stations adjacent to destination because they already reached the destination
			{
				listOfObjects<StationConnectionInfo*>* newstations=adjacency[StationIndices[i]].toStations;
				while(newstations!=NULL)
				{// adding all the stations adjacent to the source station to the array
					NewStationIndices[NewStationIndices_size]=newstations->object->adjacentStnIndex;
					NewStationIndices_size++;
					newstations=newstations->next;
				}
			}
		}
		// This step modifies the station names, like it removes all the stations in level n, and adds all the stations in level n+1
    	StationIndices=new int[512];
        StationIndices_size=0;
    	for(int i=0;i<NewStationIndices_size;i++)
		{
			StationIndices[StationIndices_size]=NewStationIndices[i];
            StationIndices_size++;
		}
	}
	printStationInfo(FinalJourneyCodeslist);//finally printing
	return;
}

#endif
