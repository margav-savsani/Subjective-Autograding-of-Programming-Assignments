using namespace std;
#include "garph.h"

int main(int argc, char **argv)
{
  Graph *myGraph;

  // if (argc != 2) {
  //   cerr << "Usage: " << argv[0] << " numNodes numEdges graphFile" << endl;
  // }

  // int numNodes = stoi(argv[1]);
  // int numEdges = stoi(argv[2]);
  // string graphFileName = argv[1];

  myGraph = new Graph();
  if (myGraph == nullptr) {
    cerr << "Memory allocation failure." << endl;
    exit(-1);
  }

  
  return 0;
}

