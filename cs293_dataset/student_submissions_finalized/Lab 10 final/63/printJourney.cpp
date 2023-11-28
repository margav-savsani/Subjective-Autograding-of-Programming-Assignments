#ifndef PRINT_JOURNEY_CPP
#define PRINT_JOURNEY_CPP

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

using namespace std;

#define DAY 2400

// This function checks whether a transit is a valid one or not 
// this function returns true if even one journey (on at least one day) is possible
bool valid_tranist(TrainInfoPerStation* A, TrainInfoPerStation* B, int time){
    int start = A->arrTime;
    int leave = B->depTime;
    bool next_day = (leave <= start);
    int r = 0;
    int S = time/DAY;
    for(int i = 0; i < 7; i++){
        if (A->daysOfWeek[i]){
            for(int j = 0; j < 7; j++){
                for(int k = 0; k <= S; k ++){
                    if(B->daysOfWeek[(j+k+next_day)%7]){
                        r = (k+next_day+j - i)*DAY + leave-start;
                        if (r < time && r > 0){     // checking the condition
                            return true;
                        }
                    }
                }
            }
        }
    }
    return false;
}


class Plan{         // class to organize the data. It is some sort of a stack to keep track of the train switch overs.
    int N;
    TrainInfoPerStation ** T;
    int * arrivtime;
    int * StationID;
    int i;
public:
    Plan(int N){        // constructor
        this->N = N;       // max size of stack
        this->T = new TrainInfoPerStation*[N];
        this->arrivtime = new int[N];
        this->StationID = new int[N];
        this->i = 0;    // current size of stack
    }

    bool insert(TrainInfoPerStation* A, int arr, int ID){       // inserts into the stack
        if (i >= N){
            return false;
        }    
        this->T[i] = A;
        this->arrivtime[i] = arr;
        this->StationID[i] = ID;
        
        i++;
        return true;
    }

    Plan * pop(){       // returns a new Plan object, a copy
        Plan * P = new Plan(this->N);
        for (int k = 0; k < this->i; k++){
            P->insert(this->T[k], this->arrivtime[k], this->StationID[k]);
        }
        return P;
    }

    TrainInfoPerStation * get_last(){   // returns the last element 
        if (i == 0){
            cout << "Some error occured" << endl;
            return nullptr;
        }
        return T[i-1];
    }

    int get_num(){      // returns the number of elements in the stack
        return this->i;
    }

    TrainInfoPerStation ** get_jrn(){
        return this->T;
    }

    int * get_arrv(){
        return this->arrivtime;
    }

    int * get_stn(){
        return this->StationID;
    }

    void remove_top(){      // removes the top element
        if (i > 0){
            this->T[i] = nullptr;
            i--;
        }  
    }

    void print(){
        for (int j = 0; j < this->i; j++){
            cout << this->T[j]->journeyCode << " ";
        }
        cout << endl;
    }

    bool isfull(){
        if (i >= N){
            return true;
        }
        return false;
    }

    ~Plan(){    // destructor
        delete[] T;
        delete[] StationID;
        delete[] arrivtime;
    }
};

// this function recursively gathers all the possible journeys into Plan objects and appends to a linked list
// this function is similar to DFS.
void get_alljourneys(listOfObjects<Plan*>* &P, TrainInfoPerStation* train, int source, int dest, int maxStopOvers, int maxTransitTime, StationAdjacencyList* adjacency){
    // base case : append to linked list if reach the destination 
    // note that the currently active recursive call is stored at the endof linked list, so, 
    // once its completed we just duplicate it into the linked list
    if (source == dest){        
        listOfObjects<Plan*>* new_plan = new listOfObjects<Plan*>(P->object->pop());
        P->next = new_plan;
        new_plan->prev = P;
        P = new_plan;
        return;
    }

    if (P->next != nullptr){    // change the pointer if added to linked list
        P = P->next;
    }
    bool flag = 0;
    listOfObjects<StationConnectionInfo*> * S = adjacency[source].toStations;   // to trains from the current station
    listOfObjects<StationConnectionInfo*> * A = adjacency[source].fromStations; // from trains that arrive at the current station
    TrainInfoPerStation * T = train;
    if (train != nullptr){      // gather the arrival time of the train here from the from list
        while(A != nullptr){
            listOfObjects<TrainInfoPerStation*> * I = A->object->trains;
            bool b = 0;
            while(I != nullptr){
                if (I->object->journeyCode == train->journeyCode){
                    T = I->object;
                    b = 1;
                    break;
                }
                if (b){
                    break;
                }
                I = I->next;
            }
            A = A->next;
        }
    }
    while (S != nullptr){       // the main loop
        listOfObjects<TrainInfoPerStation*> * I = S->object->trains;
        int adstn =  S->object->adjacentStnIndex;
        while(I != nullptr){
            if (P->object->get_num() == 0 && train == nullptr){     // first recursive call
                P->object->insert(I->object, 0, source);
                flag = 1;
                get_alljourneys(P, I->object, adstn, dest, maxStopOvers-1, maxTransitTime, adjacency);  // recursion
            }
            else if (P->object->get_num() == 0){
                return;
            }
            else if (I->object->journeyCode == train->journeyCode){     // gathers direct journeys from here to the dest
                get_alljourneys(P, I->object, adstn, dest, maxStopOvers, maxTransitTime, adjacency);    // recursion
            }
            else if(maxStopOvers > 0){      // deals ith transit cases
                if (valid_tranist(T, I->object, maxTransitTime)){
                    P->object->insert(I->object, T->arrTime, source);
                    flag = 1;
                    get_alljourneys(P, I->object, adstn, dest, maxStopOvers-1, maxTransitTime, adjacency);  // recursion
                }
            }
            if (flag){    
                P->object->remove_top();    // remove from top of stack to continue the recursion 
                flag = 0;
            }
            I = I->next;
        }
        S = S->next;
    }
    return;
}

// this class is to help the next print function
class print_helper{     // class to help print in a good format
public:
    int* day;   // stores the day of the departure  
    int* stn;   // stores the stations visited
    int* transit_time;  // records transit time at each transit
    int* dept_time;     // records departure time at each transit
    int* k;
    int* j;
    int N;
    int i;

    print_helper(int N){
        day = new int [N];
        stn = new int [N];
        transit_time = new int [N];
        k = new int [N];
        j = new int [N];
        dept_time = new int [N];
        this->N = N;
        this->i = 0;
    }

    bool insert(int day, int stn, int tra, int j, int k, int dept_time){
        if (i >= N){
            cout << "Some error occured" << endl;
            return false;
        }
        this->day[i] = day;
        this->stn[i] = stn;
        this->transit_time[i] = tra;  
        this->dept_time[i] = dept_time;
        this->k[i] = k;
        this->j[i] = j;
        i++;
        return true;
    }

    bool pop(){
        if (i <= 0){
            cout << "Some error occured" << endl;
            return false;
        }
        i--;
        return true;
    }

    bool isfull(){
        if (i == N){
            return true;
        }
        return false;
    }

    void reset(){
        this->i = 0;
    }

    ~print_helper(){
        delete[] day;
        delete[] stn;
        delete[] transit_time;
        delete[] k;
        delete[] dept_time;
    }
};

// This function is used to print the required journeys day wise
// this is called inside  printPlanJourneys
bool print(int option, Plan * plan, int maxTransitTime, Dictionary<int> stnNameToIndex){
    TrainInfoPerStation ** T = plan->get_jrn();
    int * arr = plan->get_arrv();
    int * stnID = plan->get_stn();
    int n = plan->get_num();
    int start,leave,r;
    bool next_day;
    bool first_print = 0;
    TrainInfoPerStation * tr = nullptr;
    string Days[7] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};
    print_helper H(n);

    int Il, Ih; 
    if (option == 0){
        Il = 0;
        Ih = 7;
    }
    else {
        Il = option-1;
        Ih = option;
    }

    for (int i = Il; i < Ih; i++){
        if (T[0]->daysOfWeek[i] && n > 1){
            H.insert(i, stnID[0], 0, 0, 0, T[0]->depTime);
            start = arr[H.i];
            leave = T[H.i]->depTime;
            next_day =  (leave <= start);
            bool b = 0;
            for (int j = 0; j < 7; j++){
                for (int k = 0; k < maxTransitTime/DAY; k++){
                    r = (next_day+j+k - H.day[H.i-1])*DAY + leave-start;
                    if (r > 0 && r < maxTransitTime){   // printing if the condition is satisfied
                        H.insert((j+k+next_day)%7, stnID[H.i], r, j, k, leave);
                        if (H.i < n){
                            j = 0;
                            k = 0;
                            start = arr[H.i];
                            leave = T[H.i]->depTime;
                        }
                        if (H.i == n){
                            if (!first_print){
                                cout << "=============================================" << endl;
                                first_print = 1;
                            }
                            cout << "___________________________" << endl;
                            for (int p = 0; p < n; p++){
                                if (p > 0){
                                    cout << BLUE << "Transit Time : " << RESET;
                                    cout << H.transit_time[p] << endl;
                                }
                                cout << RED << "Day : " << RESET;
                                cout << Days[H.day[p]];
                                cout << "           ";
                                cout << RED << "Dep. Time : " << RESET;
                                cout << H.dept_time[p];
                                cout << endl;
                                cout << GREEN << "Train Number : " <<  RESET;
                                cout << T[p]->journeyCode;
                                cout << GREEN << "    Station : " <<  RESET;
                                cout << BLUE << stnNameToIndex.getKeyAtIndex(H.stn[p]) << RESET << endl;
                            }
                            cout << "___________________________" << endl;
                            H.pop();
                            start = arr[H.i];
                            leave = T[H.i]->depTime;
                        }
                    }
                    while (j == 6 && k == maxTransitTime/DAY-1 ){
                        j = H.j[H.i-1];
                        k = H.k[H.i-1];
                        H.pop();
                        start = arr[H.i];
                        leave = T[H.i]->depTime;
                        if (H.i == 0){
                            b = 1;
                            break;
                        }
                    }
                    if (b){
                        break;
                    }
                }
                if (b){
                    break;
                }
            }  
        }
        if (T[0]->daysOfWeek[i] && n == 1){     // dealing with printing of direct journeys
            H.insert(i, stnID[0], 0, 0, 0, T[0]->depTime);
            if (!first_print){
                cout << "=============================================" << endl;
                first_print = 1;
                cout << "Direct Journey/s" << endl;
            }
            cout << "___________________________" << endl;
            cout << RED << "Day : " << RESET;
            cout << Days[H.day[0]];
            cout << "           ";
            cout << RED << "Dep. Time : " << RESET;
            cout << H.dept_time[0];
            cout << endl;
            cout << GREEN << "Train Number : " <<  RESET;
            cout << T[0]->journeyCode;
            cout << GREEN << "    Station : " <<  RESET;
            cout << BLUE << stnNameToIndex.getKeyAtIndex(H.stn[0]) << RESET << endl;
            cout << "___________________________" << endl;
            H.pop();
        }
    }
    if (first_print){
        cout << "=============================================" << endl;
    }
    return first_print;
}

void Planner::printPlanJourneys(string srcStnName, string destStnName, int maxStopOvers, int maxTransitTime){
    int source = stnNameToIndex.get(srcStnName)->value;
    int dest = stnNameToIndex.get(destStnName)->value;
    Plan * plan = new Plan(maxStopOvers+1);
    listOfObjects<Plan*> * PP = new listOfObjects<Plan*> (plan);
    listOfObjects<Plan*> * p = PP;
    get_alljourneys(PP, nullptr, source, dest, maxStopOvers+1, maxTransitTime, adjacency);      // recursively gathering all valid journeys

    PP = p;
    int option;
    while (true){       // sometimes the list becomes to long, so, this is for seleting the start day of the journey from the first station
        cout << "Please enter the Day of travel" << endl;
        cout << "0 : ALL DAYS" << endl;
        cout << "1 : Sun, 2 : Mon, 3 : Tue, 4 : Wed, 5 : Thu, 6 : Fri, 7 : Sun" << endl;
        cin >> option;

        if (0 <= option && option <= 7){
            break;
        }
        else {
            cout << "Invalid option!" << endl;
        }
        
    }
    bool b = 0;
    while (PP != nullptr){      // the main prin loop
        plan = PP->object;
        b = b+print(option, plan, maxTransitTime, stnNameToIndex);
        PP = PP->next;
    }
    if (!b){
        cout << "No journeys available" << endl;
    }
    return;
}

#endif