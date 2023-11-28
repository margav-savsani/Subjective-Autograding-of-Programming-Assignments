#include "late.cpp"

double givemod(int b)
{
    double k = (sqrt(5) - 1) / 2;
    for (int i = 0; i < b; i++)
    {
        k = (37 * k);
        k = k - int(k);
    }
    return k;
}

int hashValue(string s)
{
    double a = 0;
    for (int i = 0; i < s.length(); i++)
    {
        a += (int(s[i]) * givemod(i));
        a = a - int(a);
    }
    int b = (a * 64);
    return b;
}
// struct for storing journey details
struct store
{
    string dest;
    float start;
    float end;
};
// list that  is stored as value with the  station name 
struct mylist
{
    store record[64];
    int N;
    mylist() { N = 0; }
    int get(float a)
    {
        int i;
        for (i = 0; i < N; i++)
        {
            if (record[i].start > a)
            {
                return i;
            }
        }
        return N;
    }

    void put(store x)
    {
        int a = get(x.start);
        for (int i = N - 1; i >= a; i--)
        {
            record[i + 1] = record[i];
        }
        record[a] = x;
        N++;
    }

    void print(float x)
    {
        int a = get(x);
        for (int i = a; i < N; i++)
        {
            cout << record[i].start << " " << record[i].dest<< endl;
        }
    }
};
// making struct to be stored in planner in dictionary as a array i have assumed max 64 stations
struct mystation
{
    string name;
    mylist journey;
};
// main class that will store implementation of all the query using the list class
class Planner
{
    mystation sta_list[64];
    Dictionary late;

public:
    Planner()
    {
        for (int i = 0; i < 64; i++)
        {
            sta_list[i].name = "";
        }
    }
    // impementation of add 
    bool put(string a, string b, float c, float d)
    {
        store value = {b, c, d};
        int x = hashValue(a);
        late.update(a, b, c);
        for (int i = 0; i < 64; i++)
        {
            if (sta_list[(x + i) % 64].name == "")
            {
                sta_list[(x + i) % 64].name = a;
                sta_list[(x + i) % 64].journey.put(value);
                return true;
            }

            else if (sta_list[(x + i) % 64].name == a)
            {
                sta_list[(i + x) % 64].journey.put(value);
                return true;
            }
        }
    }
    // implementation of query_station
    int print(string a, float b)
    {
        int x = hashValue(a);
        for (int i = 0; i < 64; i++)
        {
            if (sta_list[(x + i) % 64].name == "")
            {
                return -1;
            }

            else if (sta_list[(x + i) % 64].name == a)
            {
                sta_list[(i + x) % 64].journey.print(b);
                return 1;
            }
        }
        return -1;
    }
    //implementation of query journey
    int findjourney(string start, string dest, float time)
    {
        int x = hashValue(start);
        int index;
        for (int i = 0; i < 64; i++)
        {
            if (sta_list[(x + i) % 64].name == "")
            {
                return -1;
            }

            else if (sta_list[(x + i) % 64].name == start)
            {
                index = (x + i) % 64;
                break;
            }
        }  
        int rec_start = sta_list[index].journey.get(time);
        for (int i = rec_start; i < sta_list[index].journey.N; i++)
        {   // if direct is the best supporting journey
            if (sta_list[index].journey.record[i].dest == dest)
            {
                cout << sta_list[index].journey.record[i].start<<endl;
                return 0;
            }
            // checking if journey from intermediate station is possible
            if (sta_list[index].journey.record[i].end < late.get(sta_list[index].journey.record[i].dest, dest))
            {
                cout << sta_list[index].journey.record[i].start<<" ";
                int y = hashValue(sta_list[index].journey.record[i].dest);
                int index2;
                for (int j = 0; j < 64; j++)
                {
                    if (sta_list[(y + j) % 64].name == sta_list[index].journey.record[i].dest)
                    {
                        index2 = (y + j) % 64;
                        break;
                    }
                } // searching for the first journey from intermediate station
                cout << sta_list[index2].name<<" ";
                int dest1_start = sta_list[index2].journey.get(sta_list[index].journey.record[i].end);
                for (int j = dest1_start; j < sta_list[index2].journey.N; j++){
                    if (sta_list[index2].journey.record[j].dest == dest)
                    {
                        cout << sta_list[index2].journey.record[j].start << endl;
                        return 0;
                    }
                }
                
            }
        }
        return -1;
    }
    };