#ifndef PRINT_JOURNEY_CPP
#define PRINT_JOURNEY_CPP

#ifndef STD_HEADERS_H
#include "std_headers.h"
#include "planner.h"
#endif

using namespace std;

void printpath(listOfObjects<TrainInfoPerStation *>* ans, listOfObjects<Entry<int>>* f, string s){
	listOfObjects<TrainInfoPerStation *>* tra;
	listOfObjects<Entry<int>>* tra2;
	tra=ans->next;
	tra2=f->next;
	string days[7] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};
	cout<<"Available on ";
	for(int i=0; i<7; i++){
		if(tra->object->daysOfWeek[i]){
			cout<<days[i]<<" ";
		}
	}
	cout<<endl;
	int k=0;
	while(tra!=NULL){
		if(k==0){cout<<"stnname: "<<tra2->object.key<<" ";}
		if(k==1){cout<<"stnname: "<<tra2->object.key<<" waiting_time: "<<tra2->object.value <<" ";}
		cout<<"jrnycode: "<<tra->object->journeyCode<<" arrtime: "<<tra->object->arrTime;
		cout<<" -> ";	
		
		tra=tra->next;
		tra2=tra2->next;
		k=1;
	}
	cout<<s;
	cout<<endl;
}

//first-arrtime, second-deptime
int timedif(TrainInfoPerStation* first, TrainInfoPerStation* second){
	int j2,j;
	if(first->journeyCode==second->journeyCode){
		return 0;
	}
	for(int i=0; i<7; i++){
		if(first->daysOfWeek[i]){
			if(second->daysOfWeek[i] && second->depTime >= first->arrTime){
				return ((second->depTime)-(first->arrTime));
			}
			j=(i+1)%7;
			j2=2400-first->arrTime;
			while(second->daysOfWeek[j]==false){
				j=(j+1)%7;
				j2=j2+2400;
			}
			j2=j2+second->depTime;
			return j2;
		}
	}
}

listOfObjects<TrainInfoPerStation *>* findpath(int src_index, int dest_index, int maxstops, int maxtime, int prevjc, listOfObjects<TrainInfoPerStation *>* ans, TrainInfoPerStation* stime, StationAdjacencyList adjacency[], listOfObjects<TrainInfoPerStation *> *stationInfo[], listOfObjects<Entry<int>>* f, Dictionary<int> stnNameToIndex){

  	if(src_index==dest_index && maxstops!=-1){
		printpath(ans, f, stnNameToIndex.getKeyAtIndex(dest_index));
		//printStationInfo(ans);
		return NULL;
  	}
  	listOfObjects<StationConnectionInfo *>* b=adjacency[src_index].toStations;
	if(b==NULL || maxstops==-1){
		ans->next=NULL;
		f->next=NULL;
  	  	return NULL;
  	}

  	while(b!=NULL){
		listOfObjects<TrainInfoPerStation *>* c=b->object->trains;
		while(c!=NULL){
			int x=b->object->adjacentStnIndex;
			listOfObjects<TrainInfoPerStation *> *t=stationInfo[x];
			TrainInfoPerStation* r;
			while(t!=NULL){
				if(t->object->journeyCode==c->object->journeyCode){
					r=t->object;
					break;
				}
				t=t->next;
			}
			int k;
			if(stime->arrTime!=-6){
				k=timedif(stime,c->object);
				// if(c->object->depTime > maxtime + stime->arrTime){
				if(k > (maxtime*100)){
					c=c->next;
					continue;
				}
			}
			
			listOfObjects<TrainInfoPerStation *>* tra;
			tra=ans;
			while(tra->next!=NULL){
				tra=tra->next;
			}
			tra->next=new listOfObjects<TrainInfoPerStation *>(c->object);

			listOfObjects<Entry<int>>* tra2;
			tra2=f;
			while(tra2->next!=NULL){
				tra2=tra2->next;
			}
			tra2->next=new listOfObjects<Entry<int>>(k%100);
			tra2->next->object.key=stnNameToIndex.getKeyAtIndex(src_index);

			if(prevjc==c->object->journeyCode || prevjc==-5){
				findpath(b->object->adjacentStnIndex,dest_index,maxstops,maxtime,c->object->journeyCode, ans, r, adjacency, stationInfo, f, stnNameToIndex);
			}
			else{
				findpath(b->object->adjacentStnIndex,dest_index,maxstops-1,maxtime,c->object->journeyCode, ans, r, adjacency, stationInfo, f, stnNameToIndex);
			}
			tra->next=NULL;
			tra2->next=NULL;
			c=c->next;
		}
		b=b->next;
  	}
}

void Planner::printPlanJourneys(string srcStnName, string destStnName, int maxStopOvers, int maxTransitTime)
{

  	// insert your code here
	
  	// Whenever you need to print a journey, construct a
  	// listOfObjects<TrainInfoPerStation *> appropriately, and then
  	// use printStationInfo that we had used in Lab 7.
  	// printStationInfo is a private member function of
  	// the Planner class. It is declared in planner.h and implemented in
  	// planner.cpp

  	Entry<int> *src_pointer=stnNameToIndex.get(srcStnName); //finding source pointer in dict
  	Entry<int> *dest_pointer=stnNameToIndex.get(destStnName);
  	int src_index=src_pointer->value;
  	int dest_index=dest_pointer->value;
	listOfObjects<TrainInfoPerStation *>* ans;
	TrainInfoPerStation* a;
	a=new TrainInfoPerStation(-10,0,0,0);
	ans= new listOfObjects<TrainInfoPerStation *>(a);
	TrainInfoPerStation* p;
	p=new TrainInfoPerStation(-20, 0,-6,0);
	listOfObjects<Entry<int>>* f;
	f=new listOfObjects<Entry<int>>(-7);
  	findpath(src_index,dest_index,maxStopOvers,maxTransitTime, -5, ans, p, adjacency, stationInfo, f, stnNameToIndex);
  	return;
}

#endif
