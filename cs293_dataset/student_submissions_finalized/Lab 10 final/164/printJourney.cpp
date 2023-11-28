#ifndef PRINT_JOURNEY_CPP
#define PRINT_JOURNEY_CPP

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

using namespace std;
// int convert(int i)
// {
//   return (i/100)*60+(i-(i/100)*100);
// }
void printStationInf(listOfObjects<TrainInfoPerStation *> *stnInfoList,Dictionary<int> stnNameToIndex)
{
	cout <<endl;
  listOfObjects<TrainInfoPerStation *> *currList, *expandedList,*result;
  TrainInfoPerStation *currInfo;
  string days[7] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};
  currList = stnInfoList;
  expandedList = nullptr;
  int listLength = 0;
  while (currList != nullptr) {
    currInfo = currList->object;
    if (currInfo != nullptr) {// Make as many copies of currInfo as the total count of days in the week
      int jCode = currInfo->journeyCode;
      int stSeq = currInfo->stopSeq;// when this train runs from/to this station
      int arrTime = currInfo->arrTime;
      int depTime = currInfo->depTime;
      for (int i=0; i < 7; i++) {
		if (currInfo->daysOfWeek[i]||(i==6&& currInfo->journeyCode==-1)||(i==6&& currInfo->journeyCode==-2)) {//also adds currInfo having journey code as -1 or -2
	  TrainInfoPerStation *newExpandedElement = new TrainInfoPerStation(jCode, stSeq, arrTime, depTime);
	  newExpandedElement->setDayOfWeek(i);
	  listOfObjects<TrainInfoPerStation *> *newExpandedListElement = new listOfObjects<TrainInfoPerStation *> (newExpandedElement);
	  if (expandedList == nullptr) {//checks if the list is empty or not
	    expandedList = newExpandedListElement;
		result = expandedList;
	  }
	  else {
	    expandedList->next = newExpandedListElement;
	    expandedList = expandedList->next;//inserts the next element
	  }
	  listLength++;
	}
	
      }
    }
    currList = currList->next;//iterates over the list
  }
  
  currList = result;
  while (currList != nullptr) {
    currInfo = currList->object;
    if (currInfo != nullptr) {
		if(currInfo->journeyCode==-1)//if journey code is -1
		{
			cout <<"Stop_Sequence: From "<<stnNameToIndex.getKeyAtIndex(currInfo->stopSeq)<<" to "<<stnNameToIndex.getKeyAtIndex(currInfo->depTime)<<endl;
			cout <<"-----------------------------------------------------------"<<endl<<"Journey Details : "<<stnNameToIndex.getKeyAtIndex(currInfo->arrTime)<<" to "<<stnNameToIndex.getKeyAtIndex(currInfo->depTime)<<endl<<"--------------------------------------------------------------"<<endl<<endl;
			currList=currList->next;
			continue;
		}
		if(currInfo->journeyCode==-2)// if journey code is -2
		{	
			cout <<"Stop_Sequence: From "<<stnNameToIndex.getKeyAtIndex(currInfo->arrTime)<<" to "<<stnNameToIndex.getKeyAtIndex(currInfo->depTime)<<endl;
			if(currInfo->stopSeq==1)
			{
				cout<< RED<<"CHANGE OF TRAIN REQUIRED"<<endl;//indicates change of train
			}
			currList=currList->next;
			continue;
		}
      cout << GREEN << "Day(s): " << RESET;
      for (int i=0; i<7; i++) {
	if (currInfo->daysOfWeek[i]) cout << days[i] << " ";
      }
      cout << endl;
      cout << BLUE << "JourneyCode: " << currInfo->journeyCode << RESET << "\t";
      cout << RED << "Arr: " << RESET;
      if (currInfo->arrTime == -1) {
	cout << "Starts";//prints start if time is -1
      }
      else {
	cout << currInfo->arrTime;
      }
      cout << RED << " Dep: " << RESET;
      if (currInfo->depTime == -1) {
	cout << "Ends";//prints en if time is -1
      }
      else {
	cout << currInfo->depTime;
      }
      cout << endl;
    }
    currList = currList->next;
  }
  cout << endl;
}

bool chec(int t1,TrainInfoPerStation*t2,int n,int k)//function chec checks time if the time is less than maxTransitTime or not
{
  for(int i=0;i<7;i++)
  {
    if(t2->daysOfWeek[i]==1)
    {
      if((t2->depTime)>=(t1)&&i-n==0&&(t2->depTime)-(t1)<=100*k)// if change is on same day
      {
        return true;
      }
      if((t2->depTime)<=(t1)&&(i-n==1||(i<n&&7+i-n==1))&&2400+(t2->depTime)-(t1)<=100*k)// if change is on different day
      {
        return true;
      }
    }
  }
  return false;
}

listOfObjects<TrainInfoPerStation*>* update(int s,StationAdjacencyList *adjacency,int j,int maxStopOvers,int maxTransitTime,int c,TrainInfoPerStation *trai,int tn,listOfObjects<TrainInfoPerStation *> **stationInfo,int start,int sstart)
{
  if(s==j)//base case for the reccursion
  {
    if(c<=maxStopOvers) 
    {
    listOfObjects<TrainInfoPerStation*>*re=new listOfObjects<TrainInfoPerStation*>(new TrainInfoPerStation(0,0,0,0));
    listOfObjects<TrainInfoPerStation*>*res=re;
    for (int i = 0; i < 7; i++)//seperates the days in to seperate stations of different days
    {
      if(trai->daysOfWeek[i]==1)//checks if bool is 1 or not
      {
      TrainInfoPerStation *train=new TrainInfoPerStation(trai->journeyCode,trai->stopSeq,trai->arrTime,trai->depTime);
      train->daysOfWeek[i]=1;
      re->next=new listOfObjects<TrainInfoPerStation*>(train);//adds the present train detais
      re=re->next;
      re->next=new listOfObjects<TrainInfoPerStation*>(new TrainInfoPerStation(-1,sstart,start,s));
      re=re->next;
      }
    }
    return res->next;    
    }
    else return nullptr;
  }
  listOfObjects<TrainInfoPerStation*>*result=new listOfObjects<TrainInfoPerStation*>(new TrainInfoPerStation(0,0,0,0));
  listOfObjects<TrainInfoPerStation*>*r=result;
  listOfObjects<StationConnectionInfo *> *to=adjacency[s].toStations;//finds the adjacent station of the current station
  while(to!=NULL)
  {
  listOfObjects<TrainInfoPerStation *> *tr=to->object->trains;
    while(tr!=NULL)
    {
      int k=tr->object->journeyCode;
      int check=c;
      int change=0;
      if(k!=tn){check=c+1;change=1;}
      listOfObjects<TrainInfoPerStation*>*t= update(to->object->adjacentStnIndex,adjacency,j,maxStopOvers,maxTransitTime,check,tr->object,k,stationInfo,start,s);//reccursion call       
      if(t!=NULL)
        {
          for(int i=0;i<7; i++)//cheks for the days with bool days of week true
          {
          listOfObjects<TrainInfoPerStation*>*t2=t;
          TrainInfoPerStation *trp=new TrainInfoPerStation(trai->journeyCode,trai->stopSeq,trai->arrTime,trai->depTime);
          if(trai->daysOfWeek[i]==1 )
          {
            bool b=false;
            trp->daysOfWeek[i]=1;
            listOfObjects<TrainInfoPerStation*>*st=stationInfo[s];
            while(st->object->journeyCode!=trp->journeyCode)//gets the station info of the required train 
            {
              st=st->next;
            }
            while(t2!=nullptr)
            {   
              bool ch;
              if(trp->depTime<st->object->arrTime)
              {
                ch=chec(st->object->arrTime,t2->object,i,maxTransitTime);
              }
              else ch=chec(st->object->arrTime,t2->object,i+1,maxTransitTime);//checks if the days is same day or not day 
              if(ch )
              {
                r->next=new listOfObjects<TrainInfoPerStation*>(trp);
                r=r->next;
                r->next=new listOfObjects<TrainInfoPerStation*>(new TrainInfoPerStation(-2,change,sstart,s));//adds a duumy element 
                r=r->next;
                while(t2->object->journeyCode!=-1)//loops until journey code is -1
                {
                  r->next=new listOfObjects<TrainInfoPerStation*>(t2->object);
                  r=r->next;
                  t2=t2->next;
                  if(t2==nullptr) break;
                }
                if(t2==nullptr) break;
                r->next=new listOfObjects<TrainInfoPerStation*>(t2->object);
                r=r->next;
                t2=t2->next;
              }
              else{
                while(t2->object->journeyCode!=-1)//loops until journeyCode -1
                {
                  t2=t2->next;
                  if(t2==nullptr) break;
                }
                if(t2==nullptr) break;
                t2=t2->next;
              }
            }
          }
         }
        }
      tr=tr->next;
    }
    to=to->next;
  }
  return result->next;
}


void Planner::printPlanJourneys(string srcStnName, string destStnName, int maxStopOvers, int maxTransitTime)
{
  // insert your code here
  Entry<int> *index_start=stnNameToIndex.get(srcStnName);  //stoes the entry of the source station
  Entry<int> *index_end=stnNameToIndex.get(destStnName);  //stores the entry of the destination station
  int i=index_start->value;
  int j=index_end->value;
  listOfObjects<StationConnectionInfo *> *toS=adjacency[i].toStations;
  listOfObjects<StationConnectionInfo *> *fromS=adjacency[j].fromStations;
  listOfObjects<int> *arr=new listOfObjects<int> (0);
  listOfObjects<int> *array=arr;
  listOfObjects<TrainInfoPerStation*>*station=new listOfObjects<TrainInfoPerStation*>(new TrainInfoPerStation(0,0,0,0));
  listOfObjects<TrainInfoPerStation *> *stat=station;

  while(toS!=NULL)//runs the loop until all the stations are covered
  {
  listOfObjects<TrainInfoPerStation *> *tra=toS->object->trains;

    while(tra!=NULL)
    {
      int tn=tra->object->journeyCode;
      listOfObjects<TrainInfoPerStation*>*lt= update(toS->object->adjacentStnIndex,adjacency,j,maxStopOvers,maxTransitTime,0,tra->object,tn,stationInfo,i,i);//if the code is present in from station of the destination station 
      if(lt!=NULL)
      {
        station->next=lt;//updates the station for the other times
        while(station->next!=NULL) {station=station->next;}
      }
      tra=tra->next;
    }

    toS=toS->next;
  }
  if(stat!=nullptr){
  printStationInf(stat->next,stnNameToIndex);}//prints the station info if the stat is not equal to nullptr
  else
  cout << "No direct journeys available" << endl;//print a statement if the stat is equal to nullptr

  
  return;
}
#endif