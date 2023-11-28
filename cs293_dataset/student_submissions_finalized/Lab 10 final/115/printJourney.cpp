#ifndef PRINT_JOURNEY_CPP
#define PRINT_JOURNEY_CPP

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

using namespace std;

struct Direct_Journey
{
	int JourneyCode;
	string stn1;
	int daysOfWeek_1;
	int arrTime1;
	int depTime1;
	string stn2;
	int daysOfWeek_2;
	int arrTime2;
	int depTime2;
	void print_Drt_Journey()//print function for direct journey this will be linked to the print function for total journey
	{
		string days[7] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};
		cout << BLUE << "JourneyCode: " << JourneyCode << RESET << "\t"<<endl;
		cout << GREEN << stn1 <<"\t\t"<<stn2<<RESET<<endl;
		cout << RED << "Arr: " << RESET;
		if (arrTime1 == -1)
		{
			cout << "Starts";
		}
		else
		{
			cout << arrTime1;
		}
	  	cout << RED<<"\t    \t" << " Arr: " << RESET;
	  	if(arrTime2 == -1)
		{
			cout << "Starts";
		}
		else
		{
			cout << arrTime2;
		}
	  	cout << endl;
		cout << GREEN << "Day(s): " <<RESET<< days[daysOfWeek_1] <<GREEN<<"\t--->\t "<< "Day(s): " << RESET << days[daysOfWeek_2]<<endl;
		cout << RED << "Dep: " << RESET;
		if (depTime1 == -1)
		{
			cout << "Ends";
		}
		else
		{
			cout << depTime1;
		}
	  	cout << RED<<"\t    \t" << " Dep: " << RESET;
	  	if(depTime2 == -1)
		{
			cout << "Ends";
		}
		else
		{
			cout << depTime2;
		}
	  	cout << endl;
	}
};//This is the direct journey part, I mean without changing trains

struct Journey// This is the total journey from given station(source) to destination station
{
	Direct_Journey* Drt_jrny[DICT_SIZE];
	int no_of_parts;
	Journey()
	{
		for(int i=0;i<DICT_SIZE;i++)
		{
			Drt_jrny[i]=NULL;//initialising all to null
		}
		no_of_parts=0;
	}
	void add(Direct_Journey* A)//adds a direct journey to complete the total journey
	{
		Drt_jrny[no_of_parts]=A;
		no_of_parts++;
		return;
	}
	void change_last(Direct_Journey* A)//This will change the last pointer and only second part of the last pointer only will be changed 
	{
		if(no_of_parts==0)
		{
			Drt_jrny[0]=A;
			no_of_parts++;
			return;
		}
		Drt_jrny[no_of_parts-1]=A;
		return;
	}
	void copy(Journey* A)//This will copy all the pointers from this struct to the argument struct
	{
		A->no_of_parts=no_of_parts;
		for(int i=0;i<no_of_parts;i++)
		{
			A->Drt_jrny[i]=Drt_jrny[i];
		}
		return;
	}
	~Journey()//destructor
	{
		for(int i=0;i<no_of_parts;i++)
		{
			Drt_jrny[i]=NULL;
		}
	}
	void print_Journey()//this is the main print function which prints all the direct journeys, note this will print only one possibility
	{
		if(no_of_parts==0)
		{
			cout << "No Journey is found :("<<endl;
			return;
		}
		cout << "-----------------------"<<endl;
		if(no_of_parts>1)
		{
			cout << BLUE <<"No of stop overs: "<<no_of_parts-1<<RESET<<endl;
		}
		else
		{
			cout << BLUE << "Direct Journey"<<RESET<<endl;
		}
		for(int i=0;i<no_of_parts;i++)
		{
			Drt_jrny[i]->print_Drt_Journey();
			if(i<no_of_parts-1)
			{
				cout<<"****Change of train****"<<endl;
			}
		}
		cout << "-----------------------"<<endl;
		return;
	}
};

int arr_time(listOfObjects<TrainInfoPerStation*>* trains,int JourneyCode)// finds the arrival time for a train whose journey code is an argument in the list of trains(list of trains from a station) 
{
	while(trains!=NULL)
	{
		if(trains->object->journeyCode==JourneyCode)
		{
			return trains->object->arrTime;
		}
		trains=trains->next;
	}
	return -1;//if that journey code is not there in the trainInfostation
}

int dep_time(listOfObjects<TrainInfoPerStation*>* trains,int JourneyCode)// finds the departure time for a train whose journey code is an argument in the list of trains(list of trains from a station)
{
	while(trains!=NULL)
	{
		if(trains->object->journeyCode==JourneyCode)
		{
			return trains->object->depTime;
		}
		trains=trains->next;
	}
	return -1;//if that journey code is not there in the trainInfostation
}

void Planner::printPlanJourneys(string srcStnName, string destStnName, int maxStopOvers, int maxTransitTime)
{
	static Journey* Jrny=new Journey();
	static int JourneyCode;
	if(maxStopOvers<0)//If max stop overs is reached then return 
	{
		return;
	}
	if(srcStnName==destStnName)//If destination is reached, then print the journey
	{
		Jrny->print_Journey();
		return;
	}
	listOfObjects<StationConnectionInfo*>* adj=adjacency[stnNameToIndex.get(srcStnName)->value].toStations;//all the trains from the source station which are there in adjaceny lists
	listOfObjects<TrainInfoPerStation*>* trains=stationInfo[stnNameToIndex.get(srcStnName)->value];
	while(trains!=NULL)
	{
		string stn_name="#";
		int arr_stn2;
		int dep_stn2;
		while(adj!=NULL && stn_name=="#")
		{
			listOfObjects<TrainInfoPerStation *> * trains2=adj->object->trains;
			while(trains2!=NULL && stn_name=="#")
			{
				if(trains2->object->journeyCode==trains->object->journeyCode)
				{
					stn_name=stnNameToIndex.getKeyAtIndex(adj->object->adjacentStnIndex);
					arr_stn2=arr_time(stationInfo[adj->object->adjacentStnIndex],trains2->object->journeyCode);
					dep_stn2=dep_time(stationInfo[adj->object->adjacentStnIndex],trains2->object->journeyCode);
				}
				trains2=trains2->next;
			}
			adj=adj->next;
		}
		adj=adjacency[stnNameToIndex.get(srcStnName)->value].toStations;
		if(stn_name!="#")// If train is not going due to track problem or something else, we are removing those here
		{
			if(Jrny->no_of_parts==0)//if we just start the question or recursion level-0
			{
				for(int i=0;i<7;i++)//so we have to take care of all the days
				{
					if(trains->object->daysOfWeek[i])
					{
						Journey* NewJrny=new Journey();
						Direct_Journey* nxt_jrny=new Direct_Journey();
						nxt_jrny->JourneyCode=trains->object->journeyCode;
						nxt_jrny->stn1=srcStnName;
						nxt_jrny->arrTime1=trains->object->arrTime;
						nxt_jrny->depTime1=trains->object->depTime;
						if(trains->object->depTime>trains->object->arrTime)
						{
							nxt_jrny->daysOfWeek_1=i;
						}
						else if(trains->object->depTime<trains->object->arrTime)
						{
							nxt_jrny->daysOfWeek_1=(i+1)%7;
						}
						nxt_jrny->stn2=stn_name;
						nxt_jrny->arrTime2=arr_stn2;
						nxt_jrny->depTime2=dep_stn2;
						if(nxt_jrny->depTime1<nxt_jrny->arrTime2)
						{
							nxt_jrny->daysOfWeek_2=nxt_jrny->daysOfWeek_1;
						}
						else if(nxt_jrny->depTime1>nxt_jrny->arrTime2)
						{
							nxt_jrny->daysOfWeek_2=(nxt_jrny->daysOfWeek_1+1)%7;
						}
						NewJrny->add(nxt_jrny);
						Journey* Dummy=Jrny;
						Jrny=NewJrny;
						int Dummy1=JourneyCode;
						JourneyCode=trains->object->journeyCode;//static variables
						printPlanJourneys(stn_name,destStnName,maxStopOvers,maxTransitTime);
						Jrny=Dummy;
						JourneyCode=Dummy1;
					}
				}
				trains=trains->next;
				continue;
			}
			if(trains->object->journeyCode==JourneyCode)//If the previous part journey is to continued
			{
				Journey* NewJrny=new Journey();
				Jrny->copy(NewJrny);
				Direct_Journey* nxt_jrny=new Direct_Journey();
				nxt_jrny->JourneyCode=JourneyCode;//copying all the contents from the remaining part journey
				nxt_jrny->stn1=NewJrny->Drt_jrny[NewJrny->no_of_parts-1]->stn1;
				nxt_jrny->daysOfWeek_1=NewJrny->Drt_jrny[NewJrny->no_of_parts-1]->daysOfWeek_1;
				nxt_jrny->arrTime1=NewJrny->Drt_jrny[NewJrny->no_of_parts-1]->arrTime1;
				nxt_jrny->depTime1=NewJrny->Drt_jrny[NewJrny->no_of_parts-1]->depTime1;
				nxt_jrny->stn2=stn_name;//changing the second half part of the previous part journey 
				nxt_jrny->arrTime2=arr_stn2;
				nxt_jrny->depTime2=dep_stn2;
				if(nxt_jrny->depTime2>nxt_jrny->arrTime2)// just taking care of the days from which trains start and trains end
				{
					if(NewJrny->Drt_jrny[NewJrny->no_of_parts-1]->depTime2>arr_stn2)
					{
						nxt_jrny->daysOfWeek_2=(NewJrny->Drt_jrny[NewJrny->no_of_parts-1]->daysOfWeek_2+1)%7;
					}
					else
					{
						nxt_jrny->daysOfWeek_2=NewJrny->Drt_jrny[NewJrny->no_of_parts-1]->daysOfWeek_2;
					}
				}
				else//If the day is changed between arrival and departure
				{
					if(NewJrny->Drt_jrny[NewJrny->no_of_parts-1]->depTime2>arr_stn2)
					{
						nxt_jrny->daysOfWeek_2=(NewJrny->Drt_jrny[NewJrny->no_of_parts-1]->daysOfWeek_2+2)%7;
					}
					else
					{
						nxt_jrny->daysOfWeek_2=(NewJrny->Drt_jrny[NewJrny->no_of_parts-1]->daysOfWeek_2+1)%7;
					}
				}

				NewJrny->change_last(nxt_jrny);
				Journey* Dummy=Jrny;
				Jrny=NewJrny;//using static variable so I have to copy all the static variables and store it
				printPlanJourneys(stn_name,destStnName,maxStopOvers,maxTransitTime);
				Jrny=Dummy;
				trains=trains->next;//changing back the static values to its previous values
				continue;
			}
			//If previous part journey is not being used, so I have to decrease no of max stop overs 
			bool found=false;
			int a3=-1;
			int a1=Jrny->Drt_jrny[Jrny->no_of_parts-1]->daysOfWeek_2;
			int a2=Jrny->Drt_jrny[Jrny->no_of_parts-1]->arrTime2;
			//assuming time taken in travelling between 2 adjacent stations is less than 24 hrs
			//assuming maxTransitTime is less than 24hrs
			if(trains->object->depTime > a2 && trains->object->depTime < a2+maxTransitTime)
			{
				if(trains->object->depTime<trains->object->arrTime)//assuming any train won't stop at a station for more than 24hrs
				{
					if(trains->object->daysOfWeek[(a1-1)%7])
					{
						a3=(a1-1)%7;
						found=true;
					}
				}
				else
				{
					if(trains->object->daysOfWeek[a1])
					{
						a3=a1;
						found=true;
					}
				}
			}
			if(trains->object->depTime < a2 && trains->object->depTime +2400< a2+maxTransitTime)
			{
				if(trains->object->depTime<trains->object->arrTime)//assuming any train won't stop at a station for more than 24hrs
				{
					if(trains->object->daysOfWeek[a1])
					{
						a3=a1;
						found=true;
					}
				}
				else
				{
					if(trains->object->daysOfWeek[(a1+1)%7])
					{
						a3=(a1+1)%7;
						found=true;
					}
				}
			}
			if(found && maxStopOvers>0)// trains exists satisfying maxTransitTime and days conditions
			{
				Journey* NewJrny=new Journey();
				Jrny->copy(NewJrny);
				Direct_Journey* nxt_jrny=new Direct_Journey();

				nxt_jrny->JourneyCode=trains->object->journeyCode;
				nxt_jrny->stn1=srcStnName;
				nxt_jrny->daysOfWeek_1=a3;
				nxt_jrny->arrTime1=trains->object->arrTime;
				nxt_jrny->depTime1=trains->object->depTime;
				nxt_jrny->stn2=stn_name;
				nxt_jrny->arrTime2=arr_stn2;
				nxt_jrny->depTime2=dep_stn2;
				if(arr_stn2>trains->object->depTime)
				{
					nxt_jrny->daysOfWeek_2=nxt_jrny->daysOfWeek_1;
				}
				else
				{
					nxt_jrny->daysOfWeek_2=(nxt_jrny->daysOfWeek_1+1)%7;
				}
				NewJrny->add(nxt_jrny);

				Journey* Dummy=Jrny;
				Jrny=NewJrny;
				int Dummy2=JourneyCode;
				JourneyCode=trains->object->journeyCode;
				printPlanJourneys(stn_name,destStnName,maxStopOvers-1,maxTransitTime);
				JourneyCode=Dummy2;
				Jrny=Dummy;
			}
		}
		trains=trains->next;//going to the next train
	}
	return;
}
#endif