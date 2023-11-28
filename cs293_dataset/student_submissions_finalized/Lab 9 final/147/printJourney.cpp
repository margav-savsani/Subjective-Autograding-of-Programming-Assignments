#ifndef PRINT_JOURNEY_CPP
#define PRINT_JOURNEY_CPP

#ifndef PLANNER_H
#include "planner.h"
#endif

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#include <queue>
#include <map>
using namespace std;


/*
  The graph representation of the railway network. A railway system can be represented as a directed weighted multigraph with:
  Vertex: a station in the network
  Edge: a journey from one stn to another, directed. Its weight(attributes) is (journeyCode, distance, startTime, endTime, platform, etc). There can be multiple edges between two vertices in both directions. Here the weight is journeyCode and can be thought of as coloring an edge with the color 'journeyCode'.
*/

/*
  Logic:
  Let's made the multigraph a graph by separating the colors! Our multigraph can be thoughout of as many intertwined graphs with edges all of one color/journeycode, all on the same vertices(nodes). The goal is to look at each of these internal graphs and find all graphs(journeycodes) in which A and B are connected. We keep queueing vertices (possibly the same one, but for a different edge) and going through paths. The goal at hand is to find all paths of the same color(journey code) from station A to station B. We start at station A, set queue = {A, color} for color in A.outedges. We then start off with {A, color1}. We iterate over possible reachable-by-a-color1-edge neighbors C of A, and for each neighbor check if color1 is among the journeycodes in the outdegree of C. If yes, we add {C, color1} to the queue, tick off the {A, C} edge with color color1, and move onto the next neighbor C' of A. 
  
  Basically we do the simultaneous BFSearch of all the internal graphs with the same queue (we could use different queues for each graph, labeled by color as well, that's a nice exercise to try).

  Implementation details:
  - Note that the pair {u, color} being in the queue means that there is an edge of color `color` out from vertex `u`, and that we must further investigate where this edge goes later.
*/

// Get the list of journeys as a listOfObjects<TrainInfoPerStation *>
// for the source station and then we can print it out by invoking
// printStationInfo that we had used in Lab 7.
// printStationInfo is a private member function of the Planner class
// It is declared in planner.h and implemented in planner.cpp
void Planner::printDirectJourneys(string srcStnName, string destStnName){
  
  listOfObjects<TrainInfoPerStation *> *journeys = nullptr; // stores ptrs to the TrainInfo objects of each journey's source station.

  typedef int color;
  
  // journeyCode to TrainInfo. This makes it easier to manage(an int is more like a color than a TrainInfo object).
  map<color, TrainInfoPerStation*> colormap;
  int srcIndex = stnNameToIndex.get(srcStnName)->value;
  for (auto journey = stationInfo[srcIndex]; journey; journey = journey->next)
    colormap[journey->object->journeyCode] = (journey->object);

  int destIndex = stnNameToIndex.get(destStnName)->value;
  
  // an edge to be investigated
  struct ToInvestigate{
    int endIndex; // index of the end node of the edge.
    color outEdgeColor; // the color of the edge.

    ToInvestigate(int endIndex, color outEdgeColor): endIndex(endIndex), outEdgeColor(outEdgeColor){}
  };

  queue<ToInvestigate> Q;
  
  for (auto connection = adjacency[srcIndex].toStations; connection; connection = connection->next){
    auto adjVertex = connection->object->adjacentStnIndex;
    for (auto edge = connection->object->trains; edge; edge = edge->next){
      Q.push(ToInvestigate(adjVertex, edge->object->journeyCode));
    }
  }

  while(!Q.empty()){
    ToInvestigate u = Q.front(); 
    Q.pop();

    if (u.endIndex == destIndex){
      auto newJourney = new listOfObjects<TrainInfoPerStation *>(colormap[u.outEdgeColor]);
      if (!journeys) journeys = newJourney;
      else{
        auto curr = journeys;
        for(; curr->next; curr = curr->next);
        curr->next = newJourney;
        newJourney->prev = curr;
      }
      continue; // no need to check this journey code(color) 's path further after destination, can move to the next element of the queue.
    }

    for (auto connection = adjacency[u.endIndex].toStations; connection; connection = connection->next){
      auto adjVertex = connection->object->adjacentStnIndex;
      for (auto edge = connection->object->trains; edge; edge = edge->next){
        if (edge->object->journeyCode != u.outEdgeColor) continue;
        else Q.push(ToInvestigate(adjVertex, u.outEdgeColor)); // continue exploring along that path - but wait for your turn, other colors at the same depth await now.
      }
    }
  }
  if (journeys) printStationInfo(journeys);
  else cout << "No direct journeys available" << endl;

  return;
}

#endif
