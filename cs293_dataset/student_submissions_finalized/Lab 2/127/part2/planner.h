#ifndef PLANNER_H
#define PLANNER_H

#include "dictionary.cpp"
#include<iostream>
#include <tuple>
#include<algorithm>




class Planner {
	private:
		Dictionary_float start_times;
		Dictionary_string destinations;
		Dictionary_float end_times;
		//std::vector< std::tuple< std::string, float, std::string, float> > Completed_Journeys;
	
	public:

		Planner() {};

		void add(std::string station_one, float start_time, std::string station_two, float end_time) {
			start_times.put(station_one, start_time);
			destinations.put(station_one, station_two);
			end_times.put(station_one, end_time);
		}
		std::tuple< std::vector<float>, std::vector<std::string>, std::vector<float> > query_station(std::string station_one, float start_time) {
			std::vector<float> start_times_station=start_times.get(station_one);
			std::vector<std::string> destinations_station=destinations.get(station_one);
			std::vector<float> end_times_station=end_times.get(station_one);
			std::vector<int> indices;
			for(int i=0; i<start_times_station.size(); i++) {
				if(start_times_station[i]>=start_time) {
					indices.push_back(i);
				}
			}

			std::vector<float> right_start_times;
			std::vector<std::string> right_destinations;
			std::vector<float> right_end_times;

			for(int theta=0; theta<indices.size(); theta++) {
				right_start_times.push_back(start_times_station[indices[theta]]);
				right_destinations.push_back(destinations_station[indices[theta]]);
				right_end_times.push_back(end_times_station[indices[theta]]);
			}

			
			return std::make_tuple(right_start_times, right_destinations, right_end_times);

		}
		std::tuple< float, std::string, float > journey(std::string station_one, float start_time, std::string destination) {
			
			std::vector<float> two_start_times;
            std::vector<std::string> two_destinations;
            std::vector<float> two_end_times;
			std::tie(two_start_times, two_destinations, two_end_times) = query_station(station_one, start_time);

			if(two_destinations.size()==0) {
				return std::make_tuple(-1, "", -1);
			}

			std::vector<float> three_start_times;
			std::vector<std::string> three_destinations;
			std::vector<float> three_end_times;

			for(int theta=0; theta<two_destinations.size(); theta++) {

				//std::tuple<std::string, float, std::string, float> temp_journey(std::make_tuple(station_one, two_start_times[theta], two_destinations[theta], two_end_times[theta]));
				//if(std::find(Completed_Journeys.begin(), Completed_Journeys.end(), temp_journey) != Completed_Journeys.end()) continue;

				std::vector<float> new_start_times;
	            std::vector<std::string> new_destinations;
        	    std::vector<float> new_end_times;
                std::tie(new_start_times, new_destinations, new_end_times)=query_station(two_destinations[theta], two_end_times[theta]);
				
				for(int gamma=0; gamma<new_destinations.size(); gamma++) {
					if(new_destinations[gamma]==destination) {

						//std::tuple<std::string, float, std::string, float> temp_journey(std::make_tuple(two_destinations[theta], new_start_times[gamma], new_destinations[gamma], new_end_times[gamma]));
						//if(std::find(Completed_Journeys.begin(), Completed_Journeys.end(), temp_journey) != Completed_Journeys.end()) continue;

						three_start_times.push_back(two_start_times[theta]);
						three_destinations.push_back(two_destinations[theta]);
						three_end_times.push_back(new_start_times[gamma]);
					}
				}
			}

			std::vector<float> final_two_start_times;
			std::vector<int> final_to_reg_indices;
			for(int kappa=0; kappa<two_destinations.size(); kappa++) {
				if(two_destinations[kappa]==destination) {

					//std::tuple<std::string, float, std::string, float> temp_journey(std::make_tuple(station_one, two_start_times[kappa], two_destinations[kappa], two_end_times[kappa]));
					//if(std::find(Completed_Journeys.begin(), Completed_Journeys.end(), temp_journey) != Completed_Journeys.end()) continue;

					final_to_reg_indices.push_back(kappa);
					final_two_start_times.push_back(two_start_times[kappa]);
				}
			}

			if(final_two_start_times.size()==0 && three_start_times.size()==0) {
				return std::make_tuple(-1, "", -1);
			}

			float min_two_start_time=999999;
			int min_two_index=-1;
			for(int epsilon=0; epsilon<final_two_start_times.size(); epsilon++) {
				if(final_two_start_times[epsilon]<min_two_start_time) {
					min_two_start_time=final_two_start_times[epsilon];
					min_two_index=epsilon;
				}
			}

			float min_three_start_time=999999;
			int min_three_index=-1;
			for(int alpha=0; alpha<three_start_times.size(); alpha++) {
				if(three_start_times[alpha]<min_three_start_time) {
					min_three_start_time=three_start_times[alpha];
					min_three_index=alpha;
				}
			}

			

			if(min_two_start_time<=min_three_start_time) {

				//std::tuple<std::string, float, std::string, float> temp_journey(std::make_tuple(station_one, final_two_start_times[min_two_index], two_destinations[final_to_reg_indices[min_two_index]], two_end_times[final_to_reg_indices[min_two_index]]));
				//Completed_Journeys.push_back(temp_journey);

				return std::make_tuple(min_two_start_time, "", -1);
			}
			else {
				return std::make_tuple(min_three_start_time, three_destinations[min_three_index], three_end_times[min_three_index]);
			}
		}

};

#endif
