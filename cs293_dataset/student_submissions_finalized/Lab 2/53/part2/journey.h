#include<iostream>
#include<string.h>
using namespace std;

#ifndef JOURNEY_H
#define JOURNEY_H

struct journey{
    char start[32]; //The starting station in a journey
    char end[32]; //The destination of the journey
    float begin_time; // The departure time of the journey
    float reach_time; //The arrival time of the journey
};

class Planner{ //Handles the sorted array which contains the journeys of a particular starting station
    private:
        journey *departures; //The array of the journeys
        int current_size; //The number of journeys filled
        int N_prime; //Size of the array
        int growth = 64; //Increasing size of array with the amount of this constant
    public:
        Planner(){ //Constructor 
            departures = new journey[64]; 
            current_size = 0;
            N_prime=64;
        }
        void insert(journey j){ // Insertion of a given journey to the departures array
            int i=0;
            if (current_size == 0){//When array is empty add the journey to the first element
                departures[0]=j;
                current_size++;
                return;
            }
            else if(current_size==N_prime){ // When array gets filled increase the size of the array
                journey *temp;
                temp = new journey[N_prime+growth];
                for(int i=0;i<current_size;i++){
                    temp[i]=departures[i];
                }
                delete departures;
                departures = temp;
                temp = NULL;
                N_prime += growth;
            }
            while(j.begin_time >= departures[i].begin_time){// Increase the index i till you reach the right index
                i++;
                if(i==current_size) break;
            }
            for(int k=current_size-1;k>=i;k--){ // Shift the elements after the found index
                departures[k+1]=departures[k];
            }
            departures[i]=j;//Assigning the value of the array at the index found as the given journey
            current_size++;//Increasing the quantity of journeys in the array
            

        }
        int next_departure(float given_time){ //This function returns the index of the departure which is just after the given time using binary search.
            int low=0;
            int high=current_size-1;
            int mid;
            given_time -= 0.005;
            if(departures[0].begin_time>given_time){
                return 0;
            }
            do
            {  mid = (low + high)/2;
               if(given_time>=departures[mid].begin_time){
                if(given_time<departures[mid+1].begin_time){
                    return mid+1;
                }
                low=mid+1;
               }
            else if(given_time<departures[mid].begin_time){
                high = mid;
            } 
            } while (low<=high);
            return -1; //returns a error index if no such departure index exists.
            
        }
        void print_next_departures(float given_time){//prints all the departures after the given time
            int index=next_departure(given_time);
            if(index == -1) {
                cout<<"No next departures"<<"endl";
                return;
            }
            for(int i=index;i<current_size;i++){
                cout<<departures[i].begin_time<<" "<<departures[i].end<<endl;
            }
            return;
        }
        journey somefunction(float given_time){//returns journey of the departure time just after given time(not used function)
            int index=next_departure(given_time);
            return departures[index];
        }
        float search_dest(char dest[32],float reaching_time_at_inter){ //returns the index of the journey(with intermediate station as starting point)in which it reaches the final destination 
            for(int i=0;i<current_size;i++){
                if(strcmp(departures[i].end,dest)==0 && departures[i].begin_time + 0.005 >= reaching_time_at_inter)
                {   
                    return departures[i].begin_time;}
            }
            return -1; //returns -1 if there is no journey satisfying the condition
        }
        bool check(int index){ //checks if the given index does not exceeds the number of journeys
            if(index<current_size) return true;
            else return false;
        }
        journey jry_given_index(int index){//returns the struct journey with the given index.
            return departures[index];
        }
};

#endif