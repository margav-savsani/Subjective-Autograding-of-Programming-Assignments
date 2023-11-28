#ifndef PLANNER_H
#define PLANNER_H

#include<cmath>
#include<string.h>

using namespace std;

struct destination
//This contains all the info about a train route
{
    float starting_time;
    struct Station *Station_Two;
    float ending_time;
};

struct Station
{
 public:
    char Station_Name[32]; // Name of the station
    struct destination Destinations[64]; // List of all the train routes starting from this station, Which is basically a ordered list
    int no_of_destinations = 0; // No of trains from that given station
    bool occupied = false;

    int find_st_time(int sp, int ep, float a)
    // This function finds least int i for which destination time of i is greater than a using binary search
    {
        if (Destinations[sp].starting_time >= a) return sp;
        else if (a > Destinations[ep].starting_time) return -1;
        else if (sp + 1 == ep) return ep;
        else
        {
            int mid = (sp+ep)/2;
            if (Destinations[mid].starting_time >= a) return find_st_time(sp, mid, a);
            else return find_st_time(mid, ep, a);
        }
    }

    void Add_Destination(destination d)
    // This will add the destination d to the list of destinations from the station.
    {
        if (no_of_destinations == 0) 
        //if no trains from station add the station
        {
            Destinations[0] = d;
            no_of_destinations = 1;
        }
        else if (no_of_destinations == 64) 
        //If max no of trains reached, we can't have more trains from that station
        {
            cout << "Max number of journeys from a station " << Station_Name << " reached maximum value.\n";
        }
        else 
        //Find the position where you should keep the new train route and shift array to the right
        {
            int s = find_st_time(0, no_of_destinations-1, d.starting_time);
            if (s == -1) 
            {
                Destinations[no_of_destinations] = d;
                no_of_destinations++;
            }
            else
            {
                for (int i = no_of_destinations - 1; i >= s; i--) Destinations[i+1] = Destinations[i];
                Destinations[s] = d;
                no_of_destinations++;
            }
        }
    }

    void query_station(float a)
    //Prints all train routes from the station after 
    {
        int i = find_st_time(0, no_of_destinations-1 ,a);
        if (i == -1) return;
        else 
        {
            for (i; i < no_of_destinations; i++)
            {
                cout << Destinations[i].starting_time  << " " << Destinations[i].Station_Two->Station_Name << "\n";
            }
        }
    }

    int find(float time, Station find_s)
    {
        int s = find_st_time(0, no_of_destinations-1, time);
        if (s == -1) return -1;
        for (s; s < no_of_destinations; s++)
        {
            if (!strcmp(Destinations[s].Station_Two->Station_Name, find_s.Station_Name)) return s;
        }
        return -1;
    }

    void queryjourney(float time, Station st2)
    {
        int i = find_st_time(0, no_of_destinations-1, time);
        if (i == -1) return;
        int a;
        for (i ; i < no_of_destinations; i++)
        {
            if (!strcmp(Destinations[i].Station_Two->Station_Name, st2.Station_Name)) 
            {
                cout << Destinations[i].starting_time << "\n";
                return;
            }
            else 
            {
                a = Destinations[i].Station_Two->find(Destinations[i].ending_time, st2);
                if (a == -1) continue;
                else 
                {
                    cout << Destinations[i].starting_time << " " << Destinations[i].Station_Two->Station_Name << " " << Destinations[i].Station_Two->Destinations[a].starting_time << "\n";
                    return;
                }
            }
        }
        cout << "ERROR\n";
    }

    // define suitable fields here
};

class Planner
{
 private:
    Station *Stations; //These stations are arranged in the form of a dictionary. So that finding element would become easy.
 public:
    Planner()
    {
        Stations = new Station [64];
    }

    void Add_Station(Station s, int i)
    {
        Stations[i] = s;
        Stations[i].occupied = true;
    }


    int polyvalue(char key[])
    {
        if (key[0] == '\0')
            return 0;
        else
            return (key[0] + 33 * polyvalue(&key[1])) % 64;
    }

    int hashValue(char key[])
    // Return the hash value (between 0 and N-1) of the given string; assume string is null terminated and of max length 32
    {
        int polykey = polyvalue(&key[0]);
        double a = (polykey * (sqrt(5) - 1) / 2);
        return int(64 * (a - int(a)));
    }

    int find_station(char name[])
    // This returns the index of the station of name name[]. Else returns -1
    {
        int a = hashValue(name);
        for (int i = 0; i < 64; i++)
        {
            int h = (a+i)%64;
            if (Stations[h].occupied)
            {
                if (!strcmp(name, Stations[h].Station_Name)) return h;
            }
            else break;
        }
        return -1;
    }

    int findFreeIndex(char key[])
    {
        int h = hashValue(key);
        for (int i = 0; i < 64; i++)
        {
            int a = (h + i) % 64;
            if (!(Stations[a]).occupied)
                return a;
        }
        return -1;
    }

    void Add(char st[], float st_time, char et[], float ed_time)
    {
        int i = find_station(st);
        if (i == -1)
        {
            Station s;
            strcpy(s.Station_Name, st);
            i = findFreeIndex(st);
            if (i == -1) 
            {
                cout << "Unable to add or find station " << st << "\n";
                return;
            }
            else Add_Station(s, i);
        }
        int j = find_station(et);
        if (j == -1)
        {
            Station s;
            strcpy(s.Station_Name, et);
            j = findFreeIndex(et);
            if (j == -1) 
            {
                cout << "Unable to add/find station " << et << "\n";
                return;
            }
            else Add_Station(s, j);
        }
        destination d;
        d.ending_time = ed_time;
        d.starting_time = st_time;
        d.Station_Two = &Stations[j];
        Stations[i].Add_Destination(d);
    }

    void querystation(char sn[], float st)
    {
        int i = find_station(sn);
        if (i == -1)
        {
            cout << "Error: Station " << sn << " Not found\n";
            return;
        }
        Stations[i].query_station(st);
    }

    void query_journey(char st[], float time, char et[])
    {
        int i = find_station(st);
        if (i == -1) 
        {
            cout << "Error: Station " << st << " Not found\n";
            return;
        }
        int j = find_station(et);
        if (j == -1)
        {
            cout << "Error: Station " << et << " Not found\n";
            return;
        }
        Stations[i].queryjourney(time, Stations[j]);
    }
};

#endif