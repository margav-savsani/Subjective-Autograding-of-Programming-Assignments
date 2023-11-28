#include "planner.h"

constexpr double infinity { 1e9 };  // Represents infinity


// Queries:
// 1. ADD  starting_station  starting_time  ending_station  ending_time
// 2. QUERY_STATION  station  min_time
// 3. QUERY_JOURNEY  starting_time min_time  ending_time
//
void Planner::query() {
    while (true) {
        std::cout << ">>> ";
        std::string query_type;
        std::cin >> query_type;

        std::string st1;
        double t1;

        // Handle all the query types accordingly.
        // Take in the input, then call the appropriate
        // function.
        if (query_type == "ADD") {
            std::string st2;
            double t2;
            std::cin >> st1 >> t1 >> st2 >> t2;
            add(st1, t1, st2, t2);

        } else if (query_type == "QUERY_STATION") {
            std::cin >> st1 >> t1;
            query_station(st1, t1);

        } else if (query_type == "QUERY_JOURNEY") {
            std::string st2;
            std::cin >> st1 >> t1 >> st2;
            query_journey(st1, t1, st2);

        } else if (query_type == "EXIT") {
            return;
        }
    }
}


// It takes in string, double, string, double then creates a new journey.
// Depending on whether starting station exists in the schedule or not, 
// it adds the new journey to old entry or creates a new one and adds that 
// to the schedule
void Planner::add(std::string start_stn, double start_t, std::string end_stn, double end_t) {
    Journey new_journey {start_stn, start_t, end_stn, end_t};

    Entry* station = schedule.get(start_stn);
    if (station) 
        // If station already exists in dictionary then add the new journey to it
        station->add(new_journey);
    else {
        // Create new entry for start_stn and put it in the dictionary
        Entry new_entry { start_stn };
        new_entry.add(new_journey);
        schedule.put(new_entry);
    }

    std::cout << "Added\n";  // Print success message
}


// This goes through all the journeys from the starting station 
// and prints those with departure time greater than the given 
// time
void Planner::query_station(std::string start_stn, double time) {
    Entry* station = schedule.get(start_stn);

    if (station) {
        bool journey {};  // Stores if there was any journey found
        for (int i=0; i<station->num_ele; i++) {
            Journey j = station->value[i];
            if (j.departure_time >= time-1e-5) {
                journey = true;
                std::cout << j.departure_time << ' ' << j.end_station << '\n';
            }
        }

        if (!journey) 
            // No journeys were found
            std::cout << "There are no such trains from this station\n";
    } else
        // No trains from the station exist
        std::cout << "This station does not exist in the database\n";
}


// Goes through all the journeys from the starting station and if their departure time 
// is acceptable then goes through all the journeys from the ending station of the first 
// journey. It keeps track of the best time and journeys it has found and updates it 
// whenever it finds something better.
void Planner::query_journey(std::string start_stn, double time, std::string end_stn) {
    Entry* station = schedule.get(start_stn);

    double best_time { infinity };  // Best(earliest) time found so far
    Journey first;  // First journey in the best solution found
    std::pair<bool, Journey> second {false, {}};  // Second journey if it exists in the best solution found
    if (station) {
        for (int i=0; i<station->num_ele; i++) {
            Journey j1 = station->value[i];

            if (j1.departure_time < time-1e-5 || j1.departure_time > best_time+1e-5) continue;  // Continue if departure time is too low or more than best

            Entry* inter = schedule.get(j1.end_station);
            if (j1.end_station == end_stn && j1.departure_time < best_time) {  // The current journey ends at the correct station and is best
                best_time = j1.departure_time;
                second.first = false;
                first = j1;
                continue;
            } else if (inter) {  // Check for all journeys from an intermediate stop
                for (int k=0; k<inter->num_ele; k++) {
                    Journey j2 = inter->value[k];

                    if (j2.departure_time < j1.arrival_time-1e-5) continue;  // Continue if departure time is too low

                    if (j2.end_station == end_stn && j1.departure_time < best_time) {  // The ending station is correct and time is best
                        best_time = j1.departure_time;
                        second = {true, j2};
                        first = j1;
                        break;
                    }
                }
            }
        }
        
    } else {
        // No trains from the station exist
        std::cout << "This station does not exist in the database\n";
        return;
    }

    
    if (best_time < infinity+1e-5 && best_time > infinity-1e-5) {  // No journeys were found
        std::cout << "No suitable journey exists\n";
    } else {
        std::cout << first.departure_time << (second.first ? ' ' : '\n');
        if (second.first) std::cout << second.second.start_station << ' ' << second.second.departure_time << '\n';
    }
}

int main() {
    freopen("test-cases-lab2-p2/input3.in", "r", stdin);
    Planner p;
    p.query();
}