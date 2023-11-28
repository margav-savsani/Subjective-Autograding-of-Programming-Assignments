#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

using namespace std;
#include "DAG.cpp"


int main(int argc, char **argv)
{
    DAG *graph;
    graph = new DAG();
    graph->getSources();
    graph->getSimilarNodePairs();
    graph->caller();
}