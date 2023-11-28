#ifndef PRINT_JOURNEY_CPP
#define PRINT_JOURNEY_CPP

#ifndef PLANNER_H
#include "planner.h"
#endif

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

using namespace std;
int arrivalTimeOfTrain(int journeyCodeOfPreviousTrain, int stnIdxOfSource, listOfObjects<StationConnectionInfo*>* adjStations){
	while(adjStations){
		if(adjStations->object->adjacentStnIndex == stnIdxOfSource){
			break;
		}
		adjStations = adjStations->next;
	}
	listOfObjects<TrainInfoPerStation*>* trains = adjStations->object->trains;
	while(trains){
		if(trains->object->journeyCode == journeyCodeOfPreviousTrain){
			return trains->object->arrTime;
		}
		trains = trains->next;
	}
	return -1;
}

struct LongJourney{
	int numberOfStopOversUsed;
	int* stopStationsIdx;
	int* trainToBoard;
	int* dayOfBoarding;
	int* transitTime;
	LongJourney(int n,int srcStnIdx){
		numberOfStopOversUsed = 0;
		stopStationsIdx = new int[n+1];
		trainToBoard = new int[n+1];
		dayOfBoarding = new int[n+1];
		transitTime = new int[n+1];
		for(int i=0;i<n+1;i++){
			stopStationsIdx[i] = -1;
			trainToBoard[i] = -1;
			dayOfBoarding[i] = -1;
			transitTime[i] = -1;
		}
	}
	LongJourney(const LongJourney& j){
		numberOfStopOversUsed = j.numberOfStopOversUsed;
		int n = numberOfStopOversUsed;
		stopStationsIdx = new int[n+1];
		trainToBoard = new int[n+1];
		dayOfBoarding = new int[n+1];
		transitTime = new int[n+1];
		for(int i=0;i<n+1;i++){
			stopStationsIdx[i] = j.stopStationsIdx[i];
			trainToBoard[i] = j.trainToBoard[i];
			dayOfBoarding[i] = j.dayOfBoarding[i];
			transitTime[i] = j.transitTime[i];
		}
	}
	~LongJourney(){
		delete[] stopStationsIdx;
		delete[] trainToBoard;
		delete[] dayOfBoarding;
		delete[] transitTime;
	}
};
void Planner::printPlanJourneys(string srcStnName, string destStnName, int maxStopOvers, int maxTransitTime)
{
	static int recursionLevel = -1;
	recursionLevel++;
	static int destStnIndex;
	static listOfObjects<LongJourney*>* possibleJourneys;
	static int journeyCodeOfPreviousTrain;
	static int arrivalDayOfPreviousTrain;
	static int currentStnIndex=0;
	static int prevStationIndex;
	static LongJourney *journeyBeingChecked;
	if(recursionLevel == 0){
		maxStopOvers++;
        destStnIndex = stnNameToIndex.get(destStnName)->value;
		possibleJourneys = nullptr;
		journeyCodeOfPreviousTrain = -1; // Initially, a dummy value
		currentStnIndex = stnNameToIndex.get(srcStnName)->value;
		journeyBeingChecked = new LongJourney(maxStopOvers,currentStnIndex);
		// Change usage of above variable
	}
	
	if(maxStopOvers<0){
		recursionLevel--;
		return;
	}
	// Using DFS
	listOfObjects<StationConnectionInfo*>* adjacentStation = adjacency[currentStnIndex].toStations;
	int tempStationIndex = currentStnIndex;
	int tempprevStationIndex = prevStationIndex;
	int temparrivalDayOfPreviousTrain = arrivalDayOfPreviousTrain;
	int tempjourneyCodeOfPreviousTrain = journeyCodeOfPreviousTrain;

	if(currentStnIndex == destStnIndex){
		listOfObjects<LongJourney*>* toAdd = new listOfObjects<LongJourney*>(new LongJourney(*journeyBeingChecked));
		toAdd -> next = possibleJourneys;
		possibleJourneys = toAdd;
		recursionLevel--;
		return;
	}
	int arrivalDayOfCurrentTrain;
	if(journeyCodeOfPreviousTrain!=-1){
		int t2=arrivalTimeOfTrain(journeyCodeOfPreviousTrain,prevStationIndex,adjacency[currentStnIndex].fromStations);
		listOfObjects<TrainInfoPerStation*>* trains_from_previous_station = stationInfo[prevStationIndex];
		while(trains_from_previous_station->object->journeyCode != journeyCodeOfPreviousTrain){
			trains_from_previous_station = trains_from_previous_station->next;
		}
		int t1=trains_from_previous_station->object->depTime;
		if(t1>t2){
			arrivalDayOfCurrentTrain = (temparrivalDayOfPreviousTrain+1)%7;
		}
	}
	prevStationIndex = currentStnIndex;
	while(adjacentStation){
		listOfObjects<TrainInfoPerStation*> *trainsGoing = adjacentStation->object->trains;
		//From planner.cpp printStationInfo function to get expanded list of trains
		listOfObjects<TrainInfoPerStation*>* currList = trainsGoing;
		listOfObjects<TrainInfoPerStation*>* expandedList = nullptr;
		int listLength = 0;
		// Finding day of arrival
		while (currList != nullptr) {
			TrainInfoPerStation* currInfo = currList->object;
			if (currInfo != nullptr) {
				// Make as many copies of currInfo as the total count of days in the week
				// when this train runs from/to this station
				int jCode = currInfo->journeyCode;
				int stSeq = currInfo->stopSeq;
				int arrTime = currInfo->arrTime;
				int depTime = currInfo->depTime;

				for (int i=0; i < 7; i++) {
					if (currInfo->daysOfWeek[i]) {
						TrainInfoPerStation *newExpandedElement = new TrainInfoPerStation(jCode, stSeq, arrTime, depTime);
						if (newExpandedElement == nullptr) {
							logFile << "Memory allocation failure." << endl;
							cerr << "Memory allocation failure." << endl;
							continue;
						}
						newExpandedElement->setDayOfWeek(i);

						listOfObjects<TrainInfoPerStation *> *newExpandedListElement = new listOfObjects<TrainInfoPerStation *> (newExpandedElement);
						if (newExpandedListElement == nullptr) {
							logFile << "Memory allocation failure." << endl;
							cerr << "Memory allocation failure." << endl;
							continue;
						}

						if (expandedList == nullptr) {
							expandedList = newExpandedListElement;
						}
						else {
							newExpandedListElement->next = expandedList;
							expandedList->prev = newExpandedListElement;
							expandedList = newExpandedListElement;
						}
						listLength++;
					}
				}
			}
			currList = currList->next;
		}

		while(expandedList){
			currentStnIndex = adjacentStation->object->adjacentStnIndex;
			TrainInfoPerStation* currTrain = expandedList->object;
			if(journeyCodeOfPreviousTrain == -1 || journeyCodeOfPreviousTrain!=currTrain->journeyCode){
				int dayOfDeparture;
				for(int i=0;i<7;i++){
					if(currTrain->daysOfWeek[i]){
						dayOfDeparture=i;
						break;
					}
				}
				if(journeyCodeOfPreviousTrain != -1){
					if(!maxStopOvers){
						expandedList = expandedList->next;
						continue;
					}
					int dayDifference = (7+dayOfDeparture-arrivalDayOfCurrentTrain)%7;
					int t1 = arrivalTimeOfTrain(tempjourneyCodeOfPreviousTrain,tempprevStationIndex,adjacency[tempStationIndex].fromStations);
					t1 = (t1/100)*60+t1%100;
					int transitTime = 24*60-t1 + currTrain->depTime/100*60 + currTrain->depTime%100 + 24*60*(dayDifference-1);
					transitTime = (transitTime+24*60*7)%(24*60*7);
					if(maxTransitTime*60 < transitTime){
						expandedList = expandedList->next;
						continue;
					}
					journeyBeingChecked->transitTime[journeyBeingChecked->numberOfStopOversUsed] = transitTime;
				}
				journeyBeingChecked->trainToBoard[journeyBeingChecked->numberOfStopOversUsed] = currTrain->journeyCode;
				journeyBeingChecked->stopStationsIdx[journeyBeingChecked->numberOfStopOversUsed] = tempStationIndex;
				journeyBeingChecked->dayOfBoarding[journeyBeingChecked->numberOfStopOversUsed] = dayOfDeparture;
				arrivalDayOfPreviousTrain = dayOfDeparture;
				journeyBeingChecked->numberOfStopOversUsed++;
				journeyCodeOfPreviousTrain = currTrain->journeyCode;
				prevStationIndex = tempStationIndex;
				printPlanJourneys(srcStnName,destStnName,maxStopOvers-1,maxTransitTime);
				journeyCodeOfPreviousTrain = tempjourneyCodeOfPreviousTrain;
				journeyBeingChecked->numberOfStopOversUsed--;
				expandedList = expandedList->next;
				continue;
			}
			// If train not to be changed
			int dayOfDeparture;
			for(int i=0;i<7;i++){
				if(currTrain->daysOfWeek[i]){
					dayOfDeparture=i;
					break;
				}
			}
			int dayDifference = (7+dayOfDeparture-temparrivalDayOfPreviousTrain)%7;
			listOfObjects<TrainInfoPerStation*>* trains_from_previous_station = stationInfo[tempprevStationIndex];
			while(trains_from_previous_station->object->journeyCode != journeyCodeOfPreviousTrain){
				trains_from_previous_station = trains_from_previous_station->next;
			}
			int t1=trains_from_previous_station->object->depTime;
			int t2=currTrain->depTime;
			int travelTime = 24*60-t1/100*60 - (t1%60) + t2/100*60+t2%60 + 24*60*(dayDifference-1);
			travelTime = (travelTime+24*60*7)%(24*60*7);
			arrivalDayOfPreviousTrain = dayOfDeparture;
			if(travelTime<24*60){
				prevStationIndex = tempStationIndex;
				printPlanJourneys(srcStnName,destStnName,maxStopOvers,maxTransitTime);
			}
			expandedList = expandedList->next;
		}
		adjacentStation = adjacentStation->next;
	}
	prevStationIndex = tempprevStationIndex;
	// Printing Final Answer
	if(recursionLevel==0){
		int count =0;
		while(possibleJourneys){
			listOfObjects<LongJourney*>* x = possibleJourneys;
			possibleJourneys = possibleJourneys->next;
			// listOfObjects<TrainInfoPerStation*>* toAdd = new 
			cout<<BLUE<<"==========Option "<<count<<"==========\n"<<GREEN;
			for(int i=0; i< x->object->numberOfStopOversUsed;i++){
				int jc = x->object->trainToBoard[i];
				int stnIdx = x->object->stopStationsIdx[i];
				listOfObjects<TrainInfoPerStation*>* trains = stationInfo[stnIdx];
				while(trains->object->journeyCode != jc){
					trains = trains->next;
				}
				if(x->object->transitTime[i]!=-1){
					cout<<GREEN<<"Wait Time: "<<RED<<x->object->transitTime[i]/60<<" hours "<<x->object->transitTime[i]%60<<" minutes "<<endl;
				}
				cout<<GREEN<<"Journey Code: "<<RED<<jc<<GREEN<<"\tStation: "<<RED<<stnNameToIndex.getKeyAtIndex(stnIdx)<<GREEN<<"\tTime: "<<RED<<trains->object->depTime<<GREEN<<"\tDay: "<<RED<<x->object->dayOfBoarding[i]<<endl;
			}
			count++;
			delete x->object;
			delete x;
		}
		cout<<RESET;
	
	}
	recursionLevel--;
	return;
}

#endif
