#include<iostream>
#include<fstream>
#include<string>

#include "planner.h"

int main() {

    Planner planner;

    std::ifstream in("sample-planner.txt");
    std::streambuf *cinbuf = std::cin.rdbuf(); //save old buf
    std::cin.rdbuf(in.rdbuf()); //redirect std::cin to in.txt!

    std::ofstream out("my-out.txt");
    std::streambuf *coutbuf = std::cout.rdbuf(); //save old buf
    std::cout.rdbuf(out.rdbuf()); //redirect std::cout to out.txt!

    std::string command;
    std::string station_one;
    float start_time;
    std::string station_two;
    float end_time;

    while(std::cin>>command) {
        if(command=="ADD") {
            std::cin>>station_one;
            std::cin>>start_time;
            std::cin>>station_two;
            std::cin>>end_time;
            planner.add(station_one, start_time, station_two, end_time);
        }
        else if(command=="QUERY_STATION") {
            std::cin>>station_one>>start_time;
            std::vector<float> start_times;
            std::vector<std::string> destinations;
            std::vector<float> end_times;
            std::tie(start_times, destinations, end_times) = planner.query_station(station_one, start_time);
            if(start_times.size()==0) {
                std::cout<<"ERROR\n";
            }
            for(int i=0; i<start_times.size(); i++) {
                std::cout<<start_times[i]<<" "<<destinations[i]<<"\n";
            }
        }
        else if(command=="QUERY_JOURNEY") {
            std::cin>>station_one>>start_time>>station_two;
            float start_timing;
            std::string intermediate_destination;
            float intermediate_timing;
            std::tie(start_timing, intermediate_destination, intermediate_timing)=planner.journey(station_one, start_time, station_two);
            if(start_timing==-1) {
                std::cout<<"ERROR\n";
            }
            else if(intermediate_timing==-1) {
                std::cout<<start_timing<<"\n";
            }
            else {
                std::cout<<start_timing<<" "<<intermediate_destination<<" "<<intermediate_timing<<"\n";
            }
        }
        else if(command=="EXIT") {
            break;
        }
    }
    //std::cin >> word;           //input from the file in.txt
    //std::cout << word << "  ";  //output to the file out.txt



    std::cin.rdbuf(cinbuf);   //reset to standard input again
    std::cout.rdbuf(coutbuf); //reset to standard output again
}