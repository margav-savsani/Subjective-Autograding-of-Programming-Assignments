#include <string>

//Contains the declarations
const int SORTED_ARR_SIZE = 1000;
const int INCREMENT_SIZE = 1000;

struct Journey //Struct representing journey -> start, start time, end, end time
{
    std::string start;
    std::string end;

    float start_time;
    float end_time;
};

class sortedArray
{ //A class of sorted array with functionalities needed to add and access elements
private:
    Journey *A;
    int N;
    int size;

    void grow();

public:
    int getSize();

    sortedArray();
    ~sortedArray();

    int getIndex(float time);

    void insert(Journey J);

    Journey *getJourney(int index);
};

struct Station
{ //A struct for station, for entry in dictionary
    std::string name;
    sortedArray* journey_arr;
    int type{0};

    Station(std::string name)
    {
        this->name = name;
        journey_arr = new sortedArray;
    }

    Station(){
        journey_arr = new sortedArray;
    };

};

const int DICT_SIZE = 128;
class Dictionary{ //Dictionary to store stations
private:
    int N;
    Station* A;

public:
    int hashValue(std::string key);

    int findFreeIndex(std::string key);

    Dictionary();

    ~Dictionary(){
        delete[] A;
    };

    Station* get(std::string key);

    bool put(Station e);

    bool remove(std::string key);
};