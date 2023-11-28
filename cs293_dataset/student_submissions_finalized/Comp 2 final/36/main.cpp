#include "graph.h"
using namespace std;

int main(int argc, char **argv)
{
    string s="outgraph.txt";
    Graph test(s);
    test.printsourcenodes();
    test.printsimilarndoepairs();
    test.collapse();
    return 0;
}
