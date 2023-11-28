#ifndef PRINT_JOURNEY_CPP
#define PRINT_JOURNEY_CPP

#ifndef PLANNER_H
#include "planner.h"
#endif
#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

using namespace std;

void Planner::printPlanJourneys(string srcStnName, string destStnName, int maxStopOvers, int maxTransitTime)
{

  static int recur = 0; // to maintain recurence
  int id1;
  id1 = stnNameToIndex.get(srcStnName)->value; // id of source station
  static int Nojourneyfound = 0;               // if journeyis not found

  listOfObjects<StationConnectionInfo *> *AdjacencyList = adjacency[id1].toStations; // adjacencylist of source station

  listOfObjects<StationConnectionInfo *> *listOfStations; // this would contain the adjacency list when it is expanded
  int counter = 0;
  listOfObjects<StationConnectionInfo *> *Linker; // helps in linking different elements of listofstations
  if (AdjacencyList != nullptr)
  {
    while (AdjacencyList != nullptr)
    {
      // cout << "Inside This loop" << endl;
      listOfObjects<TrainInfoPerStation *> *Trains = AdjacencyList->object->trains;
      while (Trains != nullptr)
      {

        bool *Days = Trains->object->daysOfWeek;

        for (int i = 0; i < 7; i++)
        {

          if (Days[i] == true) // we split a journey based on the day it travels, so a train travelling on m,w,f would be split into 2 different jounreyss
          {
            if (counter == 1)
            {
              Linker = listOfStations;
              listOfStations = listOfStations->next;
            }

            StationConnectionInfo *StaionElement = new StationConnectionInfo();
            TrainInfoPerStation *TrainElement = new TrainInfoPerStation(Trains->object->journeyCode, Trains->object->stopSeq, Trains->object->arrTime, Trains->object->depTime);
            TrainElement->daysOfWeek[i] = true;
            listOfObjects<TrainInfoPerStation *> *ListofTrains = new listOfObjects<TrainInfoPerStation *>(TrainElement);
            StaionElement->trains = ListofTrains;
            StaionElement->adjacentStnIndex = AdjacencyList->object->adjacentStnIndex;
            listOfObjects<StationConnectionInfo *> *Element = new listOfObjects<StationConnectionInfo *>(StaionElement);

            listOfStations = Element;
            if (counter == 1)
            {
              Linker->next = listOfStations;
              listOfStations->prev = Linker;
            }
            counter = 1;
          }
        }
        Trains = Trains->next;
      }
      AdjacencyList = AdjacencyList->next;
    }

    while (listOfStations->prev != nullptr)
    {
      listOfStations = listOfStations->prev;
    }

    static int flag = 0;

    int jc2;
    jc2 = stnNameToIndex.get(destStnName)->value;
    int limit = maxStopOvers;
    int excedd = 0;
    static listOfObjects<TrainInfoPerStation *> *lasttrain; // maintaining a list of prev trains in a particular journey
    static listOfObjects<string> *NameofStations;           // maintains a list of stations we passes through
    static listOfObjects<int> *TransitTime;                 // maintains a list of transit time between 2 trains

    recur++;
    while (listOfStations != nullptr)
    {
      listOfObjects<TrainInfoPerStation *> *traingoing = listOfStations->object->trains; // List of Trains between 2 stations

      if (recur == 1)
      {

        flag = 0; // setting flag to 0

        listOfObjects<string> *NameofStationsElement = new listOfObjects<string>(srcStnName); // adding source station to the list of stations
        NameofStations = NameofStationsElement;

        lasttrain = traingoing; // equating the lasttrain to traingoing for 1 recurence so that we can move forward as there would be no last train for 1st journey
      }

      // while (traingoing != nullptr)
      // {

      if (lasttrain->object->journeyCode == traingoing->object->journeyCode || limit > 0) // matching the current code with the traincode stored in queue for conforming direct journey. If the station is adjacent to source, we dont need to match codes, hence -1
      {
        if (!(lasttrain->object->journeyCode == traingoing->object->journeyCode)) // this means we changed trains , hence limit decreses
        {
          limit = limit - 1;
          excedd = 1;
        }
        else
        {
          excedd = 0;
        }

        if (excedd == 1) // if the trains changes we need to check for trasist time
        {
          int arrivalTime;
          int dayofarrival;
          int departureTime = traingoing->object->depTime; // setting departure time as the time when train leaves the station
          int dayofdept;

          listOfObjects<TrainInfoPerStation *> *IncomingTrain = stationInfo[id1];
          while (IncomingTrain != nullptr)
          {
            if (IncomingTrain->object->journeyCode == lasttrain->object->journeyCode)
            {
              arrivalTime = IncomingTrain->object->arrTime; // setting arrival time as the time the previous train arrives at the station
              break;
            }
            IncomingTrain = IncomingTrain->next;
          }
          for (int i = 0; i < 7; i++)
          {
            if (traingoing->object->daysOfWeek[i] == true) // calculating the day on which this train travels
            {
              dayofdept = i;
            }
          }

          for (int i = 0; i < 7; i++)
          {
            if (lasttrain->object->daysOfWeek[i] == true) // calculating the day on which this train travels
            {
              dayofarrival = i;
            }
          }
          if (arrivalTime < lasttrain->object->depTime) // if the arrival time of the previous train on this station is less than its departure time from the previous station means we reach the next statio the next day
          {
            dayofarrival = (dayofarrival + 1) % 7;
          }
          int differneceinTime;
          int differenceInDays = dayofdept - dayofarrival;
          if (dayofarrival == 6 && dayofdept == 0) // Sat and Sun
          {
            differenceInDays = 1;
          }
          if (differenceInDays < 0) // For proper wrapping
          {
            differenceInDays += 7;
          }
          int difinHours = ((departureTime / 100) - (arrivalTime / 100)) * 100; // calculating the first 2 places in time and then subtracting then furthur multiplying by 100 to maintain the same form
          if (difinHours < 0)
          {
            difinHours += 2400; // If difference is -ve, we add 2400 to get correct and difference and then subtract 1 from dif in days
            
          }
          int difinMins = ((departureTime % 100) - (arrivalTime % 100));
          if (difinMins < 0) // If difference is -ve, we add 60 to get correct and difference and then subtract 100 from dif in hours
          {
            difinMins += 60;
            difinHours -= 100;
          }
          differneceinTime = difinHours + difinMins + (differenceInDays * 2400); // Calculating difference in time
          if (differneceinTime <= maxTransitTime && differneceinTime >= 0)       // Less than transist time specified and greater than 0
          {

            int adjstn;
            adjstn = listOfStations->object->adjacentStnIndex;
            string intermediate;
            intermediate = stnNameToIndex.getKeyAtIndex(adjstn);
            if (recur != 1) // Addind the trasit time for this particular switch to Transist time list
            {
              listOfObjects<int> *LastTransitTime = new listOfObjects<int>(differneceinTime);
              if (TransitTime == nullptr)
              {
                TransitTime = LastTransitTime;
              }
              else
              {
                TransitTime->next = LastTransitTime;
                TransitTime->next->prev = TransitTime;
                TransitTime = TransitTime->next;
              }
            }

            if (intermediate == destStnName) // If we reach destination station
            {
              listOfObjects<TrainInfoPerStation *> *LastTrainElement = new listOfObjects<TrainInfoPerStation *>(traingoing->object); // we add this train to the list Last train
              if (recur == 1)
              {
                lasttrain = nullptr;
              }
              if (lasttrain == nullptr)
              {
                lasttrain = LastTrainElement;
              }
              else
              {
                lasttrain->next = LastTrainElement;
                lasttrain->next->prev = lasttrain;
                lasttrain = lasttrain->next;
              }

              flag = 1; // to indicate that we have reached the destination

              listOfObjects<string> *NameofStationsElement = new listOfObjects<string>(intermediate); // we also add the name of station to this name of stations list
              NameofStations->next = NameofStationsElement;
              NameofStations->next->prev = NameofStations;
              NameofStations = NameofStations->next;
            }

            else
            {
              // Exactly same as the except, we keep flag=0 and recall the function for intermediate and destination station

              listOfObjects<TrainInfoPerStation *> *LastTrainElement = new listOfObjects<TrainInfoPerStation *>(traingoing->object);
              if (recur == 1)
              {
                lasttrain = nullptr;
              }
              if (lasttrain == nullptr)
              {
                lasttrain = LastTrainElement;
              }
              else
              {
                lasttrain->next = LastTrainElement;
                lasttrain->next->prev = lasttrain;
                lasttrain = lasttrain->next;
              }

              listOfObjects<string> *NameofStationsElement = new listOfObjects<string>(intermediate);
              NameofStations->next = NameofStationsElement;
              NameofStations->next->prev = NameofStations;
              NameofStations = NameofStations->next;

              printPlanJourneys(intermediate, destStnName, limit, maxTransitTime);
            }
          }
          else
          {
            // These are add as dummy entries , which get discraded in the very next. This helps in keeping the program uniform when loop doesnt pass the max transit time time if statement and doesnt create new entries for various list
            if (recur != 1)
            {

              listOfObjects<int> *LastTransitTime = new listOfObjects<int>(0);
              if (TransitTime == nullptr)
              {
                TransitTime = LastTransitTime;
              }
              else
              {
                TransitTime->next = LastTransitTime;
                TransitTime->next->prev = TransitTime;
                TransitTime = TransitTime->next;
              }
            }
            listOfObjects<TrainInfoPerStation *> *LastTrainElement = new listOfObjects<TrainInfoPerStation *>(traingoing->object);
            if (recur == 1)
            {
              lasttrain = nullptr;
            }
            if (lasttrain == nullptr)
            {
              lasttrain = LastTrainElement;
            }
            else
            {
              lasttrain->next = LastTrainElement;
              lasttrain->next->prev = lasttrain;
              lasttrain = lasttrain->next;
            }

            listOfObjects<string> *NameofStationsElement = new listOfObjects<string>("TEMP");
            NameofStations->next = NameofStationsElement;
            NameofStations->next->prev = NameofStations;
            NameofStations = NameofStations->next;
          }
          limit++;
        }
        else
        {
          // This same case as chaning of trains case except we add 0 as transit time as time doesnt change
          int adjstn;
          adjstn = listOfStations->object->adjacentStnIndex;
          string intermediate;
          intermediate = stnNameToIndex.getKeyAtIndex(adjstn);

          if (recur != 1)
          {
            listOfObjects<int> *LastTransitTime = new listOfObjects<int>(0);
            if (TransitTime == nullptr)
            {
              TransitTime = LastTransitTime;
            }
            else
            {
              TransitTime->next = LastTransitTime;
              TransitTime->next->prev = TransitTime;
              TransitTime = TransitTime->next;
            }
          }

          if (intermediate == destStnName) // If we reach destination station, we add it to the printer for printing journey at the end
          {
            flag = 1;                                                                                                              // to indicate that we have reached the destination
            listOfObjects<TrainInfoPerStation *> *LastTrainElement = new listOfObjects<TrainInfoPerStation *>(traingoing->object); // we add this train to the list Last train
            if (recur == 1)
            {
              lasttrain = nullptr;
            }
            if (lasttrain == nullptr)
            {
              lasttrain = LastTrainElement;
            }
            else
            {
              lasttrain->next = LastTrainElement;
              lasttrain->next->prev = lasttrain;
              lasttrain = lasttrain->next;
            }

            listOfObjects<string> *NameofStationsElement = new listOfObjects<string>(intermediate); // we also add the name of station to this name of stations list
            NameofStations->next = NameofStationsElement;
            NameofStations->next->prev = NameofStations;
            NameofStations = NameofStations->next;
          }

          else
          {
            // Excatly same as change of trains else case.
            listOfObjects<TrainInfoPerStation *> *LastTrainElement = new listOfObjects<TrainInfoPerStation *>(traingoing->object);
            if (recur == 1)
            {
              lasttrain = nullptr;
            }
            if (lasttrain == nullptr)
            {
              lasttrain = LastTrainElement;
            }
            else
            {
              lasttrain->next = LastTrainElement;
              lasttrain->next->prev = lasttrain;
              lasttrain = lasttrain->next;
            }

            listOfObjects<string> *NameofStationsElement = new listOfObjects<string>(intermediate);
            NameofStations->next = NameofStationsElement;
            NameofStations->next->prev = NameofStations;
            NameofStations = NameofStations->next;

            printPlanJourneys(intermediate, destStnName, limit, maxTransitTime);
          }
        }
        listOfObjects<TrainInfoPerStation *> *Printingtrains = lasttrain; // Creating copies of main list for printing purposes as we would need to transerve the list and we would lost the location of last added element
        listOfObjects<string> *PrintingNames = NameofStations;            // Creating copies of main list for printing purposes as we would need to transerve the list and we would lost the location of last added element
        listOfObjects<int> *PrintingTime = TransitTime;                   // Creating copies of main list for printing purposes as we would need to transerve the list and we would lost the location of last added element
        if (flag == 1)                                                    // if we have reached destination station
        {
          Nojourneyfound = 1; // TO INDICATE journey has been formed
          if (recur != 1)
          {

            while (PrintingTime->prev != nullptr) // moving the front the list to print all the entries
            {
              PrintingTime = PrintingTime->prev;
            }
          }

          while (Printingtrains->prev != nullptr) // moving the front the list to print all the entries
          {
            Printingtrains = Printingtrains->prev;
          }
          while (PrintingNames->prev != nullptr) // moving the front the list to print all the entries
          {
            PrintingNames = PrintingNames->prev;
          }

          cout << "***************POSSIBLE JOURNEY******************" << endl;
          while (Printingtrains != nullptr)
          {
            cout << PrintingNames->object << ">>>>>>>>>>" << PrintingNames->next->object << endl; // Printing the name of the station between which the train runs
            // CODE FOR PRINTING STATION INFO RECYCLED FROM PLANNAR.CPP
            TrainInfoPerStation *currInfo = Printingtrains->object;
            string days[7] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};
            if (currInfo != nullptr)
            {
              cout << "Day(s): ";
              for (int i = 0; i < 7; i++)
              {
                if (currInfo->daysOfWeek[i])

                  cout << days[i] << " ";
              }
              cout << endl;
              cout << "JourneyCode: " << currInfo->journeyCode << "\t";
              cout << "Arr: ";
              if (currInfo->arrTime == -1)
              {
                cout << "Starts";
              }
              else
              {
                cout << currInfo->arrTime;
              }
              cout << " Dep: ";
              if (currInfo->depTime == -1)
              {
                cout << "Ends";
              }
              else
              {
                cout << currInfo->depTime;
              }
              cout << endl;
            }
            if (Printingtrains->next != nullptr)
            {
              cout << "==========="
                   << "Transit Time : " << PrintingTime->object << "  ===========" << endl;
              PrintingTime = PrintingTime->next;
            }
            // CODE FOR PRINTING STATION INFO RECYCLED FROM PLANNAR.CPP
            PrintingNames = PrintingNames->next;
            Printingtrains = Printingtrains->next;
          }
          cout << "**************************************************" << endl;
          cout << endl;
          flag = 0;
        }
        if (recur != 1)
        {
          // THIS SIMILAR TO HOW WE MOVE BACK IN THE CASE OF DFS AFTER VERY DISCOVERING AND REACHING TILL THE END
          NameofStations = NameofStations->prev;
          lasttrain = lasttrain->prev;
          TransitTime = TransitTime->prev;
        }
      }
      // lasttrain = traingoing;
      // cout << "Change of Trains" << endl;
      // traingoing = traingoing->next;
      // }

      //  = jc->next;jc
      // cout << "Change of Stations" << endl;

      listOfStations = listOfStations->next;
    }
    recur--;

    if (Nojourneyfound == 0 && recur == 0)
    {

      cout << "No journeys available" << endl;
    }
    else if (recur == 0) // We traceback to the 1st element of the printer so that we can supply it to printStationInfo
    {
      // RESETING ALL THE VALUES OF THE STATIC VARIABLES
      Nojourneyfound = 0;
      flag = 0;
      NameofStations = nullptr;
      lasttrain = nullptr;
      TransitTime = nullptr;
    }

    // Get the list of journeys as a listOfObjects<TrainInfoPerStation *>
    // for the source station and then we can print it out by invoking
    // printStationInfo that we had used in Lab 7.
    // printStationInfo is a private member function of the Planner class
    // It is declared in planner.h and implemented in planner.cpp
  }

  return;
}

#endif
