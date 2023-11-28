#include<iostream>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<fstream>

#include "dictionary.cpp"

using namespace std;


int main(){

    string input, st1, st2;
    float t1, t2;

    Dictionary start_st_dict;//dictionary for mapping station names to Entries containing journey data

    while (true){

        cin >> input;
        
        if (input == "ADD"){ //ADD
            cin >> st1 >> t1 >> st2 >> t2;
            Journey j(st1, t1, st2, t2);
            Entry *e_already = start_st_dict.get(st1);

            if (e_already == nullptr){ //If no entry with this name exists yet

                Entry e_new(st1, j);
                start_st_dict.put(e_new);
            }
            else{
                e_already->add_journey(j); //if this station exists and new data needs to be added to its entry
            }
        }

        else if (input == "QUERY_STATION"){ //QUERY_STATION
            cin >> st1 >> t1;
            Entry *e_existing = start_st_dict.get(st1);

            if (e_existing == nullptr){
                cout << "station not found" << endl; //if station doesnt exist
            }
            else{
                int number_of_journeys;
                Journey *j = e_existing->get_journeys_after(t1, number_of_journeys);
                if (j != nullptr){

                    for (int i = 0; i<number_of_journeys; i++){
                        cout << j[i].st_time << " " << j[i].end_station << endl; //print out all journeys after given time
                    }
                }
                else{
                    cout << "no journeys found" << endl; //no journeys
                }
            }
        }

        else if (input == "QUERY_JOURNEY"){ //QUERY_JOURNEY
            cin >> st1 >> t1 >> st2;

            Entry *e_existing = start_st_dict.get(st1);
            if (e_existing == nullptr){
                cout << "start station not found" << endl; //start station not found
            }
            else{
                int number_of_journeys;
                Journey *j = e_existing->get_journeys_after(t1, number_of_journeys);
                bool found = false;

                if (j != nullptr){ //if there is atleast one journey starting station after given time

                    for (int i = 0; i<number_of_journeys; i++){
                        string next_stop = j[i].end_station;
                        float next_time = j[i].end_time;
                        if (next_stop == st2){
                            cout << j[i].st_time << endl;
                            found = true;
                            break;
                        }// if a journey goes direct

                        Entry *e_intermediate = start_st_dict.get(next_stop);
                        if (e_intermediate == nullptr){
                            continue; //if the end station of this train is not a start station
                        }

                        int number_of_journeys2;
                        Journey *j2 = e_intermediate->get_journeys_after(next_time, number_of_journeys2);
                        if (j2 == nullptr){
                            continue; //if there are no trains from the intermediate station after reach time of this train
                        }
                        else{
                            for (int k = 0; k < number_of_journeys2; k++){
                                string st3 = j2[k].end_station;
                                if (st3 == st2){ //if station found
                                    cout << j[i].st_time << " " << next_stop << " " << j2[k].st_time << endl;
                                    found = true;
                                    break;
                                }
                            }
                        }
                        if (found){
                            break;
                        }
                    }
                    if (!found){
                        cout << "no journey found" << endl;
                    }
                }
                else{
                    cout << "no journey found" << endl;
                }
            }

        }
        else if (input == "EXIT"){//EXIT
            break;
        }

    }
}







