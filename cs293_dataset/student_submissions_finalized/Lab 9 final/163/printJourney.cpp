#ifndef PRINT_JOURNEY_CPP
#define PRINT_JOURNEY_CPP

#ifndef PLANNER_H
#include "planner.h"
#endif

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

using namespace std;

class Node
{
public:
    int index;
    listOfObjects<TrainInfoPerStation *> *trains;
    listOfObjects<TrainInfoPerStation *> *trains2;

    Node(int index)
    {
        this->index = index;
        trains = trains2 = nullptr;
    }
};

listOfObjects<TrainInfoPerStation *> *trainCheck(listOfObjects<TrainInfoPerStation *> *train, listOfObjects<TrainInfoPerStation *> *trainsTill1)
{   // train is the given train from Stn1 to Stn2(itermidiate stations)
    // trainsTill1 is the list of trains from source to Stn1
    // we are checking if given train is continued from source station or it came from some other station.
    while (trainsTill1 != nullptr) // traversing the linked list
    {
        if (trainsTill1->object->journeyCode == train->object->journeyCode)
        {
            return trainsTill1; // train is coming from source, so add it in the list by returning
        }
        trainsTill1 = trainsTill1->next;
    }
    return nullptr; // train came from some other stop, so nullptr returned to add nothing
}

listOfObjects<TrainInfoPerStation *> *BFS(listOfObjects<Node *> *queue, listOfObjects<Node *> *last, int indexStn1, int indexStn2, listOfObjects<TrainInfoPerStation *> *available, listOfObjects<TrainInfoPerStation *> *intermediate, StationAdjacencyList *adjacency)
{
    if (queue != nullptr) // Iterating in the queue
    {
        listOfObjects<StationConnectionInfo *> *temp = adjacency[queue->object->index].toStations; // list of adjacent stations from the first station in queue
        while (temp != nullptr) // checking the adjacent stations
        {
            if (temp->object->adjacentStnIndex != indexStn1) // else, we looped back to starting station, so need need to check else
            {
                if (temp->object->adjacentStnIndex != indexStn2) // if we didn't reach station2 yet
                {
                    listOfObjects<Node *> *node = new listOfObjects<Node *>(new Node(temp->object->adjacentStnIndex));
                    listOfObjects<TrainInfoPerStation *> *trains = temp->object->trains; // list of trains from this temp station
                    while (trains != nullptr) // iterating over trains
                    {
                        if (node->object->trains != nullptr) 
                        {
                            listOfObjects<TrainInfoPerStation *> *train = trainCheck(trains, queue->object->trains); // if this train is coming from src, we add it to the list
                            if (train != nullptr)
                            {
                                node->object->trains2->next = new listOfObjects<TrainInfoPerStation *>(train->object);
                                node->object->trains2 = node->object->trains2->next;
                            }
                        }
                        else
                        {
                            listOfObjects<TrainInfoPerStation *> *train = trainCheck(trains, queue->object->trains); // if this train is coming from src, we add it to the list
                            if (train != nullptr)
                            {
                                node->object->trains = new listOfObjects<TrainInfoPerStation *>(train->object);
                                node->object->trains2 = node->object->trains;
                            }
                        }
                        trains = trains->next;
                    }
                    if (node->object->trains != nullptr)
                    {
                        last->next = node;
                        last = node;
                    }
                }
                else // else we reached station2
                {
                    listOfObjects<TrainInfoPerStation *> *trains = temp->object->trains;
                    while (trains != nullptr) // adding the trains to the available
                    {
                        if (available == nullptr)
                        {
                            listOfObjects<TrainInfoPerStation *> *train = trainCheck(trains, queue->object->trains);
                            if (train != nullptr)
                            {
                                available = new listOfObjects<TrainInfoPerStation *>(train->object);
                                intermediate = available;
                            }
                        }
                        if (available != nullptr)
                        {
                            listOfObjects<TrainInfoPerStation *> *train = trainCheck(trains, queue->object->trains);
                            if (train != nullptr)
                            {
                                available = new listOfObjects<TrainInfoPerStation *>(train->object);
                                intermediate = available;
                            }
                        }
                        else
                        {

                            listOfObjects<TrainInfoPerStation *> *train = trainCheck(trains, queue->object->trains);
                            if (train != nullptr)
                            {
                                intermediate->next = new listOfObjects<TrainInfoPerStation *>(train->object);
                                intermediate = intermediate->next;
                            }
                        }
                        trains = trains->next;
                    }
                }
            }
            temp = temp->next;
        }
        queue = queue->next;
        available = BFS(queue, last, indexStn1, indexStn2, available, intermediate, adjacency); // recursively check all nodes in queue and update available list
    }
    return available; // returns the trains which are available
}

void Planner::printDirectJourneys(string srcStnName, string destStnName)
{

    // insert your code here
    int indexStn1 = stnNameToIndex.get(srcStnName)->value;
    int indexStn2 = stnNameToIndex.get(destStnName)->value; // indices of src and dest stations
    listOfObjects<StationConnectionInfo *> *temp = adjacency[indexStn1].toStations; // list of stations adjacent to src
    listOfObjects<TrainInfoPerStation *> *srcTrains = stationInfo[indexStn1]; // trains from src

    Node *source = new Node(indexStn1);
    listOfObjects<Node *> *queue = new listOfObjects<Node *>(source); // source station is inserted in the queue
    listOfObjects<TrainInfoPerStation *> *intermediate = nullptr; // list of intermediate stations from src to dest
    listOfObjects<TrainInfoPerStation *> *directTrains = nullptr; // list of direct trains from src to dest.

    while (temp != nullptr) // iterating over each adjacent station
    {
        listOfObjects<TrainInfoPerStation *> *trains = temp->object->trains; // list of trains from src to this temp adjacent station
        while (trains != nullptr) // iterating over the list of trains
        {
            listOfObjects<TrainInfoPerStation *> *train = trainCheck(trains, srcTrains); // if this train is from src, it is stored
            if (queue->object->trains == nullptr)
            {
                queue->object->trains = new listOfObjects<TrainInfoPerStation *>(train->object);
                queue->object->trains2 = queue->object->trains;
            }
            else
            {
                queue->object->trains2->next = new listOfObjects<TrainInfoPerStation *>(train->object);
                queue->object->trains2 = queue->object->trains2->next;
            }
            trains = trains->next;
        }
        temp = temp->next;
    }

    listOfObjects<Node *> *last = queue; // since queue is of length 1 for now, last is same as start
    directTrains = BFS(queue, last, indexStn1, indexStn2, directTrains, intermediate, adjacency); //BFS returns the list of directTrains which are printed
    printStationInfo(directTrains);
    return;

    // Get the list of journeys as a listOfObjects<TrainInfoPerStation *>
    // for the source station and then we can print it out by invoking
    // printStationInfo that we had used in Lab 7.
    // printStationInfo is a private member function of the Planner class
    // It is declared in planner.h and implemented in planner.cpp

    // listOfObjects<TrainInfoPerStation *> *srcTrains = stationInfo[stnNameToIndex.get(srcStnName)->value];
    // listOfObjects<TrainInfoPerStation *> *destTrains = stationInfo[stnNameToIndex.get(destStnName)->value];
    // listOfObjects<TrainInfoPerStation *> *common = nullptr;

    // listOfObjects<TrainInfoPerStation *> *tempSrc = srcTrains;
    // listOfObjects<TrainInfoPerStation *> *tempDest = destTrains;
    // listOfObjects<TrainInfoPerStation *> *tempCommon = common;

    // while (tempSrc != nullptr)
    // {
    //     while (tempDest != nullptr)
    //     {
    //         if (tempSrc->object->journeyCode == tempDest->object->journeyCode)
    //         {
    //             if (common == nullptr)
    //             {
    //                 listOfObjects<TrainInfoPerStation *> temp = tempSrc->object;
    //                 common = new listOfObjects<TrainInfoPerStation *>(temp);
    //                 tempCommon = common;
    //             }
    //             else{
    //                 listOfObjects<TrainInfoPerStation *> temp = tempSrc->object;
    //                 tempCommon->next = new listOfObjects<TrainInfoPerStation *>(temp);
    //             }
    //             tempCommon = tempCommon->next;
    //         }
    //         tempDest = tempDest->next;
    //     }
    //     tempSrc = tempSrc->next;
    // }
    // printStationInfo(common);
    // return;
}

#endif
