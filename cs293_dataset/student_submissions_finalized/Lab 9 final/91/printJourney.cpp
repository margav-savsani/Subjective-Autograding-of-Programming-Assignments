#ifndef PRINT_JOURNEY_CPP
#define PRINT_JOURNEY_CPP

#ifndef PLANNER_H
#include "planner.h"
#endif

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef QUEUE_TPL
#define QUEUE_TPL
template <typename T> struct Node_dll {
    T value;
    Node_dll<T>* next;
    Node_dll<T>* prev;
    Node_dll(T value, Node_dll<T>* next, Node_dll<T>* prev)
        : value(value), next(next), prev(prev)
    {
    }
};

template <typename T> class Queue {
    Node_dll<T>* head;
    Node_dll<T>* tail;
  public:
    Queue()
        : head(nullptr), tail(nullptr)
    {
    }

    ~Queue()
    {
        while (head != nullptr) {
            Node_dll<T>* temp = head->next;
            delete head;
            head = temp;
        }
    }

    void enqueue(T v)
    {
        if (head == nullptr) {
            head = new Node_dll<T>(v, nullptr, nullptr);
            tail = head;
        }
        else {
            tail->next = new Node_dll<T>(v, nullptr, tail);
            tail = tail->next;
        }
    }

    bool is_empty() const
    {
        return (head == nullptr);
    }

    T front() const
    {
        if (head != nullptr)
            return head->value;
        throw "Empty queue";
    }

    void dequeue()
    {
        if (head != nullptr) {
            if (head == tail) {
                delete head;
                head = tail = nullptr;
            }
            else {
                Node_dll<T>* temp = head;
                head = head->next;
                head->prev = nullptr;
                delete temp;
            }
        }
        else {
            throw "Empty queue";
        }
    }

    void print()
    {
        if (head != nullptr) {
            Node_dll<T>* temp = head;
            while (temp != nullptr) {
                std::cout << temp->value << ' ';
                temp = temp->next;
            }
        }
        else {
            std::cout << "<Empty Queue>";
        }
    }
};
#endif  // QUEUE_TPL

using namespace std;

void Planner::printDirectJourneys(string srcStnName, string destStnName)
{
    int s = stnNameToIndex.get(srcStnName)->value;
    int dest = stnNameToIndex.get(destStnName)->value;

    bool trains_found = false;

    listOfObjects<int>* outgoing_train_codes = nullptr;




  {
    listOfObjects<int>* outgoing_train_codesTemp = nullptr;

    listOfObjects<StationConnectionInfo*>* toStationsTemp = adjacency[s].toStations;
    while (toStationsTemp != nullptr) {
        listOfObjects<TrainInfoPerStation*>* trainsTemp = toStationsTemp->object->trains;
        while (trainsTemp != nullptr) {
            if (outgoing_train_codes == nullptr) {
                outgoing_train_codes = outgoing_train_codesTemp = new listOfObjects<int>(trainsTemp->object->journeyCode);
            }
            else {
                outgoing_train_codesTemp->next = new listOfObjects<int>(trainsTemp->object->journeyCode);
                outgoing_train_codesTemp->next->prev = outgoing_train_codesTemp;
                outgoing_train_codesTemp = outgoing_train_codesTemp->next;
            }
            trainsTemp = trainsTemp->next;
        }
        toStationsTemp = toStationsTemp->next;
    }
  }



    while (outgoing_train_codes != nullptr) {
        int train_no = outgoing_train_codes->object;
        
//        std::cout << "Checking train number " << train_no << '\n';

        Queue<int> Q;
        Q.enqueue(s);

        while (!Q.is_empty()) {
//            std::cout << "Queue: ";
//            Q.print();
//            std::cout << '\n';
            int u = Q.front();

            listOfObjects<StationConnectionInfo*>* out_of_u = adjacency[u].toStations;
            listOfObjects<StationConnectionInfo*>* out_of_uTemp = out_of_u;

            while (out_of_uTemp != nullptr) {
                StationConnectionInfo* sci = out_of_uTemp->object;
//                std::cout << "    " << stnNameToIndex.getKeyAtIndex(sci->adjacentStnIndex) << '\n';
                listOfObjects<TrainInfoPerStation*>* trainsTemp = sci->trains;

                while (trainsTemp != nullptr) {
//                    std::cout << stnNameToIndex.getKeyAtIndex(sci->adjacentStnIndex) << ' ' << destStnName << trainsTemp->object->journeyCode << ' ' << train_no << '\n';
                    if (trainsTemp->object->journeyCode == train_no) {
                        if (sci->adjacentStnIndex == dest) {
                            std::cout << "Train No. " << train_no << '\n';
                            trains_found = true;
                        }
                        else {
                            Q.enqueue(sci->adjacentStnIndex);
                        }
                        break;
                    }
                    trainsTemp = trainsTemp->next;
                }

                out_of_uTemp = out_of_uTemp->next;
            }

            Q.dequeue();
        }

        outgoing_train_codes = outgoing_train_codes->next;
    }

    if (!trains_found) {
        std::cout << "No direct trains between " << srcStnName << " and " << destStnName << '\n';
    }

    // Get the list of journeys as a listOfObjects<TrainInfoPerStation *>
    // for the source station and then we can print it out by invoking
    // printStationInfo that we had used in Lab 7.
    // printStationInfo is a private member function of the Planner class
    // It is declared in planner.h and implemented in planner.cpp
}

#endif
