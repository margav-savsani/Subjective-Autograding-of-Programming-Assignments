#ifndef STD_HEADERS
#include "std_headers.h"
#endif

#include "graph.cpp"
using namespace std;


int main(int argc, char *argv[]){

    Graph *myGraph; //create an object of the class graph
    string graphFileName = argv[1];  //stores the name of the file containing input
    myGraph = new Graph(graphFileName); //initialise  the graph

   
    myGraph->printResults(); //print the required results
}
