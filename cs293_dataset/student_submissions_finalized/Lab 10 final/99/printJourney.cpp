#ifndef PRINT_JOURNEY_CPP
#define PRINT_JOURNEY_CPP
#ifndef PLANNER_H
#include "planner.h"
#endif
#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

using namespace std;
// ======================================================================= CLASS STATION
class Station
{
   public:
      int index;
      listOfObjects<TrainInfoPerStation *> * trains;

      Station(int Index, listOfObjects<TrainInfoPerStation *> * Trains)
      {
         index = Index;
         trains = Trains;
      }
      Station()
      {
         index = -1;
         trains = nullptr;
      }
   
      bool isPresent(int jrnyCode)
      {
         listOfObjects<TrainInfoPerStation *> * tmp = trains;
         while (tmp != nullptr)
         {
            if (tmp->object->journeyCode == jrnyCode) return true;
            tmp = tmp->next;
         }
      }
};
// ========================================================================== CLASS PATH
class Path
{
   public:
      Station * arrStations;
      int numStations;

      Path(int num, Station listOfStations[])
      {
         arrStations = new Station[num];
         numStations = num;
         for (int i = 0; i < num; i++)
         {
            arrStations[i] = listOfStations[i];
         }
      }
      Path()
      {
         numStations = 0;
         arrStations = nullptr;
      }
};

// ============================================================= CLASS TRAINS AND STATIONS

class TrainStation
{
   public:
      Path path;
      listOfObjects<TrainInfoPerStation *>* trains;

      TrainStation()
      {
         trains = nullptr;
      }
      TrainStation(Path thisPath, listOfObjects<TrainInfoPerStation *>* thisTrains)
      {
         path = thisPath;
         trains = thisTrains;
      }
};

// ============================================================== FUNCTION DECLARATIONS HERE
void util1(int nextStnIndex, int destIndex, bool visited[], Station stnSeq[], int &pathIndex,
            listOfObjects<TrainInfoPerStation *>* stationInfo[],
            StationAdjacencyList adjacency[], listOfObjects<Path> * &allWays);

void util2(listOfObjects<TrainStation>* &allRoutes, Path path,
            int currStnNo, listOfObjects<TrainInfoPerStation *>* &tmp);

void util3(listOfObjects<TrainStation>* &filteredRoutes1, 
            listOfObjects<TrainStation>* allRoutes, int maxStopOvers);

void util4(listOfObjects<TrainStation>* & filteredRoutes2,
            listOfObjects<TrainStation>* filteredRoutes1, int maxTransitTime, StationAdjacencyList adjacency[]);

void print(TrainStation curr, Dictionary<int> stnNameToIndex);

// ==========================================================================================

void Planner::printPlanJourneys(string srcStnName, string destStnName, int maxStopOvers, int maxTransitTime)
{
   Entry<int> * src = stnNameToIndex.get(srcStnName);
   Entry<int> * dest = stnNameToIndex.get(destStnName);
   if (src == nullptr || dest == nullptr) { cout << "No journeys available\n"; return; }
   int srcIndex = src->value;
   int destIndex = dest->value;

   Station * stnSeq = new Station[numStations];
   int pathIndex = 0;
   bool * visited = new bool[DICT_SIZE];
   for (int i = 0; i < DICT_SIZE; i++) visited[i] = false;

   listOfObjects<Path> * allWays = nullptr; // stores all the paths from src to dest
   util1(srcIndex, destIndex, visited, stnSeq, pathIndex, stationInfo, adjacency, allWays);


   listOfObjects<TrainStation> * allRoutes = nullptr;

   // listOfObjects<listOfObjects<TrainInfoPerStation *>*>* allRoutes = nullptr;
   listOfObjects<Path> * allWaysCopy = allWays;
   while (allWaysCopy != nullptr)
   {
      listOfObjects<TrainInfoPerStation *> * tmp = nullptr;
      int currStnNo = 0;
      util2(allRoutes, allWaysCopy->object, currStnNo, tmp);
      allWaysCopy = allWaysCopy->next;
   }

   listOfObjects<TrainStation> * filteredRoutes1 = nullptr;
   util3(filteredRoutes1, allRoutes, maxStopOvers);

   listOfObjects<TrainStation>* filteredRoutes2 = nullptr;
   util4(filteredRoutes2, filteredRoutes1, maxTransitTime, adjacency);

   if (filteredRoutes2 == nullptr) cout << "No journeys available\n";;
   while (filteredRoutes2 != nullptr)
   {
      print(filteredRoutes2->object, stnNameToIndex);
      filteredRoutes2 = filteredRoutes2->next;
   }

}

void print(TrainStation curr, Dictionary<int> stnNameToIndex)
{
   cout << "Journey start\n";
   string srcStn = stnNameToIndex.getKeyAtIndex(curr.path.arrStations[0].index);
   cout << "Station: " << srcStn << endl;
   int pathIndex = 1;
   listOfObjects<TrainInfoPerStation *> * x = curr.trains;
   while (x != nullptr)
   {
      cout << "JourneyCode: " << x->object->journeyCode << "   ";
      if (x->object->arrTime == -1)
      {
         cout << "Arr: Starts   Dep: " << x->object->depTime << endl;
      }
      else
      {
         cout << "Arr: " << x->object->arrTime << "   Dep: " << x->object->depTime << endl;
      }
      cout << "Station: " << stnNameToIndex.getKeyAtIndex(curr.path.arrStations[pathIndex].index) << endl;
      pathIndex++;
      x = x->next;
   }
   cout << "Journey End\n";
}
// gets all possible paths from src to dest
void util1(int nextStnIndex, int destIndex, bool visited[], Station stnSeq[], int &pathIndex,
            listOfObjects<TrainInfoPerStation *>* stationInfo[],
            StationAdjacencyList adjacency[], listOfObjects<Path> * &allWays)
{
   visited[nextStnIndex] = true;
   Station nextStn(nextStnIndex, nullptr);
   stnSeq[pathIndex] = nextStn;
   pathIndex++;

   if (nextStnIndex == destIndex)
   {
      if (allWays == nullptr)
      {
         Path latest(pathIndex, stnSeq);
         allWays = new listOfObjects<Path>(latest);
      }
      else
      {
         listOfObjects<Path> * tmp = allWays;
         while (tmp->next != nullptr) tmp = tmp->next;
         Path latest(pathIndex, stnSeq);
         listOfObjects<Path> * last = new listOfObjects<Path>(latest);
         tmp->next = last;
         last->prev = tmp;
      }
   }

   else
   {
      listOfObjects<StationConnectionInfo *> *nextStnsList = adjacency[nextStnIndex].toStations;
      while (nextStnsList != nullptr)
      {
         int n = nextStnsList->object->adjacentStnIndex;
         if (!visited[n])
         {
            stnSeq[pathIndex - 1].trains = nextStnsList->object->trains;
            util1(n, destIndex, visited, stnSeq, pathIndex, stationInfo, adjacency, allWays);
         }
         nextStnsList = nextStnsList->next;
      }
   }
   pathIndex--;
   visited[nextStnIndex] = false;
}
// gets the trains of all possible paths, store in 
void util2(listOfObjects<TrainStation>* &allRoutes, Path path,
            int currStnNo, listOfObjects<TrainInfoPerStation *>* &tmp)
{
   // cout << "CURRSTN = " << currStnNo << endl;
   if (currStnNo + 1 == path.numStations)
   {
      // cout << "END OF PATH\n";
      if (allRoutes == nullptr)
      {
         // allRoutes = new listOfObjects<listOfObjects<TrainInfoPerStation *>*>(tmp);
         TrainStation curr(path, tmp);
         allRoutes = new listOfObjects<TrainStation>(curr);
      }
      else
      {
         listOfObjects<TrainStation>* other = allRoutes;
         while (other->next != nullptr) other = other->next;
         TrainStation curr(path, tmp);
         listOfObjects<TrainStation> * last = new listOfObjects<TrainStation>(curr);
         last->prev = other;
         other->next = last;
      }
      // tmp = nullptr;
      return;
   }
   else if (currStnNo + 1 > path.numStations) return;
   else
   {
      listOfObjects<TrainInfoPerStation *>* nextInList = path.arrStations[currStnNo].trains;
      while (nextInList != nullptr)
      {
         listOfObjects<TrainInfoPerStation *> * initTmp = tmp;
         if (tmp == nullptr)
         {
            tmp = new listOfObjects<TrainInfoPerStation *>(nextInList->object);
         }
         else
         {
            listOfObjects<TrainInfoPerStation *>* forTmp = tmp;
            while (forTmp->next != nullptr) forTmp = forTmp->next;
            listOfObjects<TrainInfoPerStation *> * latestTrain = new listOfObjects<TrainInfoPerStation *>(nextInList->object);
            latestTrain->next = nullptr;
            latestTrain->prev = forTmp;
            forTmp->next = latestTrain;
         }
         util2(allRoutes, path, currStnNo + 1, tmp);
         tmp = initTmp;
         nextInList = nextInList->next;
      }
   }
}

void util3(listOfObjects<TrainStation>* &filteredRoutes1, 
            listOfObjects<TrainStation>* allRoutes, int maxStopOvers)
{
   while (allRoutes != nullptr)
   {
      listOfObjects<TrainInfoPerStation *> * currWay = allRoutes->object.trains;
      int currStopOvers = 0;
      bool valid = true;
      while (currWay->next != nullptr)
      {
         // cout << "lll\n";
         if (currStopOvers > maxStopOvers) { valid = false; break; }
         if (currWay->object->journeyCode != currWay->next->object->journeyCode) {currStopOvers++; cout << "kkk\n"; if (currStopOvers > maxStopOvers) { valid = false; break; } }
         currWay = currWay->next;
      }
      if (valid)
      {
         if (filteredRoutes1 == nullptr)
         {
            TrainStation curr(allRoutes->object.path, allRoutes->object.trains);
            filteredRoutes1 = new listOfObjects<TrainStation>(curr);
         }
         else
         {
            listOfObjects<TrainStation>* crwlr = filteredRoutes1;
            while (crwlr->next != nullptr) crwlr = crwlr->next;
            TrainStation curr(allRoutes->object.path, allRoutes->object.trains);
            listOfObjects<TrainStation>* toAdd = new listOfObjects<TrainStation>(curr);
            toAdd->prev = crwlr;
            toAdd->next = nullptr;
            crwlr->next = toAdd;
         }
      }
      allRoutes = allRoutes->next;
   }
}

void util4(listOfObjects<TrainStation>* &filteredRoutes2,
            listOfObjects<TrainStation>* filteredRoutes1, int maxTransitTime, StationAdjacencyList adjacency[])
{
   while (filteredRoutes1 != nullptr)
   {
      listOfObjects<TrainInfoPerStation *>* currWay = filteredRoutes1->object.trains;
      bool srcLeaves[7];
      for (int i = 0; i < 7; i++)
      {
         srcLeaves[i] = currWay->object->daysOfWeek[i];
      } 
      bool valid = true;
      int index = 1;
      while (currWay->next != nullptr)
      {
         valid = false;
         if (currWay->object->journeyCode == currWay->next->object->journeyCode)
         {
            valid = true;
            currWay = currWay->next;
            continue;
         }
         int currStnIndx = filteredRoutes1->object.path.arrStations[index].index;

         for (int i = 0; i < 7; i++)
         {
            for (int j = i; j < 7; j++)
            {
               // cout << "277\n";
               if (currWay->object->daysOfWeek[i] && currWay->next->object->daysOfWeek[j])
               {
                  int timeDiff = (j - i) * 2400 + (currWay->next->object->depTime - currWay->object->arrTime);
                  // cout << timeDiff << endl;
                  if (timeDiff <= maxTransitTime)
                  {
                     valid = true;
                     break;
                  }
               }
            }
            if (valid) break;
         }
         if (!valid) break;
         else currWay = currWay->next;
      }
      if (valid)
      {
         if (filteredRoutes2 == nullptr)
         {
            TrainStation curr(filteredRoutes1->object.path, filteredRoutes1->object.trains);
            filteredRoutes2 = new listOfObjects<TrainStation>(curr);
         }
         else
         {
            listOfObjects<TrainStation>* crwlr = filteredRoutes2;
            while (crwlr->next != nullptr) crwlr = crwlr->next;
            TrainStation curr(filteredRoutes1->object.path, filteredRoutes1->object.trains);
            listOfObjects<TrainStation>* toAdd = new listOfObjects<TrainStation>(curr);
            toAdd->prev = crwlr;
            toAdd->next = nullptr;
            crwlr->next = toAdd;
         }
      }
      filteredRoutes1 = filteredRoutes1->next;
   }
}

#endif