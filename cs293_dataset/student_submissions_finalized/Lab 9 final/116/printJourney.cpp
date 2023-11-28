#ifndef PLANNER_H
#include "planner.h"
#endif


#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

using namespace std;

void Planner::printDirectJourneys(string srcStnName, string destStnName)
{

  Entry<int>* stnEntry1 = stnNameToIndex.get(srcStnName);
  Entry<int>* stnEntry2 = stnNameToIndex.get(destStnName);
  int index1 = stnEntry1->value;
  int index2 = stnEntry2->value;

  listOfObjects<StationConnectionInfo *> *A = adjacency[index1].toStations;


  listOfObjects<StationConnectionInfo *> *B = adjacency[index2].fromStations;

  vector<list<int>> adj;
  //vector to store the adjacents edges.
  adj.resize(DICT_SIZE);
  //make source station as current.
  

  list<int> queue;
	queue.push_back(index1); // we insert the source station index.
  int s = index1;

  vector<bool> visited;
  visited.resize(DICT_SIZE,false);


	while( s != index2 )
	{
		// Dequeue a vertex from queue and print it
		s = queue.front();
		cout << s << " ";
    
      //stations currently we are exploring.
    listOfObjects<StationConnectionInfo *> *current  = A;

    Entry<int> array = stnNameToIndex.A;
    for (int i=0; i<DICT_SIZE ; i++){
      if( array[i].value = s){
        
      }
    }


        // Get all adjacent vertices of the dequeued
        // vertex s. If a adjacent has not been visited,
        // then mark it visited and enqueue it
        
    while (current != nullptr)
    {
       
      int Jcode = current->adjacentStnIndex;

        // storing all the tostations station codes of the vertex.
      if (!visited[Jcode])
      {
        // Mark the current node as visited and enqueue it

        visited[Jcode] = true;
        queue.push_back(Jcode);
      }

      listOfObjects<TrainInfoPerStation *> *tr  = current->trains;

      // storing list of all trains of tostation .
      while(tr != nullptr){
        int n = tr->journeyCode;
        listOfObjects<StationConnectionInfo *> *from = adjacency[Jcode].fromStations;


        tr = tr->next; 
      }
        current = current->next;
    }


		queue.pop_front();

		

  }
  return;
}
