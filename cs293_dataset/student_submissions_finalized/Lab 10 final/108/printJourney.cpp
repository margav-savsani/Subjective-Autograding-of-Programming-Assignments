#ifndef PRINT_JOURNEY_CPP
#define PRINT_JOURNEY_CPP

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef PLANNER_H
#include "planner.h"
#endif

// #ifndef CODES_H
// #include "codes.h"
// #endif

#define list listOfObjects
#define trn_info TrainInfoPerStation
#define adj StationAdjacencyList

using namespace std;

void dfs(list<trn_info *> *jour, int stn, list<int> *path, int st, int dest, int left, int tt, bool v[], const adj adjacency[], list<trn_info *> *stnInfo[]) {
    if (stn == dest) {
        cout << "Journey:\n";
        auto j = jour;
        auto p = path;
        while (j->prev->object->journeyCode) {
            j = j->prev;
            if (j->object->journeyCode != j->prev->object->journeyCode) {
                list<int> *transit = nullptr;
                for (int i=0; i<7; i++) {
                    if (j->prev->object->daysOfWeek[i]) {
                        for (int k=i; k<i+7; k++) {
                            if (j->object->daysOfWeek[k%7]) {
                                // cout << k;
                                int value = 2400*(k-i) + j->object->depTime - j->prev->object->arrTime;
                                if (value >= 0 && value <= tt) {
                                    (transit ? transit->next : transit) = new list<int> {value};
                                    if (transit->next) {
                                        transit->next->prev = transit;
                                        transit = transit->next;
                                    }
                                } else {
                                    j->prev->object->daysOfWeek[i] = false;
                                }
                            }
                        }
                    }
                }
            }
        }
        // while (p->object != st) p = p->prev;
        string days[7] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};
        while (j) {
            if (j->object->journeyCode != j->prev->object->journeyCode && j->prev->object->journeyCode) {
                list<int> *transit = nullptr;
                for (int i=0; i<7; i++) {
                    if (j->prev->object->daysOfWeek[i]) {
                        for (int k=i; k<i+7; k++) {
                            if (j->object->daysOfWeek[k%7]) {
                                // cout << k;
                                int value = 2400*(k-i) + j->object->depTime - j->prev->object->arrTime;
                                // if (value >= 0 && value <= tt) {
                                (transit ? transit->next : transit) = new list<int> {value};
                                if (transit->next) {
                                    transit->next->prev = transit;
                                    transit = transit->next;
                                }
                                // }
                            }
                        }
                    }
                }
                cout << "Change to train number " << j->object->journeyCode << " after ";
                while (transit->prev) {
                    cout << transit->object/100 << ":" << transit->object%100 << (transit->object%100 ? "" : "0") << " hours" << " or ";
                    transit = transit->prev;
                }
                cout << transit->object/100 << ":" << transit->object%100 << (transit->object%100 ? "" : "0") << " hours\n";
            }
            cout << BLUE << "Train no.: " << j->object->journeyCode << '\n' << RESET;
            for (int i=0; i<7; i++) {
                // cout << j->object->daysOfWeek[i];
                if (j->object->daysOfWeek[i]) {
                    cout << GREEN << "Arrival: " << (j->object->arrTime == -1 ? "Starts" : to_string(j->object->arrTime)) << ' ' << (j->object->arrTime == -1 ? "" : days[i]) << "    " << RESET;
                    cout << RED << "Departure: " << (j->object->depTime == -1 ? "Ends" : to_string(j->object->depTime)) << ' ' << (j->object->depTime == -1 ? "" : (days[j->object->depTime > j->object->arrTime ? i:(i+1)%7])) << RESET;
                    cout << '\n';
                }
            }
            // cout << '\n';
            j = j->next;
        }
        list<trn_info *> *temp = stnInfo[stn];
        while (temp->object->journeyCode != jour->object->journeyCode) temp = temp->next;
        cout << BLUE << "Train no.: " << temp->object->journeyCode << '\n' << RESET;
        for (int i=0; i<7; i++) {
            if (temp->object->daysOfWeek[i]) {
                cout << GREEN << "Arrival: " << (temp->object->arrTime == -1 ? "Starts" : to_string(temp->object->arrTime)) << ' ' << (temp->object->arrTime == -1 ? "" : days[i]) << "    " << RESET;
                cout << RED << "Departure: " << (temp->object->depTime == -1 ? "Ends" : to_string(temp->object->depTime)) << ' ' << (temp->object->depTime == -1 ? "" : (days[temp->object->depTime > temp->object->arrTime ? i:(i+1)%7])) << RESET;
                cout << '\n';
            }
        }

        cout << '\n';
        return;
    }

    v[stn] = true;
    auto nxt = adjacency[stn].toStations;
    while(nxt) {
        if (!v[nxt->object->adjacentStnIndex]) {
            list<trn_info *> *t = nxt->object->trains;
            while (t) {
                bool dif = false;
                dif = jour->object->journeyCode != t->object->journeyCode;

                if (dif && jour->object->journeyCode) {
                    list<trn_info *> *temp = stnInfo[stn];
                    while (temp->object->journeyCode != jour->object->journeyCode) temp = temp->next;
                    jour->next = new list<trn_info *> (*temp);
                    jour->next->prev = jour;
                    jour = jour->next;
                }

                jour->next = new list<trn_info *> {new trn_info {t->object->journeyCode, t->object->stopSeq, t->object->arrTime, t->object->depTime}};
                jour->next->prev = jour;
                for (int i=0; i<7; i++) {
                    if (jour->object->daysOfWeek[i]) {
                        int c {};
                        if (dif && jour->object->journeyCode) {
                            for (int j=i; j<i+7; j++) {
                                if (t->object->daysOfWeek[j%7] && 2400*j + t->object->depTime <= 2400*i + jour->object->arrTime + tt && 2400*j + t->object->depTime >= 2400*i + jour->object->arrTime) {
                                    jour->next->object->setDayOfWeek(j%7);
                                    jour->next->object->arrTime = t->object->arrTime;
                                    jour->next->object->depTime = t->object->depTime;
                                    c++;
                                }
                            }
                            if (!c) jour->object->daysOfWeek[i] = !jour->object->daysOfWeek[i];
                        } else {
                            for (int j=0; j<7; j++) {
                                // cout << jour->next->object->journeyCode << "verab\n";
                                if (t->object->daysOfWeek[j]) jour->next->object->setDayOfWeek(j);
                                jour->next->object->arrTime = t->object->arrTime;
                                jour->next->object->depTime = t->object->depTime;
                            }
                        }

                        int cnt{};
                        for (int j=0; j<7; j++) cnt += jour->next->object->daysOfWeek[j];
                        if ((!dif || left) && cnt) {
                            path->next = new list<int> {stn};
                            path->next->prev = path;
                            dfs(jour->next, nxt->object->adjacentStnIndex, path->next, st, dest, left-dif, tt, v, adjacency, stnInfo);
                            delete path->next;
                            path->next = nullptr;
                        }
                        if (!dif || !jour->object->journeyCode) break;

                        for (int j=0; j<7; j++) jour->next->object->resetDayOfWeek(j);
                    }
                }
                delete jour->next;
                jour->next = nullptr;

                if (dif && jour->object->journeyCode) {
                    jour = jour->prev;
                    delete jour->next;
                    jour->next = nullptr;
                }

                t = t->next;
            }
        }
        nxt = nxt->next;
    }

    v[stn] = false;
}

void Planner::printPlanJourneys(string srcStnName, string destStnName, int maxStopOvers, int maxTransitTime) {

    // insert your code here
    bool v[DICT_SIZE] {};
    trn_info dummy { 0, 0, 0, 0 };
    for (int i=0; i<7; i++) dummy.setDayOfWeek(i);
    list<trn_info *> *j = new list<trn_info *> { &dummy };
    list<int> *path = new list<int> {stnNameToIndex.get(srcStnName)->value};
    dfs(j, stnNameToIndex.get(srcStnName)->value, path, stnNameToIndex.get(srcStnName)->value, stnNameToIndex.get(destStnName)->value, maxStopOvers, maxTransitTime, v, adjacency, stationInfo);
    delete j;

    // Whenever you need to print a journey, construct a
    // listOfObjects<TrainInfoPerStation *> appropriately, and then
    // use printStationInfo that we had used in Lab 7.
    // printStationInfo is a private member function of  
    // the Planner class. It is declared in planner.h and implemented in
    // planner.cpp
    
    return;
}

#endif