#include "planner.h"

int main(){
    Planner* planner = new Planner();
    char lquery[80];

    bool quit = false;


    while(!quit){
        std::cin.getline(lquery, 80);
        Query newQuery;
        strcpy(newQuery.qstring, lquery);

        quit = !planner->QueryHandler(newQuery);
        //cout << quit << endl;

    }

    

    return 0;
}