#ifndef PRINT_JOURNEY_CPP
#define PRINT_JOURNEY_CPP

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

using namespace std;
  
void Planner::printPlanJourneys(string srcStnName, string destStnName, int maxStopOvers, int maxTransitTime)
{

  // Whenever you need to print a journey, construct a
  // listOfObjects<TrainInfoPerStation *> appropriately, and then
  // use printStationInfo that we had used in Lab 7.
  // printStationInfo is a private member function of
  // the Planner class. It is declared in planner.h and implemented in
  // planner.cpp
  //printStationInfo(listOfObjects<TrainInfoPerStation *> *stnInfoList)
  //Accessing the index of the trains 
  Entry<int>* stnEntry1 = stnNameToIndex.get(srcStnName);
  Entry<int>* stnEntry2 = stnNameToIndex.get(destStnName);
  int index1 = stnEntry1->value;
  int index2 = stnEntry2->value;
   // list of trains going from source.
  set<int>list1;
 

  listOfObjects<StationConnectionInfo *> *A = adjacency[index1].toStations;
  
  
  //list of all the trains going from source.

  while (A != nullptr)
  {

    
    StationConnectionInfo * infoA = A->object;

    listOfObjects<TrainInfoPerStation *> *tr = infoA->trains;

    while(tr != nullptr)
    {

      TrainInfoPerStation * trn = tr->object;

      int all = trn->journeyCode;
      list1.insert(all);

      tr = tr->next;
    }

    A = A->next;

  }

 
  // initialise a queue.
  // to store Station index 
 	list<int> que;
  // to store correspondence stationStop object defined in dictionary.h
  list< stationStop > supr;
  stationStop pr = stationStop(index1,-1,0);
  supr.push_back(pr);
	que.push_back(index1); // we insert the source station index.

  vector<bool> visited;
  visited.resize(DICT_SIZE,false);

  
	while(!( que.empty()) )
	{
		// Dequeue a vertex from queue and print it.
		int s = que.front();
		cout << s << " ";
    stationStop cur  = supr.front();
    //if the stopOvers of a station exceeds by maxStopOvers then no more check
    if(cur.getStopover() >maxStopOvers )
      supr.pop_front(cur);
    // current station we are in .
    listOfObjects<StationConnectionInfo *> *current = adjacency[s].toStations;

    while (current != nullptr)
    {   int stop= 0;
      StationConnectionInfo *infoC = current->object;

      int Jcode = infoC->adjacentStnIndex;
      

      //list of trains going to this Jcode  from current.
      listOfObjects<TrainInfoPerStation *> *tn = infoC->trains;
      set<int>list3;
      while(tn != nullptr)
      {
        TrainInfoPerStation * trn = tn->object;

        int all = trn->journeyCode;
        list3.insert(all);

        tn = tn->next;

      }

        // storing all the tostations station codes of the vertex.
      if (!visited[Jcode])
      { que.push_back(Jcode);
        // Mark the current node as visited and enqueue it
        set<int>list2;
        visited[Jcode] = true;
          // we wii enqueue only those tostations which have trains from list3.
          
        listOfObjects<StationConnectionInfo *> * frmStnTrn= adjacency[Jcode].toStations;

        //storing the list of trains going from that station Jcode to check whether to change the train or not.
        while (frmStnTrn != nullptr)
        {
          StationConnectionInfo * infoA = frmStnTrn->object;

          listOfObjects<TrainInfoPerStation *> *tr = infoA->trains;

          while(tr != nullptr)
          {

            TrainInfoPerStation * trn = tr->object;

            int all = trn->journeyCode;
            list2.insert(all);

            tr = tr->next;
          }

          frmStnTrn = frmStnTrn->next;

        }
        list1.insert(Jcode);
        set<int> ::iterator itr1;

        set<int> ::iterator itr2;
        //we will store the stations and their correspondence of 
        //stopovers,trncode in class stationStop.

        for (itr1 = list3.begin(); itr1 != list3.end(); itr1++) 
        {
    
          for (itr2 = list2.begin() ; itr2 != list2.end(); itr2++)
          {  int stp =stop;
            if(*itr1 == *itr2 )
            { stationStop tr = stationStop(Jcode , *itr1, cur.getStopover() );
              supr.push_back(tr);
            }
            else
            {
            
              //*itr1 is the train through which it is coming.
              stationStop ch = stationStop(Jcode ,*itr1,cur.getStopover()+1)
              supr.push_back(ch);
            }
          }
        } 
       list2.clear(); 
      }

      current = current->next;
      
      list3.clear();
    }

		que.pop_front();

  }	

    
  return;
}

#endif
